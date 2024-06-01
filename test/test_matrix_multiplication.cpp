
// ######################### Source code of multiplyMatrices in src/matrix_mult

/*
StandardMatrixMultiplicationTest is the list of tests that find the errors in
the BB form the lib repo. This is done through the random matrix generation with
different structures as shown below. In particular we considered:
 - rectangular matrices with Cols over Rows and negative numbers
(RectangularMatrices): Error 5: Matrix B contains a negative number! Error 3:
Matrix A contains a negative number! Error 6: Result matrix contains a number
bigger than 100! Error 16: Matrix B contains the number 6! Error 20: Number of
columns in matrix A is odd!
 - both square matrices:
    Error 6: Result matrix contains a number bigger than 100!
    Error 2: Matrix A contains the number 7!
    Error 12: The number of rows in A is equal to the number of columns in B!
    Error 16: Matrix B contains the number 6!
    Error 18: Matrix A is a square matrix!
    Error 17: Result Matrix C contains number 17!
    Error 20: Number of columns in matrix A is odd!
 - rectangular matrix and vector:
    Error 1: Element-wise multiplication of ones detected!
    Error 5: Matrix B contains a negative number!
    Error 3: Matrix A contains a negative number!
    Error 10: A row in matrix A contains more than one '1'!
    Error 9: Result Matrix C contains the number 99!
 - Wrong dimensions (RowB>ColA):
    Error 5: Matrix B contains a negative number!
    Error 7: Result matrix contains a number between 11 and 20!
    Error 3: Matrix A contains a negative numbe
    Error 8: Result matrix contains zero!
    Segmentation fault
 - Try matrix with specific numbers:
    Error 8: Result matrix contains zero!
    Error 2: Matrix A contains the number 7!
    Error 4: Matrix B contains the number 3!
    Error 11: Every row in matrix B contains at least one '0'!
    Error 14: The result matrix C has an even number of rows!
    Error 12: The number of rows in A is equal to the number of columns in B!
    Error 13: The first element of matrix A is equal to the first element of
matrix B! Error 18: Matrix A is a square matrix!
 - Matrixes with constant numbers in the matrix:
    Error 8: Result matrix contains zero!
    Error 4: Matrix B contains the number 3!
    Error 1: Element-wise multiplication of ones detected!
    Error 7: Result matrix contains a number between 11 and 20!
    Error 10: A row in matrix A contains more than one '1'!
    Error 11: Every row in matrix B contains at least one '0'!
    Error 13: The first element of matrix A is equal to the first element of
matrix B! Error 15: A row in matrix A is filled entirely with 5s! Error 17:
Result matrix C contains the number 17! Error 20: Number of columns in matrix A
is odd!
 - Matrix of all zeros:
    Error 8: Result matrix contains zero!
    Error 11: Every row in matrix B contains at least one '0'!
    Error 13: The first element of matrix A is equal to the first element of
matrix B! Error 20: Number of columns in matrix A is odd!


NOTE: The dimensions of the matrices were kept small in order too avoid the
replication of the errors too many time at the print
*/

#include "../src/matrix_mult.cpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <matrix_multiplication.h>
#include <random>
#include <vector>

void fillMatrixWithRandomValues(std::vector<std::vector<int>> &matrix,
                                std::mt19937 &gen,
                                std::uniform_int_distribution<> &dis_val) {
  for (auto &row : matrix) {
    for (auto &elem : row) {
      elem = dis_val(gen);
    }
  }
}

void fillMatrixWithSpecifiedValues(std::vector<std::vector<int>> &matrix,
                                   int multiplier) {
  for (int i = 0; i < matrix.size(); ++i) {
    for (int j = 0; j < matrix[0].size(); ++j) {
      matrix[i][j] = multiplier * (i + j);
    }
  }
}

void fillMatrixWithConstantValues(std::vector<std::vector<int>> &matrix,
                                  int value) {
  for (auto &row : matrix) {
    std::fill(row.begin(), row.end(), value);
  }
}

void testMatrixMultiplication(const std::vector<std::vector<int>> &A,
                              const std::vector<std::vector<int>> &B, int rowsA,
                              int colsA, int colsB) {
  std::vector<std::vector<int>> C(rowsA, std::vector<int>(colsB, 0));
  std::vector<std::vector<int>> expected(rowsA, std::vector<int>(colsB, 0));

  multiplyMatrices(A, B, C, rowsA, colsA, colsB);
  multiplyMatricesWithoutErrors(A, B, expected, rowsA, colsA, colsB);

  ASSERT_EQ(C, expected) << "Matrix multiplication test failed!";
}

