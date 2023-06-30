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
    int crewmen[dimInt];    //Lista de IDs de los tripulantes
    char mission_details[dimChar]; //breve descripcion
    int crewman_amount;     //total de tripulantes
} stMission;

typedef struct
{
    int consoleColor;
    bool proceduralText;
} stUserData;

//Astronautas
void registerAstronaut();                   // Registra un astronauta
void saveAstronaut(stAstronaut user);       // Guarda los datos de un astronauta en el sistema
bool confirmAstronautID(int ID);            // Verifica si existe un astronauta con el ID dado
void changeAstronautNickname();             // Cambia el apodo de un astronauta
void changeAstronautAge();                  // Cambia la edad de un astronauta
void changeAstronautSpeciality();           // Cambia la especialidad de un astronauta
void changeAstronautFlightTime();           // Cambia el tiempo de vuelo de un astronauta
void changeAstronautHoursSpaceStation();    // Cambia las horas en la estación espacial de un astronauta
void changeAstronautAmmountMissions();      // Cambia la cantidad de misiones realizadas por un astronauta
void changeAstronautStatus();               // Cambia el estado de un astronauta
int selectAstronaut();                      // Selecciona un astronauta existente
void showAstronauts();                      // Muestra la lista de todos los astronautas registrados
void showAstronautByID();                   // Muestra los datos de un astronauta específico según su ID
bool firstAstronaut();                      //Verifica si hay un astronauta registrado

//Naves
void saveSpaceship(stSpaceship spaceship);                              // Guarda en la ultima posicion del archivo la nave recibida por parametro
void registerSpaceship();                                               // Carga de datos y en archivo una nueva nave. Con parametros en automatico
void selectSpaceshipType(stSpaceship *type);                            // Permite seleccionar el tipo de nave y asignarlo al puntero type
int getLastSpaceshipID();                                               // Obtiene la ultima ID del registro
void changeSpaceshipStatus();                                           // Cambia el estado de la nave
bool isOnMission(int ID);                                               // Verifica si la nave con el ID dado está en misión
int changeSpaceshipStatusOptions();                                     // Retorna el estado de la nave elegida, 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
void showSpaceshipByID();                                               // Verifica si la nave existe, la busca y permite modificar sus datos o visualizarla
void showSpaceship(int ID);                                             // Muestra una nave por su ID
bool spaceshipExistByID(int ID);                                        // Retorna verdadero si la nave existe en el archivo en base al ID Recibido
void printSpaceshipData(stSpaceship spaceship);                         // Imprime por pantalla los datos de la nave
void printSpaceshipStatus(int spaceshipStatus);                         // 1 lista para su uso, 2 en mision, 3 en mantenimiento, 4 de baja
int spaceshipStatus(int ID);                                            // Retorna el estado de la nave
void showAllSpaceships();                                               // Muestra todas las naves cargadas en el archivo
void showFlightTime(int ID);                                            // Muestra el tiempo de vuelo por ID
void showFlightsAmount(int ID);                                         // Muestra la cantidad de vuelos de una nave
void changeSpaceshipFlightsAmount();                                    // Cambia la cantidad de vuelos de la nave
int selectSpaceship();                                                  // Selecciona una nave y retorna la posicion de la misma
int getTotalSpaceships();                                               // Retorna la cantidad total de registros de naves
void changeSpaceshipFlightTime();                                       // Cambia la cantidad de horas de vuelo de la nave
bool firstSpaceShip();                                                  // Verifica si hay al menos una nave registrada
void autoChangeSpaceshipStatus(int IDsearch, int flag, int option);     // Cambia el estado de una nave automáticamente cuando una misión es retornada, falla o se cancela, 1 lista para su uso, 2 en misión, 3 en mantenimiento, 4 de baja

//Misiones
void registerMission();
void saveMission(stMission);
int confirmMissionID(int);
int selectMission();
void changeMissionStarshipID();
void changeMissionDetails();
void changeMissionShipment();
void changeMissionDestination();
void changeMissionCrewmanList();
void changeMissionStatus();
void showMissions();
int getLastMissionID();
bool firstMission();
int getTotalMissions();
void showMissionsByID();
bool isValidSpaceshipID(int, stSpaceship*, int);
bool isValidDestination(int);
bool isValidShipment(int);
bool isAstronautInMission(int, stMission*, int);

//Menu
void mainMenu();
void systemMenu();
void astronautMenu();
void modifyAstronautMenu();
void consultAsMenu();
void spaceshipMenu();
void consultSpMenu();
void modifySpMenu();
void missionMenu();
void consultMissionMenu();
void modifyMissionMenu();
void optionsMenu();
void infoMenu();


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
bool inThere(int, int[], int);
