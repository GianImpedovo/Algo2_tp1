#include <iostream>
#include <fstream>
#include <string>
#include "menu.h"

using namespace std;

const string PIEDRA = "piedra";
const string MADERA = "madera";
const string METAL = "metal";
const int INEXISTENTE = -1;


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
    int edificio_elegido;
    string nombre_edificio;

    switch (opcion)
    {
    case LISTAR_MATERIAL:
        listar_materiales_construccion(andypolis);
        break;

    case CONSTRUIR_EDIFICIO:
        edificio_elegido = elegir_edificio(andypolis); 
        if ( edificio_elegido != INEXISTENTE ){
            if (existen_materiales(andypolis, edificio_elegido) && construccion_permitida(andypolis, edificio_elegido)){
                construir_edificio(andypolis, edificio_elegido);

                nombre_edificio = andypolis-> edificios[ edificio_elegido ] -> nombre;

                cout << "EDIFICIO : " << nombre_edificio;
                cout << " CONSTRUIDO" << endl;
            }
        } else {
            cout << "El edificio que desea construir no existe " << endl;
        }
        break;

    case LISTAR_EDIFICIOS_CONSTRUIDOS:
        listar_edificios_construidos(andypolis);
        break;

    case LISTAR_TODOS_EDIFICIOS:
        listar_todos_edificios(andypolis);
        break;
    case DEMOLER_EDIFICIO:
        demoler_edificio(andypolis);
        break;
    }
}

// proceso los archivos :

