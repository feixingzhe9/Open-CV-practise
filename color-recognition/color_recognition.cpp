#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  
using namespace cv;  
using namespace std;  


int main()  
{  
    Mat src_image = imread("color_recognition.jpg");  
    Mat hsv_image;
    if(!src_image.data) {cout << "fail to load image" << endl;   return 0;}  
    imshow("origin picture",src_image);  

    //red HSV range  
    int iLowH = 156;    
    int iHighH = 180;    

    int iLowS = 43;     
    int iHighS = 255;    

    int iLowV = 46;    
    int iHighV = 255; 
    
    Mat threashold_image;
    Mat threashold_image_2;

    cvtColor(src_image, hsv_image,COLOR_BGR2HSV);//RGB to HSV
    inRange(hsv_image,Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV),threashold_image);
#if 1
    Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
    //morphologyEx(src_image, src_image, MORPH_TOPHAT, element);
    //morphologyEx(src_image, src_image, MORPH_BLACKHAT, element);
    //imshow("origin tophat picture",src_image);  
    morphologyEx(threashold_image, threashold_image, MORPH_CLOSE, element);//闭操作 (连接一些连通域)
    element = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(threashold_image, threashold_image, MORPH_OPEN, element);
#endif

    iLowH = 0;    
    iHighH = 10;    
    inRange(hsv_image,Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV),threashold_image_2);
#if 1
    Mat element_2 = getStructuringElement(MORPH_RECT, Size(15, 15));
    morphologyEx(threashold_image_2, threashold_image_2, MORPH_CLOSE, element_2);//闭操作 (连接一些连通域)
    element_2 = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(threashold_image_2, threashold_image_2, MORPH_OPEN, element_2);
#endif
    for(int i = 0; i < threashold_image_2.cols; i ++)
    {
        for(int j = 0; j < threashold_image_2.rows; j ++)
        {
            if(threashold_image_2.at<int>(Point(i,j)) == 255)
            {
                threashold_image.at<int>(Point(i,j)) = 255;
            }

        }
    }
    imshow("HSV picture", hsv_image);  
    imshow("threashold picture", threashold_image);  

    imwrite("1.jpg", threashold_image);  
    waitKey(0);  
    return 0;  
}
