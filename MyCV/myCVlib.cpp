#include <myCVlib.h>


	 int myCVlib::getRGBByPoint(cv::Mat mat, int x, int y,std::vector<unsigned int>&dst) {
		cv::Point p(x, y);
		if (mat.channels() == 3) {
			unsigned int b = mat.at<cv::Vec3b>(p)[0];
			unsigned int g = mat.at<cv::Vec3b>(p)[1];
			unsigned int r = mat.at<cv::Vec3b>(p)[2];
			dst.push_back(b);
			dst.push_back(g);
			dst.push_back(r);
			return 0;
		}
		else if (mat.channels() == 1) {
			unsigned int grey = mat.at<uchar>(p);
			dst.push_back(grey);
			return 1;
		}
		return 0;
	}

	 void  myCVlib::splitRGB(cv::Mat src, std::vector<cv::Mat>&dst) {
		 if (dst.size() != 3) {
			 return;
		 }
		 cv::Mat mat;
		 src.convertTo(mat, CV_8UC3);
		 dst[0].create(mat.rows, mat.cols, CV_8UC1);
		 dst[1].create(mat.rows, mat.cols, CV_8UC1);
		 dst[2].create(mat.rows, mat.cols, CV_8UC1);
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 uchar *dst_0_data = dst[0].ptr<uchar>(i);
			 uchar *dst_1_data = dst[1].ptr<uchar>(i);
			 uchar *dst_2_data = dst[2].ptr<uchar>(i);
			 int k = 0;
			 for (int j = 0; j < mat.cols*mat.channels(); j += 3) {
				 dst_0_data[k] = src_data[j];
				 dst_1_data[k] = src_data[j + 1];
				 dst_2_data[k] = src_data[j + 2];
				 k = k + 1;
			 }
		 }


		 }
	 void myCVlib::convertToGrey(cv::Mat src, cv::Mat& dst) {
		 if (src.channels() != 3) {
			 dst = src.clone();
			 return;
		 }
		 cv::Mat mat;
		 src.convertTo(mat, CV_8UC3);
		 dst.create(mat.size(), CV_8UC1);
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 uchar *dst_data = dst.ptr<uchar>(i);
			 int k = 0;
			 for (int j = 0; j < mat.cols*mat.channels(); j += 3) {
				 unsigned int r = (unsigned int)src_data[j + 2];
				 unsigned int g = (unsigned int)src_data[j + 1];
				 unsigned int b = (unsigned int)src_data[j];
				 //Gray = (R*19595 + G*38469 + B*7472) >> 16
				 //dst_data[k] = (uchar)((r +g << 1 + b) >> 2);
				 dst_data[k] = (uchar)((r*19595 + g*38469 + b*7472) >> 16);
				 k = k + 1;
			 }
		 }
	 }


	 //RGB转换为HSL：
	 void myCVlib::RGB2HSL(double r, double g, double b, double &H, double &S, double &L)
	 {
		 double R, G, B, Max, Min, del_R, del_G, del_B, del_Max;
		 R = r / 255.0;       //Where RGB values = 0 ÷ 255
		 G = g / 255.0;
		 B = b / 255.0;

		 Min = std::min(R, std::min(G, B));    //Min. value of RGB
		 Max = std::max(R, std::max(G, B));    //Max. value of RGB
		 del_Max = Max - Min;        //Delta RGB value

		 L = (Max + Min) / 2.0;

		 if (del_Max == 0)           //This is a gray, no chroma...
		 {
			 //H = 2.0/3.0;          //Windows下S值为0时，H值始终为160（2/3*240）
			 H = 0;                  //HSL results = 0 ÷ 1
			 S = 0;
		 }
		 else                        //Chromatic data...
		 {
			 if (L < 0.5) S = del_Max / (Max + Min);
			 else         S = del_Max / (2 - Max - Min);

			 del_R = (((Max - R) / 6.0) + (del_Max / 2.0)) / del_Max;
			 del_G = (((Max - G) / 6.0) + (del_Max / 2.0)) / del_Max;
			 del_B = (((Max - B) / 6.0) + (del_Max / 2.0)) / del_Max;

			 if (R == Max) H = del_B - del_G;
			 else if (G == Max) H = (1.0 / 3.0) + del_R - del_B;
			 else if (B == Max) H = (2.0 / 3.0) + del_G - del_R;

			 if (H < 0)  H += 1;
			 if (H > 1)  H -= 1;
		 }
	 }

	 double myCVlib::Hue2RGB(double v1, double v2, double vH)
	 {
		 if (vH < 0) vH += 1;
		 if (vH > 1) vH -= 1;
		 if (6.0 * vH < 1) return v1 + (v2 - v1) * 6.0 * vH;
		 if (2.0 * vH < 1) return v2;
		 if (3.0 * vH < 2) return v1 + (v2 - v1) * ((2.0 / 3.0) - vH) * 6.0;
		 return (v1);
	 }

	 //HSL转换为RGB：
	 void myCVlib::HSL2RGB(double H, double S, double L, double& r, double& g, double& b)
	 {
		 double R, G, B;
		 double var_1, var_2;
		 if (S == 0)                       //HSL values = 0 ÷ 1
		 {
			 R = L * 255.0;                   //RGB results = 0 ÷ 255
			 G = L * 255.0;
			 B = L * 255.0;
		 }
		 else
		 {
			 if (L < 0.5) var_2 = L * (1 + S);
			 else         var_2 = (L + S) - (S * L);

			 var_1 = 2.0 * L - var_2;

			 R = 255.0 * Hue2RGB(var_1, var_2, H + (1.0 / 3.0));
			 G = 255.0 * Hue2RGB(var_1, var_2, H);
			 B = 255.0 * Hue2RGB(var_1, var_2, H - (1.0 / 3.0));
			 r = R;
			 g = G;
			 b = B;

		 }
	 }


	 void myCVlib::calculateImageRGB(cv::Mat mat, double& r, double& g, double& b) {
		 double sumR = 0;
		 double sumG = 0;
		 double sumB = 0;
		 double total = mat.rows*mat.cols;
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 for (int j = 0; j < mat.cols*mat.channels(); j += 3) {
				 sumB += src_data[j];
				 sumG += src_data[j+1];
				 sumR += src_data[j+2];
			 }
		 }
		 r = sumR / total;
		 g = sumG / total;
		 b = sumB / total;
	 }
	 uchar myCVlib::clamp(double value) {
		 return (uchar)value> 255 ? 255 : (value < 0 ? 0 : value);
	 }
	 void myCVlib::changeImageRGB(cv::Mat& mat, double deltaR, double deltaG, double deltaB) {
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 for (int j = 0; j < mat.cols*mat.channels(); j += 3) {
				 src_data[j] = clamp((double)src_data[j] + deltaB);
				 src_data[j+1] = clamp((double)src_data[j+1] + deltaG);
				 src_data[j+2] = clamp((double)src_data[j+2] + deltaR);
			 }
		 }
	 }

	 void myCVlib::changeImageHSL(cv::Mat& mat, double deltaH, double deltaS, double deltaL) {
		 if (mat.channels() != 3)
			 return;
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 for (int j = 0; j < mat.cols*mat.channels(); j += 3) {
				 double H, S, L, r, g, b;
				 r =(double) src_data[j + 2];
				 g = (double)src_data[j + 1];
				 b = (double)src_data[j];
				 RGB2HSL(r,g,b, H, S, L);
				 H += deltaH;
				 S += deltaS;
				 L += deltaL;
				 HSL2RGB(H, S, L, r,g,b);
				 src_data[j] = clamp(b);
				 src_data[j+1] = clamp(g);
				 src_data[j+2] = clamp(r);
			 }
		 }
	}

	 void myCVlib::OTSU(cv::Mat src, cv::Mat& dst) {
		 cv::Mat mat;
		 convertToGrey(src, mat);
		 int histogram[256] = { 0 };
		 //double u = 0.0;
		 double cov = 0.0;
		 double maxcov = 0.0;
		 int split_index = 0;
		 for (int i = 0; i < mat.rows; i++) {
			 uchar *src_data = mat.ptr<uchar>(i);
			 for (int j = 0; j < mat.cols*mat.channels(); j++) {
				 histogram[(int)src_data[j]]++;
			 }
		 }
		 int sum = 0;
		 for (int i = 0; i < 256; i++) {
			 sum += histogram[i];
		 }
		 //u = sum / (src.rows*src.cols*src.channels()*1.0);
		 int sum0 = 0;
		 double w0 = 0.0, w1 = 0.0, u0 = 0.0, u1 = 0.0;
		 for (int i = 0; i < 255; i++) {
			 u0 = 0.0;
			 sum0 = 0;
			 for (int j = 0; j <= i; j++) {
				 u0 += j * histogram[j];
				 sum0 += histogram[j];
			 }
			 u0 = u0 / sum0;
			 w0 = sum0 *1.0 / sum;
			 u1 = 0.0;
			 for (int j = i+1; j <= 255; j++) {
				 u1 += j * histogram[j];
			 }
			 u1 = u1 / (sum-sum0);
			 w1 = 1 - w0;
			 cov = w0*w1*(u1 - u0)*(u1 - u0);
			 if (cov > maxcov) {
				 maxcov = cov;
				 split_index = i;
			 }
		 }
		 dst.create(mat.rows, mat.cols, CV_8UC1);
		 for (int i = 0; i < dst.rows; i++) {
			 uchar *dst_data = dst.ptr<uchar>(i);
			 uchar *src_data = mat.ptr<uchar>(i);
			 for (int j = 0; j < dst.cols; j++) {
				 if ((int)src_data[j] < split_index)
					 dst_data[j] = 0;
				 else
					 dst_data[j] = 255;
			 }
		 }
}

