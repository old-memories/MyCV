#pragma once
#include <vector>
#include <algorithm>
#include <opencv.hpp>

namespace myCVlib {
	int getRGBByPoint(cv::Mat mat, int x, int y, std::vector<unsigned int>&dst);
	void splitRGB(cv::Mat src, std::vector<cv::Mat>&dst);
	void convertToGrey(cv::Mat src, cv::Mat &dst);
	void RGB2HSL(double r, double g, double b, double &H, double &S, double &L);
	double Hue2RGB(double v1, double v2, double vH);
	void HSL2RGB(double H, double S, double L, double& r, double& g, double& b);
	void calculateImageRGB(cv::Mat mat, double& r, double& g, double& b);
	void changeImageRGB(cv::Mat& mat, double deltaR, double deltaG, double deltaB);
	uchar clamp(double value);
	void changeImageHSL(cv::Mat& mat, double deltaH, double deltaS, double deltaL);
	void OTSU(cv::Mat src, cv::Mat& dst);
	void  doubleBinarization(cv::Mat src, cv::Mat&dst,int minPixel, int maxPixel);
	void op_add(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
	void op_subtract(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
	void op_multiple(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
}