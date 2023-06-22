#include "Lib.h"

//aca van las funciones
void register_astronaut()
{
    STastronaut user;
    int flag = NULL;
	int opcion = 1;
	while ( opcion == 1 ) {
		printf ( "Nombre del astronauta:\n" );
		fflush(stdin);
		gets ( user.name );
		printf ( "Apellido del astronauta:\n" );
		fflush(stdin);
		gets ( user.last_name );
		printf ( "Apodo del astronauta:\n" );
		fflush(stdin);
		gets ( user.nickname );
		printf ( "Su ID:\n" );
		scanf ( "%d", &user.ID );
        //crear la funcion de validar que no se repitan las ID de astronautas
        if ( flag == NULL ) {
            printf ( "" );
        }
		printf ( "Su edad:\n" );
		scanf ( "%d", &user.age );
		printf ( "Nacionalidad:\n" );
		fflush(stdin);
		gets ( user.nationality );
		printf ( "Especialidad:\n" );
		fflush(stdin);
		gets ( user.speciality );
		printf ( "Horas de vuelo acumuladas:\n" );
		scanf ( "%d", &user.hours_flight );
		printf ( "Cantidad de misiones en las que ha participado:\n" );
		scanf ( "%d", &user.missions );
		printf ( "Horas invertidas en la estacion espacial:\n" );
		scanf ( "%d", &user.hours_at_spaceStation );
		user.status = 1; //lo registra automaticamente en 'activo'
        save_astronaut(user);
		printf ( "para registrar otro astronauta ingrese 1:\n" );
		scanf ( "%d", &opcion );
	}
}

void save_astronaut(STastronaut user)
{
    FILE *file = fopen(Fastronauts, "ab");
	if ( file != NULL ) {
		fwrite(&user, sizeof(STastronaut), 1, file);
		fclose(file);
	}

}
void draw_mainmenu()
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
