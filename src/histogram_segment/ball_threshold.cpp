// Author :  Khoirul Anwar (PENS)
// Program:  Thresholding bola
// MatKul :  Workshop Komputer Visi

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
#include <iostream>
#include <cstring>
#include <ctime>
#include <limits.h>

using namespace std;
using namespace cv;

#define vcap 	1
#define H 		0
#define S 		1
#define V 		2
#define E		0
#define D 		1

int pMin[3] = {0, 0, 0};
int pMax[3] = {255, 255, 255};
int MORPS[2] = {0, 0};
int erode_val = 0;
int erode_elem = 0;
int dilate_elem = 0;
int dilate_val = 0;

void trackBar()
{
	cvCreateTrackbar("Hue MIN", "trackBar_result", &pMin[H], 255, 0);
	cvCreateTrackbar("Sat MIN", "trackBar_result", &pMin[S], 255, 0);
	cvCreateTrackbar("Val MIN", "trackBar_result", &pMin[V], 255, 0);
	cvCreateTrackbar("Hue MAX", "trackBar_result", &pMax[H], 255, 0);
	cvCreateTrackbar("Sat MAX", "trackBar_result", &pMax[S], 255, 0);
	cvCreateTrackbar("Val MAX", "trackBar_result", &pMax[V], 255, 0);

	cvCreateTrackbar("Erode type", "trackBar_result", &erode_elem, 2, 0);
	cvCreateTrackbar("Erode val", "trackBar_result", &erode_val, 100, 0);
	cvCreateTrackbar("Dilate type", "trackBar_result", &dilate_elem, 2, 0);
	cvCreateTrackbar("Dilate val", "trackBar_result", &dilate_val, 100, 0);
}

Mat getErosion(Mat src)
{
	int erosion_type;
	Mat erosion_dst;

  	if( erode_elem == 0 ){ erosion_type = MORPH_RECT; }
  	else if( erode_elem == 1 ){ erosion_type = MORPH_CROSS; }
  	else if( erode_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  	Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erode_val + 1, 2*erode_val+1 ),
                                       Point( erode_val, erode_val ) );

  	/// Apply the erosion operation
  	erode( src, erosion_dst, element );
  	return erosion_dst;
}

Mat getDilation(Mat img)
{
	Mat dilation_src = img;
	Mat dilation_dst;
	int dilation_type;
  	if(dilate_elem == 0) dilation_type = MORPH_RECT;
  	else if(dilate_elem == 1) dilation_type = MORPH_CROSS;
  	else if(dilate_elem == 2) dilation_type = MORPH_ELLIPSE;

  	Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilate_val + 1, 2*dilate_val+1 ),
                                       Point( dilate_val, dilate_val ) );

  	dilate(dilation_src, dilation_dst, element );
	return dilation_dst;
}



Mat getThreshold(Mat srcImage)
{
	Mat thresholdImage, hsvImage;
	// convert to HSV image
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);
	// threshold image using inRange function
	inRange(hsvImage, Scalar(pMin[H], pMin[S], pMin[V]), Scalar(pMax[H], pMax[S], pMax[V]), thresholdImage);
	return thresholdImage;
}

int main(int argc, char *argv[])
{
	VideoCapture cap(vcap);
	if(!cap.isOpened()) {
		printf("Kamera tidak terhubung!. Cek kabel kamera\n");
		return -1;
	}

	cvNamedWindow("trackBar_result", CV_WINDOW_AUTOSIZE);
	while(true) 
	{
		Mat src, thresholdImg, Result; 
		cap >> src;

		trackBar();
		thresholdImg = getThreshold(src);
		Result = getErosion(thresholdImg);
		Result = getDilation(Result);

		imshow("Source", src);
		imshow("Result", Result);

		char key = cvWaitKey(20);
		if ( key == 'q')
			break;
	}

	cap.release();
	return 0;
}