void procesar_archivo_materiales(ciudad * andypolis){
    ifstream archivo;
    archivo.open(ARCHIVO_MATERIALES);

    // inicio con 0 materiales cuando empiezo a leer el archivo
    int cantidad_materiales = 0;

    string nombre;
    float cantidad;

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
    float cantidad_piedra;
    float cantidad_madera;
    float cantidad_metal;
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

// 1) listar materiales : 

void listar_materiales_construccion(ciudad * andypolis){
    cout << "\n" << endl;
    for ( int i = 0; i < andypolis->cantidad_materiales; i++){
        cout << "Material " << i + 1 << " : " << andypolis->materiales[i]->nombre << " , ";
        cout << "Cantidad : " << andypolis->materiales[i]->cantidad << endl;
    }
}

// 2) construir edificio : 

int elegir_edificio(ciudad * andypolis){
    string edificio_elegido;
    cout << "Elegir edificio para construir : ";
    cin >> edificio_elegido;

    int posicion_edificio = -1;
    for ( int i = 0; i < andypolis -> cantidad_edificios; i++){
        if ( andypolis-> edificios[ i ] -> nombre == edificio_elegido){
            posicion_edificio = i;
        }
    }

    return posicion_edificio;
}

float obtener_cantidad_material(string material, ciudad * andypolis){
    float cantidad = 0;
    for ( int i = 0 ; i < andypolis->cantidad_materiales; i++){
        if ( andypolis->materiales[i]->nombre == material){
            cantidad = andypolis->materiales[i]->cantidad;
        }
    }
    return cantidad;
}

bool existen_materiales(ciudad * andypolis,int posicion_edificio){

    bool existen_materiales = false;

    float piedra_necesaria = andypolis-> edificios[ posicion_edificio ] -> cantidad_piedra;
    float madera_necesaria = andypolis-> edificios[ posicion_edificio ] -> cantidad_madera;
    float metal_necesario = andypolis-> edificios[ posicion_edificio ] -> cantidad_metal;

    float piedra_actual = obtener_cantidad_material(PIEDRA, andypolis);
    float madera_actual = obtener_cantidad_material(MADERA, andypolis);
    float metal_actual = obtener_cantidad_material(METAL, andypolis);

    if ( piedra_necesaria <= piedra_actual ){
        if ( madera_necesaria <= madera_actual){
            if (metal_necesario <= metal_actual){
                existen_materiales = true;
            }else{
                cout << "No tenes METAL suficiente " << endl;
            }
        }else {
            cout << "No tenes MADERA suficiente " << endl;
        }
    }else {
        cout << "No tenes PIEDRA suficiente " << endl;
    }


    return existen_materiales;
}

bool construccion_permitida(ciudad * andypolis,int posicion_edificio){
    bool construccion_permitida = false;
    int construcciones_existentes = andypolis-> edificios[ posicion_edificio] ->cantidad_construidos;
    int construcciones_permitidas = andypolis-> edificios[ posicion_edificio] ->max_permitidos;

    if ( construcciones_existentes < construcciones_permitidas ){
        construccion_permitida = true;
    } else {
        cout << "No se puede construir ya que supera el limite de cantidad de " << andypolis->edificios[ posicion_edificio]->nombre;
        cout << " construidos." << endl;
    }

    return construccion_permitida;
}

void construir_edificio(ciudad * andypolis,int posicion_edificio){ 
    // - eliminar la cantidad materiales usados [x] 
    // - sumar edificio al objeto edificio elegido [x]

    float piedra_usada = andypolis-> edificios[ posicion_edificio ]-> cantidad_piedra;
    float madera_usada = andypolis-> edificios[ posicion_edificio ]-> cantidad_madera;
    float metal_usado = andypolis-> edificios[ posicion_edificio ]-> cantidad_metal;

    for ( int i = 0; i < andypolis->cantidad_materiales; i++){
        if ( andypolis-> materiales[ i ]-> nombre == PIEDRA){
            andypolis-> materiales[ i ]-> cantidad -= piedra_usada;
        }
        else if ( andypolis-> materiales[ i ]-> nombre == MADERA){
            andypolis-> materiales[ i ]-> cantidad -= madera_usada;
        }
        else if ( andypolis-> materiales[ i ]-> nombre == METAL){
            andypolis-> materiales[ i ]-> cantidad -= metal_usado;
        }
    }

    andypolis-> edificios[ posicion_edificio ]-> cantidad_construidos += 1;
}

// 3) listar edificios construidos : 

void listar_edificios_construidos(ciudad * andypolis){
    for ( int i = 0; i < andypolis -> cantidad_edificios; i++){
        if ( andypolis -> edificios [ i ] ->cantidad_construidos > 0){
            int construidos = andypolis -> edificios [ i ] ->cantidad_construidos;
            string nombre = andypolis -> edificios [ i ] -> nombre;

            cout << nombre << " - " << construidos << endl; 

        }
    }
}

// 4) listar todos los edificios : 

void listar_todos_edificios(ciudad * andypolis){
    for ( int i = 0; i < andypolis -> cantidad_edificios; i++){
        string nombre = andypolis -> edificios[ i ] -> nombre;
        float madera = andypolis -> edificios[ i ] -> cantidad_madera;
        float piedra = andypolis -> edificios[ i ] -> cantidad_piedra;
        float metal = andypolis -> edificios[ i ] -> cantidad_metal;
        int construidos = andypolis -> edificios[ i ] -> cantidad_construidos;
        int maximo = andypolis -> edificios[ i ] -> max_permitidos;
        int restantes = maximo - construidos;

        cout << nombre << " -> madera : " << madera;
        cout << " - piedra: " << piedra;
        cout << " - metal : " << metal;
        cout << " - construidos : " << construidos;
        cout << " - se pueden construir : " << restantes << endl;

    }
}

// 5) demoler un edificio por nombre :

int obtener_posicion_material(string material, ciudad  * andypolis){
    int posicion = -1;
    for ( int i = 0; i < andypolis -> cantidad_materiales; i++){
        if ( material == andypolis -> materiales[i] ->nombre ){
            posicion = i;
        }
    }
    return posicion;
}

void sumar_materiales(ciudad * andypolis, int posicion_edificio){
            float madera_edificio = andypolis -> edificios[posicion_edificio] -> cantidad_madera;
            float piedra_edificio = andypolis -> edificios[posicion_edificio] -> cantidad_piedra;
            float metal_edificio = andypolis -> edificios[posicion_edificio] -> cantidad_metal;

            float madera_obtenida = madera_edificio / 2;
            float piedra_obtenida = piedra_edificio / 2;
            float metal_obtenido = metal_edificio / 2;

            int posicion_madera = obtener_posicion_material(MADERA,andypolis);
            int posicion_piedra = obtener_posicion_material(PIEDRA,andypolis);
            int posicion_metal = obtener_posicion_material(METAL,andypolis);

            andypolis -> materiales[posicion_madera] -> cantidad += madera_obtenida;
            andypolis -> materiales[posicion_piedra] -> cantidad += piedra_obtenida;
            andypolis -> materiales[posicion_metal] -> cantidad += metal_obtenido;

}

void demoler_edificio(ciudad * andypolis ){

    int posicion_edificio = elegir_edificio(andypolis);
    if ( posicion_edificio != INEXISTENTE){

        int cantidad_construidos = andypolis -> edificios[posicion_edificio] ->cantidad_construidos;
        string nombre_edificio = andypolis -> edificios[posicion_edificio] ->nombre;

        if ( cantidad_construidos > 0) {
            
            andypolis -> edificios[posicion_edificio] ->cantidad_construidos -= 1;

            sumar_materiales(andypolis, posicion_edificio);

            cout << "El edificio : " << nombre_edificio << " fue demolido." << endl;

        } else {
            cout << "Este edificio no tiene ninguna construccion " << endl;
        }

    }else {
        cout << "El edificio NO existe" << endl;
    }

}

// 6) guardar y salir: 

void actualizar_archivo_materiales(ciudad * andypolis){
    ofstream archivo;
    archivo.open(ARCHIVO_MATERIALES);

    int cantidad_materiales = andypolis -> cantidad_materiales;

    for ( int i = 0; i < cantidad_materiales; i++){
        archivo << andypolis ->materiales[i] ->nombre << ' '
                << andypolis ->materiales[i] ->cantidad << "\n";
        delete andypolis -> materiales[i];
        andypolis -> cantidad_materiales--;
        
    }
    delete [] andypolis->materiales;
    andypolis -> materiales = nullptr;

    archivo.close();
    cout << "archivo materiales actualizado" << endl;
}

void actualizar_archivo_edificios(ciudad * andypolis){
    ofstream archivo;
    archivo.open(ARCHIVO_EDIFICIOS);

    int cantidad_edificios = andypolis -> cantidad_edificios;

    for (int i = 0; i < cantidad_edificios; i++){
        archivo << andypolis ->edificios[i] ->nombre << ' '
                << andypolis ->edificios[i] ->cantidad_piedra << ' '
                << andypolis ->edificios[i] ->cantidad_madera << ' '
                <<  andypolis ->edificios[i] ->cantidad_metal << ' '
                << andypolis ->edificios[i] ->cantidad_construidos << ' '
                << andypolis ->edificios[i] ->max_permitidos << '\n';
        delete andypolis->edificios[i];
        andypolis -> cantidad_edificios--;
    }
    delete [] andypolis -> edificios;
    andypolis -> edificios = nullptr;

    archivo.close();
    cout << "archivo edificios actualizado" << endl;
}