void  myCVlib::doubleThreshold(cv::Mat src, cv::Mat&dst, int minPixel, int maxPixel) {
	cv::Mat mat;
	convertToGrey(src, mat);
	dst.create(mat.rows, mat.cols, CV_8UC1);
	for (int i = 0; i < dst.rows; i++) {
		uchar *dst_data = dst.ptr<uchar>(i);
		uchar *src_data = mat.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++) {
			if ((int)src_data[j] < minPixel)
				dst_data[j] = 0;
			else if ((int)src_data[j] > maxPixel)
				dst_data[j] = 255;
			else
				dst_data[j] = src_data[j];
		}
	}
}

void  myCVlib::doubleThresholdBinary(cv::Mat src, cv::Mat&dst, int minPixel, int maxPixel) {
	cv::Mat mat;
	convertToGrey(src, mat);
	dst.create(mat.rows, mat.cols, CV_8UC1);
	for (int i = 0; i < dst.rows; i++) {
		uchar *dst_data = dst.ptr<uchar>(i);
		uchar *src_data = mat.ptr<uchar>(i);
		for (int j = 0; j < dst.cols; j++) {
			if ((int)src_data[j] < minPixel || (int)src_data[j] > maxPixel)
				dst_data[j] = 0;
			else
				dst_data[j] = 255;
		}
	}
}

