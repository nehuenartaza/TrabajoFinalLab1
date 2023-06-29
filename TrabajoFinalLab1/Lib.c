#include "Lib.h"
#include <unistd.h>

//aca van las funciones

//Astronautas
void registerAstronaut()        //Registra astronauta
{
    system("cls");
    stAstronaut user;
    int option = 1;
    while ( option == 1 )
    {
        pprintf ( "Nombre del astronauta:\n" );
        fflush(stdin);
        gets ( user.name );
        pprintf ( "Apellido del astronauta:\n" );
        fflush(stdin);
        gets ( user.last_name );
        pprintf ( "Apodo del astronauta:\n" );
        fflush(stdin);
        gets ( user.nickname );
        do
        {
            pprintf ( "Edad (mayor a 18 y menor a 70):\n" );
            scanf ( "%d", &user.age );
            system("cls");
        }
        while ( user.age < 18 || user.age > 70 );

        pprintf ( "Nacionalidad:\n" );
        fflush(stdin);
        gets ( user.nationality );
        pprintf ( "Especialidad:\n" );
        fflush(stdin);
        gets ( user.speciality );

        user.status = 1;    //lo registra automaticamente en 'activo'
        user.flight_hours = 0;
        user.missions = 0;
        user.hours_at_spaceStation = 0;

        if ( !firstAstronaut() )   //verifica si hay un astronauta registrado
        {
            user.ID = 1;
        }
        else
        {
            user.ID = getLastAstronautID() + 1;
        }
        printf ( "ID otorgada: %d\n", user.ID );
        saveAstronaut(user);
        pprintf ( "Para registrar otro astronauta ingrese 1. De lo contrario, ingrese otro numero:\n" );
        scanf ( "%d", &option );
        system("cls");
    }
}

void saveAstronaut(stAstronaut user)    //Guarda astronauta en archivo
{
    FILE *file = fopen(Fastronauts, "ab");
    if ( file != NULL )
    {
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

int confirmAstronautID(int ID)  //Usada para retornar flag=1 si la ID enviada se encontr� en un registro
{
    int flag = 0;
    stAstronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && ID == user.ID )
            {
                flag = 1;
            }
        }
        fclose(file);
    }
    return flag;
}

void changeAstronautNickname()  //Cambia el apodo de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nuevo apodo:\n" );
        fflush(stdin);
        gets ( user.nickname );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautAge()       //Cambia la edad de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva edad: \n" );
        scanf ( "%d", &user.age );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautSpeciality()    //Cambia la especialidad de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva especialidad: \n" );
        fflush(stdin);
        gets ( user.speciality );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautFlightTime()    //Cambia las horas de vuelo de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        do
        {
            pprintf ( "Nueva cantidad de horas de vuelo (mayor a 0): \n" );
            scanf ( "%d", &user.flight_hours );
        }
        while(user.flight_hours < 0);
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautHoursSpaceStation() //Cambia las horas que estuvo un astronauta en la estaci�n espacial
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        do
        {
            pprintf ( "Nueva cantidad de horas en la estacion espacial (mayor a 0): \n" );
            scanf ( &user.hours_at_spaceStation );
        }
        while(user.hours_at_spaceStation < 0);
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautAmmountMissions()   //Cambia la cantidad de misiones en las que particip� un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        do
        {
            pprintf ( "Nueva cantidad de misiones realizadas (mayor a 0): \n" );
            scanf ( "%d", &user.missions );
        }
        while(user.missions < 0);
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautStatus()    //Cambia el estado de un astronauta, 1-Activo, 2-Retirado
{
    stAstronaut user;
    int pos = selectAstronaut(), option = 0;
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        if ( user.status == 1 )
        {
            pprintf ( "Cambiar estado a retirado??? 1-Si \n" );
            scanf ( "%d", &option );
            if ( option == 1 )
            {
                user.status = 2;
                pprintf ( "El astronauta fue dado de baja correctamente\n" );
            }
        }
        else
        {
            pprintf ( "El astronauta ya se encuentra retirado\n" );
        }
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

int selectAstronaut()       //Selecciona un astronauta y retorna la posici�n del mismo
{
    stAstronaut user;
    int pos = 0, maxAstronauts = 0;
    showAstronauts();
    maxAstronauts = getTotalAstronauts();
    pprintf ( "Seleccione un astronauta por ID.\n" );
    scanf ( "%d", &pos );
    while ( pos < 1 || pos > maxAstronauts )
    {
        printf ( "No se permite un valor menor a 0 o mayor a %d, pruebe de nuevo\n", maxAstronauts );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        while ( pos < 1 || pos > maxAstronauts )
        {
            system("cls");
            pprintf ( "Registro no existente o valor menor a 1 no permitido, intente de nuevo\n" );
            showAstronauts();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stAstronaut) * (pos-1), SEEK_SET);
            fread(&user, sizeof(stAstronaut), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void showAstronauts()      //Muestra la totalidad del contenido del archivo de astronautas
{
    system("cls");
    stAstronaut aux;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&aux, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && aux.status == 1)
            {
                printf("-----------------------------------------\n");
                printf ( "> Nombre: %s\n> Apellido:%s\n> Apodo: '%s'\n> Edad:%d\n, ID:%d\n> Horas de vuelo:%d\n> Horas en la estacion:%d\n", aux.name, aux.last_name, aux.nickname, aux.age, aux.ID, aux.flight_hours, aux.hours_at_spaceStation );
                printf ( "> Especialidad: %s\n> Nacionalidad: %s\n> Misiones Hechas: %d\n", aux.speciality, aux.nationality, aux.missions );
                pprintf ( "> Estado: activo\n" );
                printf("-----------------------------------------\n");
            }
        }
        fclose(file);
    }
    else
    {
        system("cls");
        pprintf("No hay astronautas cargados en el sistema.");
        system("pause");
    }

    system("pause");
}

