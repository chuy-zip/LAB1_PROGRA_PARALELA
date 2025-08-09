#include <stdio.h>
#include <omp.h> 

#define N 100000000

int arreglo[N];

int main() {

    for (int i = 0; i < N; i++){
        arreglo[i] = i;
    }

    long long sum = 0;
    long long sum_paralela = 0;
    long long sum_paralela_red = 0;

    // ahora la suma pero sin un for loop
    double start = omp_get_wtime();
    for (int i = 0; i < N; i++){
        sum += arreglo[i];
    }

    double end = omp_get_wtime();

    printf("La suma total sin usar paralelismo es: %lld \n", sum);
    printf("Tiempo real: %.4f segundos\n", end - start);

    //ahora usando paralellismo sin reduction
    double start_par = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        sum_paralela += arreglo[i];
    }

    double end_par = omp_get_wtime();

    printf("\nLa suma total usando paralelismo es: %lld \n", sum_paralela);
    printf("Tiempo real: %.4f segundos\n", end_par - start_par);

    //ahora usando paralellismo con reduction
    double start_par_red = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum_paralela_red)
    for (int i = 0; i < N; i++){
        sum_paralela_red += arreglo[i];
    }

    double end_par_red = omp_get_wtime();

    printf("\nLa suma total usando paralelismo y reduction es es: %lld \n", sum_paralela_red);
    printf("Tiempo real: %.4f segundos\n", end_par_red - start_par_red);
    
    return 0;
}