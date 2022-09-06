#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "histogram.h"
#include <opencv2/opencv.hpp>
#include "api.h"
using namespace cv;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Histogram;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
   QImage QCVMat2QImage(Mat&mat);//颜色转换
    QString fileName;
      Mat oldImage;
      Mat grayImage;
private slots:
    void on_open_triggered();

    void on_rotateright_triggered();

    void on_Horizontalmirror_triggered();

    void on_brightnessSlider_valueChanged();

    void on_reduction_triggered();

    void on_contrastSlider_valueChanged();

    void on_grayaction_triggered();

    void on_actionHistogram_triggered(); 

private:
    Ui::MainWindow *ui;
    //亮度对比度
      int bright;
      float contrast;
    //灰度图转换
      bool colorful = true;
};

#endif // MAINWINDOW_H