int astronautAvailability(int ID)      // Retorna la disponibilidad del astronauta, 1-activo, 2-retirado, NULL-no existe
{
    stAstronaut user;
    int availability = NULL;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file) && availability == NULL )
        {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && ID == user.ID)
            {
                if ( user.status == 1 )
                {
                    availability = 1;
                }
                else
                {
                    availability = 2;
                }
            }
        }
        fclose(file);
    }
    return availability;
}

int getLastAstronautID()        //Toma la �ltima ID de astronauta registrada y la retorna
{
    stAstronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * -1, SEEK_END);
        fread(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
    return user.ID;
}

int getTotalAstronauts()        //Retorna la cantidad total de registros de astronautas
{
    int totalRegisters = 0;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * 0, SEEK_END);
        totalRegisters = ftell(file) / sizeof(stAstronaut);
        fclose(file);
    }
    return totalRegisters;
}

bool firstAstronaut()                           //verifica si al menos hay un astronauta registrado
{
    bool first = false;
    FILE *file = fopen(Fastronauts, "rb");
    if (file != NULL)
    {
        stAstronaut user;
        if (fread(&user, sizeof(stAstronaut), 1, file) == 1)
        {
            first = true;
        }
        fclose(file);
    }
    return first;
}

void showAstronautByID()
{
    stAstronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        int ID = 0, flag = 0;
        printf ( "Ingrese la ID a buscar\n" );
        scanf ( "%d", &ID );
        while ( !feof(file))
        {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && ID == user.ID )
            {
                printf ( "%s '%s' %s, Edad: %d, Nacionalidad: %s, Especialidad: %s,", user.name, user.nickname, user.last_name, user.age, user.nationality, user.speciality );
                printf ( "horas de vuelo: %d, horas en la estacion: %d, misiones hechas: %d, ", user.flight_hours, user.hours_at_spaceStation, user.missions );
                flag = 1;
                if ( user.status == 1 )
                {
                    printf ( "Estado: activo\n" );
                }
                else
                {
                    printf ( "Estado: retirado\n" );
                }
            }
        }
        if ( flag == 0 )
        {
            printf ( "No se pudo encontrar al astronauta\n" );
        }
        fclose(file);
    }
}

int makeListOfAstronautsForMission(stAstronaut list[])
{
    stAstronaut user;
    int i = 0;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file) && i < dimChar )
        {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && user.status != 2 )
            {
                list[i] = user;
                i++;
            }
        }
        fclose(file);
    }
    return i;
}


