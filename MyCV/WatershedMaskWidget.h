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
	void mousePressEvent(QMouseEvent *e);       //--鼠标按下事件  
	void mouseMoveEvent(QMouseEvent *e);    //--鼠标移动事件  
	void mouseReleaseEvent(QMouseEvent *e); //--鼠标释放（松开）事件  
	void mouseDoubleClickEvent(QMouseEvent *e); //--鼠标双击事件

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


