#pragma once
#include <QtWidgets/QMainWindow>
#include <myCVlib.h>
#include "ui_MyCV.h"
#include <QFileDialog>  
#include <QImage>  
#include <QLabel>
#include<QPushButton>
#include <QTextCodec>  
#include <QLayout>  
#include <QMessageBox>
#include <QStatusbar>
#include <QMouseEvent>  
#include <opencv.hpp>



class  ImgLabel : public QLabel
{
	Q_OBJECT

public:
	ImgLabel(QWidget *parent = Q_NULLPTR);
	void displayMat(cv::Mat img);
	void mousePressEvent(QMouseEvent *e);       //--��갴���¼�  
	void mouseMoveEvent(QMouseEvent *e);    //--����ƶ��¼�  
	void mouseReleaseEvent(QMouseEvent *e); //--����ͷţ��ɿ����¼�  
	void mouseDoubleClickEvent(QMouseEvent *e); //--���˫���¼�

	cv::Mat srcImg;
	cv::Mat maskImg;
	cv::Point clickPoint;
signals:
	//void showRGB(QString str);
	//void imageChanged();
	//QString WatershedMaskWidget::on_mouseGetRGB(int x, int y);

};

class  WatershedMaskWidget : public QDialog
{
	Q_OBJECT

public:
	WatershedMaskWidget(QWidget *parent = Q_NULLPTR);
	void setImg(cv::Mat src);
	ImgLabel* imgLabel;
	QPushButton* applyButton;
	QPushButton* cancelButton;
	QGridLayout *gridLayout;
	public slots:
	void on_clicked_applyButton();
	void on_clicked_cancelButton();
	
signals:
	void sendWatershed(cv::Mat);
	//void showRGB(QString str);
	//void imageChanged();
private:
	QTextCodec *code;
	//QString WatershedMaskWidget::on_mouseGetRGB(int x, int y);

};


