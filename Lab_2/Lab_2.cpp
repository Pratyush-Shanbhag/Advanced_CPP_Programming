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
            long fileSize;
            ifstream file("Compress.bin", ios::binary);

            file.seekg(0, ios::end);
            fileSize = file.tellg();
            file.seekg(0, ios::beg);

            vector<unsigned char> b(fileSize);
            file.read((char*) &b[0], fileSize);
            file.close();

            b.erase(std::remove_if(b.begin(), b.end(),
                [](const unsigned char& x) { 
                return int(x) < 33 || int(x) == 127;
                }), b.end());

            string s(b.begin(), b.end());
            return s;
        }

        vector<pair<string, float> > readFreq() {
            vector<pair<string, float> > v;
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
                v.push_back(make_pair(first.str(1), stof(second.str(1))));
            }
            infile.close();

            return v;
        }
};

class Node {
    public:
        Node() {}
        virtual string symbol() = 0;
        virtual float freq() = 0;
        virtual string id() = 0;
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
        string symbol() { return _Left->symbol() + _Right->symbol(); }
        float freq() { return _Left->freq() + _Right->freq(); }
        shared_ptr<Node> left() { return _Left; }
        shared_ptr<Node> right() { return _Right; }
        string id() { return "Branch"; }
};

class Leaf:public Node {
    private:
        string _symbol;
        float _freq;
    
    public:
        Leaf(string s, float f) {
            _symbol = s;
            _freq = f;
        }
        float freq() { return _freq; }
        string symbol() { return _symbol; }
        string id() { return "Leaf"; }
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
            return vdata.front(); 
        }
        int size() { return vdata.size(); }
        bool empty() { return vdata.size() < 1; }
        void push(shared_ptr<Node> n)
        {
            vdata.push_back(n);
            sort(vdata.begin(), vdata.end(),
            [](shared_ptr<Node> a, shared_ptr<Node> b)
            {
                return a->freq() < b->freq();
            });
        }
        void pop() { vdata.erase(vdata.begin()); }
        void print()
        {
            for_each(vdata.begin(), vdata.end(),
            [](shared_ptr<Node> n)
            {
                cout << n->symbol() << '\t' << n->freq() << endl;
            });
        }
};

class Process {
    private:
        Priority_Queue pq;
        vector<pair<string, float> > v;
        map<string, string> m;
        string leafName;
        string branchName;
        string enc;
    
    public:
        void process(vector<pair<string, float> > srcV, string str) {
            v = srcV;
            sortVec();
            cout << "\n\n\n";

            enc = str;

            constructPQ();
            encode(pq.top(), "");
            for(auto &e: m) {
                cout << e.first << ": " << e.second << endl; 
            }
            decrypt();
        }

        void sortVec() {
            sort(v.begin(), v.end(), [] (pair<string, float>& a, pair<string, float>& b) {return a.second < b.second;});
        }

        void constructPQ() {
            for(auto &x: v) {
                pq.push(make_shared<Leaf>(x.first, x.second));
            }

            shared_ptr<Node> left;
            shared_ptr<Node> right;
            while(pq.size() > 1) {
                left = pq.top();
                pq.pop();
                right = pq.top();
                pq.pop();
                shared_ptr<Branch> n = make_shared<Branch>(left, right);
                pq.push(n);
            }
        }

        void encode(shared_ptr<Node> n, string s) {
            if(n->id() == "Leaf") {
                m.insert({s, n->symbol()});
            }
            else if(n->id() == "Branch") {
                encode(static_pointer_cast<Branch>(n)->left(), s + "0");
                encode(static_pointer_cast<Branch>(n)->right(), s + "1");
            }
        }

        void decrypt() {
            cout << "\n\n\n\n\n\n" << endl;
            string s = "";
            unsigned char c;
            string in = "";
            int i;
            int j;

            for(i = 0; i < enc.length(); i++) {
                c = enc[i];
                bitset<8> bit(c);
                for(j = 0; j < 8; j++) {
                    in += to_string(bit[j]);
                    if(m.count(in) == 1) {
                        s += m.find(in)->second;
                        in = "";
                    }
                }
            }

            cout << "s:" << s << endl;
        }
};

int main() {
    FileStream fs;
    string str = fs.readFile();
    cout << str << "\n\n\n" << endl;
    Process p;
    p.process(fs.readFreq(), str);
    return 0;
}
