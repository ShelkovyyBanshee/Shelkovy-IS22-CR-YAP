#include <iostream>
#include <string>
using namespace std;

int hashSym(char sym, int k)
{
    return (int)sym % k;
}

bool checkString(string str, int* symToIndexTable, int hashK, int** stateMovesTable, string symsExpected)
{
    int strLen = (int)str.length();
    int currentState = 2;
    char sym;

    for (int i = 0; i < strLen; i++)
    {
        sym = str[i];

        if (symsExpected.find(sym) == symsExpected.npos)
            return false;

        int symIndex = symToIndexTable[hashSym(sym, hashK)];
        currentState = stateMovesTable[currentState][symIndex];
    }

    return currentState == 0;
}

int main()
{
    const int hashK = 25;
    const int symsAmount = 16;
    const int statesAmount = 13;
    int stateMovesTable[statesAmount][symsAmount] =
    {
        //       0  1  2  3  4  5  6  7  8  9  .  E  +  -  ;  #
               { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // дa 0
               { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, // нет 1
               { 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 3, 3, 1, 0}, // число 2
               { 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 1, 1, 1, 1}, // знпер 3
               { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 6, 1, 1, 1, 1, 1}, // первцифц0 4
               { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 1, 1, 1, 1, 1}, // цифц 5
               { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 1, 1, 1, 1, 1}, // точ 6
               { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 1, 8, 1, 1, 1, 1}, // цифдр 7
               {10,11,11,11,11,11,11,11,11,11, 1, 1, 9, 9, 1, 1}, // Е 8
               {10,11,11,11,11,11,11,11,11,11, 1, 1, 1, 1, 1, 1}, // знст 9
               { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0}, // первцифст0 10
               {11,11,11,11,11,11,11,11,11,11, 1, 1, 1, 1,12, 0}, // цифст 11
               { 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 1, 1, 3, 3, 1, 1}, // раздел 12
    };

    int** stateMovesTableCopy = new int* [statesAmount];
    for (int i = 0; i < statesAmount; i++)
    {
        stateMovesTableCopy[i] = new int[symsAmount];
    }

    for (int i = 0; i < statesAmount; i++)
        for (int j = 0; j < symsAmount; j++)
            stateMovesTableCopy[i][j] = stateMovesTable[i][j];

    int* symToIndexTable = new int[hashK];
    symToIndexTable[hashSym('0', hashK)] = 0;
    symToIndexTable[hashSym('1', hashK)] = 1;
    symToIndexTable[hashSym('2', hashK)] = 2;
    symToIndexTable[hashSym('3', hashK)] = 3;
    symToIndexTable[hashSym('4', hashK)] = 4;
    symToIndexTable[hashSym('5', hashK)] = 5;
    symToIndexTable[hashSym('6', hashK)] = 6;
    symToIndexTable[hashSym('7', hashK)] = 7;
    symToIndexTable[hashSym('8', hashK)] = 8;
    symToIndexTable[hashSym('9', hashK)] = 9;
    symToIndexTable[hashSym('.', hashK)] = 10;
    symToIndexTable[hashSym('E', hashK)] = 11;
    symToIndexTable[hashSym('+', hashK)] = 12;
    symToIndexTable[hashSym('-', hashK)] = 13;
    symToIndexTable[hashSym(';', hashK)] = 14;
    symToIndexTable[hashSym('#', hashK)] = 15;

    string symsExpected = "0123456789+-.E;#";
    string strToCheck;
    cin >> strToCheck;
    if (checkString(strToCheck, symToIndexTable, hashK, stateMovesTableCopy, symsExpected))
        cout << "STRING is RIGHT";
    else
        cout << "STRING is WRONG";
    cout << endl;

    delete[] symToIndexTable;

    for (int i = 0; i < statesAmount; i++)
        delete[] stateMovesTableCopy[i];
    delete[] stateMovesTableCopy;
    return 0;
}


