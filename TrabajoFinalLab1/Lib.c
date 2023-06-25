#include "Lib.h"
#include <unistd.h>

//aca van las funciones

//Astronautas
void registerAstronaut()        //Registra astronauta
{
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
        pprintf ( "Edad:\n" );
        scanf ( "%d", &user.age );
        pprintf ( "Nacionalidad:\n" );
        fflush(stdin);
        gets ( user.nationality );
        pprintf ( "Especialidad:\n" );
        fflush(stdin);
        gets ( user.speciality );
        pprintf ( "Horas de vuelo acumuladas:\n" );
        scanf ( "%d", &user.flight_hours );
        pprintf ( "Cantidad de misiones en las que ha participado:\n" );
        scanf ( "%d", &user.missions );
        pprintf ( "Horas invertidas en la estacion espacial:\n" );
        scanf ( "%d", &user.hours_at_spaceStation );
        user.status = 1; //lo registra automaticamente en 'activo'
        user.ID = getLastAstronautID() + 1; //le otorga la última ID encontrada + 1
        printf ( "ID otorgada: %d", user.ID );
        saveAstronaut(user);
        pprintf ( "Para registrar otro astronauta ingrese 1. De lo contrario, ingrese otro numero:\n" );
        scanf ( "%d", &option );
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

int confirmAstronautID(int ID)  //Usada para encontrar ID repetida y verificar si existe el tripulante, retorna NULL si la ID enviada se encontró en un registro
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
                flag = NULL;
            }
        }
        fclose(file);
    }
    return flag;
}

void changeAstronautName()      //Cambia el nombre de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nuevo nombre: \n" );
        fflush(stdin);
        gets ( user.name );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautLastName()  //Cambia el apellido de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nuevo apellido: \n" );
        fflush(stdin);
        gets ( user.last_name );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautNickname()  //Cambia el apodo de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
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
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva edad: \n" );
        scanf ( "%d", &user.age );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautID()        //Cambia la ID de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut(), flag = 0;  //flag confirma que la ID que se quiera otorgar no exista previamente
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva ID: \n" );
        scanf ( "%d", &user.ID );
        flag = confirmAstronautID(user.ID);
        while ( flag == NULL )
        {
            pprintf ( "ID en uso, intente de nuevo\n" );
            scanf ( "%d", &user.ID );
            flag = confirmAstronautID(user.ID);
        }
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautNationality()   //Cambia la nacionalidad de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva nacionalidad: \n" );
        fflush(stdin);
        gets ( user.nationality );
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
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
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
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva cantidad de horas de vuelo: \n" );
        scanf ( "%d", &user.flight_hours );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautHoursSpaceStation() //Cambia las horas que estuvo un astronauta en la estación espacial
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva cantidad de horas en la estacion espacial: \n" );
        scanf ( &user.hours_at_spaceStation );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void changeAstronautAmmountMissions()   //Cambia la cantidad de misiones en las que participó un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva cantidad de misiones: \n" );
        scanf ( "%d", &user.missions );
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
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Cambiar estado??? 1-Si \n" );
        scanf ( "%d", &option );
        if ( option == 1 && user.status == 1 )
        {
            user.status = 2;
            pprintf ( "El astronauta ahora es un retirado\n" );
        }
        if ( option == 1 && user.status == 2 )
        {
            user.status = 1;
            pprintf ( "El astronauta ahora es activo\n" );
        }
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

