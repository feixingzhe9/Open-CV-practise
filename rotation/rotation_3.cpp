#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
//#include <stdio.h>
#include <iostream>
//#include <stdlib.h>


cv::Mat AngleRotate(cv::Mat srcimage,float angle, int x = 0, int y = 0)//普通旋转  
{  
    /* 
       旋转过程： 
       1、将原始图像的坐标系换成数学坐标系 
       2、通过旋转公式对图像坐标进行旋转 
       3、将旋转后的数学坐标系转换成图像坐标系 
                         |1       0  0| |cos -sin 0| |1     0     0| 
       [x,y,1]=[x0,y0,1]*|0      -1  0|*|sin  cos 0|*|0     -1    0| 
                         |-0.5w 0.5h 1| | 0    0  1| |0.5w' 0.5h' 1| 
       但是这是旋转过程，接着要反转，就是新图像每个坐标的像素对应之前图像坐标的像素 
                             |1       0  0| |cos  sin 0| |1     0     0|   
       就是[x0,y0,1]=[x,y,1]*|0      -1  0|*|-sin cos 0|*|0     -1    0|  
                             |-0.5w'0.5h'1| | 0    0  1| |0.5w  0.5h  1| 
       最终得到   x0=xcos+ysin-0.5w'cos-0.5h,sin+0.5w; 
                  y0=-xsin+ycos+0.5w'sin-0.5h'cos+0.5h; 
     */  

    float alpha=angle*CV_PI/180.0;  
    float cs=cos(alpha);  
    float sn=sin(alpha);  
    int nrows=srcimage.rows;    
    int ncols=srcimage.cols;  

    // 旋转后四个角的坐标（以图像中心为坐标系原点）  
    cv::Mat xy_0 = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_1 = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_2 = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_3 = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);

    cv::Mat xy_0_ = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_1_ = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_2_ = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat xy_3_ = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);

    xy_0_.at<float>(0,0) = 0;
    xy_0_.at<float>(0,1) = nrows;
    xy_0_.at<float>(0,2) = 1;

    xy_1_.at<float>(0,0) = ncols;
    xy_1_.at<float>(0,1) = nrows;
    xy_1_.at<float>(0,2) = 1;

    xy_2_.at<float>(0,0) = 0;
    xy_2_.at<float>(0,1) = 0;
    xy_2_.at<float>(0,2) = 1;

    xy_3_.at<float>(0,0) = ncols;
    xy_3_.at<float>(0,1) = 0;
    xy_3_.at<float>(0,2) = 1;

    cv::Mat A_ = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);
    cv::Mat B_ = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);
    cv::Mat C_ = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);
    A_.at<float>(0,0) = 1;
    A_.at<float>(1,1) = -1;
    A_.at<float>(2,0) = -0.5*ncols;
    A_.at<float>(2,1) = 0.5*nrows;
    A_.at<float>(2,2) = 1;
    
    B_.at<float>(0,0) = cs;
    B_.at<float>(0,1) = -sn;
    B_.at<float>(1,0) = sn;
    B_.at<float>(1,1) = cs;
    B_.at<float>(2,2) = 1;

    C_.at<float>(0,0) = 1;
    C_.at<float>(1,1) = -1;
    C_.at<float>(2,0) = 0.5*ncols;
    C_.at<float>(2,1) = 0.5*nrows;
    xy_0 = xy_0_ * A_ * B_ * C_;
    xy_1 = xy_1_ * A_ * B_ * C_;
    xy_2 = xy_2_ * A_ * B_ * C_;
    xy_3 = xy_3_ * A_ * B_ * C_;

    //float ao=-0.5*ncols*cs+0.5*nrows*sn;  
    //float bo=-0.5*ncols*(-sn)+0.5*nrows*cs;  
    //float a1=0.5*ncols*cs+0.5*nrows*sn;  
    //float b1=0.5*ncols*(-sn)+0.5*nrows*cs;  
    //float a2=-0.5*ncols*cs-0.5*nrows*sn;  
    //float b2=-0.5*ncols*(-sn)-0.5*nrows*cs;  
    //float a3=0.5*ncols*cs-0.5*nrows*sn;  
    //float b3=0.5*ncols*(-sn)-0.5*nrows*cs;  

    //int Rows=std::max(fabs(b3-bo),fabs(b2-b1));  
    //int Cols=std::max(fabs(a3-ao),fabs(a2-a1));  

    int Rows=std::max(fabs(xy_3.at<float>(0,1) - xy_0.at<float>(0,1)),fabs(xy_2.at<float>(0,1) - xy_1.at<float>(0,1)));  //new rows
    int Cols=std::max(fabs(xy_3.at<float>(0,0) - xy_0.at<float>(0,0)),fabs(xy_2.at<float>(0,0) - xy_1.at<float>(0,0)));  //new columns





    cv::Mat xy = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat x0y0 = cv::Mat::zeros(cv::Size(3,1),CV_32FC1);
    cv::Mat A = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);
    cv::Mat B = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);
    cv::Mat C = cv::Mat::zeros(cv::Size(3,3),CV_32FC1);

    A.at<float>(0,0) = 1;
    A.at<float>(1,1) = -1;
    A.at<float>(2,0) = -0.5*Cols;
    A.at<float>(2,1) = 0.5*Rows;
    A.at<float>(2,2) = 1;
    
    B.at<float>(0,0) = cs;
    B.at<float>(0,1) = -sn;
    B.at<float>(1,0) = sn;
    B.at<float>(1,1) = cs;
    B.at<float>(2,2) = 1;

    C.at<float>(0,0) = 1;
    C.at<float>(1,1) = -1;
    C.at<float>(2,0) = 0.5*ncols;
    C.at<float>(2,1) = 0.5*nrows;
    std::cout<<"xy  = "<<std::endl<<xy<<std::endl<<std::endl;  
    std::cout<<"x0y0  = "<<std::endl<<x0y0<<std::endl<<std::endl;  
    std::cout<<"A  = "<<std::endl<<A<<std::endl<<std::endl;  
    std::cout<<"B  = "<<std::endl<<B<<std::endl<<std::endl;  
    std::cout<<"C  = "<<std::endl<<C<<std::endl<<std::endl;  



    cv::Mat dstimage(Rows,Cols,srcimage.type());  
    for(int i=0;i<Rows;i++)  
    {  
        for(int j=0;j<Cols;j++)  
        {  
            //新图像坐标对应老图像坐标  

            //int x=j*cs+i*sn-0.5*Cols*cs-0.5*Rows*sn+0.5*ncols;  
            //int y=-j*sn+i*cs+0.5*Cols*sn-0.5*Rows*cs+0.5*nrows;  

            xy.at<float>(0,0) = j;
            xy.at<float>(0,1) = i;
            xy.at<float>(0,2) = 1;
            x0y0 = xy * A * B * C;
            int x = x0y0.at<float>(0,0);
            int y = x0y0.at<float>(0,1);
            if(x>=0 && x<ncols && y>=0 && y<nrows)  
            {  
                if(srcimage.channels()==3)//彩色图像channel通道是3  
                    dstimage.at<cv::Vec3b>(i,j)=srcimage.at<cv::Vec3b>(y,x);  
                else if(srcimage.channels()==1)//灰度图像channel通道是1  
                    dstimage.at<uchar>(i,j)=srcimage.at<uchar>(y,x);  
            }  
            else  
            {  
                if(srcimage.channels()==3)  
                    dstimage.at<cv::Vec3b>(i,j)=cv::Vec3b(0,0,0);  
                else if(srcimage.channels()==1)  
                    dstimage.at<uchar>(i,j)=0;  
            }  
        }  
    }  
    return dstimage;  
}  


#if 0
int main()
{

    cv::Mat src = cv::imread("rotation.jpg");  
    cv::Mat dst;  

    //旋转角度  
    double angle = 345;  

    cv::Size src_sz = src.size();  
    cv::Size dst_sz(src_sz.height, src_sz.width);  
    int len = std::max(src.cols, src.rows);  

    //指定旋转中心  
    cv::Point2f center(len / 2., len / 2.);  

    //获取旋转矩阵（2x3矩阵）  
    cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);  

    //根据旋转矩阵进行仿射变换  
    cv::warpAffine(src, dst, rot_mat, dst_sz);  

    //显示旋转效果  
    cv::imshow("image", src);  
    cv::imshow("result", dst);  

    cv::waitKey(0);  

    return 0;  
}
#else
int main()
{
    cv::Mat src = cv::imread("rotation.jpg");
    cv::Mat dst;
    double angle = 30;
    dst = AngleRotate(src,angle);
    cv::imshow("rotation",dst);
    cv::imshow("origin",src);
    cv::waitKey(0);
    return 0;
}
#endif
