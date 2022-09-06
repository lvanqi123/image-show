#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "histogram.h"
#include "api.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\types_c.h>
#include <QFileDialog>
#include <QImage>
#include <QLabel>
using namespace cv;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    contrast=1;
    bright=0;
    QImage grayimage;


}

MainWindow::~MainWindow()
{
    delete ui;


}

//打开图片
void MainWindow::on_open_triggered()
{
    fileName = QFileDialog::getOpenFileName(
                   this, "open image file",
                   ".",
                   "Image files (*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.jpeg *.xpm);;All files (*.*)");
    if(fileName.isEmpty())
    {
        return;
    }
    QImage src;
    src.load(fileName);
    ui->label->setPixmap(QPixmap::fromImage(src.scaled(ui->label->size(),Qt::KeepAspectRatio)));
    QByteArray a;
     a.append(fileName);
    oldImage=imread(a.data());
}
//顺时针旋转90°
void MainWindow::on_rotateright_triggered()
{
     QImage image(ui->label->pixmap()->toImage());
        QMatrix matrix;
       matrix.rotate(90.0);//顺时针旋转90度
       image= image.transformed(matrix,Qt::FastTransformation);
       ui->label->setPixmap(QPixmap::fromImage(image));
       ui->label->setAlignment(Qt::AlignCenter);
}
//水平镜像
void MainWindow::on_Horizontalmirror_triggered()
{
    QImage image(ui->label->pixmap()->toImage());
      image= image.mirrored(true, false);
      ui->label->setPixmap(QPixmap::fromImage(image));
      ui->label->setAlignment(Qt::AlignCenter);
}
//颜色转换
QImage MainWindow::QCVMat2QImage(Mat& mat)
{
    const unsigned char* data = mat.data;
    int width = mat.cols;
    int height = mat.rows;
    int bytesPerLine = static_cast<int>(mat.step);
    switch(mat.type())
    {
        //8 bit , ARGB
        case CV_8UC4:
        {
            QImage image(data, width, height, bytesPerLine, QImage::Format_ARGB32);
            return image;
        }

        //8 bit BGR
        case CV_8UC3:
        {
            QImage image(data, width, height, bytesPerLine, QImage::Format_RGB888);
            //swap blue and red channel
            return image.rgbSwapped();
        }

        //8 bit Gray shale
        case CV_8UC1:
        {
            QImage image(data, width, height, bytesPerLine, QImage::Format_Grayscale8);
            return image;
        }
        default:
        {
            return QImage();
        }
    }
}
//亮度调节
void MainWindow::on_brightnessSlider_valueChanged()
{

    contrast=ui->contrastSlider->value();
   float con=1+(float)contrast/100;
     bright=ui->brightnessSlider->value();

    Mat newimage=Mat(oldImage.rows,oldImage.cols,oldImage.type());
    oldImage.copyTo(newimage);
    Api A;
    A.brightcontrast(bright,con,newimage);

    QImage dest=QCVMat2QImage(newimage);
   ui->label->setPixmap(QPixmap::fromImage(dest.scaled(ui->label->size(),Qt::KeepAspectRatio)));
}

//显示原图
void MainWindow::on_reduction_triggered()
{
    ui->brightnessSlider->valueChanged(0);
    ui->contrastSlider->valueChanged(0);
    QImage image(fileName);
    ui->label->setPixmap(QPixmap::fromImage(image.scaled(ui->label->size(),Qt::KeepAspectRatio)));
}
//对比度调节
void MainWindow::on_contrastSlider_valueChanged()
{
    contrast=ui->contrastSlider->value();
   float con=1+(float)contrast/100;
     bright=ui->brightnessSlider->value();

    Mat newimage=Mat(oldImage.rows,oldImage.cols,oldImage.type());
    oldImage.copyTo(newimage);
    Api A;
    A.brightcontrast(bright,con,newimage);
    QImage dest=QCVMat2QImage(newimage);
    ui->label->setPixmap(QPixmap::fromImage(dest.scaled(ui->label->size(),Qt::KeepAspectRatio)));
}

//灰度图
void MainWindow::on_grayaction_triggered()
{
    if (colorful){
        cvtColor(oldImage, grayImage, COLOR_RGB2GRAY);
        QImage dest=QCVMat2QImage(grayImage);
        ui->label->setPixmap(QPixmap::fromImage(dest.scaled(ui->label->size(),Qt::KeepAspectRatio)));

         }
    else
    {
        Mat colorImage;
        cvtColor(oldImage, colorImage,COLOR_RGBA2RGB);
        QImage grayimage=QCVMat2QImage(colorImage);
        ui->label->setPixmap(QPixmap::fromImage(grayimage.scaled(ui->label->size(),Qt::KeepAspectRatio)));
    }
   colorful = !colorful;
}
//显示灰度直方图
void MainWindow::on_actionHistogram_triggered()
{
    Histogram*widget=new Histogram(nullptr);
    widget->showhistogram(fileName);
    widget->show();

}


