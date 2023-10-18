from bs4 import BeautifulSoup
import requests
import time

'''
def obter_ids_tbody(url):
    # Faz uma requisição HTTP para obter o código HTML da página
    response = requests.get(url)

    if response.status_code == 200:
        # Analisa o HTML usando BeautifulSoup
        soup = BeautifulSoup(response.text, 'html.parser')

        # Encontrar a tabela com classe "app-table app-wide"
        table = soup.find('table', class_='app-table app-wide')

        if table:
            # Encontrar todos os elementos tbody com a classe 'surebet_record'
            tbody_elements = table.find_all('tbody', class_='surebet_record')

            # Extrair e salvar os IDs em uma lista
            id_list = [tbody.get('id') for tbody in tbody_elements]

            return id_list
        else:
            return "Nenhuma tabela encontrada com a classe 'app-table app-wide'"
    else:
        return f"Erro ao acessar a URL. Código de status: {response.status_code}"

def main():
    url = 'https://pt.surebet.com/surebets?utf8=%E2%9C%93&filter%5Bselected%5D%5B%5D=&filter%5Bselected%5D%5B%5D=33821015&filter%5Bsave%5D=&filter%5Bcurrent_id%5D=33821015&selector%5Border%5D=profit&selector%5Boutcomes%5D%5B%5D=&selector%5Boutcomes%5D%5B%5D=2&selector%5Boutcomes%5D%5B%5D=3&selector%5Bmin_profit%5D=&selector%5Bmax_profit%5D=&selector%5Bmin_roi%5D=&selector%5Bmax_roi%5D=&selector%5Bsettled_in%5D=604800&selector%5Bbookies_settings%5D=0%3A67%3A%3A%3B0%3A105%3A%3A%3B0%3A72%3A%3A%3B4%3A66%3A%3A%3B0%3A76%3A%3A%3B0%3A93%3A%3A%3B0%3A182%3A%3A%3B0%3A74%3A%3A%3B0%3A37%3A%3A%3B0%3A148%3A%3A%3B0%3A211%3A%3A%3B0%3A114%3A%3A%3B0%3A260%3A%3A%3B0%3A101%3A%3A%3B0%3A132%3A%3A%3B0%3A42%3A%3A%3B0%3A40%3A%3A%3B0%3A225%3A%3A%3B0%3A126%3A%3A%3B0%3A21%3A%3A%3B0%3A70%3A%3A%3B0%3A263%3A%3A%3B0%3A246%3A%3A%3B4%3A26%3A%3A%3B0%3A139%3A%3A%3B0%3A111%3A%3A%3B0%3A36%3A%3A%3B0%3A150%3A%3A%3B4%3A202%3A%3A%3B0%3A151%3A%3A%3B0%3A23%3A%3A%3B0%3A204%3A%3A%3B0%3A200%3A%3A%3B0%3A203%3A%3A%3B0%3A0%3A%3A%3B0%3A116%3A%3A%3B0%3A32%3A%3A%3B0%3A138%3A%3A%3B0%3A1%3A%3A%3B0%3A65%3A%3A%3B0%3A161%3A%3A%3B0%3A29%3A%3A%3B0%3A10%3A%3A%3B0%3A107%3A%3A%3B0%3A106%3A%3A%3B0%3A45%3A%3A%3B0%3A228%3A%3A%3B0%3A34%3A%3A%3B0%3A77%3A%3A%3B0%3A58%3A%3A%3B0%3A253%3A%3A%3B0%3A165%3A%3A%3B0%3A100%3A%3A%3B0%3A153%3A%3A%3B0%3A95%3A%3A%3B0%3A180%3A%3A%3B4%3A208%3A%3A%3B0%3A48%3A%3A%3B0%3A14%3A%3A%3B0%3A197%3A%3A%3B4%3A152%3A%3A%3B0%3A11%3A%3A%3B0%3A188%3A%3A%3B0%3A38%3A%3A%3B0%3A147%3A%3A%3B0%3A52%3A%3A%3B0%3A198%3A%3A%3B0%3A55%3A%3A%3B0%3A187%3A%3A%3B0%3A33%3A%3A%3B0%3A13%3A%3A%3B0%3A68%3A%3A%3B0%3A176%3A%3A%3B0%3A125%3A%3A%3B0%3A248%3A%3A%3B0%3A236%3A%3A%3B0%3A49%3A%3A%3B0%3A215%3A%3A%3B0%3A113%3A%3A%3B0%3A62%3A%3A%3B0%3A75%3A%3A%3B4%3A12%3A%3A%3B0%3A193%3A%3A%3B4%3A90%3A%3A%3B0%3A46%3A%3A%3B0%3A229%3A%3A%3B0%3A210%3A%3A%3B0%3A146%3A%3A%3B0%3A117%3A%3A%3B0%3A135%3A%3A%3B0%3A24%3A%3A%3B0%3A92%3A%3A%3B0%3A88%3A%3A%3B0%3A73%3A%3A%3B0%3A261%3A%3A%3B0%3A144%3A%3A%3B0%3A121%3A%3A%3B0%3A154%3A%3A%3B0%3A129%3A%3A%3B0%3A214%3A%3A%3B4%3A56%3A%3A%3B0%3A104%3A%3A%3B4%3A108%3A%3A%3B0%3A230%3A%3A%3B4%3A22%3A%3A%3B0%3A145%3A%3A%3B0%3A136%3A%3A%3B0%3A109%3A%3A%3B0%3A257%3A%3A%3B0%3A5%3A%3A%3B0%3A6%3A%3A%3B0%3A60%3A%3A%3B0%3A112%3A%3A%3B4%3A245%3A%3A%3B0%3A235%3A%3A%3B0%3A175%3A%3A%3B0%3A224%3A%3A%3B0%3A190%3A%3A%3B0%3A4%3A%3A%3B0%3A183%3A%3A%3B0%3A242%3A%3A%3B0%3A213%3A%3A%3B0%3A244%3A%3A%3B0%3A30%3A%3A%3B0%3A15%3A%3A%3B0%3A212%3A%3A%3B0%3A219%3A%3A%3B0%3A128%3A%3A%3B0%3A233%3A%3A%3B0%3A50%3A%3A%3B0%3A9%3A%3A%3B0%3A179%3A%3A%3B0%3A259%3A%3A%3B0%3A178%3A%3A%3B0%3A41%3A%3A%3B0%3A85%3A%3A%3B0%3A84%3A%3A%3B0%3A130%3A%3A%3B0%3A133%3A%3A%3B0%3A247%3A%3A%3B0%3A3%3A%3A%3B0%3A131%3A%3A%3B4%3A240%3A%3A%3B0%3A8%3A%3A%3B0%3A118%3A%3A%3B0%3A89%3A%3A%3B0%3A166%3A%3A%3B0%3A124%3A%3A%3B0%3A226%3A%3A%3B4%3A209%3A%3A%3B0%3A82%3A%3A%3B0%3A63%3A%3A%3B0%3A83%3A%3A%3B0%3A98%3A%3A%3B0%3A99%3A%3A%3B0%3A61%3A%3A%3B0%3A167%3A%3A%3B0%3A20%3A%3A%3B0%3A137%3A%3A%3B0%3A141%3A%3A%3B0%3A19%3A%3A%3B0%3A142%3A%3A%3B4%3A164%3A%3A%3B0%3A249%3A%3A%3B0%3A39%3A%3A%3B0%3A174%3A%3A%3B0%3A31%3A%3A%3B0%3A54%3A%3A%3B0%3A51%3A%3A%3B0%3A181%3A%3A%3B0%3A2%3A%3A%3B0%3A87%3A%3A%3B0%3A143%3A%3A%3B0%3A122%3A%3A%3B4%3A7%3A%3A%3B0%3A189%3A%3A%3B0%3A237%3A%3A%3B0%3A156%3A%3A%3B0%3A47%3A%3A%3B0%3A234%3A%3A%3B0%3A251%3A%3A%3B0%3A262%3A%3A%3B0%3A134%3A%3A%3B0%3A218%3A%3A%3B0%3A123%3A%3A%3B0%3A94%3A%3A%3B0%3A254%3A%3A%3B0%3A25%3A%3A%3B0%3A69%3A%3A%3B0%3A140%3A%3A%3B0%3A119%3A%3A%3B0%3A16%3A%3A%3B0%3A207%3A%3A%3B0%3A232%3A%3A%3B0%3A223%3A%3A%3B0%3A163%3A%3A%3B0%3A256%3A%3A%3B0%3A97%3A%3A%3B0%3A173%3A%3A%3B4%3A191%3A%3A%3B0%3A186%3A%3A%3B4%3A192%3A%3A%3B0%3A43%3A%3A%3B0%3A243%3A%3A%3B0%3A199%3A%3A%3B0%3A103%3A%3A%3B0%3A159%3A%3A%3B0%3A184%3A%3A%3B0%3A18%3A%3A%3B0%3A35%3A%3A%3B0%3A59%3A%3A%3B0%3A64%3A%3A%3B0%3A216%3A%3A%3B0%3A86%3A%3A%3B0%3A120%3A%3A%3B0%3A205%3A%3A%3B0%3A149%3A%3A%3B0%3A127%3A%3A%3B0%3A115%3A%3A%3B0%3A17%3A%3A%3B4%3A110%3A%3A%3B0%3A238%3A%3A%3B0%3A102%3A%3A%3B0%3A239%3A%3A%3B0%3A217%3A%3A%3B0%3A155%3A%3A%3B0%3A96%3A%3A%3B0%3A28%3A%3A%3B0%3A220%3A%3A%3B0%3A222%3A%3A%3B0%3A250%3A%3A%3B0%3A252%3A%3A%3B0%3A44%3A%3A%3B0%3A196%3A%3A%3B0%3A227%3A%3A%3B0%3A206%3A%3A%3B0%3A221%3A%3A%3B0%3A71%3A%3A%3B0%3A79%3A%3A%3B0%3A80%3A%3A%3B0%3A78%3A%3A%3B0%3A57%3A%3A%3B0%3A81%3A%3A%3B0%3A27%3A%3A&selector%5Bexclude_sports_ids_str%5D=56+57+43+32+1+2+3+55+60+7+6+5+28+44+9+26+34+10+11+39+47+48+49+59+27+53+54+58+16+30+13+29+45+19+33+31+40+64+42+41+20+62+61+50+51+63+21+37+23+35+38+25&selector%5Bextra_filters%5D=&commit=Filtrar&narrow='
    ids_antigos = []

    while True:
        result = obter_ids_tbody(url)

        # Verificar se há valores novos na lista
        novos_ids = [item for item in result if item not in ids_antigos]

        # Se houver valores novos, imprimir e atualizar a lista antiga
        if novos_ids:
            print("IDs Novos:")
            for item in novos_ids:
                print(item)
            ids_antigos = result
        time.sleep(5)

if __name__ == "__main__":
    main()

'''
def extrair_dados_tbody(tbody):
    print('aqui')
    # Encontrar a segunda td da primeira tr
    chave = tbody.find('tr').find_all('td')[1].find('span').text

    # Encontrar a terceira td da primeira tr
    valor = tbody.find('tr').find_all('td')[2].find('span').text

    return {chave: valor}

