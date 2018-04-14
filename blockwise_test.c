#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <stdlib.h>
#include <time.h>

#define M_SIZE 6
#define RD_MAX 30

typedef int matrix[M_SIZE][M_SIZE];

int * fill_matrix(int nb_rows, int nb_cols);
// void empty_matrix(matrix m, int rows, int cols);
// void split_matrix_h(matrix m, int nbrows, int nbcols, int size);
void display_matrix(int *m, int rows, int cols);
// void get_block(matrix m, int id_processor, int nb_processor, matrix block, int block_nb_cols, int block_nb_rows);

int main(int argc, char ** argv) {

    int *a, *b, *c;
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);



    if (rank == 0) {
        // Fill our matrix with randoms numbers
        a = fill_matrix(M_SIZE, M_SIZE);
        b = fill_matrix(M_SIZE, M_SIZE);
        // display_matrix(a, M_SIZE, M_SIZE);
        // display_matrix(a, M_SIZE, M_SIZE);
    }

    // -------- Broadcast the matrix --------- //
    // MPI_Barrier(MPI_COMM_WORLD);
    // MPI_Bcast(&(a[0][0]), M_SIZE*M_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    // MPI_Barrier(MPI_COMM_WORLD);

    // Calcul numbers of rows and numbers of columns in blocks
    int block_nb_cols, block_nb_rows;
    if (size == 1) {
        block_nb_rows = M_SIZE;
        block_nb_cols = M_SIZE;
    } else if (size <= 2) {
        block_nb_rows = M_SIZE;
        block_nb_cols = M_SIZE/size;
    } else {
        block_nb_rows = M_SIZE/2;
        block_nb_cols = M_SIZE/(size/2);
    }
    //
    // matrix myBlock;
    // get_block(a, rank, size, myBlock, block_nb_cols, block_nb_rows);
    // display_matrix(myBlock, block_nb_cols, block_nb_rows);

    MPI_Finalize();
}

// void get_block(matrix m, int id_processor, int nb_processor, matrix block, int block_nb_cols, int block_nb_rows) {
//     int index=0;
//     int offset_rows=0;
//     int offset_cols=0;
//     int i, j, p;
//
//     // Create result matrix
//     // matrix block;
//     if (nb_processor == 1) {
//         for (i=0; i<M_SIZE; i++) {
//             for (j=0; j<M_SIZE; j++) {
//                 block[i][j]=m[i][j];
//             }
//     }
//         // display_matrix(block, block_nb_cols, block_nb_rows);
//     } else {
//         printf("ID PROCESSEUR: %d\n", id_processor);
//         empty_matrix(block, block_nb_rows, block_nb_cols);
//
//         if (id_processor < nb_processor/2) {
//             offset_cols = 0 + block_nb_cols*id_processor;
//         } else {
//             offset_rows = 0 + block_nb_rows;
//             id_processor = id_processor - nb_processor/2;
//             if (id_processor < nb_processor/2) {
//                 offset_cols = 0 + block_nb_cols*id_processor;
//             }
//         }
//
//         // Separate blocks
//         for (i=0; i<M_SIZE; i++) {
//             for (j=0; j<M_SIZE; j++) {
//                 if ( i>=offset_rows && i<(offset_rows+block_nb_rows) && j>=offset_cols && j<(offset_cols+block_nb_cols) ) {
//                     block[i-offset_rows][j-offset_cols]=m[i][j];
//                     index++;
//                 }
//             }
//         }
//     }
//     // display_matrix(block, block_nb_cols, block_nb_rows);
// }
//
// void split_matrix_h(matrix m, int nbrows, int nbcols, int size) {
//     int offset_rows=0;
//     int offset_cols=0;
//     int i, j, p;
//     for (p=0; p<size;p++) {
//         int sub_m[nbrows*nbcols];
//         int index=0;
//         for(i=0;i<M_SIZE;i++) {
//             for(j=0;j<M_SIZE;j++) {
//                 if(i>=offset_rows && i<(offset_rows+nbrows) && j>=offset_cols && j<(offset_cols+nbcols)) {
//                     sub_m[index]=m[i][j];
//                     index++;
//                 }
//             }
//         }
//
//         if(offset_cols < M_SIZE) {
//             offset_cols=offset_cols+nbcols;
//         }
//         else if (offset_cols == M_SIZE) {
//             offset_cols=0;
//             offset_rows=offset_rows+nbrows;
//         }
//     }
// }

int * fill_matrix(int nb_rows, int nb_cols) {
    int i,j;
    int *m;
    for (i=0; i<nb_rows; i++) {
        for (j=0; j<nb_cols; j++) {
            m[M_SIZE*i+j] = M_SIZE*i+j;
        }
    }
    return m;
}
//
// void empty_matrix(matrix m, int rows, int cols){
//     int i,j;
//     for (i=0; i<rows; i++)
//         for (j=0; j<cols; j++)
//             m[i][j] = 0;
// }

void display_matrix(int *m, int rows, int cols) {
    int i, j;
    for (i=0; i<rows; i++) {
        for (j=0; j<cols; j++) {
            printf("%d   ", m[cols*i+j]);
        }
        printf ("\n");
    }
}
