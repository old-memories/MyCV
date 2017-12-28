#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"
#include <QDialog>
#include <QSlider>
#include <QTextCodec>  
#include <QPushButton>  
#include <QLineEdit>  
#include <QLayout>  
#include <QLabel>  
#include <QTextEdit>  
#include <opencv.hpp>

//void houghCircle(cv::Mat src, cv::Mat &dst, double dp, double min_dist, double canny_threshold, double threshold, int minRadius, int maxRadius);

class  HoughSliderWidget : public QDialog
{
	Q_OBJECT

public:
	HoughSliderWidget(QWidget *parent = Q_NULLPTR);
	void initHough(double, double, double, double, double, int, int);
signals:
	void applyHough(double, double, double,double,double, int, int);
	public slots:
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
	void setValueLineThreshold(int value);
	void setValueDp(int value);
	void setValueCannyThreshold(int value);
	void setValueCircleThreshold(int value);
	void setValueMinDist(int value);
	void setValueMinRadius(int value);
	void setValueMaxRadius(int value);

private:
	double line_threshold;
	double dp;
	double min_dist;
	double canny_threshold;
	double circle_threshold;
	int minRadius;
	int maxRadius;

	QTextCodec *code;

	QLabel* value_line_threshold;
	QLabel* value_dp;
	QLabel* value_min_dist;
	QLabel* value_canny_threshold;
	QLabel* value_circle_threshold;
	QLabel* value_minRadius;
	QLabel* value_maxRadius;

	QSlider* slider_line_threshold;
	QSlider* slider_dp;
	QSlider* slider_min_dist;
	QSlider* slider_canny_threshold;
	QSlider* slider_circle_threshold;
	QSlider* slider_minRadius;
	QSlider* slider_maxRadius;

	
	QLabel* label_line_threshold;
	QLabel* label_dp;
	QLabel* label_min_dist;
	QLabel* label_canny_threshold;
	QLabel* label_circle_threshold;
	QLabel* label_minRadius;
	QLabel* label_maxRadius;

	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
};