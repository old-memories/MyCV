#include "ImageShowLabel.h"



ImageShowLabel::ImageShowLabel(QWidget *parent)
	: QLabel(parent)
{

	code = QTextCodec::codecForName("gb18030");
	setMouseTracking(true);
}


void ImageShowLabel::displayMat(cv::Mat img) {
	image = img.clone();
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
	else 
		return;
	
	
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
	std::vector<unsigned int> rgb;
	int channels = myCVlib::getRGBByPoint(image, x, y, rgb);
	if (rgb.size() == 3) {
		str =
			code->toUnicode("���꣺") +
			"(" + QString::number(x) + ", " + QString::number(y) + ")" +
			code->toUnicode("  ��ͨ��ֵ��") +
			"r=" + QString::number(rgb[2]) + " " +
			"g=" + QString::number(rgb[1]) + " " +
			"b=" + QString::number(rgb[0]) + " ";
	}
	else if (rgb.size() == 1) {
		str =
			code->toUnicode("���꣺") +
			"(" + QString::number(x) + ", " + QString::number(y) + ")" +
			code->toUnicode("  ��ͨ��ֵ��") +
			"grey=" + QString::number(rgb[0]) + " ";
	}
	else {
		str =
			code->toUnicode("���꣺") +
			"(" + QString::number(x) + ", " + QString::number(y) + ")";
	}
	
	return str;
}