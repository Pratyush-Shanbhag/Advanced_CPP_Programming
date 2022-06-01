#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <memory>
#include <algorithm>
#include <regex>

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

        vector<pair<string, double> > readFreq() {
            vector<pair<string, double> > v;
            ifstream infile;
            infile.open("AsciiFrequenciesV3.txt");
            string line;
            smatch first;
            smatch second;
            regex pat1("\\('?(.)");
            regex pat2("(?!',')'*',(.*)(\\))");
            while(getline(infile, line)) {
                regex_search(line, first, pat1);
                regex_search(line, second, pat2);
                v.push_back(make_pair(first.str(1), stod(second.str(1))));
            }
            infile.close();
        }
};

class Node {
    public:
        Node();
        virtual string symbol() = 0;
        virtual float freq() = 0;
};

class Branch:public Node {
    private:
        shared_ptr<Node> _Left;
        shared_ptr<Node> _Right;
    public:
        Branch(shared_ptr<Node> n0, shared_ptr<Node> n1) {
            _Left = n0;
            _Right = n1;
        }
        string symbol() { return _Left.get()->symbol() + _Right.get()->symbol(); }
        float freq() { return _Left.get()->freq() + _Right.get()->freq(); }
        shared_ptr<Node> left() { return _Left; }
        shared_ptr<Node> right() { return _Right; }
};

class Leaf:public Node {
    private:
        string _symbol;
        float _freq;
    
    public:
        Leaf(string &s, float f) {
            _symbol = s;
            _freq = f;
        }
        float freq() { return _freq; }
        string symbol() { return _symbol; }
};

class Priority_Queue
{
    vector<shared_ptr<Node> > vdata;
    public:
        Priority_Queue() { }
        shared_ptr<Node> top()
        {
            if (vdata.size() > 0)
                return vdata[0];
            return make_shared<Node>(vdata.end());
        }
        int size() { return vdata.size(); }
        bool empty() { return vdata.size() < 1; }
        void push(shared_ptr<Node> n)
        {
            vdata.push_back(n);
            sort(vdata.begin(), vdata.end(),
            [](shared_ptr<Node> a, shared_ptr<Node> b)
            {
                // return a->symbol() < b->symbol();
                return a.get()->freq() < b.get()->freq();
            });
        }
        void pop() { vdata.erase(vdata.begin()); }
        void print()
        {
            for_each(vdata.begin(), vdata.end(),
            [](shared_ptr<Node> n)
            {
                // cout << n->key() << '\t' << n->value() << endl;
                cout << n.get()->symbol() << '\t' << n.get()->freq() << endl;
            });
        }
};

class Process {
    private:
        Priority_Queue pq;
        vector<pair<string, double> > v;
        map<string, string> m;
    
    public:
        string process(vector<pair<string, double> > srcV, string enc) {
            v = srcV;
            sortMap();
            constructPQ(v);
            encode(pq.top(), "");
            return decrypt(enc);
        }
        
        bool compare(pair<string, double>& a, pair<string, double>& b) {
            return a.second < b.second;
        }

        void sortMap() {
            sort(v.begin(), v.end(), compare);
        }

        void constructPQ(vector<pair<string, double> > &v) {
            for(pair<string, double> &x: v) {
                shared_ptr<Node> n = make_shared<Leaf>(Leaf(x.first, x.second));
                pq.push(n);
            }
            shared_ptr<Node> left;
            shared_ptr<Node> right;
            while(pq.size() > 1) {
                left = make_shared<Node>(pq.top());
                pq.pop();
                right = make_shared<Node>(pq.top());
                pq.pop();
                shared_ptr<Node> n = make_shared<Branch>(Branch(left, right));
                pq.push(n);
            }
        }

        void encode(shared_ptr<Node> n, string s) {
            if(typeid(n).name() == "Leaf") {
                m.insert(make_pair<string, string>(s, n.get()->symbol()));
            }
            else {
                encode(static_pointer_cast<Branch>(n).get()->left(), s + "0");
                encode(static_pointer_cast<Branch>(n).get()->right(), s + "1");
            }
        }

        string decrypt(string encrypted) {
            string s = "";
            unsigned char c;
            string in = "";
            for(int i = 0; i < encrypted.length(); i++) {
                c = s[i];
                bitset<8> bit(c);
                for(int j = 0; j < 8; j++) {
                    in += (bit >> j).to_string();
                    if(m.count(in) == 1) {
                        s += m.at(in);
                        in = "";
                    }
                }
            }

            return "";
        }
};

int main() {
    FileStream fs;
    cout << fs.readFile() << endl;
    Process p;
    p.process(fs.readFreq());
    return 0;
}
