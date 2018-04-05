#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define M_SIZE 512
#define RD_MAX 500

typedef int matrix[M_SIZE][M_SIZE];

void fill_matrix(matrix m) {
    for (int i=0; i<M_SIZE; i++)
        for (int j=0; j<M_SIZE; j++)
            m[i][j] = rand() % RD_MAX;
}

void empty_matrix(matrix m) {
    for (int i=0; i<M_SIZE; i++)
        for (int j=0; j<M_SIZE; j++)
            m[i][j] = 0;
}

int main(int argc, char ** argv) {

    matrix a,b,c;

    int rank, size;
    char name[80];
    int length;

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Get_processor_name(name,&length);

    if (rank == 0) {

        fill_matrix(a);
        fill_matrix(b);
        empty_matrix(c);
        // Create 2 random matrix

        // Calculate C matrix SEQUENCALY
        clock_t c_begin = clock();

        for (int i=0; i<M_SIZE; i++) {
            for (int j=0; j<M_SIZE; j++) {
                c[i][j] = 0;
                for (int k=0; k<M_SIZE; k++) {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                }
                // printf("C[%i][%i]=%i\n", i, j, C[i][j]);
            }
        }

        clock_t c_end = clock();
        printf("A & C multiplication sequencialy in %f seconds\n", (double)(c_end - c_begin) / CLOCKS_PER_SEC);


    }

    printf("Hello MPI: processor %d of %d on %s\n", rank,size-1,name);

    MPI_Finalize();
}
