#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <QWidget>
#include "qcustomplot.h"
#include"mainwindow.h"
#include <QImage>
class MainWindow;
namespace Ui {
class Histogram;
}
class Histogram : public QWidget
{
    Q_OBJECT

public:
    explicit Histogram(QWidget *parent = nullptr);
    ~Histogram();
       void showhistogram(QString& fileName);
       void SetFileName(QString&name);
private slots:

private:
    Ui::Histogram *ui;
    QCustomPlot *plot;
    QString fileName;
};

#endif // HISTOGRAM_H
