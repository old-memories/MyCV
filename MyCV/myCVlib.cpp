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
	 static uchar clamp(double value) {
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
	const double pi = CV_PI;
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

void myCVlib::avgFilter(cv::Mat src, cv::Mat &dst, int size) {
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

	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			int k = 0;
			double count = 0.0;
			for (int m = -size / 2; m <= size / 2; m++) {
				for (int n = -size / 2; n <= size / 2; n++) {
					int x = i + m;
					int y = j + n;
					x = x < 0 ? 0 : x;
					x = x >= mat.rows ? mat.rows - 1 : x;
					y = y < 0 ? 0 : y;
					y = y >= mat.cols ? mat.cols - 1 : y;
					count += 1.0/(size*size) * (double)mat.at <uchar>(x, y);
					k++;
				}
			}
			dst.at<uchar>(i, j) = (uchar)count;
		}
	}
}
void myCVlib::midFilter(cv::Mat src, cv::Mat &dst, int size) {
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

	for (int i = 0; i < mat.rows; i++) {
		for (int j = 0; j < mat.cols; j++) {
			int k = 0;
			std::vector<double> count;
			count.clear();
			for (int m = -size / 2; m <= size / 2; m++) {
				for (int n = -size / 2; n <= size / 2; n++) {
					int x = i + m;
					int y = j + n;
					x = x < 0 ? 0 : x;
					x = x >= mat.rows ? mat.rows - 1 : x;
					y = y < 0 ? 0 : y;
					y = y >= mat.cols ? mat.cols - 1 : y;
					//count = std::max(count,(double)src.at <uchar>(x, y));
					count.push_back( (double)mat.at <uchar>(x, y));
					k++;
				}
			}
			std::sort(count.begin(), count.end());
			double mid = count[size*size/2];
			dst.at<uchar>(i, j) = (uchar)mid;
		}
	}
}
void myCVlib::sobelDector(cv::Mat src, cv::Mat &dst) {
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
	cv::Mat sobel_X, sobel_Y;
	double *directionArray;
	sobelGradDirction(mat, sobel_X, sobel_Y, directionArray);
	amplitude(sobel_X, sobel_Y, dst);
	delete[] directionArray;
}

void myCVlib::laplaceDector(cv::Mat src, cv::Mat &dst) {
	cv::Mat mat;
	gausFilter(src, mat,11, 5);

	dst.create(mat.size(), CV_8UC1);
	int size = 3;
	double *laplaceArray = new double[size*size];
	laplaceArray[0] = 0;
	laplaceArray[1] = 1;
	laplaceArray[2] = 0;
	laplaceArray[3] = 1;
	laplaceArray[4] = -4;
	laplaceArray[5] = 1;
	laplaceArray[6] = 0;
	laplaceArray[7] = 1;
	laplaceArray[8] = 0;

for (int i = 0; i < mat.rows; i++) {
	for (int j = 0; j < mat.cols; j++) {
		int k = 0;
		double count = 0.0;
		for (int m = -size / 2; m <= size / 2; m++) {
			for (int n = -size / 2; n <= size / 2; n++) {
				int x = i + m;
				int y = j + n;
				x = x < 0 ? 0 : x;
				x = x >= mat.rows ? mat.rows - 1 : x;
				y = y < 0 ? 0 : y;
				y = y >= mat.cols ? mat.cols - 1 : y;
				count += laplaceArray[k] * (double)mat.at <uchar>(x, y);
				k++;
			}
		}





		dst.at<uchar>(i, j) = (uchar)count;
	}
}
delete[] laplaceArray;


}

