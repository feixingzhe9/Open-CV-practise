#include<opencv2/opencv.hpp> 
#include<cv.h>

using namespace cv; 
using namespace std;

int main(void) 
{ 
    //【1】从摄像头读入视频
    VideoCapture capture(0);//若测试摄像头有没有打开，/*if(!capture.isOpened())                {cout<< "cannot open the camera.";cin.get();return -1;}*

    Mat edges; //定义一个Mat变量，用于存储每一帧的图像
    //【2】循环显示每一帧
    while(1)
    {
        Mat frame; //定义一个Mat变量，用于存储每一帧的图像
        capture >> frame;  //读取当前帧                        
        if(frame.empty())
        {
            printf("--(!) No captured frame -- Break!");
            break;                
        }
        else
        {
            cvtColor(frame, edges, CV_BGR2GRAY);//彩色转换成灰度
            blur(edges, edges, Size(7, 7));//模糊化
            Canny(edges, edges, 0, 30, 3);//边缘化
            imshow("origin frames", frame); //显示当前帧
            imshow("读取被边缘后的视频", edges); //显示当前帧

        }

        if (char(waitKey(15) & 0xff) == 'q') //延时30ms
        {
            printf("quit \n");
            break;
        }
    }
    return 0;    
} 

