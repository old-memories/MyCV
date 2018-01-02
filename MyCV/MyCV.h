#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"
#include "HSLSliderWidget.h"
#include "ImageShowLabel.h"
#include "BinarizationSliderWidget.h"
#include "CannySliderWidget.h"
#include "GausFilterSliderWidget.h"
#include "HoughSliderWidget.h"
#include "SetSEWidget.h"

class MyCV : public QMainWindow
{
	Q_OBJECT

public:
	MyCV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCVClass ui;
	QTextCodec *code;
	ImageShowLabel *imageShowLabel;
	QWidget *histImageShowWindow;
	QLabel *histImageShowLabel;
	HSLSliderWidget *adjustHSLWindow;
	BinarizationSliderWidget *binarizationWindow;
	GausFilterSliderWidget *gausFilterWindow;
	CannySliderWidget *cannyWindow;
	HoughSliderWidget *houghLineWindow;
	HoughSliderWidget *houghCircleWindow;
	SetSEWidget *setSEWindow;

	QMenu* file_menu;
	QMenu* edit_menu;
	QMenu* addition_menu;
	cv::Mat src_image;
	std::vector<char> kernal;
	void setEnable_when_displayMat();
	enum ImageStatus {NO_IMAGE,IMAGE_REMAINED,IMAGE_CHANGED} imageStatus;
private slots:
	void on_beautifyCamera_action_selected();
	void on_open_action_selected();
	void on_splitR_action_selected();
	void on_splitG_action_selected();
	void on_splitB_action_selected();
	void on_mergeRGB_action_selected();
	void on_add_action_selected();
	void on_subtract_action_selected();
	void on_multiple_action_selected();
	void on_converetToGrey_action_selected();
	void on_showHist_action_selected();
	void on_avgFilter_action_selected();
	void on_midFilter_action_selected();
	void on_gausFilter_action_selected();
	void on_OTSU_action_selected();
	void on_setSE_action_selected();
	void setSE(std::vector<char>kernal);
	void on_bin_dilate_action_selected();
	void on_bin_erode_action_selected();
	void on_bin_open_action_selected();
	void on_bin_close_action_selected();
	void on_bin_thin_action_selected();
	void showMessage(QString str);
	void changeImageStatus();
	void showadjustHSLWindow();
	void changeImageHSL(double H, double S, double L);
	void showbinarizationWindow();
	void changeBinarization(int minPixel, int maxPixel);
	void on_saveas_action_selected();
	void on_canny_action_selected();
	void on_sobel_action_selected();
	void on_laplace_action_selected();
	void on_nn_mul2_action_selected();
	void on_nn_div2_action_selected();
	void on_linear_mul2_action_selected();
	void on_linear_div2_action_selected();
	void on_nn_rotate45_action_selected();
	void on_houghLine_action_selected();
	void on_houghCircle_action_selected();
	void on_equalizeHist_action_selected();
	void on_linearAdjust_action_selected();
	void on_logAdjust_action_selected();
	void on_powAdjust_action_selected();
	void canny(double lowThreshold, double highThreshold, int aperture_size, int aperture_sigma);
	void useGausFilter(int aperture_size, int aperture_sigma);
	void HoughLine(double line_threshold, double dp, double min_dist, double canny_threshold, double circle_threshold, int minRadius, int maxRadius);
	void HoughCircle(double line_threshold, double dp, double min_dist, double canny_threshold, double circle_threshold, int minRadius, int maxRadius);

};
