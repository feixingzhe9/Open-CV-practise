#include <stdio.h>  
#include <opencv2/opencv.hpp>  
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;  

int main(int argc, char** argv )  
{ 

#if 0
    if ( argc != 2 )  
    {  
        printf("usage: DisplayImage.out <Image_Path>\n");  
        return -1;  
    }  

    Mat image;  
    image = imread( argv[1], 1 );  

    if ( !image.data )  
    {  
        printf("No image data \n");  
        return -1;  
    }  
    namedWindow("Display Image", WINDOW_AUTOSIZE );  
    imshow("Display Image", image);  

    waitKey(0);  

    return 0;  
#endif


    cv::Mat image= cv::imread("test.jpg");    
    // create image window named "My Image"
    cv::namedWindow("My Image");
    // show the image on window
    cv::imshow("My Image", image);
    // wait key for 5000 ms
    cv::waitKey(5000);

    return 1;
}
