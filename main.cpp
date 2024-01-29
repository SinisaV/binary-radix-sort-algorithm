#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

bool BranjeStevil(vector<unsigned int> &A, const char *filename);
bool ZapisStevil(vector<unsigned int> &A, const char *filename);

void CountingSort(vector<unsigned int> &A, vector<unsigned int> &B);
vector<unsigned int> BinaryRadixSort(vector<unsigned int> A);

int main(int argc, const char** argv) {

    if (argc != 3) {
        return 0;
    }

    vector<unsigned int> vectorA;
    BranjeStevil(vectorA, argv[2]);

    cout << "VECTOR INPUT" << endl;
    for (unsigned int a : vectorA) {
        cout << a << " ";
    }
    cout << "\n";

    vector<unsigned int> vectorB;
    vectorB = BinaryRadixSort(vectorA);

    cout << "VECTOR OUTPUT" << endl;
    for (unsigned int b : vectorB) {
        cout << b << " ";
    }
    cout << "\n";


    /*vector<unsigned int> result;
    result.reserve(vectorA.size());
    for (unsigned char n : vectorB) {
        result.push_back(static_cast<int>(n));
    }*/

    ZapisStevil(vectorB, "out.txt");

    return 0;
}

bool BranjeStevil(vector<unsigned int> &A, const char *filename) {
    ifstream input(filename);
    int st;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> st;
        if (!input) break;
        A.push_back(st);
    }

    input.close();

    return true;
}

bool ZapisStevil(vector<unsigned int> &A, const char *filename) {
    ofstream output(filename);

    if (!output.is_open()) {
        return false;
    }

    for (uint i = 0; i<A.size(); i++)
        output << A[i] << ' ';

    output.close();

    return true;
}

void CountingSort(vector<unsigned int> &A, vector<unsigned int> &B) {

    vector<unsigned int> C(2, 0);
    vector<unsigned int> myIndex;
    //cout << C.size() << endl;

    for (int myIt = 0; myIt < A.size(); myIt++) {
        C[B[myIt]] = C[B[myIt]] + 1;
    }
    /*for (int myIt = 0; myIt < A.size(); myIt++) {
        cout << static_cast<int>(C[myIt]) << " ";
    }
    cout << "\n";*/

    C[1] += C[0];

    myIndex.resize(A.size());
    for (int myIt = A.size() - 1; myIt >= 0; myIt--) {
        myIndex[--C[B[myIt]]] = myIt;
    }

    vector<unsigned int> resultVector(A.size());

    for (int myIt = 0; myIt < A.size(); myIt++) {
        resultVector[myIt] = A[myIndex[myIt]];
    }
    /*for (int myIt = 0; myIt < A.size(); myIt++) {
        cout << resultVector[myIt] << " ";
    }*/

    swap(A, resultVector);
}

vector<unsigned int> BinaryRadixSort(vector<unsigned int> A) {
    vector<unsigned int> vectorD(A.size());

    for (int k = 0; k < 8; ++k) {
        for (int myIt = 0; myIt < A.size(); myIt++) {
            //std::cout<< ((A[myIt] >> k) & 1)<<"\n";
            vectorD[myIt] = (A[myIt] >> k) & 1;
        }
        CountingSort(A, vectorD);
    }
    return A;
}
