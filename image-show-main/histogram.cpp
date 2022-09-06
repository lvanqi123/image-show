#include "histogram.h"
#include "ui_histogram.h"
#include <QString>
#include <QFileDialog>
Histogram::Histogram(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Histogram)
{
     ui->setupUi(this);

     plot=new QCustomPlot(ui->histogram);
     plot->resize(ui->histogram->width(),ui->histogram->height());
     plot->xAxis->setLabel(tr("灰度值"));
     plot->yAxis->setLabel(tr("像素点"));
     plot->addGraph();
     QCPTextElement *title = new QCPTextElement(plot,tr("灰度直方图"));
     plot->plotLayout()->insertRow(0);
     plot->plotLayout()->addElement(0,0,title);
     plot->xAxis->setRange(0,255);
     plot->graph(0)->setLineStyle(QCPGraph::lsImpulse);

 }



Histogram::~Histogram()
{
    delete ui;
}

void Histogram::SetFileName(QString& name)
{
    fileName = name;
}

void Histogram::showhistogram(QString& fileName)
{
    if(fileName.isEmpty())
        return;
    QImage image(fileName);
    if(!image.allGray())
    {

        image = image.convertToFormat(QImage::Format_Grayscale8);
    }

    if(!image.isNull())
    {
        int nWidth = image.width();
        int nHeight =image.height();
        QVector<double> vecX;
        QVector<double> vecY(256,0);   //init Y data with 0;
        int i = 0;
        while (256 != i) {
            vecX.append(i);
            ++i;
        }

        for(int j = 0; j < nHeight; j++)
        {
            for(int k = 0; k < nWidth; k ++)
            {
                int nIndex = int(image.bits()[j*nHeight + k]);
                vecY[nIndex] = vecY.at(nIndex) + 1;
            }
        }

        double yMax = 0;
        for(int j = 0; j < 256 ; j++)
        {
            if(yMax < vecY.at(j))
                yMax = vecY.at(j);
        }
        plot->yAxis->setRange(0,yMax);
        plot->graph(0)->setData(vecX,vecY);
        plot->replot();

    }
}
