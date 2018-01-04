#include "WatershedMaskWidget.h"

ImgLabel::ImgLabel(QWidget *parent)
	: QLabel(parent)
{

}

void ImgLabel::displayMat(cv::Mat img) {
	cv::Mat image = img.clone();
	if (image.channels() == 3) {
		cv::Mat rgb;
		cvtColor(image, rgb, CV_BGR2RGB);
		QImage Qimg = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);
		QPixmap qPixap = QPixmap::fromImage(Qimg);
		resize(qPixap.size());
		//qPixap.scaled(labelimage->size(), Qt::KeepAspectRatio);
		setPixmap(qPixap);
		//labelimage->resize(labelimage->pixmap()->size());
	}
	else if (image.channels() == 1) {
		QImage Qimg = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_Grayscale8);
		QPixmap qPixap = QPixmap::fromImage(Qimg);
		resize(qPixap.size());
		//qPixap.scaled(labelimage->size(), Qt::KeepAspectRatio);
		setPixmap(qPixap);
		//labelimage->resize(labelimage->pixmap()->size());
	}
	//emit imageChanged();



}

//--��갴���¼�  
void ImgLabel::ImgLabel::mousePressEvent(QMouseEvent *e)
{

	//----QMouseEvent���ṩ��x()��y()�ɻ�ȡ�����Դ��ڵ�λ��  
	//QString str = "(" + QString::number(e->x()) + ", " + QString::number(e->y()) + ")";

	//---������  
	if (Qt::LeftButton == e->button())
	{
		clickPoint = cv::Point(e->x(), e->y());
	}
	//---������  
	if (Qt::RightButton == e->button())
	{
	}
	//---������  
	if (Qt::MidButton == e->button())
	{
	}
}

//---����ͷţ��ɿ����¼�  
void ImgLabel::ImgLabel::mouseReleaseEvent(QMouseEvent *e)
{

}

//--s���˫���¼�  
void ImgLabel::ImgLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
}

//--����ƶ��¼�  
void ImgLabel::ImgLabel::mouseMoveEvent(QMouseEvent *e)
{
	cv::Point point(e->x(), e->y());
	line(maskImg, clickPoint, point, cv::Scalar::all(255), 5, 8, 0);
	line(srcImg, clickPoint, point, cv::Scalar::all(255), 5, 8, 0);
	clickPoint = point;
	displayMat(srcImg);
	//QString str = on_mouseGetRGB(e->x(), e->y());
	//emit showRGB(str);
}


WatershedMaskWidget::WatershedMaskWidget(QWidget *parent)
	: QDialog(parent)
{

	imgLabel = new ImgLabel();
	imgLabel->setGeometry(QRect(0, 0, 0, 0));
	imgLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken); //�������
	code = QTextCodec::codecForName("gb18030");
	applyButton = new QPushButton(QString(code->toUnicode("��")));
	cancelButton = new QPushButton(QString(code->toUnicode("ȡ��")));
	connect(applyButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_applyButton()));
	connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(on_clicked_cancelButton()));

	gridLayout = new QGridLayout();

	gridLayout->addWidget(imgLabel, 0, 0, 2, 2);
	gridLayout->addWidget(applyButton, 2, 0, 1, 1);
	gridLayout->addWidget(cancelButton, 2, 1, 1, 1);

	

	


	this->setLayout(gridLayout);

	//setMouseTracking(true);
}

void WatershedMaskWidget::setImg(cv::Mat src) {
	imgLabel->srcImg = src.clone();
	//resize(QSize(src.rows, src.cols));
	imgLabel->maskImg.create(src.size(), CV_8UC1);
	imgLabel->maskImg = cv::Scalar::all(0);
	imgLabel->displayMat(imgLabel->srcImg);
}


void WatershedMaskWidget::on_clicked_applyButton() {
	this->close();
	emit sendWatershed(imgLabel->maskImg);
}
void WatershedMaskWidget::on_clicked_cancelButton() {
	this->close();
}



