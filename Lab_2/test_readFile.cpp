/*#include <iostream>
#include <fstream>
#include <string>
#include <memory>

using namespace std;

class FileStream {
    public:
        string readFile()
        {
            long size;
            // opens a file in binary mode
            ifstream file("Compress.bin", ios::binary);
            // check for open file
            if (file.is_open())
            {
                // go to the beginning of the file
                file.seekg(0, ios::end);
                // go to the end of the file (size = endoffile-beginoffile)
                size = file.tellg();
                // declares a memory block for the size of the file
                unique_ptr<unsigned char[]> memblock(new unsigned char[size]());
                // go to beginning of the file
                file.seekg(0, ios::beg);
                // read in 'size' of characters into memblock
                file.read((char*)memblock.get(), size);
                // closes file
                file.close();
                // cleans up pointer
                string a(reinterpret_cast<char*>(memblock.get()));
                return a;
            }
        }
};

int main() {
    FileStream fs;
    cout << "\n\n\n" << fs.readFile() << "asdf\n\n\n" << endl;

    return 0;
}*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>


std::vector<unsigned char> readFile(std::string filename)
{
    // open the file:
    std::streampos fileSize;
    std::ifstream file(filename, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<unsigned char> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

int main() {
    std::cout << "\n\n\n";
    std::vector<unsigned char> b = readFile("Compress.bin");
    int i;
    /*for(i = b.size()-1; i <= 0; i--) {
        if(int(b.at(i)) < 32 || int(b.at(i)) == 127) {
            b.erase(b.begin() + i);
        }
    }*/
    b.erase(std::remove_if(
    b.begin(), b.end(),
    [](const unsigned char& x) { 
        return int(x) < 33 || int(x) == 127; // put your condition here
    }), b.end());
    /*for(i = 0; i < b.size(); i++) {
        std::cout << "|" << b.at(i) << "|" << int(b.at(i)) << "\n";
    }*/
    std::cout << "\n\n\n" << std::endl;
    std::cout << b.size() << std::endl;

    return 0;
}