void myCVlib::nn_resize(cv::Mat src, cv::Mat &dst, float ratio) {
	cv::Mat mat;
	if (src.channels() == 3) {
		convertToGrey(src, mat);
	}
	else if (src.channels() == 1) {
		mat = src.clone();
	}
	else
		return;
	dst.create(int(mat.rows*ratio), int(mat.cols*ratio), CV_8UC1);
	for (int i = 0; i < int(mat.rows*ratio); i++) {
		for (int j = 0; j < int(mat.cols*ratio); j++) {

			dst.at<uchar>(i, j) = mat.at<uchar>(int(i*1.0f / ratio), int(j*1.0 / ratio));
		}
	}

}
void myCVlib::linear_resize(cv::Mat src, cv::Mat &dst, float ratio) {
	cv::Mat mat;
	if (src.channels() == 3) {
		convertToGrey(src, mat);
	}
	else if (src.channels() == 1) {
		mat = src.clone();
	}
	else
		return;
	dst.create(int(mat.rows *ratio), int(mat.cols *ratio), CV_8UC1);
	for (int i = 0; i < int(mat.rows *ratio); i++) {
		for (int j = 0; j < int(mat.cols *ratio); j++) {
			float x0 = i*1.0f / ratio;
			float y0 = j*1.0f / ratio;

			int x1 = int(x0);
			int x2 = (x1 + 1) >= mat.rows ? x1 : x1 + 1;
			int y1 = int(y0);
			int y2 = (y1 + 1) >= mat.cols ? y1 : y1 + 1;
			float fx1 = x0 - x1;
			float fx2 = 1.0f - fx1;
			float fy1 = y0 - y1;
			float fy2 = 1.0f - fy1;

			float s1 = fx1*fy1;
			float s2 = fx2*fy1;
			float s3 = fx2*fy2;
			float s4 = fx1*fy2;
			dst.at<uchar>(i, j) = uchar(float(mat.at<uchar>(x2, y2)*s1)
				+ float(mat.at<uchar>(x1, y2)*s2)
				+ float(mat.at<uchar>(x1, y1)*s3)
				+ float(mat.at<uchar>(x2, y1)*s4));
		}
	}
}

static int Max_four(int a, int b, int c, int d)
{
	int max = 0;
	max = a>b ? a : b;
	max = max>c ? max : c;
	max = max>d ? max : d;
	return max;
}

static int Min_four(int a, int b, int c, int d)
{
	int min = 0;
	min = a<b ? a : b;
	min = min<c ? min : c;
	min = min<d ? min : d;
	return min;
}

void myCVlib::nn_rotate(cv::Mat src, cv::Mat &dst, float angle) {
	cv::Mat mat;
	if (src.channels() == 3) {
		convertToGrey(src, mat);
	}
	else if (src.channels() == 1) {
		mat = src.clone();
	}
	else
		return;


	float rad = angle*(CV_PI / 180);
	int nWidth = mat.cols;
	int nHeight = mat.rows;

	int srcX1 = 0;
	int srcY1 = 0;
	int srcX2 = nWidth - 1;
	int srcY2 = 0;//nHeight/2;  
	int srcX3 = nWidth - 1;
	int srcY3 = -(nHeight - 1);
	int srcX4 = 0;
	int srcY4 = -(nHeight - 1);

	int detX1 = (int)((cos(rad)*srcX1 + sin(rad)*srcY1) + 0.5);
	int dstY1 = (int)((-sin(rad)*srcX1 + cos(rad)*srcY1) + 0.5);
	int dstX2 = (int)((cos(rad)*srcX2 + sin(rad)*srcY2) + 0.5);
	int dstY2 = (int)((-sin(rad)*srcX2 + cos(rad)*srcY2) + 0.5);
	int dstX3 = (int)((cos(rad)*srcX3 + sin(rad)*srcY3) + 0.5);
	int dstY3 = (int)((-sin(rad)*srcX3 + cos(rad)*srcY3) + 0.5);
	int dstX4 = (int)((cos(rad)*srcX4 + sin(rad)*srcY4) + 0.5);
	int dstY4 = (int)((-sin(rad)*srcX4 + cos(rad)*srcY4) + 0.5);

	int max_dstX = Max_four(detX1, dstX2, dstX3, dstX4);
	int max_dstY = Min_four(dstY1, dstY2, dstY3, dstY4);

	int dstWidth = std::max(abs(detX1 - dstX3), abs(dstX2 - dstX4)) + 1;
	int dstHeight = std::max(abs(dstY1 - dstY3), abs(dstY2 - dstY4)) + 1;

	dst.create(dstHeight, dstWidth,CV_8UC1);

	float varX = (float)(-(dstWidth - abs(max_dstX))*cos(rad) - (dstHeight - abs(max_dstY))*sin(rad));
	float varY = (float)((dstWidth - abs(max_dstX))*sin(rad) - (dstHeight - abs(max_dstY))*cos(rad));

	for (int i = 0; i<dstHeight; i++)
		for (int j = 0; j < dstWidth; j++)
		{
			int x = (int)(cos(rad)*j + sin(rad)*i + varX);
			int y = (int)(-sin(rad)*j + cos(rad)*i + varY);

			if (x > (nWidth - 1) || x<0 || y>(nHeight - 1) || y < 0)

				dst.at<uchar>(i, j) = 0;

			else {

				dst.at<uchar>(i, j) = mat.at<uchar>(y, x);
			}
		}
}

