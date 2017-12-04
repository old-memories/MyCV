#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"
#include "ThreeSliderWidget.h"
#include "ImageShowLabel.h"

class MyCV : public QMainWindow
{
	Q_OBJECT

public:
	MyCV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCVClass ui;
	QTextCodec *code;
	ImageShowLabel *imageShowLabel;
	ThreeSliderWidget *adjustHSLWindow;
	QMenu* file_menu;
	QMenu* edit_menu;
	cv::Mat src_image;
	void setEnable_when_displayMat();
	enum ImageStatus {NO_IMAGE,IMAGE_REMAINED,IMAGE_CHANGED} imageStatus;
private slots:
	void on_displayMat_action_selected();
	void on_splitR_action_selected();
	void on_splitG_action_selected();
	void on_splitB_action_selected();
	void on_mergeRGB_action_selected();
	void on_converetToGrey_action_selected();
	void on_OTSU_action_selected();
	void showMessage(QString str);
	void changeImageStatus();
	void showadjustHSLWindow();
	void changeImageHSL(double H, double S, double L);


};
