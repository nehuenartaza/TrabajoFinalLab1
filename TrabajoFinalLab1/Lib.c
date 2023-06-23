#include "Lib.h"
#include <unistd.h>

//aca van las funciones

//Astronautas
void RegisterAstronaut()            //registra astronauta
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
        pprintf ( "Su edad:\n" );
        scanf ( "%d", &user.age );
        pprintf ( "Nacionalidad:\n" );
        fflush(stdin);
        gets ( user.nationality );
        pprintf ( "Especialidad:\n" );
        fflush(stdin);
        gets ( user.speciality );
        pprintf ( "Horas de vuelo acumuladas:\n" );
        scanf ( "%d", &user.hours_flight );
        pprintf ( "Cantidad de misiones en las que ha participado:\n" );
        scanf ( "%d", &user.missions );
        pprintf ( "Horas invertidas en la estacion espacial:\n" );
        scanf ( "%d", &user.hours_at_spaceStation );
        user.status = 1; //lo registra automaticamente en 'activo'
        user.ID = GetLastAstronautID() + 1;
        printf ( "ID otorgada: %d", user.ID );
        SaveAstronaut(user);
        pprintf ( "para registrar otro astronauta ingrese 1:\n" );
        scanf ( "%d", &option );
    }
}

void SaveAstronaut(stAstronaut user)    //guarda astronauta en archivo
{
    FILE *file = fopen(Fastronauts, "ab");
    if ( file != NULL )
    {
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

int ConfirmAstronautID(int ID)  //usada para encontrar ID repetida y verificar si existe el tripulante, retorna NULL si la ID enviada se encontró en un registro
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

void ChangeAstronautName()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautLastName()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautNickname()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautAge()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautID()
{
    stAstronaut user;
    int pos = SelectAstronaut(), flag = 0;
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva ID: \n" );
        scanf ( "%d", &user.ID );
        flag = ConfirmAstronautID(user.ID);
        while ( flag == NULL )
        {
            pprintf ( "ID en uso, intente de nuevo\n" );
            scanf ( "%d", &user.ID );
            flag = ConfirmAstronautID(user.ID);
        }
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void ChangeAstronautNationality()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautSpeciality()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautFlightTime()
{
    stAstronaut user;
    int pos = SelectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva cantidad de hrs de vuelo: \n" );
        scanf ( "%d", &user.hours_flight );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void ChangeAstronautHoursSpaceStation()
{
    stAstronaut user;
    int pos = SelectAstronaut();
    FILE *file = fopen (Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        pprintf ( "Nueva cantidad de hrs en la estacion espacial: \n" );
        scanf ( &user.hours_at_spaceStation );
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

void ChangeAstronautAmmountMissions()
{
    stAstronaut user;
    int pos = SelectAstronaut();
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

void ChangeAstronautStatus()
{
    stAstronaut user;
    int pos = SelectAstronaut(), option = 0;
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
        }
        if ( option == 1 && user.status == 2 )
        {
            user.status = 1;
        }
        fseek(file, sizeof(stAstronaut) * -1, SEEK_CUR);
        fwrite(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
}

int SelectAstronaut()       //fedep: probar esto porfa
{
    stAstronaut user;
    int pos = 0;
    ShowAstronauts();
    pprintf ( "Seleccione un astronauta\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 )
    {
        pprintf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        while ( feof(file) || pos < 0 )     //en teoría esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
        {
            system("cls");
            pprintf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
            ShowAstronauts();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
            fread(&user, sizeof(stAstronaut), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void ShowAstronauts()      //muestra la totalidad del contenido del archivo de astronautas
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
                printf ( "|%d| %s '%s' %s, Edad:%d, ID:%d, horas de vuelo:%d, horas en la estacion:%d\n", i, aux.name, aux.nickname, aux.last_name, aux.age, aux.ID, aux.hours_flight, aux.hours_at_spaceStation );
                printf ( "Especialidad: %s, nacionalidad: %s, misiones hechas: %d ", aux.speciality, aux.nationality, aux.missions );
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

int AstronautAvailability(int ID)      //indica la disponibilidad del astronauta, 1-activo, 2-retirado, NULL-no existe
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

int GetLastAstronautID()
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


//Naves
void saveStarship(stStarship starship)          //Guarda en la ultima posicion del archivo la nave recibida por parametro
{
    FILE * archive;
    archive = fopen(Fstarships, "ab");
    if(archive != NULL)
    {
        fwrite(&starship, sizeof(stStarship), 1, archive);
        fclose(archive);
    }
}

void registerStarship()                         //Carga de datos y en archivo una nueva nave. Con parametros en automatico
{
    stStarship starship;
    if (!firstSpaceShip())
    {
        starship.ID = 1;
    }
    else
    {
        starship.ID = getLastStarshipID() + 1;
    }
    changeStarshipType(&starship.type);
    starship.hours_flight = NULL;
    starship.ammount_flights = NULL;
    starship.status = 1; // Lista para su uso
    saveStarship(starship);

    printSpaceshipData(starship);

    system("cls");
    pprintf("Nave cargada exitosamente, ID <");
    printf("%i", starship.ID);
    pprintf(">\nPara modificar sus datos, seleccione el modulo correspondiente\n");
}

int getLastStarshipID()                         //Obtiene la ultima ID del registro
{
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    stStarship starship;
    if(archive != NULL)
    {
        fseek(archive, sizeof(stStarship) * -1, SEEK_END);
        fread(&starship, sizeof(stStarship), 1, archive);
        fclose(archive);
    }
    return starship.ID;
}

void changeStarshipType(char starshipName[])    //Cambia el tipo de nave
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
        strcpy((starshipName), "Starship");
        break;

    case 2:
        strcpy((starshipName), "Falcon 9");
        break;

    case 3:
        strcpy((starshipName), "Falcon Heavy");
        break;
    }
}

int changeStarshipStatus()                      //Retorna el estado de la nave elegida, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
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
        if (option < 1 && option > Max)
        {
            system("cls");
            pprintf("Valor invalido, intente de nuevo.");
            system("pause");
        }
    }
    while(option < 1 && option > Max);

    return option;
}

void searchSpaceshipByID()                      //Verifica si la nave existe la busca y permite modificar sus datos o visualizarla
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
        if(starshipExistByID(ID))
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
    stStarship starship;
    if(starshipExistByID(ID))
    {
        archive = fopen(Fstarships,"rb");
        if(archive != NULL)
        {
            fseek(archive, sizeof(stStarship) * (ID-1), SEEK_SET);
            fread(&starship, sizeof(stStarship),1, archive);
            printSpaceshipData(starship);
            fclose(archive);
        }
    }

}

bool starshipExistByID(int ID)                  //Retorna verdadero si la nave existe en el archivo en base al ID Recibido
{
    bool exist = false;
    stStarship aux;
    FILE* archive;
    archive = fopen(Fstarships, "rb");
    if (archive != NULL)
    {
        while (fread(&aux, sizeof(stStarship), 1, archive) == 1)
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

void printSpaceshipData(stStarship starship)    //Imprime por pantalla los datos de la nave
{
    pprintf("----------------------------------------\n");
    printf("Nave ID: %i\n", starship.ID);
    printf("Tipo de nave: %s\n", starship.type);
    printf("Vuelos Realizados: %i\n", starship.ammount_flights);
    printf("Horas de vuelo: %i\n", starship.hours_flight);
    printStarshipStatus(starship.status);
    pprintf("----------------------------------------\n");
    system("pause");
}

void printStarshipStatus(int starshipStatus)    //1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
{
    pprintf("Estado de la nave: ");
    switch(starshipStatus){
    case 1: pprintf("Lista para su uso\n"); break;
    case 2: pprintf("En Mision\n"); break;
    case 3: pprintf("En mantenimiento\n"); break;
    case 4: pprintf("De baja\n"); break;
    }
}

int starshipStatus(int ID)                      //Retorna el estado de la nave
{
    stStarship starship;
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    if(starshipExistByID(ID))
    {
        if(archive != NULL)
        {
            while(!feof(archive))
            {
                fread(&starship, sizeof(stStarship), 1, archive);
                if(starship.ID == ID)
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
    return starship.status;
}

void printAllStarships()                        //Muestra todas las naves cargadas en el archivo
{

    FILE* archive;
    archive = fopen(Fstarships,"rb");
    stStarship starship;
    if(archive != NULL)
    {
        do
        {
            fread(&starship, sizeof(stStarship), 1, archive);
            printSpaceshipData(starship);
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

void changeFlyTime(int ID, int time_fly)        //Cambia el tiempo de vuelo
{
    FILE * archive;
    archive = fopen(Fstarships, "w+b");
    stStarship starship;
    if(starshipExistByID(ID))
    {
        if(archive!= NULL)
        {
            fseek(archive, sizeof(stStarship) * (ID -1),SEEK_SET);
            fread(&starship, sizeof(stStarship), 1,archive);
            fseek(archive, sizeof(stStarship) * (-1),SEEK_CUR);
            starship.hours_flight = starship.hours_flight + time_fly;
            fwrite(&starship, sizeof(stStarship), 1, archive);
            fclose(archive);
        }
    }
}

void changeFlyTimebyUser(int ID)                //solicita un tiempo sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{
    int time;
    pprintf("Ingrese cant de horas: ");
    scanf("%i", &time);
    changeFlyTime(ID, time);
}

void showFlyTime(int ID)                        //Muestra el tiempo de vuelo por ID
{
    FILE* archive;
    archive = fopen(Fstarships, "rb");
    stStarship starship;
    if(starshipExistByID(ID))
    {
        if(archive != NULL)
        {
            fseek(archive, sizeof(stStarship) * (ID -1), SEEK_SET);
            fread(&starship, sizeof(stStarship), 1, archive);
            pprintf("Cantidad de horas en vuelo: ");
            printf("%i\n", starship.hours_flight);
            fclose(archive);
        }
    }
}

void showAmmountFlys(int ID)                    //Muestra la cantidad de vuelos
{

    FILE* archive;
    archive = fopen(Fstarships, "rb");
    stStarship starship;
    if(starshipExistByID(ID))
    {
        if(archive != NULL)
        {
            fseek(archive, sizeof(stStarship) * (ID -1), SEEK_SET);
            fread(&starship, sizeof(stStarship), 1, archive);
            pprintf("Cantidad de vuelos: ");
            printf("%i\n", starship.ammount_flights);
            fclose(archive);
        }
    }
}

void changeAmmountFlys(int ID, int times_fly)    //Cambia la cantidad de vuelos
{
    FILE * archive;
    archive = fopen(Fstarships, "w+b");
    stStarship starship;
    if(starshipExistByID(ID))
    {
        if(archive!= NULL)
        {
            fseek(archive, sizeof(stStarship) * (ID -1),SEEK_SET);
            fread(&starship, sizeof(stStarship), 1,archive);
            fseek(archive, sizeof(stStarship) * (-1),SEEK_CUR);
            starship.ammount_flights = starship.ammount_flights + times_fly;
            fwrite(&starship, sizeof(stStarship), 1, archive);
            fclose(archive);
        }
    }
}

void changeAmmountFlysbyUser(int ID)             //solicita una cantidad sin restricciones, por si se quisiese modificar un error de ingreso restando horas.
{
    int times;
    pprintf("Ingrese cant de horas: ");
    scanf("%i", &times);
    changeAmmountFlys(ID, times);
}


//Misiones
void RegisterMission()
{
    stMission mission;
    bool shipExists = false;
    int option = 1, flag = 0, shipAvailability = 0, astronautAvailability = 0, i = 0; //i, contador de tripulantes por misión
    while ( option == 1 )
    {
        pprintf ( "ID de la nave:\n" );
        scanf ( "%d", &mission.ID_ship );
        shipExists = starshipExistByID(mission.ID_ship);
        while ( shipExists != true || shipAvailability != 1 ) {
            pprintf ( "La ID de la nave no existe o la nave no esta lista para su uso, intente de nuevo\n" );
            scanf ( "%d", &mission.ID_ship );
            shipExists = starshipExistByID(mission.ID_ship);

            if ( shipExists == true ) {
                shipAvailability = starshipStatus(mission.ID_ship);
            }
        }
        pprintf ( "destino de la mision: 1-EEI, 2-orbita terrestre, 3-luna\n" );
        scanf ( "%d", &mission.destiny );
        while ( mission.destiny <= 0 || mission.destiny > 3 )
        {
            pprintf ( "destino desconocido, intente de nuevo\n" );
            scanf ( "%d", &mission.destiny );
        }
        pprintf ( "tipo de cargamento de la mision: 1-satelite, 2-insumos para la EE\n" );
        scanf ( "%d", &mission.shipment);
        while ( mission.shipment < 0 || mission.shipment > 2 )
        {
            pprintf ( "cargamento desconocido, intente de nuevo\n" );
            scanf ( "%d", &mission.shipment );
        }
        printf ( "Ingrese las ID de los tripulantes que van a estar presentes en la mision: (hasta %d tripulantes)\n", dimInt );
        for ( i = 0; option == 1 && i < dimInt; i++ )
        {
            scanf ( "%d", &mission.crewmans[i] );
            flag = ConfirmAstronautID(mission.crewmans[i]);               //confirma si el astronauta existe
            astronautAvailability = AstronautAvailability(mission.crewmans[i]);     //confirma si el astronauta está disponible o si está retirado
            while ( flag != NULL || astronautAvailability != 1 )
            {
                pprintf ( "La ID no existe o el astronauta no esta disponible, ingrese de nuevo la ID\n" );
                scanf ( "%d", &mission.crewmans[i]);
                flag = ConfirmAstronautID(mission.crewmans[i]);
                shipAvailability = AstronautAvailability(mission.crewmans[i]);
            }
            pprintf ( "para meter otro tripulante ingrese 1:\n" );
            scanf ( "%d", &option );
        }
        mission.ammount_crewmans = i;       //cantidad total de tripulantes
        printf ( "agregue una breve descripcion de la mision: (%d caracteres)\n", dimChar );
        fflush(stdin);
        gets ( mission.details_of_mission );
        mission.ID = GetLastMissionID() + 1;
        mission.status = 1; //lo registra automáticamente en 'mision lista'
        SaveMission(mission);
        pprintf ( "para registrar otra mision ingrese 1:\n" );
        scanf ( "%d", &option );
    }
}

void SaveMission(stMission the_mission)
{
    FILE *file = fopen(Fmissions, "ab");
    if ( file != NULL )
    {
        fwrite(&the_mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

int ConfirmMissionID(int ID)  //usada para encontrar ID repetida y verificar si existe el tripulante, retorna NULL si la ID enviada se encontró en un registro
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

void ChangeMissionID()
{
    stMission mission;
    int pos = SelectMission(), flag = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nueva ID de mision: \n" );
        scanf ( "%d", &mission.ID );
        flag = ConfirmMissionID(mission.ID);
        while ( flag == NULL )
        {
            pprintf ( "La ID de mision ya existe, intente de nuevo\n" );
            scanf ( "%d", &mission.ID );
            flag = ConfirmMissionID(mission.ID);
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionStarshipID()
{
    stMission mission;
    bool flag = false;
    int pos = SelectMission(), shipAvailability = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nueva ID de nave: \n" );
        scanf ( "%d", &mission.ID_ship );
        flag = starshipExistByID(mission.ID_ship);
        while ( flag != true || shipAvailability != 1 )
        {
            pprintf ( "ID de nave no existente o nave no lista para su uso, intente de nuevo\n" );
            scanf ( "%d", &mission.ID_ship );
            flag = starshipExistByID(mission.ID_ship);

            if ( flag == true ) {
                shipAvailability = starshipStatus(mission.ID_ship);
            }
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionDetails()
{
    stMission mission;
    int pos = SelectMission();
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevos detalles: \n" );
        fflush(stdin);
        gets ( mission.details_of_mission );
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionShipment()
{
    stMission mission;
    int pos = SelectMission();
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevo cargamento: 1-satelite, 2-insumos para la EE\n" );
        scanf ( "%d", &mission.shipment );
        while ( mission.shipment < 1 || mission.shipment > 2 )
        {
            pprintf ( "Cargamento no existente, pruebe de nuevo \n" );
            scanf ( "%d", &mission.shipment );
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionDestiny()
{
    stMission mission;
    int pos = SelectMission();
    FILE *file = (Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Nuevo destino: 1-EEI, 2-orbita terrestre, 3-luna" );
        scanf ( "%d", &mission.destiny );
        while ( mission.destiny <= 0 || mission.destiny > 3 )
        {
            pprintf ( "Destino desconocido, vuelva a intentar\n" );
            scanf ( "%d", &mission.destiny );
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionCrewmanList()
{
    stMission mission;
    int pos = SelectMission(), option = 0, i = 0, flag = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Seleccione los tripulantes por sus IDs:\n" );
        for ( i = 0; i < dimInt && option == 1; i++ )
        {
            scanf ( "%d", &mission.crewmans[i] );
            flag = ConfirmAstronautID(mission.crewmans[i]);
            while ( flag != NULL )
            {
                pprintf ( "El astronauta no existe, intente de nuevo\n" );
                scanf ( "%d", &mission.crewmans[i] );
                flag = ConfirmAstronautID(mission.crewmans[i]);
            }
            pprintf ( "Agregar otro astronauta? 1-Si\n" );
            scanf ( "%d", &option );
        }
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionStatus()
{
    stMission mission;
    int pos = SelectMission(), option = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        pprintf ( "Cambiar estado??? 1-Si \n" );
        scanf ( "%d", &option );
        if ( option == 1 && mission.status == 1 )
        {
            mission.status = 2;
        }
        if ( option == 1 && mission.status == 2 )
        {
            mission.status = 1;
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

int SelectMission()     //fedep: probar esto porfa
{
    stMission mission;
    int pos = 0;
    ShowMissions();
    pprintf ( "Seleccione una mision\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 )
    {
        pprintf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
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
            pprintf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
            ShowMissions();
            scanf ( "%d", &pos );
            fseek(file, sizeof(stMission) * pos, SEEK_SET);
            fread(&mission, sizeof(stMission), 1, file);
        }
        fclose(file);
    }
    return pos;
}

void ShowMissions()    //muestra todas las misiones registradas
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
                printf ( "|%d| ID:%d, ID de nave:%d, ", i, mission.ID, mission.ID_ship );
                if ( mission.shipment == 1 )
                {
                    pprintf ( "Cargamento: satelite, " );
                }
                else
                {
                    pprintf ( "Cargamento: insumos para la EE, " );
                }
                if ( mission.destiny == 1 )
                {
                    pprintf ( "Destino: EEI, " );
                }
                else if ( mission.destiny == 2 )
                {
                    pprintf ( "Destino: orbita terrestre\n" );
                }
                else
                {
                    pprintf ( "Destino: Luna\n" );
                }
                printf ( "Mision: %s\n", mission.details_of_mission );
                for ( j = 0; j < mission.ammount_crewmans; j++ )
                {
                    printf ( "ID Tripulante n%d: %d\n", j+1, mission.crewmans[j] );
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

int GetLastMissionID()
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
        stStarship starship;
        if (fread(&starship, sizeof(stStarship), 1, archive) == 1)
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

void saveColorChange(int colorChoosed)
{
    stUserData userData;
    userData.proceduralText = proceduralTextRead();
    userData.consoleColor = colorChoosed;
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
void textMainMenu(){





}