static void sort(int* seq, int length, int* data){
	int i, j, t1, t;
	for (j = 0; j<length; j++)
		for (i = 0; i<length - 1 - j; i++)
			if (data[i]<data[i + 1])
			{
				t = data[i];
				data[i] = data[i + 1];
				data[i + 1] = t;


				t1 = seq[i];
				seq[i] = seq[i + 1];
				seq[i + 1] = t1;
			}
}

void myCVlib::createHoughLine(cv::Mat src, int threshold, std::vector<std::pair<float, float>> &lines, float rho, float theta) {
	int numangle = int(CV_PI / theta);
	int numrho = int(((src.cols + src.rows) * 2 + 1) / rho);
	int total = 0;
	int *accum = new int[(numangle + 2)*(numrho + 2)];
	memset(accum, 0, sizeof(accum[0])*(numangle + 2)*(numrho + 2));
	int *detectd_lines = new int[numangle*numrho];
	int *sort_buf = new int[numangle*numrho];
	float *tabSin = new float[numangle];
	float *tabCos = new float[numangle];
	float ang = 0;
	for (int n = 0; n < numangle; ang += theta, n++)
	{
		tabSin[n] = (float)(sin((double)ang) * 1.0f / rho);
		tabCos[n] = (float)(cos((double)ang) * 1.0f / rho);
	}

	for (int i = 0; i < src.rows; i++){
		for (int j = 0; j < src.cols; j++) {
			if (src.at<uchar>(i, j) != 0) {
				for (int n = 0; n < numangle; n++) {
					int r = int(j*tabCos[n] + i*tabSin[n]);
					r += (numrho - 1) / 2;
					accum[(n + 1)*(numrho + 2) + r + 1]++;
				}
			}
		}
	}

	for (int r = 0; r < numrho; r++) {
		for (int n = 0; n < numangle; n++) {
			int base = (n + 1) * (numrho + 2) + r + 1;
			if (accum[base] > threshold &&
				accum[base] > accum[base - 1] && accum[base] >= accum[base + 1] &&
				accum[base] > accum[base - numrho - 2] && accum[base] >= accum[base + numrho + 2]) {
				detectd_lines[total] = accum[base];
				sort_buf[total] = base;
				total++;
			}
				
		}
	}

	sort(sort_buf, total, detectd_lines);

	float scale = 1.0f / (numrho + 2);
	for (int i = 0; i < total; i++) {
		int idx = sort_buf[i];
		int n = int(idx*scale) - 1;
		int r = idx - (n + 1)*(numrho + 2) - 1;
		float line_rho = (r - (numrho - 1)*0.5f) * rho;
		float line_angle = n * theta;
		lines.push_back(std::pair<float, float>(line_rho, line_angle));
	}

	delete[] accum;
	delete[] detectd_lines;
	delete[] sort_buf;
	delete[] tabSin;
	delete[] tabCos;
}

