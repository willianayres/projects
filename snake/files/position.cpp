#include "position.h"


//Move o cursor no console para posi��o espec�fica.//
void goto_XY(short x, short y)
{
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}
