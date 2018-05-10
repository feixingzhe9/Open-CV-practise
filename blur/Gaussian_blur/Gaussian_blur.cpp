#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
using namespace cv;  
using namespace std;  


int main()  
{  
    Mat src_image = imread("src.jpg");  
    Mat gaussian_blur_image;
    if(!src_image.data) {cout << "fail to load image" << endl;   return 0;}  
    imshow("origin picture",src_image);  

    Size ksize; //Gaussian kernel size
    ksize.width = 15;
    ksize.height = 15;
    double sigmaX, sigmaY;
    sigmaX = 9;
    sigmaY = 0;
    GaussianBlur(src_image, gaussian_blur_image, ksize, sigmaX, sigmaY );
    imshow("Gaussian blur image", gaussian_blur_image);

    imwrite("Gaussian_blur.jpg", gaussian_blur_image);  
    waitKey(0);  
    return 0;  
}
