#pragma once
#include <vector>
#include <algorithm>
#include <cmath>
#include <opencv.hpp>
#include <imgproc.hpp>

namespace myCVlib {
	int getRGBByPoint(cv::Mat mat, int x, int y, std::vector<unsigned int>&dst);
	void splitRGB(cv::Mat src, std::vector<cv::Mat>&dst);
	void convertToGrey(cv::Mat src, cv::Mat &dst);
	void RGB2HSL(double r, double g, double b, double &H, double &S, double &L);
	double Hue2RGB(double v1, double v2, double vH);
	void HSL2RGB(double H, double S, double L, double& r, double& g, double& b);
	void calculateImageRGB(cv::Mat mat, double& r, double& g, double& b);
	void changeImageRGB(cv::Mat& mat, double deltaR, double deltaG, double deltaB);
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
	void gausFilter(cv::Mat src, cv::Mat &dst, int  aperture_size = 9, int aperture_sigma = 3);
	void avgFilter(cv::Mat src, cv::Mat &dst,int size);
	void midFilter(cv::Mat src, cv::Mat &dst,int size);
	void sobelDector(cv::Mat src, cv::Mat &dst);
	void laplaceDector(cv::Mat src, cv::Mat &dst);
	void nn_resize(cv::Mat src, cv::Mat &dst, float ratio);
	void linear_resize(cv::Mat src, cv::Mat &dst, float ratio);
	void createHoughLine(cv::Mat src, int threshold, std::vector<std::pair<float,float>> &lines, float rho, float theta);
	void houghLine(cv::Mat src, int threshold, cv::Mat &dst);
	void createhoughCircle(cv::Mat src, cv::Mat sobel_x, cv::Mat sobel_y, std::vector<std::pair<std::pair<float, float>, float>> &circles, double min_dist, int canny_threshold, int threshold, int minRadius, int maxRadius);
	void houghCircle(cv::Mat src, cv::Mat &dst, double dp,double min_dist,double canny_threshold,double threshold,int minRadius,int maxRadius);
	void calcHist(cv::Mat src, int* hist, int histSize, int *ranges);
	void getHistImg(int* hist, cv::Mat &dst, int histSize, int *ranges);
	void equalizeHist(cv::Mat src, cv::Mat &dst,int histSize,int *ranges);
	void linear_adjustContrast(cv::Mat src, cv::Mat &dst, int *p1, int *p2);
}