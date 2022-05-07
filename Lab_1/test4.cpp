#include <iostream>
#include <bitset>
using namespace std;

wstring StringToBinString(const wstring& str) {
    wstring binString = L"";
    wchar_t c;
    for(int i = 0; i < str.length(); i++) {
        c = str[i];
        wcout << c << " " << int(c) << endl;
        string s = bitset<8>(c).to_string();
        
        wstring b(s.begin(), s.end());
        binString += b;
    }
    return binString;
}
        
int main()
{
    wstring out = L"ó";
    wchar_t o = L'ó';
    wcout << o << " " << int(o) << endl;
    wcout << StringToBinString(out) << endl;

    return 0;
}