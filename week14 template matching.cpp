#include<iostream>
#include<opencv2/opencv.hpp>
#include "week10 HOG.cpp"


using namespace cv;
using namespace std;

int main() {
	//--------------------------------------------ģ��ƥ��-----------------------------------------------------------------
	VideoCapture cap;
	cap.open(0);
	
	Mat frame;		//��ǰ֡
	Mat tempMat;
	Mat refMat;		//ģ��
	int cnt = 0;
	
	while (1) {
		cap >> frame;
		//ѡ��ROI
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}

		Mat resultMat;
		int method = 0;
		matchTemplate(frame, refMat, resultMat, method); //ģ��ƥ�亯�����õ�resultMat

		normalize(resultMat,resultMat,0,1,NORM_MINMAX,-1,Mat());//��resultMat��һ��
		double min, max;
		Point minloc, maxloc,matchloc;
		minMaxLoc(resultMat,&min,&max,&minloc,&maxloc,Mat());	//ȡ�������Сֵλ��

		rectangle(frame,Point(minloc.x,minloc.y),Point(minloc.x + refMat.cols, minloc.y + refMat.rows),Scalar(234,33,23),2,8);

		cnt++;
		imshow("",frame);


		waitKey(30);
	
	
	}



}