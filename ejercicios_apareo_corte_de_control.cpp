/* Ejercicio:
    Una empresa de transporte cuenta con camiones de diferente tamaño.
    Al finalizar el día se cuenta con los datos de cada viaje ordenados por patente en forma ascendente:

    - Patente
    - Hora de inicio
    - Hora de fin
    - Kilómetros recorridos
    - Importe

    Y en forma separada, los datos de cada vehículo:

    - Patente
    - Modelo
    - Consumo por kilómetro

    Para escribir el código, se asume que los datos ya están cargados en vectores estáticos y que cada vector tiene una variable asociada que indica la cantidad de elementos cargados.
    Se asume que cada vehículo realiza al menos un viaje en el día.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct Vehiculo {
    string patente;
    string modelo;
    float consumo_por_km;
};

struct Viaje {
    string patente;
    int hora_de_inicio;
    int hora_de_fin;
    float km_recorridos;
    float importe;
};

const int CANT_VEHICULOS = 10;
const int CANT_VIAJES = 20;

// 1) Escribir una función que ordene el vector de vehículos por modelo (ordenamiento burbuja).
void ordenar_vehiculo_por_modelo (Vehiculo vehiculos[], int len_vehiculos){
    bool ordenado = false;
    int i=0;
    while(i<len_vehiculos && !ordenado){
        ordenado = true;
        for(int j=0; j < len_vehiculos-i-1; j++ ){
            if(vehiculos[j].modelo > vehiculos[j+1].modelo){
                Vehiculo aux = vehiculos[j+1];
                vehiculos[j+1] = vehiculos[j];
                vehiculos[j] = aux;
                ordenado = false;
            }
        }
        i++;
    }
    return;
}

void ordenar_vehiculo_por_patente (Vehiculo vehiculos[], int len_vehiculos){
    bool ordenado = false;
    int i=0;
    while(i<len_vehiculos && !ordenado){
        ordenado = true;
        for(int j=0; j < len_vehiculos-i-1; j++ ){
            if(vehiculos[j].patente > vehiculos[j+1].patente){
                Vehiculo aux = vehiculos[j+1];
                vehiculos[j+1] = vehiculos[j];
                vehiculos[j] = aux;
                ordenado = false;
            }
        }
        i++;
    }
    return;
}

// 2) Escribir una función que busque en el vector de vehículos por patente y devuelva la posición en el vector (búsqueda binaria).
// Devuelve el indice de la patente a buscar o -1 en caso de no encontrarla
int buscar_indice_patente (Vehiculo vehiculos[], int len_vehiculos, string patente_a_buscar){
    int inicio = 0, fin = len_vehiculos-1;
    int ret = -1;
    while(fin >= inicio && ret == -1){
        int medio = inicio + (fin-inicio)/2;

        if(vehiculos[medio].patente == patente_a_buscar){
            ret = medio;
        } else if (vehiculos[medio].patente > patente_a_buscar){
            fin = medio-1;
        } else {
            inicio = medio + 1;
        }
    }
    
    return ret;
}

// 3) Escribir una función que calcule el costo total del combustible utilizado por todos los camiones en el día.
float combustible_total_utilizado (Viaje viajes[], Vehiculo vehiculos[], int len_viajes, int len_vehiculos){
    //costo de 1 vehiculo = km_recorridos * consumo_por_km;
    float consumo_total = 0.00;
    for(int i = 0; i < len_viajes; i++){
        int index = buscar_indice_patente(vehiculos,len_vehiculos, viajes[i].patente);
        if(index>=0){
            consumo_total += viajes[i].km_recorridos * vehiculos[index].consumo_por_km;
            // Para chequear el consumo total, desconemtar las 2 siguientes lineas:
            //cout << "\nviajes[" << i << "].km_recorridos: " << viajes[i].km_recorridos << " * vehiculos[" << index << "].consumo_por_km: " << vehiculos[index].consumo_por_km << " = " << viajes[i].km_recorridos * vehiculos[index].consumo_por_km;
            //cout << "\nConsumo total:" << consumo_total;
        }
    }
    return consumo_total;
}

// 4) Escribir una función que indique la patente del vehículo con mejor y peor rendimiento, de acuerdo al consumo total de combustible en relación con el total de los importes cobrados por los viajes.
void peor_y_mejor_rendimiento (Viaje viajes[], Vehiculo vehiculos[], int len_viajes, int len_vehiculos){
    int indice_mejor_rendimiento = -1;
    int indice_peor_rendimiento = -1;
    float mejor_rendimiento = -1, peor_rendimiento = 9999.99;
    int i=0;
    while(i < len_viajes){
        int index = buscar_indice_patente(vehiculos,len_vehiculos, viajes[i].patente);
        if(index == -1){
            cout << "No hay vehiculo registrado para la patente del vehiculo que realizo este viaje." << endl;
        } else {

            string key = vehiculos[index].patente;
            float consumo_por_vehiculo = 0.00;
            float total_importes_por_vehiculo = 0.00;
    
            // Utilizo index de key
            while( key == viajes[i].patente && i < len_viajes){
                consumo_por_vehiculo += viajes[i].km_recorridos * vehiculos[index].consumo_por_km;
                total_importes_por_vehiculo += viajes[i].importe;
    
                i++;
            }
            float rendimiento = 0.00;
            if(consumo_por_vehiculo != 0){
                // rendimiento = importe / consumo_del_vehiculo; (cuanto importe obtengo cada litro de combustible utilizado)
                rendimiento = total_importes_por_vehiculo/consumo_por_vehiculo;
                if(rendimiento < peor_rendimiento){
                    peor_rendimiento = rendimiento;
                    indice_peor_rendimiento = index;
                } // Si pongo "else if", y la primer patente es la de mayor rendimiento, no la va a tomar.
                if(rendimiento > mejor_rendimiento){
                    mejor_rendimiento = rendimiento;
                    indice_mejor_rendimiento = index;
                }
            }
            /*
            Para facilitar chequeo, descomentar.
            cout << "\nKey: " << key;
            cout << "\nconsumo_por_vehiculo:" << consumo_por_vehiculo;
            cout << "\ntotal_importes_por_vehiculo:" << total_importes_por_vehiculo;
            cout << "\nrendimiento:" << rendimiento;
            cout << "\nmejor_rendimiento:" << mejor_rendimiento;
            cout << "\npeor_rendimiento:" << peor_rendimiento << endl;
            */
        }
    }

    if(indice_mejor_rendimiento != -1){
        cout << "\n Mejor rendimiento:\n    - vehiculo con patente: " << vehiculos[indice_mejor_rendimiento].patente << endl;
        cout << "     - Rendimiento de: " << fixed << setprecision(2) << mejor_rendimiento <<"$/L." << endl;   
    } else {
        cout << "\n     No se ha encontrado viaje con mejor rendimiento" << endl;
    }
    if(indice_peor_rendimiento != -1){
        cout << "\n Peor rendimiento:\n     - vehiculo con patente: " << vehiculos[indice_peor_rendimiento].patente << endl;  
        cout << "     - Rendimiento de: " << fixed << setprecision(2) << peor_rendimiento <<"$/L." << endl;
    } else {
        cout << "\n     No se ha encontrado viaje con peor rendimiento" << endl;
    }
    return;
}