int selectAstronaut()       //Selecciona un astronauta y retorna la posición del mismo
{
    stAstronaut user;
    int pos = 0, maxAstronauts = 0;
    showAstronauts();
    maxAstronauts = getTotalAstronauts();
    pprintf ( "Seleccione un astronauta\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 || pos > maxAstronauts )
    {
        printf ( "No se permite un valor menor a 0 o mayor a %d, pruebe de nuevo\n", maxAstronauts );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        while ( pos < 0 || pos > maxAstronauts )
        {
            system("cls");
            pprintf ( "Registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
            showAstronauts();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
            fread(&user, sizeof(stAstronaut), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void showAstronauts()      //Muestra la totalidad del contenido del archivo de astronautas
{
    stAstronaut aux;
    int i = 0;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&aux, sizeof(stAstronaut), 1, file);
            if ( !feof(file))
            {
                printf ( "|%d| %s '%s' %s, Edad:%d, ID:%d, horas de vuelo:%d, horas en la estacion:%d\n", i, aux.name, aux.nickname, aux.last_name, aux.age, aux.ID, aux.flight_hours, aux.hours_at_spaceStation );
                printf ( "Especialidad: %s, Nacionalidad: %s, Misiones Hechas: %d ", aux.speciality, aux.nationality, aux.missions );
                if ( aux.status == 1 )
                {
                    pprintf ( "Astronauta activo\n" );
                }
                else
                {
                    pprintf ( "Astronauta retirado\n" );
                }
            }
            i++;
        }
        fclose(file);
    }
}

int astronautAvailability(int ID)      //Indica la disponibilidad del astronauta, 1-activo, 2-retirado, NULL-no existe
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
    }
    return availability;
}

int getLastAstronautID()        //Toma la última ID de astronauta registrada y la retorna
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
    stAstronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL ) {
        totalRegisters = fseek(file, sizeof(stAstronaut) * 0, SEEK_END) / sizeof(stAstronaut);
    }
    return totalRegisters;
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
    stSpaceship spaceship;
    if (!firstSpaceShip())
    {
        spaceship.ID = 1;
    }
    else
    {
        spaceship.ID = getLastSpaceshipID() + 1;
    }
    changeSpaceshipType(&spaceship.type);
    spaceship.flight_hours = NULL;
    spaceship.number_of_flights = NULL;
    spaceship.status = 1; // Lista para su uso
    saveSpaceship(spaceship);
    printSpaceshipData(spaceship);

    system("cls");
    pprintf("Nave cargada exitosamente, ID <");
    printf("%i", spaceship.ID);
    pprintf(">\nPara modificar sus datos, seleccione el modulo correspondiente\n");
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

void changeSpaceshipType(char spaceshipName[])    //Cambia el tipo de nave
{
    int Max = 3;
    int option = 0;
    do
    {
        system("cls");
        pprintf("Tipo de nave:\n");
        pprintf("1- Starship \n");
        pprintf("2- Falcon 9\n");
        pprintf("3- Falcon Heavy\n");
        fflush(stdin);
        scanf("%i", &option);
        if (option < 1 || option > Max )
        {
            system("cls");
            pprintf("Valor invalido, intente de nuevo.\n");
            system("pause");
        }
    }
    while(option < 1 || option > Max);
    switch(option)
    {
    case 1:
        strcpy((spaceshipName), "Starship");
        break;

    case 2:
        strcpy((spaceshipName), "Falcon 9");
        break;

    case 3:
        strcpy((spaceshipName), "Falcon Heavy");
        break;
    }
}

int changeSpaceshipStatus()                      //Retorna el estado de la nave elegida, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    int Max = 4;
    int option;
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
        if (option < 1 || option > Max)
        {
            system("cls");
            pprintf("Valor invalido, intente de nuevo.");
            system("pause");
        }
    }
    while(option < 1 || option > Max);

    return option;
}

void searchSpaceshipByID()                      //Verifica si la nave existe, la busca y permite modificar sus datos o visualizarla
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
            do
            {
                system("cls");
                pprintf("Nave encontrada\n ¿Que desea hacer?\n");
                pprintf("1- Mostrar Nave.\n");
                pprintf("2- Ver y Modificar nave.\n");
                fflush(stdin);
                pprintf(">: ");
                scanf("%i", &option);
                switch(option)
                {
                case 1://Mostrar
                    system("cls");
                    showSpaceship(ID);
                    break;

                case 2://Modificar
                    system("cls");
                    pprintf("Datos actuales de la nave: \n");
                    showSpaceship(ID);
                    pprintf("\nQue desea modificar: \n");
                    pprintf(" 1- Estado de la nave.\n");
                    pprintf(" 2- Horas de vuelo.\n");
                    pprintf(" 3- Tipo de nave.\n");
                    pprintf(" 4- Cantidad de viajes.\n");
                    pprintf(">: ");
                    scanf("%i", &option);
                    break;

                default:
                    system("cls");
                    pprintf("Dato no valido en el contexto actual\n");
                    break;
                }
            }
            while(option != 2 && option  != 1);
        }
        else
        {
            system("cls");
            pprintf("La nave proporcionada en base a ID no existe\n");
            system("pause");
        }
        fclose(archive);
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

