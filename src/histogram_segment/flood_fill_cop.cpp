#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int xpos[100], ypos[100], i=0, r[100], g[100], b[100];
void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		b[i] = (unsigned)theRNG() & 255;
		g[i] = (unsigned)theRNG() & 255;
		r[i] = (unsigned)theRNG() & 255;
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		xpos[i] = x;
		ypos[i] = y;
		i++;
		
	}
	else if (event == EVENT_RBUTTONDOWN) {
		i = 0;
	}

}

int main(int argc, char** argv)
{

	VideoCapture cap(1);

	//	Point seedPoint = (xpos, ypos);
	Scalar newScalar = 20;
	Rect* rect = 0;
	Scalar loDiff = Scalar(2, 2, 2);
	Scalar upDiff = Scalar(5, 5, 5);
	int flags = 4;


	while (1)
	{
		Mat src, src1;
		cap >> src;
		//cvtColor(src, src1, COLOR_BGR2GRAY);
		setMouseCallback("input", CallBackFunc, NULL);
		Mat im_floodfill = src.clone();
		for (int j = 0; j < i; j++)
		floodFill(im_floodfill, Point(xpos[j], ypos[j]), CV_RGB(r[j], g[j], b[j]), rect, loDiff, upDiff, flags);



		imshow("input", im_floodfill);
		if (waitKey(1) >= 0) break;
	}
	return 0;
}