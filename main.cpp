#include <iostream>
#include <fstream>
#include <cstdlib>
#include<math.h>
using namespace std;


void wyswietlenie (double **A, double *b, int matrix_size){
    for ( int i = 0; i<matrix_size; i++ ){
        for ( int j = 0; j<matrix_size; j++ )
            cout << A[i][j]<<" ";
        cout << " | " << b[i];
        cout << endl;
    }
    cout << endl;
}
void sortowanie(int *Tab, double *Indexs, int N){
    int temp;
    for (int i = 0; i<N; i++){
        for (int j = 1; j<N-i; j++){
            if (Tab[j] < Tab[j-1]){
                swap(Tab[j], Tab[j-1]);
                swap(Indexs[j], Indexs[j-1]);
            }
        }
    }
}

double * inicjalizacja(double **A, double *b, int matrix_size, int *index_arr){
    double *result_x = new double[matrix_size];
    for (int i = 0; i < matrix_size; i++)
        result_x[i] = 0;

    for ( int i = matrix_size-1; i>=0; i-- ){
        result_x[i] = b[i];
        for ( int j = i+1; j < matrix_size; j ++ )
            result_x[i] = result_x[i] - A[i][j] * result_x[j];
        if ( A[i][i] != 0)
            result_x[i] /= A[i][i];
        else if ( b[i] == 0)
            result_x[i] = 0;
        else{
            cout << "Nie mozliwo dzielenie na zero!" << endl;
            return result_x;
        }
    }
    for ( int i = 0; i<matrix_size; i++ )

   sortowanie(index_arr, result_x, matrix_size);

    return result_x;
}


void eliminacja_Gaussa_bez_wyboru(double **A, double *b, int matrix_size){
    string tmp;
    double *result;
    int *index_arr = new int[matrix_size];


    for (int i = 0; i<matrix_size; i++)
        index_arr[i] = i;

    for ( int i = 0; i < matrix_size-1; i++ ){



        for ( int j = i; j<matrix_size-1; j ++){
            double p = A[j+1][i]/A[i][i];

            for ( int k = i; k<matrix_size; k++ ){
                A[j+1][k] = A[j+1][k] - p * A[i][k];
            }
            b[j+1] = b[j+1] - p * b[i];
        }
        wyswietlenie(A, b, matrix_size);
    }
    result = inicjalizacja(A, b, matrix_size, index_arr);
    for ( int i = 0; i < matrix_size; i++ ){
        cout << "x" << i+1  << " = " << result[i] << endl;
    }
}
int wczytanie (double **&A, double *&b,string a){
    int matrix_size = -1;
        string line;
        ifstream source_file(a);
        if (!source_file.is_open())
        {
        cout <<"The file has not been open!"<<endl;
        }
    source_file >> matrix_size;
    A = new double*[matrix_size];
    A[0] = new double[matrix_size*matrix_size];
    for(unsigned i = 1; i< matrix_size; i++)
        A[i] = A[i-1] + matrix_size;
    b = new double[matrix_size];
    char semicolumn;
    for (unsigned i = 0; i < matrix_size+1; i++)
        source_file >> semicolumn;

    for (unsigned i = 0; i < matrix_size; i++)
    {
        for (unsigned j = 0; j < matrix_size; j++)
        {
            source_file >> A[i][j];
            source_file >> semicolumn;
        }
        source_file >> semicolumn;
        source_file >> b[i];
    }

        source_file.close();

    return matrix_size;
}

void zadanie1(string a)
{
     double **A, *b;
    int matrix_size =wczytanie(A,b,a);
    wyswietlenie(A,b,matrix_size);
    eliminacja_Gaussa_bez_wyboru(A,b,matrix_size);
}





int main(){

    zadanie1("plik1.csv");
}