def obter_dados_tbody(url, ids_antigos):
    # Faz uma requisição HTTP para obter o código HTML da página
    response = requests.get(url)
    if response.status_code == 200:
        # Analisa o HTML usando BeautifulSoup
        time.sleep(1)
        soup = BeautifulSoup(response.text, 'html.parser')
        # Encontrar a tabela com classe "app-table app-wide"
        table = soup.find('table', class_='app-table app-wide')
        print(table)
        if table:
            # Encontrar todos os elementos tbody com a classe 'surebet_record'
            tbody_elements = table.find_all('tbody', class_='surebet_record')

            # Extrair e salvar os IDs em uma lista
            id_list = [tbody.get('id') for tbody in tbody_elements]

            # Verificar se há valores novos na lista
            novos_ids = [item for item in id_list if item not in ids_antigos]

            # Lista para armazenar os dados dos novos IDs
            novos_dados = []

            for novo_id in novos_ids:
                # Encontrar o elemento tbody pelo ID
                novo_tbody = table.find('tbody', {'id': novo_id})

                # Extrair dados do novo tbody
                dados_tbody = extrair_dados_tbody(novo_tbody)

                # Adicionar dados à lista
                novos_dados.append(dados_tbody)

            # Atualizar a lista antiga
            ids_antigos = id_list

            return novos_dados, ids_antigos

        else:
            return "Nenhuma tabela encontrada com a classe 'app-table app-wide'", ids_antigos
    else:
        return f"Erro ao acessar a URL. Código de status: {response.status_code}", ids_antigos