void myCVlib::houghLine(cv::Mat src, int threshold, cv::Mat &dst) {
	cv::Mat mat;

	mat.create(src.size(), CV_8UC1);
	//dst.create(src.size(), CV_8UC1);
	canny(src, mat, 50, 200, 3);
	std::vector<std::pair<float, float>> lines;
	createHoughLine(mat, threshold, lines, 1, CV_PI / 180);
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i].first, theta = lines[i].second;
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a*rho, y0 = b*rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(dst, pt1, pt2, cv::Scalar(0, 0, 150), 3, CV_AA);
	}
}

void myCVlib::createhoughCircle(cv::Mat src, cv::Mat sobel_x, cv::Mat sobel_y, std::vector<std::pair<std::pair<float, float>, float>> &circles, double min_dist, int canny_threshold, int threshold, int minRadius, int maxRadius) {
	const int SHIFT = 10, ONE = 1 << SHIFT;
	int *accum = new int[(src.rows + 2)*(src.cols + 2)];
	int *detected_centers = new int[src.rows *src.cols];
	memset(accum, 0, sizeof(accum[0])*(src.rows + 2)*(src.cols + 2));
	std::vector<std::pair<int, int>>nz;
	std::vector<int> centers;
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			float vx = sobel_x.at<short>(y, x);
			float vy = sobel_y.at<short>(y, x);
			if (!src.at<uchar>(y, x) || (vx == 0 && vy == 0))
				continue;
			float mag = sqrt(vx*vx + vy*vy);
			int sx = int(vx*ONE / mag);
			int sy = int(vy*ONE / mag);

			int x0 = int(x*ONE);
			int y0 = int(y*ONE);

			for (int k1 = 0; k1 < 2; k1++) {
				int x1 = x0 + minRadius*sx;
				int y1 = y0 + minRadius*sy;
				for (int r = minRadius; r <= maxRadius; x1 + sx, y1 + sy, r++) {
					int x2 = x1 >> SHIFT, y2 = y1 >> SHIFT;
					if ((unsigned int)x2 >= (unsigned int)(src.cols) || (unsigned int)y2 >= (unsigned int)(src.rows))
						break;
					accum[y*src.rows + x2]++;
				}
				sx = -sx; sy = -sy;
			}
			nz.push_back(std::pair<int, int>(x, y));
		}
	}
	int nz_count = nz.size();
	if (!nz_count)
		return;
	int k = 0;
	for (int y = 1; y < src.rows - 1; y++) {
		for (int x = 1; x < src.cols - 1; x++) {
			int base = y*src.rows + x;
			if (accum[base] > threshold &&
				accum[base] > accum[base - 1] && accum[base] > accum[base + 1] &&
				accum[base] > accum[base - src.cols - 4] && accum[base] > accum[base + src.cols]) {
				centers.push_back(base);
				detected_centers[k] = accum[base];
				k++;
			}

		}
	}
	int center_count = centers.size();
	if (!center_count)
		return;
	int *sort_buf = new int[MAX(center_count, nz_count)];
	for (int i = 0; i < center_count; i++) {
		sort_buf[i] = centers[i];
	}
	sort(sort_buf, center_count, detected_centers);
	centers.clear();
	for (int i = 0; i < center_count; i++) {
		centers[i] = sort_buf[i];
	}
	memset(sort_buf, 0, sizeof(sort_buf[0])*MAX(center_count, nz_count));
	int *dist_buf = new int[nz_count];
	int x;
	int y;
	min_dist = MAX(min_dist, 1);
	min_dist *= min_dist;
	for (int i = 0; i < center_count; i++) {
		int ofs = centers[i];
		y = ofs / src.rows;
		x = ofs - y*src.rows;
		float r_best = 0;
		int max_count = 0;
		float dist_sum, start_dist;
		float cx = (float)(x + 0.5f), cy = (float)(y + 0.5f);
		int a = 0;
		for (a = 0; a < circles.size(); a++) {
			if ((circles[a].first.first - cx)*(circles[a].first.first - cx) + (circles[a].first.second - cy)*(circles[a].first.second - cy) < min_dist)
				break;
		}
		if (a < circles.size())
			continue;
		int b, c;
		for (b = c = 0; b < nz_count; b++)
		{
			float _dx, _dy, _r2;
			_dx = cx - nz[b].first; _dy = cy - nz[b].second;
			_r2 = _dx*_dx + _dy*_dy;
			if (minRadius*minRadius <= _r2 && _r2 <= maxRadius*maxRadius)
			{
				dist_buf[k] = _r2;
				sort_buf[k] = k;
				k++;
			}
		}

		int nz_count1 = k, start_idx = nz_count1 - 1;
		if (nz_count1 == 0)
			continue;
		for (int m = 0; m < nz_count; m++) {
			sqrt(dist_buf[m]);
		}
		sort(sort_buf, nz_count1, dist_buf);
		dist_sum = start_dist = dist_buf[nz_count1 - 1];
		for (int j = nz_count1 - 2; j >= 0; j--)
		{
			float d = dist_buf[j];

			if (d > maxRadius)
				break;

			if (d - start_dist > 1)
			{
				float r_cur = dist_buf[(j + start_idx) / 2];
				if ((start_idx - j)*r_best >= max_count*r_cur ||
					(r_best < FLT_EPSILON && start_idx - j >= max_count))
				{
					r_best = r_cur;
					max_count = start_idx - j;
				}
				start_dist = d;
				start_idx = j;
				dist_sum = 0;
			}
			dist_sum += d;
		}
		// Check if the circle has enough support
		if (max_count > threshold)
		{
			float c[3];
			c[0] = cx;
			c[1] = cy;
			c[2] = (float)r_best;
			std::pair<float, float> p0(cx, cy);
			std::pair<std::pair<float, float>, float> p1(p0, r_best);
			circles.push_back(p1);
		}
	}
}

