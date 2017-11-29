#include "MyCV.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyCV w;
	w.show();
	return a.exec();
}
