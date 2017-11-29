#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"
#include "ImageShowLabel.h"

class MyCV : public QMainWindow
{
	Q_OBJECT

public:
	MyCV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCVClass ui;
	QTextCodec *code;
	ImageShowLabel *imageShowLabel;
	QMenuBar* pMenuBar;
	//QPushButton *showImageButton;
	QLabel *statusLabel;                //---��ʾ����ƶ�ʱ��ʵʱλ��   
	QLabel *mousePointLabel;        //---��ʾ���λ��
private slots:
	void on_DisplayMat_button_clicked();
	void on_DisplayMat_action_selected();
	void showMessage(QString str);
};