# Substitua a URL abaixo pela URL real que você deseja analisar
url = "https://pt.surebet.com/surebets?utf8=%E2%9C%93&filter%5Bselected%5D%5B%5D=&filter%5Bselected%5D%5B%5D=33916940&filter%5Bsave%5D=&filter%5Bcurrent_id%5D=33916940&selector%5Border%5D=profit&selector%5Boutcomes%5D%5B%5D=&selector%5Boutcomes%5D%5B%5D=2&selector%5Boutcomes%5D%5B%5D=3&selector%5Bmin_profit%5D=3.0&selector%5Bmax_profit%5D=&selector%5Bmin_roi%5D=&selector%5Bmax_roi%5D=&selector%5Bsettled_in%5D=604800&selector%5Bbookies_settings%5D=0%3A67%3A%3A%3B0%3A105%3A%3A%3B0%3A72%3A%3A%3B4%3A66%3A%3A%3B0%3A76%3A%3A%3B0%3A93%3A%3A%3B0%3A182%3A%3A%3B0%3A74%3A%3A%3B0%3A37%3A%3A%3B0%3A148%3A%3A%3B0%3A211%3A%3A%3B0%3A114%3A%3A%3B0%3A260%3A%3A%3B0%3A101%3A%3A%3B0%3A132%3A%3A%3B0%3A42%3A%3A%3B0%3A40%3A%3A%3B0%3A225%3A%3A%3B0%3A126%3A%3A%3B0%3A21%3A%3A%3B0%3A70%3A%3A%3B0%3A263%3A%3A%3B0%3A246%3A%3A%3B4%3A26%3A%3A%3B0%3A139%3A%3A%3B0%3A111%3A%3A%3B0%3A36%3A%3A%3B0%3A150%3A%3A%3B4%3A202%3A%3A%3B0%3A151%3A%3A%3B0%3A23%3A%3A%3B0%3A204%3A%3A%3B0%3A200%3A%3A%3B0%3A203%3A%3A%3B0%3A0%3A%3A%3B0%3A116%3A%3A%3B0%3A32%3A%3A%3B0%3A138%3A%3A%3B0%3A1%3A%3A%3B0%3A65%3A%3A%3B0%3A161%3A%3A%3B0%3A29%3A%3A%3B0%3A10%3A%3A%3B0%3A107%3A%3A%3B0%3A106%3A%3A%3B0%3A45%3A%3A%3B0%3A228%3A%3A%3B0%3A34%3A%3A%3B0%3A77%3A%3A%3B0%3A58%3A%3A%3B0%3A253%3A%3A%3B0%3A165%3A%3A%3B0%3A100%3A%3A%3B0%3A153%3A%3A%3B0%3A95%3A%3A%3B0%3A180%3A%3A%3B4%3A208%3A%3A%3B0%3A48%3A%3A%3B0%3A14%3A%3A%3B0%3A197%3A%3A%3B0%3A152%3A%3A%3B0%3A11%3A%3A%3B0%3A188%3A%3A%3B0%3A38%3A%3A%3B0%3A147%3A%3A%3B0%3A52%3A%3A%3B0%3A198%3A%3A%3B0%3A55%3A%3A%3B0%3A187%3A%3A%3B0%3A33%3A%3A%3B4%3A13%3A%3A%3B0%3A68%3A%3A%3B0%3A176%3A%3A%3B0%3A125%3A%3A%3B4%3A248%3A%3A%3B0%3A236%3A%3A%3B0%3A49%3A%3A%3B0%3A215%3A%3A%3B0%3A113%3A%3A%3B0%3A62%3A%3A%3B0%3A75%3A%3A%3B4%3A12%3A%3A%3B0%3A193%3A%3A%3B0%3A90%3A%3A%3B0%3A46%3A%3A%3B0%3A229%3A%3A%3B0%3A210%3A%3A%3B0%3A146%3A%3A%3B0%3A117%3A%3A%3B0%3A135%3A%3A%3B0%3A24%3A%3A%3B0%3A92%3A%3A%3B0%3A88%3A%3A%3B0%3A73%3A%3A%3B0%3A261%3A%3A%3B0%3A144%3A%3A%3B0%3A121%3A%3A%3B0%3A154%3A%3A%3B0%3A129%3A%3A%3B0%3A214%3A%3A%3B0%3A56%3A%3A%3B0%3A104%3A%3A%3B0%3A108%3A%3A%3B0%3A230%3A%3A%3B0%3A22%3A%3A%3B0%3A145%3A%3A%3B0%3A136%3A%3A%3B0%3A109%3A%3A%3B0%3A257%3A%3A%3B0%3A5%3A%3A%3B0%3A6%3A%3A%3B0%3A60%3A%3A%3B0%3A112%3A%3A%3B4%3A245%3A%3A%3B0%3A235%3A%3A%3B0%3A175%3A%3A%3B0%3A224%3A%3A%3B0%3A190%3A%3A%3B0%3A4%3A%3A%3B0%3A183%3A%3A%3B0%3A242%3A%3A%3B0%3A213%3A%3A%3B0%3A244%3A%3A%3B0%3A30%3A%3A%3B0%3A15%3A%3A%3B0%3A212%3A%3A%3B4%3A219%3A%3A%3B0%3A128%3A%3A%3B0%3A233%3A%3A%3B0%3A50%3A%3A%3B0%3A9%3A%3A%3B0%3A179%3A%3A%3B0%3A259%3A%3A%3B0%3A178%3A%3A%3B0%3A41%3A%3A%3B0%3A85%3A%3A%3B0%3A84%3A%3A%3B0%3A130%3A%3A%3B0%3A133%3A%3A%3B0%3A247%3A%3A%3B0%3A3%3A%3A%3B0%3A131%3A%3A%3B4%3A240%3A%3A%3B0%3A8%3A%3A%3B0%3A118%3A%3A%3B0%3A89%3A%3A%3B0%3A166%3A%3A%3B0%3A124%3A%3A%3B0%3A226%3A%3A%3B4%3A209%3A%3A%3B0%3A82%3A%3A%3B0%3A63%3A%3A%3B0%3A83%3A%3A%3B0%3A98%3A%3A%3B0%3A99%3A%3A%3B0%3A61%3A%3A%3B0%3A167%3A%3A%3B0%3A20%3A%3A%3B0%3A137%3A%3A%3B0%3A141%3A%3A%3B0%3A19%3A%3A%3B0%3A142%3A%3A%3B0%3A164%3A%3A%3B0%3A249%3A%3A%3B0%3A39%3A%3A%3B4%3A174%3A%3A%3B0%3A31%3A%3A%3B0%3A54%3A%3A%3B0%3A51%3A%3A%3B0%3A181%3A%3A%3B0%3A2%3A%3A%3B0%3A87%3A%3A%3B0%3A143%3A%3A%3B0%3A122%3A%3A%3B4%3A7%3A%3A%3B0%3A189%3A%3A%3B0%3A237%3A%3A%3B0%3A156%3A%3A%3B0%3A47%3A%3A%3B0%3A234%3A%3A%3B0%3A251%3A%3A%3B0%3A262%3A%3A%3B0%3A134%3A%3A%3B0%3A218%3A%3A%3B0%3A123%3A%3A%3B0%3A94%3A%3A%3B0%3A254%3A%3A%3B0%3A25%3A%3A%3B0%3A69%3A%3A%3B0%3A140%3A%3A%3B0%3A119%3A%3A%3B0%3A16%3A%3A%3B0%3A207%3A%3A%3B0%3A232%3A%3A%3B0%3A223%3A%3A%3B0%3A163%3A%3A%3B0%3A256%3A%3A%3B0%3A97%3A%3A%3B0%3A173%3A%3A%3B4%3A191%3A%3A%3B0%3A186%3A%3A%3B0%3A192%3A%3A%3B0%3A43%3A%3A%3B0%3A243%3A%3A%3B0%3A199%3A%3A%3B0%3A103%3A%3A%3B0%3A159%3A%3A%3B0%3A184%3A%3A%3B0%3A18%3A%3A%3B0%3A35%3A%3A%3B0%3A59%3A%3A%3B0%3A64%3A%3A%3B0%3A216%3A%3A%3B0%3A86%3A%3A%3B0%3A120%3A%3A%3B0%3A205%3A%3A%3B0%3A149%3A%3A%3B0%3A127%3A%3A%3B0%3A115%3A%3A%3B0%3A17%3A%3A%3B4%3A110%3A%3A%3B0%3A238%3A%3A%3B0%3A102%3A%3A%3B0%3A239%3A%3A%3B0%3A217%3A%3A%3B0%3A155%3A%3A%3B0%3A96%3A%3A%3B0%3A28%3A%3A%3B0%3A220%3A%3A%3B0%3A222%3A%3A%3B0%3A250%3A%3A%3B0%3A252%3A%3A%3B0%3A44%3A%3A%3B0%3A196%3A%3A%3B0%3A227%3A%3A%3B0%3A206%3A%3A%3B0%3A221%3A%3A%3B0%3A71%3A%3A%3B0%3A79%3A%3A%3B0%3A80%3A%3A%3B0%3A78%3A%3A%3B0%3A57%3A%3A%3B0%3A81%3A%3A%3B0%3A27%3A%3A&selector%5Bexclude_sports_ids_str%5D=56+57+43+32+3+55+60+28+8+44+9+26+34+10+11+12+39+47+48+49+59+14+53+54+58+30+13+29+45+19+36+33+31+40+42+41+20+62+61+50+51+63+21+37+23+35+38+25&selector%5Bextra_filters%5D=&commit=Filtrar&narrow="

# Lista para armazenar IDs antigos
ids_antigos = []

while True:
    novos_dados, ids_antigos = obter_dados_tbody(url, ids_antigos)

    # Imprimir os novos dados
    if novos_dados:
        print("Novos Dados:")
        for dados in novos_dados:
            print(dados)

    # Aguardar 1 minuto antes da próxima execução
    time.sleep(10)