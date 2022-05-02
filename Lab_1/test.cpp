#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// C style
void CBinaryFiles(string sfile)
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
        delete[] memblock;
    }
}
int main()
{
    CBinaryFiles("Morse.bin");

    return 0;
}