void myCVlib::op_add(cv::Mat src1, cv::Mat src2, cv::Mat &dst) {
	if (src1.rows != src2.rows || src1.cols != src2.cols) {
		dst = src1.clone();
		return;
	}
	if (src1.channels() == 3 && src2.channels() == 1) {
		cv::Mat src1_grey;
		convertToGrey(src1, src1_grey);
		dst.create(src1_grey.size(), CV_8UC1);
		for (int i = 0; i < src1_grey.rows; i++) {
			uchar *src1_data = src1_grey.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1_grey.cols*src1_grey.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] +(double) src2_data[j]);
			}
		}
		return;
	}

	else if (src1.channels() == 1 && src2.channels() == 1) {
		dst.create(src1.size(), CV_8UC1);
		for (int i = 0; i < src1.rows; i++) {
			uchar *src1_data = src1.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1.cols*src1.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] +(double) src2_data[j]);
			}
		}
		return;
	}
	else {
		dst = src1.clone();
		return;
	}
}
void myCVlib::op_subtract(cv::Mat src1, cv::Mat src2, cv::Mat &dst) {
	if (src1.rows != src2.rows || src1.cols != src2.cols) {
		dst = src1.clone();
		return;
	}
	if (src1.channels() ==3 && src2.channels()==1) {
		cv::Mat src1_grey;
		convertToGrey(src1, src1_grey);
		dst.create(src1_grey.size(), CV_8UC1);
		for (int i = 0; i < src1_grey.rows; i++) {
			uchar *src1_data = src1_grey.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1_grey.cols*src1_grey.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] - (double)src2_data[j]);
			}
		}
		return;
	}

	else if (src1.channels() == 1 && src2.channels() == 1) {
		dst.create(src1.size(), CV_8UC1);
		for (int i = 0; i < src1.rows; i++) {
			uchar *src1_data = src1.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1.cols*src1.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] -(double) src2_data[j]);
			}
		}
		return;
	}
	else {
		dst = src1.clone();
		return;
	}
	
}
void myCVlib::op_multiple(cv::Mat src1, cv::Mat src2, cv::Mat &dst) {
	if (src1.rows != src2.rows || src1.cols != src2.cols) {
		dst = src1.clone();
		return;
	}
	if (src1.channels() == 3 && src2.channels() == 1) {
		cv::Mat src1_grey;
		convertToGrey(src1, src1_grey);
		dst.create(src1_grey.size(), CV_8UC1);
		for (int i = 0; i < src1_grey.rows; i++) {
			uchar *src1_data = src1_grey.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1_grey.cols*src1_grey.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] * (double)src2_data[j]);
			}
		}
		return;
	}

	else if (src1.channels() == 1 && src2.channels() == 1) {
		dst.create(src1.size(), CV_8UC1);
		for (int i = 0; i < src1.rows; i++) {
			uchar *src1_data = src1.ptr<uchar>(i);
			uchar *src2_data = src2.ptr<uchar>(i);
			uchar *dst_data = dst.ptr<uchar>(i);
			for (int j = 0; j < src1.cols*src1.channels(); j += 1) {
				dst_data[j] = clamp((double)src1_data[j] * (double)src2_data[j]);
			}
		}
		return;
	}
	else {
		dst = src1.clone();
		return;
	}
}

