#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"

using namespace std;


int main(){

    ciudad * andypolis = new ciudad;
    procesar_archivo_materiales(andypolis);
    procesar_archivo_edificios(andypolis);

    mostrar_menu();
    int opcion = elegir_opcion();

    while ( opcion != GUARDAR_SALIR ){

        procesar_opcion(opcion, andypolis);

        for ( int i = 0; i < andypolis->cantidad_materiales; i++){
            cout << andypolis->materiales[i]->cantidad;
        }

        mostrar_menu();
        opcion = elegir_opcion();
    }


    // liberar memoria 
    delete andypolis;
    return 0;
}

