#include "menu.h"

using namespace std;


int main(){

    ciudad * andypolis = new ciudad;
    procesar_archivo_materiales(andypolis);
    procesar_archivo_edificios(andypolis);

    cout << "\n\t ### Bienvenido a Andynopolis ! ### \n" << endl;

    mostrar_menu();
    int opcion = elegir_opcion();

    while ( opcion != GUARDAR_SALIR ){

        procesar_opcion(opcion, andypolis);

        mostrar_menu();
        opcion = elegir_opcion();
    }

    actualizar_archivo_materiales(andypolis);
    actualizar_archivo_edificios(andypolis);

    // Libero memoria
    delete andypolis;

    return 0;
}

