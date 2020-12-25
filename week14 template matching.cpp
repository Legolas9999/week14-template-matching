#include<iostream>
#include<opencv2/opencv.hpp>
#include "week10 HOG.cpp"


using namespace cv;
using namespace std;

int main() {
	//--------------------------------------------模板匹配-----------------------------------------------------------------
	VideoCapture cap;
	cap.open(0);
	
	Mat frame;		//当前帧
	Mat tempMat;
	Mat refMat;		//模板
	int cnt = 0;
	
	while (1) {
		cap >> frame;
		//选定ROI
		if (cnt == 0) {
			Rect2d r;
			r = selectROI(frame, true);
			tempMat = frame(r);
			tempMat.copyTo(refMat);
			destroyAllWindows();
		}

		Mat resultMat;
		int method = 0;
		matchTemplate(frame, refMat, resultMat, method); //模板匹配函数，得到resultMat

		normalize(resultMat,resultMat,0,1,NORM_MINMAX,-1,Mat());//对resultMat归一化
		double min, max;
		Point minloc, maxloc,matchloc;
		minMaxLoc(resultMat,&min,&max,&minloc,&maxloc,Mat());	//取得最大最小值位置

		rectangle(frame,Point(minloc.x,minloc.y),Point(minloc.x + refMat.cols, minloc.y + refMat.rows),Scalar(234,33,23),2,8);

		cnt++;
		imshow("",frame);


		waitKey(30);
	
	
	}



}