#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

void salt(cv::Mat &image, int n) {

    int i,j;
    for (int k=0; k<n; k++) {

        // rand() is the MFC random number generator
        i= rand()%image.cols;
        j= rand()%image.rows;


        if (image.channels() == 1) { // gray-level image

            image.at<uchar>(j,i)= 255; 

        } else if (image.channels() == 3) { // color image

            image.at<cv::Vec3b>(j,i)[0]= 255; 
            image.at<cv::Vec3b>(j,i)[1]= 255; 
            image.at<cv::Vec3b>(j,i)[2]= 255; 
        }
    }
}



void colorReduce0(cv::Mat &image, int div=64) {

    int nl= image.rows; // 每行的像素数目
    int nc= image.cols * image.channels(); // total number of elements per line

    for (int j=0; j<nl; j++) {

        uchar* data= image.ptr<uchar>(j);//此句返回j行的首地址

        for (int i=0; i<nc; i++) {

            // process each pixel ---------------------

            data[i]= data[i]/div*div + div/2;
            //data[i]= data[i] + div/2;

            // end of pixel processing ----------------

        } // end of line                   
    }
}

#if 1
int main()
{
    //srand(cv::getTickCount()); // init random number generator

    cv::Mat image= cv::imread("salt.jpg");

    colorReduce0(image);

    cv::namedWindow("Image");
    cv::imshow("Image",image);

    cv::imwrite("cat.jpg",image);

    cv::waitKey(5000);

    return 0;
}
#else
int main()
{
    srand(cv::getTickCount()); // init random number generator

    //cv::Mat image= cv::imread("salt.jpg",0);
    cv::Mat image= cv::imread("salt.jpg");

    salt(image,5000);

    cv::namedWindow("Image");
    cv::imshow("Image",image);

    cv::imwrite("salted.bmp",image);

    cv::waitKey(5000);

    return 0;
}
#endif
