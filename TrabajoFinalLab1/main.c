#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib.h"
int main()
{
    int option = 1, flag = NULL, position = NULL, search_astronaut = 0, search_ship = 0, search_mission = 0;
    while ( option == 1 ) {

        printf ( "Bienvenido!\n" );
        draw_mainmenu();
        scanf ( "%d", &option );
        switch ( option ) {
        case 1:
            system("cls");
            drawmenu_1();
            scanf ( "%d", &option );
            switch ( option ) {
            case 1:
                system("cls");
                register_astronaut();
                break;

            case 2:
                system("cls");
                //funcion de registrar nave
                break;

            case 3:
                system("cls");
                //funcion de registrar mision
                break;

            case 4:
                system("cls");
                break;

            default:
                system("cls");
                break;
            }
            break;

        case 2:
            system("cls");
            drawmenu_2();
            scanf ( "%d", &option );
            switch ( option ) {
            case 1:
                system("cls");
                modify_astronauts();
                break;

                case 2:
                    system("cls");
                    //funcion de modificar nave
                    break;

                case 3:
                    system("cls");
                    //funcion de modificar mision
                    break;

                case 4:
                    system("cls");
                    break;

                default:
                    system("cls");
                    break;
            }
            break;

        case 3:
            system("cls");
            drawmenu_3();
            scanf ( "%d", &option );
            break;

        case 4:
            system("cls");
            drawmenu_4();
            scanf ( "%d", &option );
            break;

        case 0:
            option = 0;
            system("cls");
            break;

        default:
            system("cls");
            break;
        }
    }



    return 0;
}
