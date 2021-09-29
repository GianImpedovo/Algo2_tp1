#include <iostream>
#include <fstream>
#include "menu.h"

using namespace std;



void mostrar_menu(){
    cout << "\n" << endl;
    cout << "1. Listar materiales de construcción. " << endl;
    cout << "2. Construir edificio por nombre." << endl;
    cout << "3. Listar los edificios construidos." << endl;
    cout << "4. Listar todos los edificios." << endl;
    cout << "5. Demoler un edificio por nombre." << endl;
    cout << "6. Guardar y salir. " << endl;

}

bool opcion_valida(int opcion){
    if ( opcion <= 0 || opcion > 6){
        return false;
    }else {
        return true;
    }
}

int elegir_opcion(){
    // validar la opcion elegida por el usuario: 
    int opcion;

    cout << " -> ";
    cin >> opcion;

    while (!opcion_valida(opcion)){
        cout << "Ingrese una opcion valida : ";
        cin >> opcion;
    }

    return opcion;
}



void procesar_opcion(int opcion, ciudad * andypolis){
    switch (opcion)
    {
    case LISTAR_MATERIAL:
        listar_materiales_construccion(andypolis);
        break;
    case CONSTRUIR_EDIFICIO:
        /* code */
        break;
    case LISTAR_EDIFICIOS_CONSTRUIDOS:
        /* code */
        break;
    case LISTAR_TODOS_EDIFICIOS:
        /* code */
        break;
    case DEMOLER_EDIFICIO:
        /* code */
        break;
    }
}

void procesar_archivo_materiales(ciudad * andypolis){
    ifstream archivo;
    archivo.open(ARCHIVO_MATERIALES);

    // inicio con 0 materiales cuando empiezo a leer el archivo
    int cantidad_materiales = 0;

    string nombre;
    int cantidad;

    while (archivo >> nombre){
        archivo >> cantidad;

        material * nuevo_material;

        nuevo_material = new material;
        nuevo_material->nombre = nombre;
        nuevo_material->cantidad = cantidad;

        material ** vector_materiales = new material * [cantidad_materiales + 1];

        if ( cantidad_materiales == 0){
            vector_materiales[cantidad_materiales] = nuevo_material;
            andypolis->materiales = vector_materiales;
        } else {
            for ( int i = 0; i < cantidad_materiales ; i++){
                vector_materiales[i] = andypolis->materiales[i];
            }
            vector_materiales[cantidad_materiales] = nuevo_material;
            delete [] andypolis->materiales;
            andypolis->materiales = vector_materiales;
        }
        cantidad_materiales++;
        

    }
    andypolis->cantidad_materiales = cantidad_materiales;

    archivo.close();

}

void procesar_archivo_edificios(ciudad * andypolis){
    ifstream archivo;
    archivo.open(ARCHIVO_EDIFICIOS);

    // inicio con 0 materiales cuando empiezo a leer el archivo
    int cantidad_edificios = 0;

    string nombre_edificio;
    int cantidad_piedra;
    int cantidad_madera;
    int cantidad_metal;
    int construidos;
    int maximo;


    while (archivo >> nombre_edificio){
        archivo >> cantidad_piedra;
        archivo >> cantidad_madera;
        archivo >> cantidad_metal;
        archivo >> construidos;
        archivo >> maximo;

        edificio * nuevo_edificio;

        nuevo_edificio = new edificio;

        nuevo_edificio->nombre = nombre_edificio;
        nuevo_edificio->cantidad_piedra = cantidad_piedra;
        nuevo_edificio->cantidad_madera = cantidad_madera;
        nuevo_edificio->cantidad_metal = cantidad_metal;
        nuevo_edificio->cantidad_construidos = construidos;
        nuevo_edificio->max_permitidos = maximo;

        edificio ** vector_edificio = new edificio * [ cantidad_edificios + 1];

        if ( cantidad_edificios == 0){
            vector_edificio[cantidad_edificios] = nuevo_edificio;
            andypolis->edificios = vector_edificio;
        } else {
            for ( int i = 0; i < cantidad_edificios; i++){
                vector_edificio[i] = andypolis->edificios[i];
            }
            vector_edificio[cantidad_edificios] = nuevo_edificio;
            delete [] andypolis->edificios;
            andypolis->edificios = vector_edificio;
        }
        cantidad_edificios++;

    }
    andypolis->cantidad_edificios = cantidad_edificios;

    archivo.close();
}

void listar_materiales_construccion(ciudad * andypolis){
    cout << "\n" << endl;
    for ( int i = 0; i < andypolis->cantidad_materiales; i++){
        cout << "Material " << i + 1 << " : " << andypolis->materiales[i]->nombre << " , ";
        cout << "Cantidad : " << andypolis->materiales[i]->cantidad << endl;
    }
}

