//
//  main.cpp
//  mlperceptron
//
//  Created by Sergei Bugrov on 7/1/17.
//  Copyright © 2017 Sergei Bugrov. All rights reserved.
//

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>

#define N 800

using namespace std;

vector<float> X {
    5.1, 3.5, 1.4, 0.2, 1,
    4.9, 3.0, 1.4, 0.2, 3,
    6.2, 3.4, 5.4, 2.3, 1.4,
    5.9, 3.0, 5.1, 1.8, 1.9,
    5.9, 3.0, 5.1, 1.8, 1.9
};

vector<float> y {
    0,
    0,
    1,
    1 };

vector<float> W {
    0.5,
    0.5,
    0.5,
    0.5};

vector <float> sigmoid_d (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function derivative f'(x) = f(x)(1 - f(x)), 
        where f(x) is sigmoid function.
        Input: m1, a vector.
        Output: x(1 - x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = m1[ i ] * (1 - m1[ i ]);
    }
    
    return output;
}

vector <float> sigmoid (const vector <float>& m1) {
    
    /*  Returns the value of the sigmoid function f(x) = 1/(1 + e^-x).
        Input: m1, a vector.
        Output: 1/(1 + e^-x) for every element of the input matrix m1.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> output (VECTOR_SIZE);
    
    
    for( unsigned i = 0; i != VECTOR_SIZE; ++i ) {
        output[ i ] = 1 / (1 + exp(-m1[ i ]));
    }
    
    return output;
}

vector <float> operator+(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the elementwise sum of two vectors.
        Inputs: 
            m1: a vector
            m2: a vector
        Output: a vector, sum of the vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> sum (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        sum[i] = m1[i] + m2[i];
    };
    
    return sum;
}

vector <float> operator-(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the difference between two vectors.
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 - m2, difference between two vectors m1 and m2.
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> difference (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        difference[i] = m1[i] - m2[i];
    };
    
    return difference;
}

vector <float> operator*(const vector <float>& m1, const vector <float>& m2){
    
    /*  Returns the product of two vectors (elementwise multiplication).
        Inputs:
            m1: vector
            m2: vector
        Output: vector, m1 * m2, product of two vectors m1 and m2
    */
    
    const unsigned long VECTOR_SIZE = m1.size();
    vector <float> product (VECTOR_SIZE);
    
    for (unsigned i = 0; i != VECTOR_SIZE; ++i){
        product[i] = m1[i] * m2[i];
    };
    
    return product;
}

vector <float> transpose (float *m, const int C, const int R) {
    
    /*  Returns a transpose matrix of input matrix.
        Inputs:
            m: vector, input matrix
            C: int, number of columns in the input matrix
            R: int, number of rows in the input matrix
        Output: vector, transpose matrix mT of input matrix m
    */
    
    vector <float> mT (C*R);
    
    for(unsigned n = 0; n != C*R; n++) {
        unsigned i = n/C;
        unsigned j = n%C;
        mT[n] = m[R*j + i];
    }
    
    return mT;
}

vector <float> dot (const vector <float>& m1, const vector <float>& m2, const int m1_rows, const int m1_columns, const int m2_columns) {
    
    /*  Returns the product of two matrices: m1 x m2.
        Inputs:
            m1: vector, left matrix of size m1_rows x m1_columns
            m2: vector, right matrix of size m1_columns x m2_columns (the number of rows in the right matrix 
                must be equal to the number of the columns in the left one)
            m1_rows: int, number of rows in the left matrix m1
            m1_columns: int, number of columns in the left matrix m1
            m2_columns: int, number of columns in the right matrix m2
        Output: vector, m1 * m2, product of two vectors m1 and m2, a matrix of size m1_rows x m2_columns
    */
    
    vector <float> output (m1_rows*m2_columns);
    
    for( int row = 0; row != m1_rows; ++row ) {
        for( int col = 0; col != m2_columns; ++col ) {
            output[ row * m2_columns + col ] = 0.f;
            for( int k = 0; k != m1_columns; ++k ) {
                output[ row * m2_columns + col ] += m1[ row * m1_columns + k ] * m2[ k * m2_columns + col ];
            }
        }
    }
    
    return output;
}

void print ( const vector <float>& m, int n_rows, int n_columns ) {
    
    /*  "Couts" the input vector as n_rows x n_columns matrix.
        Inputs:
            m: vector, matrix of size n_rows x n_columns
            n_rows: int, number of rows in the left matrix m1
            n_columns: int, number of columns in the left matrix m1
    */
    
    for( int i = 0; i != n_rows; ++i ) {
        for( int j = 0; j != n_columns; ++j ) {
            cout << m[ i * n_columns + j ] << " ";
        }
        cout << '\n';
    }
    cout << endl;
}

vector<float> getVector(FILE* Arquivo, int n){
    vector<float> T;
    
    float aux = 0;
    for(int i=0; i < n; i++){
        aux = (float)fgetc(Arquivo) - (float)48;
        //cout << aux;
        T.push_back(aux);
    }
    cout << "END\n";
    return T;
}

void preencheDados(){
    //int N = N;
    FILE *ArquivoX;
    ArquivoX = fopen("X.txt","r");
    X = getVector(ArquivoX, N*N);
    fclose(ArquivoX);

    FILE *ArquivoY;
    ArquivoY = fopen("Y.txt","r");
    y = getVector(ArquivoY, N);
    fclose(ArquivoY);

    FILE *ArquivoW;
    ArquivoW = fopen("W.txt","r");
    W = getVector(ArquivoW, N);
    fclose(ArquivoW);
}


int main(int argc, const char * argv[]) {
    preencheDados();
    for (unsigned i = 0; i != N; ++i) {
        
        vector<float> pred = sigmoid(dot(X, W, N, N, 1 ) );
        vector<float> pred_error = y - pred;        
        vector<float> pred_delta = pred_error * sigmoid_d(pred);        
        vector<float> W_delta = dot(transpose( &X[0], N, N ), pred_delta, N, N, 1);        
        W = W + W_delta;
        
        if (i == N-1){
            print ( pred, N, 1 );
        };
    };

    return 0;
}
