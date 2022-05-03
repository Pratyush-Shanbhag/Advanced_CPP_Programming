#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string getBitRep(unsigned char c) {
    bitset<8> bit(c);
    return bit.to_string();
}

int main() {
    string s = "QR";
    for(int i = 0; i < s.length(); i++) {
        cout << getBitRep(s[i]) << endl;
    }

    return 0;
}