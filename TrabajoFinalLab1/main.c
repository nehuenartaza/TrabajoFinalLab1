
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lib.h"


int main()
{
    readUserData();
    mainMenu();
    return 0;
}
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
            break;
        case 3:
            break;
        default:
            break;
            if(option != 0)
            {
                printf("Opcion invalida, ingrese un valor valido");
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

            break;
        case 3:
            spaceshipMenu();
            break;

        default:
            if(option != 0)
            {
                printf("Opcion invalida, ingrese un valor valido");
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
                printf("Opcion invalida, ingrese un valor valido");
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
                printf("Opcion invalida, ingrese un valor valido");
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
            //showAstronautByID();
            break;
        case 2:
            showAstronauts();
            break;
        default:
            if(option != 0)
            {
                printf("Opcion invalida, ingrese un valor valido");
            }
            break;
        }
    }
    while(option != 0);
}

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
                printf("Opcion invalida, ingrese un valor valido");
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
                printf("Opcion invalida, ingrese un valor valido");
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

        pprintf(" 1- Modificar estado de la nave.\n");
        pprintf(" 2- Modificar horas de vuelo.\n");
        pprintf(" 3- Modificar cantidad de viajes.\n");
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
                printf("Opcion invalida, ingrese un valor valido");
            }
            break;
        }
    }
    while(option != 0);
}




void optionsMenu()
{

    int option = 0;
    do
    {
        system("cls");

        pprintf(" 1- Cambiar color de la consola.\n");
        pprintf(" 2- Desactivar / Activar Texto procedural.\n");
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
                printf("Opcion invalida, ingrese un valor valido");
            }
            break;
        }
    }
    while(option != 0);
}


