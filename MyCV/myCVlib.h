#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
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
	void  doubleThresholdBinary(cv::Mat src, cv::Mat&dst, int minPixel, int maxPixel);
	void op_add(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
	void op_subtract(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
	void op_multiple(cv::Mat src1, cv::Mat src2, cv::Mat &dst);
	void  doubleThreshold(cv::Mat src, cv::Mat&dst, int minPixel, int maxPixel);
	void getGaussianKernel(double **gaus, int size, double sigma);
	void gaussianFilter(cv::Mat src, cv::Mat & dst, double**gaus, int size);
	void sobelGradDirction(cv::Mat src, cv::Mat &dst_SobelX, cv::Mat &dst_SobelY, double *&directionArray);
	void amplitude(cv::Mat src_x, cv::Mat src_y, cv::Mat &dst_xy);
	void localMaxValue(cv::Mat src, cv::Mat &dst, double *directionArray);
	void doubleThresholdLink(cv::Mat src, cv::Mat &dst, double lowThreshold, double highThreshold);
	void canny(cv::Mat src, cv::Mat &dst, double lowThreshold, double highThreshold, int aperture_size = 7, int aperture_sigma = 1);
	}