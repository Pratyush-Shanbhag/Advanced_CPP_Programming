#include <iostream>
#include <string>
#include <bitset>

using namespace std;

int main() {
    unsigned char c = 'Q';
    bitset<8> bit(c);
    cout << bit.to_string() << endl;

    return 0;
}