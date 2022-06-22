#include "lab_4_qt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

Lab_4_QT::Lab_4_QT(QWidget *parent)
    : QMainWindow(parent)
{
}

Lab_4_QT::~Lab_4_QT()
{
}

class InputStream {
    public:
        shared_ptr<vector<pair<int, double> > > readcsv() {
            vector<pair<string, vector<string> > > v;
            ifstream infile;
            infile.open("co2.csv");

            string line;
            int year;
            double avg;
            double sum = 0.0;
            int count = 0;
            int i;
            for(i = 0; i < 3; i++) {
                getline(infile, line);
            }
            while(getline(infile, line)) {
                stringstream ss(line);
                getline(ss, year, ',');
                for(i = 0; i < 3; i++) {
                    getline(ss, avg, ',');
                }
                sum += avg;
                count++;
                if(count%12 == 0) {
                    v.push_back(make_pair(year, sum));
                    sum = 0.0;
                }
            }

            infile.close();

            return make_shared<vector<pair<int, double> > >(v);
        }
};

class Database {
    private:
        shared_ptr<vector<pair<int, double> > > v;

    public:
        Database(shared_ptr<vector<pair<int, double> > > vIn) {
            v = vIn;
        }
        shared_ptr<vector<pair<int, double> > > getData() { return v; }
};

class Process {
    private:
        shared_ptr<Database> db;

    public:
        Process(shared_ptr<Database> dbase) {
            db = dbase;
        }
        void process() {

        }
};









