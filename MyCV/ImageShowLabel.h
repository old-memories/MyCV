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
	void mousePressEvent(QMouseEvent *e);       //--��갴���¼�  
	void mouseMoveEvent(QMouseEvent *e);    //--����ƶ��¼�  
	void mouseReleaseEvent(QMouseEvent *e); //--����ͷţ��ɿ����¼�  
	void mouseDoubleClickEvent(QMouseEvent *e); //--���˫���¼�
	cv::Mat image;
signals:
	void showRGB(QString str);
	void imageChanged();
private:
	QTextCodec *code;
	QString ImageShowLabel::on_mouseGetRGB(int x, int y);

};