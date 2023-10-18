import argparse
import csv
from datetime import datetime
import geopy.distance
import logging
from logging.handlers import TimedRotatingFileHandler
import math
import os
import pandas as pd
import time


class Warehouse:
    
    # Initialize the warehouse with the given areas data.
    def __init__(self):
        
        # Set as False to deative the logger.
        self.logging_enabled = True
        
        # Check if the logger is activated.
        if self.logging_enabled:
            try:
                # Log system configuration.
                log_directory = 'logs'
                os.makedirs(log_directory, exist_ok=True)
                log_filename = os.path.join(log_directory, datetime.now().strftime('%Y-%m-%d') + '-warehouse.log')
                
                handler = TimedRotatingFileHandler(log_filename, when='midnight', interval=1, backupCount=7)
                handler.setFormatter(logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
                
                self.logger = logging.getLogger('warehouse')
                self.logger.setLevel(logging.INFO)
                self.logger.addHandler(handler)
            except Exception as e:
                self.logging_enabled = False
                print(f"Error configuring log handler: {e}")

        # List to store incoming packages.
        self.entries = []
        
        # List to store the distribution report.
        self.report = []

        # Vehicle details.
        self.vehicle = {
            'capacity': 0,
            'current_load': 0,
            'packages':[],
            'current_area': None
        }

        self.traveled_movement = int(0)
        self.traveled_distance = float(0)
        self.traveled_report = []
        self.filename_export = './csv/exports/export_warehouse_' + datetime.now().strftime('%Y-%m-%d') + '.csv'

    # Read the Areas from CSV.
    def get_geographical_areas(self, file = './csv/geographical_areas.csv'):
        try:
            # Init the dict for the areas.
            areas = {}

            # Check if the file exists.
            if not os.path.exists(file):
                if self.logging_enabled:
                    self.logger.error(f"File not found: {file}")
                return areas

            # Check the file permission.
            if not os.access(file, os.R_OK):
                if self.logging_enabled:
                    self.logger.error(f"Permission denied for file: {file}")
                return areas

            # Read the CSV file.
            df = pd.read_csv(file, sep=";", names=['Area ID','Size','Latitude','Longitude','Distance','Distance Rank','Penalty','Score'], skiprows=1, on_bad_lines='skip')

            # Iterate the rows from DataFrame.
            for index, row in df.iterrows():
                if row['Area ID'] == 'Vehicle':
                    # Set the vehicle details.
                    self.vehicle['capacity'] = int(row['Size'])
                    self.vehicle['current_load'] = 0
                    self.vehicle['current_area'] = 'Cargo'
                else:
                    areas[row['Area ID']] = {
                        'size': float(row['Size']) if not math.isnan(row['Size']) else float('inf'),
                        'coordinates': (float(str(row['Latitude']).replace(',','.')), float(str(row['Longitude']).replace(',','.'))),
                        'penalty': row['Penalty'],
                        'score': float(row['Score']) if not math.isnan(row['Score']) else float(0),
                        'packages': []
                    }
                    self.report.append(f'Area {row["Area ID"]} added successfuly!')
                    if self.logging_enabled:
                        self.logger.info(f'Area {row["Area ID"]} added successfuly!')

            return areas
        except FileNotFoundError:
            self.logger.error(f"File not found: {file}")
            return areas
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error reading the areas with geographical coordinates: {e}")
                return areas

    def rank_distance_between_areas(self):
        try:
            areas = self.areas.copy()
            if 'Cargo' in areas:
                del areas['Cargo']
            # Inicializar um dicionário vazio para o ranking
            self.distances_beetween_areas = {}

            # Calcular distâncias e criar ranking
            for i, (area_i, data_i) in enumerate(areas.items()):
                coords_i = data_i['coordinates']
                distances = []
                
                for j, (area_j, data_j) in enumerate(areas.items()):
                    coords_j = data_j['coordinates']
                    distance = 0 if i == j else float(str(geopy.distance.geodesic(coords_i, coords_j))[:-3])
                    distances.append((area_j, distance+data_j['penalty']))
                
                # Ordenar as distâncias e criar o ranking
                distances.sort(key=lambda x: x[1])
                self.distances_beetween_areas[area_i] = [area for area, _ in distances]
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error ranking distances beetween areas: {e}")

    # Update the distances in the CSV with areas.
    def update_distances(self, file='./csv/geographical_areas.csv'):
        try:
            # Read the CSV file.
            df = pd.read_csv(file, sep=";", names=['Area ID','Size','Latitude','Longitude','Distance','Distance Rank','Penalty','Score'], skiprows=1, on_bad_lines='skip')
            cargo_coordinates = ()
            for index, row in df.iterrows():
                area_id = row['Area ID']

                # Skip updating the "Cargo" area.
                if area_id == 'Cargo':
                    cargo_coordinates = (float(row['Latitude'].replace(",", ".")), float(row['Longitude'].replace(",", ".")))
            # Iterate the rows from DataFrame.
            for index, row in df.iterrows():
                area_id = row['Area ID']

                # Skip updating the "Cargo" area.
                if area_id in ('Cargo','Vehicle'):
                    continue

                # Calculate the Haversine distance between the current area and "Cargo".
                current_coordinates = (float(row['Latitude'].replace(",", ".")), float(row['Longitude'].replace(",", ".")))
                new_distance = geopy.distance.geodesic(current_coordinates, cargo_coordinates)
                new_distance = str(new_distance)[:-3].replace('.',',')

                # Update the Distance column in the DataFrame.
                df.at[index, 'Distance'] = new_distance
                #df['Distance Rank'] = df['Distance'].rank(ascending=True, method='min', na_option='bottom')
                df['Distance Rank'] = df.loc[df['Area ID'] != 'Cargo', 'Distance'].rank(ascending=True, method='min', na_option='bottom')
                df.loc[df['Area ID'] == 'Cargo', 'Distance Rank'] = 0.0
                df['Distance Rank'] = df['Distance Rank'].apply(lambda x: int(x) if not math.isnan(x) else 0)
                df['Score'] = df['Distance Rank'] + df['Penalty']
                

                if self.logging_enabled:
                    self.logger.info(f"Distance updated for Area {area_id}")

            # Write the updated DataFrame back to the CSV file.
            df.to_csv(file, sep=';', index=False, header=True)
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error updating distances in the CSV file: {e}")

    # Get packages form the CSV.
    def get_packages(self, area_file = './csv/Consulta.csv', packages_file = './csv/geographical_areas.csv'):

        try:
            areas = self.get_geographical_areas(area_file)
            
            # Check if the file exists.
            if not os.path.exists(packages_file):
                self.logger.error(f"File not found: {packages_file}")

            # Check the file permission.
            if not os.access(packages_file, os.R_OK):
                self.logger.error(f"Permission denied for file: {packages_file}")

            # Read the CSV file.
            df = pd.read_csv(packages_file, sep=";", names=['Cargo Type','Cargo Subtype','Id','Import/Export Status','Operator','Total Weight (MT)','Total Quantity','Voyage','Location'], skiprows=1, on_bad_lines='skip')

            # Filter the data to use only "Steel Slab".
            df = df[df['Cargo Type'] == 'Steel Slab']

            # Initialize a dictionary to count the packages in "Cargo".
            cargo_package_count = {}
            terminal_package_count = {}

            # Iterate the rows from DataFrame.
            for index, row in df.iterrows():
                cargo_subtype = row['Cargo Subtype']
                location = row['Location']

                # Check if the package is at the Cargo.
                if location[0] == 'V':
                    cargo_area = 'Cargo'
                    areas[cargo_area]['packages'].append((cargo_subtype, 0))

                    # Update the package count in "Cargo".
                    if cargo_subtype in cargo_package_count:
                        cargo_package_count[cargo_subtype] += 1
                    else:
                        cargo_package_count[cargo_subtype] = 1

                else:
                    # Get the area SAxx.
                    sa_area = location.split()[0]
                    # Check if its a Valid area.
                    if sa_area in areas:
                        areas[sa_area]['packages'].append((cargo_subtype, 1))
                    else:
                        areas['Cargo']['packages'].append((cargo_subtype, 1))
                        self.report.append(f"Unkown area: {sa_area}")
                        if self.logging_enabled:
                            self.logger.info(f"Unkown area: {sa_area}")
                    
                    # Update the package count in "Cargo".
                    if cargo_subtype in terminal_package_count:
                        terminal_package_count[cargo_subtype] += 1
                    else:
                        terminal_package_count[cargo_subtype] = 1
            
            # Assign the package count in "Cargo" to the Warehouse instance.
            self.cargo_package_count = cargo_package_count
            self.terminal_package_count = terminal_package_count
        except FileNotFoundError:
            self.logger.error(f"File not found: {packages_file}")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error reading the CSV with packages data: {e}")

        try:
            # Print the actual state of each area.
            for area, packages in areas.items():
                self.report.append(f'{area}: {packages}')
                if self.logging_enabled:
                    self.logger.info(f'{area}: {packages}')
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error in printing the state of each area: {e}")
        
        try:
            self.areas = areas
            self.rank_distance_between_areas()
            # Add incoming packages.
            entries = []
            i = 0
            while i < len(self.areas['Cargo']['packages']):
                if self.areas['Cargo']['packages'][i][1] == 0:
                    entries.append(self.areas['Cargo']['packages'].pop(i))
                else:
                    i = i + 1
            for package in entries:
                self.add_entry(package)
            temp = sorted(self.entries, key=lambda x: x[0])
            self.entries = temp
            self.count_packages_in_cargo()
            self.count_packages_in_terminal()
            
            '''
            temp = dict(sorted(self.cargo_package_count.items(), key=lambda item: item[1], reverse=True))
            self.cargo_package_count = temp
            temp_aux = sorted(self.cargo_package_count, key=lambda x: x[1])
            temp = sorted(self.entries, key=lambda x: temp_aux.index(x[0]))
            self.entries = temp
            '''
            temp2 = dict(sorted(self.terminal_package_count.items(), key=lambda item: item[1], reverse=True))
            self.terminal_package_count = temp2
            temp_aux2 = sorted(self.terminal_package_count, key=lambda x: x[1])
            temp2 = sorted(self.entries, key=lambda x: temp_aux2.index(x[0]) if x[0] in temp_aux2 else len(temp_aux2))
            self.entries = temp2
            
            self.create_export_csv()
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error adding entries: {e}")

    # Count type of each package in Terminal.
    def count_packages_in_terminal(self):
        try:
            if hasattr(self, 'terminal_package_count'):
                if self.logging_enabled:
                    self.report.append("Package count in 'Terminal':")
                    if self.logging_enabled:
                        self.logger.info("Package count in 'Terminal':")
                    for package, count in self.terminal_package_count.items():
                        self.report.append(f'{package}: {count}')
                        if self.logging_enabled:
                            self.logger.info(f'{package}: {count}')
            else:
                self.report.append("No package count available as 'get_packages' method has not been called.")
                if self.logging_enabled:
                    self.logger.info("No package count available as 'get_packages' method has not been called.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error counting packages in 'Terminal': {e}")

    # Update noumber of each package in Cargo.
    def update_terminal_package_count(self, package):
        try:
            if package[0] in self.terminal_package_count:
                self.terminal_package_count[package[0]] -= 1
                self.report.append(f"Removed package {package[0]} from 'Terminal' count.")
                if self.logging_enabled:
                    self.logger.info(f"Removed package {package[0]} from 'Terminal' count.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error updating 'Cargo' package count: {e}")

    # Count type of each package in Cargo.
    def count_packages_in_cargo(self):
        try:
            if hasattr(self, 'cargo_package_count'):
                if self.logging_enabled:
                    self.report.append("Package count in 'Cargo':")
                    if self.logging_enabled:
                        self.logger.info("Package count in 'Cargo':")
                    for package, count in self.cargo_package_count.items():
                        self.report.append(f'{package}: {count}')
                        if self.logging_enabled:
                            self.logger.info(f'{package}: {count}')
            else:
                self.report.append("No package count available as 'get_packages' method has not been called.")
                if self.logging_enabled:
                    self.logger.info("No package count available as 'get_packages' method has not been called.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error counting packages in 'Cargo': {e}")

    # Update noumber of each package in Cargo.
    def update_cargo_package_count(self, package):
        try:
            if package[0] in self.cargo_package_count:
                self.cargo_package_count[package[0]] -= 1
                self.report.append(f"Removed package {package[0]} from 'Cargo' count.")
                if self.logging_enabled:
                    self.logger.info(f"Removed package {package[0]} from 'Cargo' count.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error updating 'Cargo' package count: {e}")

    # Add an incoming package to the list of entries.
    def add_entry(self, package):
        try:
            self.entries.append(package)
            self.report.append(f"Added package: {package[0]} to entries.")
            if self.logging_enabled:
                self.logger.info(f"Added package: {package[0]} to entries.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error adding entry: {e}")

    # Destribute packages.
    def distribute_packages(self):
        try:
            while self.vehicle['current_load'] > 0 or len(self.entries) > 0:
                if self.vehicle['current_load'] == 0:
                    # Load the vehicle from "Cargo".
                    self.load_vehicle()
                # Distribute packages from the vehicle to other areas.
                self.distribute_from_vehicle()

                # Unload packages from the vehicle.
                self.vehicle['packages'] = []
                self.vehicle['current_load'] = 0
                movement = float(str(geopy.distance.geodesic(self.areas[self.vehicle['current_area']]['coordinates'], self.areas['Cargo']['coordinates']))[:-3])
                if movement > 0.0:
                    self.traveled_movement += 1
                    self.traveled_distance += movement
                self.vehicle['current_area'] = 'Cargo'

            self.report.append("All packages distributed.")
            self.append_to_csv_export("delivery")
            self.append_to_csv_export("moves")
            if self.logging_enabled:
                self.logger.info("All packages distributed.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error distributing packages: {e}")

    def check_empty_area(self, area):
        return len(self.areas[area]['packages']) == 0
    
    def check_type_of_package_in_area(self, area):
        if not self.check_empty_area(area):
            return self.areas[area]['packages'][0][0]
        else:
            return None

    # Function to load the vehicle from Cargo.
    def load_vehicle(self):
        try:
            # Calculate how many packages can be loaded to the vehicle.
            available_capacity = self.vehicle['capacity'] - self.vehicle['current_load']
            packages_to_load = min(available_capacity, len(self.entries))

            # Load packages to the vehicle.
            for _ in range(packages_to_load):
                self.vehicle['packages'].append(self.entries.pop(0))
                self.vehicle['current_load'] += 1

            self.report.append(f"Loaded {packages_to_load} packages to the vehicle.")
            if self.logging_enabled:
                self.logger.info(f"Loaded {packages_to_load} packages to the vehicle.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error loading the vehicle: {e}")

    def distribute_from_vehicle(self):
        try:
            temporary_entries = []
            # Find the nearest available area for each package in the vehicle.
            old_pkg = ""
            old_area = ""
            num_of_same_pkg = 0
            for index, package in enumerate(self.vehicle['packages']):
                current_coordinates = self.areas[self.vehicle['current_area']]['coordinates']
                cargo_coordinates = self.areas['Cargo']['coordinates']
                area_for_package = self.find_area_for_package(package,  current_coordinates)
                msg = ""
                if area_for_package:
                    self.areas[area_for_package]['packages'].append(package)
                    if old_pkg == "":
                        old_pkg = package
                        old_area = area_for_package
                        num_of_same_pkg += 1
                        if index == len(self.vehicle['packages']) - 1:
                            movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[area_for_package]['coordinates']))[:-3])
                            if movement > 0.0:
                                self.traveled_movement += 1
                                self.traveled_distance += movement
                            msg = f"Move 1 x {package[0]} from {self.vehicle['current_area']} to {area_for_package}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                            self.vehicle['current_area'] = area_for_package
                    elif old_pkg == package and index == len(self.vehicle['packages']) - 1:
                        movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[area_for_package]['coordinates']))[:-3])
                        if movement > 0.0:
                            self.traveled_movement += 1
                            self.traveled_distance += movement
                        num_of_same_pkg += 1
                        msg = f"Move {num_of_same_pkg} x {package[0]} from {self.vehicle['current_area']} to {area_for_package}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                        self.vehicle['current_area'] = area_for_package
                    elif old_pkg == package and index != len(self.vehicle['packages']) - 1:
                        old_area = area_for_package
                        num_of_same_pkg += 1
                    elif old_pkg != package:
                        movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[old_area]['coordinates']))[:-3])
                        if movement > 0.0:
                            self.traveled_movement += 1
                            self.traveled_distance += movement
                        if index == len(self.vehicle['packages']) - 1:
                            msg = f"Move {num_of_same_pkg} x {old_pkg[0]} From {self.vehicle['current_area']} to {old_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                            self.vehicle['current_area'] = old_area
                        else:
                            msg = f"Move {num_of_same_pkg} x {old_pkg[0]} From {self.vehicle['current_area']} to {old_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                            self.vehicle['current_area'] = old_area
                            old_pkg = package
                            old_area = area_for_package
                            num_of_same_pkg = 1
                    if msg != "":
                        self.traveled_report.append(msg)
                        self.report.append(msg)
                        if self.logging_enabled:
                            self.logger.info(msg)
                        if old_pkg != package and index == len(self.vehicle['packages']) - 1:
                            movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[area_for_package]['coordinates']))[:-3])
                            if movement > 0.0:
                                self.traveled_movement += 1
                                self.traveled_distance += movement
                            msg = f"Move {num_of_same_pkg} x {package[0]} From {self.vehicle['current_area']} to {area_for_package}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                            self.traveled_report.append(msg)
                            self.report.append(msg)
                            if self.logging_enabled:
                                self.logger.info(msg)

                    # Update the package count in "Cargo".
                    self.update_cargo_package_count(package)
                    self.report.append(f"Package{package} assigned to Area {area_for_package}")
                    if self.logging_enabled:
                        self.logger.info(f"Package {package} assigned to Area {area_for_package}")
                else:
                    nearest_area = self.find_nearest_available_area(package, cargo_coordinates)
                    if nearest_area:
                        self.areas[nearest_area]['packages'].append(package)
                        if old_pkg == "":
                            old_pkg = package
                            old_area = nearest_area
                            num_of_same_pkg += 1
                            if index == len(self.vehicle['packages']) - 1:
                                movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[nearest_area]['coordinates']))[:-3])
                                if movement > 0.0:
                                    self.traveled_movement += 1
                                    self.traveled_distance += movement
                                msg = f"Move 1 x {package[0]} from {self.vehicle['current_area']} to {nearest_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                                self.vehicle['current_area'] = nearest_area
                        elif old_pkg == package and index == len(self.vehicle['packages']) - 1:
                            num_of_same_pkg += 1
                            movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[nearest_area]['coordinates']))[:-3])
                            if movement > 0.0:
                                self.traveled_movement += 1
                                self.traveled_distance += movement
                            msg = f"Move {num_of_same_pkg} x {package[0]} from {self.vehicle['current_area']} to {nearest_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                            self.vehicle['current_area'] = nearest_area
                        elif old_pkg == package and index != len(self.vehicle['packages']) - 1:
                            old_area = nearest_area
                            num_of_same_pkg += 1
                        elif old_pkg != package:
                            movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[old_area]['coordinates']))[:-3])
                            if movement > 0.0:
                                self.traveled_movement += 1
                                self.traveled_distance += movement
                            if index == len(self.vehicle['packages']) - 1:
                                msg = f"Move {num_of_same_pkg} x {old_pkg[0]} From {self.vehicle['current_area']} to {old_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                                self.vehicle['current_area'] = old_area
                            else:
                                msg = f"Move {num_of_same_pkg} x {old_pkg[0]} From {self.vehicle['current_area']} to {old_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                                self.vehicle['current_area'] = old_area
                                old_area = nearest_area
                                old_pkg = package
                                num_of_same_pkg = 1
                        if msg != "":
                            self.traveled_report.append(msg)
                            self.report.append(msg)
                            if self.logging_enabled:
                                self.logger.info(msg)
                            if old_pkg != package and index == len(self.vehicle['packages']) - 1:
                                movement = float(str(geopy.distance.geodesic(current_coordinates, self.areas[nearest_area]['coordinates']))[:-3])
                                if movement > 0.0:
                                    self.traveled_movement += 1
                                    self.traveled_distance += movement
                                msg = f"Move {num_of_same_pkg} x {package[0]} From {self.vehicle['current_area']} to {nearest_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
                                self.traveled_report.append(msg)
                                self.report.append(msg)
                                if self.logging_enabled:
                                    self.logger.info(msg)
                            
                        # Update the package count in "Cargo".
                        self.update_cargo_package_count(package)
                        self.report.append(f"Package {package} assigned to Area {nearest_area}")
                        if self.logging_enabled:
                            self.logger.info(f"Package {package} assigned to Area {nearest_area}")
                    else:
                        temporary_entries.append(package)
                        self.report.append(f"No available area for package {package[0]}")
                        if self.logging_enabled:
                            self.logger.info(f"No available area for package {package[0]}")

            for entry in temporary_entries:
                self.areas['Cargo']['packages'].append(entry)

            self.report.append("Packages unloaded from the vehicle.")
            if self.logging_enabled:
                self.logger.info("Packages unloaded from the vehicle.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error distributing packages from the vehicle: {e}")

    # Find the nearest area of the same package type.
    def find_area_for_package(self, package_name, current_coordinates):
        try:
            min_distance = float('inf')
            min_score = float('inf')
            nearest_area = None

            for area_name, area_data in self.areas.items():
                filtered_area = [item[0] for item in area_data['packages']]
                if area_name != 'Cargo' and package_name[0] in filtered_area:
                    if len(area_data['packages']) < area_data['size']:
                        distance = geopy.distance.geodesic(current_coordinates, area_data['coordinates'])

                        if area_data.get('score', float('inf')) < min_score or (area_data.get('score', float('inf')) == min_score and distance < min_distance):
                            min_score = area_data.get('score', float('inf'))
                            min_distance = distance
                            nearest_area = area_name

            self.report.append(f"Finding area for package: {nearest_area}")
            if self.logging_enabled:
                self.logger.info(f"Finding area for package: {nearest_area}")
            return nearest_area
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error finding area for package: {e}")
            return nearest_area
    
    def find_area_for_package_except(self, package_name, current_coordinates, except_area):
        try:
            min_distance = float('inf')
            min_score = float('inf')
            nearest_area = None

            for area_name, area_data in self.areas.items():
                filtered_area = [item[0] for item in area_data['packages']]
                if area_name != 'Cargo' and package_name[0] in filtered_area:
                    if area_name == except_area:
                        continue
                    if len(area_data['packages']) < area_data['size']:
                        distance = geopy.distance.geodesic(current_coordinates, area_data['coordinates'])

                        if area_data.get('score', float('inf')) < min_score or (area_data.get('score', float('inf')) == min_score and distance < min_distance):
                            min_score = area_data.get('score', float('inf'))
                            min_distance = distance
                            nearest_area = area_name

            self.report.append(f"Finding area for package: {nearest_area}")
            if self.logging_enabled:
                self.logger.info(f"Finding area for package: {nearest_area}")
            return nearest_area
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error finding area for package: {e}")
            return nearest_area
    
    # Find the nearest area of the same package type.
    def find_full_area(self, package_name, current_coordinates):
        try:
            min_distance = float('inf')
            min_score = float('inf')
            nearest_area = None

            for area_name, area_data in self.areas.items():
                filtered_area = [item[0] for item in area_data['packages']]

                if area_name != 'Cargo' and package_name[0] in filtered_area:
                    if len(area_data['packages']) == area_data['size']:
                        distance = geopy.distance.geodesic(current_coordinates, area_data['coordinates'])
                        if area_data.get('score', float('inf')) < min_score or (area_data.get('score', float('inf')) == min_score and distance < min_distance):
                            min_score = area_data.get('score', float('inf'))
                            min_distance = distance
                            nearest_area = area_name

            self.report.append(f"Finding area for package: {nearest_area}")
            if self.logging_enabled:
                self.logger.info(f"Finding area for package: {nearest_area}")
            return nearest_area
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error finding area for package: {e}")
            return nearest_area

    # Find the nearest available area for a package.
    def find_nearest_available_area(self, package_name, current_coordinates, current_area=None):
        try:
            nearest_area = None 
            min_distance = float('inf')
            min_score = float('inf')

            for area_name, area_data in self.areas.items():
                if area_name != current_area and area_name != 'Cargo' and (not area_data['packages'] or len(area_data['packages']) < area_data['size']):
                    # Check if the area does not have any other package.
                    filtered_area = [item[0] for item in area_data['packages']]
                    if not any(package_name[0] != pkg for pkg in filtered_area):
                        distance = geopy.distance.geodesic(current_coordinates, area_data['coordinates'])
                        if area_data.get('score', float('inf')) < min_score or (area_data.get('score', float('inf')) == min_score and distance < min_distance):
                            min_score = area_data.get('score', float('inf'))
                            min_distance = distance
                            nearest_area = area_name

            self.report.append(f"Finding nearest available area: {nearest_area}")
            if self.logging_enabled:
                self.logger.info(f"Finding nearest available area: {nearest_area}")
            return nearest_area
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error finding nearest available area: {e}")
            return nearest_area

    def reorganize_area(self):
        try:
            for pkg, pkg_count in self.cargo_package_count.items():
                area = self.find_area_for_package((pkg,1), self.areas['Cargo']['coordinates'])
                if area != None:
                    cur_area_pgks_avaible = self.areas[area]['size'] - len(self.areas[area]['packages'])
                    if cur_area_pgks_avaible >= pkg_count:
                        continue
                    else:
                        pkg_count -= cur_area_pgks_avaible
                        new_area = self.distances_beetween_areas[area][1]
                        type_of_package = self.check_type_of_package_in_area(new_area)
                        if type_of_package != pkg:
                            if(len(self.areas[new_area]['packages']) <= self.areas[new_area]['size'] * .25):
                                area_to_move = self.find_area_for_package_except((type_of_package, 0), self.areas[new_area]['coordinates'], new_area)
                                if area_to_move == None:
                                    area_to_move =  self.find_nearest_available_area(type_of_package, self.areas[new_area]['coordinates'], new_area)
                                self.move_packages_beetween_areas(new_area, area_to_move, type_of_package)
                else:
                
                    area = self.find_full_area((pkg,1), self.areas['Cargo']['coordinates'])
                    if area != None:
                        pkg_count -= cur_area_pgks_avaible
                        new_area = self.distances_beetween_areas[area][1]
                        type_of_package = self.check_type_of_package_in_area(new_area)
                        if type_of_package != pkg:
                            #cur_area_pgks_avaible = self.areas[new_area]['size'] - len(self.areas[new_area]['packages'])
                            if(len(self.areas[new_area]['packages']) <= self.areas[new_area]['size'] * .25):
                                area_to_move = self.find_area_for_package_except((type_of_package, 0), self.areas[new_area]['coordinates'], new_area)
                                if area_to_move == None:
                                    area_to_move =  self.find_nearest_available_area(type_of_package, self.areas[new_area]['coordinates'], new_area)
                                self.move_packages_beetween_areas(new_area, area_to_move, type_of_package)
            self.append_to_csv_export("terminal")
            self.append_to_csv_export("moves_reorganize")
            self.traveled_report = []
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error reorganizing area: {e}")

    def move_packages_beetween_areas(self, source_area, destination_area, package_type):
        try:
            # Mova pacotes da área de origem para a área de destino
            source_area_packages = self.areas[source_area]['packages']
            packages_to_move = [(pkg[0], 1) for pkg in source_area_packages if pkg[0] == package_type]
            # Adicione pacotes à área de destino
            self.areas[destination_area]['packages'].extend(packages_to_move)
            # Remova pacotes da área de origem
            self.areas[source_area]['packages'] = [(pkg[0], 1) for pkg in source_area_packages if pkg[0] != package_type]

            movement = float(str(geopy.distance.geodesic(self.areas[source_area]['coordinates'], self.areas[destination_area]['coordinates']))[:-3])

            self.traveled_movement += (math.ceil(len(source_area_packages) / self.vehicle['capacity']) * 2) - 1
            self.traveled_distance += self.traveled_movement * movement

            msg = f"Move {len(source_area_packages)} x {package_type} from {source_area} to {destination_area}. Moved {str('%.3f'%float(movement)).replace('.',',')} km."
            self.traveled_report.append(msg)
            self.report.append(msg)
            if self.logging_enabled:
                self.logger.info(msg)

        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error moving packages: {e}")

    # Create a CSV file named 'export.csv' and write packages from each area to it.
    def create_export_csv(self):
        try:
            time.sleep(1)
            csv_filename = self.filename_export
            with open(csv_filename, mode='w', newline='') as csv_file:
                # Get the area names.
                fieldnames = list(self.areas.keys())
                # Remove 'Cargo' from the field list (it will be added first).
                fieldnames.remove('Cargo')

                # Add 'Cargo' as the first field.
                fieldnames.insert(0, 'Cargo')
                fieldnames.insert(0, '')

                writer = csv.DictWriter(csv_file, fieldnames=fieldnames, delimiter=';')
                writer.writeheader()  # Write the CSV header.

                # Add a blank row after the header.
                writer.writerow({})
                filtered_data_terminal = {}
                filtered_data_delivery = {}
                for area, data_dict in self.areas.items():
                    filtered_package_terminal = [(string, value) for string, value in data_dict["packages"] if value == 1]
                    if filtered_package_terminal:
                        filtered_data_terminal[area] = {"packages": filtered_package_terminal}
                    filtered_package_delivery = [(string, value) for string, value in data_dict["packages"] if value == 0]
                    if filtered_package_delivery:
                        filtered_data_delivery[area] = {"packages": filtered_package_delivery}
                
                # Find the maximum number of packages among all areas including 'Cargo'.
                max_num_packages_already_in_areas = 0
                try:
                    for area_name, area in filtered_data_terminal.items():
                        package = area.get("packages", [])
                        package_size = sum(1 for name, value in package if value == 1)
                        if package_size > max_num_packages_already_in_areas:
                            max_num_packages_already_in_areas = package_size
                except Exception as e:
                    max_num_packages_already_in_areas = 0
                try:
                    max_num_packages = max((len(filtered_data_delivery[area_name]['packages']) if area_name != "" else 0) for area_name in filtered_data_delivery.keys())
                except Exception as e:
                    max_num_packages = 0
                
                writer.writerow({"": "Terminal (Now):"})
                for i in range(0, max_num_packages_already_in_areas):
                    row_data = {area_name: '' for area_name in fieldnames}
                    for area_name in filtered_data_terminal.keys():
                        if area_name == "":
                            continue
                        if i < len(filtered_data_terminal[area_name]['packages']) and filtered_data_terminal[area_name]['packages'][i][1] == 1:
                            row_data[area_name] = filtered_data_terminal[area_name]['packages'][i][0]
                    writer.writerow(row_data)
                writer.writerow({})
            
            self.report.append("CSV file 'export.csv' created successfully.")
            if self.logging_enabled:
                self.logger.info("CSV file 'export.csv' created successfully.")
        except PermissionError:
            if self.logging_enabled:
                self.logger.error("CSV file 'export.csv' is already open by another process.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error creating CSV file: {e}")

    def append_to_csv_export(self, type_of_append="terminal"):
        try:
            csv_filename = self.filename_export
            
            with open(csv_filename , 'a', newline='') as csv_file:
                
                # Check if the file exists.
                if not os.path.exists(csv_filename):
                    self.logger.error(f"File not found: {csv_filename}")

                # Check the file permission.
                if not os.access(csv_filename, os.R_OK):
                    self.logger.error(f"Permission denied for file: {csv_filename}")
                
                # Get the area names.
                fieldnames = list(self.areas.keys())
                # Remove 'Cargo' from the field list (it will be added first).
                fieldnames.remove('Cargo')

                # Add 'Cargo' as the first field.
                fieldnames.insert(0, 'Cargo')
                fieldnames.insert(0, '')

                writer = csv.DictWriter(csv_file, fieldnames=fieldnames, delimiter=';')
                
                try:
                    filtered_data_terminal = {}
                    filtered_data_delivery = {}
                    for area, data_dict in self.areas.items():
                        filtered_package_terminal = [(string, value) for string, value in data_dict["packages"] if value == 1]
                        if filtered_package_terminal:
                            filtered_data_terminal[area] = {"packages": filtered_package_terminal}
                        filtered_package_delivery = [(string, value) for string, value in data_dict["packages"] if value == 0]
                        if filtered_package_delivery:
                            filtered_data_delivery[area] = {"packages": filtered_package_delivery}
                except Exception as e:
                    if self.logging_enabled:
                        self.logger.error(f"Error appending CSV file: Filtered_dada {e}")


                # Find the maximum number of packages among all areas including 'Cargo'.
                max_num_packages_already_in_areas = 0
                try:
                    for area_name, area in filtered_data_terminal.items():
                        package = area.get("packages", [])
                        package_size = sum(1 for name, value in package if value == 1)
                        if package_size > max_num_packages_already_in_areas:
                            max_num_packages_already_in_areas = package_size
                except Exception as e:
                    max_num_packages_already_in_areas = 0
                try:
                    max_num_packages = max((len(filtered_data_delivery[area_name]['packages']) if area_name != "" else 0) for area_name in filtered_data_delivery.keys())
                except Exception as e:
                    max_num_packages = 0
                    #if self.logging_enabled:
                    #    self.logger.error(f"Error appending CSV file: Max Num Packages {e}")
                
                try:
                    if type_of_append == "terminal":
                        writer.writerow({"": "Terminal (Reorganized):"})
                        for i in range(0, max_num_packages_already_in_areas):
                            row_data = {area_name: '' for area_name in fieldnames}
                            for area_name in filtered_data_terminal.keys():
                                if area_name == "":
                                    continue
                                if i < len(filtered_data_terminal[area_name]['packages']) and filtered_data_terminal[area_name]['packages'][i][1] == 1:
                                    row_data[area_name] = filtered_data_terminal[area_name]['packages'][i][0]
                            writer.writerow(row_data)
                        writer.writerow({})

                    elif type_of_append == "delivery":
                        writer.writerow({"": "Delivery (In Trip):"})
                        for i in range(max_num_packages):
                            row_data = {area_name: '' for area_name in fieldnames}
                            for area_name in fieldnames:
                                if area_name in filtered_data_delivery.keys() and i < len(filtered_data_delivery[area_name]['packages']):
                                    row_data[area_name] = filtered_data_delivery[area_name]['packages'][i][0]
                            writer.writerow(row_data)
                        writer.writerow({})
                    
                    elif type_of_append == "moves_reorganize":
                        writer.writerow({"": "Movements"})
                        for movement in self.traveled_report:
                            writer.writerow({"Cargo": movement})
                        writer.writerow({})

                    elif type_of_append == "moves":
                        writer.writerow({"": "Movements"})
                        for movement in self.traveled_report:
                            writer.writerow({"Cargo": movement})
                        writer.writerow({})
                        writer.writerow({"": "Number of Movements:", "Cargo": self.traveled_movement})
                        writer.writerow({"": "Vehicle Transit Distance:", "Cargo": str('%.3f'%float(self.traveled_distance)).replace('.',',') + ' km'})
                except Exception as e:
                    if self.logging_enabled:
                        self.logger.error(f"Error appending CSV file: Append functions {e}")
                
            self.report.append("CSV file 'export.csv' appended successfully.")
            if self.logging_enabled:
                self.logger.info("CSV file 'export.csv' appended successfully.")
        except FileNotFoundError:
            self.logger.error(f"File not found: {csv_filename}")
        except PermissionError:
            if self.logging_enabled:
                self.logger.error("CSV file 'export.csv' is already open by another process.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error appending CSV file: {e}")

    def create_report_csv(self):
        try:
            if self.logging_enabled:
                for report in self.report:
                    self.logger.info(report)
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error printing report: {e}")
        try:
            csv_filename = './csv/reports/report_' + datetime.now().strftime('%Y-%m-%d') + '.csv'
            time.sleep(1)

            with open(csv_filename, mode='w', newline='') as csv_file:
                writer = csv.writer(csv_file)
                for entry in self.report:
                    writer.writerow([entry])

            if self.logging_enabled:
                self.logger.info(f"CSV file '{csv_filename}' created successfully.")
        except PermissionError:
            if self.logging_enabled:
                self.logger.error(f"CSV file '{csv_filename}' is already open by another process.")
        except Exception as e:
            if self.logging_enabled:
                self.logger.error(f"Error creating report CSV file: {e}")


