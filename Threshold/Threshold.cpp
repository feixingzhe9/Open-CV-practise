#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mat src_image;
Mat dst_image;
Mat dst_adaptive_image;
int threshold_value = 100;
int maxVal = 255;
static void change_threshold_callback(int, void *)
{
    
    threshold(src_image, dst_image, (float)threshold_value, maxVal, cv::THRESH_BINARY);  
    imshow("Threshold",dst_image);
}

int main()
{
    src_image = imread("src.jpg",IMREAD_GRAYSCALE);    
    if(!src_image.data)
    {
        cout<<"failed to load src image !"<<endl;
    }

    int adaptive_max_value = 255;  
    int blockSize = 41;  
    double C = 0;  
    adaptiveThreshold(src_image, dst_adaptive_image, adaptive_max_value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, blockSize, C);  
    imshow("Adaptive Threshold- MEAN",dst_adaptive_image);

    adaptiveThreshold(src_image, dst_adaptive_image, adaptive_max_value, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, blockSize, C);  
    imshow("Adaptive Threshold- GAUSSION",dst_adaptive_image);
    
    blockSize = 41;
    namedWindow("Threshold", 1);
    createTrackbar("Threshold Value：", "Threshold",&threshold_value, 255,change_threshold_callback);
    change_threshold_callback(threshold_value,0);

    waitKey(0);
    return 0;
}
