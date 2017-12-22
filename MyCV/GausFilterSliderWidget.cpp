#include "GausFilterSliderWidget.h"

GausFilterSliderWidget::GausFilterSliderWidget(QWidget *parent)
	:
	QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	aperture_size = 7;
	aperture_sigma = 1;
	value_aperture_size = new QLabel();
	value_aperture_sigma = new QLabel();
	slider_aperture_size = new QSlider(Qt::Horizontal);
	slider_aperture_sigma = new QSlider(Qt::Horizontal);
	label_aperture_size = new QLabel(QString(code->toUnicode("卷积核大小")));
	label_aperture_sigma = new QLabel(QString(code->toUnicode("卷积核标准差")));
	slider_aperture_size->setMinimum(3);
	slider_aperture_size->setMaximum(10);
	slider_aperture_sigma->setMinimum(1);
	slider_aperture_sigma->setMaximum(10);
	slider_aperture_size->setValue(7);
	slider_aperture_sigma->setValue(1);
	value_aperture_size->setText(QString::number(7));
	value_aperture_sigma->setText(QString::number(1));
	applyButton = new QPushButton(QString(code->toUnicode("好")));
	cancelButton = new QPushButton(QString(code->toUnicode("取消")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(label_aperture_size, 0, 0, 1, 1);
	gridLayout->addWidget(value_aperture_size, 0, 1, 1, 1);
	gridLayout->addWidget(slider_aperture_size, 0, 2, 1, 4);

	gridLayout->addWidget(label_aperture_sigma, 1, 0, 1, 1);
	gridLayout->addWidget(value_aperture_sigma, 1, 1, 1, 1);
	gridLayout->addWidget(slider_aperture_sigma, 1, 2, 1, 4);


	gridLayout->addWidget(applyButton, 3, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 3, 2, 1, 2);


	this->setLayout(gridLayout);


	connect(slider_aperture_size, SIGNAL(valueChanged(int)), this, SLOT(setAperture_sizeLabel(int)));
	connect(slider_aperture_sigma, SIGNAL(valueChanged(int)), this, SLOT(setAperture_sigmaLabel(int)));
}

void GausFilterSliderWidget::setAperture_sizeLabel(int value) {
	value_aperture_size->setText(QString::number(value));
}
void GausFilterSliderWidget::setAperture_sigmaLabel(int value) {
	value_aperture_sigma->setText(QString::number(value));
}



void GausFilterSliderWidget::on_clicked_applyButton() {
	aperture_size = slider_aperture_size->value();
	aperture_sigma = slider_aperture_sigma->value();
	emit applyGausFilter(aperture_size, aperture_sigma);
	//this->close();
}
void GausFilterSliderWidget::on_clicked_cancelButton() {
	this->close();
}



