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

	histImageShowWindow = new QWidget(this,Qt::Window);
	histImageShowLabel = new QLabel(histImageShowWindow);
	histImageShowLabel->setGeometry(QRect(0, 0, 0, 0));
	histImageShowLabel->setFrameStyle(QFrame::Panel | QFrame::Sunken); //设置外观

	adjustHSLWindow = new HSLSliderWidget(this);
	adjustHSLWindow->resize(600, 250);
	adjustHSLWindow->setWindowTitle(code->toUnicode("色相 饱和度 亮度调节"));
	//adjustHSLWindow->show();
	binarizationWindow = new BinarizationSliderWidget(this);
	binarizationWindow->resize(600, 200);
	binarizationWindow->setWindowTitle(code->toUnicode("双阈值二值化调节"));

	gausFilterWindow = new GausFilterSliderWidget(this);
	gausFilterWindow->resize(600, 200);
	gausFilterWindow->setWindowTitle(code->toUnicode("Gauss平滑滤波"));

	cannyWindow = new CannySliderWidget(this);
	cannyWindow->resize(600, 350);
	cannyWindow->setWindowTitle(code->toUnicode("Canny检测"));

	houghLineWindow = new HoughSliderWidget(this);
	houghLineWindow->resize(600, 600);
	houghLineWindow->setWindowTitle(code->toUnicode("Hough Line"));
	houghCircleWindow = new HoughSliderWidget(this);
	houghCircleWindow->resize(600, 600);
	houghCircleWindow->setWindowTitle(code->toUnicode("Hough Circle"));

	for (int i = 0; i < 25; i++) {
		kernal.push_back(1);
	}
	setSEWindow = new SetSEWidget(this);
	setSEWindow->resize(300, 300);
	setSEWindow->setWindowTitle(code->toUnicode("SE"));
	connect(setSEWindow, SIGNAL(applySE(std::vector<char>)), this, SLOT(setSE(std::vector<char>)));


	//QMenu
	file_menu = new QMenu(code->toUnicode("文件"));
	edit_menu = new QMenu(code->toUnicode("编辑"));
	menuBar()->addMenu(file_menu);
	menuBar()->addMenu(edit_menu);
	edit_menu->setEnabled(false);


	//QAction
	QAction* action_open = new QAction(QIcon("png/folder_open_icon&32.png"), code->toUnicode("打开文件"));
	file_menu->addAction(action_open);
	ui.mainToolBar->addAction(action_open);
	connect(action_open, SIGNAL(triggered(bool)), this, SLOT(on_open_action_selected()));

	//QAction
	QAction* action_save = new QAction(QIcon("png/folder_plus_icon&32.png"), code->toUnicode("另存为"));
	file_menu->addAction(action_save);
	ui.mainToolBar->addAction(action_save);
	connect(action_save, SIGNAL(triggered(bool)), this, SLOT(on_saveas_action_selected()));

	//QAction
	QAction* action_adjustHSL = new QAction(code->toUnicode("色相 饱和度 亮度调节"));
	edit_menu->addAction(action_adjustHSL);
	connect(action_adjustHSL, SIGNAL(triggered(bool)), this, SLOT(showadjustHSLWindow()));
	connect(adjustHSLWindow, SIGNAL(applyHSL(double, double, double)), this, SLOT(changeImageHSL(double, double, double)));

	//QAction
	QAction* action_binarization = new QAction(code->toUnicode("双阈值二值化调节"));
	edit_menu->addAction(action_binarization);
	connect(action_binarization, SIGNAL(triggered(bool)), this, SLOT(showbinarizationWindow()));
	connect(binarizationWindow, SIGNAL(applyBinarization(int, int)), this, SLOT(changeBinarization(int, int)));



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

	// QMenu
	QAction *action_showHist = new QAction(code->toUnicode("灰度直方图"));
	edit_menu->addAction(action_showHist);
	connect(action_showHist, SIGNAL(triggered(bool)), this, SLOT(on_showHist_action_selected()));

	//QMenu
	QMenu *adjustContrast_menu = new QMenu(code->toUnicode("对比度调节"));
	edit_menu->addMenu(adjustContrast_menu);
	QAction *action_equalizeHist = new QAction(code->toUnicode("直方图均衡化"));
	QAction *action_linearAdjust = new QAction(code->toUnicode("分段线性"));
	QAction *action_logAdjust = new QAction(code->toUnicode("对数"));
	QAction *action_powAdjust = new QAction(code->toUnicode("指数"));
	adjustContrast_menu->addAction(action_equalizeHist);
	adjustContrast_menu->addAction(action_linearAdjust);
	adjustContrast_menu->addAction(action_logAdjust);
	adjustContrast_menu->addAction(action_powAdjust);
	connect(action_equalizeHist, SIGNAL(triggered(bool)), this, SLOT(on_equalizeHist_action_selected()));
	connect(action_linearAdjust, SIGNAL(triggered(bool)), this, SLOT(on_linearAdjust_action_selected()));
	connect(action_logAdjust, SIGNAL(triggered(bool)), this, SLOT(on_logAdjust_action_selected()));
	connect(action_powAdjust, SIGNAL(triggered(bool)), this, SLOT(on_powAdjust_action_selected()));


	//QMenu
	QMenu *edgeDetect_menu = new QMenu(code->toUnicode("边缘检测"));
	edit_menu->addMenu(edgeDetect_menu);
	QAction *action_canny = new QAction(code->toUnicode("Canny边缘检测"));
	QAction *action_sobel = new QAction(code->toUnicode("Sobel边缘检测"));
	QAction *action_laplace = new QAction(code->toUnicode("Laplace边缘检测"));
	edgeDetect_menu->addAction(action_canny);
	edgeDetect_menu->addAction(action_sobel);
	edgeDetect_menu->addAction(action_laplace);
	connect(action_canny, SIGNAL(triggered(bool)), this, SLOT(on_canny_action_selected()));
	connect(action_sobel, SIGNAL(triggered(bool)), this, SLOT(on_sobel_action_selected()));
	connect(action_laplace, SIGNAL(triggered(bool)), this, SLOT(on_laplace_action_selected()));
	connect(cannyWindow, SIGNAL(applyCanny(double, double, int, int)), this, SLOT(canny(double, double, int,int)));

	//QMenu
	QMenu *hough_menu = new QMenu(code->toUnicode("Hough"));
	edit_menu->addMenu(hough_menu);
	QAction *action_houghLine = new QAction(code->toUnicode("直线"));
	QAction *action_houghCircle = new QAction(code->toUnicode("圆"));
	hough_menu->addAction(action_houghLine);
	hough_menu->addAction(action_houghCircle);
	connect(action_houghLine, SIGNAL(triggered(bool)), this, SLOT(on_houghLine_action_selected()));
	connect(action_houghCircle, SIGNAL(triggered(bool)), this, SLOT(on_houghCircle_action_selected()));
	connect(houghLineWindow, SIGNAL(applyHough(double, double, double, double, double, int, int)), this, SLOT(HoughLine(double, double, double, double, double, int, int)));
	connect(houghCircleWindow, SIGNAL(applyHough(double, double, double, double, double, int, int)), this, SLOT(HoughCircle(double, double, double, double, double, int, int)));


	//QMenu
	QAction *action_OTSU = new QAction(code->toUnicode("OTSU二值化"));
	edit_menu->addAction(action_OTSU);
	connect(action_OTSU, SIGNAL(triggered(bool)), this, SLOT(on_OTSU_action_selected()));

	//QMenu
	QMenu* bin_menu = new QMenu(code->toUnicode("二值数学形态学"));
	edit_menu->addMenu(bin_menu);
	QAction* action_setSE = new QAction(code->toUnicode("设置卷积核"));
	QAction* action_bin_dilate = new QAction(code->toUnicode("二值膨胀"));
	QAction* action_bin_erode = new QAction(code->toUnicode("二值腐蚀"));
	QAction* action_bin_open = new QAction(code->toUnicode("二值开"));
	QAction* action_bin_close = new QAction(code->toUnicode("二值闭"));
	QAction *action_bin_thin = new QAction(code->toUnicode("二值细化"));
	
	bin_menu->addAction(action_setSE);
	bin_menu->addAction(action_bin_dilate);
	bin_menu->addAction(action_bin_erode);
	bin_menu->addAction(action_bin_open);
	bin_menu->addAction(action_bin_close);
	bin_menu->addAction(action_bin_thin);

	connect(action_bin_dilate, SIGNAL(triggered(bool)), this, SLOT(on_bin_dilate_action_selected()));
	connect(action_bin_erode, SIGNAL(triggered(bool)), this, SLOT(on_bin_erode_action_selected()));
	connect(action_bin_open, SIGNAL(triggered(bool)), this, SLOT(on_bin_open_action_selected()));
	connect(action_bin_close, SIGNAL(triggered(bool)), this, SLOT(on_bin_close_action_selected()));
	connect(action_setSE, SIGNAL(triggered(bool)), this, SLOT(on_setSE_action_selected()));
	connect(action_bin_thin, SIGNAL(triggered(bool)), this, SLOT(on_bin_thin_action_selected()));


	//QMenu
	QMenu* arithop_menu = new QMenu(code->toUnicode("图像代数操作"));
	edit_menu->addMenu(arithop_menu);
	QAction* action_add = new QAction(code->toUnicode("图像相加"));
	QAction* action_subtract = new QAction(code->toUnicode("图像相减"));
	QAction* action_multiple = new QAction(code->toUnicode("图像相乘（二值图像）"));
	arithop_menu->addAction(action_add);
	arithop_menu->addAction(action_subtract);
	arithop_menu->addAction(action_multiple);
	connect(action_add, SIGNAL(triggered(bool)), this, SLOT(on_add_action_selected()));
	connect(action_subtract, SIGNAL(triggered(bool)), this, SLOT(on_subtract_action_selected()));
	connect(action_multiple, SIGNAL(triggered(bool)), this, SLOT(on_multiple_action_selected()));

	QMenu* gemoop_menu = new QMenu(code->toUnicode("图像几何操作"));
	edit_menu->addMenu(gemoop_menu);
	QAction* action_nn_mul2 = new QAction(code->toUnicode("最近邻放大"));
	QAction* action_nn_div2 = new QAction(code->toUnicode("最近邻缩小"));
	QAction* action_linear_mul2 = new QAction(code->toUnicode("双线性放大"));
	QAction* action_linear_div2 = new QAction(code->toUnicode("双线性缩小"));
	QAction* action_nn_rotate45 = new QAction(code->toUnicode("最近邻旋转"));
	gemoop_menu->addAction(action_nn_mul2);
	gemoop_menu->addAction(action_nn_div2);
	gemoop_menu->addAction(action_linear_mul2);
	gemoop_menu->addAction(action_linear_div2);
	gemoop_menu->addAction(action_nn_rotate45);
	connect(action_nn_mul2, SIGNAL(triggered(bool)), this, SLOT(on_nn_mul2_action_selected()));
	connect(action_nn_div2, SIGNAL(triggered(bool)), this, SLOT(on_nn_div2_action_selected()));
	connect(action_linear_mul2, SIGNAL(triggered(bool)), this, SLOT(on_linear_mul2_action_selected()));
	connect(action_linear_div2, SIGNAL(triggered(bool)), this, SLOT(on_linear_div2_action_selected()));
	connect(action_nn_rotate45, SIGNAL(triggered(bool)), this, SLOT(on_nn_rotate45_action_selected()));

	//QMenu
	QMenu* filter_menu = new QMenu(code->toUnicode("平滑滤波"));
	edit_menu->addMenu(filter_menu);
	QAction* action_avgFilter = new QAction(code->toUnicode("均值"));
	QAction* action_midFilter = new QAction(code->toUnicode("中值"));
	QAction* action_gausFilter = new QAction(code->toUnicode("高斯"));
	filter_menu->addAction(action_avgFilter);
	filter_menu->addAction(action_midFilter);
	filter_menu->addAction(action_gausFilter);
	connect(action_avgFilter, SIGNAL(triggered(bool)), this, SLOT(on_avgFilter_action_selected()));
	connect(action_midFilter, SIGNAL(triggered(bool)), this, SLOT(on_midFilter_action_selected()));
	connect(action_gausFilter, SIGNAL(triggered(bool)), this, SLOT(on_gausFilter_action_selected()));
	connect(gausFilterWindow, SIGNAL(applyGausFilter(int, int)), this, SLOT(useGausFilter(int, int)));
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


