// Author :  Khoirul Anwar (PENS)
// Program:  Flood fill algorithm
// MatKul :  Workshop Komputer Visi

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#define vcap 	1
#define H 		0
#define S 		1
#define V 		2

using namespace cv;
using namespace std;

int pMin[3] = {0, 0, 0};
int pMax[3] = {255, 255, 255};
int r[100], g[100], b[100];
int i = 0, posx[100], posy[100];

void mouseCb(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		b[i] = (unsigned)theRNG() & 255;
		g[i] = (unsigned)theRNG() & 255;
		r[i] = (unsigned)theRNG() & 255;
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		posx[i] = x;
		posy[i] = y;
		i++;
	}

	else if (event == EVENT_RBUTTONDOWN)
		i = 0;


}

int main(int argc, char *argv[])
{
	
	VideoCapture videocap(vcap);
	if(!videocap.isOpened()) {
		printf("Kamera tidak terhubung!. Cek kabel kamera\n");
		return -1;
	}

	// cvNamedWindow("trackBar_result", CV_WINDOW_AUTOSIZE);

	Mat imgSrc, imgThresh, hsvImage, grayImg;
	// videocap >> imgSrc;
	imgSrc = imread("image/image_data002.png");
	cvtColor(imgSrc, imgSrc, COLOR_BGR2GRAY);

	int rows = imgSrc.rows;
	int cols = imgSrc.cols;
	bool mapState[rows][cols];

	for(int i=0; i<rows; i++)
		for(int j=0; j<cols; j++)
			mapState[i][j] = false;

	int queue[rows][cols];	
	int c_rows=0,c_cols=0; 

	for(int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++) 
		{
			// TODO
        	Vec3b color = imgSrc.at<Vec3b>(Point(i,j));
        	if (color[0] > 100)
        		color[0] = 255;

        	imgSrc.at<Vec3b>(Point(i,j)) = color;
		}
	}

	while(true) 
	{
		imshow("Test", imgSrc);

		// setMouseCallback("input", mouseCb, NULL);

		// imshow("grayImg", grayImg);

		// inRange(hsvImage, Scalar(pMin[H], pMin[S], pMin[V]), Scalar(pMax[H], pMax[S], pMax[V]), imgThresh);

		// threshold(grayImg, imgThresh, 200, 255, THRESH_BINARY);
		// imshow("threshold", imgThresh);



		// Mat imgFloodFill = imgThresh.clone();
		// floodFill(imgFloodFill, Point(0, 0), Scalar(255));

		// Mat imgFloodFill_inv;
		// bitwise_not(imgFloodFill, imgFloodFill_inv);

		// Mat imgOut = (imgThresh | imgFloodFill_inv);

		// imshow("floodFill", imgFloodFill);
		// imshow("floodFill_inv", imgFloodFill_inv);
		// imshow("Out", imgOut);

		char key = cvWaitKey(20);
		if (key == 'q')
			break;
	}

	// videocap.release();
	return 0;
}