//Naves
void saveSpaceship(stSpaceship spaceship)          //Guarda en la ultima posicion del archivo la nave recibida por parametro
{
    FILE * archive;
    archive = fopen(Fstarships, "ab");
    if(archive != NULL)
    {
        fwrite(&spaceship, sizeof(stSpaceship), 1, archive);
        fclose(archive);
    }
}

void registerSpaceship()                         //Carga de datos y en archivo una nueva nave. Con parametros en automatico
{
    system("cls");
    stSpaceship spaceship;
    if (!firstSpaceShip())
    {
        spaceship.ID = 1;
    }
    else
    {
        spaceship.ID = getLastSpaceshipID() + 1;
    }
    selectSpaceshipType(&spaceship.type);
    spaceship.flight_hours = NULL;
    spaceship.number_of_flights = NULL;
    spaceship.status = 1; // Lista para su uso
    saveSpaceship(spaceship);
    printSpaceshipData(spaceship);

    system("cls");
    pprintf("Nave cargada exitosamente, ID <");
    printf("%i", spaceship.ID);
    pprintf(">\nPara modificar sus datos, seleccione el modulo correspondiente\n");
    system("pause");
}

void selectSpaceshipType(stSpaceship *type)
{
    stSpaceship spaceship;
    int tipo = 0;
    do
    {
        pprintf( "Ingrese tipo de nave:\n\n1-Starship\n2-Falcon 9\n3-Falcon Heavy\n" );
        scanf ( "%d", &tipo);
    }
    while ( tipo <= 0 || tipo > 3 );
    if ( tipo == 1 )
    {
        strcpy(type, "Starship");
    }
    else if ( tipo == 2 )
    {
        strcpy(type, "Falcon 9");
    }
    else
    {
        strcpy(type, "Falcon Heavy");
    }
}

int getLastSpaceshipID()                         //Obtiene la ultima ID del registro
{
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    stSpaceship spaceship;
    if(archive != NULL)
    {
        fseek(archive, sizeof(stSpaceship) * -1, SEEK_END);
        fread(&spaceship, sizeof(stSpaceship), 1, archive);
        fclose(archive);
    }
    return spaceship.ID;
}

int changeSpaceshipStatus()                      //Retorna el estado de la nave elegida, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    int option = 0;
    do
    {
        system("cls");
        pprintf("Ingrese estado de la nave:\n");
        pprintf("1- Lista para su uso\n");
        pprintf("2- En Mision\n");
        pprintf("3- En mantenimiento\n");
        pprintf("4- De baja\n");
        fflush(stdin);
        scanf("%i", &option);
        if (option < 1 || option > 4)
        {
            system("cls");
            pprintf("Valor invalido, intente de nuevo.");
            system("pause");
        }
    }
    while(option < 1 || option > 4);

    return option;
}

void showSpaceshipByID()                      //Verifica si la nave existe, la busca y permite modificar sus datos o visualizarla
{
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    int ID = 0;
    int option = 0;
    if(archive != NULL)
    {
        pprintf("Inserte <ID> de nave a buscar: \n");
        pprintf("ID: ");
        fflush(stdin);
        scanf("%i", &ID);
        if(spaceshipExistByID(ID))
        {
            system("cls");
            showSpaceship(ID);
        }
        else
        {
            system("cls");
            pprintf("La nave proporcionada en base a ID no existe\n");
            system("pause");
        }
        fclose(archive);
    }
    else
    {
        system("cls");
        pprintf("No hay archivos de naves en el sistema. / Error al intentar acceder al archivo.\n");
        system("pause");
    }
}

void showSpaceship(int ID)                      //Muestra una nave por su ID
{
    FILE * archive;
    stSpaceship spaceship;
    if(spaceshipExistByID(ID))
    {
        archive = fopen(Fstarships,"rb");
        if(archive != NULL)
        {
            fseek(archive, sizeof(stSpaceship) * (ID-1), SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship),1, archive);
            printSpaceshipData(spaceship);
            fclose(archive);
        }
    }

}

bool spaceshipExistByID(int ID)                  //Retorna verdadero si la nave existe en el archivo en base al ID Recibido
{
    bool exist = false;
    stSpaceship aux;
    FILE* archive;
    archive = fopen(Fstarships, "rb");
    if (archive != NULL)
    {
        while (fread(&aux, sizeof(stSpaceship), 1, archive) == 1)
        {
            if (aux.ID == ID)
            {
                exist = true;
                break;
            }
        }
        fclose(archive);
    }
    return exist;
}

