#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
using namespace cv;  
using namespace std;  

void Help()  
{  
    printf("\n\n  ----------------------------------------------------------------------------\n");  
}  


int main()  
{  
    //Mat srcImage = imread("histogram.jpg", 0);  
    Mat srcImage = imread("histogram.jpg");  
    if(!srcImage.data) {cout << "fail to load image" << endl;   return 0;}  
    //imshow("origin picture",srcImage);  
    //system("color 1F");  
    //Help();  

    MatND dstHist;       // 在cv中用CvHistogram *hist = cvCreateHist  
    int dims = 1;  
    float hranges[2] = {0, 255};  
    const float *ranges[1] = {hranges};   // 这里需要为const类型  
    int size = 256;  
    int channels = 0;  
    //计算图像的直方图  
    calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    // cv 中是cvCalcHist  
    cout<<"dimensional : "<<dims<<endl;
    cout<<"histogram size : "<<size<<endl;
    //cout<<"dst histogram: "<<dstHist<<endl;
    int scale = 6;  
    //Mat dstImage(size * scale, size, CV_8U, Scalar(0));  
    Mat dstImage(size, size * scale, CV_8UC3, Scalar(0,0,0));  
    //获取最大值和最小值  
    double minValue = 0;  
    double maxValue = 0;  
    minMaxLoc(dstHist,&minValue, &maxValue, 0, 0);  //  在cv中用的是cvGetMinMaxHistValue  
    //绘制出直方图  
    int hpt = saturate_cast<int>(0.9 * size);  
    for(int i = 0; i < 256; i++)  
    {  
        float binValue = dstHist.at<float>(i);           //   注意hist中是float类型      
        int realValue = saturate_cast<int>(binValue * hpt/maxValue);  
        rectangle(dstImage,Point(i*scale, size - 1), Point((i+1)*scale - 1, size - realValue), Scalar(0,255,0),2);  
        //line(dstImage,Point(i*scale,size-1),Point((i+1)*scale-1,size-realValue),Scalar(255,255,255));  
    }  
    for(int j = 1; j < 5; j++)
    {
        line(dstImage,Point(0,(size/5) * j),Point(size*scale - 1,(size/5) * j),Scalar(0,0,255),3);  
    }
    //imshow("一维直方图", dstImage);  
    imshow("one-dimensional histogram", dstImage);  
    waitKey(0);  
    return 0;  
}
