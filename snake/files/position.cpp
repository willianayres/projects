#include "position.h"


//Move o cursor no console para posição específica.//
void goto_XY(short x, short y)
{
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}
