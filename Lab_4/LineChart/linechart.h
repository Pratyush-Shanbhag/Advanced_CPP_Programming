#ifndef LINECHART_H
#define LINECHART_H

#include <QMainWindow>

class LineChart : public QMainWindow
{
    Q_OBJECT

public:
    LineChart(QWidget *parent = nullptr);
    ~LineChart();
};
#endif // LINECHART_H
