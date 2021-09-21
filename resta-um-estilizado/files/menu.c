#include <allegro.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"
#include "control.h"
#include "file.h"
#include "keystates.h"
#include "menu.h"
#include "variables.h"

volatile int exit_program;
volatile int timer;
Board *bd;
Paths* paths;
Volume* vol;

// Main menu function. //
void menu()
{
    /// BITMAPS ///
    Bitmaps* m1=(Bitmaps*)malloc(sizeof(Bitmaps));                      //Pointer to print the field.//
    setBoardBitmaps(m1,0);                                              //Initialize the bitmaps for the field.//
    BITMAP* logo=load_bitmap(paths->logo,NULL);                         //Bitmaps for the menu section.//
    BITMAP* button=load_bitmap(paths->buttonM,NULL);
    BITMAP* title=load_bitmap(paths->title,NULL);
    /// FONTS ///
    FONT* f24=load_font("fonts\\F24.pcx",NULL,NULL);                    //Fonts used in the menu section.//
    FONT* f28=load_font("fonts\\F28.pcx",NULL,NULL);
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef1.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    set_volume(vol->noise,vol->music);                                  //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    char aux[9][9]={"*********","***OOO***","***OOO***","*OOOOOOO*","*OOOIOOO*","*OOOOOOO*","***OOO***","***OOO***","*********"};
    int exit_screen=FALSE;                                              //Escape variable.//
    int t=0,sel_i=0,bip=0,at=0,i,j;                                     //Timers, counters and sounders.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// IMPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                          //If ESC pressed close the program.//
        {
            free(m1);
            fecha_programa();
        }
        if(pressed(KEY_UP))                                             //If UP pressed update the variables.//
        {
            sel_i--;
            play_sample(ef1,vol->noise,0,1000,FALSE);                   //Read button sound.//
        }
        else if(pressed(KEY_DOWN))                                      //If DOWN pressed.//
        {
            sel_i++;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
                                                                        //Instructions button selected.//
        if((sel_i==0&&pressed(KEY_ENTER))||(mouseIn(560,721,250,291)&&at==2))
            screen_state=RULE;
                                                                        //Game button selected.//
        else if((sel_i==1&&pressed(KEY_ENTER))||(mouseIn(560,721,300,341)&&at==2))
            screen_state=BOARDS;
                                                                        //Historic button selected.//
        else if((sel_i==2&&pressed(KEY_ENTER))||(mouseIn(560,721,350,391)&&at==2))
            screen_state=HISTORIC;
                                                                        //Ranking button selected.//
        else if((sel_i==3&&pressed(KEY_ENTER))||(mouseIn(560,721,400,441)&&at==2))
            screen_state=RECORD;
                                                                        //Configuration button selected.//
        else if((sel_i==4&&pressed(KEY_ENTER))||(mouseIn(560,721,450,491)&&at==2))
            screen_state=SETTINGS;
                                                                        //Exit button selected.//
        else if((sel_i==5&&pressed(KEY_ENTER))||(mouseIn(560,721,500,541)&&at==2))
        {
            free(m1);
            fecha_programa();
        }
        /// UPDATE ///
        mouseStates(50,0,560,721,250,291,sel_i,0,&at);                  //Check valid positions for clicking and sounding.//
        bipControl(50,0,560,721,250,291,&bip,sel_i,sel_i);
        if(bip==1)                                                      //If invalid position sounding resets.//
            play_sample(ef1,vol->noise,0,1000,FALSE);
        if(sel_i>5)                                                     //Selector update for keyboard inputs.//
            sel_i=0;
        if(sel_i<0)
            sel_i=5;
        for(i=0;i<6;i++)                                                //Selector update for mouse inputs.//
        {
            if(mouseIn(560,721,250+i*50,291+i*50))
                sel_i=i;
        }
        if(screen_state!=MENUSCREEN)                                    //If the screen changes, deallocate the
        {                                                               //space for auxiliary structure and
            free(m1);                                                   //Close the program.//
            exit_screen=TRUE;
        }
        /// DRAW ///
        draw_sprite(m1->buffer,m1->bg,0,0);                             //Printing the field on the screen.//
        draw_sprite(m1->buffer,logo,96,68);
        draw_sprite(m1->buffer,m1->board,86,192);
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
            if(aux[i][j]=='O'||aux[i][j]=='I')
                draw_sprite(m1->buffer,m1->pieceBg,86+(j-1)*50,192+(i-1)*50);
            }
        }
        draw_sprite(m1->buffer,m1->piece,236,342);
        draw_sprite(m1->buffer,title,500,150);
        for(i=0;i<6;i++)
            draw_sprite(m1->buffer,button,560,250+50*i);                //Printing the buttons and options on the screen.//
        textout_centre_ex(m1->buffer,f28,"Menu Principal",640,150,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Instrucoes",640,250,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Jogar",640,300,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Historico",640,350,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Ranking",640,400,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Ajustes",640,450,fonte_state,-1);
        textout_centre_ex(m1->buffer,f24,"Sair",640,500,fonte_state,-1);
        if(t>100)                                                       //Timer for blinking effect.//
            t=0;
        if(t<50)                                                        //Blinking effect.//
            rectfill(m1->buffer,565,253+sel_i*50,715,287+sel_i*50,cor_state);
        if(mouseIn(560,721,250+50*sel_i,291+50*sel_i))
            rectfill(m1->buffer,565,253+sel_i*50,715,287+sel_i*50,cor_state);
        draw_sprite(m1->buffer,m1->cursor,mouse_x,mouse_y);             //Mouse drawing.//
        draw_sprite(screen,m1->buffer,0,0);
        t++;
    }
    /// FINALIZATION ///
    destroyBoardBitmaps(m1);                                            //Destruction of the bitmaps, fonts and samples.//
    destroy_bitmap(button);
    destroy_bitmap(logo);
    destroy_bitmap(title);
    destroy_font(f24);
    destroy_font(f28);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(menu);
// ------------------- //