def main():

    parser = argparse.ArgumentParser(description='Warehouse Script')
    parser.add_argument('-f', '--area_file', type=str, default='./csv/geographical_areas.csv', help='Path to area CSV file')
    parser.add_argument('-p', '--packages_file', type=str, default='./csv/Consulta.csv', help='Path to packages CSV file')
    parser.add_argument('-u', '--update_area', action='store_true')
    parser.add_argument('-r', '--report', action='store_true')
    args = parser.parse_args()

    # Check if the --areea_type is valid.
    if args.update_area:
        warehouse = Warehouse()
        warehouse.update_distances()
    else:
        # Check if --area_file exists and readeable.
        if not os.path.isfile(args.area_file) or not os.access(args.area_file, os.R_OK):
            print(f"Error: {args.area_file} does not exist or is not accessible.")
        else:
            # Check if --package_file exists and readeable.
            if not os.path.isfile(args.packages_file) or not os.access(args.packages_file, os.R_OK):
                print(f"Error: {args.packages_file} does not exist or is not accessible.")
            else:
                # Create an instance of the warehouse with the areas (by type of coordinates, it can be cartesian or geographical).
                warehouse = Warehouse()
                warehouse.get_packages(args.area_file, args.packages_file)
                warehouse.reorganize_area()
                warehouse.distribute_packages()
                # Print the distribution report.
                if args.report:
                    warehouse.create_report_csv()

if __name__ == "__main__":
    main()