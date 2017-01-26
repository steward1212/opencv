#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int slider_value;
Mat frameA;
Mat frameB;
Mat videoFrame;

void on_trackbar(int, void*)
{
	double alpha = (double)slider_value / 100.0;
	double beta = (1.0 - alpha);
	Mat dst;
	Mat out;
	Mat in[] = { frameB, frameB, frameB };
	merge(in, 3, out);
	addWeighted(frameA, beta, out, alpha, 0.0, dst);
	Mat ROI = videoFrame(Rect(0, 0, dst.cols, dst.rows));
	addWeighted(ROI, 0, dst, 1, 0, ROI);
	imshow("camera", videoFrame);
}

int main()
{
	VideoCapture cap(0);
	VideoCapture video("1.MTS");

	if (!cap.isOpened())
		return -1;

	if (!video.isOpened())
		return -1;

	namedWindow("camera", CV_WINDOW_KEEPRATIO);
	for(;;)
	{
		Mat frame;
		Mat edges;
		video >> videoFrame;
		if (videoFrame.empty())
		{
			break;
		}
		cap >> frame;
		Canny(frame, edges, 100, 300);
		frameA = frame.clone();
		frameB = edges.clone();
		createTrackbar("Ratio", "camera", &slider_value, 100, on_trackbar);
		on_trackbar(slider_value, 0);
		int key = waitKey(30);
		if (key != 255)
		{
			break;
		}
	}

	system("pause");
	return 0;
}