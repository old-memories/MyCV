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
class  GausFilterSliderWidget : public QDialog
{
	Q_OBJECT

public:
	GausFilterSliderWidget(QWidget *parent = Q_NULLPTR);
signals:
	void applyGausFilter(int, int);
	public slots:
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
	void setAperture_sizeLabel(int value);
	void setAperture_sigmaLabel(int value);
private:
	int aperture_size;
	int aperture_sigma;
	QTextCodec *code;
	QLabel* value_aperture_size;
	QLabel* value_aperture_sigma;
	QSlider* slider_aperture_size;
	QSlider* slider_aperture_sigma;
	QLabel* label_aperture_size;
	QLabel* label_aperture_sigma;
	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
};