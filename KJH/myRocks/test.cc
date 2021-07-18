#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
// File open
    ifstream readFile;
    readFile.open("./factory.csv");

    if (readFile.is_open()) {
        while(!readFile.eof()) {
            string str;
            getline(readFile, str);
            cout << str << endl;
        }
        readFile.close();
    }
}
