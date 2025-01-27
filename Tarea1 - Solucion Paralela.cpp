/*
Tarea 1. Programación de una solución paralela
Alumno: Luis Fernando Rojas Marta
A00757351
*/

// Se incluyen las librerias
#include <iostream>
#include <omp.h>   //Libreria de OpenMP
#include <cstdlib> //Para la generación de numeros aleatorios
#include <ctime>   //Para la semilla aleatoria

//Creacion de constantes
#define N 1000       //Tamaño del arreglo
#define CHUNK 100    //Tamaño del bloque para la distribucion de trabajo
#define MOSTRAR 10   //Cantidad de valores a mostrar en la impresión

void imprimeArreglo(float *d); //Declaración de la funcion para imprimir un arreglo
void llenarArreglo(float *d); //Función para llenar el arreglo con valores aleatorios entre 0 y 100

int main()
{
    std::cout << "Sumando Arreglos en Paralelo!\n";

   
    std::srand(std::time(0)); //Inicializar la semilla aleatoria

    //Se declaran  los arreglos
    float a[N], b[N], c[N];
    int i;

    // Llenado de los arreglos con valores random/aleatorios
    llenarArreglo(a);
    llenarArreglo(b);

    int pedazos = CHUNK; //Definicion del tamaño de pedazos para la paralelizacion

    //Sección de el codigo paralelizada usando OpenMP
    #pragma omp parallel for \
        shared(a, b, c, pedazos) private(i) \
        schedule(static, pedazos)
    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i]; //Suma de todos los elementos correspondientes de a y b
    }

    //Se imprimen los primeros 'MOSTRAR' valores de los arreglos
    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimiendo los primeros " << MOSTRAR << " valores del arreglo c (resultado de a + b): " << std::endl;
    imprimeArreglo(c);

    return 0;
}

void imprimeArreglo(float *d) //Funcion para imprimir los primeros 'MOSTRAR' valores de un arreglo
{
    for (int x = 0; x < MOSTRAR; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}

void llenarArreglo(float *d) //Función para llenar el arreglo con valores aleatorios entre 0 y 100

{
    for (int i = 0; i < N; i++)
        d[i] = static_cast<float>(rand() % 101); // Genera valores entre 0 y 100
}
