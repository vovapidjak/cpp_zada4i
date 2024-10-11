#include <iostream>
#include <vector>
#include <cassert>

void flipMatrix(int** mat, int rowCount) {
    int top = 0;
    int bottom = rowCount - 1;

    while (top < bottom) {
        int* temp = mat[top];
        mat[top] = mat[bottom];
        mat[bottom] = temp;
        ++top;
        --bottom;
    }
}


bool areMatricesEqual(int** mat1, int** mat2, int rowCount, int colCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            if (mat1[i][j] != mat2[i][j]) {
                return false;
            }
        }
    }
    return true;
}


void displayMatrix(int** mat, int rowCount, int colCount) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void freeMatrix(int** mat, int rowCount) {
    for (int i = 0; i < rowCount; ++i) {
        delete[] mat[i];
    }
    delete[] mat;
}


void testFlipMatrix() {
    // Тест 1
    int** mat1 = new int* [2];
    mat1[0] = new int[2] {1, 2};
    mat1[1] = new int[2] {3, 4};

    int** expected1 = new int* [2];
    expected1[0] = new int[2] {3, 4};
    expected1[1] = new int[2] {1, 2};

    std::cout << "Initial matrix 1:\n";
    displayMatrix(mat1, 2, 2);
    std::cout << "Expected flipped matrix 1:\n";
    displayMatrix(expected1, 2, 2);
    flipMatrix(mat1, 2);
    assert(areMatricesEqual(mat1, expected1, 2, 2));

    // Тест 2
    int** mat2 = new int* [3];
    mat2[0] = new int[3] {-1, -2, -3};
    mat2[1] = new int[3] {-4, -5, -6};
    mat2[2] = new int[3] {-7, -8, -9};

    int** expected2 = new int* [3];
    expected2[0] = new int[3] {-7, -8, -9};
    expected2[1] = new int[3] {-4, -5, -6};
    expected2[2] = new int[3] {-1, -2, -3};

    std::cout << "Initial matrix 2:\n";
    displayMatrix(mat2, 3, 3);
    std::cout << "Expected flipped matrix 2:\n";
    displayMatrix(expected2, 3, 3);
    flipMatrix(mat2, 3);
    assert(areMatricesEqual(mat2, expected2, 3, 3));

    // Тест 3
    int** mat3 = new int* [3];
    mat3[0] = new int[3] {1, 2, 3};
    mat3[1] = new int[3] {4, 5, 6};
    mat3[2] = new int[3] {7, 8, 9};

    int** expected3 = new int* [3];
    expected3[0] = new int[3] {7, 8, 9};
    expected3[1] = new int[3] {4, 5, 6};
    expected3[2] = new int[3] {1, 2, 3};

    std::cout << "Initial matrix 3:\n";
    displayMatrix(mat3, 3, 3);
    std::cout << "Expected flipped matrix 3:\n";
    displayMatrix(expected3, 3, 3);
    flipMatrix(mat3, 3);
    assert(areMatricesEqual(mat3, expected3, 3, 3));

    // Тест 4
    int** mat4 = new int* [4];
    mat4[0] = new int[4] {10, 20, 30, 40};
    mat4[1] = new int[4] {50, 60, 70, 80};
    mat4[2] = new int[4] {90, 100, 110, 120};
    mat4[3] = new int[4] {130, 140, 150, 160};

    int** expected4 = new int* [4];
    expected4[0] = new int[4] {130, 140, 150, 160};
    expected4[1] = new int[4] {90, 100, 110, 120};
    expected4[2] = new int[4] {50, 60, 70, 80};
    expected4[3] = new int[4] {10, 20, 30, 40};

    std::cout << "Initial matrix 4:\n";
    displayMatrix(mat4, 4, 4);
    std::cout << "Expected flipped matrix 4:\n";
    displayMatrix(expected4, 4, 4);
    flipMatrix(mat4, 4);
    assert(areMatricesEqual(mat4, expected4, 4, 4));

    
    freeMatrix(mat1, 2);
    freeMatrix(mat2, 3);
    freeMatrix(mat3, 3);
    freeMatrix(mat4, 4);

    freeMatrix(expected1, 2);
    freeMatrix(expected2, 3);
    freeMatrix(expected3, 3);
    freeMatrix(expected4, 4);
}


void executeTests() {
    testFlipMatrix();
    std::cout << "All tests passed!" << std::endl;
}


int** getUserMatrix(int& rowCount, int& colCount) {
    std::cout << "Enter number of rows: ";
    std::cin >> rowCount;
    std::cout << "Enter number of columns: ";
    std::cin >> colCount;

    int** mat = new int* [rowCount];
    for (int i = 0; i < rowCount; ++i) {
        mat[i] = new int[colCount];
    }

    std::cout << "Enter matrix elements:\n";
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < colCount; ++j) {
            std::cin >> mat[i][j];
        }
    }

    return mat;
}

int main() {
    executeTests();

    int rowCount, colCount;
    int** userMatrix = getUserMatrix(rowCount, colCount);

    std::cout << "Original Matrix:\n";
    displayMatrix(userMatrix, rowCount, colCount);

    flipMatrix(userMatrix, rowCount);

    std::cout << "\nMatrix after flipping rows:\n";
    displayMatrix(userMatrix, rowCount, colCount);

    freeMatrix(userMatrix, rowCount);

    return 0;
}
