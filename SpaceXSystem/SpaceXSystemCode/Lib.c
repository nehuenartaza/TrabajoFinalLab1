#include "Lib.h"
#include <unistd.h>

//aca van las funciones

//Astronautas
void registerAstronaut()        //Registra astronauta
{
    system("cls");
    stAstronaut user;
    int option = 1;
    while ( option ==1 && option != 0 )
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
        system("cls");
        pprintf("Astronauta registrado con exito!\n");
        pprintf ( "1- Registrar otro astronauta\n" );
        pprintf ( "0- salir:\n" );
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
bool confirmAstronautID(int ID)     //cambiado, retornaba una flag, ahora retorna un boleano
{
    bool flag = false;
    stAstronaut user;
    FILE* file = fopen(Fastronauts, "rb");
    if (file != NULL)
    {
        while (!flag && fread(&user, sizeof(stAstronaut), 1, file) == 1)
        {
            if (ID == user.ID)
            {
                flag = true;
            }
        }
        fclose(file);
    }
    return flag;
}
void changeAstronautNickname()//cambia el apodo del Astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Apodo\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);

        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);

        printf("Apodo actual: %s\n", user.nickname);
        printf("Nuevo apodo: ");
        fflush(stdin);
        gets(user.nickname);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);

        fclose(file);
    }
}
void changeAstronautAge() //Cambiar la edad de un astronauta
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Edad\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);

        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);

        printf("Edad actual: %d\n", user.age);
        printf("Nueva edad: ");
        scanf("%d", &user.age);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);

        fclose(file);
    }
}
void changeAstronautSpeciality() //Cambiar la especialidad
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Especialidad\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);

        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);

        printf("Especialidad actual: %s\n", user.speciality);
        printf("Nueva especialidad: ");
        fflush(stdin);
        gets(user.speciality);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);

        fclose(file);
    }
}
void changeAstronautFlightTime()        //cambiar el tiempo de vuelo
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Horas de Vuelo\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);

        printf("Horas de vuelo actual: %d\n", user.flight_hours);

        do
        {
            printf("Nueva cantidad de horas de vuelo (mayor a 0): ");
            scanf("%d", &user.flight_hours);
        }
        while (user.flight_hours < 0);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}
void changeAstronautHoursSpaceStation()     //cambia el tiempo en la estacion espacial
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Horas en la Estación Espacial\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);
        printf("Horas en la estación espacial actual: %d\n", user.hours_at_spaceStation);

        do
        {
            printf("Nueva cantidad de horas en la estación espacial (mayor a 0): ");
            scanf("%d", &user.hours_at_spaceStation);
        }
        while (user.hours_at_spaceStation < 0);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}
void changeAstronautAmmountMissions()
{
    stAstronaut user;
    int pos = selectAstronaut();
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        system("cls");
        printf("Modificar Cantidad de Misiones\n");

        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf("ID: <%i>\n", user.ID);
        printf("Astronauta: %s %s\n", user.name, user.last_name);
        printf("Cantidad de misiones actual: %d\n", user.missions);

        do
        {
            printf("Nueva cantidad de misiones realizadas (mayor a 0): ");
            scanf("%d", &user.missions);
        }
        while (user.missions < 0);

        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}
