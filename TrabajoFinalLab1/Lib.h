#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>
//Constantes
#define dimInt 15
#define dimChar 50
#define Fastronauts "astronautsData.bin"
#define Fstarships "starshipsData.bin"
#define Fmissions "missionsData.bin"
#define FuserData "userData.bin"
//aca van los prototipados y estructuras

//Estructuras
typedef struct
{
    int ID;
    char name[dimChar];
    char last_name[dimChar];
    char nickname[dimChar];
    int age;
    char nationality[dimChar];
    char speciality[dimChar];
    int flight_hours;
    int missions;
    int hours_at_spaceStation;
    int status; //1-activo, 2-retirado
} stAstronaut;

typedef struct
{
    int ID;
    char type[dimChar]; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
    int number_of_flights;
    int flight_hours;
    int status; //1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
} stSpaceship;

typedef struct
{
    int ID;
    int ship_ID;
    int status; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
    int destination; //1-EEI, 2-orbita terrestre, 3-luna
    int shipment; //1-satelite, 2-insumos para la EE
    int crewmen[dimInt];
    char mission_details[dimChar]; //breve descripcion
    int crewman_amount;
} stMission;

typedef struct
{
    int consoleColor;
    bool proceduralText;
}stUserData;

//Astronautas
void registerAstronaut();
void saveAstronaut(stAstronaut);
int confirmAstronautID(int);
void changeAstronautNickname();
void changeAstronautAge();
void changeAstronautSpeciality();
void changeAstronautFlightTime();
void changeAstronautHoursSpaceStation();
void changeAstronautAmmountMissions();
void changeAstronautStatus();
int selectAstronaut();
void showAstronauts();
int astronautAvailability(int);
int getLastAstronautID();
int getTotalAstronauts();
bool firstAstronaut();
//void showAstronautByID()

//Naves
void saveSpaceship(stSpaceship starship);                           // Guarda en la ultima posicion del archivo la nave recibida por parametro
void registerSpaceship();                                           // Carga de datos y en archivo una nueva nave. Con parametros en automatico
int getLastSpaceshipID();                                           // Obtiene la ultima ID del registro
int changeSpaceshipStatus();                                        // Retorna el estado de la nave elegida: 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
void showSpaceshipByID();                                           // Verifica si la nave existe, la busca y permite modificar sus datos o visualizarla
void showSpaceship(int ID);                                         // Muestra una nave por su ID
bool spaceshipExistByID(int ID);                                    // Retorna verdadero si la nave existe en el archivo en base al ID recibido
void printSpaceshipData(stSpaceship starship);                      // Imprime por pantalla los datos de la nave
void printSpaceshipStatus(int spaceshipStatus);                     // Imprime el estado de la nave: 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
int spaceshipStatus(int ID);                                        // Retorna el estado de la nave
void printAllStarships();                                           // Muestra todas las naves cargadas en el archivo
void changeFlightTime(int ID, int time_fly);                        // Cambia el tiempo de vuelo
void changeSpaceshipFlightTime();                                   // Solicita un tiempo sin restricciones, por si se quisiese modificar un error de ingreso restando horas
void showFlightTime(int ID);                                        // Muestra el tiempo de vuelo por ID
void showFlightsAmount(int ID);                                     // Muestra la cantidad de vuelos
void changeFlightsAmount(int ID, int times_fly);                    // Cambia la cantidad de vuelos
void changeSpaceshipFlightsAmount();                          //
bool firstSpaceShip();
void autoChangeSpaceshipStatus(int, int, int);
void selectSpaceshipType(stSpaceship*);

//Misiones
void registerMission();
void saveMission(stMission);
int confirmMissionID(int);
void changeMissionStarshipID();
void changeMissionDetails();
void changeMissionShipment();
void changeMissionDestination();
void changeMissionCrewmanList();
void changeMissionStatus();
int selectMission();
void showMissions();
int getLastMissionID();
bool firstMission();
int getTotalMissions();

//Menu


//Otros
void pprintf(const char *str);

//Otros-> UserData
void changeColor();                                 //A - Permite cambiar el color de la consola se anexan las funciones A -
void textColorsOptions();                           //A - Muestra las Opciones de colores
void setColor(int colorCode);                       //A - Aplica uno de los colores
void colorOption(int option);                       //A - Aplica en un Switch el color elegido por parametro
void saveColorChange(int colorChoosed);             //A - Salva la eleccion del usuario
void readUserData();                                //  Busca los datos del usuario, si existe los aplica, si no, los crea por defecto
bool proceduralTextRead();                          //  Lee el registro del usuario, si este desea el texto procedural habilitado, retorna true, caso contrario, false
