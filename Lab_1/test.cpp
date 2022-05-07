#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <tuple>

using namespace std;
// C style
class A {
    private:
        vector< tuple<string, string, string> > keys;

    public:
        A() {
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

        string search(string binchar) {
            for(int i = 0; i < keys.size(); i++) {
                if(get<2>(keys.at(i)) == binchar)
                    return get<0>(keys.at(i));
            }
            return "";
        }



        void callSearch(string str) {

            string s = "";
            string in = "";
            bitset<8> one("11");
            string ans;
            for(int i = 0; i < str.length(); i += 8) {
                ans = (bitset<8>(str.substr(i, 8)) >> 6 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
                


                ans = (bitset<8>(str.substr(i, 8)) >> 4 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
                


                ans = (bitset<8>(str.substr(i, 8)) >> 2 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;



                ans = (bitset<8>(str.substr(i, 8)) & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
            }
            s += search(in);
            cout << s << "\n" << endl;
        }

};

int main()
{
    A a;
    string out = a.CBinaryFiles("Morse.bin");
    string s = a.StringToBinString(out);
    a.callSearch(s);
/*    cout << out << "\n\n\n";
    unsigned char c;
    for(int i = 0; i < out.length(); i++) {
        c = out[i];
        cout << out[i] << " " << int(c) << "\n";
    }
    string s = a.StringToBinString(out);
    cout << "\n" << s << "\n" << out.length() << " " << s.length() << endl;
*/

    return 0;
}




/*
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <vector>
#include <tuple>

using namespace std;
// C style
class A {
    private:
        vector< tuple<string, string, string> > keys;

    public:
        A() {
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
                cout << c << " " << int(c) << endl;
                binString += bitset<8>(c).to_string();
            }
            return binString;
        }

        string search(string binchar) {
            for(int i = 0; i < keys.size(); i++) {
                if(get<2>(keys.at(i)) == binchar)
                    return get<0>(keys.at(i));
            }
            return "";
        }



        void callSearch(string str) {

            string s = "";
            string in = "";
            bitset<8> one("11");
            string ans;
            for(int i = 0; i < str.length(); i += 8) {
                ans = (bitset<8>(str.substr(i, 8)) >> 6 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
                


                ans = (bitset<8>(str.substr(i, 8)) >> 4 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
                


                ans = (bitset<8>(str.substr(i, 8)) >> 2 & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;



                ans = (bitset<8>(str.substr(i, 8)) & one).to_string();
                ans = ans.substr(ans.length()-2, 2);
                if(ans == "00") {
                    s += search(in);
                    in = "";
                }
                else if(ans == "11")
                    s += " ";
                else
                    in += ans;
            }
            s += search(in);
            cout << s << "\n" << endl;
        }

};

int main()
{
    A a;
    //string out = a.CBinaryFiles("Morse.bin");
    string out = "QRb"; //"QRbó6aQ";
    cout << a.StringToBinString(out) << endl;
    out += "ó";
    string s = a.StringToBinString(out);
    cout << s << endl;
    a.callSearch(s);
/*    cout << out << "\n\n\n";
    unsigned char c;
    for(int i = 0; i < out.length(); i++) {
        c = out[i];
        cout << out[i] << " " << int(c) << "\n";
    }
    string s = a.StringToBinString(out);
    cout << "\n" << s << "\n" << out.length() << " " << s.length() << endl;


    return 0;
}



#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

int main(int argc, char const *argv[])
{
    fstream file("Morse.bin" , ios::out | ios::binary | ios::in);

    auto my_str = string();

    copy_n(istream_iterator<char>(file), 
           5, 
           std::back_inserter(my_str));

    cout << "String = " << my_str<< endl ;
}

*/