TEST(MatrixMultiplicationTest, RectangularMatrices) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 8);
  std::uniform_int_distribution<> dis_val(-50, 50);

  const int rowsA = dis_dim(gen);
  const int colsA = dis_dim(gen);
  std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA));
  fillMatrixWithRandomValues(A, gen, dis_val);

  const int rowsB = colsA;
  const int colsB = dis_dim(gen);
  std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB));
  fillMatrixWithRandomValues(B, gen, dis_val);

  testMatrixMultiplication(A, B, rowsA, colsA, colsB);
}

TEST(MatrixMultiplicationTest, SquareMatrices) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);
  std::uniform_int_distribution<> dis_val(0, 100);

  const int dim = dis_dim(gen);
  std::vector<std::vector<int>> A(dim, std::vector<int>(dim));
  fillMatrixWithRandomValues(A, gen, dis_val);

  std::vector<std::vector<int>> B(dim, std::vector<int>(dim));
  fillMatrixWithRandomValues(B, gen, dis_val);

  testMatrixMultiplication(A, B, dim, dim, dim);
}

TEST(MatrixMultiplicationTest, MatrixVector) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);
  std::uniform_int_distribution<> dis_val(-2, 2);

  const int rowsA = dis_dim(gen);
  const int colsA = dis_dim(gen);
  std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA));
  fillMatrixWithRandomValues(A, gen, dis_val);

  const int rowsB = colsA;
  const int colsB = 1;
  std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB));
  fillMatrixWithRandomValues(B, gen, dis_val);

  testMatrixMultiplication(A, B, rowsA, colsA, colsB);
}

TEST(MatrixMultiplicationTest, SpecifiedValues) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);

  const int dim = dis_dim(gen);
  std::vector<std::vector<int>> A(dim, std::vector<int>(dim));
  fillMatrixWithSpecifiedValues(A, 1);

  std::vector<std::vector<int>> B(dim, std::vector<int>(dim));
  fillMatrixWithSpecifiedValues(B, 1);

  testMatrixMultiplication(A, B, dim, dim, dim);
}

TEST(MatrixMultiplicationTest, LargeSpecifiedValues) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);

  const int dim = dis_dim(gen);
  std::vector<std::vector<int>> A(dim, std::vector<int>(dim));
  fillMatrixWithSpecifiedValues(A, 100);

  std::vector<std::vector<int>> B(dim, std::vector<int>(dim));
  fillMatrixWithSpecifiedValues(B, 100);

  testMatrixMultiplication(A, B, dim, dim, dim);
}

TEST(MatrixMultiplicationTest, ConstantValues) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);

  const int rowsA = dis_dim(gen);
  const int colsA = dis_dim(gen);
  std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA));
  fillMatrixWithConstantValues(A, 1);

  const int rowsB = colsA;
  const int colsB = dis_dim(gen);
  std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB));
  fillMatrixWithConstantValues(B, 1);

  testMatrixMultiplication(A, B, rowsA, colsA, colsB);
}

TEST(MatrixMultiplicationTest, AllZeros) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);

  const int rowsA = dis_dim(gen);
  const int colsA = dis_dim(gen);
  std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA, 0));

  const int rowsB = colsA;
  const int colsB = dis_dim(gen);
  std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB, 0));

  testMatrixMultiplication(A, B, rowsA, colsA, colsB);
}

TEST(MatrixMultiplicationTest, InvalidDimensions) {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis_dim(1, 10);
  std::uniform_int_distribution<> dis_val(-2, 2);

  const int rowsA = 2;
  const int colsA = 2;
  std::vector<std::vector<int>> A(rowsA, std::vector<int>(colsA));
  fillMatrixWithRandomValues(A, gen, dis_val);

  const int rowsB = 10; // let's check that dimensions are checked
  const int colsB = 2;
  std::vector<std::vector<int>> B(rowsB, std::vector<int>(colsB));
  fillMatrixWithRandomValues(B, gen, dis_val);

  testMatrixMultiplication(A, B, rowsA, colsA, colsB);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
