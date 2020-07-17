#include "qt0515.h"
#include <QtWidgets/QApplication>

#include <QPushButton>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qt0515 w;
	w.show();
	return a.exec();
}
