/*
 * File:   MatrixMath.c
 * Author: Rahil Prakash
 *
 * Created on April 17, 2024, 1:17 PM
 *
 */

// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// Support Library
#include "BOARD.h"

// User libraries:
#include "MatrixMath.h"

void MatrixPrint(float mat[3][3])
{
    // Iterate through each row
    for (int i = 0; i < 3; i++)
    {
        // Iterate through each column in the current row
        for (int j = 0; j < 3; j++)
        {
            // Print the current element in the matrix with formatting
            // %.4f specifies the formatting to 4 decimal places, adjust as needed
            printf("%8.4f ", mat[i][j]);
        }
        // Move to the next line after printing all columns in the current row
        printf("\n");
    }
}

int MatrixEquals(float mat1[3][3], float mat2[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (fabs(mat1[i][j] - mat2[i][j]) > FP_DELTA)
            {
                return 0; // Matrices are not equal
            }
        }
    }
    return 1; // Matrices are equal
}

void MatrixAdd(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    // Iterate through each row
    for (int i = 0; i < 3; i++)
    {
        // Iterate through each column in the current row
        for (int j = 0; j < 3; j++)
        {
            // Perform element-wise addition and store the result
            result[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
}

void MatrixMultiply(float mat1[3][3], float mat2[3][3], float result[3][3])
{
    // Initialize the result matrix to zero
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                // Calculate the dot product of the i-th row of mat1 and the j-th column of mat2
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}

void MatrixScalarAdd(float x, float mat[3][3], float result[3][3])
{
    // Iterate through each row of the matrix
    for (int i = 0; i < 3; i++)
    {
        // Iterate through each column of the matrix
        for (int j = 0; j < 3; j++)
        {
            // Add the scalar x to the element in mat[i][j] and store the result
            // in the corresponding element of the result matrix
            result[i][j] = mat[i][j] + x;
        }
    }
}

void MatrixScalarMultiply(float x, float mat[3][3], float result[3][3])
{
    // Iterate over each element of the matrix
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Multiply each element by the scalar 'x' and store the result in the corresponding element of 'result'
            result[i][j] = mat[i][j] * x;
        }
    }
}

float MatrixTrace(float mat[3][3])
{
    float trace = 0.0; // Initialize trace as zero

    // Iterate through the diagonal elements of the matrix
    for (int i = 0; i < 3; i++)
    {
        trace += mat[i][i]; // Add the diagonal element to the trace
    }

    // Return the calculated trace
    return trace;
}

void MatrixTranspose(float mat[3][3], float result[3][3])
{
    // Iterate through the rows and columns of the input matrix (mat)
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Set the element at position (j, i) in the result matrix
            // to the element at position (i, j) in the input matrix
            result[j][i] = mat[i][j];
        }
    }
}

void MatrixSubmatrix(int i, int j, float mat[3][3], float result[2][2])
{
    // Initialize the indices for the submatrix result
    int sub_i = 0;
    int sub_j = 0;

    // Iterate over each row in the 3x3 matrix
    for (int row = 0; row < 3; row++)
    {
        // Skip the row if it matches the i-th row to be removed
        if (row == i)
        {
            continue;
        }

        // Iterate over each column in the 3x3 matrix
        for (int col = 0; col < 3; col++)
        {
            // Skip the column if it matches the j-th column to be removed
            if (col == j)
            {
                continue;
            }

            // Store the value from the 3x3 matrix to the submatrix result
            result[sub_i][sub_j] = mat[row][col];

            // Increment the submatrix column index
            sub_j++;

            // If we reach the end of a row in the submatrix, reset the column index
            if (sub_j == 2)
            {
                sub_j = 0;
                sub_i++;
            }
        }
    }
}

float MatrixDeterminant(float mat[3][3])
{
    // Calculate the determinant using the rule of Sarrus
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

void MatrixInverse(float mat[3][3], float result[3][3])
{
    // Calculate the determinant
    float det = MatrixDeterminant(mat);
    if (det == 0.0)
    {
        // If the determinant is zero, the matrix is not invertible
        // Invertibility is checked elsewhere in the code, so it will not be handled here
        return;
    }

    // Calculate the cofactor matrix and the adjugate matrix
    float cofactor[3][3];
    cofactor[0][0] = mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1];
    cofactor[0][1] = mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2];
    cofactor[0][2] = mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0];
    cofactor[1][0] = mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2];
    cofactor[1][1] = mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0];
    cofactor[1][2] = mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1];
    cofactor[2][0] = mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1];
    cofactor[2][1] = mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2];
    cofactor[2][2] = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    // Transpose the cofactor matrix to get the adjugate matrix
    float adjugate[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            adjugate[i][j] = cofactor[j][i];
        }
    }

    // Calculate the inverse using the formula adjugate / determinant
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            result[i][j] = adjugate[i][j] / det;
        }
    }
}