void changeAstronautStatus()
{
    stAstronaut user;
    int pos = selectAstronaut(), option = 0;
    FILE* file = fopen(Fastronauts, "r+b");
    if (file != NULL)
    {
        fseek(file, sizeof(stAstronaut) * (pos - 1), SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        if (user.status == 1)
        {
            system("cls");
            printf("Cambiar estado a retirado?\n");
            printf("1 - Sí\n");
            printf("Opción: ");
            scanf("%d", &option);
            if (option == 1)
            {
                user.status = 2;
                printf("El astronauta ha sido dado de baja correctamente.\n");
            }
        }
        else
        {
            system("cls");
            printf("El astronauta ya se encuentra retirado.\n");
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
    pprintf ( "Seleccione un astronauta por ID.\n" );
    scanf ( "%d", &pos );
    while ( pos < 1 || pos > maxAstronauts )
    {
        printf ( "No se permite un valor menor o igual a 0 o mayor a %d, pruebe de nuevo\n", maxAstronauts );
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
        pprintf("Muestra del astronauta de todos los astronautas cargados\n");
        while ( !feof(file))
        {
            fread(&aux, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && aux.status == 1)
            {


                printf("-----------------------------------------\n");
                printf ( "> ID:%d\n> Nombre: %s\n> Apellido:%s\n> Apodo: '%s'\n> Edad:%d\n> Horas de vuelo:%d\n> Horas en la estacion:%d\n", aux.ID, aux.name, aux.last_name, aux.nickname, aux.age, aux.flight_hours, aux.hours_at_spaceStation );
                printf ( "> Especialidad: %s\n> Nacionalidad: %s\n> Misiones Hechas: %d\n", aux.speciality, aux.nationality, aux.missions );
                pprintf ( "> Estado: activo\n" );
                printf("-----------------------------------------\n");
                system("pause");
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
}
void showAstronautByID()
{
    stAstronaut user;
    int ID = 0;
    bool exist = false;
    FILE* archive = fopen(Fastronauts, "rb");
    if (archive != NULL)
    {
        system("cls");
        printf("Ingrese la ID a buscar: ");
        scanf("%d", &ID);
        while (fread(&user, sizeof(stAstronaut), 1, archive) == 1)
        {
            if (ID == user.ID)
            {
                system("cls");
                pprintf("Muestra del astronauta ID <");
                printf("%i", ID);
                pprintf(">\n");
                pprintf("-----------------------------------------------------\n");
                printf("Nombre: %s\n", user.name);
                printf("Apodo: %s\n", user.nickname);
                printf("Apellido: %s\n", user.last_name);
                printf("Edad: %d\n", user.age);
                printf("Nacionalidad: %s\n", user.nationality);
                printf("Especialidad: %s\n", user.speciality);
                printf("Horas de vuelo: %d\n", user.flight_hours);
                printf("Horas en la estacion: %d\n", user.hours_at_spaceStation);
                printf("Misiones hechas: %d\n", user.missions);
                printf("Estado: %s\n", (user.status == 1) ? "activo" : "retirado");
                exist = true;
                pprintf("-----------------------------------------------------\n");
                system("pause");
                break;

            }
        }
        fclose(archive);

        if (!exist)
        {
            printf("No se pudo encontrar al astronauta con la ID especificada.\n");
            system("pause");
        }
    }
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
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        fseek(file, 0, SEEK_END);
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
    if (firstSpaceShip())
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
    pprintf(">\n\nPara modificar sus datos, dirijase al modulo correspondiente del programa\n");
    system("pause");
}

void selectSpaceshipType(stSpaceship *type)
{
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

void changeSpaceshipStatus()                // Cambia el estado de la nave
{
    stSpaceship spaceship;
    int ID = 0;
    int newStatus = 0;
    FILE* archive;
    archive = fopen(Fstarships, "r+b");
    if (archive != NULL)
    {
        system("cls");
        ID = selectSpaceship();
        system("cls");
        if (!isOnMission(ID))
        {
            fseek(archive, sizeof(stSpaceship) * (ID - 1), SEEK_SET);
            fread(&spaceship, sizeof(stSpaceship), 1, archive);
            pprintf("Modificar estado de nave\n");
            printf("ID: %d\n", spaceship.ID);
            printf("Tipo de nave: %s\n", spaceship.type);
            printSpaceshipStatus(spaceship.status);
            newStatus = changeSpaceshipStatusOptions();

            spaceship.status = newStatus;

            fseek(archive, sizeof(stSpaceship) * (ID - 1), SEEK_SET);
            fwrite(&spaceship, sizeof(stSpaceship), 1, archive);
        }
        else
        {
            system("cls");
            pprintf("Esa nave está en misión actualmente\n");
            system("pause");
        }
        fclose(archive);
    }
}



bool isOnMission(int ID)
{

    bool is = false;
    FILE* archive;
    stMission miss;
    archive = fopen(Fmissions, "rb");
    if(archive != NULL)
    {
        while(fread(&miss, sizeof(stMission),1,archive)==1)
        {
            if(miss.ship_ID == ID)
            {
                is = true;
                break;
            }
        }
        fclose(archive);
    }
    return is;
}

int changeSpaceshipStatusOptions()                      //Retorna el estado de la nave elegida, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    int option = 0;
    do
    {

        pprintf("\nIngrese estado de la nave:\n");
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
            system("cls");
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

        while(fread(&spaceship, sizeof(stSpaceship), 1, archive) ==1)
        {
            printSpaceshipData(spaceship);
        }
        fclose(archive);
    }
    else
    {
        system("cls");
        pprintf("No hay naves cargadas en el sistema.");
        system("pause");
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

void showFlightsAmount(int ID)                    //Muestra la cantidad de vuelos de una nave
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

//arreglado
void changeSpaceshipFlightsAmount() //cambia la cantidad de vuelos de la nave
{
    stSpaceship spaceship;
    int ID = 0;
    FILE* archive;
    archive = fopen(Fstarships, "r+b");
    if (archive != NULL)
    {
        int newAmount = 0;

        system("cls");
        ID = selectSpaceship();
        system("cls");
        fseek(archive, sizeof(stSpaceship) * (ID - 1), SEEK_SET);
        fread(&spaceship, sizeof(stSpaceship), 1, archive);

        pprintf("Modificar Cantidad de Vuelos\n");
        printf("ID: %d\n", spaceship.ID);
        printf("Tipo de nave: %s\n", spaceship.type);
        printf("Cantidad actual: %d\n", spaceship.number_of_flights);
        printf("Ingrese la nueva cantidad de vuelos: ");
        scanf("%d", &newAmount);


        spaceship.number_of_flights += newAmount;

        fseek(archive, sizeof(stSpaceship) * (ID - 1), SEEK_SET);
        fwrite(&spaceship, sizeof(stSpaceship), 1, archive);

        fclose(archive);
    }
    changeSpaceshipFlightTime();
}


int selectSpaceship()   //selecciona una nave y retorna la posicion de la misma
{
    stSpaceship spaceship;
    FILE* archive;
    archive = fopen(Fstarships, "rb");
    int ID = 0;

    if (archive != NULL)
    {
        do
        {
            showAllSpaceships();
            printf("\nSeleccione una nave por su ID:\n");
            scanf("%i", &ID);
            if (!spaceshipExistByID(ID))
            {
                system("cls");
                printf("Ingrese un valor válido para la ID.\n");
                system("pause");
            }
        }
        while (!spaceshipExistByID(ID));

        fclose(archive);
    }

    return ID;
}
//arreglado
int getTotalSpaceships()        //Retorna la cantidad total de registros de naves
{
    int totalRegisters = 0;
    FILE *file = fopen(Fstarships, "rb");
    if ( file != NULL )
    {
        fseek(file, sizeof(stSpaceship) * 0, SEEK_END);
        totalRegisters = ftell(file) / sizeof(stSpaceship);
        fclose(file);
    }
    return totalRegisters;
}

void changeSpaceshipFlightTime()
{
    stSpaceship spaceship;
    FILE* archive = fopen(Fstarships, "r+b");
    if (archive != NULL)
    {
        int pos = selectSpaceship();
        int newTime = 0;
        do
        {
            fread(&spaceship, sizeof(stSpaceship), 1, archive);
            system("cls");
            pprintf("Modificar Cantidad de horas\n");
            printf("ID: %d\n", spaceship.ID);
            printf("Cantidad actual: %d\n", spaceship.flight_hours);
            pprintf("Ingrese la nueva cantidad de horas de vuelo de la nave: ");
            scanf("%d", &newTime);
            if (newTime < 0)
            {
                system("cls");
                pprintf("Ingrese un valor válido para las horas de vuelo.\n");
                system("pause");
            }
        }
        while (newTime < 0);

        fseek(archive, sizeof(stSpaceship) * (pos - 1), SEEK_SET);
        fread(&spaceship, sizeof(stSpaceship), 1, archive);
        spaceship.flight_hours += newTime;
        fseek(archive, sizeof(stSpaceship) * (pos - 1), SEEK_SET);
        fwrite(&spaceship, sizeof(stSpaceship), 1, archive);
        fclose(archive);
    }
}


bool firstSpaceShip()                                               //verifica si hay al menos una nave registrada
{
    bool firstOne = false;

    FILE *archive;
    archive = fopen(Fstarships, "rb");

    if (archive != NULL)
    {
        stSpaceship spaceship;
        if (fread(&spaceship, sizeof(stSpaceship), 1, archive) == 0)
        {
            firstOne = true;
        }

        fclose(archive);
    }

    return firstOne;
}

void autoChangeSpaceshipStatus(int IDsearch, int flag, int option)    //cambia el estado de una nave automáticamente cuando una mision es retornada, falla o se cancela, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
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
                if ( flag == 2 && option == 1 )     //si la mision retornó
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


//Misiones

bool isValidSpaceshipID(int shipID, stSpaceship* spaceships, int totalSpaceshipsList)
{
    bool valid = false;
    for (int i = 0; i < totalSpaceshipsList; i++)
    {
        if (spaceships[i].ID == shipID)
        {
        valid = true;
        }
    }
    return valid;
}
bool isValidDestination(int destination)
{
    return (destination >= 1 && destination <= 3);
}
bool isValidShipment(int shipment)
{
    return (shipment >= 1 && shipment <= 2);
}
bool isAstronautInMission(int astronautID, stMission* mission, int crewmanAmount)
{
    for (int i = 0; i < crewmanAmount; i++)
    {
        if (mission->crewmen[i] == astronautID)
        {
            return true;
        }
    }
    return false;
}
void registerMission()
{
    stSpaceship spaceships[300];
    stAstronaut astronauts[300];
    int totalSpaceshipsList = makeListOfSpaceshipsForMission(spaceships);
    int totalAstronautsList = makeListOfAstronautsForMission(astronauts);

    if (totalAstronautsList != 0 && totalSpaceshipsList != 0)
    {
        stMission mission;
        int crewmanAmount = 0;
        int lastID = 0;
        int option = 1;

        for (int aux = 0; aux < totalSpaceshipsList; aux++)
        {
            printSpaceshipData(spaceships[aux]);
        }

        do
        {
            pprintf("ID de la nave a enviar a la mision:\n");
            scanf("%d", &mission.ship_ID);

            if (!isValidSpaceshipID(mission.ship_ID, spaceships, totalSpaceshipsList))
            {
                pprintf("ID invalido, intente nuevamente.\n");
                system("pause");
                system("cls");
            }
        }
        while (!isValidSpaceshipID(mission.ship_ID, spaceships, totalSpaceshipsList));

        do
        {
            pprintf("Destino de la mision:\n1- EEI\n2- Orbita Terrestre\n3- Luna\n");
            scanf("%d", &mission.destination);
            system("cls");

            if (!isValidDestination(mission.destination))
            {
                system("cls");
                pprintf("El valor ingresado no es valido, intente de nuevo.\n");
                system("pause");
                system("cls");
            }
        }
        while (!isValidDestination(mission.destination));

        do
        {
            pprintf("Tipo de cargamento de la mision:\n1- Satelite\n2- Insumos para la EE\n");
            scanf("%d", &mission.shipment);
            system("cls");

            if (!isValidShipment(mission.shipment))
            {
               system("cls");
                pprintf("El valor ingresado no es valido, intente de nuevo.\n");
                system("pause");
                system("cls");
            }
        }
        while (!isValidShipment(mission.shipment));

        system("cls");

        while (option == 1)
        {
            int flag = 0;
            int auxOption = 1;

            do
            {
                showAstronauts();
                pprintf("Seleccione los tripulantes por sus IDs:\n");
                scanf("%d", &lastID);

                if (isAstronautInMission(lastID, &mission, crewmanAmount))
                {
                    system("cls");
                    pprintf("Este astronauta ya participa de la mision.\n");
                    pprintf("Ingrese una ID valida.\n");
                    system("pause");
                    system("cls");
                }

                flag = confirmAstronautID(lastID);
                if (!flag)
                {
                    pprintf("El astronauta no existe, intente de nuevo. Para hacerlo, ingrese 1, de lo contrario, elija otro valor.\n");
                    scanf("%d", &auxOption);
                }
            }
            while (isAstronautInMission(lastID, &mission, crewmanAmount) || !flag || auxOption != 1);

            mission.crewmen[crewmanAmount] = lastID;
            crewmanAmount++;
            system("cls");
            pprintf("Agregar otro astronauta?\n1-Si\n2-No\n");
            scanf("%d", &option);
        }
    system("cls");
        pprintf("Agregue una breve descripcion de la mision: (");
        printf("%d",dimChar);
        pprintf("caracteres maximos)\n");
        fflush(stdin);
        gets(mission.mission_details);

        if (firstMission())
        {
            mission.ID = 1;

        }
        else
        {
            mission.ID = getLastMissionID() + 1;

        }

        printf("ID otorgada a la mision: %d\n", mission.ID);
        mission.status = 1; // registra automaticamente en 'mision lista'
        saveMission(mission);
        system("pause");
        system("cls");
    }
    else
    {
        system("cls");
        pprintf("No hay suficientes naves o astronautas disponibles para crear una mision.\n");
        system("pause");
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

void changeMissionStarshipID()              //Se cambia la nave que se va a utilizar en la misión
{
    stMission mission;
    stSpaceship spaceships[300];
    int lastID = 0;
    int totalSpaceships = makeListOfSpaceshipsForMission(spaceships);
    bool flag = false;      //Confirma si la ID de la nave existe o no en el arreglo
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL && totalSpaceships != 0 )
    {
        do {
            for ( int i = 0; i < totalSpaceships; i++) {
                printSpaceshipData(spaceships[i]);
            }
                pprintf ( "Nueva nave para enviar a la mision (ingresar la ID): \n" );
                scanf ( "%d", &lastID );
                for ( int i = 0; i < totalSpaceships; i++ ) {
                    if ( spaceships[i].ID == lastID ) {
                        mission.ship_ID = lastID;
                        flag = true;
                        break;
                    }
                }
            if ( flag != 1 ) {
                pprintf ( "ID de nave no existente o nave no lista para su uso, intente de nuevo.\n" );
                system("pause");
            }
        } while ( flag != true );
        stMission aux;
        fseek( file, 0, SEEK_SET);

        while ( !feof(file) && flag == true ) {
            fread(&aux, sizeof(stMission), 1, file);
            if ( aux.ship_ID == mission.ship_ID ) {
                fseek(file, sizeof(stMission) * -1, SEEK_CUR);
                fwrite(&mission, sizeof(stMission), 1, file);
            }
        }
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
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevos detalles (max 50 caracteres): \n" );
        fflush(stdin);
        gets ( mission.mission_details );
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void changeMissionShipment()                //Cambia el cargamento de la misión
{
    stMission mission;
    int pos = selectMission();
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevo cargamento: 1- Satelite, 2- Insumos para la EE\n" );
        scanf ( "%d", &mission.shipment );
        while ( mission.shipment < 1 || mission.shipment > 2 )
        {
            pprintf ( "Cargamento no existente, pruebe de nuevo. \n" );
            scanf ( "%d", &mission.shipment );
        }
        pprintf ( "Cargamento modificado con exito\n");
        system("pause");
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
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
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
    int lastID = 0;
    int pos = selectMission(), option = 1, i = 0, flag = 0, auxOption = 1;
    FILE * file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        showAstronauts();
        pprintf ( "Seleccione los tripulantes por sus IDs:\n" );
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
                    pprintf ( "El astronauta no existe, intente de nuevo, para hacerlo ingrese 1, de lo contrario elija otro valor.\n" );
                    scanf ( "%d", &auxOption);
                }
            }
            while(inThere(lastID,mission.crewmen,i) || flag != 1 || auxOption != 1);

            mission.crewmen[i] = lastID;
            pprintf ( "Agregar otro astronauta? 1-Si Otro-No\n" );
            scanf ( "%d", &option );
        }
        if ( i > 1 && auxOption != 1) {    //En caso de que el for haya terminado por auxOption != 1, aunque no se haya ingresado otro astronauta por x motivo igualmente se estaría guardando en el arreglo, este if borra ese dato basura
            i--;
        }
        mission.crewman_amount = i;       //cantidad total de tripulantes
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);

    }
}

void changeMissionStatus()                  //Cambia el estado de la misión, 1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
{
    stMission mission;
    int pos = selectMission(), option = 0, flag = 0;    //Indica en qué caso del swtich entró
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * (pos -1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        switch ( mission.status )
        {
        case 1:                                                                 //Caso de si la mision está lista
            flag = 1;
            pprintf ( "Estado de la mision: 'Lista'\n" );
            pprintf ( "Iniciar mision? Ingrese 1 | Cancelar la mision? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 )
            {
                mission.status = 2;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'en vuelo'\n" );
                system("pause");
            }
            if ( option == 2 )
            {
                mission.status = 4;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Cancelada'\n" );
                system("pause");
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            break;

        case 2:                                                                 //Caso de si la mision está en vuelo
            flag = 2;
            pprintf ( "Estado de la mision: 'En vuelo'\n" );
            pprintf ( "La mision esta retornada? Ingrese 1 | La mision ha fallado? Ingrese 2\n" );
            scanf ( "%d", &option );
            if ( option == 1 )
            {
                mission.status = 3;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Retornada'\n" );
                system("pause");
            }
            if ( option == 2 )
            {
                mission.status = 5;
                autoChangeSpaceshipStatus(mission.ship_ID, flag, option);
                pprintf ( "La mision fue cambiada a 'Fallida'\n" );
                system("pause");
            }
            fseek(file, sizeof(stMission) * -1, SEEK_CUR);
            fwrite(&mission, sizeof(stMission), 1, file);
            break;

        default:
            pprintf ( "La mision que se ha seleccionado no tiene el estado de 'Lista' o 'En vuelo' por lo tanto no puede ser modificada\n" );
            system("pause");
            break;
        }
        fclose(file);
    }
}

int getTotalMissions()        //Retorna la cantidad total de registros de Mishions
{
    int totalRegisters = 0;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * 0, SEEK_END);
        totalRegisters = ftell(file) / sizeof(stMission);
        fclose(file);
    }
    return totalRegisters;
}

int selectMission()                         //Selecciona una misión y retorna la posición de la misma
{
    stMission mission;
    int pos = 0;
    showMissions();
    pprintf ( "Seleccione una mision por ID: \n" );
    scanf ( "%d", &pos );
    while ( pos < 1 )
    {
        pprintf ( "No se permite un valor menor a 1, pruebe de nuevo.\n" );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        while ( feof(file) || pos < 1 )
        {
            system("cls");
            pprintf ( "Registro no existente o valor menor a 1 no permitido, intente de nuevo.\n" );
            showMissions();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stMission) * (pos-1), SEEK_SET);
            fread(&mission, sizeof(stMission), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void showMissions() //muestra todas las misiones registradas
{
    stMission mission;

    FILE* file = fopen(Fmissions, "rb");
    if (file != NULL)
    {
        while (!feof(file))
        {
            fread(&mission, sizeof(stMission), 1, file);

            if (!feof(file))
            {
                printf("ID de mision: %d\nID de nave: %d\n", mission.ID, mission.ship_ID);
                if (mission.shipment == 1)
                {
                    pprintf("Cargamento: satelite\n");
                }
                else
                {
                    pprintf("Cargamento: insumos para la EE\n");
                }
                if (mission.destination == 1)
                {
                    pprintf("Destino: EEI\n");
                }
                else if (mission.destination == 2)
                {
                    pprintf("Destino: Orbita Terrestre\n");
                }
                else
                {
                    pprintf("Destino: Luna\n");
                }
                printf("Resumen de Mision: %s\n", mission.mission_details);
                for (int j = 0; j < mission.crewman_amount; j++)
                {
                    printf("ID del Tripulante %d: %d\n", j + 1, mission.crewmen[j]);
                }
                if (mission.status == 1)
                {
                    pprintf("Estado de mision: Lista\n");
                }
                else if (mission.status == 2)
                {
                    pprintf("Estado de mision: En vuelo\n");
                }
                else if (mission.status == 3)
                {
                    pprintf("Estado de mision: Retornada\n");
                }
                else if (mission.status == 4)
                {
                    pprintf("Estado de mision: Cancelada\n");
                }
                else
                {
                    pprintf("Estado de mision: Fallida\n");
                }
                system("pause");
            }
        }
        fclose(file);
    }
}


void showMissionsByID()                         //muestra la mision Por ID
{
    stMission mission;
    int ID = 0, option = 1;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL )
    {
        do {
            pprintf("Ingrese el ID a buscar\n>:");
            fflush(stdin);
            scanf("%d", &ID);
            if(ID <= 0 || ID > getTotalMissions())
            {
                system("cls");
                pprintf("Esa Mision no existe / Valor invalido\n");
                system("pause");
                pprintf ( "Si quiere volver a intentar, ingrese 1\n");
                scanf ( "%d", &option);
            }
        } while(ID < 1 || ID > getTotalMissions() && option == 1 );

        fseek(file, sizeof(stMission) * (ID-1), SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
                if ( mission.ID == ID ) {
                    fseek(file, sizeof(stMission) * -1, SEEK_CUR);
                    fread(&mission, sizeof(stMission), 1, file);
                    printf ( "ID de mision: %d\nID de nave: %d\n", mission.ID, mission.ship_ID );
                    if ( mission.shipment == 1 )
                    {
                        pprintf ( "Cargamento: satelite\n" );
                    }
                    else
                    {
                        pprintf ( "Cargamento: insumos para la EE\n" );
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
                    for (int j = 0; j < mission.crewman_amount; j++ )
                    {
                        printf ( "ID del Tripulante %d: %d\n", j+1, mission.crewmen[j] );
                    }
                    if ( mission.status == 1 )
                    {
                        pprintf ( "Estado de mision: Lista\n" );
                    }
                    else if ( mission.status == 2 )
                    {
                        pprintf ( "Estado de mision: En vuelo\n" );
                    }
                    else if ( mission.status == 3 )
                    {
                        pprintf ( "Estado de mision: Retornada\n" );
                    }
                    else if ( mission.status == 4 )
                    {
                        pprintf ( "Estado de mision: Cancelada\n" );
                    }
                    else
                    {
                        pprintf ( "Estado de mision: Fallida\n" );
                    }
                    system("pause");
            }
        fclose(file);
    } else {
            pprintf ( "No hay ninguna mision registrada\n");
            system("pause");
        }
}

int getLastMissionID()                       //Toma la última ID de misión registrada y la retorna
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

int makeListOfSpaceshipsForMission(stSpaceship list[])      //todas las naves que esten aptas para una mision se guardan en un arreglo y retorna sus validós
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
    system("cls");
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

void toggleProceduralText()
{

    system("cls");
    stUserData userData;

    FILE * archive;
    archive = fopen(FuserData, "r+b");
    if(archive != NULL)
    {
        fread(&userData, sizeof(userData), 1, archive);
        fseek(archive, 0, SEEK_SET);
        if(userData.proceduralText)
        {
            pprintf("Procedural Text desactivado\n");
            userData.proceduralText = false;

        }
        else
        {
            pprintf("Procedural Text Activado\n");
            userData.proceduralText = true;

        }
        fwrite(&userData, sizeof(userData),1,archive);


        fclose(archive);
    }

    system("pause");
}


//Menus
void mainMenu()
{
    int option= 0;
    do
    {

        system("cls");
        printf("      ########## ########### ########    ##   ######       ###       ########### ########### ######## ########### \n");
        printf("     #+#            #+#     +#+   +#+   +#+  +#+  +#+      +#+           #+#     #+#       #+#    #+#    #+#      \n");
        printf("    +#+            +#+     +#+    +#+  +#+  +#+    +#+     +#+           +#+     +#+       +#+           +#+       \n");
        printf("   :#::+::#       +#+     +#+     +#+ +#+  +#+      +#+    +#+           +#+     +#++:++#  +#++:++#++    +#+        \n");
        printf("  +#+            +#+     +#+      #+##+#  +#+########+#+   +#+           +#+     +#+              +#+    +#+         \n");
        printf(" #+#            #+#     #+#       #+#+#  +#+          +#+  #+#           #+#     #+#       #+#    #+#    #+#          \n");
        printf("###        ########### ###        ####  +#+            +#+ ##########    ###     ########## ########     ###           \n\n\n");

        pprintf("1- Sistema\n");
        pprintf("2- Opciones\n");
        pprintf("3- Info\n");
        pprintf("0- Salir\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);


        switch(option)
        {

        case 1:
            systemMenu();
            break;
        case 2:
            optionsMenu();
            break;
        case 3:
            infoMenu();
            break;
        default:
            break;
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option !=0);
}
void systemMenu()
{
    int option = 0;
    do
    {
        system("cls");
        pprintf("1- Astronautas\n");
        pprintf("2- Misiones\n");
        pprintf("3- Naves\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            astronautMenu();
            break;
        case 2:
            missionMenu();
            break;
        case 3:
            spaceshipMenu();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}


//Menues Astronautas
void astronautMenu()
{
    int option = 0;


    do
    {
        system("cls");
        pprintf("1- Agregar astronauta\n");
        pprintf("2- Modificar astronauta\n");
        pprintf("3- Consulta astronauta\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            registerAstronaut();
            break;
        case 2:
            modifyAstronautMenu();
            break;
        case 3:
            consultAsMenu();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}
void modifyAstronautMenu()
{

    int option = 0;


    do
    {
        system("cls");
        pprintf("1- Cambiar Apodo\n");
        pprintf("2- Cambiar Edad\n");
        pprintf("3- Cambiar Especialidad\n");
        pprintf("4- Cambiar Estado\n");
        pprintf("5- Cambiar Horas de vuelo\n");
        pprintf("6- Cambiar Cantidad de misiones\n");
        pprintf("7- Cambiar Horas en la estacion espacial\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {


        case 1:
            changeAstronautNickname();
            break;
        case 2:
            changeAstronautAge();
            break;
        case 3:
            changeAstronautSpeciality();
            break;
        case 4:
            changeAstronautStatus();
            break;
        case 5:
            changeAstronautFlightTime();
            break;
        case 6:
            changeAstronautAmmountMissions();
            break;
        case 7:
            changeAstronautHoursSpaceStation();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}
void consultAsMenu()
{

    int option = 0;


    do
    {
        system("cls");
        pprintf("1- Ver Por ID\n");
        pprintf("2- Ver Todos los Astronautas\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            showAstronautByID();
            break;
        case 2:
            showAstronauts();
            break;
        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}


//Menues Spaceship
void spaceshipMenu()
{
    int option = 0;
    do
    {
        system("cls");
        pprintf("1- Agregar Nave\n");
        pprintf("2- Modificar Nave\n");
        pprintf("3- Consultar naves\n");

        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            registerSpaceship();
            break;
        case 2:
            modifySpMenu();
            break;
        case 3:
            consultSpMenu();
            break;


        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}
void consultSpMenu()
{
    int option = 0;
    do
    {
        system("cls");
        pprintf("1- Ver por ID\n");
        pprintf("2- Ver todas las Naves\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            showSpaceshipByID();

            break;
        case 2:
            showAllSpaceships();
            break;
        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}
void modifySpMenu()
{

    int option = 0;
    do
    {
        system("cls");

        pprintf("1- Modificar estado de la nave.\n");
        pprintf("2- Modificar horas de vuelo.\n");
        pprintf("3- Modificar cantidad de viajes.\n");
        pprintf("0- Volver.\n");

        pprintf(">: ");
        fflush(stdin);
        scanf("%i", &option);

        switch(option)
        {

        case 1:
            changeSpaceshipStatus();
            break;
        case 2:
            changeSpaceshipFlightTime();
            break;
        case 3:
            changeSpaceshipFlightsAmount();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}


//Menues Misiones
void missionMenu()
{
    int option = 0;


    do
    {
        system("cls");
        pprintf("1- Agregar mision\n");
        pprintf("2- Modificar mision\n");
        pprintf("3- Consulta mision\n");

        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            registerMission();
            break;
        case 2:
            modifyMissionMenu();
            break;
        case 3:
            consultMissionMenu();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);


}
void consultMissionMenu()
{

    int option = 0;
    do
    {
        system("cls");

        pprintf("1- Ver por ID.\n");
        pprintf("2- Ver todas las misiones.\n");
        pprintf("0- Volver.\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i", &option);

        switch(option)
        {

        case 1:
            showMissionsByID();
            break;
        case 2:
            showMissions();
            break;


        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}
void modifyMissionMenu()
{
    int option = 0;


    do
    {
        system("cls");
        pprintf("1- Modificar tripulantes\n"); //amongus
        pprintf("2- Modificar destino\n");
        pprintf("3- Modificar detalles\n");
        pprintf("4- Modificar cargamento\n");
        pprintf("5- Modificar nave asignada\n");
        pprintf("6- Modificar estado\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i",&option);
        switch(option)
        {

        case 1:
            changeMissionCrewmanList();
            break;
        case 2:
            changeMissionDestination();
            break;
        case 3:
            changeMissionDetails();
            break;
        case 4:
            changeMissionShipment();
            break;
        case 5:
            changeMissionStarshipID();
            break;
        case 6:
            changeMissionStatus();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}


//Menues Extra
void optionsMenu()
{

    int option = 0;
    do
    {
        system("cls");

        pprintf("1- Cambiar color de la consola.\n");
        pprintf("2- Desactivar / Activar Texto procedural.\n");
        pprintf("0- Volver\n");
        pprintf(">: ");
        fflush(stdin);
        scanf("%i", &option);

        switch(option)
        {

        case 1:
            changeColor();
            break;
        case 2:
            toggleProceduralText();
            break;

        default:
            if(option != 0)
            {
                system("cls");
                printf("Opcion invalida, ingrese un valor valido\n");
                system("pause");
            }
            break;
        }
    }
    while(option != 0);
}

void infoMenu()
{
    system("cls");
    printf(" _______          _            _                                        _               _______ _             _  \n");
    printf("(_______)        | |          (_)                                   _  (_)             (_______|_)           | | \n");
    printf("    _  ____ _____| |__  _____  _  ___     ____   ____ _____  ____ _| |_ _  ____ ___     _____   _ ____  _____| | \n");
    printf("   | |/ ___|____ |  _ \\(____ || |/ _ \\   |  _ \\ / ___|____ |/ ___|_   _) |/ ___) _ \\   |  ___) | |  _ \\(____ | | \n");
    printf("   | | |   / ___ | |_) ) ___ || | |_| |  | |_| | |   / ___ ( (___  | |_| ( (__| |_| |  | |     | | | | / ___ | | \n");
    printf("   |_|_|   \\_____|____/\\_____|| |\\___/   |  __/|_|   \\_____|\____)  \\__)_|\\____)____/   |_|     |_|_| |_\\_____|\_)\n");
    printf("                             (__/        |_|                                                                 \n");
    printf(" _______            _      _                ___      ______  _____  ______  ______                               \n");
    printf("(_______)          (_)    (_)              (___)    (_____ \\(_____)\\____ \\(_____ \\                              \n");
    printf(" _       ___  ____  _  ___ _  ___  ____       _       ____) )  __ _  ____) )_____) )                             \n");
    printf("| |     / _ \\|    \\| |/___) |/ _ \\|  _ \\     | |     / ____/ |/ /| |/ ____/(_____ (                              \n");
    printf("| |____| |_| | | | | |___ | | |_| | | | |   _| |_   | (____|   /_| | (_____ _____) )                             \n");
    printf(" \\______)___/|_|_|_|_(___/|_|\___/|_| |_|  (_____)   |_______)_____/|_______|______/                              \n");

    printf("\n\n\n");
    printf("\n\n\n");

    pprintf("                                 Aristegui Federico - Artaza Nehuen - Roldan Eloy\n                                  ");
    printf("\n\n\n");
    printf("\n\n\n");
    printf("\n\n\n");

    system("pause");
}