void printSpaceshipData(stSpaceship spaceship)    //Imprime por pantalla los datos de la nave
{
    pprintf("----------------------------------------\n");
    printf("ID: %i\n", spaceship.ID);
    printf("Tipo de nave: %s\n", spaceship.type);
    printf("Vuelos Realizados: %i\n", spaceship.number_of_flights);
    printf("Horas de Vuelo: %i\n", spaceship.flight_hours);
    printSpaceshipStatus(spaceship.status);
    pprintf("----------------------------------------\n");
    system("pause");
}

void printSpaceshipStatus(int spaceshipStatus)    //1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    pprintf("Estado de la nave: ");
    switch(spaceshipStatus)
    {
    case 1:
        pprintf("Lista para su uso\n");
        break;
    case 2:
        pprintf("En Mision\n");
        break;
    case 3:
        pprintf("En mantenimiento\n");
        break;
    case 4:
        pprintf("De baja\n");
        break;
    }
}

int spaceshipStatus(int ID)                      //Retorna el estado de la nave
{
    stSpaceship spaceship;
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    if(spaceshipExistByID(ID))
    {
        if(archive != NULL)
        {
            while(!feof(archive))
            {
                fread(&spaceship, sizeof(stSpaceship), 1, archive);
                if(spaceship.ID == ID)
                {
                    break;
                }
            }
            fclose(archive);
        }
    }
    else
    {
        system("cls");
        pprintf("La nave solicitada no existe\n");
        system("pause");
    }
    return spaceship.status;
}

void showAllSpaceships()                        //Muestra todas las naves cargadas en el archivo
{

    FILE* archive;
    archive = fopen(Fstarships,"rb");
    stSpaceship spaceship;
    if(archive != NULL)
    {
        do
        {
            fread(&spaceship, sizeof(stSpaceship), 1, archive);
            printSpaceshipData(spaceship);
        }
        while(!feof(archive));
        fclose(archive);
    }
    else
    {
        system("cls");
        pprintf("No hay naves cargadas en el sistema.");
        system("pause");
    }
}

void changeFlightTime(int ID, int time_fly)        //Suma el tiempo de vuelo recibido
{
    FILE * archive;
    archive = fopen(Fstarships, "w+b");
    stSpaceship spaceship;
    if(spaceshipExistByID(ID))
    {
        if(archive!= NULL)
        {
            fseek(archive, sizeof(stSpaceship) * (ID -1),SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship), 1,archive);
            fseek(archive, sizeof(stSpaceship) * (-1),SEEK_CUR);
            spaceship.flight_hours = spaceship.flight_hours + time_fly;
            fwrite(&spaceship, sizeof(stSpaceship), 1, archive);
            fclose(archive);
        }
    }
}

void changeSpaceshipFlightTime()                //Solicita un tiempo sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{
    system("cls");
    int time;
    int ID;
    pprintf("Ingrese ID de la nave: ");
    scanf("%i", &ID);
    if(spaceshipExistByID(ID))
    {
        do
        {
            pprintf("Ingrese cantidad de horas de vuelo (mayor a 0): ");
            scanf("%i", &time);
        }
        while(time < 0);

        changeFlightTime(ID, time);
    }
    else
    {
        pprintf("ID nave invalida");
    }
}

void showFlightTime(int ID)                        //Muestra el tiempo de vuelo por ID
{
    FILE* archive;
    archive = fopen(Fstarships, "rb");
    stSpaceship spaceship;
    if(spaceshipExistByID(ID))
    {
        if(archive != NULL)
        {
            fseek(archive, sizeof(stSpaceship) * (ID -1), SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship), 1, archive);
            pprintf("Cantidad de horas en vuelo: ");
            printf("%i\n", spaceship.flight_hours);
            fclose(archive);
        }
    }
}

void showFlightsAmount(int ID)                    //Muestra la cantidad de vuelos
{

    FILE* archive;
    archive = fopen(Fstarships, "rb");
    stSpaceship spaceship;
    if(spaceshipExistByID(ID))
    {
        if(archive != NULL)
        {
            fseek(archive, sizeof(stSpaceship) * (ID -1), SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship), 1, archive);
            pprintf("Cantidad de vuelos: ");
            printf("%i\n", spaceship.number_of_flights);
            fclose(archive);
        }
    }
}

