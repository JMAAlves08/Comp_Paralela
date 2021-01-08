#include <iostream>
#include <fstream>
#include <stdlib.h>

#define LINHAS 10
#define COLUNAS 10
#define N 800
#define SEED 5

using namespace std;

void generateVector(string filename, int n){
    ofstream myfile;
    myfile.open (filename);
    for(int i=0; i < n; i++){
        myfile << rand() % SEED;
    }

    myfile.close();
}

int main(){
    generateVector("X.txt", N*N);
    generateVector("Y.txt", N);
    generateVector("W.txt", N);
    ifstream myfile;
    myfile.open ("X.txt");
    cout << myfile.tellg();

    return 0;
}