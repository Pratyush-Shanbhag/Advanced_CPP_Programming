#include <iostream>
#include <iomanip>
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
#include <pthread.h>
#include <bitset>


using namespace std;

mutex mu;

class Database {
    private:
        shared_ptr<map<string, pair<string, double> > > m;
        shared_ptr<vector<pair<string, vector<string> > > > v;

    public:
        Database(shared_ptr<map<string, pair<string, double> > > mIn,
                 shared_ptr<vector<pair<string, vector<string> > > >vIn) {
            m = mIn;
            v = vIn;
        }
        auto getProducts() { return m; }
        auto getCarts() { return v; }
        void getProduct(string b, pair<string, double> &p) {
            mu.lock();
            p = m->find(convertHexToBin(b))->second;
            mu.unlock();
        }

        // correct: 100001100100001001001000110100001100011000100
        string convertHexToBin(string h) {
            string binstr = "";
            cout << h << "\t";
            for(int i = 0; i < h.length(); i+=3) {
                //cout << h.substr(i, 3) << "";
                bitset<12> b(stoi(h.substr(i, 3), 0, 16));
                //cout << ": ";
                binstr += b.to_string().substr(3);
            }
            //cout << endl;
            return binstr;
        }
};

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
        pair<string, double> p;

    public:
        Product(string b) { barcode = b; }
        string getBarcode() { return barcode; }
        void setItem(pair<string, double> &pIn) {
            p = make_pair(pIn.first, pIn.second);
        }
        pair<string, double>& getItem() {
            return p;
        }
        friend ostream& operator<<(ostream& os, const Product &product) {
            os << product.p.first << setw(31) << " " << product.p.second;
            return os;
        }
};

class Cart {
    private:
        string name;
    
    public:
        vector<Product> products;

    public:
        Cart(string n) { name = n; }
        void insert(Product p) { products.push_back(p); }
        int getSize() { return products.size(); }
        string getName() { return name; }
        friend ostream& operator<<(ostream& os, const Cart &cart) {
            os << "\n\n\n" << cart.name << ":\n\n";
            os << "Name" << setw(31) << " " << "Price\n";
            for(const auto& product : cart.products) {
                os << product;
            }
            return os;
        }
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
        int getSize() { return carts.size(); }
        void run() {
            while(carts.size() > 0) {
                thread th(&Queue::threadFunc, this);
                th.join();
                pop();
            }
        }
        void threadFunc() {
            int size = carts.front().products.size();
            for(int i = 0; i < size; i++) {
                pair<string, double> p;
                db->getProduct(carts.front().products.at(i).getBarcode(), p);
                carts.front().products.at(i).setItem(p);
            }
            cout << carts.front();
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
            prepare();
        }
        void prepare() {
            vector<Cart> carts;
            auto v = db->getCarts();
            int i;
            for(i = 0; i < v->size(); i++) {
                Cart c(v->at(i).first);
                for(const auto& n : v->at(i).second) {
                    c.insert(Product(n));
                }
                carts.push_back(c);
            }

            /*for(i = 0; i < carts.size(); i++) {
                queues.at(i % queues.size()).insert(carts.at(i));
            }*/
            queues.at(0).insert(carts.at(0));
        }
        void execute() {
            /*for(auto& q : queues) {
                q.run();
            }*/
            queues.at(0).run();
        }
};

class InputStream {
    public:
        void readxml(map<string, pair<string, double> > &m) {
            ifstream infile;
            infile.open("ProductPrice.xml");

            string line;
            regex pat(">(.*?)<");
            smatch first;
            smatch second;
            smatch third;
            string f;
            string s;
            double t;

            while(getline(infile, line)) {
                getline(infile, line);
                regex_search(line, first, pat);
                f = first.str(1);

                getline(infile, line);
                regex_search(line, second, pat);
                s = second.str(1);

                getline(infile, line);
                regex_search(line, third, pat);
                t = stod(third.str(1));

                getline(infile, line);

                m.insert(make_pair(f, make_pair(s, t)));
            }

            infile.close();
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
                //cout << str << endl;
                getline(infile, line);
                stringstream ss2(line);
                vector<string> cv;
                while(getline(ss2, num, ',')) {
                    cv.push_back(num);
                }
                v.push_back(make_pair(str, cv));
            }

            infile.close();
        }
};

class OutputStream {
    public:
        void run() {
            map<string, pair<string, double> > m;
            vector<pair<string, vector<string> > > v;
            InputStream is;
            is.readxml(m);
            is.readcsv(v);
            /*for(const auto& elem : v) {
                //cout << elem.first << " ";
                for(const auto& n : elem.second) {
                    cout << n << " ";
                }
                cout << endl;
            }*/
            for(const auto &elem: v.front().second) {
                cout << elem << endl;
            }
            shared_ptr<Database> db = make_shared<Database>(make_shared<map<string, pair<string, double> > >(m), make_shared<vector<pair<string, vector<string> > > >(v));
            QueueManager qm(db);
            qm.prepare();
            qm.execute();
        }
};

int main() {
    OutputStream output;
    output.run();

    return 0;
}

//jdoodle.cpp:82:35: error: ambiguous overload for ‘operator=’ (operand types are ‘Node’ and ‘std::__shared_ptr<Node, __gnu_cxx::_S_atomic>::element_type*’ {aka ‘Node*’})
