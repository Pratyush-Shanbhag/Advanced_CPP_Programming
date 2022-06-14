#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <regex>
#include <vector>

using namespace std;

void func() {
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

int main() {
    func();
    return 0;
}