void myCVlib::getGaussianKernel(double **gaus, int size, double sigma) {
	const double pi = 4.0*atan(1.0);
	int center = size / 2;
	double sum = 0.0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			gaus[i][j] = (1 / (2 * pi*sigma*sigma))*exp(-((i - center)*(i - center) + (j - center)*(j - center)) / (2 * sigma*sigma));
			sum += gaus[i][j];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			gaus[i][j] /= sum;
		}
	}
}

void myCVlib::gaussianFilter(cv::Mat src, cv::Mat & dst, double**gaus, int size) {
	dst.create(src.size(), CV_8UC1);
	double *gausArray = new double[size*size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			gausArray[i*size + j] = gaus[i][j];
		}
	}
	for (int i = 0; i < src.rows; i++) {
		for (int j = 0; j < src.cols; j++) {
			int k = 0;
			double count = 0.0;
			for (int m = -size / 2; m <= size / 2; m++) {
				for (int n = -size / 2; n <= size / 2; n++) {
					int x = i + m;
					int y = j + n;
					x = x<0 ? 0 : x;
					x = x >= src.rows ? src.rows - 1 : x;
					y = y<0 ? 0 : y;
					y = y >= src.cols ? src.cols - 1 : y;
					count += gausArray[k] * (double)src.at <uchar>(x, y);
					k++;
				}
			}
			dst.at<uchar>(i, j) = (uchar)count;
		}
	}
	delete[] gausArray;
}
void myCVlib::sobelGradDirction(cv::Mat src, cv::Mat &dst_SobelX, cv::Mat &dst_SobelY, double *&directionArray) {
	directionArray = new double[(src.rows - 1)*(src.cols - 1)];
	for (int i = 0; i < (src.rows - 1)*(src.cols - 1); i++) {
			directionArray[i] = 0;
	}
	dst_SobelX=cv::Mat::zeros(src.size(), CV_8UC1);
	dst_SobelY=cv::Mat::zeros(src.size(), CV_8UC1);
	int k = 0;
	for (int i = 1; i < src.rows-1; i++) {
		for (int j = 1; j < src.cols-1; j++) {
			double gradY = (double)src.at<uchar>(i - 1, j + 1) + 2 * (double)src.at<uchar>(i, j + 1) + (double)src.at<uchar>(i - 1, j + 1) -
				(double)src.at<uchar>(i - 1, j - 1) - 2 * (double)src.at<uchar>(i, j - 1) - (double)src.at<uchar>(i + 1, j - 1);
			double gradX = (double)src.at<uchar>(i + 1, j - 1) + 2 * (double)src.at<uchar>(i+1, j) + (double)src.at<uchar>(i + 1, j + 1) -
				(double)src.at<uchar>(i - 1, j - 1) - 2 * (double)src.at<uchar>(i-1, j) - (double)src.at<uchar>(i-1,j+1);
			dst_SobelX.at<uchar>(i, j) = (uchar)abs(gradX);
			dst_SobelY.at<uchar>(i, j) = (uchar)abs(gradY);
			if (gradX == 0) {
				gradX = 0.00000001;
			}
			directionArray[k] = atan(gradY / gradX)*57.3 + 90;
			k++;
		}
	}
}
void myCVlib::amplitude(cv::Mat src_x, cv::Mat src_y, cv::Mat &dst_xy) {
	dst_xy.create(src_x.size(), CV_8UC1);
	for (int i = 0; i < dst_xy.rows; i++) {
		for (int j = 0; j < dst_xy.cols; j++) {
			dst_xy.at<uchar>(i, j) =(uchar)sqrt((int)src_x.at<uchar>(i, j)*(int)src_x.at<uchar>(i, j) + (int)src_y.at<uchar>(i, j)*(int)src_y.at<uchar>(i, j));
		}
	}
}
void myCVlib::localMaxValue(cv::Mat src, cv::Mat &dst, double *directionArray) {
	//imageInput.copyTo(imageOutput);  
	dst = src.clone();
	int k = 0;
	for (int i = 1; i<src.rows - 1; i++)
	{
		for (int j = 1; j<src.cols - 1; j++)
		{
			int value00 = src.at<uchar>((i - 1), j - 1);
			int value01 = src.at<uchar>((i - 1), j);
			int value02 = src.at<uchar>((i - 1), j + 1);
			int value10 = src.at<uchar>((i), j - 1);
			int value11 = src.at<uchar>((i), j);
			int value12 = src.at<uchar>((i), j + 1);
			int value20 = src.at<uchar>((i + 1), j - 1);
			int value21 = src.at<uchar>((i + 1), j);
			int value22 = src.at<uchar>((i + 1), j + 1);

			if (directionArray[k]>0 && directionArray[k] <= 45)
			{
				if (value11 <= (value12 + (value02 - value12)*tan(directionArray[i*(src.rows-1) + j])) || (value11 <= (value10 + (value20 - value10)*tan(directionArray[i*(src.rows-1) + j]))))
				{
					src.at<uchar>(i, j) = 0;
				}
			}
			if (directionArray[k]>45 && directionArray[k] <= 90)

			{
				if (value11 <= (value01 + (value02 - value01) / tan(directionArray[i*(src.cols-1) + j])) || value11 <= (value21 + (value20 - value21) / tan(directionArray[i*(src.cols-1) + j])))
				{
					src.at<uchar>(i, j) = 0;

				}
			}
			if (directionArray[k]>90 && directionArray[k] <= 135)
			{
				if (value11 <= (value01 + (value00 - value01) / tan(180 - directionArray[i*(src.cols-1) + j])) || value11 <= (value21 + (value22 - value21) / tan(180 - directionArray[i*(src.cols-1) + j])))
				{
					src.at<uchar>(i, j) = 0;
				}
			}
			if (directionArray[k]>135 && directionArray[k] <= 180)
			{
				if (value11 <= (value10 + (value00 - value10)*tan(180 - directionArray[i*(src.cols-1) + j])) || value11 <= (value12 + (value22 - value11)*tan(180 - directionArray[i*(src.cols-1) + j])))
				{
					src.at<uchar>(i, j) = 0;
				}
			}
			k++;
		}
	}
}
void myCVlib::doubleThresholdLink(cv::Mat src, cv::Mat &dst, double lowThreshold, double highThreshold) {
	dst = src.clone();
	for (int i = 1; i<src.rows - 1; i++)
	{
		for (int j = 1; j<src.cols - 1; j++)
		{
			if (src.at<uchar>(i, j)>lowThreshold&&src.at<uchar>(i, j)<255)
			{
				if (src.at<uchar>(i - 1, j - 1) == 255 || src.at<uchar>(i - 1, j) == 255 || src.at<uchar>(i - 1, j + 1) == 255 ||
					src.at<uchar>(i, j - 1) == 255 || src.at<uchar>(i, j) == 255 || src.at<uchar>(i, j + 1) == 255 ||
					src.at<uchar>(i + 1, j - 1) == 255 || src.at<uchar>(i + 1, j) == 255 || src.at<uchar>(i + 1, j + 1) == 255)
				{
					dst.at<uchar>(i, j) = 255;
				}
				else
				{
					dst.at<uchar>(i, j) = 0;
				}
			}
		}
	}
}


