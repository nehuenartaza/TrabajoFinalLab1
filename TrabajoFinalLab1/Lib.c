#include "Lib.h"
//aca van las Funciones




void drawmenu_principal()
{
    system("cls");
    printf ( "1- Registrar\n" );
    printf ( "2- Modificar\n" );
    printf ( "3- Consultar\n" );
    printf ( "4- Mofidicar estados de astronautas, naves y misiones\n" );
    printf ( "0- Cerrar programa\n" );
    printf ( "opcion: " );
}
void drawmenu_1()
{
    system("cls");
    printf ( "1 | 1- Registrar astronautas\n" );
    printf ( "1 | 2- Registrar naves\n" );
    printf ( "1 | 3- Registrar misiones\n" );
    printf ( "1 | 4- Regresar al menu principal\n" );
    printf ( "opcion: " );
}
void drawmenu_2()
{
    system("cls");
    printf ( "2 | 1- Modificar astronauta\n" );
    printf ( "2 | 2- Modificar nave\n" );
    printf ( "2 | 3- Modificar mision\n" );
    printf ( "2 | 4- Regresar\n" );
    printf ( "opcion: " );
}
void drawmenu_3()
{
    system("cls");
    printf ( "3 | 1- Consultar astronautas por ID\n" );
    printf ( "3 | 2- Consultar naves por ID\n" );
    printf ( "3 | 3- Consultar misiones por ID\n" );
    printf ( "3 | 4- Regresar\n" );
    printf ( "opcion: " );
}
void drawmenu_4()
{
    system("cls");
    printf ( "4 | 1- Dar de Alta a un astronauta\n" );
    printf ( "4 | 2- Dar de Baja a un astronauta\n" );
    printf ( "4 | 3- Cambiar estado de una nave\n" );
    printf ( "4 | 4- Cambiar estado de una mision\n" );
    printf ( "opcion: " );
}
