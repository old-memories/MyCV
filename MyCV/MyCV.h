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
	QMenu* file_menu;
	QMenu* edit_menu;
	QMenu* splitRGB_menu;
	cv::Mat src_image;
	void setEnable_when_displayMat();
private slots:
	void on_displayMat_action_selected();
	void on_splitR_action_selected();
	void on_splitG_action_selected();
	void on_splitB_action_selected();
	void on_mergeRGB_action_selected();
	void showMessage(QString str);
};