void myCVlib::houghCircle(cv::Mat src, cv::Mat &dst, double dp, double min_dist, double canny_threshold, double threshold, int minRadius, int maxRadius) {
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	gausFilter(src, mat, 9, 3);
	std::vector<cv::Vec3f> circles;
	cv::HoughCircles(mat, circles, CV_HOUGH_GRADIENT, dp, min_dist, canny_threshold, threshold, minRadius, maxRadius);
	for (int i = 0; i < circles.size(); i++) {
		cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		circle(dst, center, 3, cv::Scalar(0, 255, 0), -1, 8, 0);
		circle(dst, center, radius, cv::Scalar(0, 0, 255), 3, 8, 0);
	}
}

void myCVlib::calcHist(cv::Mat src, int *hist, int histSize, int *ranges) {
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	convertToGrey(src, mat);
	int histogram[256] = { 0 };
	for (int i = 0; i < mat.rows; i++) {
		uchar *src_data = mat.ptr<uchar>(i);
		for (int j = 0; j < mat.cols*mat.channels(); j++) {
			histogram[(int)src_data[j]]++;
		}
	}
	//0-25 26-51 52-77 78-103 103-128 129-154 155-180 181-206 207-232 233-258
	//0-4 5-9 10-14 15-19 20-24

	int step = cvCeil((ranges[1] - ranges[0])*1.0 / histSize);
	for (int i = ranges[0]; i <= ranges[1]; i++) {
		hist[i / step] += histogram[i];
	}
	
	
}

void myCVlib::getHistImg(int* hist, cv::Mat &dst, int histSize, int *ranges) {
	
	
	int minVal = INT32_MAX;
	int maxVal = INT32_MIN;
	for (int i = 0; i < histSize; i++) {
		if (hist[i] < minVal)
			minVal = hist[i];
		if (hist[i] > maxVal)
			maxVal = hist[i];
	}
	cv::Mat mat(400, 400, CV_8U, cv::Scalar(255));
	int hpt = 360;
	for (int h = 0; h < histSize; h++) {
		int val = hist[h];
		int intensity = int(val *hpt / maxVal);
		cv::line(mat, cv::Point(1.0*h/histSize*400, 400), cv::Point(1.0*h / histSize * 400,  400-intensity),cv:: Scalar::all(0),10);
	}
	dst = mat.clone();
}


