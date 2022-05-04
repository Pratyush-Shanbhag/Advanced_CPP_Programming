#include <iostream>
#include <string>
#include <bitset>

using namespace std;

string getBitRep(unsigned char c) {
    bitset<8> bit(c);
    return bit.to_string();
}

void a() {
    unsigned long c = 'Q';
    bitset<8> bit(c);
    bitset<8> as("0101");
    bitset<8> bi("11");
    bitset<8> result = bit >> 6 & bi;
    cout << result << endl;
   // bitset<2>  = result
    cout << as.to_ulong() << endl;
    cout << char(101) << endl;
}

int main() {
    /*string s = "QR";
    for(int i = 0; i < s.length(); i++) {
        cout << getBitRep(s[i]) << endl;
    }*/
    
    a();

    return 0;
}