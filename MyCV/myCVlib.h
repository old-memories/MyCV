#pragma once
#include <vector>
#include <opencv.hpp>

namespace myCVlib {
	int getRGBByPoint(cv::Mat mat, int x, int y, std::vector<unsigned int>&dst);
	void splitRGB(cv::Mat src, std::vector<cv::Mat>&dst);

}