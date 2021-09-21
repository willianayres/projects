#include "board.h"
#include "control.h"
#include "file.h"
#include "game.h"
#include "keystates.h"
#include "menu.h"

volatile int exit_program;
volatile int timer;
Board *bd;
Paths *paths;
Volume *vol;

// Function to set the board correctly. //
void setBoard(int* h)
{
    bd->points=0;                                   //Set the play to 0.//
    bd->piece=0;
    char ch,b[82];                                  //Auxiliary variables.//
    int i,aux=0;
    FILE* file=openFile("files\\board.txt","r");    //File to get the board's information.//
    while(ch!=EOF)                                  //Read the file until the end.//
    {
        if(aux==*h&&ch!='\n')                       //If it's the correctly line.//
            fscanf(file,"%s",b);                    //Scan the board and the number of pines.//
        if(aux==*h+42&&ch!='\n')                    //Scan the name of the board on the correctly line.//
        {
            fgets(bd->name,30,file);
            break;
        }
        if(ch=='\n')                                //Check the break line.//
            aux++;
        ch=getc(file);
    }
    for(i=0;i<strlen(bd->name);i++)                 //Put a END CHARACTER on the final of the name.//
    {
        if(bd->name[i]=='\n')
            bd->name[i]='\0';
    }
    for(i=0;i<strlen(b);i++)                        //Count the number of pines.//
    {
        if(b[i]=='I')
            bd->piece++;
    }
    b[81]='\0';                                     //Put a END CHARACTER on the final of the auxiliary board string.//
    memcpy(bd->board,b,sizeof(bd->board));          //Put the string on the matrix.//
    closeFile(file);                                //Close the file.//
}
// ------------------------------------ //

// Function to set board bitmaps. //
void setBoardBitmaps(Bitmaps* m,int n)
{
    if(!n)                                              //Check the type of board.//
        m->board=load_bitmap(paths->boardI,NULL);       //English board.//
    if(n)
        m->board=load_bitmap(paths->boardF,NULL);       //French board.//
    m->buffer=create_bitmap(SCREEN_W,SCREEN_H);         //Main buffer.//
    m->cursor=load_bitmap("bitmaps\\Cursor.bmp",NULL);  //Cursor.//
    m->pieceBg=load_bitmap(paths->pieceBg,NULL);        //Space of the piece.//
    m->bg=load_bitmap(paths->bg,NULL);                  //Background.//
    m->bufferAux=create_bitmap(SCREEN_W,SCREEN_H);      //Auxiliary buffer.//
    m->buttonB=load_bitmap(paths->buttonB,NULL);        //Button.//
    m->boardName=load_bitmap(paths->buttonM,NULL);      //Space of the name.//
    m->piece=load_bitmap(paths->piece,NULL);            //Piece.//
    m->f1=load_font("fonts\\F16.pcx",NULL,NULL);        //Font.//
}
// ------------------------------ //