void mostrar_vehiculos(Vehiculo vehiculos[], int len_vehiculos){
    cout << "Vehiculos: [";
    for(int i=0; i<len_vehiculos; i++){
        cout << "\n     (patente numero " << i+1 << " : " << vehiculos[i].patente;
        cout << "; modelo : " << vehiculos[i].modelo;
        if(i==len_vehiculos-1){
            cout << "; consumo_por_km :" << vehiculos[i].consumo_por_km <<")\n]" << endl;
        } else {
            cout << "; consumo_por_km :" << vehiculos[i].consumo_por_km <<"),";
        }
    }
    return;
}

void mostrar_viajes(Viaje viajes[], int len_viajes){
    cout << "\nVehiculos: [";
    for(int i=0; i<len_viajes; i++){
        cout << "\n     (patente " << i+1 << " : " << viajes[i].patente;
        cout << "; hora_de_inicio : " << viajes[i].hora_de_inicio;
        cout << "; hora_de_fin : " << viajes[i].hora_de_fin;
        cout << "; km_recorridos : " << viajes[i].km_recorridos;
        if(i==len_viajes-1){
            cout << "; importe :" << viajes[i].importe <<")\n]" << endl;
        } else {
            cout << "; importe :" << viajes[i].importe <<"),";
        }
    }
    return;
}

