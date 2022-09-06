#ifndef API_H
#define API_H
#include <QWidget>
#include "mainwindow.h"
#include <opencv2/opencv.hpp>
using namespace cv;
class Api
{
public:
    Api();
void brightcontrast(int bright,float con,Mat&oldimage);
private:

};

#endif // API_H