void printAllSpaceships()                        //Muestra todas las naves cargadas en el archivo
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
    }
    else
    {
        system("cls");
        pprintf("No hay naves cargadas en el sistema");
        system("pause");
    }
}

void changeFlightTime(int ID, int time_fly)        //Cambia el tiempo de vuelo
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

void changeFlightTimeByUser(int ID)                //Solicita un tiempo sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{
    int time;
    pprintf("Ingrese cant de horas: ");
    scanf("%i", &time);
    changeFlightTime(ID, time);
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

void changeFlightsAmountByUser(int ID)             //Solicita una cantidad sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{
    int times;
    pprintf("Ingrese cantidad de horas: ");
    scanf("%i", &times);
    changeFlightsAmount(ID, times);
}


//Misiones
void registerMission()                      //Registra una misión
{
    stMission mission;
    bool shipExists = false;
    int option = 1, flag = 0, shipAvailability = 0, availabilityOfAstronaut = 0, i = 0; //i, contador de tripulantes por misión
    while ( option == 1 )
    {
        pprintf ( "ID de la nave a enviar a la mision:\n" );
        scanf ( "%d", &mission.ship_ID );
        shipExists = spaceshipExistByID(mission.ship_ID);
        while ( shipExists != true || shipAvailability != 1 )   //Primero confirma que la nave exista, luego confirma que la nave que existe esté lista para su uso
        {
            pprintf ( "La ID de la nave no existe o la nave no esta lista para su uso, intente de nuevo.\n" );
            scanf ( "%d", &mission.ship_ID );
            shipExists = spaceshipExistByID(mission.ship_ID);

            if ( shipExists == true )
            {
                shipAvailability = spaceshipStatus(mission.ship_ID);
            }
        }
        pprintf ( "Destino de la mision: 1- EEI, 2- Orbita Terrestre, 3- Luna\n" );
        scanf ( "%d", &mission.destination );
        while ( mission.destination <= 0 || mission.destination > 3 )
        {
            pprintf ( "Destino desconocido, intente de nuevo.\n" );
            scanf ( "%d", &mission.destination );
        }
        pprintf ( "Tipo de cargamento de la mision: 1- Satelite, 2- Insumos para la EE\n" );
        scanf ( "%d", &mission.shipment);
        while ( mission.shipment < 0 || mission.shipment > 2 )
        {
            pprintf ( "Cargamento desconocido, intente de nuevo.\n" );
            scanf ( "%d", &mission.shipment );
        }
        printf ( "Ingrese las ID de los tripulantes que van a estar presentes en la mision: (Hasta %d Tripulantes como maximo)\n", dimInt );
        for ( i = 0; option == 1 && i < dimInt; i++ )
        {
            scanf ( "%d", &mission.crewmen[i] );
            flag = confirmAstronautID(mission.crewmen[i]);               //confirma si el astronauta existe
            availabilityOfAstronaut = astronautAvailability(mission.crewmen[i]);     //confirma si el astronauta está disponible o si está retirado
            while ( flag != NULL || availabilityOfAstronaut != 1 )  //Primero confirma que el astronauta exista, luego comprueba que es astronauta no esté retirado
            {
                pprintf ( "La ID no existe o el astronauta no esta disponible, ingrese de nuevo la ID.\n" );
                scanf ( "%d", &mission.crewmen[i]);
                flag = confirmAstronautID(mission.crewmen[i]);
                availabilityOfAstronaut = astronautAvailability(mission.crewmen[i]);
            }
            pprintf ( "Para incluir otro tripulante ingrese 1. De lo contrario ingrese un numero distinto:\n" );
            scanf ( "%d", &option );
        }
        mission.crewman_amount = i;       //cantidad total de tripulantes
        printf ( "Agregue una breve descripcion de la mision: (%d caracteres max)\n", dimChar );
        fflush(stdin);
        gets ( mission.mission_details );
        mission.ID = getLastMissionID() + 1;
        mission.status = 1; //lo registra automáticamente en 'mision lista'
        saveMission(mission);
        pprintf ( "Para registrar otra mision ingrese 1. De lo contrario, ingrese otro numero:\n" );
        scanf ( "%d", &option );
    }
}

