#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include <cstdlib>
using namespace std;

// handwritten
void mtx_multiply(int n, double* A, double* B, double* C) {
    double y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            y = 0;
            for (int k = 0; k < n; k++) y += A[i * n + k] * B[k * n + j];
            C[i * n + j] = y;
        }
    }
}

// lapack dgemm
extern "C" void dgemm_(char* TRANSA, char* TRANSB, int* M, int* N, int* K, double* ALPHA,
                      double* A, int* LDA, double* B, int* LDB, double* BETA, double* C, int* LDC);

void lapack_dgemm(int n, double* A, double* B, double* C) {
    char TRANSA = 'N';
    char TRANSB = 'N';
    int M = n;
    int N = n;
    int K = n;
    double ALPHA = 1.0;
    double BETA = 0.0;
    int LDA = n;
    int LDB = n;
    int LDC = n;

    dgemm_(&TRANSA, &TRANSB, &M, &N, &K, &ALPHA, B, &LDA, A, &LDB, &BETA, C, &LDC);
}

// main
int main() {
    ofstream outfile("result.csv"); 

    outfile << "n,t_lapack,t_handwriting" << endl;

    vector<int> dim = {5, 50, 500, 1000, 5000}; 
    vector<double> t_lapack;    
    vector<double> t_handwritten; 

    for (auto n : dim) {
        double* A = new double[n * n];
        double* B = new double[n * n];
        double* C = new double[n * n];
        for (int i = 0; i < n * n; i++) {
            A[i] = ((double)rand()) / RAND_MAX;
            B[i] = ((double)rand()) / RAND_MAX;
        }

        clock_t t1 = clock();
        lapack_dgemm(n, A, B, C);
        clock_t t2 = clock();
        double lapack_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        t_lapack.push_back(lapack_time);

        t1 = clock();
        mtx_multiply(n, A, B, C);
        t2 = clock();
        double handwritten_time = (double)(t2 - t1) / CLOCKS_PER_SEC;
        t_handwritten.push_back(handwritten_time);

        outfile << n << "," << lapack_time << "," << handwritten_time << endl;

        delete[] A;
        delete[] B;
        delete[] C;
    }

    outfile.close(); 
    cout << "Results saved to result.csv" << endl; 

    return 0;
}