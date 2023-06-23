#include <stdio.h>
#include <time.h>
#include <stdbool.h>
//Constantes
#define dimInt 15
#define dimChar 50
#define Fastronauts "astronautsData.bin"
#define Fstarships "starshipsData.bin"
#define Fmissions "missionsData.bin"
//aca van los prototipados y estructuras

//Estructuras
typedef struct
{
    char name[dimChar];
    char last_name[dimChar];
    char nickname[dimChar];
    int ID;
    int age;
    char nationality[dimChar];
    char speciality[dimChar];
    int hours_flight;
    int missions;
    int hours_at_spaceStation;
    int status; //1-activo, 2-retirado
} stAstronaut;

typedef struct
{
    int ID;
    char type[dimChar]; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
    int ammount_flights;
    int hours_flight;
    int status; //0-mantenimiento, 1-lista para usar, 2-en uso, 3-de baja
} stStarship;

typedef struct
{
    int ID;
    int ID_ship;
    int status; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
    int destiny; //1-EEI, 2-orbita terrestre, 3-luna
    int shipment; //1-satelite, 2-insumos para la EE
    int crewmans[dimInt];
    char details_of_mission[dimChar]; //breve descripcion
    int ammount_crewmans;
} stMission;

//Astronautas
void RegisterAstronaut();
void SaveAstronaut(stAstronaut);
int ConfirmAstronautID(int);
void ChangeAstronautName();
void ChangeAstronautLastName();
void ChangeAstronautNickname();
void ChangeAstronautAge();
void ChangeAstronautID();
void ChangeAstronautNationality();
void ChangeAstronautSpeciality();
void ChangeAstronautFlightTime();
void ChangeAstronautHoursSpaceStation();
void ChangeAstronautAmmountMissions();
void ChangeAstronautStatus();
int SelectAstronaut();
void ShowAstronauts();
int AstronautAvailability(int);
int GetLastAstronautID();

//Naves
void saveStarship(stStarship starship);
void changeStarshipType();
void registerStarship();
int getLastStarshipID();
void changeStarshipType(char starshipName[]);
int changeStarshipStatus();
void searchSpaceshipByID();
bool starshipExistByID(int ID);
void printSpaceshipData(stStarship starship);

//Misiones
void RegisterMission();
void SaveMission(stMission);
int ConfirmMissionID(int);
void ChangeMissionID();
void ChangeMissionStarshipID();
void ChangeMissionDetails();
void ChangeMissionShipment();
void ChangeMissionDestiny();
void ChangeMissionCrewmanList();
void ChangeMissionStatus();
int SelectMission();
void ShowMissions();
int GetLastMissionID();

//Menu
void draw_mainmenu();
void drawmenu_1();
void drawmenu_2();
void drawmenu_3();
void drawmenu_4();


//Otros
void pprintf(const char *str);
bool firstSpaceShip();
