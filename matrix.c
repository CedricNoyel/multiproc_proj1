#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

const int M_SIZE = 512;
const int RD_MAX = 100;

int main(int argc, char ** argv) {

    int A[M_SIZE][M_SIZE];
    int B[M_SIZE][M_SIZE];
    int C[M_SIZE][M_SIZE];

    int rank, size;
    char name[80];
    int length;

    MPI_Init(&argc, &argv); // note that argc and argv are passed
                            // by address

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(name,&length);

    if (rank == 0) {

        clock_t begin = clock();

        // Create 2 random matrix
        for (int i=0; i<M_SIZE; i++) {
            for (int j=0; j<M_SIZE; j++) {
                A[i][j] = rand() % RD_MAX;
                B[i][j] = rand() % RD_MAX;
                C[i][j] = 0;
            }
        }

        clock_t end = clock();
        printf("Created 2 matrix in %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);


        // Calculate C matrix
        clock_t c_begin = clock();

        for (int i=0; i<M_SIZE; i++) {
            for (int j=0; j<M_SIZE; j++) {
                C[i][j] = 0;
                for (int k=0; k<M_SIZE; k++) {
                    C[i][j] = C[i][j] + A[i][k] * B[k][j];
                }
                printf("C[%i][%i]=%i\n", i, j, C[i][j]);
            }
        }
        clock_t c_end = clock();
        printf("A & C multiplication in %f seconds\n", (double)(c_end - c_begin) / CLOCKS_PER_SEC);



    }

    printf("Hello MPI: processor %d of %d on %s\n", rank,size-1,name);

    MPI_Finalize();
}
