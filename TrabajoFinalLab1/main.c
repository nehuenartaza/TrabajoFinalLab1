#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define dimInt 15
#define dimChar 50

typedef struct {
	char nombre[dimChar];
	char apellido[dimChar];
	char apodo[dimChar];
	int ID;
	int edad;
	char nacionalidad[dimChar];
	char especialidad[dimChar];
	int horas_vuelo;
	int misiones;
	int horas_estacion_espacial;
	int estado; //1-activo, 2-retirado
} STastronauta;
typedef struct {
	int ID;
	int tipo_nave; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
	int vuelos;
	int horas_vuelo;
	int estado; //0-mantenimiento, 1-lista para usar, 2-en uso, 3-de baja
} STnave;
typedef struct {
	int ID;
	int ID_nave;
	int estado; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
	int destino; //1-EEI, 2-orbita terrestre, 3-luna
	int cargamento; //1-satelite, 2-insumos para la EE
	int tripulantes[dimInt];
	char detalle_mision[dimChar]; //breve descripcion
	int cant_tripulantes;
} STmision;
int main()
{
    int opcion = 1, flag = NULL, posicion = NULL, search_astronauta = 0, search_nave = 0, search_mision = 0;
    while ( opcion == 1 ) {
        printf ( "Bienvenido!\n" );
        drawmenu_principal();
        scanf ( "%d", &opcion );
        switch ( opcion ) {
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









void drawmenu_principal()
{
	printf ( "1- Registrar\n" );
	printf ( "2- Modificar\n" );
	printf ( "3- Consultar\n" );
	printf ( "4- Mofidicar estados de astronautas, naves y misiones\n" );
	printf ( "0- Cerrar programa\n" );
	printf ( "opcion: " );
}
void drawmenu_1()
{
	printf ( "1 | 1- Registrar astronautas\n" );
	printf ( "1 | 2- Registrar naves\n" );
	printf ( "1 | 3- Registrar misiones\n" );
	printf ( "1 | 4- Regresar al menu principal\n" );
	printf ( "opcion: " );
}
void drawmenu_2()
{
    printf ( "2 | 1- Modificar astronauta\n" );
    printf ( "2 | 2- Modificar nave\n" );
    printf ( "2 | 3- Modificar mision\n" );
    printf ( "2 | 4- Regresar\n" );
    printf ( "opcion: " );
}
void drawmenu_3()
{
    printf ( "3 | 1- Consultar astronautas por ID\n" );
    printf ( "3 | 2- Consultar naves por ID\n" );
    printf ( "3 | 3- Consultar misiones por ID\n" );
    printf ( "3 | 4- Regresar\n" );
    printf ( "opcion: " );
}
void drawmenu_4()
{
    printf ( "4 | 1- Dar de Alta a un astronauta\n" );
    printf ( "4 | 2- Dar de Baja a un astronauta\n" );
    printf ( "4 | 3- Cambiar estado de una nave\n" );
    printf ( "4 | 4- Cambiar estado de una mision\n" );
    printf ( "opcion: " );
}
