#include "MyCV.h"

MyCV::MyCV(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	/*
	QWidget*  imgWindow = new  QWidget(this, Qt::Window);
	imgWindow->resize(600, 400);
	imgWindow->setWindowTitle("img");
	imgWindow->show();
	*/
	code = QTextCodec::codecForName("gb18030");
	imageShowLabel = new ImageShowLabel(this);
	imageShowLabel->setGeometry(QRect(50, 50, 0, 0));
	imageShowLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观
																   //setCentralWidget(imageShowLabel);
	connect(imageShowLabel, SIGNAL(showRGB(QString)), this, SLOT(showMessage(QString)));
	pMenuBar = ui.menuBar;
	QMenu* file_menu = new QMenu(code->toUnicode("文件"));
	QAction* action_open = new QAction(code->toUnicode("打开文件"));
	file_menu->addAction(action_open);
	pMenuBar->addMenu(file_menu);
	connect(action_open, SIGNAL(triggered(bool)), this, SLOT(on_DisplayMat_action_selected()));
	//showImageButton = new QPushButton(this);
	//showImageButton->setGeometry(QRect(50, 50, 200, 80));
	//showImageButton->setText(code->toUnicode("加载图片"));
	//connect(showImageButton, SIGNAL(clicked(bool)), this, SLOT(on_DisplayMat_button_clicked()));
	resize(2000, 1500);   //设置主窗体大小  
	setWindowTitle("Qt Test");  //设置主窗体标签 
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
	}
}