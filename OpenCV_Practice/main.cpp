#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	/*Mat img = imread("penggan.jpg");
	Mat resized_img;
	resize(img, resized_img, Size(img.cols / 8, img.rows / 8));
	imshow("Hello World!", resized_img);
	waitKey();*/
	VideoCapture cap(0);

	if (!cap.isOpened())
		return -1;

	namedWindow("camera", 1);
	for(;;)
	{
		Mat frame;
		Mat edges;
		cap >> frame;
		Canny(frame, edges, 10, 100);
		imshow("camera", edges);
		int key = waitKey(30);
		if (key != 255)
		{
			break;
		}
	}
	system("pause");
	return 0;
}