// Rules opening function. //
void rules()
{
    /// BITMAPS ///
    BITMAP* bg=load_bitmap(paths->bg,NULL);                             //Background bitmap.//
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);                    //Auxiliary buffer.//
    BITMAP* bufferaux=create_bitmap(SCREEN_W,SCREEN_H);                 //Auxiliary for the buffer.//
    BITMAP* button=load_bitmap(paths->buttonS,NULL);                    //Back Button.
    BITMAP* cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);             //Cursor bitmap.//
    /// FONTS ///
    FONT* f14=load_font("fonts\\F14.pcx",NULL,NULL);                    //Font for text prints.//
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef2.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    set_volume(vol->noise,vol->music);                                  //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                              //Close program variable.//
    int at=0,bip=0,t=0,aux=0,no=0,corfonte=PRETO;                       //Auxiliary variables.//
    char c;                                                             //Character for file reading.//
    FILE* file=openFile("files\\rule.txt","r");                         //Open the file for reading.//
    if(paths->bg[13]=='2'||paths->bg[13]=='4')                          //Color font check.//
        corfonte=BRANCO;
    draw_sprite(bufferaux,bg,0,0);                                      //Drawn the background.//
    while(c!=EOF)
    {
        if(c=='\n')                                                     //Check the break lines.//
        {
            no++;
            aux=0;
        }
        aux++;
        if(c!='\n')                                                     //If it's not break line, it will print on the buffer.//
            textprintf_centre_ex(bufferaux,f14,11.5*aux,no*20+10,corfonte,-1,"%c",c);
        c=fgetc(file);
    }
    closeFile(file);                                                    //Close the file.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                          //Close program.//
            fecha_programa();
                                                                        //If BACK button selected.//
        if(pressed(KEY_ENTER)||(mouseIn(349,450,550,571)&&at==2))
        {
            screen_state=MENUSCREEN;
            exit_screen=TRUE;
        }
        /// UPDATE ///
        mouseStates(0,0,349,450,550,571,0,0,&at);                       //Mouse states.//
        bipControl(0,0,349,450,550,571,&bip,0,0);                       //Sound state.//
        if(bip==1)
            play_sample(ef1,vol->noise,0,1000,FALSE);
        /// DRAW ///
        draw_sprite(buffer,bufferaux,0,0);                              //Draw the auxiliary buffer on the main buffer.//
        draw_sprite(buffer,button,349,550);                             //Drawn the back button.//
        textout_centre_ex(buffer,f14,"Voltar",400,550,fonte_state,-1);
        if(t>100)                                                       //Timer for blinking effect.//
            t=0;
        if(t<50)
            rectfill(buffer,354,553,443,565,cor_state);
        if(mouseIn(349,450,550,571))                                    //Blinking effect.//
            rectfill(buffer,354,553,443,565,cor_state);
        draw_sprite(buffer,cursor,mouse_x,mouse_y);                     //Draw the cursor.//
        draw_sprite(screen,buffer,0,0);                                 //Draw the buffer on the screen.//
        t++;
    }
    /// FINALIZATION ///
    destroy_bitmap(bg);                                                 //Destruction of bitmaps, fonts and samples.//
    destroy_bitmap(buffer);
    destroy_bitmap(bufferaux);
    destroy_bitmap(button);
    destroy_bitmap(cursor);
    destroy_font(f14);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(rules);
// ----------------------- //