void changeFlightsAmount(int ID, int times_fly)    //Cambia la cantidad de vuelos
{
    FILE * archive;
    archive = fopen(Fstarships, "w+b");
    stSpaceship spaceship;
    if(spaceshipExistByID(ID))
    {
        if(archive!= NULL)
        {
            fseek(archive, sizeof(stSpaceship) * (ID -1),SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship), 1,archive);
            fseek(archive, sizeof(stSpaceship) * (-1),SEEK_CUR);
            spaceship.number_of_flights = spaceship.number_of_flights + times_fly;
            fwrite(&spaceship, sizeof(stSpaceship), 1, archive);
            fclose(archive);
        }
    }
}

void changeSpaceshipFlightsAmount()
{
    int times;
    int ID;
    pprintf("Ingrese ID de la nave: ");
    scanf("%i", &ID);
    pprintf("Ingrese cantidad de vuelos: ");
    scanf("%i", &times);
    changeFlightsAmount(ID, times);
    changeSpaceshipFlightTimeID();

}

void changeSpaceshipFlightTimeID(ID)                //Solicita un tiempo sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{

    int time;
    do
    {
        pprintf("Ingrese cant de horas: ");
        system("cls");
        scanf("%i", &time);
        if(time<0)
        {
            system("cls");
            pprintf("Valor invalido\n");

        }
    }
    while(time<0);

    changeFlightTime(ID, time);
}

bool firstSpaceShip()                                               //verifica si hay al menos una nave registrada
{
    bool firstOne = false;

    FILE *archive;
    archive = fopen(Fstarships, "rb");

    if (archive != NULL)
    {
        stSpaceship spaceship;
        if (fread(&spaceship, sizeof(stSpaceship), 1, archive) == 1)
        {
            firstOne = true;
        }

        fclose(archive);
    }

    return firstOne;
}

void autoChangeSpaceshipStatus(int IDsearch, int flag, int option)    //cambia el estado de una nave autom�ticamente cuando una mision es retornada, falla o se cancela, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    stSpaceship spaceship;
    FILE *file = fopen(Fstarships, "r+b");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&spaceship, sizeof(stSpaceship), 1, file);
            if ( !feof(file) && IDsearch == spaceship.ID )
            {
                if ( flag == 1 && option == 1 )     //si la mision es puesta en vuelo
                {
                    spaceship.status = 2;
                }
                if ( flag == 1 && option == 2 )     //si la mision es cancelada
                {
                    spaceship.status = 3;
                }
                if ( flag == 2 && option == 1 )     //si la mision retorn�
                {
                    spaceship.status = 3;
                }
                if ( flag == 2 && option == 2 )
                {
                    spaceship.status = 4;
                }
            }
        }
        fseek(file, sizeof(stSpaceship) * -1, SEEK_CUR);
        fwrite(&spaceship, sizeof(stSpaceship), 1, file);
        fclose(file);
    }
}

int makeListOfSpaceshipsForMission(stSpaceship list[])
{
    stSpaceship spaceship;
    int i = 0;
    FILE *file = fopen(Fstarships, "rb");
    if ( file != NULL )
    {
        while ( !feof(file) && i < dimChar )
        {
            fread(&spaceship, sizeof(stSpaceship), 1, file);
            if ( !feof(file) && spaceship.status  == 1 )
            {
                list[i] = spaceship;
                i++;
            }
        }
        fclose(file);
    }
    return i;
}


