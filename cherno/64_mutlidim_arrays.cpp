#include <iostream>

int main() {
    // a single 1D array, 50 * 4 (int bytes) = 200 bytes
    int* array = new int[50];

    // a 2D array, pointer of pointers, 50 * 4 (int ptr bytes) = 200 bytes
    int** a2d = new int*[50];

    // now create an array for each of the 50 pointers from above step
    for (int i=0; i < 50; i++)
        a2d[i] = new int[50];

    // for a 3D Array!!!
    int*** a3d = new int**[50];
    for (int i=0; i < 50; i++){
        a3d[i] = new int*[50];
        for (int j=0; j < 50; j++){
            // both version of code equivalent 
            // int** ptr = a3d[i];
            // ptr[j] = new int[5];
            a3d[i][j] = new int [50];
        }
            
    }

    // Deleting a 2D Array
    for (int i=0; i< 50; i++)
        delete[] a2d[i];
    delete[] a2d; 

    // A better, more memory efficient way is to just store in 1 1D array
    int* arraybetter = new int[5 * 5];
    std::cin.get();
}