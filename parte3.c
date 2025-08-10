#include <stdio.h>
#include <omp.h> 

#define N 10000000

int arreglo[N];

int main() {

    for (int i = 0; i < N; i++){
        arreglo[i] = i;
    }

    long long sum = 0;
    long long sum_paralela_critic = 0;
    long long sum_paralel_red = 0;

    // ahora la suma pero sin un for loop
    double start = omp_get_wtime();
    for (int i = 0; i < N; i++){
        if(arreglo[i] % 2 == 0){
            sum += 1;
        }
        
    }

    double end = omp_get_wtime();

    printf("La suma total de numeros pares sin usar paralelismo es: %lld \n", sum);
    printf("Tiempo real: %.4f segundos\n", end - start);

    //ahora usando paralellismo sin reduction pero con critical
    double start_par = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++){
        if(arreglo[i] % 2 == 0){
            #pragma omp critical 
            {
                sum_paralela_critic += 1;
            }
            
        }
        
    }

    double end_par = omp_get_wtime();

    printf("\nLa suma total de numeros pares usando paralelismo con critical es: %lld \n", sum_paralela_critic);
    printf("Tiempo real: %.4f segundos\n", end_par - start_par);

    //ahora usando paralellismo con reduction
    double start_par_red = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum_paralel_red)
    for (int i = 0; i < N; i++){
        if(arreglo[i] % 2 == 0){
            sum_paralel_red += 1;
        }
        
    }

    double end_par_red = omp_get_wtime();

    printf("\nLa suma total de numeros pares usando paralelismo y reduction es: %lld \n", sum_paralel_red);
    printf("Tiempo real: %.4f segundos\n", end_par_red - start_par_red);
    
    return 0;
}