#include "CannySliderWidget.h"

CannySliderWidget::CannySliderWidget(QWidget *parent)
	:
	QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	lowThreshold = 0;
	highThreshold = 255;
	aperture_size = 7;
	aperture_sigma = 1;
	value_lowThreshold = new QLabel();
	value_highThreshold = new QLabel();
	value_aperture_size = new QLabel();
	value_aperture_sigma = new QLabel();
	slider_lowThreshold = new QSlider(Qt::Horizontal);
	slider_highThreshold = new QSlider(Qt::Horizontal);
	slider_aperture_size = new QSlider(Qt::Horizontal);
	slider_aperture_sigma = new QSlider(Qt::Horizontal);

	label_lowThreshold = new QLabel(QString(code->toUnicode("下阈值")));
	label_highThreshold = new QLabel(QString(code->toUnicode("上阈值")));
	label_aperture_size = new QLabel(QString(code->toUnicode("卷积核大小")));
	label_aperture_sigma = new QLabel(QString(code->toUnicode("卷积核标准差")));
	applyButton = new QPushButton(QString(code->toUnicode("好")));
	cancelButton = new QPushButton(QString(code->toUnicode("取消")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(label_lowThreshold, 0, 0, 1, 1);
	gridLayout->addWidget(value_lowThreshold, 0, 1, 1, 1);
	gridLayout->addWidget(slider_lowThreshold, 0, 2, 1, 4);

	gridLayout->addWidget(label_highThreshold, 1, 0, 1, 1);
	gridLayout->addWidget(value_highThreshold, 1, 1, 1, 1);
	gridLayout->addWidget(slider_highThreshold, 1, 2, 1, 4);

	gridLayout->addWidget(label_aperture_size, 2, 0, 1, 1);
	gridLayout->addWidget(value_aperture_size, 2, 1, 1, 1);
	gridLayout->addWidget(slider_aperture_size, 2, 2, 1, 4);


	gridLayout->addWidget(label_aperture_sigma, 3, 0, 1, 1);
	gridLayout->addWidget(value_aperture_sigma, 3, 1, 1, 1);
	gridLayout->addWidget(slider_aperture_sigma, 3, 2, 1, 4);

	gridLayout->addWidget(applyButton, 4, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 4, 2, 1, 2);


	this->setLayout(gridLayout);


	connect(slider_lowThreshold, SIGNAL(valueChanged(int)), this, SLOT(setValueLowThreshold(int)));
	connect(slider_highThreshold, SIGNAL(valueChanged(int)), this, SLOT(setValueHighThreshold(int)));
	connect(slider_aperture_size, SIGNAL(valueChanged(int)), this, SLOT(setValueAperture_size(int)));
	connect(slider_aperture_sigma, SIGNAL(valueChanged(int)), this, SLOT(setValueAperture_sigma(int)));

}

void CannySliderWidget::setValueLowThreshold(int value) {
	value_lowThreshold->setText(QString::number(value));
}
void CannySliderWidget::setValueHighThreshold(int value) {
	value_highThreshold->setText(QString::number(value));
}
void CannySliderWidget::setValueAperture_size(int value) {
	value_aperture_size->setText(QString::number(value));
}

void CannySliderWidget::setValueAperture_sigma(int value) {
	value_aperture_sigma->setText(QString::number(value));
}

void CannySliderWidget::initCanny(double init_lowThreshold, double init_highThreshold, int init_Aperture_size, int init_Aperture_sigma) {
	int int_lowThreshold = (int)(init_lowThreshold);
	int int_highThreshold = (int)(init_highThreshold);
	int int_Aperture_size = (int)(init_Aperture_size);
	int int_Aperture_sigma = (int)(init_Aperture_sigma);

	
	lowThreshold = int_lowThreshold;
	highThreshold = int_highThreshold;
	aperture_size = int_Aperture_size;
	aperture_sigma = int_Aperture_sigma;
	slider_lowThreshold->setMinimum(0);
	slider_lowThreshold->setMaximum(255);
	slider_highThreshold->setMinimum(0);
	slider_highThreshold->setMaximum(255);
	slider_aperture_size->setMinimum(3);
	slider_aperture_size->setMaximum(10);
	slider_aperture_sigma->setMinimum(1);
	slider_aperture_sigma->setMaximum(10);
	slider_lowThreshold->setValue(lowThreshold);
	slider_highThreshold->setValue(highThreshold);
	slider_aperture_size->setValue(aperture_size);
	slider_aperture_sigma->setValue(aperture_sigma);
	value_lowThreshold->setText(QString::number(lowThreshold));
	value_highThreshold->setText(QString::number(highThreshold));
	value_aperture_size->setText(QString::number(aperture_size));
	value_aperture_sigma->setText(QString::number(aperture_sigma));
}
void CannySliderWidget::on_clicked_applyButton() {
	double l = (double)(slider_lowThreshold->value());
	double h = (double)(slider_highThreshold->value());
	int size = slider_aperture_size->value();
	int sigma = slider_aperture_sigma->value();
	emit applyCanny(l, h, size,sigma);
	//this->close();
}
void CannySliderWidget::on_clicked_cancelButton() {
	this->close();
}



