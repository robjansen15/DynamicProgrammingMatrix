#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "MatrixCombo.h"
#include "Combo.h"

using namespace std;

/*PRELIMINARY WORK*/
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
            cout<<table[i][j]<<"\t\t\t";
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
/*PRELIMINARY WORK*/



/*TABLE CREATION ALGORITHM*/
//solve A[i,k]
int pieceOne(int i, int k, vector<vector<int>> table){
    if(i == k)
        return 0;
    else
        return table[i-1][k-1];
}


//solve A[k+1,j]
int pieceTwo(int k, int j, vector<vector<int>> table){
    //increment k
    k++;

    if(k == j)
        return 0;
    else
        return table[k-1][j-1];
}


//solve P_i-1 * P_k * P_j
int pieceThree(int i, int k, int j,vector<int> pList){
    return pList[i-1] * pList[k] * pList[j];
}


//solve combo
int lowestComboValue(vector<vector<int>> table, vector<int> pList, int x, int y, int priority) {
    vector<int> minimumList;

    //get the value
    for(int z = 0; z < priority; z++){
        int i = x+1;
        int k = i+z;
        int j = y+1;

        minimumList.push_back(pieceOne(i, k, table) + pieceTwo(k, j, table) + pieceThree(i, k, j, pList));
    }

    //find the min value
    int min = minimumList[0];
    for(int i = 0; i < minimumList.size(); i++){
        if(min > minimumList[i])
            min = minimumList[i];
    }

    return min;
}


vector<vector<int>> solveTable(vector<vector<int>> table, vector<int> pList, vector<Combo> matrixWorkCombos){
    //solve each matrix work combinations for the minimum
    int maxPriority = matrixWorkCombos[0].priority_;

    //get the max priority or number of times
    for(int i = 0; i < matrixWorkCombos.size(); i++){
        if(maxPriority < matrixWorkCombos[i].priority_){
            maxPriority = matrixWorkCombos[i].priority_;
        }
    }

    /*
     * BAD HARD CODING, but just need to get the assignment done
     */


    //execute priority by priority
    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 1){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 2){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 3){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 4){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 5){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 6){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 7){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 8){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 9){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    for(int i = 0; i < matrixWorkCombos.size(); i++){
        //solve the piece if we have the correct priority
        if(matrixWorkCombos[i].priority_ == 10){
            int min = lowestComboValue(table, pList, matrixWorkCombos[i].x_, matrixWorkCombos[i].y_, matrixWorkCombos[i].priority_);
            table[matrixWorkCombos[i].x_][matrixWorkCombos[i].y_] = min;
        }
    }


    printTable(table);

    return table;
}
/*END TABLE CREATION ALGORITHM*/




/*START MIN PATH ALGORITHM*/

int getMinPath(vector<vector<int>> table){
    int max = table.size();
    int min = 0;







    return min;
}



/*END MIN PATH ALGORITHM*/

int main() {
    //variables / preliminary work
    vector<MatrixCombo> matrices = getMatrices();
    vector<vector<int>> table = initializeTable(matrices.size());
    vector<int> pList = getPList(matrices);
    vector<Combo> matrixWorkCombos = getMatrixCombinations(table, matrices.size());

    //solves the table
    cout<<"Table:"<<endl;
    table = solveTable(table, pList, matrixWorkCombos);



    //minimal work path
    int path = getMinPath(table);
    cout<<endl<<endl<<"The minimum path: "<<path<<endl;





    int a;
    cin>>a;
    return 0;
}