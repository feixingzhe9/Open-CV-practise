#include <opencv2/opencv.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <vector>

using namespace cv;  
using namespace std;
int main( )  
{  
    Mat srcImage = imread("src.jpg");    
    Mat midImage,dstImage;  

    //【2】进行边缘检测和转化为灰度图  
    Canny(srcImage, midImage, 50, 200, 3);//进行一此canny边缘检测  
    cvtColor(midImage,dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图  

    //【3】进行霍夫线变换  
    vector<Vec2f> lines;  
    HoughLines(midImage, lines, 1, CV_PI/180, 150, 0, 0 );  

    //【4】依次在图中绘制出每条线段  
    for( size_t i = 0; i < lines.size(); i++ )  
    {  
        float rho = lines[i][0], theta = lines[i][1];  
        Point pt1, pt2;  
        double a = cos(theta), b = sin(theta);  
        double x0 = a*rho, y0 = b*rho;  
        pt1.x = cvRound(x0 + 1000*(-b));  
        pt1.y = cvRound(y0 + 1000*(a));  
        pt2.x = cvRound(x0 - 1000*(-b));  
        pt2.y = cvRound(y0 - 1000*(a));  
        line( dstImage, pt1, pt2, Scalar(55,100,195), 1, CV_AA);  
    }  

    imshow("【原始图】", srcImage);    

    imshow("【边缘检测后的图】", midImage);    

    imshow("【效果图】", dstImage);    

    waitKey(0);    

    return 0;    
} 
