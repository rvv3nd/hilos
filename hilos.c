#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define N 2
#define k 4

int sumaAB[2][2], restaAB[2][2], restaBA[2][2], mul[2][2], kA[2][2], kB[2][2];
int A[N][N] = {1,5,8,12};
int B[N][N] = {5,2,3,18};

void suma(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            sumaAB[i][j] = A[i][j]+B[i][j];
        }
    }
    pthread_exit(NULL);
}

void restaA_B(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            restaAB[i][j] = A[i][j]-B[i][j];
        }
    }
    pthread_exit(NULL);
}

void restaB_A(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            restaBA[i][j] = B[i][j]-A[i][j];
        }
    }
    pthread_exit(NULL);
}

void k_A(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            kA[i][j] = k*A[i][j];
        }
    }
    pthread_exit(NULL);
}

void k_B(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            kB[i][j] = k*B[i][j];
        }
    }
    pthread_exit(NULL);
}

void multi(){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mul[i][j] = 0;
            for (int l = 0; l < N; l++)
                mul[i][j] += A[i][l] * B[l][j];
        }
    }
}

void muestra(int matriz[N][N]){
    printf("\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf(" %d ",matriz[i][j]);
        }
        printf("\n");
    }
}

int main(){
    pthread_t t_suma,t_restaAB,t_restaBA,t_kA,t_kB,t_multi;
    int opc;
    pthread_create(&t_suma,NULL,(void*)suma,&A);
    pthread_join(t_suma,NULL);
    pthread_create(&t_restaAB,NULL,(void*)restaA_B,&A);
    pthread_join(t_restaAB,NULL);
    pthread_create(&t_restaBA,NULL,(void*)restaB_A,&A);
    pthread_join(t_restaBA,NULL);
    pthread_create(&t_kA,NULL,(void*)k_A,&A);
    pthread_join(t_kA,NULL);
    pthread_create(&t_kB,NULL,(void*)k_B,&B);
    pthread_join(t_kB,NULL);
    pthread_create(&t_multi,NULL,(void*)multi,&B);
    pthread_join(t_multi,NULL);
    bool in = true;
    while(in){
        printf("Selecciona una opción: \n");
        printf("1.-Suma\n2.-Resta A-B \n3.-Resta B-A\n4.-K por A\n5.-K por B\n6.-Multiplicacion\n7.-Resta A-B y B-A\n8.-Salir\n:");
        scanf("%d",&opc);
        switch (opc)
        {
        case 1:
            muestra(A);
            printf("+");
            muestra(B);
            printf("_____________");
            muestra(sumaAB);
            break;
        case 2:
            muestra(A);
            printf("-");
            muestra(B);
            printf("_____________");
            muestra(restaAB);
            break;
        case 3:
            muestra(B);
            printf("-");
            muestra(A);
            printf("_____________");
            muestra(restaBA);
            break;
        case 4:
            printf("%d",k);
            printf("*");
            muestra(A);
            printf("_____________");
            muestra(kA);
            break;
        case 5:
            printf("%d",k);
            printf("*");
            muestra(B);
            printf("_____________");
            muestra(kB);
            break;
        case 6:
            muestra(A);
            printf("*");
            muestra(B);
            printf("_____________");
            muestra(mul);
            break;
        case 7:
            muestra(A);
            printf("-");
            muestra(B);
            printf("_____________");
            muestra(restaAB);
            muestra(B);
            printf("-");
            muestra(A);
            printf("_____________");
            muestra(restaBA);
            break;
        case 8:
            printf("Saliendo...");
            in = false;
            break;
        default:
            break;
        }
    }
}