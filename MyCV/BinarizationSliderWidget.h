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
class  BinarizationSliderWidget : public QDialog
{
	Q_OBJECT

public:
	BinarizationSliderWidget(QWidget *parent = Q_NULLPTR);
signals:
	void applyBinarization(int, int);
	public slots:
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
	void setValueMinLabel(int value);
	void setValueMaxLabel(int value);
private:
	int minPixel;
	int maxPixel;
	QTextCodec *code;
	QLabel* value_min;
	QLabel* value_max;
	QSlider* slider_min;
	QSlider* slider_max;
	QLabel* label_min;
	QLabel* label_max;
	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
};