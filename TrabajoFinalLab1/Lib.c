#include "Lib.h"
#include <unistd.h>
bool proceduralText = true;
//aca van las funciones
void register_astronaut()
{
    STastronaut user;
    int option = 1, flag = 0;
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
        pprintf ( "Su ID:\n" );
        scanf ( "%d", &user.ID );
        flag = confirm_astronaut_ID(user.ID);
        while ( flag == NULL )
        {
            pprintf ( "La ID ya existe, ingrese de nuevo la ID\n" );
            scanf ( "%d", &user.ID );
            flag = confirm_astronaut_ID(user.ID);
        }
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
        save_astronaut(user);
        pprintf ( "para registrar otro astronauta ingrese 1:\n" );
        scanf ( "%d", &option );
    }
}

void save_astronaut(STastronaut user)
{
    FILE *file = fopen(Fastronauts, "ab");
    if ( file != NULL )
    {
        fwrite(&user, sizeof(STastronaut), 1, file);
        fclose(file);
    }
}

int confirm_astronaut_ID(int ID)  //flag pasa a NULL si la ID está repetida
{
    int flag = 0;
    STastronaut user;
    FILE *file = fopen(Fastronauts, "rb");
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&user, sizeof(STastronaut), 1, file);
            if ( !feof(file) && ID == user.ID )
            {
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
    pprintf ( "Modifique un astronauta\n" );
    scanf ( "%d", &value );
    while ( value < 0 )         //value es la posicion del registro
    {
        pprintf ( "No se permite un valor menor a 0, pruebe de nuevo\n" );
        scanf ( "%d", &value );
    }
    FILE *file = fopen(Fastronauts, "r+b");
    if ( file != NULL )
    {
        fseek(file, sizeof(STastronaut) * value, SEEK_SET);
        fread(&aux, sizeof(STastronaut), 1, file);
        while ( feof(file) || value < 0 )     //en teoria esto salva al programa, ej: tener 10 registros y que el usuario elija el registro 11, encargado fedep de probar esto
        {
            system("cls");
            pprintf ( "registro no existente o valor menor a 0 no permitido, intente de nuevo\n" );
            show_astronauts();
            scanf ( "%d", &value );
            fseek(file, sizeof(STastronaut) * value, SEEK_SET);
            fread(&aux, sizeof(STastronaut), 1, file);
        }
        user = aux;
        pprintf ( "modificar nombre? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nuevo nombre: \n" );
            fflush(stdin);
            gets ( user.name );
        }
        pprintf ( "cambiar apodo? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nuevo apodo: \n" );
            fflush(stdin);
            gets ( user.nickname );
        }
        pprintf ( "modificar apellido? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nuevo apellido: \n" );
            fflush(stdin);
            gets ( user.last_name );
        }
        pprintf ( "modificar ID? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva ID: \n" );
            scanf ( "%d", &user.ID );
            flag = confirm_astronaut_ID(user.ID);
            while ( flag == NULL )
            {
                pprintf ( "ID en uso, intente de nuevo\n" );
                scanf ( "%d", &user.ID );
                flag = confirm_astronaut_ID(user.ID);
            }
        }
        pprintf ( "modificar edad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva edad: \n" );
            scanf ( "%d", &user.age );
        }
        pprintf ( "modificar nacionalidad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva nacionalidad: \n" );
            fflush(stdin);
            gets ( user.nationality );
        }
        pprintf ( "modificar especialidad? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva especialidad: \n" );
            fflush(stdin);
            gets ( user.speciality );
        }
        pprintf ( "modificar horas de vuelo? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva cantidad de hrs de vuelo: \n" );
            scanf ( &user.hours_flight );
        }
        pprintf ( "modificar horas en la estacion espacial? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva cantidad de hrs en la estacion espacial: \n" );
            scanf ( &user.hours_at_spaceStation );
        }
        pprintf ( "modificar cantidad de misiones hechas? 1-Si\n" );
        scanf ( "%d", &option );
        if ( option == 1 )
        {
            pprintf ( "Nueva cantidad de misiones: \n" );
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
    if ( file != NULL )
    {
        while ( !feof(file))
        {
            fread(&aux, sizeof(STastronaut), 1, file);
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
void drawmenu_1()//menuPrincipal
{
    system("cls");
    pprintf("<REGISTROS>\n");
    pprintf ( "1- Registrar astronautas\n" );
    pprintf ( "2- Registrar naves\n" );
    pprintf ( "3- Registrar misiones\n" );
    pprintf ( "4- Regresar al menu principal\n" );
    pprintf ( "opcion: " );
}
void drawmenu_2() //menuModificar
{
    system("cls");
    pprintf("<MODIFICAR>\n");
    pprintf ( "1- Modificar astronauta\n" );
    pprintf ( "2- Modificar nave\n" );
    pprintf ( "3- Modificar mision\n" );
    pprintf ( "4- Regresar\n" );
    pprintf ( "opcion: " );
}
void drawmenu_3() //menuConsultas
{
    system("cls");
    pprintf("<CONSULTAS>\n");
    pprintf ( "1- Consultar astronautas por ID\n" );
    pprintf ( "2- Consultar naves por ID\n" );
    pprintf ( "3- Consultar misiones por ID\n" );
    pprintf ( "4- Regresar\n" );
    pprintf ( "opcion: " );
}
void drawmenu_4()//darDebajaNave
{
    system("cls");
    pprintf("<ALTA / BAJA > \n");
    pprintf ( "1- Dar de Alta a un astronauta \n" );
    pprintf ( "2- Dar de Baja a un astronauta \n" );
    pprintf ( "3- Cambiar estado de una nave \n" );
    pprintf ( "4- Cambiar estado de una mision \n" );
    pprintf ( "Opcion: " );
}

//Naves

void saveStarship (stStarship starship)
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

void printStarshipStatus(int i){
//transformar los int en cadena de caracteres



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

bool firstSpaceShip() {
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
