#include "ImageShowLabel.h"



ImageShowLabel::ImageShowLabel(QWidget *parent)
	: QLabel(parent)
{

	code = QTextCodec::codecForName("gb18030");
	setMouseTracking(true);
}


void ImageShowLabel::DisplayMat(cv::Mat image) {
	cv::Mat rgb;
	cvtColor(image, rgb, CV_BGR2RGB);
	QImage Qimg = QImage((const unsigned char*)(rgb.data), rgb.cols, rgb.rows, rgb.cols*rgb.channels(), QImage::Format_RGB888);
	QPixmap qPixap = QPixmap::fromImage(Qimg);
	resize(qPixap.size());
	//qPixap.scaled(labelimage->size(), Qt::KeepAspectRatio);
	setPixmap(qPixap);
	//labelimage->resize(labelimage->pixmap()->size());
}



//--��갴���¼�  
void ImageShowLabel::ImageShowLabel::mousePressEvent(QMouseEvent *e)
{

	//----QMouseEvent���ṩ��x()��y()�ɻ�ȡ�����Դ��ڵ�λ��  
	//QString str = "(" + QString::number(e->x()) + ", " + QString::number(e->y()) + ")";

	//---������  
	if (Qt::LeftButton == e->button())
	{

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
void ImageShowLabel::ImageShowLabel::mouseReleaseEvent(QMouseEvent *e)
{

}

//--s���˫���¼�  
void ImageShowLabel::ImageShowLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
}

//--����ƶ��¼�  
void ImageShowLabel::ImageShowLabel::mouseMoveEvent(QMouseEvent *e)
{
	QString str = on_mouseGetRGB(e->x(), e->y());
	emit showRGB(str);
}


QString ImageShowLabel::on_mouseGetRGB(int x, int y)
{
	QString str;
	if (!image.data) {
		str = code->toUnicode("���ͼƬ");
		return str;
	}
	cv::Point p(x, y);
	unsigned int b = image.at<cv::Vec3b>(p)[0];
	unsigned int g = image.at<cv::Vec3b>(p)[1];
	unsigned int r = image.at<cv::Vec3b>(p)[2];

	str =
		code->toUnicode("���꣺")+
		"("+ QString::number(x) +", "+ QString::number(y) +")"+
		code->toUnicode("  ��ͨ��ֵ��") +
		"r=" + QString::number(r) + " " +
		"g=" + QString::number(g) + " " +
		"b=" + QString::number(b) + " ";
	return str;
}