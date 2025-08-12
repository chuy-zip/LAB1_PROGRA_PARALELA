#include <stdio.h>
#include <omp.h>

#define N 10000

int main() {
    int num_threads = 4;
    omp_set_num_threads(num_threads);
    
    // Variables para medir tiempos
    double start, end;
    
    //Prueba con schedule static
    start = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        int suma = 0;
        if (i % 10 == 0) {
            // Carga pesada para el 10% de las iterciones
            for (int j = 0; j < 5000000; j++) {
                suma += j % 7;
            }
        } else {
            // Carga ligera para los demas
            for (int j = 0; j < 50000; j++) {
                suma += j % 7;
            }
        }
        //printf("Static - Hilo %d ejecuta i = %d\n", omp_get_thread_num(), i);
    }
    end = omp_get_wtime();
    float static_tiempo = end - start;

    printf("Tiempo static: %.4f segundos\n\n", static_tiempo);
    
    // Prueba con schedule dynamic
    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic, 2)
    for (int i = 0; i < N; i++) {
        int suma = 0;
        if (i % 10 == 0) {
            for (int j = 0; j < 5000000; j++) {
                suma += j % 7;
            }
        } else {
            for (int j = 0; j < 50000; j++) {
                suma += j % 7;
            }
        }
        //printf("Dynamic - Hilo %d ejecuta i = %d\n", omp_get_thread_num(), i);
    }
    end = omp_get_wtime();

    float dynamic_tiempo = end - start;
    printf("Tiempo dynamic: %.4f segundos\n\n", dynamic_tiempo);
    
    //Prueba con schedule guided
    start = omp_get_wtime();
    #pragma omp parallel for schedule(guided, 2)
    for (int i = 0; i < N; i++) {
        int suma = 0;
        if (i % 10 == 0) {
            for (int j = 0; j < 5000000; j++) {
                suma += j % 7;
            }
        } else {
            for (int j = 0; j < 50000; j++) {
                suma += j % 7;
            }
        }
        //printf("Guided - Hilo %d ejecuta i = %d\n", omp_get_thread_num(), i);
    }
    end = omp_get_wtime();

    float guided_tiempo = end - start;
    printf("Tiempo guided: %.4f segundos\n\n", end - start);

    printf("\nResumen de los tiempos: \nStatic: %.4f s \nDynamic: %.4f s \nGuided: %.4f s\n", static_tiempo, dynamic_tiempo, guided_tiempo);
    
    return 0;
}