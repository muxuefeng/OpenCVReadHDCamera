// OpenCV 2.4.11
// 1920x1080 30fps
// MU XUEFENG
// 2019.02.26


#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <ctime>


using namespace cv;
using namespace std;

static const int MAX_WIDTH_RESOLUTION = 7680;
static const int MAX_HEIGHT_RESOLUTION = 4800;

string getTime()
{
	time_t now_time;
	time(&now_time);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m%d-%H%M%S", localtime(&now_time));
	return tmp;
}

int main(int, char**)
{
	Mat src;
	VideoCapture cap(0);
	if (!cap.isOpened())
	{
		cerr << "error! Unable to open camera";
		return -1;
	}

	cap.set(CV_CAP_PROP_FRAME_WIDTH, 7680);
	cap.set(CV_CAP_PROP_FRAME_HEIGHT, 4800);

	cap >> src;

	if (src.empty())
	{
		cerr << "blank frame";
		return -1;
	}

	bool isColor = (src.type() == CV_8UC3);
	VideoWriter writer;
	int codec_MJPG = CV_FOURCC('M', 'J', 'P', 'G');
	int codec_MP42 = CV_FOURCC('M', 'P', '4', '2');
	int codec_H263 = CV_FOURCC('U', '2', '6', '3');
	double fps = 30.0;
	string filename = "./live.avi";
	writer.open(filename, codec_MP42, fps, src.size(), isColor);

	if (!writer.isOpened())
	{
		cerr << "could not open output video file";
	}

	cout << "writing ...." << filename << endl
		<< "press any key to terminate" << endl;

	for (;;)
	{
		if (!cap.read(src))
		{
			cerr << "error, blank frame";
			break;
		}
		writer.write(src);
		imshow("Live", src);
		if(waitKey(5) >=0 )
			break;
	}

	return 0;

}