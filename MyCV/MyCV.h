#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MyCV.h"

class MyCV : public QMainWindow
{
	Q_OBJECT

public:
	MyCV(QWidget *parent = Q_NULLPTR);

private:
	Ui::MyCVClass ui;
};
