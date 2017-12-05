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
class  HSLSliderWidget : public QDialog
{
	Q_OBJECT

public:
	HSLSliderWidget(QWidget *parent = Q_NULLPTR );
	void initHSL(double init_H, double init_S, double init_L);
signals:
	void applyHSL(double, double, double);
public slots:
void on_clicked_applyButton();
void on_clicked_cancelButton();
void on_clicked_undoButton();
void setValueHueLabel(int value);
void setValueSatuationLabel(int value);
void setValueLightness(int value);
private:
	int H;
	int S;
	int L;
	QTextCodec *code;
	QLabel* value_hue;
	QLabel* value_satuation;
	QLabel* value_lightness;
	QSlider* slider_hue;
	QSlider* slider_satuation;
	QSlider* slider_lightness;
	QLabel* label_hue;
	QLabel* label_satuation;
	QLabel* label_lightness;
	QPushButton* applyButton;
	QPushButton* cancelButton;
	QPushButton* undoButton;
	QGridLayout *gridLayout;
};