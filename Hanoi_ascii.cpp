#include <iostream>
#include <stdio.h>
using namespace std;

void ImpresionGrafica(int*, int, int, int);
void MovimientoDiscos(int *, int, int, int, int, int);
void TorresDeHanoi(int*, int, int, int, int, int, int, int);

int main(){
    int filas, columnas, *matriz = NULL, numdisc, num;
    filas = 3;
    numdisc = 1;
    // Se solicita la cantidad de discos a mover
    cout << "Ingrese la cantidad de discos: ";
    cin >> columnas;
    matriz = (int*) malloc(sizeof(int) * filas * columnas);
    // En la matriz hay tres agujas, por lo que se dejan los discos en una de ellas
    // y en las otras dos se les asigna un 0 por lo que se recorre toda la matriz
    for (int i = 0; i < filas; i++){
        for (int j = columnas - 1; j >= 0; j--){
            if (i == 0){
                matriz[(columnas * i) + j] = numdisc;
                numdisc += 2;
            } else{
                matriz[(columnas * i) + j] = 0;
            } // Fin If
        } // Fin For
    } // Fin For
    num = numdisc;
    // Metodo de la impresion grafica en la terminal
    ImpresionGrafica(matriz, filas, columnas, num);
    // Metodo donde esta el juego "Torres de Hanoi"
    TorresDeHanoi(matriz, filas, columnas, columnas, num, 0, 1, 2);
} // Fin Main

// Metodo el cual se encarga de imprimir graficamente el movimiento de las torres, 
// los discos estan representados por el caracter "▄",
// lo que no es un disco es representado con un espacio " "
// Parametros:
// - *matriz: Apuntador de la matriz de tipo entero, esta se maneja como un tablero
//   para poder hacer las respectivas impresiones
// - filas: Numero de filas dentro de la matriz
// - columnas: Numero de columnas dentro de la matriz
// - num: Numero dentro de la matriz el cual esta utilizando el disco mas grande

void ImpresionGrafica(int* matriz, int filas, int columnas, int num){
    int espacio;
    // Recorrido dentro de la matriz
    for (int i = columnas - 1; i >= 0; i--){
        for (int j = 0; j < filas; j++){
            espacio = (num - matriz[columnas * j + i]) / 2;
            // Impresion de los espacios en el lado izquierdo
            for (int k = 0; k < espacio; k++){
                cout << " ";
            } // Fin For
            // Impresion de los discos
            for (int k = 0; k < matriz[columnas * j + i]; k++){
                // Esta impresion esta hecha con printf para que ese caracter 
                // especial se pudiera imprimir
                printf("%c", 220);
            } // Fin For
            // Impresion de los espacios en el lado derecho
            for (int k = 0; k < espacio; k++){
                cout << " ";
            } // Fin For
        cout << "\t"; 
        } // Fin For
        cout << "\n";
    } // Fin For
} // Fin Impresion Grafica

// Metodo que hace el movimiento de los discos (inicial a destino)
// Parametros:
// - *matriz: Apuntador de la matriz de tipo entero, esta se maneja como un tablero 
//   para poder hacer las respectivas impresiones
// - filas: Numero de filas dentro de la matriz
// - columnas: Numero de columnas dentro de la matriz
// - num: Numero dentro de la matriz el cual esta utilizando el disco mas grande
// - agujaInicial: Aguja (fila) dentro de la matriz que nos dice en donde esta el disco a mover
// - agujaDestino: Aguja (fila) dentro de la matriz que nos dice en donde hay que colocar el disco a mover

void MovimientoDiscos(int* matriz, int filas, int columnas, int num, int agujaInicial, int agujaDestino){
    int columnaInicial, columnaDestino;
    columnaInicial = columnas - 1;
    columnaDestino = columnas - 1;
    // Se busca el disco que este mas arriba en la aguja inicial, o sea el disco mas pequeño en esa aguja
    while (columnaInicial >= 0 && matriz[columnas * agujaInicial + columnaInicial] == 0){
        columnaInicial--;
    } // Fin While
    if (columnaInicial < 0){
        columnaInicial = 0;
    } // Fin If
    // Teniendo el disco mas pequeño a mover, se busca en la aguja de destino el espacio mas
    // arriba para colocar dicho disco. 
    // Siempre respetando que ningun disco mas grande este por encima de uno mas pequeño
    while (columnaDestino >= 0 && matriz[columnas * agujaDestino + columnaDestino] == 0){
        columnaDestino--;
    } // Fin While
    // Con las posiciones identificadas se hace el respectivo cambio del disco en la matriz, 
    // el disco se mueve de la fila inicial hacia la fila del destino
    matriz[columnas * agujaDestino + columnaDestino + 1] = matriz[columnas * agujaInicial + columnaInicial];
    matriz[columnas * agujaInicial + columnaInicial] = 0;
    // Llamado de la impresion grafica, el cual imprime la matriz
    ImpresionGrafica(matriz, filas, columnas, num);
} // Fin Movimiento Discos

// Metodo recursivo que hace el juego de las Torres de Hanoi (el intercambio de discos en las diferentes agujas)
// Parametros:
// - *matriz: Apuntador de la matriz de tipo entero, esta se maneja como un tablero para
//   poder hacer las respectivas impresiones
// - filas: Numero de filas dentro de la matriz
// - columnas: Numero de columnas dentro de la matriz
// - numdisc: Numero de discos utilizados
// - num: Numero dentro de la matriz el cual esta utilizando el disco mas grande
// - agujaInicial: Aguja (fila) en donde inicialmente comienza el juego
// - agujaTemporal: Aguja (fila) en donde temporalmente se pondran los discos para poder hacer el juego
// - agujaDestino: Aguja (fila) en donde se trasladaran todos los discos y estaran colocodos del mayor al menor

void TorresDeHanoi(int* matriz, int filas, int columnas, int numdisc, int num, 
int agujaInicial, int agujaTemporal, int agujaDestino){
    if (numdisc == 1){
        // Caso Base
        MovimientoDiscos(matriz, filas, columnas, num, agujaInicial, agujaDestino);
    } else {
        // Recursividad
        TorresDeHanoi(matriz, filas, columnas, numdisc - 1, num, agujaInicial, agujaDestino, agujaTemporal);
        MovimientoDiscos(matriz, filas, columnas, num, agujaInicial, agujaDestino);
        TorresDeHanoi(matriz, filas, columnas, numdisc - 1, num, agujaTemporal, agujaInicial, agujaDestino);
    } // Fin If
} // Fin Torres de Hanoi