int main() {
    Vehiculo vehiculos[] = {
        {"AD012EF", "Fiat Cronos", 2.5f},
        {"AE345GH", "Peugeot 208", 2.2f},
        {"AB456CD", "Ford Ranger", 4.0f},
        {"AC789DE", "Volkswagen Amarok", 3.8f},
        {"AF678IJ", "Renault Kangoo", 3.0f},
        {"AG901KL", "Ford Focus", 2.8f},
        {"AH234MN", "Mercedes Sprinter", 4.5f},
        {"AI567OP", "Ford Fiesta", 2.6f},
        {"AA123BB", "Toyota Hilux", 4.2f},
        {"AJ890QR", "Volkswagen Polo", 2.3f}
    };
    const int len_vehiculos = CANT_VEHICULOS;

    Viaje viajes[] = {
        {"AA123BB", 800, 1000, 100, 1500},
        {"AA123BB", 1100, 1300, 50, 600},   
        {"AB456CD", 900, 1100, 80, 1000},
        {"AB456CD", 1400, 1600, 120, 1800},
        {"AC789DE", 700, 900, 60, 900},
        {"AC789DE", 1000, 1200, 40, 500},
        {"AD012EF", 1000, 1200, 150, 1500},
        {"AD012EF", 1300, 1500, 70, 800},
        {"AE345GH", 900, 1100, 90, 1200},
        {"AE345GH", 1200, 1400, 110, 1500},
        {"AF678IJ", 800, 1000, 70, 900},
        {"AF678IJ", 1300, 1500, 80, 1100},
        {"AG901KL", 900, 1100, 130, 1700},
        {"AG901KL", 1400, 1600, 100, 1200},
        {"AH234MN", 700, 900, 50, 750},
        {"AH234MN", 1000, 1200, 30, 400},
        {"AI567OP", 800, 1000, 100, 1300},
        {"AI567OP", 1100, 1300, 60, 750},
        {"AJ890QR", 900, 1100, 80, 1100},
        {"AJ890QR", 1200, 1400, 70, 950}
    };
    const int len_viajes = CANT_VIAJES;

    cout << "--- Inicio de Pruebas ---" << endl;

    cout << "\n1) Ordeno vehiculos por modelo:" << endl;
    cout << "\nLista de vehiculos antes de ordenar:" << endl;
    mostrar_vehiculos(vehiculos, len_vehiculos);
    ordenar_vehiculo_por_modelo(vehiculos, len_vehiculos);
    cout << "\nLista de vehiculos despues de ordenar:" << endl;
    mostrar_vehiculos(vehiculos, len_vehiculos);


    cout << "\n2) Busco patente AC789DE:" << endl;
    // Ordeno vehiculos por patente para que funcione correctamente.
    ordenar_vehiculo_por_patente(vehiculos, len_vehiculos);
    string patente_a_buscar1 = "AC789DE";
    int index = buscar_indice_patente(vehiculos, len_vehiculos, patente_a_buscar1);
    if (index != -1) {
        cout << "   Patente " << patente_a_buscar1 << " encontrada en indice " << index << ". Modelo: " << vehiculos[index].modelo << endl;
    } else {
        cout << "   Patente " << patente_a_buscar1 << " no encontrada." << endl;
    }

    cout << "\n3) Calculo combustible total utilizado:" << endl;
    float total_combustible = combustible_total_utilizado(viajes, vehiculos, len_viajes, len_vehiculos);
    cout << "   Costo total de combustible utilizado: " << total_combustible << " L " << endl;

    cout << "\n4) Calculo rendimiento de vehiculos:" << endl;
    peor_y_mejor_rendimiento(viajes, vehiculos, len_viajes, len_vehiculos);

    cout << "\n--- Fin de Pruebas ---" << endl;

    return 0;
}