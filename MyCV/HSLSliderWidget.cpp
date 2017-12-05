#include "HSLSliderWidget.h"

HSLSliderWidget::HSLSliderWidget(QWidget *parent)
:
QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	H = 0;
	S = 0;
	L = 0;
	value_hue = new QLabel();
	value_satuation = new QLabel();
	value_lightness = new QLabel();
	slider_hue = new QSlider(Qt::Horizontal);
	slider_satuation = new QSlider(Qt::Horizontal);
	slider_lightness = new QSlider(Qt::Horizontal);
	label_hue = new QLabel(QString(code->toUnicode("色相")));
	label_satuation = new QLabel(QString(code->toUnicode("饱和度")));
	label_lightness = new QLabel(QString(code->toUnicode("亮度")));
	applyButton = new QPushButton(QString(code->toUnicode("好")));
	cancelButton= new QPushButton(QString(code->toUnicode("取消")));
	undoButton = new QPushButton(QString(code->toUnicode("还原")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));
	connect(undoButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_undoButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(label_hue, 0, 0,1,1);
	gridLayout->addWidget(value_hue, 0, 1,1,1);
	gridLayout->addWidget(slider_hue, 0, 2,1,4);

	gridLayout->addWidget(label_satuation, 1, 0,1,1);
	gridLayout->addWidget(value_satuation, 1, 1,1,1);
	gridLayout->addWidget(slider_satuation, 1, 2,1,4);

	gridLayout->addWidget(label_lightness, 2, 0,1,1);
	gridLayout->addWidget(value_lightness, 2, 1,1,1);
	gridLayout->addWidget(slider_lightness, 2, 2,1,4);

	gridLayout->addWidget(applyButton, 3, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 3, 2, 1, 2);
	gridLayout->addWidget(undoButton, 3, 4, 1, 2);


	this->setLayout(gridLayout);
	
	
	connect(slider_hue, SIGNAL(valueChanged(int)), this, SLOT(setValueHueLabel(int)));
	connect(slider_satuation, SIGNAL(valueChanged(int)), this, SLOT(setValueSatuationLabel(int)));
	connect(slider_lightness, SIGNAL(valueChanged(int)), this, SLOT(setValueLightness(int)));
}

void HSLSliderWidget::setValueHueLabel(int value) {
	value_hue->setText(QString::number(value));
}
void HSLSliderWidget::setValueSatuationLabel(int value) {
	value_satuation->setText(QString::number(value));
}
void HSLSliderWidget::setValueLightness(int value) {
	value_lightness->setText(QString::number(value));
}

void HSLSliderWidget::initHSL(double init_H, double init_S, double init_L) {
	int int_H = (int)(init_H*100.0);
	int int_S = (int)(init_S*100.0);
	int int_L = (int)(init_L*100.0);
	H = int_H;
	S = int_S;
	L = int_L;
	slider_hue->setMinimum(int_H -20);
	slider_hue->setMaximum(int_H +20);
	slider_satuation->setMinimum(int_S -10);
	slider_satuation->setMaximum(int_S +10);
	slider_lightness->setMinimum(int_L-10);
	slider_lightness->setMaximum(int_L+10);
	slider_hue->setValue(int_H);
	slider_satuation->setValue(int_S);
	slider_lightness->setValue(int_L);
	value_hue->setText(QString::number(int_H));
	value_satuation->setText(QString::number(int_S));
	value_lightness->setText(QString::number(int_L));
}
void HSLSliderWidget::on_clicked_applyButton() {
	double double_H = (double)(slider_hue->value()) / 100.0;
	double double_S = (double)(slider_satuation->value()) / 100.0;
	double double_L = (double)(slider_lightness->value()) / 100.0;
	emit applyHSL(double_H, double_S, double_L);
	//this->close();
}
void HSLSliderWidget::on_clicked_cancelButton() {
	this->close();
}
void HSLSliderWidget::on_clicked_undoButton() {
	slider_hue->setValue(H);
	slider_satuation->setValue(S);
	slider_lightness->setValue(L);
	value_hue->setText(QString::number(H));
	value_satuation->setText(QString::number(S));
	value_lightness->setText(QString::number(L));
	//this->close();
}


