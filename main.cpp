#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"

using namespace std;


int main(){

    ciudad * andynopolis = new ciudad;

    mostrar_menu();
    int opcion = elegir_opcion();

    while ( opcion != GUARDAR_SALIR ){

        mostrar_menu();
        opcion = elegir_opcion();
    }


    // liberar memoria 
    delete andynopolis;
    return 0;
}

