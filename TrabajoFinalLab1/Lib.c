#include "Lib.h"
#include <unistd.h>
bool proceduralText = true;
//aca van las funciones

//Astronautas
void RegisterAstronaut()            //registra astronauta
{
    stAstronaut user;
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
		user.ID = GetLastAstronautID() + 1;
        printf ( "ID otorgada: %d", user.ID );
        SaveAstronaut(user);
		printf ( "para registrar otro astronauta ingrese 1:\n" );
		scanf ( "%d", &option );
	}
}

void SaveAstronaut(stAstronaut user)    //guarda astronauta en archivo
{
    FILE *file = fopen(Fastronauts, "ab");
	if ( file != NULL ) {
		fwrite(&user, sizeof(stAstronaut), 1, file);
		fclose(file);
	}
}

int ConfirmAstronautID(int ID)  //usada para encontrar ID repetida y verificar si existe el tripulante, retorna NULL si la ID enviada se encontró en un registro
{
    int flag = 0;
    stAstronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && ID == user.ID ) {
                flag = NULL;
            }
        }
        fclose(file);
    }
    return flag;
}

void ChangeAstronautName()      //modifica uno o todos los campos de un astronauta excepto el estado
{
    stAstronaut user;
    int pos = SelectAstronaut();
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nuevo nombre: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nuevo apellido: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nuevo apodo:\n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva edad: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva ID: \n" );
        scanf ( "%d", &user.ID );
        flag = ConfirmAstronautID(user.ID);
        while ( flag == NULL ) {
            printf ( "ID en uso, intente de nuevo\n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva nacionalidad: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva especialidad: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva cantidad de hrs de vuelo: \n" );
        scanf ( &user.hours_flight );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva cantidad de hrs en la estacion espacial: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Nueva cantidad de misiones: \n" );
        scanf ( &user.missions );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        printf ( "Cambiar estado??? 1-Si \n" );
        scanf ( &option );
        if ( option == 1 && user.status == 1 ) {
            user.status = 2;
        }
        if ( option == 1 && user.status == 2 ) {
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
    printf ( "Modifique un astronauta\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 ) {
        printf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * pos, SEEK_SET);
        fread(&user, sizeof(stAstronaut), 1, file);
        while ( feof(file) || pos < 0 ) {   //en teoría esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
            system("cls");
            printf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
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
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&aux, sizeof(stAstronaut), 1, file);
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

int AstronautAvailability(int ID)      //indica la disponibilidad del astronauta, 1-activo, 2-retirado, NULL-no existe
{
    stAstronaut user;
    int availability = NULL;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL ) {
        while ( !feof(file) && availability == NULL ) {
            fread(&user, sizeof(stAstronaut), 1, file);
            if ( !feof(file) && ID == user.ID) {
                if ( user.status == 1 ) {
                    availability = 1;
                } else {
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
    if ( file != NULL ) {
        fseek(file, sizeof(stAstronaut) * -1, SEEK_END);
        fread(&user, sizeof(stAstronaut), 1, file);
        fclose(file);
    }
    return user.ID;
}


//Naves
void saveStarship(stStarship starship)
{
    FILE * archive;
    archive = fopen(Fstarships, "ab");
    if(archive != NULL)
    {
        fwrite(&starship, sizeof(stStarship), 1, archive);
        fclose(archive);
    }
}

void registerStarship()
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

int getLastStarshipID()
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

void changeStarshipType(char starshipName[])
{

    char typeSelected[30];
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
        strcpy((starshipName),"Falcon 9");
        break;

    case 3:
        strcpy((starshipName), "Falcon Heavy");
        break;
    }

}

int changeStarshipStatus()
{

    char typeSelected[30];
    int Max = 4;
    int option;
    do
    {
        system("cls");
        pprintf("Tipo de nave:\n");
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

void searchSpaceshipByID() //Verifica si la nave existe la busca y permite modificar sus datos o visualizarla
{
    FILE * archive;
    archive = fopen(Fstarships, "rb");
    int ID = 0;
    int option = 0;
    stStarship starship;
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
                pprintf("Nave encontrada\n ¿Que desea hacer?\n>: ");
                fflush(stdin);
                scanf("%i", &option);
                switch(option)
                {

                case 1://Modificar


                    break;

                case 2://Mostrar
                    fseek(archive, sizeof(stStarship) * (ID-1), SEEK_SET);
                    fread(&starship, sizeof(stStarship),1, archive);
                    printSpaceshipData(starship);
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

bool starshipExistByID(int ID)
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

void printSpaceshipData(stStarship starship)
{
    system("cls");
    pprintf("----------------------------------------\n");
    printf("Nave ID: %i\n", starship.ID);
    printf("Tipo de nave: %s\n", starship.type);
    printf("Vuelos Realizados: %i\n", starship.ammount_flights);
    printf("Horas de vuelo: %i\n", starship.hours_flight);
    printf("Estado de la nave: %i\n", starship.status);
    pprintf("----------------------------------------\n");
    system("pause");
}

void printStarshipStatus(int i)
{   //transformar los int en cadena de caracteres



}


//Misiones
void RegisterMission() //pendiente 2 funciones de Eloy: la primera que retorne NULL si la ID de la nave se encontró en los registros o 0 si no se encontró
{
	stMission mission;
	int option = 1, flag = 0, availability = 0, i = 0; //contador de tripulantes por misión
	while ( option == 1 ) {
		printf ( "ID de la mision\n" );
		scanf ( "%d", &mission.ID );
		flag = ConfirmMissionID(mission.ID);
		printf ( "ID de la nave:\n" );
		scanf ( "%d", &mission.ID_ship );
		//aca va: flag = funcion
        while ( flag != NULL ) {//crear la funcion que verifique si existe el ID de la nave, y ademas que la nave no este en mantenimiento, ni este de baja, ni este en uso, que solo este en estado 'lista', para que pueda ser otorgada a la misión
            printf ( "La ID de la nave no existe, intente de nuevo}n" );
            scanf ( "%d", &mission.ID_ship );
            //flag = funcion
        }
		printf ( "destino de la mision: 1-EEI, 2-orbita terrestre, 3-luna\n" );
		scanf ( "%d", &mission.destiny );
		while ( mission.destiny <= 0 || mission.destiny > 3 ) {
			printf ( "destino desconocido, intente de nuevo\n" );
			scanf ( "%d", &mission.destiny );
		}
		printf ( "tipo de cargamento de la mision: 1-satelite, 2-insumos para la EE\n" );
		scanf ( "%d", &mission.shipment);
		while ( mission.shipment < 0 || mission.shipment > 2 ) {
			printf ( "cargamento desconocido, intente de nuevo\n" );
			scanf ( "%d", &mission.shipment );
		}
		printf ( "Ingrese las ID de los tripulantes que van a estar presentes en la mision: (hasta %d tripulantes)\n", dimInt );
		for ( i = 0; option == 1 && i < dimInt; i++ ) {
			scanf ( "%d", &mission.crewmans[i] );
            flag = ConfirmAstronautID(mission.crewmans[i]);               //confirma si el astronauta existe
            availability = AstronautAvailability(mission.crewmans[i]);     //confirma si el astronauta está disponible o si está retirado
			while ( flag != NULL || availability != 1 ) {
                printf ( "La ID no existe o el astronauta no esta disponible, ingrese de nuevo la ID\n" );
                scanf ( "%d", &mission.crewmans[i]);
                flag = ConfirmAstronautID(mission.crewmans[i]);
                availability = AstronautAvailability(mission.crewmans[i]);
			}
			printf ( "para meter otro tripulante ingrese 1:\n" );
			scanf ( "%d", &option );
		}
		mission.ammount_crewmans = i;       //cantidad total de tripulantes
		printf ( "agregue una breve descripcion de la mision: (%d caracteres)\n", dimChar );
		fflush(stdin);
		gets ( mission.details_of_mission );
		mission.ID = GetLastMissionID() + 1;
		mission.status = 1; //lo registra automáticamente en 'mision lista'
		SaveMission(mission);
		printf ( "para registrar otra mision ingrese 1:\n" );
		scanf ( "%d", &option );
    }
}

void SaveMission(stMission the_mission)
{
    FILE *file = fopen(Fmissions, "ab");
	if ( file != NULL ) {
		fwrite(&the_mission, sizeof(stMission), 1, file);
		fclose(file);
	}
}

int ConfirmMissionID(int ID)  //usada para encontrar ID repetida y verificar si existe el tripulante, retorna NULL si la ID enviada se encontró en un registro
{
    int flag = 0;
    stMission the_mission;
    FILE *file = fopen(Fmissions, "rb");
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&the_mission, sizeof(stMission), 1, file);
            if ( !feof(file) && ID == the_mission.ID ) {
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Nueva ID de mision: \n" );
        scanf ( "%d", &mission.ID );
        flag = ConfirmMissionID(mission.ID);
        while ( flag == NULL ) {
            printf ( "La ID de mision ya existe, intente de nuevo\n" );
            scanf ( "%d", &mission.ID );
            flag = ConfirmMissionID(mission.ID);
        }
        fseek(file, sizeof(stMission) * -1, SEEK_CUR);
        fwrite(&mission, sizeof(stMission), 1, file);
        fclose(file);
    }
}

void ChangeMissionStarshipID()  //pendiente 1 funcion de Eloy
{
    stMission mission;
    int pos = SelectMission(), flag = 0;
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Nueva ID de nave: \n" );
        scanf ( "%d", &mission.ID_ship );
        //flag = funcion de si ID de nave existe
        while ( flag != NULL ) {
            printf ( "ID de nave no existente, intente de nuevo\n" );
            scanf ( "%d", &mission.ID_ship );
            //flag = funcion de si ID de nave existe
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Nuevos detalles: \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Nuevo cargamento: 1-satelite, 2-insumos para la EE\n" );
        scanf ( "%d", &mission.shipment );
        while ( mission.shipment < 1 || mission.shipment > 2 ) {
            printf ( "Cargamento no existente, pruebe de nuevo \n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Nuevo destino: 1-EEI, 2-orbita terrestre, 3-luna" );
        scanf ( "%d", &mission.destiny );
        while ( mission.destiny <= 0 || mission.destiny > 3 ) {
            printf ( "Destino desconocido, vuelva a intentar\n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Seleccione los tripulantes por sus IDs:\n" );
            for ( i = 0; i < dimInt && option == 1; i++ ) {
                scanf ( "%d", &mission.crewmans[i] );
                flag = ConfirmAstronautID(mission.crewmans[i]);
                while ( flag != NULL ) {
                    printf ( "El astronauta no existe, intente de nuevo\n" );
                    scanf ( "%d", &mission.crewmans[i] );
                    flag = ConfirmAstronautID(mission.crewmans[i]);
                }
                printf ( "Agregar otro astronauta? 1-Si\n" );
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
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        printf ( "Cambiar estado??? 1-Si \n" );
        scanf ( "%d", &option );
        if ( option == 1 && mission.status == 1 ) {
            mission.status = 2;
        }
        if ( option == 1 && mission.status == 2 ) {
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
    printf ( "Modifique una mision\n" );
    scanf ( "%d", &pos );
    while ( pos < 0 ) {
        printf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
        scanf ( "%d", &pos );
    }
    FILE *file = fopen(Fmissions, "r+b");
    if ( file != NULL ) {
        fseek(file, sizeof(stMission) * pos, SEEK_SET);
        fread(&mission, sizeof(stMission), 1, file);
        while ( feof(file) || pos < 0 ) {   //en teoría esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
            system("cls");
            printf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
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
    if ( file != NULL ) {
        while ( !feof(file)) {
            fread(&mission, sizeof(stMission), 1, file);
            if ( !feof(file)) {
                printf ( "|%d| ID:%d, ID de nave:%d, ", i, mission.ID, mission.ID_ship );
                if ( mission.shipment == 1 ) {
                    printf ( "Cargamento: satelite, " );
                } else {
                        printf ( "Cargamento: insumos para la EE, " );
                    }
                if ( mission.destiny == 1 ) {
                    printf ( "Destino: EEI, " );
                } else if ( mission.destiny == 2 ) {
                        printf ( "Destino: orbita terrestre\n" );
                    } else {
                            printf ( "Destino: Luna\n" );
                        }
                printf ( "Mision: %s\n", mission.details_of_mission );
                for ( j = 0; j < mission.ammount_crewmans; j++ ) {
                    printf ( "ID Tripulante n%d: %d\n", j+1, mission.crewmans[j] );
                }
                if ( mission.status == 1 ) {
                    printf ( "Estado de mision: Lista" );
                } else if ( mission.status == 2 ) {
                        printf ( "Estado de mision: En vuelo" );
                    } else if ( mission.status == 3 ) {
                            printf ( "Estado de mision: Retornada" );
                        } else if ( mission.status == 4 ) {
                                printf ( "Estado de mision: Cancelada" );
                            } else {
                                    printf ( "Estado de mision: Fallida" );
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
    if ( file != NULL ) {
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

    if (proceduralText)
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

    if (archive != NULL) {
        stStarship starship;
        if (fread(&starship, sizeof(stStarship), 1, archive) == 1) {
            firstOne = true;
        }

        fclose(archive);
    }

    return firstOne;
}


//Menus
void draw_mainmenu()
{
    system("cls");
    pprintf("<EmmaMusk>\n");
    pprintf ( "1- Registrar\n" );
    pprintf ( "2- Modificar\n" );
    pprintf ( "3- Consultar\n" );
    pprintf ( "4- Mofidicar estados de astronautas, naves y misiones\n" );
    pprintf ( "0- Cerrar programa\n" );
    pprintf ( "opcion: " );
}
void drawmenu_1()   //menuPrincipal
{
    system("cls");
    pprintf("<REGISTROS>\n");
    pprintf ( "1- Registrar astronautas\n" );
    pprintf ( "2- Registrar naves\n" );
    pprintf ( "3- Registrar misiones\n" );
    pprintf ( "4- Regresar al menu principal\n" );
    pprintf ( "opcion: " );
}
void drawmenu_2()   //menuModificar
{
    system("cls");
    pprintf("<MODIFICAR>\n");
    pprintf ( "1- Modificar astronauta\n" );
    pprintf ( "2- Modificar nave\n" );
    pprintf ( "3- Modificar mision\n" );
    pprintf ( "4- Regresar\n" );
    pprintf ( "opcion: " );
}
void drawmenu_3()    //menuConsultas
{
    system("cls");
    pprintf("<CONSULTAS>\n");
    pprintf ( "1- Consultar astronautas por ID\n" );
    pprintf ( "2- Consultar naves por ID\n" );
    pprintf ( "3- Consultar misiones por ID\n" );
    pprintf ( "4- Regresar\n" );
    pprintf ( "opcion: " );
}
void drawmenu_4()   //menuModificarEstados
{
    system("cls");
    pprintf("<ALTA / BAJA > \n");
    pprintf ( "1- Dar de Alta a un astronauta \n" );
    pprintf ( "2- Dar de Baja a un astronauta \n" );
    pprintf ( "3- Cambiar estado de una nave \n" );
    pprintf ( "4- Cambiar estado de una mision \n" );
    pprintf ( "Opcion: " );
}

