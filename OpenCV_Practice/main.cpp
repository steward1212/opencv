#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int slider_value;
Mat frameA;
Mat frameB;

void on_trackbar(int, void*)
{
	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	Mat dst;
	Mat out;
	Mat in[] = { frameB, frameB, frameB };
	merge(in, 3, out);

	addWeighted(frameA, beta, out, alpha, 0.0, dst);
	imshow("camera", dst);
}

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

	namedWindow("camera", CV_WINDOW_KEEPRATIO);
	for(;;)
	{
		Mat frame;
		Mat edges;
		cap >> frame;
		Canny(frame, edges, 100, 300);
		frameA = frame.clone();
		frameB = edges.clone();
		createTrackbar("Ratio", "camera", &slider_value, 100, on_trackbar);
		on_trackbar(slider_value, 0);
		//imshow("camera", frameA);
		int key = waitKey(30);
		if (key != 255)
		{
			break;
		}
	}
	system("pause");
	return 0;
}