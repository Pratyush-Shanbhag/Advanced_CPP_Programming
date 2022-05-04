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

        shared_ptr<unsigned char> readFile() {
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

                return memblock;
            }

        }
};

class Database {
    private:
        string encrypted;
        vector<char> rotorChars;
    
    public:
        Database(string str) {
            encrypted = str;
            rotorChars = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                     'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
                     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                     ' ', '.', ',', ';', '!', '?', '(', ')', '-', '\'', '"'};
        }

        string getEncrypted() {
            return encrypted;
        }

        vector<char> getRotorChars() {
            return rotorChars;
        }
};

class Process {
    private:
        string encrypted;
        vector<char> a;
        unsigned int length;
        vector<int> indices;

    private:
        int location(char chr) {
            int i;
            for(i = 0; i < length; i++) {
                if(a[i] == chr)
                    break;
            }
            return i;
        }

        string encrypt(int r1, int r2) {
            string str = "";
            char chr;
            for(int i = 0; i < encrypted.length(); i++) {
                chr = encrypted[i];
                str.push_back(a[(location(chr) + r1 + r2) % length]);
                r1++;
                if(r1 % length == length - 1) {
                    r2++;
                }
            }
            
            return str;
        }

        void count() {
            int num = 2;
            for(int i = 1; i < 100; i++) {
                if(location(encrypted[i]) + num == location(encrypted[i+num]))
                    indices.push_back(i);
            }
        }

        int findRotorSum() {
            int num1, num2;
            int Aloc = 0;
            int spaceLoc = 36;
            int index;
            int quotient;
            for(unsigned int i = 0; i < indices.size(); i++) {
                index = indices.at(i);

                num1 = (location(encrypted[index]) - (spaceLoc + index));
                if(num1 < 0) {
                    quotient = abs(num1) / length;
                    num1 = (num1 + length * (quotient + 1)) % length;
                }
                else
                    num1 %= length;

                num2 = (location(encrypted[index + 1]) - (Aloc + index + 1));
                if(num2 < 0) {
                    quotient = abs(num2) / length;
                    num2 = (num2 + length * (quotient + 1)) % length;
                }
                else
                    num2 %= length;                

                if(num1 == num2)
                    return num1 - 1;
            }
            return -1;
        }

        

        tuple<int, int, string> decrypt(int rSum) {
            string decrypted;
            int index;
            int n = -1;
            int inc;
            int quotient;
            do
            {
                decrypted = "";
                n++;
                inc = 0;
                for(int i = 0; i < encrypted.length(); i++) {
                    if((i + n +1) % length == 0 && i != 0)
                        inc++;
                    index = (location(encrypted[i]) - (rSum + i + inc));
                    if(index < 0) {
                        quotient = abs(index) / length;
                        index = (index + length * (quotient + 1)) % length;
                    }
                    else
                        index %= length;
                    index = index < 0 ? index + length : index;
                    decrypted.push_back(a[index]);
                }   
            } while (countFrequency(decrypted.substr(0, 99), ". ") != 1);

            return make_tuple(n, rSum - n, decrypted);
        }

        int countFrequency(const string &str, const string &target) {
            int count = 0;
            for(int i = 0; i < str.length() - target.length() + 1; i++) {
                if(target.compare(str.substr(i, 2)) == 0)
                    count++;
            }
            return count;
        }

    public:
        Process(Database &db) {
            a = db.getRotorChars();
            length = a.size();
            encrypted = db.getEncrypted();
        }

        tuple<int, int, string> process() {
            count();
            return decrypt(findRotorSum());
        }
};

class OutputStream {
    public:
        void run(string str) {
            FileStream fs(str);
            string encrypted = fs.readFile();
            Database db(encrypted);
            Process p(db);
            tuple<int, int, string> decryptedTuple = p.process();
            cout << "\nInitial Settings:\n";
            cout << "\tRotor1: " << get<0>(decryptedTuple);
            cout << "\n\tRotor2: " << get<1>(decryptedTuple);
            cout << "\n\n\nDecrypted Text:\n\n" << get<2>(decryptedTuple) << "\n" << endl;
            p.process();
        }
};


int main() {
    OutputStream os;
    os.run("encrypt.txt");
    return 0;
}