// Function to draw the board on the auxiliary buffer. //
void drawBoard(Bitmaps* m)
{
    draw_sprite(m->bufferAux,m->bg,0,0);                                    //Draw background on the buffer.//
    draw_sprite(m->bufferAux,m->boardName,319,54);                          //Draw the name background on the buffer.//
    draw_sprite(m->bufferAux,m->buttonB,100,125);                           //Draw the button on the buffer.//
    draw_sprite(m->bufferAux,m->buttonB,100,200);
    draw_sprite(m->bufferAux,m->buttonB,625,125);
    draw_sprite(m->bufferAux,m->buttonB,625,345);
    draw_sprite(m->bufferAux,m->buttonB,625,420);

    textout_centre_ex(m->bufferAux,m->f1,"Volta",662,350,fonte_state,-1);   //Print the texts on the buffer.//
    textout_centre_ex(m->bufferAux,m->f1,"(R)",662,372,fonte_state,-1);
    textout_centre_ex(m->bufferAux,m->f1,"Sair",662,425,fonte_state,-1);
    textout_centre_ex(m->bufferAux,m->f1,"(V)",662,447,fonte_state,-1);
    textout_centre_ex(m->bufferAux,m->f1,"Tempo",662,130,fonte_state,-1);
    textprintf_centre_ex(m->bufferAux,m->f1,662,152,fonte_state,-1,"%2d:%02d",(timer/60)%60,timer%60);
    textprintf_centre_ex(m->bufferAux,m->f1,400,64,fonte_state,-1,"%s",bd->name);
    textout_centre_ex(m->bufferAux,m->f1,"Jogada",137,130,fonte_state,-1);
    textprintf_centre_ex(m->bufferAux,m->f1,137,152,fonte_state,-1,"%d",bd->points);
    textout_centre_ex(m->bufferAux,m->f1,"Pinos",137,205,fonte_state,-1);
    textprintf_centre_ex(m->bufferAux,m->f1,137,227,fonte_state,-1,"%d",bd->piece);

    int i,j;                                                                 //Draw the board, spaces and pines on the buffer.//
    draw_sprite(m->bufferAux,m->board,225,125);                              //It will ignore the *.//
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
        if(bd->board[i][j]=='O'||bd->board[i][j]=='I')                         //If it's a space or a pine, draws a space.//
            draw_sprite(m->bufferAux,m->pieceBg,225+(j-1)*50,125+(i-1)*50);
        if(bd->board[i][j]=='I')                                              //If its's a pine, draw a pine.//
            draw_sprite_ex(m->bufferAux,m->piece,225+(j-1)*50,125+(i-1)*50,DRAW_SPRITE_NORMAL,DRAW_SPRITE_NO_FLIP);
        }
    }
}
// --------------------------------------------------- //

// Function to destroy board bitmaps. //
void destroyBoardBitmaps(Bitmaps* m)
{
    destroy_bitmap(m->bg);              //Destroy the background bitmap.//
    destroy_bitmap(m->board);           //Destroy the board bitmap.//
    destroy_bitmap(m->boardName);       //Destroy the title bitmap.//
    destroy_bitmap(m->buffer);          //Destroy the buffer bitmap.//
    destroy_bitmap(m->bufferAux);       //Destroy the auxiliary buffer bitmap./
    destroy_bitmap(m->buttonB);         //Destroy the button bitmap.///
    destroy_bitmap(m->cursor);          //Destroy the cursor bitmap.//
    destroy_bitmap(m->pieceBg);         //Destroy the background pine bitmap.//
    destroy_bitmap(m->piece);           //Destroy the pine bitmap.//
    destroy_font(m->f1);                //Destroy the font.//
}
// ---------------------------------- //

