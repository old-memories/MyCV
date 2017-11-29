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



//--鼠标按下事件  
void ImageShowLabel::ImageShowLabel::mousePressEvent(QMouseEvent *e)
{

	//----QMouseEvent类提供的x()和y()可获取鼠标相对窗口的位置  
	//QString str = "(" + QString::number(e->x()) + ", " + QString::number(e->y()) + ")";

	//---点击左键  
	if (Qt::LeftButton == e->button())
	{

	}
	//---点击左键  
	if (Qt::RightButton == e->button())
	{
	}
	//---点击左键  
	if (Qt::MidButton == e->button())
	{
	}
}

//---鼠标释放（松开）事件  
void ImageShowLabel::ImageShowLabel::mouseReleaseEvent(QMouseEvent *e)
{

}

//--s鼠标双击事件  
void ImageShowLabel::ImageShowLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
}

//--鼠标移动事件  
void ImageShowLabel::ImageShowLabel::mouseMoveEvent(QMouseEvent *e)
{
	QString str = on_mouseGetRGB(e->x(), e->y());
	emit showRGB(str);
}


QString ImageShowLabel::on_mouseGetRGB(int x, int y)
{
	QString str;
	if (!image.data) {
		str = code->toUnicode("请打开图片");
		return str;
	}
	cv::Point p(x, y);
	unsigned int b = image.at<cv::Vec3b>(p)[0];
	unsigned int g = image.at<cv::Vec3b>(p)[1];
	unsigned int r = image.at<cv::Vec3b>(p)[2];

	str =
		code->toUnicode("坐标：")+
		"("+ QString::number(x) +", "+ QString::number(y) +")"+
		code->toUnicode("  三通道值：") +
		"r=" + QString::number(r) + " " +
		"g=" + QString::number(g) + " " +
		"b=" + QString::number(b) + " ";
	return str;
}