// Auxiliary menu function. //
void menuS(int* h)
{
    /// BITMAPS ///
    Bitmaps* m1=(Bitmaps*)malloc(sizeof(Bitmaps));                      //Structure for field printing.//
    setBoardBitmaps(m1,0);                                              //Start the bitmaps.//
    BITMAP* logo=load_bitmap(paths->logo,NULL);
    BITMAP* button=load_bitmap(paths->buttonS,NULL);
    BITMAP* title=load_bitmap(paths->title,NULL);
    /// FONTS ///
    FONT* f12=load_font("fonts\\F12.pcx",NULL,NULL);                    //Fonts for text print.//
    FONT* f28=load_font("fonts\\F28.pcx",NULL,NULL);
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef1.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    set_volume(vol->noise,vol->music);                                  //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    char aux[9][9]={"*********","***OOO***","***OOO***","*OOOOOOO*","*OOOIOOO*","*OOOOOOO*","***OOO***","***OOO***","*********"};
    int exit_screen=FALSE;                                              //Escape variable.//
    int t=0,sel_i=0,sel_j=0,bip=0,at=0,i,j;                             //Timers, counters and sounders.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// IMPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                          //If ESC pressed close the program.//
        {
            free(m1);
            fecha_programa();
        }
        if(pressed(KEY_UP))                                             //If UP pressed update the variable and play the sound.//
        {
            sel_i--;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        else if(pressed(KEY_DOWN))                                      //If DOWN pressed.//
        {
            sel_i++;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        else if(pressed(KEY_LEFT))                                      //If LEFT pressed.//
        {
            sel_j--;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        else if(pressed(KEY_RIGHT))                                     //If RIGHT is pressed.//
        {
            sel_j++;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
                                                                        //If a valid button was pressed.//
        if(pressed(KEY_ENTER)||(mouseIn(450+110*sel_j,551+110*sel_j,150+30*sel_i,171+30*sel_i)&&at==2))
        {
            bd=(Board*)malloc(sizeof(Board));                           //Allocate space in memory for the field.//
            if(*h>=0&&*h<31)                                            //Check if it's a English field.//
                screen_state=GAMEI;                                     //Change the screen.//
            else if(*h>30&&*h<42)                                       //Check if it's a French field.//
                screen_state=GAMEF;
            else if(*h==42)
            {                                                           //Check if it's the BACK button.//
                free(m1);
                free(bd);
                screen_state=MENUSCREEN;
                exit_screen=TRUE;
                END_OF_FUNCTION(menuS);
            }
        }
        /// UPDATE ///
        mouseStates(30,110,450,551,150,171,sel_i,sel_j,&at);            //Mouse state.//
        bipControl(30,110,450,551,150,171,&bip,sel_i,sel_j);            //Sound state.//
        if(bip==1)                                                      //Sound controllers.//
            play_sample(ef1,vol->noise,0,1000,FALSE);
        selUpdateMenuS(&sel_i,&sel_j);                                  //Update the selectors.//
        selUpdateMenuSMouse(&sel_i,&sel_j);                             //Update the selectors.//
                                                                        //Exit screen if game starting.//
        if(screen_state==GAMEI||screen_state==GAMEF)
        {
            free(m1);
            setBoard(h);
            exit_screen=TRUE;
            END_OF_FUNCTION(menuS);                                     //Finish the function.//
        }
        *h=sel_i+15*sel_j;                                              //Field definer.//
        /// DRAW ///
        draw_sprite(m1->buffer,m1->bg,0,0);                             //Draw the field on the screen.//
        draw_sprite(m1->buffer,logo,96,68);
        draw_sprite(m1->buffer,m1->board,86,192);
        for(i=0;i<9;i++)
        {
            for(j=0;j<9;j++)
            {
                if(aux[i][j]=='O'||aux[i][j]=='I')
                    draw_sprite(m1->buffer,m1->pieceBg,86+50*(j-1),192+50*(i-1));
            }
        }
        draw_sprite(m1->buffer,m1->piece,236,342);                      //Draw the buttons and the options on the screen.//
        draw_sprite(m1->buffer,title,470,60);
        for(i=0;i<15;i++)
        {
            for(j=0;j<2;j++)
                draw_sprite(m1->buffer,button,450+110*j,150+30*i);
        }
        for(i=0;i<13;i++)
            draw_sprite(m1->buffer,button,670,150+30*i);
        textout_centre_ex(m1->buffer,f28,"Tabuleiros",610,60,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Padrao",500,150,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Iniciante",500,180,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"L",500,210,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"P",500,240,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Cruz",500,270,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Quadrados",500,300,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Mais",500,330,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"X",500,360,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Espelho",500,390,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Canto",500,420,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Oito",500,450,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Cartola",500,480,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Casinha",500,510,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Plateia",500,540,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Abajur",500,570,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Alvo",610,150,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Triangulo",610,180,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Anel",610,210 ,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Flecha",610,240,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Estrada",610,270,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Ampulheta",610,300,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Barra",610,330,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Circulo",610,360,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Caveira",610,390,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Losango",610,420,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Forquilhas",610,450,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Espiral",610,480,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Cruzamento",610,510,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Ventilador",610,540,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Nave",610,570,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"1 Buraco",720,150,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Frances",720,180,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Cristal",720,210,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Prisao",720,240,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"X Negrito",720,270,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Foguete",720,300,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"5 Cruzes",720,330,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Floco",720,360,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Quadradao",720,390,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Octogono",720,420,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"4 Buracos",720,450,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Alternativo",720,480,fonte_state,-1);
        textout_centre_ex(m1->buffer,f12,"Voltar",720,510,fonte_state,-1);
        if(t>100)                                                       //Timer for blinking effect.//
            t=0;
        if(t<50)                                                        //Blinking effect.//
            rectfill(m1->buffer,455+sel_j*110,153+sel_i*30,545+sel_j*110,167+sel_i*30,cor_state);
        if(mouseIn(450+110*sel_j,551+110*sel_j,150+30*sel_i,171+30*sel_i))
            rectfill(m1->buffer,455+sel_j*110,153+sel_i*30,545+sel_j*110,167+sel_i*30,cor_state);
        draw_sprite(m1->buffer,m1->cursor,mouse_x,mouse_y);             //Mouse drawing.//
        draw_sprite(screen,m1->buffer,0,0);
        t++;
    }
    /// FINALIZATION ///
    destroyBoardBitmaps(m1);                                            //Destruction of the bitmaps, fonts and samples.//
    destroy_bitmap(button);
    destroy_bitmap(logo);
    destroy_bitmap(title);
    destroy_font(f12);
    destroy_font(f28);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(menuS);
// ------------------------ //

// Historic opening function. //
void historic()
{
    /// BITMAPS ///
    BITMAP* bg=load_bitmap(paths->bg,NULL);                             //Background bitmap.//
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);                    //Main buffer.//
    BITMAP* bufferaux1=create_bitmap(SCREEN_W,SCREEN_H);                //Auxiliary buffer 1.//
    BITMAP* bufferaux2=create_bitmap(SCREEN_W,SCREEN_H);                //Auxiliary buffer 2.//
    BITMAP* button=load_bitmap(paths->buttonS,NULL);                    //Button.//
    BITMAP* cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);             //Cursor bitmap.//
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef2.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    set_volume(vol->noise,vol->music);                                  //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                              //Close program variable.//
    int aux=0,control=0,no=0,sel_j=1,t=0,corfonte=PRETO;                //Auxiliary variables.//
    int at1=0,at2=0,at3=0,bip1=0,bip2=0,bip3=0;                         //Auxiliary sound variables.//
    char c;                                                             //Character for file reading.//
    FILE* file=openFile("files\\historic.txt","r");                     //File to read.//
    if(paths->bg[13]=='2'||paths->bg[13]=='4')                          //Color font check.//
        corfonte=BRANCO;
    draw_sprite(bufferaux1,bg,0,0);                                     //Draw the background on the buffer1.//
    draw_sprite(bufferaux2,bg,0,0);                                     //Draw the background on the buffer2.//
    while(c!=EOF)                                                       //Read the file until the end.//
    {
        if(c=='\n')                                                     //Check for break lines.//
        {
            no++;
            aux=0;
        }
        aux++;
        if(c!='\n')
        {
            if(no<20)                                                   //The first 19 lines appear on the screen 1.//
                textprintf_centre_ex(bufferaux1,font,aux*8.5,no*20+50,corfonte,-1,"%c",c);
            if(no>19&&no<40)                                            //From line 20 to line 39 appear on the screen 2.//
                textprintf_centre_ex(bufferaux2,font,aux*8.5,(no-20)*20+50,corfonte,-1,"%c",c);
            if(no>=40)                                                  //If there's more than 40 lines, the file is full.//
                textout_centre_ex(bufferaux2,font,"O arquivo cheio! Limpe-o para leitura de novos dados.",400,500,corfonte,-1);
        }
        c=fgetc(file);
    }
    closeFile(file);                                                    //Close the file.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                          //Close the program.//
            fecha_programa();
                                                                        //If BACK button selected.//
        if((pressed(KEY_ENTER)&&sel_j==1)||(mouseIn(349,450,550,571)&&at1==2))
        {
            exit_screen=TRUE;
            screen_state=MENUSCREEN;
        }                                                               //If CLEAR button selected.//
        if(((pressed(KEY_ENTER))&&sel_j==0)||(mouseIn(12,103,550,571)&&at2==2))
        {
            clearFile("files\\historic.txt","");
            exit_screen=TRUE;
        }                                                               //If LEFT button selected.//
        if((pressed(KEY_ENTER)&&sel_j==2)||(mouseIn(570,671,550,571)&&at3==2))
        {
            at3=0;
            control--;
            play_sample(ef2,vol->noise,0,1000,FALSE);
        }                                                               //If RIGHT button selected.//
        if((pressed(KEY_ENTER)&&sel_j==3)||(mouseIn(680,781,550,571)&&at3==2))
        {
            at3=0;
            control++;
            play_sample(ef2,vol->noise,0,1000,FALSE);
        }

        if(pressed(KEY_RIGHT))                                          //If RIGHT pressed.//
        {
            play_sample(ef1,vol->noise,0,1000,FALSE);
            sel_j++;
        }
        if(pressed(KEY_LEFT))                                           //If LEFT pressed.//
        {
            play_sample(ef1,vol->noise,0,1000,FALSE);
            sel_j--;
        }
        /// UPDATE ///
        mouseStates(0,0,349,450,550,571,0,0,&at1);                      //Mouse state.//
        mouseStates(0,0,12,103,550,571,0,0,&at2);
        mouseStates(0,110,570,671,550,571,0,sel_j-2,&at3);
        bipControl(0,0,349,450,550,571,&bip1,0,0);                      //Sound state.//
        bipControl(0,0,12,103,550,571,&bip2,0,0);
        bipControl(0,110,570,671,550,571,&bip3,0,sel_j-2);
        if(bip1==1||bip2==1||bip3==1)
            play_sample(ef1,vol->noise,0,1000,FALSE);
        if(control>1)                                                   //Screen updater.//
            control=0;
        if(control<0)
            control=1;
        if(sel_j>3)                                                     //Select updater.//
            sel_j=0;
        if(sel_j<0)
            sel_j=3;
        if(mouseIn(349,450,550,571))
            sel_j=1;
        if(mouseIn(12,103,550,571))
            sel_j=0;
        if(mouseIn(570,671,550,571))
            sel_j=2;
        if(mouseIn(680,781,550,571))
            sel_j=3;
        /// DRAW ///
        if(!control)                                                    //First screen.//
            draw_sprite(buffer,bufferaux1,0,0);
        if(control)                                                     //Second screen.//
            draw_sprite(buffer,bufferaux2,0,0);
        textout_ex(buffer,font,"Nome",12,10,fonte_state,-1);            //Print the header of the historic.//
        textout_ex(buffer,font,"Tabuleiro",192,10,fonte_state,-1);
        textout_ex(buffer,font,"Resultado",445,10,fonte_state,-1);
        textout_ex(buffer,font,"Jogadas",585,10,fonte_state,-1);
        textout_ex(buffer,font,"Tempo",700,10,fonte_state,-1);          //Print the buttons.//
        draw_sprite(buffer,button,349,550);
        draw_sprite(buffer,button,12,550);
        draw_sprite(buffer,button,570,550);
        draw_sprite(buffer,button,680,550);
        textout_centre_ex(buffer,font,"Voltar",400,557,fonte_state,-1);
        textout_centre_ex(buffer,font,"Limpar",62,557,fonte_state,-1);
        textout_centre_ex(buffer,font,"<--",620,557,fonte_state,-1);
        textout_centre_ex(buffer,font,"-->",730,557,fonte_state,-1);
        if(t>100)                                                       //Timer for blinking effect.//
            t=0;
        if(t<50)                                                        //Blinking effect.//
        {
            if(sel_j==0)
                rectfill(buffer,17,553,107,565,cor_state);
            else if(sel_j==1)
                rectfill(buffer,354,553,443,565,cor_state);
            else if(sel_j==2)
                rectfill(buffer,575,553,664,565,cor_state);
            else if(sel_j==3)
                rectfill(buffer,685,553,764,565,cor_state);
        }
        if(mouseIn(680,781,550,571))
            rectfill(buffer,685,553,764,565,cor_state);
        if(mouseIn(570,671,550,571))
            rectfill(buffer,575,553,664,565,cor_state);
        if(mouseIn(349,450,550,571))
            rectfill(buffer,354,553,443,565,cor_state);
        if(mouseIn(12,103,550,571))
            rectfill(buffer,17,553,107,565,cor_state);
        draw_sprite(buffer,cursor,mouse_x,mouse_y);                     //Mouse drawing.//
        draw_sprite(screen,buffer,0,0);                                 //Buffer drawing.//
        t++;
    }
    /// FINALIZATION ///
    destroy_bitmap(bg);                                                 //Destruction of bitmaps, fonts and samples.//
    destroy_bitmap(buffer);
    destroy_bitmap(bufferaux1);
    destroy_bitmap(bufferaux2);
    destroy_bitmap(button);
    destroy_bitmap(cursor);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(historic);
// -------------------------- //

// Ranking opening function. //
void ranking()
{
    /// BITMAPS ///
    BITMAP* bg=load_bitmap(paths->bg,NULL);                             //Background bitmap.//
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);                    //Main buffer.//
    BITMAP* bufferaux1=create_bitmap(SCREEN_W,SCREEN_H);                //Auxiliary buffer 1.//
    BITMAP* bufferaux2=create_bitmap(SCREEN_W,SCREEN_H);                //Auxiliary buffer 2.//
    BITMAP* button=load_bitmap(paths->buttonS,NULL);                    //Button bitmap.//
    BITMAP* cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);             //Cursor bitmap.//
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef2.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    set_volume(vol->noise,vol->music);                                  //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                              //Close program variable.//
    int aux=0,control=0,no=0,sel_j=0,t=0,corfonte=PRETO;                //Auxiliary variables.//
    int at1=0,at2=0,bip1=0,bip2=0;                                      //Auxiliary sound variables.//
    char c;                                                             //Character for file reading.//
    FILE* file=openFile("files\\ranking.txt","r");                      //File to read.//
    if(paths->bg[13]=='2'||paths->bg[13]=='4')                          //Color font check.//
        corfonte=BRANCO;
    draw_sprite(bufferaux1,bg,0,0);                                     //Draw background on the auxiliary buffers.//
    draw_sprite(bufferaux2,bg,0,0);
    while(c!=EOF)                                                       //Read the file until the end.//
    {
        if(c=='\n')                                                     //Break line check.//
        {
            no++;
            aux=0;
        }
        aux++;
        if(c!='\n'&&no<22&&c!='$')                                      //First 22 records read.//
            textprintf_centre_ex(bufferaux1,font,aux*8.5,no*20+50,corfonte,-1,"%c",c);
        if(c!='\n'&&(no>21&&no<44)&&c!='$')                             //The rest of the records.//
            textprintf_centre_ex(bufferaux2,font,aux*8.5,(no-22)*20+50,corfonte,-1,"%c",c);
        c=fgetc(file);
    }
    closeFile(file);                                                    //Close the file.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                                //Close program.//
            fecha_programa();
                                                                        //If BACK button selected.//
        if((pressed(KEY_ENTER)&&sel_j==0)||(mouseIn(349,450,550,571)&&at1==2))
        {
            exit_screen=TRUE;
            screen_state=MENUSCREEN;
        }                                                               //If LEFT button selected.//
        if((pressed(KEY_ENTER)&&sel_j==1)||(mouseIn(570,671,550,571)&&at2==2))
        {
            control--;
            at2=0;
            play_sample(ef2,vol->noise,0,1000,FALSE);
        }                                                               //If RIGHT button selected.//
        if((pressed(KEY_ENTER)&&sel_j==2)||(mouseIn(680,781,550,571)&&at2==2))
        {
            control++;
            at2=0;
            play_sample(ef2,vol->noise,0,1000,FALSE);
        }                                                               //If RIGHT pressed.//
        if(pressed(KEY_RIGHT))
        {
            play_sample(ef1,vol->noise,0,1000,FALSE);
            sel_j++;
        }
        if(pressed(KEY_LEFT))                                           //If LEFT pressed.//
        {
            play_sample(ef1,vol->noise,0,1000,FALSE);
            sel_j--;
        }
        /// UPDATE
        mouseStates(0,0,349,450,550,571,0,0,&at1);                      //Mouse states.//
        mouseStates(0,110,570,671,550,571,0,sel_j-1,&at2);
        bipControl(0,0,349,450,550,571,&bip1,0,0);                      //Sound states.//
        bipControl(0,110,570,671,550,571,&bip2,0,sel_j-1);
        if(bip1==1||bip2==1)
            play_sample(ef1,vol->noise,0,1000,FALSE);
        if(control>1)                                                   //Screen updater.//
            control=0;
        if(control<0)
            control=1;
        if(sel_j>2)                                                     //Select updater.//
            sel_j=0;
        if(sel_j<0)
            sel_j=2;
        if(mouseIn(349,450,550,571))                                    //Select updater for mouse pressed.//
            sel_j=0;
        if(mouseIn(570,671,550,571))
            sel_j=1;
        if(mouseIn(680,781,550,571))
            sel_j=2;
        /// DRAW ///
        if(!control)                                                    //Change record screens.//
            draw_sprite(buffer,bufferaux1,0,0);
        if(control)
            draw_sprite(buffer,bufferaux2,0,0);
        textout_ex(buffer,font,"Nome",12,10,fonte_state,-1);            //Print the records header.//
        textout_ex(buffer,font,"Tabuleiro",192,10,fonte_state,-1);
        textout_ex(buffer,font,"Resultado",455,10,fonte_state,-1);
        textout_ex(buffer,font,"Jogadas",597,10,fonte_state,-1);
        textout_ex(buffer,font,"Tempo",707,10,fonte_state,-1);
        draw_sprite(buffer,button,349,550);                             //Draw the buttons.//
        draw_sprite(buffer,button,570,550);
        draw_sprite(buffer,button,680,550);
        textout_centre_ex(buffer,font,"Voltar",400,557,fonte_state,-1);
        textout_centre_ex(buffer,font,"<--",620,557,fonte_state,-1);
        textout_centre_ex(buffer,font,"-->",730,557,fonte_state,-1);
        if(t>100)                                                       //Time for blinking effect.//
            t=0;
        if(t<50)                                                        //Blinking effect.//
        {
            if(sel_j==0)
                rectfill(buffer,354,553,443,565,cor_state);
            if(sel_j==1)
                rectfill(buffer,575,553,664,565,cor_state);
            if(sel_j==2)
                rectfill(buffer,685,553,764,565,cor_state);
        }
        if(mouseIn(680,781,550,571))
            rectfill(buffer,685,553,764,565,cor_state);
        if(mouseIn(570,671,550,571))
            rectfill(buffer,575,553,664,565,cor_state);
        if(mouseIn(349,450,550,571))
            rectfill(buffer,354,553,443,565,cor_state);
        draw_sprite(buffer,cursor,mouse_x,mouse_y);                     //Mouse drawing.//
        draw_sprite(screen,buffer,0,0);                                 //Buffer drawing.//
        t++;
    }
    /// FINALIZATION ///
    destroy_bitmap(bg);                                                 //Destruction of bitmaps and samples.//
    destroy_bitmap(buffer);
    destroy_bitmap(bufferaux1);
    destroy_bitmap(bufferaux2);
    destroy_bitmap(button);
    destroy_bitmap(cursor);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(ranking);
// ------------------------- //

// Settings menu function. //
void settings()
{
    /// BITMAPS ///
    BITMAP* bg=load_bitmap(paths->bg,NULL);                             //Background bitmap.//
    BITMAP* buffer=create_bitmap(SCREEN_W,SCREEN_H);                    //Auxiliary buffer.//
    BITMAP* button=load_bitmap(paths->buttonS,NULL);                    //Button bitmap.//
    BITMAP* cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);             //Cursor bitmap.//
    BITMAP* title=load_bitmap(paths->buttonM,NULL);
    /// FONTS ///
    FONT* f12=load_font("fonts\\F12.pcx",NULL,NULL);                    //Fonts for prints.//
    FONT* f24=load_font("fonts\\F24.pcx",NULL,NULL);
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef2.wav");                         //Sound for options1.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");                         //Sound for options2.//
    play_sample(ef2,vol->noise,0,1000,FALSE);                           //Entering sound.//
    /// VARIABLES ///
    int exit_screen=FALSE;                                              //Exit variable.//
    int sel_i=0,sel_j=0,t=0,corfonte=PRETO,i,j;                         //Auxiliary variables.//
    int at1=0,at2=0,at3=0,bip1=0,bip2=0,bip3=0;                         //Auxiliary Sound variables.//
    /// GAME LOOP ///
    while(!exit_program&&!exit_screen)
    {
        set_volume(vol->noise,vol->music);                              //Volume setting.//
        /// INPUT ///
        keyboardInput();
        if(unpressed(KEY_ESC))                                          //Close program.//
            fecha_programa();
        if((pressed(KEY_N)||hold(KEY_N))&&vol->noise>VOLMIN)            //If N pressed.//
            vol->noise--;                                               //Options volume sound reduces.//
        if((pressed(KEY_M)||hold(KEY_M))&&vol->noise<VOLMAX)            //If M pressed.//
            vol->noise++;                                               //Options volume sound increases.//
        if((pressed(KEY_J)||hold(KEY_J))&&vol->music>VOLMIN)            //If J pressed.//
            vol->music--;                                               //Music volume sound reduces.//
        if((pressed(KEY_K)||hold(KEY_K))&&vol->music<VOLMAX)            //If K pressed.//
            vol->music++;                                               //Music volume sound increases.//
        if(mouseIn(95,105,185,440)&&mouse_b==1)                         //Volume buttons updater.//
            vol->noise=mouse_y-185;
        if(mouseIn(246,256,185,440)&&mouse_b==1)
            vol->music=mouse_y-185;
        if(pressed(KEY_RIGHT)&&sel_i!=5)                                //If RIGHT pressed.//
        {
            sel_j++;                                                    //Update selector.//
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        if(pressed(KEY_LEFT)&&sel_i!=5)                                 //If LEFT pressed.//
        {
            sel_j--;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        if(pressed(KEY_UP))                                             //If UP pressed.//
        {
            sel_i--;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
        if(pressed(KEY_DOWN))                                           //If DOWN pressed.//
        {
            sel_i++;
            play_sample(ef1,vol->noise,0,1000,FALSE);
        }
                                                                        //If BACK button pressed.//
        if((pressed(KEY_ENTER)&&sel_i==5)||(mouseIn(349,450,550,571)&&at2==2))
        {
            screen_state=MENUSCREEN;
            exit_screen=TRUE;
        }
        if(((pressed(KEY_R)))||(mouseIn(12,103,550,571)&&at3==2))       //If RESET button pressed.//
        {                                                               //Reset all the settings.//
            vol->noise=50;
            vol->music=50;
            strcpy(paths->boardI,"bitmaps\\board\\bi1.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf1.bmp");
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg1.bmp");
            strcpy(paths->bg,"bitmaps\\bg\\bg1.bmp");
            strcpy(paths->buttonB,"bitmaps\\button\\big1.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l1.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium1.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small1.bmp");
            strcpy(paths->title,"bitmaps\\button\\title1.bmp");
            strcpy(paths->piece,"bitmaps\\piece\\p1.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid1.bmp");
            at1=0;
            cor_state=VERDIN;
            fonte_state=PRETO;
            exit_screen=TRUE;
        }
                                                                        //Button 1 selected.//
        if((sel_i==0&&sel_j==0)&&((pressed(KEY_ENTER))||(mouseIn(471,493,151,173)&&at1==2)))
        {
            strcpy(paths->buttonB,"bitmaps\\button\\big1.bmp");
            strcpy(paths->title,"bitmaps\\button\\title1.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium1.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small1.bmp");
            exit_screen=TRUE;
        }                                                               //Button 2 selected.//
        if((sel_i==0&&sel_j==1)&&((pressed(KEY_ENTER))||(mouseIn(521,543,151,173)&&at1==2)))
        {
            strcpy(paths->buttonB,"bitmaps\\button\\big2.bmp");
            strcpy(paths->title,"bitmaps\\button\\title2.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium2.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small2.bmp");
            exit_screen=TRUE;
        }                                                               //Button 3 selected.//
        if((sel_i==0&&sel_j==2)&&((pressed(KEY_ENTER))||(mouseIn(571,593,151,173)&&at1==2)))
        {
            strcpy(paths->buttonB,"bitmaps\\button\\big3.bmp");
            strcpy(paths->title,"bitmaps\\button\\title3.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium3.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small3.bmp");
            exit_screen=TRUE;
        }                                                               //Button 4 selected.//
        if((sel_i==0&&sel_j==3)&&((pressed(KEY_ENTER))||(mouseIn(621,643,151,173)&&at1==2)))
        {
            strcpy(paths->buttonB,"bitmaps\\button\\big4.bmp");
            strcpy(paths->title,"bitmaps\\button\\title4.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium4.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small4.bmp");
            exit_screen=TRUE;
        }                                                               //Button 5 selected.//
        if((sel_i==0&&sel_j==4)&&((pressed(KEY_ENTER))||(mouseIn(671,693,151,173)&&at1==2)))
        {
            strcpy(paths->buttonB,"bitmaps\\button\\big5.bmp");
            strcpy(paths->title,"bitmaps\\button\\title5.bmp");
            strcpy(paths->buttonM,"bitmaps\\button\\medium5.bmp");
            strcpy(paths->buttonS,"bitmaps\\button\\small5.bmp");
            exit_screen=TRUE;
        }
                                                                        //Button 6 selected.//
        if((sel_i==1&&sel_j==0)&&((pressed(KEY_ENTER))||(mouseIn(471,493,221,243)&&at1==2)))
        {
            strcpy(paths->bg,"bitmaps\\bg\\bg1.bmp");
            exit_screen=TRUE;
        }                                                               //Button 7 selected.//
        if((sel_i==1&&sel_j==1)&&((pressed(KEY_ENTER))||(mouseIn(521,543,221,243)&&at1==2)))
        {
            strcpy(paths->bg,"bitmaps\\bg\\bg2.bmp");
            exit_screen=TRUE;
        }                                                               //Button 8 selected.//
        if((sel_i==1&&sel_j==2)&&((pressed(KEY_ENTER))||(mouseIn(571,593,221,243)&&at1==2)))
        {
            strcpy(paths->bg,"bitmaps\\bg\\bg3.bmp");
            exit_screen=TRUE;
        }                                                               //Button 9 selected.//
        if((sel_i==1&&sel_j==3)&&((pressed(KEY_ENTER))||(mouseIn(621,643,221,243)&&at1==2)))
        {
            strcpy(paths->bg,"bitmaps\\bg\\bg4.bmp");
            exit_screen=TRUE;
        }                                                               //Button 10 selected.//
        if((sel_i==1&&sel_j==4)&&((pressed(KEY_ENTER))||(mouseIn(671,693,221,243)&&at1==2)))
        {
            strcpy(paths->bg,"bitmaps\\bg\\bg5.bmp");
            exit_screen=TRUE;
        }
                                                                        //Button 11 selected.//
        if((sel_i==2&&sel_j==0)&&((pressed(KEY_ENTER))||(mouseIn(471,493,291,313)&&at1==2)))
        {
            strcpy(paths->boardI,"bitmaps\\board\\bi1.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf1.bmp");
            exit_screen=TRUE;
        }                                                               //Button 12 selected.//
        if((sel_i==2&&sel_j==1)&&((pressed(KEY_ENTER))||(mouseIn(521,543,291,313)&&at1==2)))
        {
            strcpy(paths->boardI,"bitmaps\\board\\bi2.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf2.bmp");
            exit_screen=TRUE;
        }                                                               //Button 13 selected.//
        if((sel_i==2&&sel_j==2)&&((pressed(KEY_ENTER))||(mouseIn(571,593,291,313)&&at1==2)))
        {
            strcpy(paths->boardI,"bitmaps\\board\\bi3.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf3.bmp");
            exit_screen=TRUE;
        }                                                               //Button 14 selected.//
        if((sel_i==2&&sel_j==3)&&((pressed(KEY_ENTER))||(mouseIn(621,643,291,313)&&at1==2)))
        {
            strcpy(paths->boardI,"bitmaps\\board\\bi4.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf4.bmp");
            exit_screen=TRUE;
        }                                                               //Button 15 selected.//
        if((sel_i==2&&sel_j==4)&&((pressed(KEY_ENTER))||(mouseIn(671,693,291,313)&&at1==2)))
        {
            strcpy(paths->boardI,"bitmaps\\board\\bi5.bmp");
            strcpy(paths->boardF,"bitmaps\\board\\bf5.bmp");
            exit_screen=TRUE;
        }
                                                                        //Button 16 selected.//
        if((sel_i==3&&sel_j==0)&&((pressed(KEY_ENTER))||(mouseIn(471,493,361,383)&&at1==2)))
        {
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg1.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l1.bmp");
            exit_screen=TRUE;
        }                                                               //Button 17 selected.//
        if((sel_i==3&&sel_j==1)&&((pressed(KEY_ENTER))||(mouseIn(521,543,361,383)&&at1==2)))
        {
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg2.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l2.bmp");
            exit_screen = TRUE;
        }                                                               //Button 18 selected.//
        if((sel_i==3&&sel_j==2)&&((pressed(KEY_ENTER))||(mouseIn(571,593,361,383)&&at1==2)))
        {
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg3.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l3.bmp");
            exit_screen=TRUE;
        }                                                               //Button 19 selected.//
        if((sel_i==3&&sel_j==3)&&((pressed(KEY_ENTER))||(mouseIn(621,643,361,383)&&at1==2)))
        {
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg4.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l4.bmp");
            exit_screen=TRUE;
        }                                                               //Button 20 selected.//
        if((sel_i==3&&sel_j==4)&&((pressed(KEY_ENTER))||(mouseIn(671,693,361,383)&&at1==2)))
        {
            strcpy(paths->pieceBg,"bitmaps\\piece_bg\\p_bg5.bmp");
            strcpy(paths->logo,"bitmaps\\logo\\l5.bmp");
            exit_screen=TRUE;
        }
                                                                        //Button 21 selected.//
        if((sel_i==4&&sel_j==0)&&((pressed(KEY_ENTER))||(mouseIn(471,493,431,453)&&at1==2)))
        {
            strcpy(paths->piece,"bitmaps\\piece\\p1.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid1.bmp");
            exit_screen=TRUE;
        }                                                               //Button 22 selected.//
        if((sel_i==4&&sel_j==1)&&(( pressed(KEY_ENTER))||(mouseIn(521,543,431,453)&&at1==2)))
        {
            strcpy(paths->piece,"bitmaps\\piece\\p2.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid2.bmp");
            exit_screen=TRUE;
        }                                                               //Button 23 selected.//
        if((sel_i==4&&sel_j==2)&&((pressed(KEY_ENTER))||(mouseIn(571,593,431,453)&&at1==2)))
        {
            strcpy(paths->piece,"bitmaps\\piece\\p3.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid3.bmp");
            exit_screen=TRUE;
        }                                                               //Button 24 selected.//
        if((sel_i==4&&sel_j==3)&&((pressed(KEY_ENTER))||(mouseIn(621,643,431,453)&&at1==2)))
        {
            strcpy(paths->piece,"bitmaps\\piece\\p4.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid4.bmp");
            exit_screen=TRUE;
        }                                                               //Button 25 selected.//
        if((sel_i==4&&sel_j==4)&&((pressed(KEY_ENTER))||(mouseIn(671,693,431,453)&&at1==2)))
        {
            strcpy(paths->piece,"bitmaps\\piece\\p5.bmp");
            strcpy(paths->pieceV,"bitmaps\\piece\\valid5.bmp");
            exit_screen=TRUE;
        }
        /// UPDATE ///
        if(paths->buttonM[21]=='5')                                     //Check the font color.//
        {
            cor_state=PRETIN;
            fonte_state=BRANCO;
        }
        else
        {
            fonte_state=PRETO;                                          //Check for the blinking effect color.//
            if(paths->buttonM[21]=='1')
                cor_state=VERDIN;
            else if(paths->buttonM[21]=='2')
                cor_state=CINZA;
            else if(paths->buttonM[21]=='3')
                cor_state=VERDE;
            else if(paths->buttonM[21]=='4')
                cor_state=VERMELHO;
        }
        mouseStates(70,50,471,493,151,173,sel_i,sel_j,&at1);            //Mouse states.//
        mouseStates(0,0,349,450,550,571,0,0,&at2);
        mouseStates(0,0,12,103,550,571,0,0,&at3);
        bipControl(70,50,471,493,151,173,&bip1,sel_i,sel_j);            //Sound states.//
        bipControl(0,0,349.5,450.5,550,571,&bip2,0,0);
        bipControl(0,0,12,103,550,571,&bip3,0,0);
        if(bip1==1||bip2==1||bip3==1)
            play_sample(ef1,vol->noise,0,1000,FALSE);
        if(sel_i>5)                                                     //Selectors updater.//
            sel_i=0;
        if(sel_i<0)
            sel_i=5;
        if(sel_j>4)
            sel_j=0;
        if(sel_j<0)
            sel_j=4;
        if(sel_i==5)
            sel_j=0;
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                if(mouseIn(471+50*j,493+50*j,151+70*i,173+70*i))        //Selector updater for mouse inputs.//
                {
                    sel_j=j;
                    sel_i=i;
                }
            }
        }
        if(mouseIn(349,450,550,571))
        {
            sel_i=5;
            sel_j=0;
        }
        /// DRAW ///
        draw_sprite(buffer,bg,0,0);
        textout_ex(buffer,f12,"Botao",400,150,corfonte,-1);             //Options name prints.//
        textout_ex(buffer,f12,"Fundo",400,220,corfonte,-1);
        textout_ex(buffer,f12,"Campo",400,290,corfonte,-1);
        textout_ex(buffer,f12,"Espaco",400,360,corfonte,-1);
        textout_ex(buffer,f12,"Peca",400,430,corfonte,-1);
        draw_sprite(buffer,button,349,550);
        draw_sprite(buffer,title,490,75);
        draw_sprite(buffer,title,90,75);
        draw_sprite(buffer,button,12,550);                              //Sound options name prints.//
        textout_centre_ex(buffer,f12,"Reseta (R)",62.5,550,fonte_state,-1);
        textout_centre_ex(buffer,f12,"Voltar",400,550,fonte_state,-1);
        textout_centre_ex(buffer,f24,"Volume",170,75,fonte_state,-1);
        textout_centre_ex(buffer,f24,"Ajustes",570,75,fonte_state,-1);
        textout_centre_ex(buffer,f12,"Som",100,150,corfonte,-1);
        textout_centre_ex(buffer,f12,"Musica",250,150,corfonte,-1);
        textout_centre_ex(buffer,f12,"Pressione (N/M) ou (J/K)",170,460,corfonte,-1);
        textout_centre_ex(buffer,f12,"Vol Min",50,185,corfonte,-1);
        textout_centre_ex(buffer,f12,"Vol Max",50,420,corfonte,-1);
        rectfill(buffer,99,185,101,440,corfonte);                       //Sound buttons prints.//
        rectfill(buffer,249,185,251,440,corfonte);
        rect(buffer,95,181+vol->noise,105,189+vol->noise,corfonte);
        rect(buffer,245,181+vol->music,255,189+vol->music,corfonte);
        rectfill(buffer,96,182+vol->noise,104,188+vol->noise,cor_state);
        rectfill(buffer,246,182+vol->music,254,188+vol->music,cor_state);
        for(i=0;i<5;i++)                                                //Buttons prints.//
        {
            for(j=0;j<5;j++)
            {
                rect(buffer,470+50*i,150+70*j,494+50*i,174+70*j,fonte_state);
                rectfill(buffer,471+50*i,151+70*j,493+50*i,173+70*j,cor_state);
            }
        }
        for(i=0;i<5;i++)
        {
            for(j=0;j<5;j++)
            {
                textprintf_centre_ex(buffer,f12,482+50*j,153+70*i,fonte_state,-1,"%d",j+1);
            }
        }
        if(t>100)                                                       //Timer for blinking effect.//
            t=0;
        if(t<50)                                                        //Blinking effect.//
        {
            if(sel_i>=0&&sel_i<5)
                rectfill(buffer,471+(50*sel_j),151+(70*sel_i),493+(50*sel_j),173+(70*sel_i),cor_state);
            if(sel_i==5)
                rectfill(buffer,354,553,443,565,cor_state);
        }
        if(sel_i!=5&&mouseIn(471+50*sel_j,493+50*sel_j,151+70*sel_i,173+70*sel_i))
            rectfill(buffer,471+(50*sel_j),151+(70*sel_i),493+(50*sel_j),173+(70*sel_i),cor_state);
        if(mouseIn(349,450,550,571))
            rectfill(buffer,354,553,443,565,cor_state);
        if(mouseIn(12,103,550,571))
            rectfill(buffer,17,553,107,565,cor_state);
        draw_sprite(buffer,cursor,mouse_x,mouse_y);                     //Mouse drawing.//
        draw_sprite(screen,buffer,0,0);                                 //Double buffering.//
        t++;
    }
    /// FINALIZATION ///
    destroy_bitmap(bg);                                                 //Destruction of bitmaps, fonts and samples.//
    destroy_bitmap(buffer);
    destroy_bitmap(button);
    destroy_bitmap(cursor);
    destroy_bitmap(title);
    destroy_font(f12);
    destroy_font(f24);
    destroy_sample(ef1);
    destroy_sample(ef2);
}
END_OF_FUNCTION(settings);
// ----------------------- //
