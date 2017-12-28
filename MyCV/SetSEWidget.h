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
#include <QPlainTextEdit>
#include <opencv.hpp>
class  SetSEWidget : public QDialog
{
	Q_OBJECT

public:
	SetSEWidget(QWidget *parent = Q_NULLPTR);
signals:
	void applySE(std::vector<char>);
	public slots :
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
private:
	QTextCodec *code;

	//1
	QPlainTextEdit *k0;
	QPlainTextEdit *k1;
	QPlainTextEdit *k2;
	QPlainTextEdit *k3;
	QPlainTextEdit *k4;

	//2
	QPlainTextEdit *k5;
	QPlainTextEdit *k6;
	QPlainTextEdit *k7;
	QPlainTextEdit *k8;
	QPlainTextEdit *k9;


	//3
	QPlainTextEdit *k10;
	QPlainTextEdit *k11;
	QPlainTextEdit *k12;
	QPlainTextEdit *k13;
	QPlainTextEdit *k14;

	//4
	QPlainTextEdit *k15;
	QPlainTextEdit *k16;
	QPlainTextEdit *k17;
	QPlainTextEdit *k18;
	QPlainTextEdit *k19;

	//5
	QPlainTextEdit *k20;
	QPlainTextEdit *k21;
	QPlainTextEdit *k22;
	QPlainTextEdit *k23;
	QPlainTextEdit *k24;

	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
};