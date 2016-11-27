#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


/*Classes Begin*/

class MatrixCombo {
public:
    int x_;
    int y_;
    MatrixCombo(int x, int y);

private:
};

MatrixCombo::MatrixCombo(int x, int y) {
    this->x_ = x;
    this->y_ = y;
}

class Combo {
public:
    int x_;
    int y_;
    int priority_;
    int value_;
    Combo(int x, int y);

private:
};

Combo::Combo(int x, int y) {
    this->x_ = x;
    this->y_ = y;
    this->priority_ = y -x;
    this->value_ = -1;
}

/*Classes End*/

//code for splitting a string
//found at: http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c%2B%2B
vector<string> split(string str, char delimiter) {
    vector<string> internal;
    stringstream ss(str);
    string tok;

    while(getline(ss, tok, delimiter)) {
        internal.push_back(tok);
    }

    return internal;
}


//get matrix combinations of values from input
vector<MatrixCombo> getMatrices(){
    vector<string> inputArr;
    vector<MatrixCombo> matrices;

    //get input
    ifstream infile("/home/terrabyte/Development/DynamicProgrammingMatrixTable/input.txt");
    string line;
    while (getline(infile, line))
    {
        istringstream iss(line);
        string n;

        while (iss >> n)
        {
            inputArr.push_back(n);
        }
    }

    //convert input
    for(int i = 0; i < inputArr.size(); i++){
        vector<string> tempStr = split(inputArr[i],'x');

        MatrixCombo mC(atoi(tempStr[0].c_str()), atoi(tempStr[1].c_str()));

        matrices.push_back(mC);
    }

    return matrices;
}


//get P List
vector <int> getPList(vector<MatrixCombo> matrices){
    vector<int> list;

    for(int i = 0; i < matrices.size(); i++){
        if(i == 0){
            list.push_back(matrices[i].x_);
            list.push_back(matrices[i].y_);
        }
        else{
            list.push_back(matrices[i].y_);
        }
    }

    return list;
}


//initialize the table with -1 and 0 values
vector<vector<int>> initializeTable(int count){
    vector<vector<int>>table;
    for(int i = 0; i < count; i++){
        vector<int> tempRow;
        for(int j = 0; j < count; j++){
            if(i == j){
                tempRow.push_back(0);
            }
            else if(i > j){
                tempRow.push_back(-2);
            }
            else{
                tempRow.push_back(-1);
            }
        }

        table.push_back(tempRow);
    }

     return table;
}


//print table
void printTable(vector<vector<int>> table){
    for(int i = 0; i < table.size(); i++){
        for(int j = 0; j < table.size(); j++){
            cout<<table[i][j]<<"\t\t";
        }

        cout<<endl<<endl;
    }
}


//generate matrix combinations
vector<Combo> getMatrixCombinations(vector<vector<int>> table, int count){
    vector<Combo> combos;

    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            if(table[i][j] == -1){
                Combo c(i,j);
                combos.push_back(c);
            }
        }
    }

    return combos;
}



/*base algorithm start*/

//solve combo
int lowestComboValue(Combo combo){



}


//solve A[i,k]
int pieceOne(int i, int k, vector<vector<int>> table){
    if(i == k)
        return 0;
    else
        return table[i][k];
}


//solve A[k+1,j]
int pieceTwo(int k, int j, vector<vector<int>> table){
    //increment k
    k++;

    if(k == j)
        return 0;
    else
        return table[k][j];
}


//solve P_i-1 * P_k * P_j
int pieceThree(int i, int k, int j, vector<vector<int>> table){

}

/*end base end*/


int main() {
    //variables
    vector<MatrixCombo> matrices = getMatrices();
    vector<vector<int>> table = initializeTable(matrices.size());
    vector<int> pList = getPList(matrices);
    vector<Combo> matrixWorkCombos = getMatrixCombinations(table, matrices.size());



    //equation
    // A[i,j] = A[i,k] + A[k+1,j] + P_i-1 * P_k * P_j



    //printTable(table);


    int a;
    cin>>a;
    return 0;
}