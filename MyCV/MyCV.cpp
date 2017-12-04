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
	imageStatus = NO_IMAGE;
	imageShowLabel = new ImageShowLabel(centralWidget());
	imageShowLabel->setGeometry(QRect(0, 0, 0, 0));
	imageShowLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观
	connect(imageShowLabel, SIGNAL(showRGB(QString)), this, SLOT(showMessage(QString)));
	connect(imageShowLabel, SIGNAL(imageChanged(void)), this, SLOT(changeImageStatus()));
	adjustHSLWindow = new ThreeSliderWidget(this);
	adjustHSLWindow->resize(600,250);
	adjustHSLWindow->setWindowTitle(code->toUnicode("色相 饱和度 亮度调节"));
	//adjustHSLWindow->show();
	//QMenu
    file_menu = new QMenu(code->toUnicode("文件"));
	edit_menu = new QMenu(code->toUnicode("编辑"));
	menuBar()->addMenu(file_menu);
	menuBar()->addMenu(edit_menu);
	edit_menu->setEnabled(false);


	//QAction
	QAction* action_open = new QAction(QIcon("png/folder_open_icon&32.png"),code->toUnicode("打开文件"));
	file_menu->addAction(action_open);
	ui.mainToolBar->addAction(action_open);
	connect(action_open, SIGNAL(triggered(bool)), this, SLOT(on_displayMat_action_selected()));

	//QAction
	QAction* action_adjustHSL = new QAction(code->toUnicode("色相 饱和度 亮度调节"));
	edit_menu->addAction(action_adjustHSL);
	connect(action_adjustHSL, SIGNAL(triggered(bool)), this, SLOT(showadjustHSLWindow()));
	connect(adjustHSLWindow, SIGNAL(applyHSL(double, double, double)), this, SLOT(changeImageHSL(double,double,double)));

	//QMenu
	QMenu* splitRGB_menu = new QMenu(code->toUnicode("三通道分离"));
	edit_menu->addMenu(splitRGB_menu);
	QAction* action_splitR = new QAction(code->toUnicode("红色"));
	QAction* action_splitG = new QAction(code->toUnicode("绿色"));
	QAction* action_splitB = new QAction(code->toUnicode("蓝色"));
	QAction* action_mergeRGB = new QAction(code->toUnicode("恢复彩色"));
	splitRGB_menu->addAction(action_splitR);
	splitRGB_menu->addAction(action_splitG);
	splitRGB_menu->addAction(action_splitB);
	splitRGB_menu->addAction(action_mergeRGB);
	connect(action_splitR, SIGNAL(triggered(bool)), this, SLOT(on_splitR_action_selected()));
	connect(action_splitG, SIGNAL(triggered(bool)), this, SLOT(on_splitG_action_selected()));
	connect(action_splitB, SIGNAL(triggered(bool)), this, SLOT(on_splitB_action_selected()));
	connect(action_mergeRGB, SIGNAL(triggered(bool)), this, SLOT(on_mergeRGB_action_selected()));
	
	
	//QMenu
	QAction *action_converetToGrey = new QAction(code->toUnicode("转换灰度图"));
	edit_menu->addAction(action_converetToGrey);
	connect(action_converetToGrey, SIGNAL(triggered(bool)), this, SLOT(on_converetToGrey_action_selected()));
	
	
	//QMenu
	QAction *action_OTSU = new QAction(code->toUnicode("OTSU二值化"));
	edit_menu->addAction(action_OTSU);
	connect(action_OTSU, SIGNAL(triggered(bool)), this, SLOT(on_OTSU_action_selected()));
}


void MyCV::setEnable_when_displayMat() {
	edit_menu->setEnabled(true);
}


void MyCV::showMessage(QString str) {
	statusBar()->showMessage(str);
}

void MyCV::changeImageStatus() {
	if (imageStatus == NO_IMAGE) {
		imageStatus = IMAGE_REMAINED;
		return;
	}
	if (imageStatus == IMAGE_REMAINED) {
		imageStatus = IMAGE_CHANGED;
		QString newWindowTitle(this->windowTitle() + QString(code->toUnicode("（文件已改变）")));
		this->setWindowTitle(newWindowTitle);
	}
}


void MyCV::on_displayMat_action_selected()
{
	QString filename = QFileDialog::getOpenFileName(this,
		code->toUnicode("打开图片"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	src_image = cv::imread(name);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!src_image.data)
	{
		return;
	}
	else {
		setEnable_when_displayMat();
		imageStatus = NO_IMAGE;
		imageShowLabel->displayMat(src_image);
		this->setWindowTitle(filename + QString(" - My openCV"));
	}
}

void MyCV::on_splitR_action_selected() {
	
	std::vector<cv::Mat> out;
	cv::Mat mat1;
	cv::Mat mat2;
	cv::Mat mat3;
	out.push_back(mat1);
	out.push_back(mat2);
	out.push_back(mat3);
	myCVlib::splitRGB(src_image, out);
	imageShowLabel->displayMat(out[2]);
}

void MyCV::on_splitG_action_selected() {
	std::vector<cv::Mat> out;
	cv::Mat mat1;
	cv::Mat mat2;
	cv::Mat mat3;
	out.push_back(mat1);
	out.push_back(mat2);
	out.push_back(mat3);
	myCVlib::splitRGB(src_image, out);
	imageShowLabel->displayMat(out[1]);
}

void MyCV::on_splitB_action_selected() {
	std::vector<cv::Mat> out;
	cv::Mat mat1;
	cv::Mat mat2;
	cv::Mat mat3;
	out.push_back(mat1);
	out.push_back(mat2);
	out.push_back(mat3);
	myCVlib::splitRGB(src_image, out);
	imageShowLabel->displayMat(out[0]);
}

void MyCV::on_mergeRGB_action_selected() {
	imageShowLabel->displayMat(src_image);
}

void MyCV::on_converetToGrey_action_selected() {
	cv::Mat mat;
	myCVlib::convertToGrey(src_image, mat);
	src_image = mat.clone();
	imageShowLabel->displayMat(src_image);
}

void MyCV::on_OTSU_action_selected() {
	cv::Mat mat;
	myCVlib::OTSU(src_image, mat);
	src_image = mat.clone();
	imageShowLabel->displayMat(src_image);
}



void MyCV::showadjustHSLWindow() {
	double r, g, b, H, S, L;
	myCVlib::calculateImageRGB(src_image, r, g, b);
	myCVlib::RGB2HSL(r, g, b, H, S, L);
	adjustHSLWindow->initHSL(H,S,L);
	adjustHSLWindow->show();
}

void MyCV::changeImageHSL(double H, double S,double L) {
	double r, g, b, imgR, imgG, imgB,imgH,imgS,imgL;
#if 0
	myCVlib::HSL2RGB(H,S,L,r,g,b);
	myCVlib::calculateImageRGB(src_image, imgR, imgG, imgB);
	double deltaR = r - imgR;
	double deltaG = g - imgG;
	double deltaB = b - imgB;
	myCVlib::changeImageRGB(src_image, deltaR, deltaG, deltaB);
#endif
#if 1
	myCVlib::calculateImageRGB(src_image, imgR, imgG, imgB);
	myCVlib::RGB2HSL(imgR, imgG, imgB, imgH, imgS, imgL);
	double deltaH = H - imgH;
	double deltaS = S - imgS;
	double deltaL = L - imgL;
	myCVlib::changeImageHSL(src_image, deltaH, deltaS, deltaL);
#endif
	imageShowLabel->displayMat(src_image);
	
}
