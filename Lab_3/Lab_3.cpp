#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <tuple>
#include <map>
#include <memory>
#include <algorithm>
#include <regex>
#include <thread>
#include <mutex>

using namespace std;

/*class Product {
    private:
        string barcode;
        string name;
        double price;

    public:
        Product() {}
        void setBarcode(string b) { barcode = b; }
        void setName(string n) { name = n; }
        void setPrice(double p) { price = p; }
        string getBarcode() { return barcode; }
        pair<string, double> getItem() { return make_pair(name, price); }
};*/

class Product {
    private:
        string barcode;

    public:
        Product(string b) { barcode = b; }
        string getBarcode() { return barcode; }
};

class Cart {
    private:
        string name;
        vector<shared_ptr<Product> > products;

    public:
        Cart(string n) { name = n; }
        shared_ptr<Product> top() { return products.front(); }
        void insert(shared_ptr<Product> p) { products.push_back(p); }
        void pop() { products.erase(products.begin()); }
        int size() { return products.size(); }
        string getName() { return name; }
};

/*class Queue {
    private:
        vector<Cart> carts;

    public:
        Queue() {}
        Cart top() { return carts.front(); }
        void insert(Cart c) { carts.push_back(c); }
        void pop() { carts.erase(carts.begin()); }
        int size() { return carts.size(); }
};*/

class Queue {
    private:
        vector<Cart> carts;
        shared_ptr<Database> db;

    public:
        Queue(shared_ptr<Database> dbase) { db = dbase; }
        Cart top() { return carts.front(); }
        void insert(Cart &c) { carts.push_back(c); }
        void pop() { carts.erase(carts.begin()); }
        int size() { return carts.size(); }
        void run() {
            for(int i = 0; i < carts.size(); i++) {
                thread th(a, i);
                th.join();
            }
        }
        void a(int index) {

        }
};

class QueueManager {
    private:
        vector<Queue> queues;
        shared_ptr<Database> db;

    public:
        QueueManager(shared_ptr<Database> dbase) {
            db = dbase;
            //queues.reserve(15);
            for(int i = 0; i < 15; i++) {
                queues.push_back(Queue(db));
            }
            t();
            p();
        }
        void t() {
            vector<Cart> carts;
            for(const auto& elem : db.get()->getCarts()) {
                Cart c(elem.first);
                for(const auto& n : elem.second) {
                    c.insert(make_shared<Product>(Product(n)));
                }
                carts.push_back(c);
            }

            for(int i = 0; i < carts.size(); i++) {
                queues.at(i % queues.size()).insert(carts.at(i));
            }
        }

        void p() {
        }
};

class Database {
    private:
        map<string, pair<string, string> > m;
        vector<pair<string, vector<string> > > v;
        mutex mu;

    public:
        Database() {}
        Database(map<string, pair<string, string> > mIn,
                 vector<pair<string, vector<string> > > vIn) {
            m = mIn;
            v = vIn;
        }
        const auto& getProducts() { return m; }
        const auto& getCarts() { return v; }
        void getProduct(string b, pair<string, string> &p) {
            mu.lock();
            p = m.at(convertHexToBin(b));
            mu.unlock();
        }

        // correct: 100001100100001001001000110100001100011000100
        string convertHexToBin(string h) {
            string binstr = "";
            for(int i = 0; i < h.length(); i+=3) {
                bitset<12> b(stoi(h.substr(i, 3), 0, 16));
                binstr += b.to_string().substr(3);
            }
            return binstr;
        }
};

class Process {
    private:
        shared_ptr<Database> db;
    public:
        Process(shared_ptr<Database> dbase) { db = dbase; }

        void process() {

        }

};

class InputStream {
    public:
        void readxml(map<string, pair<string, string> > &m) {
            ifstream infile;
            infile.open("ProductPrice.xml");

            string line;
            regex pat(">(.*?)<");
            smatch first;
            smatch second;
            smatch third;
            string f;
            string s;
            string t;

            while(getline(infile, line)) {
                getline(infile, line);
                regex_search(line, first, pat);
                f = first.str(1);

                getline(infile, line);
                regex_search(line, second, pat);
                s = second.str(1);

                getline(infile, line);
                regex_search(line, third, pat);
                t = third.str(1);

                getline(infile, line);

                m.insert(make_pair(f, make_pair(s, t)));
            }

            infile.close();

            for(const auto& elem : m) {
                cout << elem.first << " " << elem.second.first << " " << elem.second.second << endl;
            }
        }

        void readcsv(vector<pair<string, vector<string> > > &v) {
            ifstream infile;
            infile.open("Carts.csv");

            string line;
            string num;
            string str;

            while(getline(infile, str)) {
                stringstream ss1(str);
                ss1 >> str;
                getline(infile, line);
                stringstream ss2(line);
                vector<string> cv;
                while(getline(ss2, num, ',')) {
                    cv.push_back(num);
                }
                v.push_back(make_pair(str, cv));
            }

            infile.close();

            for(const auto& elem : v) {
                cout << elem.first << " ";
                for(const auto& n : elem.second) {
                    cout << n << " ";
                }
                cout << endl;
            }
        }
};