//Misiones
void registerMission()                      //Registra una misi�n
{
    stSpaceship spaceships[300];
    stAstronaut astronauts[300];
    int totalSpaceshipsList = makeListOfSpaceshipsForMission(spaceships);
    int totalAstronautsList = makeListOfAstronautsForMission(astronauts);

    if ( totalAstronautsList != 0 && totalSpaceshipsList != 0 )
    {
        stMission mission;
        int aux = 0; //contador para mostrar el listado de astronautas y naves obtenidas
        int option = 1, flag = 0,  i = 0; //i, contador de tripulantes por misi�n
        for ( aux = 0; aux < totalSpaceshipsList; aux++ )
        {
            printSpaceshipData(spaceships[aux]);
        }
        do
        {
            pprintf ( "ID de la nave a enviar a la mision:\n" );
            scanf ( "%d", &mission.ship_ID );
            for ( aux = 0; aux < totalSpaceshipsList; aux++ )
            {
                if ( spaceships[aux].ID == mission.ship_ID )   //confirma si la ID de nave coincide con alguna de las naves en la lista
                {
                    flag = 1;
                }
            }
            system("cls");
            if(flag == 0)
            {
                pprintf("ID invalido, intente nuevamente.\n");
            }
        }
        while ( flag == 0 );

        do
        {
            pprintf ( "Destino de la mision: 1- EEI, 2- Orbita Terrestre, 3- Luna\n" );
            scanf ( "%d", &mission.destination );
            system("cls");
        }
        while ( mission.destination <= 0 || mission.destination > 3 );

        do
        {
            pprintf ( "Tipo de cargamento de la mision: 1- Satelite, 2- Insumos para la EE\n" );
            scanf ( "%d", &mission.shipment);
            system("cls");
        }
        while ( mission.shipment <= 0 || mission.shipment > 2 );

            do
            {
                system("cls");
                showAstronauts();
                printf ( "Ingrese la ID del tripulante que va a estar presente en la mision: \n" );
                flag = 0;
                scanf ( "%d", &mission.crewmen[i]);
                for(aux = 0; aux < totalAstronautsList; aux++)
                    {
                    if ( astronauts[aux].ID == mission.crewmen[i])
                        {
                            flag = 1;
                        }
                    }
                if(flag == 0)
                {
                    pprintf("La ID ingresada no corresponde a un astronauta existente.\n");
                }
                pprintf("Para ingresar mas astronautas en la mision, acceder a la seccion de modificar lista de Astronautas.\n");
            }while ( flag == 0 );


        mission.crewman_amount = 1;       //cantidad total de tripulantes
        printf ( "Agregue una breve descripcion de la mision: (%d caracteres max)\n", dimChar );
        fflush(stdin);
        gets ( mission.mission_details );
        if ( !firstSpaceShip() )        //verifica si hay al menos una mision registrada
        {
            mission.ID = 1;
        }
        else
        {
            mission.ID = getLastMissionID() + 1;
        }
        printf ( "ID otorgada a la mision: %d", mission.ID );
        mission.status = 1; //lo registra autom�ticamente en 'mision lista'
        saveMission(mission);
        system("cls");
    }
    else
        {
            pprintf("No hay suficientes naves o astronautas disponibles para crear una mision.");
        }
}