void myCVlib::canny(cv::Mat src, cv::Mat &dst, double lowThreshold,double highThreshold, int aperture_size , int aperture_sigma) {
	cv::Mat mat;
	if (src.channels() == 3) {
		convertToGrey(src, mat);
	}
	else if (src.channels() == 1) {
		mat = src.clone();
	}
	else
		return;
	dst.create(mat.size(), CV_8UC1);
	double **gaus = new double*[aperture_size];
	for (int i = 0; i < aperture_size; i++) {
		gaus[i] = new double[aperture_size];
	}
	getGaussianKernel(gaus, aperture_size, aperture_sigma);
	cv::Mat mat_gaus;
	gaussianFilter(mat, mat_gaus, gaus, aperture_size);
	cv::Mat sobel_X, sobel_Y;
	double *directionArray;
	sobelGradDirction(mat_gaus, sobel_X, sobel_Y, directionArray);
	cv::Mat sobel_XY;
	amplitude(sobel_X, sobel_Y, sobel_XY);
	cv::Mat localMax;
	localMaxValue(sobel_XY, localMax, directionArray);
	cv::Mat threshold;
	doubleThreshold(localMax, threshold, lowThreshold, highThreshold);
	doubleThresholdLink(threshold,dst, lowThreshold, highThreshold);
	//dst = sobel_X.clone();
	//dst = sobel_Y.clone();
	for (int i = 0; i < aperture_size; i++) {
		delete[] gaus[i];
	}
	delete[] gaus;
	delete[] directionArray;
}

void myCVlib::gausFilter(cv::Mat src, cv::Mat &dst, int  aperture_size, int aperture_sigma){
cv::Mat mat;
	if (src.channels() == 3) {
		convertToGrey(src, mat);
	}
	else if (src.channels() == 1) {
		mat = src.clone();
	}
	else
		return;
	double **gaus = new double*[aperture_size];
	for (int i = 0; i < aperture_size; i++) {
		gaus[i] = new double[aperture_size];
	}
	getGaussianKernel(gaus, aperture_size, aperture_sigma);
	dst.create(mat.size(), CV_8UC1);
	gaussianFilter(mat, dst, gaus, aperture_size);
	for (int i = 0; i < aperture_size; i++) {
		delete[] gaus[i];
	}
	delete[] gaus;
}