// Function to play the game. //
void game(int b)
{
    /// BITMAPS ///
    Bitmaps* m1=(Bitmaps*)malloc(sizeof(Bitmaps));              //Auxiliary bitmaps.//
    setBoardBitmaps(m1,b);                                      //Draw bitmaps.//
    /// SOUNDS ///
    SAMPLE* ef1=load_sample("sounds\\ef1.wav");                 //Sounds of effects.//
    SAMPLE* ef2=load_sample("sounds\\ef3.wav");
    SAMPLE* ef3=load_sample("sounds\\ef4.wav");
    set_volume(vol->noise,vol->music);                          //Volume setter.//
    play_sample(ef2,vol->noise,0,1000,FALSE);
    /// VARIABLES ///
    int exit_screen=FALSE;                                      //Exit function variable.//
    int t=0,sel_i=3,sel_j=3,at=0,at2=0,at3=0;                   //Auxiliary variables.//
    timer=0;
    install_int_ex(incrementa_timer,SECS_TO_TIMER(1));          //Timer for the game.//
    /// GAME LOOP
    while(!exit_program&&!exit_screen)
    {
        /// INPUT ///
        keyboardInput();                                        //Keyboard reading.//
        if(unpressed(KEY_ESC))                                  //Exit program.//
        {
            free(bd);
            fecha_programa();
        }
        selInput(&sel_i,&sel_j);                                //Selectors input.//
        if(bd->board[sel_i+1][sel_j+1]=='I')                    //If the player select a pine.//
        {
            if(pressed(KEY_ENTER)||(mouseIn(225+sel_j*50,276+sel_j*50,125+sel_i*50,176+sel_i*50)&&at==2))
                screen_state=MOVE;
        }
        if(pressed(KEY_V)||(mouseIn(625,701,420,476)&&at3==2))  //If the player pressed V.//
        {
            free(m1);                                           //Deallocate the auxiliary bitmaps.//
            free(bd);
            screen_state=MENUSCREEN;                            //Change the screen state.//
            exit_screen=TRUE;
        }
                                                                //If the player press R.//
        if((bd->points>0)&&(pressed(KEY_R)||(mouseIn(625,701,342,401)&&at2==2)))
        {
            returnMove(bd);                                     //Return the board for the previous move.//
            at=0;
            at2=0;
            mouse_b=0;
            play_sample(ef2,vol->noise,0,1000,FALSE);
        }
        /// UPDATE ///
        mouseStatesMove(&at,sel_i,sel_j,bd);                    //Mouse events.//
        mouseStates(0,0,625,701,345,401,0,0,&at2);
        mouseStates(0,0,625,701,420,476,0,0,&at3);
        selUpdateMove(&sel_i,&sel_j,b);                         //Selectors update.//
        selUpdateMoveMouse(&sel_i,&sel_j,b);                    //Selectors update with mouse.//
        if(screen_state==MOVE)                                  //Will check if it's a valid move.//
        {
            gameMove(sel_i,sel_j,b);                            //Check the move.//
            play_sample(ef3,vol->noise,0,1000,FALSE);
            if(mouseIn(225+(sel_j+2)*50,276+(sel_j+2)*50,125+sel_i*50,176+sel_i*50)||
               mouseIn(225+sel_j*50,276+sel_j*50,125+(sel_i+2)*50,176+(sel_i+2)*50)||
               mouseIn(225+(sel_j-2)*50,276+(sel_j-2)*50,125+sel_i*50,176+sel_i*50)||
               mouseIn(225+sel_j*50,276+sel_j*50,125+(sel_i-2)*50,176+(sel_i-2)*50)||
               mouseIn(225+sel_j*50,276+sel_j*50,125+sel_i*50,176+sel_i*50))
            {
                at=0;
                at2=0;
                mouse_b=0;
            }
            if(pressed(KEY_RIGHT))                              //Update the selectors again.//
                sel_j+=2;
            if(pressed(KEY_DOWN))
                sel_i+=2;
            if(pressed(KEY_LEFT))
                sel_j-=2;
            if(pressed(KEY_UP))
                sel_i-=2;
        }
        if(checkGameOver())                                     //Check if there's still moves to do.//
        {
            if(checkGameResult())                               //If the game ends, check if the play won or lost.//
                strcpy(bd->result,"Ganhou");
            else
                strcpy(bd->result,"Perdeu");
            screen_state=NAME;
            exit_screen=TRUE;
        }
        /// DRAW ///
        set_burn_blender(255,255,255,128);                      //Burn blender for selected pine.//
        drawBoard(m1);                                          //Draw the board.//
        draw_sprite(m1->buffer,m1->bufferAux,0,0);              //Draw the auxiliary buffer on the main buffer.//
        if(t>100)                                               //Timer for blinking effect.//
            t=0;
        if(t<50)                                                //Blinking effect.//
        {
            draw_sprite_ex(m1->buffer,m1->piece,225+sel_j*50,125+sel_i*50,DRAW_SPRITE_TRANS,DRAW_SPRITE_NO_FLIP);
            if(mouseIn(625,701,345,401))
                rectfill(m1->buffer,630,350,694,394,cor_state);
            if(mouseIn(625,701,420,476))
                rectfill(m1->buffer,630,425,694,469,cor_state);
        }                                                       //Hover effect.//
        if(mouseIn(225+sel_j*50,276+sel_j*50,125+sel_i*50,176+sel_i*50))
            draw_sprite_ex(m1->buffer,m1->piece,225+sel_j*50,125+sel_i*50,DRAW_SPRITE_TRANS,DRAW_SPRITE_NO_FLIP);
        draw_sprite(m1->buffer,m1->cursor,mouse_x,mouse_y);     //Draw the cursor.//
        draw_sprite(screen,m1->buffer,0,0);                     //Draw the buffer on the screen.//
        t++;                                                    //Update the auxiliary timer.//
    }
    /// FINALIZATION ///
    destroyBoardBitmaps(m1);                                    //Destroy the bitmaps and the samples.//
    destroy_sample(ef1);
    destroy_sample(ef2);
    destroy_sample(ef3);
    free(m1);
}
END_OF_FUNCTION(game);
// --------------------------------------------------------
