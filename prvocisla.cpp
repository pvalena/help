#include <iostream>

using namespace std;

void sieve(int n, int* A){
    for (int p = 2; p<= n; p++){
        A[p]=p;
    }

    for (int p = 2; p*p <= n; p++){
        if (A[p] != 0 ){
            int j;
            j = p*p;
            while (j <= n){
                A[j] = 0;
                j = j + p; 
            }
        }
    }
}

void printPrime(int n, int*A) {

    for (int p = 2; p<= n; p++){
        if (A[p] != 0) cout << A[p] << " ";
    }
    cout << endl;
}

int main()
{
    int n = 200;

    int * A;
    A =(int *) malloc(n*sizeof(int));

    sieve(n, A);
    printPrime(n, A);

    free(A);
    return 0;
}