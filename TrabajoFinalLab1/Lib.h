#include <stdio.h>
#define dimInt 15
#define dimChar 50
#define Fastronauts "astronauts.bin"
#define Fships "ships.bin"
#define Fmissions "missions.bin"
//aca van los prototipados y estructuras
void register_astronaut();
void save_astronaut(STastronaut);
int confirm_astronaut_ID(int);
void modify_astronauts();
void show_astronauts();




void draw_mainmenu();
void drawmenu_1();
void drawmenu_2();
void drawmenu_3();
void drawmenu_4();

typedef struct {
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
} STastronaut;
typedef struct {
	int ID;
	int type_ship; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
	int ammount_flights;
	int hours_flight;
	int status; //0-mantenimiento, 1-lista para usar, 2-en uso, 3-de baja
} STship;
typedef struct {
	int ID;
	int ID_ship;
	int status; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
	int destiny; //1-EEI, 2-orbita terrestre, 3-luna
	int shipment; //1-satelite, 2-insumos para la EE
	int crewmans[dimInt];
	char details_of_mission[dimChar]; //breve descripcion
	int ammount_crewmans;
} STmission;
