#pragma once
#include <QtWidgets/QMainWindow>
#include <myCVlib.h>
#include "ui_MyCV.h"
#include <QFileDialog>  
#include <QImage>  
#include <QLabel>
#include<QPushButton>
#include <QTextCodec>  
#include <QMessageBox>
#include <QStatusbar>
#include <QMouseEvent>  
#include <opencv.hpp>



class  ImageShowLabel : public QLabel
{
	Q_OBJECT

public:
	ImageShowLabel(QWidget *parent = Q_NULLPTR);
	void displayMat(cv::Mat img);
	void mousePressEvent(QMouseEvent *e);       //--鼠标按下事件  
	void mouseMoveEvent(QMouseEvent *e);    //--鼠标移动事件  
	void mouseReleaseEvent(QMouseEvent *e); //--鼠标释放（松开）事件  
	void mouseDoubleClickEvent(QMouseEvent *e); //--鼠标双击事件
	cv::Mat image;
signals:
	void showRGB(QString str);
	void imageChanged();
private:
	QTextCodec *code;
	QString ImageShowLabel::on_mouseGetRGB(int x, int y);

};