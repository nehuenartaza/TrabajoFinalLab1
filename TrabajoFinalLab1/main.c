#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib.h"


int main()
{
    int opcion = 1, flag = NULL, posicion = NULL, search_astronauta = 0, search_nave = 0, search_mision = 0;
    while ( opcion == 1 )
    {
        printf ( "Bienvenido!\n" );
        drawmenu_principal();
        scanf ( "%d", &opcion );
        switch ( opcion )
        {
        case 1:
            system("cls");
            drawmenu_1();
            break;

        case 2:
            system("cls");
            drawmenu_2();
            break;

        case 3:
            system("cls");
            drawmenu_3();
            break;

        case 4:
            system("cls");
            drawmenu_4();
            break;

        case 0:
            opcion == 0;
            system("cls");
            break;

        default:
            system("cls");
            break;
        }
    }



    return 0;
}






