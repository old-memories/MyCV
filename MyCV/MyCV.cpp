#include "MyCV.h"

MyCV::MyCV(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	resize(2000, 1500);   //设置主窗体大小  
	setWindowTitle("My openCV");  //设置主窗体标签 
	/*
	QWidget*  imgWindow = new  QWidget(this, Qt::Window);
	imgWindow->resize(600, 400);
	imgWindow->setWindowTitle("img");
	imgWindow->show();
	*/
	code = QTextCodec::codecForName("gb18030");
	imageShowLabel = new ImageShowLabel(centralWidget());
	imageShowLabel->setGeometry(QRect(int(this->width()*0.2),0, 0, 0));
	imageShowLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观
	connect(imageShowLabel, SIGNAL(showRGB(QString)), this, SLOT(showMessage(QString)));
    file_menu = new QMenu(code->toUnicode("文件"));
	QAction* action_open = new QAction(code->toUnicode("打开文件"));
	file_menu->addAction(action_open);
	menuBar()->addMenu(file_menu);
	connect(action_open, SIGNAL(triggered(bool)), this, SLOT(on_DisplayMat_action_selected()));
	
}


void MyCV::showMessage(QString str) {
	statusBar()->showMessage(str);
}


void MyCV::on_DisplayMat_button_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	imageShowLabel->image = cv::imread(name);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!imageShowLabel->image.data)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Image Data Is Null"));
		msgBox.exec();
	}
	else {
		imageShowLabel->DisplayMat(imageShowLabel->image);
	}
}

void MyCV::on_DisplayMat_action_selected()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Image"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	imageShowLabel->image = cv::imread(name);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!imageShowLabel->image.data)
	{
		QMessageBox msgBox;
		msgBox.setText(tr("Image Data Is Null"));
		msgBox.exec();
	}
	else {
		imageShowLabel->DisplayMat(imageShowLabel->image);
		this->setWindowTitle(filename + QString(" - My openCV"));
	}
}