#include <opencv2/core/core.hpp> 
#include "opencv2/highgui/highgui.hpp"  
#include "opencv2/imgproc/imgproc.hpp"  
#include <iostream>  

using namespace cv;
using namespace std;

int g_nBilateralFilterValue=10;  //Bilateral Filter value 
Mat g_src_image,g_dst_bilateral_filter_image;  
static void on_BilateralFilter(int, void *)  
{  
    bilateralFilter ( g_src_image, g_dst_bilateral_filter_image, g_nBilateralFilterValue, g_nBilateralFilterValue*2, g_nBilateralFilterValue/2 );  // Bilateral Filter 
    imshow("BilateralFilter", g_dst_bilateral_filter_image);  
} 

int main()
{
    //Mat src_image = imread("src.jpg",IMREAD_COLOR);
    g_src_image = imread("src.jpg");
    //Mat src_image = imread("src.jpg",IMREAD_UNCHANED);
    if(!g_src_image.data)
    {
        cout<<"failed to load src image"<<endl;
        return 0;
    }

    g_dst_bilateral_filter_image = g_src_image.clone( );  
    cout<<"g_dst_bilateral_filter_image.channels(): "<<g_dst_bilateral_filter_image.channels()<<endl;
    //cvtColor(g_dst_bilateral_filter_image,g_dst_bilateral_filter_image,COLOR_BGR2RGB);

    namedWindow("BilateralFilter", 1);  
    createTrackbar("Parameter Value：", "BilateralFilter",&g_nBilateralFilterValue, 50,on_BilateralFilter);  
    on_BilateralFilter(g_nBilateralFilterValue,0);  

    waitKey(0);
    return 0;
}
