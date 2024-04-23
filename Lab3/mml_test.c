// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// CMPE13 Support Library
#include "BOARD.h"

// User libraries:
#include "MatrixMath.h"

// Module-level variables:
float zero_matrix[3][3] = {{}, {}, {}};

void print_test_result(const char *test_name, int result)
{
    printf("%s: %s\n", test_name, result ? "Passed" : "Failed");
    printf(" \n");
}

int MatrixEquals2x2(float mat1[2][2], float mat2[2][2])
{
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (mat1[i][j] != mat2[i][j])
            {
                return 0; // Matrices are not equal
            }
        }
    }
    return 1; // Matrices are equal
}

int main()
{
    BOARD_Init();

    printf("Beginning CRUZID's mml test harness, compiled on %s %s\n", __DATE__, __TIME__);

    printf("Demonstrating MatrixPrint():\n");
    MatrixPrint(zero_matrix);
    printf(" \n");

    // Add more tests here!

    // MatrixEquals Test
    // Define two identical matrices
    float eqmat1[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}};

    float eqmat2[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}};

    // Define a different matrices
    float eqmat3[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.5, 6.0}, // Note the difference here (5.5 instead of 5.0)
        {7.0, 8.0, 9.0}};

    // Test MatrixEquals function
    int test_result1 = MatrixEquals(eqmat1, eqmat2); // Should return TRUE (1)
    print_test_result("MatrixEquals Test 1: Identical matrices", test_result1);

    int test_result2 = MatrixEquals(eqmat1, eqmat3); // Should return FALSE (0)
    if (test_result2 == 0)
        print_test_result("MatrixEquals Test 2: Different matrices", 1);

    // MatrixAdd Test
    // Test case 1: Adding zero_matrix (all zeros) to another matrix
    float zero_matrix[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    float admat3[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Expected result: The matrix should remain unchanged
    float expected_result1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Matrix to hold the result
    float result1[3][3];

    // Perform the addition
    MatrixAdd(zero_matrix, admat3, result1);

    // Test the result
    int test1_result = MatrixEquals(result1, expected_result1);
    print_test_result("MatrixAdd Test 1: Adding zero_matrix", test1_result);

    // Test case 2: Adding two different matrices
    float admat4[3][3] = {
        {3, 5, 7},
        {2, 4, 6},
        {1, 3, 5}};

    float admat5[3][3] = {
        {9, 7, 5},
        {8, 6, 4},
        {3, 1, 9}};

    // Expected result: Sum of the two matrices
    float expected_result2[3][3] = {
        {12, 12, 12},
        {10, 10, 10},
        {4, 4, 14}};

    // Matrix to hold the result
    float result2[3][3];

    // Perform the addition
    MatrixAdd(admat4, admat5, result2);

    // Test the result
    int test2_result = MatrixEquals(result2, expected_result2);
    print_test_result("MatrixAdd Test 2: Adding two different matrices", test2_result);

    // MatrixMultiply Tests
    //  MatrixMultiply Test 1: Multiplying identity matrix with a matrix
    //  Define an identity matrix (3x3)
    float identity_matrix[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};

    // Define a matrix (3x3) to multiply with the identity matrix
    float mulmat1[3][3] = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};

    // Define expected result matrix (multiplication of identity_matrix and mulmat1)
    float expected_mul_result1[3][3] = {
        {3, 4, 5},
        {6, 7, 8},
        {9, 10, 11}};

    // Matrix to hold the result of the multiplication
    float mul_result1[3][3];

    // Perform matrix multiplication
    MatrixMultiply(identity_matrix, mulmat1, mul_result1);

    // Test the result
    int mul_test_result1 = MatrixEquals(mul_result1, expected_mul_result1);
    print_test_result("MatrixMultiply Test 1: Multiplying identity matrix with a matrix", mul_test_result1);

    // MatrixMultiply Test 2: Multiplying two different matrices
    // Define another matrix (3x3)
    float mulmat2[3][3] = {
        {2, 0, 1},
        {1, 3, 4},
        {0, 1, 2}};

    // Define another matrix (3x3) to multiply with mulmat2
    float mulmat3[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Define expected result matrix (multiplication of mulmat2 and mulmat3)
    float expected_mul_result2[3][3] = {
        {9, 12, 15},
        {41, 49, 57},
        {18, 21, 24}};

    // Matrix to hold the result of the multiplication
    float mul_result2[3][3];

    // Perform matrix multiplication
    MatrixMultiply(mulmat2, mulmat3, mul_result2);

    // Test the result
    int mul_test_result2 = MatrixEquals(mul_result2, expected_mul_result2);
    print_test_result("MatrixMultiply Test 2: Multiplying two different matrices", mul_test_result2);

    // MatrixScalerAdd Tests
    //  Test 1: Add a scalar value of 5 to a matrix
    //  Define the scalar value to add
    float scalar1 = 5;

    // Define the matrix to which the scalar will be added
    float scalar_add_matrix1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Define the expected result matrix after adding the scalar
    float expected_scalar_add_result1[3][3] = {
        {6, 7, 8},
        {9, 10, 11},
        {12, 13, 14}};

    // Matrix to hold the result of the scalar addition
    float result_scalar_add1[3][3];

    // Perform the scalar addition
    MatrixScalarAdd(scalar1, scalar_add_matrix1, result_scalar_add1);

    // Test the result
    int scalar_add_test_result1 = MatrixEquals(result_scalar_add1, expected_scalar_add_result1);
    print_test_result("MatrixScalarAdd Test 1: Add scalar 5 to matrix", scalar_add_test_result1);

    // Test 2: Add a scalar value of -3 to a matrix

    // Define the scalar value to add
    float scalar2 = -3;

    // Define the matrix to which the scalar will be added
    float scalar_add_matrix2[3][3] = {
        {5, 6, 7},
        {8, 9, 10},
        {11, 12, 13}};

    // Define the expected result matrix after adding the scalar
    float expected_scalar_add_result2[3][3] = {
        {2, 3, 4},
        {5, 6, 7},
        {8, 9, 10}};

    // Matrix to hold the result of the scalar addition
    float result_scalar_add2[3][3];

    // Perform the scalar addition
    MatrixScalarAdd(scalar2, scalar_add_matrix2, result_scalar_add2);

    // Test the result
    int scalar_add_test_result2 = MatrixEquals(result_scalar_add2, expected_scalar_add_result2);
    print_test_result("MatrixScalarAdd Test 2: Add scalar -3 to matrix", scalar_add_test_result2);

    // MatrixScalarMultiply Test
    // Test case 1: Multiply by zero
    float test_matrix3[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Scalar value
    float scalar3 = 0;

    // Expected result: All elements should be zero
    float expected_result3[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};

    // Matrix to hold the result
    float result3[3][3];

    // Perform the scalar multiplication
    MatrixScalarMultiply(scalar3, test_matrix3, result3);

    // Test the result
    int test3_result = MatrixEquals(result3, expected_result3);
    print_test_result("MatrixScalarMultiply Test 1: Multiply by zero", test3_result);

    // Test case 2: Multiply by a positive scalar
    float test_matrix4[3][3] = {
        {2, 4, 6},
        {8, 10, 12},
        {14, 16, 18}};

    // Scalar value
    float scalar4 = 2;

    // Expected result: Each element should be doubled
    float expected_result4[3][3] = {
        {4, 8, 12},
        {16, 20, 24},
        {28, 32, 36}};

    // Matrix to hold the result
    float result4[3][3];

    // Perform the scalar multiplication
    MatrixScalarMultiply(scalar4, test_matrix4, result4);

    // Test the result
    int test4_result = MatrixEquals(result4, expected_result4);
    print_test_result("MatrixScalarMultiply Test 2: Multiply by a positive scalar", test4_result);

    // MatrixTrace Tests
    //  Test 1: Calculate the trace of a matrix with non-zero elements on the diagonal
    float test_matrix1[3][3] = {
        {1, 0, 0},
        {0, 2, 0},
        {0, 0, 3}};

    // Expected result: Trace should be 1 + 2 + 3 = 6
    float expected_trace1 = 6;

    // Calculate the trace of test_matrix1
    float trace1 = MatrixTrace(test_matrix1);

    // Test the result
    print_test_result("MatrixTrace Test 1: Non-zero diagonal elements", trace1 == expected_trace1);

    // Test 2: Calculate the trace of a matrix with a mix of zero and non-zero elements
    float test_matrix2[3][3] = {
        {5, 0, 1},
        {3, 4, 0},
        {2, 1, 8}};

    // Expected result: Trace should be 5 + 4 + 8 = 17
    float expected_trace2 = 17;

    // Calculate the trace of test_matrix2
    float trace2 = MatrixTrace(test_matrix2);

    // Test the result
    print_test_result("MatrixTrace Test 2: Mix of zero and non-zero elements", trace2 == expected_trace2);

    // MatrixTranspose Tests
    // Test case 1: Transpose of a standard 3x3 matrix
    // Define an input matrix
    float input_matrix1[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Define the expected transposed matrix
    float expected_transposed1[3][3] = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}};

    // Define a matrix to hold the transposed result
    float transposed_result1[3][3];

    // Perform the transpose using MatrixTranspose
    MatrixTranspose(input_matrix1, transposed_result1);

    // Test the result using MatrixEquals
    int test_result5 = MatrixEquals(transposed_result1, expected_transposed1);
    print_test_result("MatrixTranspose Test 1: Standard 3x3 matrix", test_result5);

    // Test case 2: Transpose of a 3x3 matrix with different values
    // Define an input matrix with different values
    float input_matrix2[3][3] = {
        {0, -1, 2},
        {3, 4, -5},
        {6, -7, 8}};

    // Define the expected transposed matrix
    float expected_transposed2[3][3] = {
        {0, 3, 6},
        {-1, 4, -7},
        {2, -5, 8}};

    // Define a matrix to hold the transposed result
    float transposed_result2[3][3];

    // Perform the transpose using MatrixTranspose
    MatrixTranspose(input_matrix2, transposed_result2);

    // Test the result using MatrixEquals
    int test_result6 = MatrixEquals(transposed_result2, expected_transposed2);
    print_test_result("MatrixTranspose Test 2: 3x3 matrix with different values", test_result6);

    // MatrixSubmatrix Tests
    // Needed to impliment Matrix2x2 for tests
    // Test 1: Remove first row and first column
    {
        float matrix[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}};

        float expected_submatrix[2][2] = {
            {5.0, 6.0},
            {8.0, 9.0}};

        float result_submatrix[2][2];

        // Call MatrixSubmatrix with the first row and first column to be removed
        MatrixSubmatrix(0, 0, matrix, result_submatrix);

        // Use the new MatrixEquals2x2 function to test the result
        int test_result = MatrixEquals2x2(result_submatrix, expected_submatrix);
        print_test_result("MatrixSubmatrix Test 1: Remove first row and first column", test_result);
    }

    // Test 2: Remove second row and second column
    {
        float matrix[3][3] = {
            {1.0, 2.0, 3.0},
            {4.0, 5.0, 6.0},
            {7.0, 8.0, 9.0}};

        float expected_submatrix[2][2] = {
            {1.0, 3.0},
            {7.0, 9.0}};

        float result_submatrix[2][2];

        // Call MatrixSubmatrix with the second row and second column to be removed
        MatrixSubmatrix(1, 1, matrix, result_submatrix);

        // Use the new MatrixEquals2x2 function to test the result
        int test_result = MatrixEquals2x2(result_submatrix, expected_submatrix);
        print_test_result("MatrixSubmatrix Test 2: Remove second row and second column", test_result);
    }

    // MatrixDeterminant Test
    // Test 1: Calculate the determinant of a 3x3 matrix
    {
        // Define the 3x3 matrix
        float matrix[3][3] = {
            {4, 7, 2},
            {3, 5, 1},
            {1, 8, 6}};

        // Calculate the expected determinant manually
        float expected_determinant = 4 * (5 * 6 - 1 * 8) - 7 * (3 * 6 - 1 * 1) + 2 * (3 * 8 - 5 * 1);

        // Calculate the determinant using the function
        float calculated_determinant = MatrixDeterminant(matrix);

        // Compare the calculated determinant with the expected determinant
        // The test result is 1 (Passed) if they match, otherwise 0 (Failed)
        int test_result = (calculated_determinant == expected_determinant);

        // Print the test result using print_test_result
        print_test_result("MatrixDeterminant Test 1: Calculate determinant of a 3x3 matrix", test_result);
    }

    // Test 2: Calculate the determinant of a singular 3x3 matrix
    {
        // Define the 3x3 singular matrix
        float matrix[3][3] = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};

        // The expected determinant of a singular matrix is 0
        float expected_determinant = 0;

        // Calculate the determinant using the function
        float calculated_determinant = MatrixDeterminant(matrix);

        // Compare the calculated determinant with the expected determinant
        // The test result is 1 (Passed) if they match, otherwise 0 (Failed)
        int test_result = (calculated_determinant == expected_determinant);

        // Print the test result using print_test_result
        print_test_result("MatrixDeterminant Test 2: Calculate determinant of a singular 3x3 matrix", test_result);
    }

    // MatrixInverse Tests
    // Test 1: Calculate inverse of a 3x3 identity matrix
    {
        // Define a 3x3 identity matrix
        float matrix[3][3] = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}};

        // Define expected inverse as the identity matrix itself
        float expected_inverse[3][3] = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}};

        // Define a matrix to hold the calculated inverse
        float calculated_inverse[3][3];

        // Calculate the inverse
        MatrixInverse(matrix, calculated_inverse);

        // Compare the calculated inverse with the expected inverse
        int test_result = MatrixEquals(calculated_inverse, expected_inverse);

        // Print the test result using print_test_result
        print_test_result("MatrixInverse Test 1: Calculate inverse of a 3x3 identity matrix", test_result);
    }

    // Test 2: Calculate the inverse of a 3x3 matrix
    {
        // Define a 3x3 matrix
        float matrix[3][3] = {
            {3, 0, 2},
            {2, 0, -2},
            {0, 1, 1}};

        // Define the expected inverse matrix
        float expected_inverse[3][3] = {
            {0.2, 0.2, -0},
            {-0.2, 0.3, 1},
            {0.2, -0.3, 0}};

        // Define a matrix to hold the calculated inverse
        float calculated_inverse[3][3];

        // Calculate the inverse
        MatrixInverse(matrix, calculated_inverse);

        // Compare the calculated inverse with the expected inverse
        int test_result = MatrixEquals(calculated_inverse, expected_inverse);

        // Print the test result using print_test_result
        print_test_result("MatrixInverse Test 2: Calculate inverse of a 3x3 matrix", test_result);
    }

    BOARD_End();
    while (1)
        ;
}
