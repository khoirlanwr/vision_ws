#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

#define indexCamera	1

using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst_norm, dst_norm_scaled;

int thresh = 200;
int max_thresh = 255;
const char* source_window = "Source image";
const char* corners_window = "Corners detected";

void cornerHarris_demo( int, void* );

int main( int argc, char** argv )
{	
	VideoCapture videocap(indexCamera);
	
	while (true)
	{
		videocap >> src;
	    cvtColor( src, src_gray, COLOR_BGR2GRAY );
    
    	namedWindow( source_window );	
	    createTrackbar( "Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo );

	    imshow( source_window, src );
	    cornerHarris_demo( 0, 0 );

		char key = cvWaitKey(20);
		
		if (key == 's')
			imwrite("image/saved_001.png", dst_norm_scaled);

		if (key == 'q')
			break;


	}	


    // src = imread("image/image_data001.png");
    // if ( src.empty() )
    // {
    //     cout << "Could not open or find the image!\n" << endl;
    //     cout << "Usage: " << argv[0] << " <Input image>" << endl;
    //     return -1;
    // }
    // waitKey();
    return 0;
}

void cornerHarris_demo( int, void* )
{
    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;
    Mat dst = Mat::zeros( src.size(), CV_32FC1 );
    cornerHarris( src_gray, dst, blockSize, apertureSize, k );
    normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( dst_norm, dst_norm_scaled );
    
    int i,j;

    for( i = 0; i < dst_norm.rows ; i++ )
    {
        for(  j = 0; j < dst_norm.cols; j++ )
        {
            if( (int) dst_norm.at<float>(i,j) > thresh )
            {
                circle(dst_norm_scaled, Point(j,i), 5,  Scalar(0), 2, 8, 0 );
                printf("Corner detected: in Point %d, %d\n", i, j);
            }
        }
    }

    namedWindow( corners_window );
    imshow( corners_window, dst_norm_scaled );
}