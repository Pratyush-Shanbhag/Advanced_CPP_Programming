#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <regex>
#include <vector>

using namespace std;

void readxml() {
    ifstream infile;
    infile.open("/uploads/ProductPrice.xml");

    map<string, pair<string, string> > m;

    string line;
    regex pat(">(.*?)<");
    smatch first;
    smatch second;
    smatch third;
    string f;
    string s;
    string t;

    while(getline(infile, line)) {
        getline(infile, line);
        regex_search(line, first, pat);
        f = first.str(1);

        getline(infile, line);
        regex_search(line, second, pat);
        s = second.str(1);

        getline(infile, line);
        regex_search(line, third, pat);
        t = third.str(1);

        getline(infile, line);

        m.insert(make_pair(f, make_pair(s, t)));
    }

    infile.close();

    for(const auto& elem : m) {
        cout << elem.first << " " << elem.second.first << " " << elem.second.second << endl;
    }
}

void readcsv() {
    ifstream infile;
    infile.open("/uploads/Carts.csv");

    vector<pair<string, vector<string> > > v;

    string line;
    string num;
    string str;

    while(getline(infile, str)) {
        stringstream ss1(str);
        ss1 >> str;
        getline(infile, line);
        stringstream ss2(line);
        vector<string> cv;
        while(getline(ss2, num, ',')) {
            cv.push_back(num);
        }
        v.push_back(make_pair(str, cv));
    }

    infile.close();

    for(const auto& elem : v) {
        cout << elem.first << " ";
        for(const auto& n : elem.second) {
            cout << n << " ";
        }
        cout << endl;
    }
}

int main() {
    //readxml();
    //cout << endl;
    readcsv();
    return 0;
}