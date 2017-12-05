#include "BinarizationSliderWidget.h"

BinarizationSliderWidget::BinarizationSliderWidget(QWidget *parent)
	:
	QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	minPixel = 0;
	maxPixel = 0;
	value_min = new QLabel();
	value_max = new QLabel();
	slider_min = new QSlider(Qt::Horizontal);
	slider_max = new QSlider(Qt::Horizontal);
	label_min = new QLabel(QString(code->toUnicode("下阈值")));
	label_max = new QLabel(QString(code->toUnicode("上阈值")));
	slider_min->setMinimum(0);
	slider_min->setMaximum(255);
	slider_max->setMinimum(0);
	slider_max->setMaximum(255);
	slider_min->setValue(50);
	slider_max->setValue(200);
	value_min->setText(QString::number(50));
	value_max->setText(QString::number(200));
	applyButton = new QPushButton(QString(code->toUnicode("好")));
	cancelButton = new QPushButton(QString(code->toUnicode("取消")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(label_max, 0, 0, 1, 1);
	gridLayout->addWidget(value_max, 0, 1, 1, 1);
	gridLayout->addWidget(slider_max, 0, 2, 1, 4);

	gridLayout->addWidget(label_min, 1, 0, 1, 1);
	gridLayout->addWidget(value_min, 1, 1, 1, 1);
	gridLayout->addWidget(slider_min, 1, 2, 1, 4);


	gridLayout->addWidget(applyButton, 3, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 3, 2, 1, 2);


	this->setLayout(gridLayout);


	connect(slider_min, SIGNAL(valueChanged(int)), this, SLOT(setValueMinLabel(int)));
	connect(slider_max, SIGNAL(valueChanged(int)), this, SLOT(setValueMaxLabel(int)));
}

void BinarizationSliderWidget::setValueMinLabel(int value) {
	value_min->setText(QString::number(value));
}
void BinarizationSliderWidget::setValueMaxLabel(int value) {
	value_max->setText(QString::number(value));
}



void BinarizationSliderWidget::on_clicked_applyButton() {
	minPixel = slider_min->value();
	maxPixel = slider_max->value();
	emit applyBinarization(minPixel, maxPixel);
	//this->close();
}
void BinarizationSliderWidget::on_clicked_cancelButton() {
	this->close();
}



