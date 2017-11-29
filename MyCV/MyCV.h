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
	QLabel *statusLabel;                //---显示鼠标移动时的实时位置   
	QLabel *mousePointLabel;        //---显示鼠标位置
private slots:
	void on_DisplayMat_button_clicked();
	void on_DisplayMat_action_selected();
	void showMessage(QString str);
};