void MyCV::on_open_action_selected()
{
	QString filename = QFileDialog::getOpenFileName(this,
		code->toUnicode("打开图片"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	src_image = cv::imread(name, cv::IMREAD_UNCHANGED);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	int channels = src_image.channels();
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

void MyCV::on_saveas_action_selected()
{
	QString filename = QFileDialog::getSaveFileName(this,
		code->toUnicode("另存为"), "", tr("*.bmp;; *.png;; *.jpg;; *.tif;; *.GIF"));
	if (filename.isEmpty())
	{
		return;
	}
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	
	cv::imwrite(name,imageShowLabel->image);
	src_image = imageShowLabel->image.clone();
	imageStatus = NO_IMAGE;
	imageShowLabel->displayMat(src_image);
	this->setWindowTitle(filename + QString(" - My openCV"));
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

void MyCV::on_showHist_action_selected() {
	cv::Mat mat;
	int ranges[2] = { 0,255 };
	int *hist = new int[256];
	memset(hist, 0, sizeof(int)*256);
	myCVlib::calcHist(src_image, hist, 256, ranges);
	myCVlib::getHistImg(hist, mat,256,ranges);
	delete[] hist;
	//imageShowLabel->displayMat(mat);
	
	QImage Qimg = QImage((const unsigned char*)(mat.data), mat.cols, mat.rows, mat.cols*mat.channels(), QImage::Format_Grayscale8);
	QPixmap qPixap = QPixmap::fromImage(Qimg);
	histImageShowWindow->resize(qPixap.size());
	histImageShowLabel->resize(qPixap.size());
	//qPixap.scaled(labelimage->size(), Qt::KeepAspectRatio);
	histImageShowLabel->setPixmap(qPixap);
	//labelimage->resize(labelimage->pixmap()->size());
	histImageShowWindow->show();
	
	
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

void  MyCV::showbinarizationWindow() {
	binarizationWindow->show();
}
void  MyCV::changeBinarization(int minPixel, int maxPixel) {
	cv::Mat dst;
	myCVlib::doubleThresholdBinary(src_image, dst, minPixel, maxPixel);
	imageShowLabel->displayMat(dst);
}

void MyCV::on_add_action_selected() {
	cv::Mat src1 = src_image;
	cv::Mat src2;
	cv::Mat dst;
	QString filename = QFileDialog::getOpenFileName(this,
		code->toUnicode("打开图片"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	src2 = cv::imread(name,cv::IMREAD_UNCHANGED);
	int channels = src2.channels();
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!src2.data)
	{
		return;
	}
	myCVlib::op_add(src1, src2, dst);
	imageShowLabel->displayMat(dst);
}

void MyCV::on_subtract_action_selected() {
	cv::Mat src1 = src_image;
	cv::Mat src2;
	cv::Mat dst;
	QString filename = QFileDialog::getOpenFileName(this,
		code->toUnicode("打开图片"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	src2 = cv::imread(name,cv::IMREAD_UNCHANGED);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!src2.data)
	{
		return;
	}
	myCVlib::op_subtract(src1, src2, dst);
	imageShowLabel->displayMat(dst);

}
void MyCV::on_multiple_action_selected() {
	cv::Mat src1 = src_image;
	cv::Mat src2;
	cv::Mat dst;
	QString filename = QFileDialog::getOpenFileName(this,
		code->toUnicode("打开图片"), ".", tr("Image File (*.jpg *.png *.bmp)"));
	std::string name = code->fromUnicode(filename).data();//filename.toAscii().data()
	src2 = cv::imread(name,cv::IMREAD_UNCHANGED);
	//cv::imshow(name.c_str(), image);
	//cv::waitKey();
	if (!src2.data)
	{
		return;
	}
	myCVlib::op_multiple(src1, src2, dst);
	imageShowLabel->displayMat(dst);

}

void MyCV::on_canny_action_selected() {
	cannyWindow->initCanny(40.0,90.0,7,1);
	cannyWindow->show();
}


void MyCV::on_sobel_action_selected() {
	cv::Mat mat;
	myCVlib::sobelDector(src_image, mat);
	imageShowLabel->displayMat(mat);


}void MyCV::on_laplace_action_selected() {
	cv::Mat mat;
	myCVlib::laplaceDector(src_image, mat);
	imageShowLabel->displayMat(mat);


}

void MyCV::canny(double lowThreshold, double highThreshold, int aperture_size, int aperture_sigma) {
	cv::Mat mat;
	myCVlib::canny(src_image, mat, lowThreshold,highThreshold,aperture_size,aperture_sigma);
	//src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}

void MyCV::on_avgFilter_action_selected() {
	cv::Mat mat;
	myCVlib::avgFilter(src_image, mat, 7);	
	imageShowLabel->displayMat(mat);


}
void MyCV::on_midFilter_action_selected() {
	cv::Mat mat;
	myCVlib::midFilter(src_image, mat,7);
	imageShowLabel->displayMat(mat);
}
void MyCV::on_gausFilter_action_selected() {
	gausFilterWindow->show();
}

void MyCV::useGausFilter(int aperture_size, int aperture_sigma) {
	cv::Mat mat;
	myCVlib::gausFilter(src_image, mat, aperture_size, aperture_sigma);
	//src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}

void MyCV::on_nn_mul2_action_selected() {
	cv::Mat mat;
	myCVlib::nn_resize(src_image, mat, 2);
	src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}
void MyCV::on_nn_div2_action_selected() {
	cv::Mat mat;
	myCVlib::nn_resize(src_image, mat, 0.5);
	src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}
void MyCV::on_linear_mul2_action_selected() {
	cv::Mat mat;
	myCVlib::linear_resize(src_image, mat, 2);
	src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}
void MyCV::on_linear_div2_action_selected() {
	cv::Mat mat;
	myCVlib::linear_resize(src_image, mat, 0.5);
	src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}

void MyCV::on_nn_rotate45_action_selected() {
	cv::Mat mat;
	myCVlib::nn_rotate(src_image, mat,45);
	//src_image = mat.clone();
	imageShowLabel->displayMat(mat);

}



void MyCV::on_houghLine_action_selected() {
	houghLineWindow->initHough(200,1, 20, 100, 60, 0, 0);
	houghLineWindow->show();
}
void MyCV::on_houghCircle_action_selected() {
	houghCircleWindow->initHough(200, 1, 20, 100, 60, 0, 0);
	houghCircleWindow->show();
}

void MyCV::HoughCircle(double line_threshold, double dp, double min_dist, double canny_threshold, double circle_threshold, int minRadius, int maxRadius) {
	cv::Mat mat;
	mat = src_image.clone();
	myCVlib::houghCircle(src_image, mat,dp,min_dist,canny_threshold, circle_threshold,minRadius,maxRadius);
	//src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}
void MyCV::HoughLine(double line_threshold, double dp, double min_dist, double canny_threshold, double circle_threshold, int minRadius, int maxRadius){
	cv::Mat mat;
	mat = src_image.clone();
	myCVlib::houghLine(src_image, line_threshold, mat );
	//src_image = mat.clone();
	imageShowLabel->displayMat(mat);
}

void MyCV::on_equalizeHist_action_selected() {
	cv::Mat mat;
	int ranges[2] = { 0,255 };
	myCVlib::equalizeHist(src_image, mat, 256, ranges);
	imageShowLabel->displayMat(mat);
}
void MyCV::on_linearAdjust_action_selected() {
	cv::Mat mat;
	int p1[2] = { 100,50 };
	int p2[2] = { 150,200 };
	myCVlib::linear_adjustContrast(src_image, mat, p1, p2);
	imageShowLabel->displayMat(mat);
}
void MyCV::on_logAdjust_action_selected() {
	cv::Mat mat;
	int ground = 10;
	myCVlib::log_adjustContrast(src_image, mat, ground);
	imageShowLabel->displayMat(mat);
}
void MyCV::on_powAdjust_action_selected() {
	cv::Mat mat;
	int index = 2;
	myCVlib::pow_adjustContrast(src_image, mat,index);
	imageShowLabel->displayMat(mat);
}

void MyCV::on_setSE_action_selected() {
	setSEWindow->show();
}

void  MyCV::setSE(std::vector<char>se) {
	for (int i = 0; i < kernal.size();i++) {
		kernal[i] = se[i];
	}
}


void MyCV::on_bin_dilate_action_selected() {
	cv::Mat mat;
	myCVlib::bin_dilate(src_image, mat, kernal, 5);
	imageShowLabel->displayMat(mat);
}

void MyCV::on_bin_erode_action_selected() {
	cv::Mat mat;
	/*
	char **kernal = new char*[3];
	for (int i = 0; i < 3; i++) {
		kernal[i] = new char[3];
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			kernal[i][j] = 1;
		}
	}
	*/
	

	myCVlib::bin_erode(src_image, mat, kernal,5);
	imageShowLabel->displayMat(mat);
}

void MyCV::on_bin_open_action_selected() {
	cv::Mat mat;
	myCVlib::bin_open(src_image, mat, kernal, 5);
	imageShowLabel->displayMat(mat);
}

void MyCV::on_bin_close_action_selected() {
	cv::Mat mat;
	myCVlib::bin_close(src_image, mat, kernal, 5);
	imageShowLabel->displayMat(mat);

}
void MyCV::on_bin_thin_action_selected() {
		cv::Mat mat;
		myCVlib::bin_thin(src_image, mat, 3);
		imageShowLabel->displayMat(mat);
}
