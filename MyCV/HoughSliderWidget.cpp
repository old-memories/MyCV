#include "HoughSliderWidget.h"

HoughSliderWidget::HoughSliderWidget(QWidget *parent)
	:
	QDialog(parent)
{
	code = QTextCodec::codecForName("gb18030");
	line_threshold = 200;
	dp = 1;
	min_dist = 200;
	canny_threshold = 140;
	circle_threshold = 140;
	minRadius = 0;
	maxRadius = 0;
	value_line_threshold = new QLabel();
	value_dp = new QLabel();
	value_min_dist = new QLabel();
	value_canny_threshold = new QLabel();
	value_circle_threshold = new QLabel();
	value_minRadius = new QLabel();
	value_maxRadius = new QLabel();
	slider_line_threshold = new QSlider(Qt::Horizontal);
	slider_dp = new QSlider(Qt::Horizontal);
	slider_min_dist = new QSlider(Qt::Horizontal);
	slider_canny_threshold = new QSlider(Qt::Horizontal);
	slider_circle_threshold = new QSlider(Qt::Horizontal);
	slider_minRadius = new QSlider(Qt::Horizontal);
	slider_maxRadius = new QSlider(Qt::Horizontal);

	label_line_threshold = new QLabel(QString(code->toUnicode("Hough线检测阈值")));
	label_dp = new QLabel(QString(code->toUnicode("Hough空间的分辨率")));
	label_min_dist = new QLabel(QString(code->toUnicode("最小圆心距")));
	label_canny_threshold = new QLabel(QString(code->toUnicode("canny上阈值")));
	label_circle_threshold = new QLabel(QString(code->toUnicode("Hough圆检测阈值")));
	label_minRadius = new QLabel(QString(code->toUnicode("最小半径")));
	label_maxRadius = new QLabel(QString(code->toUnicode("最大半径")));
	applyButton = new QPushButton(QString(code->toUnicode("好")));
	cancelButton = new QPushButton(QString(code->toUnicode("取消")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(label_line_threshold, 0, 0, 1, 1);
	gridLayout->addWidget(value_line_threshold, 0, 1, 1, 1);
	gridLayout->addWidget(slider_line_threshold, 0, 2, 1, 4);

	gridLayout->addWidget(label_dp, 1, 0, 1, 1);
	gridLayout->addWidget(value_dp, 1, 1, 1, 1);
	gridLayout->addWidget(slider_dp, 1, 2, 1, 4);

	gridLayout->addWidget(label_min_dist, 2, 0, 1, 1);
	gridLayout->addWidget(value_min_dist, 2, 1, 1, 1);
	gridLayout->addWidget(slider_min_dist, 2, 2, 1, 4);


	gridLayout->addWidget(label_canny_threshold, 3, 0, 1, 1);
	gridLayout->addWidget(value_canny_threshold, 3, 1, 1, 1);
	gridLayout->addWidget(slider_canny_threshold, 3, 2, 1, 4);

	gridLayout->addWidget(label_circle_threshold, 4, 0, 1, 1);
	gridLayout->addWidget(value_circle_threshold, 4, 1, 1, 1);
	gridLayout->addWidget(slider_circle_threshold, 4, 2, 1, 4);

	gridLayout->addWidget(label_minRadius, 5, 0, 1, 1);
	gridLayout->addWidget(value_minRadius, 5, 1, 1, 1);
	gridLayout->addWidget(slider_minRadius, 5, 2, 1, 4);
	
	gridLayout->addWidget(label_maxRadius, 6, 0, 1, 1);
	gridLayout->addWidget(value_maxRadius, 6, 1, 1, 1);
	gridLayout->addWidget(slider_maxRadius, 6, 2, 1, 4);

	gridLayout->addWidget(applyButton, 7, 0, 1, 2);
	gridLayout->addWidget(cancelButton, 7, 2, 1, 2);


	this->setLayout(gridLayout);


	connect(slider_line_threshold, SIGNAL(valueChanged(int)), this, SLOT(setValueLineThreshold(int)));
	connect(slider_dp, SIGNAL(valueChanged(int)), this, SLOT(setValueDp(int)));
	connect(slider_min_dist, SIGNAL(valueChanged(int)), this, SLOT(setValueCannyThreshold(int)));
	connect(slider_canny_threshold, SIGNAL(valueChanged(int)), this, SLOT(setValueCircleThreshold(int)));
	connect(slider_circle_threshold, SIGNAL(valueChanged(int)), this, SLOT(setValueMinDist(int)));
	connect(slider_minRadius, SIGNAL(valueChanged(int)), this, SLOT(setValueMinRadius(int)));
	connect(slider_maxRadius, SIGNAL(valueChanged(int)), this, SLOT(setValueMaxRadius(int)));

}

void HoughSliderWidget::setValueLineThreshold(int value) {
	value_line_threshold->setText(QString::number(value));
}
void HoughSliderWidget::setValueDp(int value) {
	value_dp->setText(QString::number(value));
}
void HoughSliderWidget::setValueCannyThreshold(int value) {
	value_min_dist->setText(QString::number(value));
}

void HoughSliderWidget::setValueCircleThreshold(int value) {
	value_canny_threshold->setText(QString::number(value));
}

void HoughSliderWidget::setValueMinDist(int value) {
	value_circle_threshold->setText(QString::number(value));
}
void HoughSliderWidget::setValueMinRadius(int value) {
	value_minRadius->setText(QString::number(value));
}
void HoughSliderWidget::setValueMaxRadius(int value) {
	value_maxRadius->setText(QString::number(value));
}
void HoughSliderWidget::initHough(double _line_threshold, double _dp, double _min_dist, double _canny_threshold, double _circle_threshold, int _minRadius, int _maxRadius ){
	


	line_threshold = _line_threshold;
	dp = _dp;
	min_dist = _min_dist;
	canny_threshold = _canny_threshold;
	circle_threshold = _circle_threshold;
	minRadius = _minRadius;
	maxRadius = _maxRadius;

	slider_line_threshold->setMinimum(0);
	slider_line_threshold->setMaximum(800);

	slider_dp->setMinimum(-4);
	slider_dp->setMaximum(4);

	slider_min_dist->setMinimum(0);
	slider_min_dist->setMaximum(100);


	slider_canny_threshold->setMinimum(0);
	slider_canny_threshold->setMaximum(255);

	slider_circle_threshold->setMinimum(0);
	slider_circle_threshold->setMaximum(800);

	slider_minRadius->setMinimum(-10);
	slider_minRadius->setMaximum(10);

	slider_maxRadius->setMinimum(-10);
	slider_maxRadius->setMaximum(10);

	slider_line_threshold->setValue(line_threshold);
	slider_dp->setValue(dp);
	slider_min_dist->setValue(min_dist);
	slider_canny_threshold->setValue(canny_threshold);
	slider_circle_threshold->setValue(circle_threshold);
	slider_minRadius->setValue(minRadius);
	slider_maxRadius->setValue(maxRadius);

	value_line_threshold->setText(QString::number(line_threshold));
	value_dp->setText(QString::number(dp));
	value_min_dist->setText(QString::number(min_dist));
	value_canny_threshold->setText(QString::number(canny_threshold));
	value_circle_threshold->setText(QString::number(circle_threshold));
	value_minRadius->setText(QString::number(minRadius));
	value_maxRadius->setText(QString::number(maxRadius));
}
void HoughSliderWidget::on_clicked_applyButton() {
	double l = (double)(slider_line_threshold->value());
	double d = (double)(slider_dp->value());
	d = d > 0 ? d : (d < 0 ? -1.0 / d : 1);
	double md = (double)(slider_min_dist->value());
	double ca = (double)(slider_canny_threshold->value());
	double c = (double)(slider_circle_threshold->value());
	int minr = slider_minRadius->value();
	int maxr = slider_maxRadius->value();
	emit applyHough(l, d, md, ca,c,minr,maxr);
	//this->close();
}
void HoughSliderWidget::on_clicked_cancelButton() {
	this->close();
}



