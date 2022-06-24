#include "lab_4_qt.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <QFile>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <memory>
#include <algorithm>

QT_USE_NAMESPACE

using namespace std;

class InputStream {
    public:
        void readcsv(vector<pair<int, double> > &v) {
            // /Users/pratshan11/Documents/Projects/CIS_29/Lab_4/co2.csv
            ifstream infile;
            infile.open("co2.csv");

            string str;
            int year;
            double sum = 0.0;
            int count = 0;
            int i;
            for(i = 0; i < 3; i++) {
                getline(infile, str);
            }
            while(getline(infile, str)) {
                stringstream ss(str);
                getline(ss, str, ',');
                year = stoi(str);
                for(i = 0; i < 3; i++) {
                    getline(ss, str, ',');
                }
                sum += stod(str);
                count++;
                if(count%12 == 0) {
                    v.push_back(make_pair(year, sum));
                    sum = 0.0;
                }
            }

            infile.close();
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

class QTManager {
    private:
        shared_ptr<Database> db;

    public:
        QTManager(shared_ptr<Database> dbase) {
            db = dbase;
        }
        void graph() {
            //![1]
                QLineSeries *series = new QLineSeries();
            //![1]

            //![2]
                for(auto elem : *(db->getData())) {
                    series->append(elem.first, elem.second);
                }

            //![2]

            //![3]
                QChart *chart = new QChart();
                chart->legend()->hide();
                chart->addSeries(series);
                chart->createDefaultAxes();
                chart->setTitle("CO2 Data");
            //![3]

            //![4]
                QChartView *chartView = new QChartView(chart);
                chartView->setRenderHint(QPainter::Antialiasing);
            //![4]


            //![5]
                QMainWindow window;
                window.setCentralWidget(chartView);
                window.resize(400, 300);
                window.show();
            //![5]
    }
};

class OutputStream {
    public:
        void run() {
            vector<pair<int, double> > v;
            //InputStream is;
            //is.readcsv(v);
            for(int i = 1; i <= 10; i++) {
                v.push_back(make_pair(i, i));
            }
            shared_ptr<Database> db = make_shared<Database>(make_shared<vector<pair<int, double> > >(v));
            QTManager qm(db);
            qm.graph();
            //Process p(db);
            //p.process();
        }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //OutputStream os;
    //os.run();
    vector<pair<int, double> > v;
    //InputStream is;
    //is.readcsv(v);
    for(int i = 1; i <= 10; i++) {
        v.push_back(make_pair(i, i));
    }
    //![1]
        QLineSeries *series = new QLineSeries();
    //![1]

    //![2]
        for(auto elem : v) {
            series->append(elem.first, elem.second);
        }

    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("CO2 Data");
    //![3]

    //![4]
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    //![4]


    //![5]
        QMainWindow window;
        window.setCentralWidget(chartView);
        window.resize(400, 300);
        window.show();
    //![5]

    return a.exec();
}

/*
// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

QT_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//![1]
    QLineSeries *series = new QLineSeries();
//![1]

//![2]
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
//![2]

//![3]
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");
//![3]

//![4]
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
//![4]


//![5]
    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();
//![5]

    return a.exec();
}
*/
