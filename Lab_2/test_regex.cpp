#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

void func(string filename) {
   map<string, double> m;
    ifstream infile;
    infile.open(filename);
    string line;
    smatch first;
    smatch second;
    regex pat1("\\('?(.)");
    regex pat2("(?!',')'*',(.*)(\\))");
    while(getline(infile, line)) {
        regex_search(line, first, pat1);
        regex_search(line, second, pat2);
        m.insert(make_pair(first.str(1), stod(second.str(1))));
    }
    infile.close();

    for (auto itr = m.begin(); itr != m.end(); ++itr) {
        cout << itr->first << '\t' << itr->second << '\n';
    }
}

int main() {
    func("AsciiFrequenciesV3.txt");

    return 0;
}
///Users/pratyush/Library/Mobile Documents/com~apple~CloudDocs/Documents/Projects/CIS_29/Lab_2/test_regex.cpp
//g++ -std=c++11 *.cpp -o run   