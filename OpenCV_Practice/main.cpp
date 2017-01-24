#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"


using namespace cv;

int main()
{
	Mat img = imread("penggan.jpg");
	Mat resized_img;
	resize(img, resized_img, Size(img.cols / 8, img.rows / 8));
	imshow("Hello World!", resized_img);
	waitKey();
}