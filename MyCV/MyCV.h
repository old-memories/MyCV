#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"
#include "HSLSliderWidget.h"
#include "ImageShowLabel.h"
#include "BinarizationSliderWidget.h"
#include "CannySliderWidget.h"
#include "GausFilterSliderWidget.h"

class MyCV : public QMainWindow
{
	Q_OBJECT

public:
	MyCV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCVClass ui;
	QTextCodec *code;
	ImageShowLabel *imageShowLabel;
	HSLSliderWidget *adjustHSLWindow;
	BinarizationSliderWidget *binarizationWindow;
	GausFilterSliderWidget *gausFilterWindow;
	CannySliderWidget *cannyWindow;
	QMenu* file_menu;
	QMenu* edit_menu;
	cv::Mat src_image;
	void setEnable_when_displayMat();
	enum ImageStatus {NO_IMAGE,IMAGE_REMAINED,IMAGE_CHANGED} imageStatus;
private slots:
	void on_open_action_selected();
	void on_splitR_action_selected();
	void on_splitG_action_selected();
	void on_splitB_action_selected();
	void on_mergeRGB_action_selected();
	void on_add_action_selected();
	void on_subtract_action_selected();
	void on_multiple_action_selected();
	void on_converetToGrey_action_selected();
	void on_avgFilter_action_selected();
	void on_midFilter_action_selected();
	void on_gausFilter_action_selected();
	void on_OTSU_action_selected();
	void showMessage(QString str);
	void changeImageStatus();
	void showadjustHSLWindow();
	void changeImageHSL(double H, double S, double L);
	void showbinarizationWindow();
	void changeBinarization(int minPixel, int maxPixel);
	void on_saveas_action_selected();
	void on_canny_action_selected();
	void canny(double lowThreshold, double highThreshold, int aperture_size, int aperture_sigma);
	void useGausFilter(int aperture_size, int aperture_sigma);
};
