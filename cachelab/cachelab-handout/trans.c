/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

// 黄子骕 21307130013
int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    //第一种情况
    if(M == 32 && N == 32){
        int i, j, k;
        for(i = 0; i < 32; i+=8){
            for(j = 0; j < 32; j+=8){
                    for(k = 0; k < 8; k++){
                        int temp0 = A[i+k][j];
                        int temp1 = A[i+k][j+1];
                        int temp2 = A[i+k][j+2];
                        int temp3 = A[i+k][j+3];
                        int temp4 = A[i+k][j+4];
                        int temp5 = A[i+k][j+5];
                        int temp6 = A[i+k][j+6];
                        int temp7 = A[i+k][j+7];
                        B[j][i+k] = temp0;
                        B[j+1][i+k] = temp1;
                        B[j+2][i+k] = temp2;
                        B[j+3][i+k] = temp3;
                        B[j+4][i+k] = temp4;
                        B[j+5][i+k] = temp5;
                        B[j+6][i+k] = temp6;
                        B[j+7][i+k] = temp7;
                    }
            }
        }
    }else if(M == 64 && N == 64){
        int i, j, k;
        for(i = 0; i < 64; i+=8){
            for(j = 0; j < 64; j+=8){
                int temp0,temp1,temp2,temp3,temp4,temp5,temp6,temp7;
                //先进行预处理
                for(k = 0; k < 4; k++){
                    temp0 = A[i+k][j];
                    temp1 = A[i+k][j+1];
                    temp2 = A[i+k][j+2];
                    temp3 = A[i+k][j+3];
                    temp4 = A[i+k][j+4];
                    temp5 = A[i+k][j+5];
                    temp6 = A[i+k][j+6];
                    temp7 = A[i+k][j+7];
                    //对于B中的两列写入
                    B[j][i+k] = temp0;
                    B[j+1][i+k] = temp1;
                    B[j+2][i+k] = temp2;
                    B[j+3][i+k] = temp3;
                    B[j][i+k+4] = temp4;
                    B[j+1][i+k+4] = temp5;
                    B[j+2][i+k+4] = temp6;
                    B[j+3][i+k+4] = temp7;
                }
                for(k = 4; k < 8; k++){
                    temp0 = A[i+k][j];
                    temp1 = A[i+k][j+1];
                    temp2 = A[i+k][j+2];
                    temp3 = A[i+k][j+3];
                    temp4 = A[i+k][j+4];
                    temp5 = A[i+k][j+5];
                    temp6 = A[i+k][j+6];
                    temp7 = A[i+k][j+7];
                    //对于B中的两列写入
                    B[j+4][i+k-4] = temp0;
                    B[j+5][i+k-4] = temp1;
                    B[j+6][i+k-4] = temp2;
                    B[j+7][i+k-4] = temp3;
                    B[j+4][i+k] = temp4;
                    B[j+5][i+k] = temp5;
                    B[j+6][i+k] = temp6;
                    B[j+7][i+k] = temp7;
                }
                //此时对角线上的两块小矩阵已经没有问题，接下来再处理另外两块小矩阵，即交换他们的元素
                for(k = 0; k < 4; k++){
                    temp0 = B[j+k+4][i+k];
                    temp1 = B[j+k+4][i+k];
                    temp2 = B[j+k+4][i+k];
                    temp3 = B[j+k+4][i+3];
                    B[j+k+4][i] = B[j+k][i+4];
                    B[j+k+4][i] = B[j+k][i+5];
                    B[j+k+4][i] = B[j+k][i+6];
                    B[j+k+4][i] = B[j+k][i+7];
                    B[j+k][i+4] = temp0;
                    B[j+k][i+5] = temp1;
                    B[j+k][i+6] = temp2;
                    B[j+k][i+7] = temp3;
                }
            }
        }
    }
    registerTransFunction(transpose_submit, transpose_submit_desc);
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

