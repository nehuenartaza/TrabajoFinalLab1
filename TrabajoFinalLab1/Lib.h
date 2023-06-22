#include <stdio.h>


#define dimInt 15
#define dimChar 50
//Aca van los prototipados y estructuras



typedef struct {
	char nombre[dimChar];
	char apellido[dimChar];
	char apodo[dimChar];
	int ID;
	int edad;
	char nacionalidad[dimChar];
	char especialidad[dimChar];
	int horas_vuelo;
	int misiones;
	int horas_estacion_espacial;
	int estado; //1-activo, 2-retirado
} STastronauta;
typedef struct {
	int ID;
	int tipo_nave; //1-Starship, 2-Falcon 9, 3-Falcon Heavy
	int vuelos;
	int horas_vuelo;
	int estado; //0-mantenimiento, 1-lista para usar, 2-en uso, 3-de baja
} STnave;
typedef struct {
	int ID;
	int ID_nave;
	int estado; //1-listo, 2-en vuelo, 3-retornada, 4-cancelada, 5-fallida
	int destino; //1-EEI, 2-orbita terrestre, 3-luna
	int cargamento; //1-satelite, 2-insumos para la EE
	int tripulantes[dimInt];
	char detalle_mision[dimChar]; //breve descripcion
	int cant_tripulantes;
} STmision;

