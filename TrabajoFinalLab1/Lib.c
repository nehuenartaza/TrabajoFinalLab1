#include "Lib.h"
//aca van las funciones
void register_astronaut()
{
    STastronaut user;
	int option = 1, flag = 0;
	while ( option == 1 ) {
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
        flag = confirm_astronaut_ID(user.ID);
        while ( flag == NULL ) {
            printf ( "La ID ya existe, ingrese de nuevo la ID\n" );
            scanf ( "%d", &user.ID );
            flag = confirm_astronaut_ID(user.ID);
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
		scanf ( "%d", &option );
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

int confirm_astronaut_ID(int ID)  //flag pasa a NULL si la ID está repetida
{
    int flag = 0;
    STastronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&user, sizeof(STastronaut), 1, file);
            if ( !feof(file) && ID == user.ID ) {
                flag = NULL;
            }
        }
        fclose(file);
    }
    return flag;
}

void modify_astronauts()
{
    STastronaut user, aux;
    int value = 0, option = 0, flag = 0;
    show_astronauts();
    printf ( "Modifique un astronauta\n" );
    scanf ( "%d", &value );
    while ( value < 0 ) {       //value es la posicion del registro
        printf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
        scanf ( "%d", &value );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL ) {
        fseek(file, sizeof(STastronaut) * value, SEEK_SET);
        fread(&aux, sizeof(STastronaut), 1, file);
        while ( feof(file) || value < 0 ) {   //en teoria esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
            system("cls");
            printf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
            show_astronauts();
            scanf ( "%d", &value );
            fseek(file, sizeof(STastronaut) * value, SEEK_SET);
            fread(&aux, sizeof(STastronaut), 1, file);
        }
        user = aux;
        printf ( "modificar nombre? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nuevo nombre: \n" );
            fflush(stdin);
            gets ( user.name );
        }
        printf ( "cambiar apodo? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nuevo apodo: \n" );
            fflush(stdin);
            gets ( user.nickname );
        }
        printf ( "modificar apellido? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nuevo apellido: \n" );
            fflush(stdin);
            gets ( user.last_name );
        }
        printf ( "modificar ID? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva ID: \n" );
            scanf ( "%d", &user.ID );
            flag = confirm_astronaut_ID(user.ID);
            while ( flag == NULL ) {
                printf ( "ID en uso, intente de nuevo\n" );
                scanf ( "%d", &user.ID );
                flag = confirm_astronaut_ID(user.ID);
            }
        }
        printf ( "modificar edad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva edad: \n" );
            scanf ( "%d", &user.age );
        }
        printf ( "modificar nacionalidad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva nacionalidad: \n" );
            fflush(stdin);
            gets ( user.nationality );
        }
        printf ( "modificar especialidad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva especialidad: \n" );
            fflush(stdin);
            gets ( user.speciality );
        }
        printf ( "modificar horas de vuelo? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva cantidad de hrs de vuelo: \n" );
            scanf ( &user.hours_flight );
        }
        printf ( "modificar horas en la estacion espacial? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva cantidad de hrs en la estacion espacial: \n" );
            scanf ( &user.hours_at_spaceStation );
        }
        printf ( "modificar cantidad de misiones hechas? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 ) {
            printf ( "Nueva cantidad de misiones: \n" );
            scanf ( &user.missions );
        }
        fseek(file, sizeof(STastronaut) * value, SEEK_SET);
        fwrite(&user, sizeof(STastronaut), 1, file);
        fclose(file);
    }
}

void show_astronauts()
{
    STastronaut aux;
    int i = 0;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&aux, sizeof(STastronaut), 1, file);
            if ( !feof(file)) {
                printf ( "|%d| %s '%s' %s, Edad:%d, ID:%d, horas de vuelo:%d, horas en la estacion:%d\n", i, aux.name, aux.nickname, aux.last_name, aux.age, aux.ID, aux.hours_flight, aux.hours_at_spaceStation );
                printf ( "Especialidad: %s, nacionalidad: %s, misiones hechas: %d ", aux.speciality, aux.nationality, aux.missions );
                if ( aux.status == 1 ) {
                    printf ( "Astronauta activo\n" );
                } else {
                        printf ( "Astronauta retirado\n" );
                    }
            }
            i++;
        }
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

