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
class  CannySliderWidget : public QDialog
{
	Q_OBJECT

public:
	CannySliderWidget(QWidget *parent = Q_NULLPTR);
	void initCanny(double, double, int, int);
signals:
	void applyCanny(double, double, int, int);
	public slots:
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
	void setValueLowThreshold(int value);
	void setValueHighThreshold(int value);
	void setValueAperture_size(int value);
	void setValueAperture_sigma(int value);
private:
	int lowThreshold;
	int highThreshold;
	int aperture_size;
	int aperture_sigma;
	QTextCodec *code;
	QLabel* value_lowThreshold;
	QLabel* value_highThreshold;
	QLabel* value_aperture_size;
	QLabel* value_aperture_sigma;
	QSlider* slider_lowThreshold;
	QSlider* slider_highThreshold;
	QSlider* slider_aperture_size;
	QSlider* slider_aperture_sigma;
	QLabel* label_lowThreshold;
	QLabel* label_highThreshold;
	QLabel* label_aperture_size;
	QLabel* label_aperture_sigma;
	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
};