void saveMission(stMission the_mission)     //Guarda la misi�n en un archivo
{
    FILE *file = fopen(Fmissions, "ab");
    if ( file != NULL )
    {
        fwrite(&the_mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionStarshipID()              //Se cambia la nave que se va a utilizar en la misi�n
{
    stMission mission;
    bool flag = false;      //Confirma si la ID de la nave existe o no
    int pos = selectMission(), shipAvailability = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nueva nave para enviar a la mision (ingresar la ID): \n" );
        scanf ( "%d", &mission.ship_ID );
        flag = spaceshipExistByID(mission.ship_ID);
        while ( flag != true || shipAvailability != 1 )
        {
            pprintf ( "ID de nave no existente o nave no lista para su uso, intente de nuevo.\n" );
            scanf ( "%d", &mission.ship_ID );
            flag = spaceshipExistByID(mission.ship_ID);

            if ( flag == true )
            {
                shipAvailability = spaceshipStatus(mission.ship_ID);
            }
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionDetails()                 //Cambia la breve descripci�n de la misi�n
{
    stMission mission;
    int pos = selectMission();
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevos detalles (max 50 caracteres): \n" );
        fflush(stdin);
        gets ( mission.mission_details );
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionShipment()                //Cambia el cargamento de la misi�n
{
    stMission mission;
    int pos = selectMission();
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevo cargamento: 1- Satelite, 2- Insumos para la EE\n" );
        scanf ( "%d", &mission.shipment );
        while ( mission.shipment < 1 || mission.shipment > 2 )
        {
            pprintf ( "Cargamento no existente, pruebe de nuevo. \n" );
            scanf ( "%d", &mission.shipment );
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionDestination()             //Cambia el destino de la misi�n
{
    stMission mission;
    int pos = selectMission();
    FILE *file = (Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevo destino: 1- EEI, 2- Orbita terrestre, 3- Luna" );
        scanf ( "%d", &mission.destination );
        while ( mission.destination <= 0 || mission.destination > 3 )
        {
            pprintf ( "Destino desconocido, vuelva a intentarlo.\n" );
            scanf ( "%d", &mission.destination );
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionCrewmanList()             //Cambia el listado de tripulantes que se van a enviar a la misi�n
{
    stMission mission;
    int lastID = 0;
    int pos = selectMission(), option = 1, i = 0, flag = 0;
    FILE * file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        showAstronauts();
        pprintf ( "Seleccione los tripulantes por sus IDs:\n" );
        for ( i = 0; i < dimInt && option == 1; i++ )
        {
            do
            {
                fflush(stdin);
                scanf ( "%d", &lastID );

                if(inThere(lastID, mission.crewmen,i))
                {
                    pprintf("Este astronauta ya participa de la mision.\n");
                    pprintf("Ingrese una ID valida\n");
                }

            flag = confirmAstronautID(lastID);
            if(flag != 1)
            {
                pprintf ( "El astronauta no existe, intente de nuevo.\n" );
            }
            }while(inThere(lastID,mission.crewmen,i) || flag != 1);

            mission.crewmen[i] = lastID;

            pprintf ( "Agregar otro astronauta? 1-Si Otro-No\n" );
            scanf ( "%d", &option );

        }
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);

    }
}

void changeMissionStatus()                  //Cambia el estado de la misi�n, 1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
{
    stMission mission;
    int pos = selectMission(), option = 0, flag = 0;    //Indica en qu� caso del swtich entr�
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        switch ( mission.status )
        {
        case 1:                                                                 //Caso de si la mision est� lista
            flag = 1;
            pprintf ( "Estado de la mision: 'Lista'\n" );
            pprintf ( "Iniciar mision? Ingrese 1 | Cancelar la mision? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 )
            {
                mission.status = 2;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'en vuelo'\n" );
            }
            if ( option == 2 )
            {
                mission.status = 4;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Cancelada'\n" );
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            break;

        case 2:                                                                 //Caso de si la mision est� en vuelo
            flag = 2;
            pprintf ( "Estado de la mision: 'En vuelo'\n" );
            pprintf ( "La mision esta retornada? Ingrese 1 | La mision ha fallado? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 )
            {
                mission.status = 3;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Retornada'\n" );
            }
            if ( option == 2 )
            {
                mission.status = 5;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Fallida'\n" );
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            break;

        default:
            pprintf ( "La mision que se ha seleccionado no tiene el estado de 'Lista' o 'En vuelo' por lo tanto no puede ser modificada\n" );
            break;
        }
        fclose(file);
    }
}

int selectMission()                         //fedep: probar esto porfa//Selecciona una misi�n y retorna la posici�n de la misma
{
    stMission mission;
    int pos = 0;
    showMissions();
    pprintf ( "Seleccione una mision:\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 )
    {
        pprintf ( "No se permite un valor menor a 0, pruebe de nuevo.\n" );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        while ( feof(file) || pos < 0 )     //en teor�a esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
        {
            system("cls");
            pprintf ( "Registro no existente o valor menor a 0 no permitido, intente de nuevo.\n" );
            showMissions();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stMission) * pos, SEEK_SET);
            fread(&mission, sizeof(stMission), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void showMissions()                         //muestra todas las misiones registradas
{
    stMission mission;
    int i = 0, j = 0;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&mission, sizeof(stMission), 1, file);
            if ( !feof(file))
            {
                printf ( "|%d| ID:%d, ID de nave:%d, ", i, mission.ID, mission.ship_ID );
                if ( mission.shipment == 1 )
                {
                    pprintf ( "Cargamento: satelite, " );
                }
                else
                {
                    pprintf ( "Cargamento: insumos para la EE, " );
                }
                if ( mission.destination == 1 )
                {
                    pprintf ( "Destino: EEI\n" );
                }
                else if ( mission.destination == 2 )
                {
                    pprintf ( "Destino: Orbita Terrestre\n" );
                }
                else
                {
                    pprintf ( "Destino: Luna\n" );
                }
                printf ( "Resumen de Mision: %s\n", mission.mission_details );
                for ( j = 0; j < mission.crewman_amount; j++ )
                {
                    printf ( "ID del Tripulante %d: %d\n", j+1, mission.crewmen[j] );
                }
                if ( mission.status == 1 )
                {
                    pprintf ( "Estado de mision: Lista" );
                }
                else if ( mission.status == 2 )
                {
                    pprintf ( "Estado de mision: En vuelo" );
                }
                else if ( mission.status == 3 )
                {
                    pprintf ( "Estado de mision: Retornada" );
                }
                else if ( mission.status == 4 )
                {
                    pprintf ( "Estado de mision: Cancelada" );
                }
                else
                {
                    pprintf ( "Estado de mision: Fallida" );
                }
            }
            i++;
        }
    }
}

int getLastMissionID()                       //Toma la �ltima ID de misi�n registrada y la retorna
{
    stMission mission;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * -1, SEEK_END);
        fread(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }

    return mission.ID;
}

bool firstMission()                             //verifica si al menos hay una mision registrada
{
    bool firstMission = false;
    FILE *file = fopen(Fmissions, "rb");
    if (file != NULL)
    {
        stMission mission;
        if (fread(&mission, sizeof(stMission), 1, file) == 1)
        {
            firstMission = true;
        }
        fclose(file);
    }
    return firstMission;
}

bool inThere(int forSearch, int array[], int valids)
{
    bool isIn = false;
    for(int i = 0; i < valids; i++)
    {
        if(forSearch == array[i])
        {
            isIn = true;
            break;
        }

    }

    return isIn;
}


//Otros
void pprintf(const char *str)
{
    int i = 0;

    if (proceduralTextRead())
    {
        while (str[i] != '\0')
        {
            putchar(str[i]);
            fflush(stdout);
            usleep(1000);
            i++;
        }
        usleep(10000);
    }
    else
    {
        printf("%s", str);
    }
}


//UsuarioData
void changeColor()
{
    int option;
    int maxColors = 5;

    do
    {
        textColorsOptions();
        scanf("%i", &option);
        colorOption(option);
    }
    while (option < 1 || option > maxColors);

    saveColorChange(option);
}

void setColor(int colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void textColorsOptions()
{
    pprintf("Seleccione un color:\n");
    setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    pprintf("1. Azul\n");
    setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    pprintf("2. Verde\n");
    setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    pprintf("3. Rojo\n");
    setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    pprintf("4. Amarillo\n");
    setColor(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    pprintf("5. Blanco\n");
    readUserData();
    pprintf("Ingrese su opcion: ");
}

void colorOption(int option)
{
    switch (option)
    {
    case 1:
        setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;
    case 2:
        setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        break;
    case 3:
        setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 4:
        setColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
        break;
    case 5:
        setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        break;

    default:
        system("cls");
        pprintf("Opcion invalida\n");
        break;
    }
}

void saveColorChange(int colorChosen)
{
    stUserData userData;
    userData.proceduralText = proceduralTextRead();
    userData.consoleColor = colorChosen;
    FILE* archive = fopen(FuserData, "w+b");

    if (archive != NULL)
    {
        fwrite(&userData, sizeof(userData), 1, archive);
        fclose(archive);
        pprintf("Eleccion de color guardada con exito.\n");
    }
    else
    {
        pprintf("No se pudo abrir el archivo para guardar la eleccion de color.\n");
    }
}

void readUserData()
{
    stUserData userData;
    int color;

    FILE* archive;
    archive = fopen(FuserData, "rb");
    if (archive == NULL)
    {
        archive = fopen(FuserData, "w+b");
        if (archive != NULL)
        {
            stUserData userData;
            userData.consoleColor = 5;//Blanco
            userData.proceduralText = true;
            fwrite(&userData, sizeof(stUserData), 1, archive);
            fclose(archive);
        }
    }
    else
    {
        fread(&userData, sizeof(stUserData), 1, archive);
        color = userData.consoleColor;
        colorOption(color);
        fclose(archive);
    }
}

bool proceduralTextRead()
{
    stUserData userData;

    FILE * archive;
    archive = fopen(FuserData, "rb");
    if(archive != NULL)
    {
        fread(&userData, sizeof(userData), 1, archive);
        fclose(archive);
    }
    return userData.proceduralText;
}


//Menus
