#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;
// C style
string CBinaryFiles(string sfile)
{
    long size;
    unsigned char* memblock;
    // opens a file in binary mode
    ifstream file(sfile, ios::binary);
    // check for open file
    if (file.is_open())
    {
        // go to the beginning of the file
        file.seekg(0, ios::end);
        // go to the end of the file (size = endoffile-beginoffile)
        size = file.tellg();
        // declares a memory block for the size of the file
        memblock = new unsigned char[size];
        // go to beginning of the file
        file.seekg(0, ios::beg);
        // read in 'size' of characters into memblock
        file.read((char*)memblock, size);
        // prints the characters
        cout << memblock << endl;
        // closes file
        file.close();
        // cleans up pointer
        string a(reinterpret_cast<char*>(memblock));
        delete[] memblock;
        return a;
    }
}

string StringToBinString(const string& str) {
    string binString = "";
    unsigned char c;
    for(int i = 0; i < str.length(); i++) {
        c = str[i];
        binString += bitset<8>(c).to_string();
    }
    return binString;
}

int main()
{
    string out = CBinaryFiles("Morse.bin");
    cout << out << "\n\n\n";
    unsigned char c;
    for(int i = 0; i < out.length(); i++) {
        c = out[i];
        cout << out[i] << " " << int(c) << "\n";
    }
    string s = StringToBinString(out);
    cout << "\n" << s << "\n" << out.length() << " " << s.length() << endl;
    return 0;
}