#include "lab_4_qt.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

#include <QFile>
#include <QTextStream>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <algorithm>

QT_USE_NAMESPACE

using namespace std;

class InputStream {
    public:
        void readcsv(vector<pair<int, double> > &v) {
            QFile file("/Users/pratshan11/Documents/Projects/CIS_29/Lab_4/co2.csv");
            file.open(QIODevice::ReadOnly);
            QTextStream stream(&file);
            QString line;

            string str;
            int year;
            double sum = 0.0;
            int count = 0;
            int i;
            for(i = 0; i < 3; i++)
                line = stream.readLine();
            while(!stream.atEnd()) {
                line = stream.readLine();
                str = line.toStdString();
                stringstream ss(str);
                getline(ss, str, ',');
                year = stoi(str);
                for(i = 0; i < 4; i++) {
                    getline(ss, str, ',');
                }
                sum += stod(str);
                count++;
                if(count%12 == 0) {
                    v.push_back(make_pair(year, sum/12));
                    sum = 0.0;
                }
            }
            v.push_back(make_pair(year, sum/11));
        }
};


class Process {
    private:
        //shared_ptr<vector<pair<int, double> > > v;
        shared_ptr<vector<pair<int, double> > > pv;

    public:
        Process(shared_ptr<vector<pair<int, double> > > pvIn) {
            pv = pvIn;
        }
        void calcLinReg(pair<double, double> &consts) {
            double sumX = 0;
            double sumX2 = 0;
            double sumY = 0;
            double sumXY = 0;

            for(auto &p: *pv) {
                sumX += p.first;
                sumX2 += p.first * p.first;
                sumY += p.second;
                sumXY += p.first * p.second;
            }

            double a = (pv->size() * sumXY - sumX * sumY)/(pv->size() * sumX2 - sumX * sumX);
            double b = (sumY - a*sumX)/pv->size();

            consts = make_pair(a, b);
        }
};


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    vector<pair<int, double> > v;
    InputStream is;
    is.readcsv(v);

    Process p(make_shared<vector<pair<int, double> > >(v));
    pair<double, double> consts;
    p.calcLinReg(consts);
    QTextStream(stdout) << consts.first << ", " << consts.second;

    QScatterSeries *series = new QScatterSeries();

    for(auto elem: v) {
        series->append(elem.first, elem.second);
    }

    QLineSeries *lseries = new QLineSeries();

    for(auto elem: v) {
        lseries->append(elem.first, consts.first * elem.first + consts.second);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(lseries);
    chart->createDefaultAxes();
    chart->setTitle("CO2 Data");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(1400, 700);
    window.show();

    return a.exec();
}
