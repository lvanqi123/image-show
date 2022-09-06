#include "api.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
Api::Api()
{

}
void Api:: brightcontrast(int bright,float con,Mat&newimage)
{
       uchar*imgdata=newimage.data;
       int pixels=newimage.rows*newimage.cols;
       for(int pix=0;pix<pixels;pix++)
       {
         imgdata[0] =cv::saturate_cast<uchar>(con*(imgdata[0])+bright);
         imgdata[1] =cv::saturate_cast<uchar>(con*(imgdata[1])+bright);
         imgdata[2] =cv::saturate_cast<uchar>(con*(imgdata[2])+bright);
         imgdata+=3;
        }
}
