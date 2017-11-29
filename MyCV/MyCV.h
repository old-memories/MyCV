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
private slots:
	void on_DisplayMat_button_clicked();
	void on_DisplayMat_action_selected();
	void showMessage(QString str);
};
