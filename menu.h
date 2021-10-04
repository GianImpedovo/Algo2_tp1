#if !defined(MENU_H)
#define MENU_H

#include <iostream>
#include <string>

using namespace std;

const string ARCHIVO_MATERIALES = "materiales.txt";
const string ARCHIVO_EDIFICIOS = "edificios.txt";
int const LISTAR_MATERIAL = 1;
int const CONSTRUIR_EDIFICIO = 2;
int const LISTAR_EDIFICIOS_CONSTRUIDOS = 3;
int const LISTAR_TODOS_EDIFICIOS = 4;
int const DEMOLER_EDIFICIO = 5;
int const GUARDAR_SALIR = 6;

struct material
{
    string nombre;
    float cantidad;
};

struct edificio
{
    string nombre;
    float cantidad_madera;
    float cantidad_piedra;
    float cantidad_metal;
    int cantidad_construidos;
    int max_permitidos;
};

struct ciudad
{
    material ** materiales;
    int cantidad_materiales;
    edificio ** edificios;
    int cantidad_edificios;
};


// Pre: -  
// Pos: Imprime por terminal el menu de opciones
void mostrar_menu();

// Pre: - 
// Pos: Devuelve la opcion elegida , ya validada , del usuario.
int elegir_opcion();

// Pre: Recibe el puntero ciudad ya creado.
// Pos: Guarda la informacion del archivo materiales dentro de la struct ciudad.
void procesar_archivo_materiales(ciudad * andypolis);

// Pre: Recibe el puntero ciudad ya creado.
// Pos: Guarda la informacion del archivo edificios dentro de la struct ciudad.
void procesar_archivo_edificios(ciudad * andypolis);

// Pre: 0 < opcion < 6 , y la ciudad andynopolis con los archivos ya procesados 
// Pos: Se dirige a la opcion elegida por el usuario.
void procesar_opcion(int opcion, ciudad * andypolis);

// Pre: Recibe la ciudad para utilizar la parte de los materiales, el vector materiales.
// Pos: - 
void listar_materiales_construccion(ciudad * andypolis);

// Pre: - 
// Pos: Devuelve la posicion del edificio solicitado por el usuario.
int elegir_edificio(ciudad * andypolis);

// Pre: - 
// Pos: Devuelve la cantidad de materiales que se encuentran para utilizar.
float obtener_cantidad_material(string material, ciudad * andypolis);


// Pre: - 
// Pos: Verifica si existen la cantidad de materiales necesarios.
bool existen_materiales(ciudad * andypolis,int posicion_edificio_elegido);

// Pre: - 
// Pos: Verifica que no se supere la cantidad de edificios disponibles para construir.
bool construccion_permitida(ciudad * andypolis,int posicion_edificio);

// Pre: - 
// Pos: Devuelve la posicion del material al cual le suma 
int obtener_posicion_material(string material, ciudad  * andypolis);

// Pre: - 
// Pos: Suma al edificio una construiccion y elimina los materiales usados.
void sumar_edificio(ciudad * andypolis , int posicion_edificio);

// Pre: cantidad_edificios > Posicion_edificio > -1 
// Pos: Elimina la cantidad de materiales usados y agrega un edificio a la cantidad de edificios cosntruidos.
void construir_edificio(ciudad * andypolis,int posicion_edificio);

// Pre: - 
// Pos: Lista edificios construidos al menos 1 vez.
void listar_edificios_construidos(ciudad * andypolis);


// Pre: - 
// Pos: Lista todos los edificios con sus materiales necesarios , cuantos fueron cosntruidos y 
//      cuantos puedo construir.
void listar_todos_edificios(ciudad * andypolis);

// Pre: - 
// Pos: Reintegro los materiales obtenidos luego de la demolicion.
void sumar_materiales(ciudad * andypolis, int posicion_edificio);

// Pre: - 
// Pos: Obtengo la posicion del edificio, le resto una construccion 
//      y retorno la mitad de los materiales utilizados
void demoler_edificio(ciudad * andypolis );

// Pre: - 
// Pos: Actualizo el archivo: "materiales.txt" con las ultimas modificaciones y libero la memoria.
void actualizar_archivo_materiales(ciudad * andypolis);

// Pre: - 
// Pos: Actualizo el archivo: "edificios.txt" con las ultimas modificaciones y libero la memoria.
void actualizar_archivo_edificios(ciudad * andypolis);


#endif // MENU_H
