#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <cstdio>
#include <iostream>

using namespace cv;
using namespace std;
int xpos[100], ypos[100], i = 0, r[100], g[100], b[100], compCount = 0;

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == EVENT_LBUTTONDOWN)
	{
		/*b[i] = (unsigned)theRNG() & 255;
		g[i] = (unsigned)theRNG() & 255;
		r[i] = (unsigned)theRNG() & 255;
		*/
		cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
		xpos[i] = x;
		ypos[i] = y;
		i++;
		b[0] = (unsigned)theRNG() & 255;
		g[0] = (unsigned)theRNG() & 255;
		r[0] = (unsigned)theRNG() & 255;

		b[1] = (unsigned)theRNG() & 255;
		g[1] = (unsigned)theRNG() & 255;
		r[1] = (unsigned)theRNG() & 255;
		
	}
	else if (event == EVENT_RBUTTONDOWN) {
		i = 0;
	}

}

class WatershedSegmenter {
private:
	cv::Mat markers;
public:
	void setMarkers(cv::Mat& markerImage)
	{
		markerImage.convertTo(markers, CV_32S);
	}

	cv::Mat process(cv::Mat &image)
	{
		cv::watershed(image, markers);
		markers.convertTo(markers, CV_8UC3);
		return markers;
	}
};


int main(int argc, char* argv[])
{
	VideoCapture cap(0);
	while (1)
	{

		Mat image, dest;
		cap >> image;
		imshow("originalimage", image);
		Mat markers(image.size(), CV_8U, cv::Scalar(-1));


		markers(Rect(0, 0, image.cols, 5)) = CV_RGB(255, 255, 255);

		markers(Rect(0, image.rows - 5, image.cols, 5)) = CV_RGB(255, 0, 255);

		markers(Rect(0, 0, 5, image.rows)) = CV_RGB(255, 0, 255);
		markers(Rect(image.cols - 5, 0, 5, image.rows)) = CV_RGB(255, 0, 255);
		setMouseCallback("watershed", CallBackFunc, NULL);

		for (int j = 0; j < i; j++)
		markers(Rect(xpos[j], ypos[j], 20, 20)) = Scalar::all(2);

		markers.convertTo(markers, CV_BGR2GRAY);
		imshow("markers", markers);

		printf("%d", xpos[i]);
		//Create watershed segmentation object
		WatershedSegmenter segmenter;
		segmenter.setMarkers(markers);
		Mat mask;
		cv::Mat awal = segmenter.process(image);
		double thresh = 	
		cvtColor(awal, mask, COLOR_GRAY2BGR);


		//MENAMPILKAN HASIL WATERSHED
		//Mat wshed(wshedMask.size(), CV_8UC3);



		for (int c = 0; c<mask.rows; c++)
		{
			for (int j = 0; j<mask.cols; j++)
			{
				if (mask.at<Vec3b>(c, j)[0] == 0 && mask.at<Vec3b>(c, j)[1] == 0 && mask.at<Vec3b>(c, j)[2] == 0) {
					mask.at<Vec3b>(c, j)[0] = b[0];
					mask.at<Vec3b>(c, j)[1] = g[0];
					mask.at<Vec3b>(c, j)[2] = r[0];
				}
				else if (mask.at<Vec3b>(c, j)[0] == 255 && mask.at<Vec3b>(c, j)[1] == 255 && mask.at<Vec3b>(c, j)[2] == 255) {
					mask.at<Vec3b>(c, j)[0] = b[1];
					mask.at<Vec3b>(c, j)[1] = g[1];
					mask.at<Vec3b>(c, j)[2] = r[1];
				}
			}
		}
		//imshow("watershed transform", wshedMask );

		mask = mask + image*0.5;
		imshow("watershed", mask);

		//bitwise_and(image, image, dest, mask);
		//dest.convertTo(dest, CV_8U);

		//imshow("final_result", mask);
		//imshow("final_resul1t", mask);

		if (waitKey(1) >= 0) break;
	}
	return 0;
}