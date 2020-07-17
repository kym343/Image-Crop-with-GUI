#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qt0515.h"

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QtWidgets/QMainWindow>
#include "ui_qt0515.h"
#include "atlstr.h"
#include <Windows.h>
#include <qlistwidget.h>

using namespace std;
using namespace cv;

class qt0515 : public QMainWindow
{
	Q_OBJECT

public:
	qt0515(QWidget *parent = Q_NULLPTR);
	QImage qt0515::convertOpenCVMatToQtQImage(cv::Mat mat);

private:
	Ui::qt0515Class ui;
	private slots:

	void selectInputDir();
	void selectOutputDir();
	void slotDisplay();
	void nextImage();

	void saveCrop45();
	void saveCrop70();
	void saveCrop80();
	void saveCrop100();
	void saveCrop110();

	void loadUserCrop();
	void saveUserCrop();

	//void pushbutton();
	//void Display();
};