void saveMission(stMission the_mission)     //Guarda la misión en un archivo
{
    FILE *file = fopen(Fmissions, "ab");
    if ( file != NULL )
    {
        fwrite(&the_mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

int confirmMissionID(int ID)                //Usada para encontrar ID repetida y verificar si existe la misión, retorna NULL si la ID enviada se encontró en un registro
{
    int flag = 0;
    stMission the_mission;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&the_mission, sizeof(stMission), 1, file);
            if ( !feof(file) && ID == the_mission.ID )
            {
                flag = NULL;
            }
        }
        fclose(file);
    }
    return flag;
}

void changeMissionID()                      //Modifica la ID de una misión
{
    stMission mission;
    int pos = selectMission(), flag = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nueva ID de mision: \n" );
        scanf ( "%d", &mission.ID );
        flag = confirmMissionID(mission.ID);
        while ( flag == NULL )
        {
            pprintf ( "La ID de mision ya existe, intente de nuevo\n" );
            scanf ( "%d", &mission.ID );
            flag = confirmMissionID(mission.ID);
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionStarshipID()              //Se cambia la nave que se va a utilizar en la misión
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

void changeMissionDetails()                 //Cambia la breve descripción de la misión
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

void changeMissionShipment()                //Cambia el cargamento de la misión,
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

void changeMissionDestination()             //Cambia el destino de la misión
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

void changeMissionCrewmanList()             //Cambia el listado de tripulantes que se van a enviar a la misión
{
    stMission mission;
    int pos = selectMission(), option = 0, i = 0, flag = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Seleccione los tripulantes por sus IDs:\n" );
        for ( i = 0; i < dimInt && option == 1; i++ )
        {
            scanf ( "%d", &mission.crewmen[i] );
            flag = confirmAstronautID(mission.crewmen[i]);
            while ( flag != NULL )
            {
                pprintf ( "El astronauta no existe, intente de nuevo.\n" );
                scanf ( "%d", &mission.crewmen[i] );
                flag = confirmAstronautID(mission.crewmen[i]);
            }
            pprintf ( "Agregar otro astronauta? 1-Si Otro-No\n" );
            scanf ( "%d", &option );
        }
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionStatus()                  //Cambia el estado de la misión, 1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
{
    stMission mission;
    int pos = selectMission(), option = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        switch ( mission.status ) {
        case 1:
            pprintf ( "Estado de la mision: 'Lista'\n" );
            pprintf ( "Iniciar mision? Ingrese 1 | Cancelar la mision? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 ) {
                mission.status = 2;
                pprintf ( "La mision fue cambiada a 'en vuelo'\n" );
            }
            if ( option == 2 ) {
                mission.status = 4;
                pprintf ( "La mision fue cambiada a 'Cancelada'\n" );
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            fclose(file);
            break;

        case 2:
            pprintf ( "Estado de la mision: 'En vuelo'\n" );
            pprintf ( "La mision esta retornada? Ingrese 1 | La mision ha fallado? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 ) {
                mission.status = 3;
                pprintf ( "La mision fue cambiada a 'Retornada'\n" );
            }
            if ( option == 2 ) {
                mission.status = 5;
                pprintf ( "La mision fue cambiada a 'Fallida'\n" );
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            fclose(file);
            break;

        default:
            pprintf ( "La mision que se ha seleccionado no tiene el estado de 'Lista' o 'En vuelo' por lo tanto no puede ser modificada\n" );
            break;
        }
    }
}

int selectMission()     //fedep: probar esto porfa//Selecciona una misión y retorna la posición de la misma
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
        while ( feof(file) || pos < 0 )     //en teoría esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
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

void showMissions()    //muestra todas las misiones registradas
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

int getLastMissionID()  //Toma la última ID de misión registrada y la retorna
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

bool firstSpaceShip()
{
    bool firstOne = false;

    FILE *archive;
    archive = fopen(Fstarships, "rb");

    if (archive != NULL)
    {
        stSpaceship starship;
        if (fread(&starship, sizeof(stSpaceship), 1, archive) == 1)
        {
            firstOne = true;
        }

        fclose(archive);
    }

    return firstOne;
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
            userData.consoleColor = 1;
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
void textMainMenu()
{





}
