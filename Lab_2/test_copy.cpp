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

        map<string, double> readFreq() {
            map<string, double> m;
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
                m.insert(make_pair(first.str(1), stod(second.str(1))));
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

class Branch:Node {
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

class Leaf:Node {
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
    vector<Node*> vdata;
    public:
        Priority_Queue() { }
        Node* top()
        {
            if (vdata.size() > 0)
            return vdata[0];
            return *vdata.end();
        }
        int size() { return vdata.size(); }
        bool empty() { return vdata.size() < 1; }
        void push(Node* n)
        {
            vdata.push_back(n);
            sort(vdata.begin(), vdata.end(),
            [](Node* a, Node* b)
            {
                // return a->symbol() < b->symbol();
                return a->freq() < b->freq();
            });
        }
        void pop() { vdata.erase(vdata.begin()); }
        void print()
        {
            for_each(vdata.begin(), vdata.end(),
            [](Node* n)
            {
                // cout << n->key() << '\t' << n->value() << endl;
                cout << n->symbol() << '\t' << n->freq() << endl;
            });
        }
};

class Process {
    private:
        Priority_Queue pq;
        map<string, double> m;
    
    public:
        void process(map<string, double> srcM) {
            m = sortMap(srcM);
        }
        
        bool compare(pair<string, double>& a, pair<string, double>& b) {
            return a.second < b.second;
        }

        map<string, double> sortMap(map<string, double> &srcM) {
            vector<pair<string, double> > v;
            for(auto &x: srcM) {
                v.push_back(x);
            }

            sort(v.begin(), v.end(), compare);

            map<string, double> m(v.begin(), v.end());

            return m;
        }
};

int main() {
    FileStream fs;
    cout << fs.readFile() << endl;
    Process p;
    p.process(fs.readFreq());
    return 0;
}