void myCVlib::equalizeHist(cv::Mat src, cv::Mat &dst,int histSize,int *ranges) {
	int *hist = new int[histSize];
	float *hs = new float[histSize];
	float *hp = new float[histSize];
	int *equalizedHist = new int[histSize];
	memset(hist, 0, sizeof(int)*histSize);
	memset(hs, 0, sizeof(float)*histSize);
	memset(hp, 0, sizeof(float)*histSize);
	memset(equalizedHist, 0, sizeof(int)*histSize);
	calcHist(src, hist, histSize, ranges);
	
	int sum = src.rows*src.cols;
	
	for (int i = 0; i < histSize; i++) {
		hs[i] = hist[i] * 1.0 / sum;
	}
	for (int i = 0; i < histSize; i++) {
		if (i == 0)
			hp[i] = hs[i];
		else
			hp[i] = hp[i - 1] + hs[i];
		equalizedHist[i] = cvRound(255.0*hp[i]);
	}

	dst.create(src.size(), CV_8UC1);
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	convertToGrey(src, mat);


	for (int i = 0; i < mat.rows; i++) {
		uchar *src_data = mat.ptr<uchar>(i);
		uchar *dst_data = dst.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j++) {
			int grey =int (src_data[j]);
			if (grey == 0)
				dst_data[j] = 0;
			else
				dst_data[j] = uchar(equalizedHist[grey]);
		}
	}
	delete[] hist;
	delete[] hs;
	delete[] hp;
	delete[] equalizedHist;
}

void myCVlib::linear_adjustContrast(cv::Mat src, cv::Mat &dst, int *p1, int *p2) {
	
	double x1 = p1[0];
	double y1 = p1[1];
	double x2 = p2[0];
	double y2 = p2[1];
	if (x1 == 0 || y1==255|| x1 == x2)
		return;
	double k1 = y1*1.0 / x1;
	double k2 = (y2 - y1)*1.0 / (x2 - x1);
	double k3 = (255.0 - y2) / (255.0 - y1);

	dst.create(src.size(), CV_8UC1);
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	convertToGrey(src, mat);

	for (int i = 0; i < mat.rows; i++) {
		uchar *src_data = mat.ptr<uchar>(i);
		uchar *dst_data = dst.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j++) {
			double x = double(src_data[j]);
			if (x < x1) {
				dst_data[j] = cvRound(k1*x);
			}
			else if (x >= x1&&x <= x2) {
				dst_data[j] = cvRound(k2*(x-x1)+y1);
			}
			else {
				dst_data[j] = cvRound(k3*(x - x2) + y2);
			}
		}
	}
}

void myCVlib::log_adjustContrast(cv::Mat src, cv::Mat &dst, int ground) {
	dst.create(src.size(), CV_8UC1);
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	convertToGrey(src, mat);

	for (int i = 0; i < mat.rows; i++) {
		uchar *src_data = mat.ptr<uchar>(i);
		uchar *dst_data = dst.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j++) {
			double src_grey = double(src_data[j]) / 255.0;
			dst_data[j] = clamp(cvRound(log(1+ src_grey*ground) / log(1+ground)*255.0));
		}
	}
}
void myCVlib::pow_adjustContrast(cv::Mat src, cv::Mat &dst, int index) {
	dst.create(src.size(), CV_8UC1);
	cv::Mat mat;
	mat.create(src.size(), CV_8UC1);
	convertToGrey(src, mat);

	for (int i = 0; i < mat.rows; i++) {
		uchar *src_data = mat.ptr<uchar>(i);
		uchar *dst_data = dst.ptr<uchar>(i);
		for (int j = 0; j < mat.cols; j++) {
			double src_grey = double(src_data[j]) / 255.0;
			dst_data[j] = clamp(cvRound(pow(src_grey, index)*255.0));
		}
	}
}

