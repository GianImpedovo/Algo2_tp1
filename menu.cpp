#include <iostream>
#include <fstream>
#include "menu.h"

using namespace std;



void mostrar_menu(){
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



void procesar_opcion(int opcion){
    switch (opcion)
    {
    case LISTAR_MATERIAL:
        /* code */
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

void procesar_archivo_materiales(ciudad* andynopolis){
    ifstream archivo;
    archivo.open(ARCHIVO_MATERIALES);

    string nombre;
    int cantidad;

    while (archivo >> nombre){
        archivo >> cantidad;

        

    }

    archivo.close();

}