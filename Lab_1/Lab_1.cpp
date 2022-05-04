#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class FileStream {
    private:
        string filename;
    
    public:
        FileStream(string inputFile) {
            filename = inputFile;
        }

        char* readFile() {
            long size;
            shared_ptr<unsigned char> memblock(nullptr);
            // opens a file in binary mode
            ifstream file(filename, ios::binary);
            // check for open file
            if (file.is_open())
            {
                // go to the beginning of the file
                file.seekg(0, ios::end);
                // go to the end of the file (size = endoffile-beginoffile)
                size = file.tellg();
                // declares a memory block for the size of the file
                memblock = make_shared<unsigned char>(new unsigned char[size]);
                // go to beginning of the file
                file.seekg(0, ios::beg);
                // read in 'size' of characters into memblock
                file.read((char*)memblock.get(), size);
                // prints the characters
                cout << memblock << endl;
                // closes file
                file.close();

                return (char*)memblock.get();
            }

        }
};

class Database {
    private:
        string encrypted;
        vector< tuple<string, string, string> > keys;
    
    public:
        Database(string str) {
            encrypted = str;
            keys = { make_tuple("A", ".-", "1001"), make_tuple("B", "-...", "01101010"), make_tuple("C", "-.-.", "01100110"), make_tuple("D", "-..", "011010"),
                     make_tuple("E", ".", "10"), make_tuple("F", "..-.", "10100110"), make_tuple("G", "--.", "010110"), make_tuple("H", "....", "10101010"),
                     make_tuple("I", "..", "1010"), make_tuple("J", ".---", "10010101"), make_tuple("K", "-.-", "011001"), make_tuple("L", ".-..", "10011010"),
                     make_tuple("M", "--", "0101"), make_tuple("N", "-.", "0110"), make_tuple("O", "---", "010101"), make_tuple("P", ".--.", "10010110"),
                     make_tuple("Q", "--.-", "01011001"), make_tuple("R", ".-.", "100110"), make_tuple("S", "...", "101010"), make_tuple("T", "-", "01"),
                     make_tuple("U", "..-", "101001"), make_tuple("V", "...-", "10101001"), make_tuple("W", ".--", "100101"), make_tuple("X", "-..-", "01101001"),
                     make_tuple("Y", "-.--", "01100101"), make_tuple("Z", "--..", "01011010"), make_tuple("Ä", ".-.-", "10011001"), make_tuple("Ö", "---.", "01010110"),
                     make_tuple("Ü", "..--", "10100101"), make_tuple("Ch", "----", "01010101"), make_tuple("0", "-----", "0101010101"), make_tuple("1", ".----", "1001010101"),
                     make_tuple("2", "..---", "1010010101"), make_tuple("3", "...--", "1010100101"), make_tuple("4", "....-", "1010101001"), make_tuple("5", ".....", "1010101010"),
                     make_tuple("6", "-....", "0110101010"), make_tuple("7", "--...", "0101101010"), make_tuple("8", "---..", "0101011010"), make_tuple("9", "----.", "0101010110"),
                     make_tuple(".", ".-.-.-", "100110011001"), make_tuple(",", "--..--", "010110100101"), make_tuple("?", "..--..", "101001011010"), make_tuple("!", "..--.", "1010010110"),
                     make_tuple(":", "---...", "010101101010"), make_tuple("\"", ".-..-.", "100110100110"), make_tuple("'", ".----.", "100101010110"), make_tuple("=", "-...-", "0110101001"),
                  };
        }

        string getEncrypted() {
            return encrypted;
        }

        vector< tuple<string, string, string> >& getKeys() {
            return keys;
        }
};

class Process {
    private:
        string encrypted;
        vector<char> a;
        unsigned int length;
        vector<int> indices;
        Database db;

    private:

        /*
        Algorithm Search(binchar) // “0101”
            foreach tup in tupleList
            if tup.binary == binchar
            return tup
            return null
        Algorithm Decrypt(encryptedstring)    // “QRb¢$”
            decryptedstring = Empty 
            for chr in encryptedstring
            found = tupleList.Search(chr)    // “0101”
            decryptedstring.append(found.ascii)
        */
        string decrypt() {
            string decrypted = "";
            tuple<string, string, string> found;
            for(int i = 0; i < encrypted.length(); i++) {
                found = search(encrypted[i]);
                
            }
        }

    public:
        Process(Database &dbase) {
            db = dbase;
        }

        string process() {
            return decrypt();
        }
};

class OutputStream {
    public:
        void run(string str) {
            FileStream fs(str);
            string encrypted(fs.readFile());
            Database db(encrypted);
            Process p(db);
            cout << "\n\n\nDecrypted Text:\n\n";
            cout << p.process() << "\n\n\n" << endl;
        }
};


int main() {
    OutputStream os;
    os.run("encrypt.txt");
    return 0;
}