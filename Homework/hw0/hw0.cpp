//Alvaro Urtaza
//hw0
//This code will calculate C = A^2 from a given matrix A.
#include <iostream>
#include <fstream>
#include <sstream>
#include "ArgumentManager.h"
#include <iomanip>

using namespace std;

int main(int argc, char **argv) {
    ArgumentManager am(argc, argv);
    //const string input = am.get("input");
    //const string output = am.get("output");

    ifstream inputfile("1.txt"); // for grading use input
    ofstream outputfile("output.txt"); // for grading use output
    
    string l, l1;
    int matrix_size = 0, lcount = 0;
    double matrix[20][20];

    while (getline(inputfile, l)) {
        lcount++;
        if (lcount == 1) {
            continue;
        }
        else {
            int loop = 0;
            for (int i = 0; i < l.length(); i++) {
                if (l[i] != ' ')  {
                matrix[matrix_size][loop] = l[i]-48;
                loop++;
                }
            }
                matrix_size++;
            
        }
    }
    cout << "#Matrix C=AA, 2 decimals" << endl;
    cout << fixed << setprecision(2);

    for (int i = 0 ; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            if (j == matrix_size - 1) {
                cout << matrix[i][j];
            }
            else {
            cout << matrix[i][j] << " ";
            }
        }
        cout << endl;
    }
    
    return 0;
}
