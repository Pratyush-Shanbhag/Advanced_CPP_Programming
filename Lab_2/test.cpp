#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <map>
#include <memory>

using namespace std;

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