#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

void func(string filename) {
    ifstream infile;
    infile.open(filename);
    string line;
    smatch first;
    smatch second;
    regex pat1("\\('?(.)");
    regex pat2(",(.*)(\\))");
    while(getline(infile, line)) {
        regex_search(line, first, pat1);
        regex_search(line, second, pat2);
        cout << first[1] << " " << second[1] << endl;
    }
    infile.close();
}

int main() {
    func("AsciiFrequenciesV3.txt");

    return 0;
}
///Users/pratyush/Library/Mobile Documents/com~apple~CloudDocs/Documents/Projects/CIS_29/Lab_2/test_regex.cpp
//g++ -std=c++11 *.cpp -o run   