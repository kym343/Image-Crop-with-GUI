#include "qt0515.h"

#include <QtWidgets/QApplication>
#include <QPushButton>
#include <iostream>
#include "atlstr.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qspinbox.h>
#include <io.h>
#include <string>
#include <stdio.h>
#include <QThread>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <qlistwidget.h>
#include <qtextstream.h>

using namespace std;
using namespace cv;

//int i = 0;

QString inputdirname = "C:";	// input directory path
QString outputdirname = "C:";	// output directory path

struct _finddata_t fd;	// folder
intptr_t handle;		// iterator
int spin_num;			// scroll num
string path_add;		// Image path
string out_img_path;	// Output dir path to save images

int i = 0;				// Num of this file

// Crop Images
Mat crop45;
Mat crop70;
Mat crop80;
Mat crop100;
Mat crop110;
Mat crop_user;

qt0515::qt0515(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
}

// Conver OpenCV::Mat -> Qt::QImage
QImage qt0515::convertOpenCVMatToQtQImage(cv::Mat mat) {
	if (mat.channels() == 1) {		// if grayscale image
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_Indexed8);
	}
	else if (mat.channels() == 3) {	// if 3channel color image
		cv::cvtColor(mat, mat, CV_BGR2RGB);
		return QImage((uchar*)mat.data, (int)mat.cols, (int)mat.rows, (int)mat.step, QImage::Format_RGB888);
	}
	return QImage();
}

// Select Input Directory to Qfiledialog
void qt0515::selectInputDir() {
	inputdirname = QFileDialog::getExistingDirectory(
		this,
		tr("Select Directory"),
		"C://"
	);
	if (inputdirname > 0) {
		QMessageBox::information(this, tr("Input Directory Name"), inputdirname);
	}
	else {
		QMessageBox::information(this, tr("Input Directory Name"), "Cancled");
	}

	// Display Input Directory
	ui.label_3->setText(inputdirname);
}

// Select Output Directory to Qfiledialog
void qt0515::selectOutputDir() {
	outputdirname = QFileDialog::getExistingDirectory(
		this,
		tr("Select Directory"),
		"C://"
	);
	if (outputdirname > 0) {
		QMessageBox::information(this, tr("Output Directory Name"), outputdirname);
	}
	else {
		QMessageBox::information(this, tr("Output Directory Name"), "Cancled");
	}

	// Display Onput Directory
	ui.label_4->setText(outputdirname);
}

void qt0515::slotDisplay() {
	FILE *out;
	Mat img;

	// Input Path
	string path = inputdirname.toLocal8Bit().constData(); // orignal input directory path

														  // input directory path processing to search image files
	path_add = path;
	for (int i = path.length() - 1; i >= 0; i--) {
		if (path[i] == '/') {
			path_add.replace(i, 1, "//");
		}
	}

	// Output Path
	string out_path = outputdirname.toLocal8Bit().constData(); // orignal output directory path

																// output directory path processing to save image files
	string out_path_add = out_path;
	for (int i = out_path.length() - 1; i >= 0; i--) {
		if (out_path[i] == '/') {
			out_path_add.replace(i, 1, "//");
		}
	}
	out_img_path = out_path_add;

	// all bmp file to search
	string input_path = path_add;
	input_path.append("//*.bmp");

	// Directory Cheak
	if ((handle = _findfirst(input_path.c_str(), &fd)) == -1L)
		cout << "No file in directory!" << endl;

	/*do {*/
	// Creat Image Path in Input Directory
	string img_path = path_add;
	img_path.append("//");
	img_path.append(fd.name);

	// Add image file name to listbox
	ui.listWidget->addItem(QString::number(i) + ". " + fd.name);
	i++;

	// Image read
	img = imread(img_path, 1);

	//// Just resize input image if you want
	//cv::resize(img, img, Size(640, 480));

	// ========= Original Image to draw =========
	Mat img_cp = img.clone();

	// Convert Image
	QImage qimg_Input = convertOpenCVMatToQtQImage(img_cp);

	// Display output
	ui.label_5->setPixmap(QPixmap::fromImage(qimg_Input));

	// ================= ROI 45 =================
	Mat roi45 = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect1(20, 45, 280, 100);

	// Crop ROI
	crop45 = roi45(rect1);

	// Convert Image
	QImage qimg_crop45 = convertOpenCVMatToQtQImage(crop45);

	// Display output
	ui.label_6->setPixmap(QPixmap::fromImage(qimg_crop45));

	// ================= ROI 70 =================
	Mat roi70 = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect2(20, 70, 280, 100);

	// Crop ROI
	crop70 = roi70(rect2);

	// Convert Image
	QImage qimg_crop70 = convertOpenCVMatToQtQImage(crop70);

	// Display output
	ui.label_7->setPixmap(QPixmap::fromImage(qimg_crop70));

	// ================= ROI 80 =================
	Mat roi80 = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect3(20, 80, 280, 100);

	// Crop ROI
	crop80 = roi45(rect3);

	// Convert Image
	QImage qimg_crop80 = convertOpenCVMatToQtQImage(crop80);

	// Display output
	ui.label_8->setPixmap(QPixmap::fromImage(qimg_crop80));

	// ================= ROI 100 =================
	Mat roi100 = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect4(20, 100, 280, 100);

	// Crop ROI
	crop100 = roi100(rect4);

	// Convert Image
	QImage qimg_crop100 = convertOpenCVMatToQtQImage(crop100);

	// Display output
	ui.label_9->setPixmap(QPixmap::fromImage(qimg_crop100));

	// ================= ROI 110 =================
	Mat roi110 = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect5(20, 110, 280, 100);

	// Crop ROI
	crop110 = roi110(rect5);

	// Convert Image
	QImage qimg_crop110 = convertOpenCVMatToQtQImage(crop110);

	// Display output
	ui.label_10->setPixmap(QPixmap::fromImage(qimg_crop110));



	//} while (_findnext(handle, &fd) == 0);	// Until all the files in the folder have passed

	//_findclose(handle);

}

void qt0515::nextImage(){
	Mat img;

	if (_findnext(handle, &fd) != 0) {	// Until all the files in the folder have passed
		_findclose(handle);
		ui.listWidget->addItem("================== Finish ==================");
		QMessageBox::warning(this, tr("Finish"), "These images are empty.");
	}
	else {
		// Creat Image Path in Input Directory
		string img_path = path_add;
		img_path.append("//");
		img_path.append(fd.name);

		// Add image file name to listbox
		ui.listWidget->addItem(QString::number(i) + ". " + fd.name);
		i++;

		// Image read
		img = imread(img_path, 1);

		//// Just resize input image if you want
		//cv::resize(img, img, Size(640, 480));

		// ========= Original Image to draw =========
		Mat img_cp = img.clone();

		// Convert Image
		QImage qimg_Input = convertOpenCVMatToQtQImage(img_cp);

		// Display output
		ui.label_5->setPixmap(QPixmap::fromImage(qimg_Input));

		// ================= ROI 45 =================
		Mat roi45 = img_cp.clone();

		// set ROI(X, Y, W, H)).
		Rect rect1(20, 45, 280, 100);

		// Crop ROI
		crop45 = roi45(rect1);

		// Convert Image
		QImage qimg_crop45 = convertOpenCVMatToQtQImage(crop45);

		// Display output
		ui.label_6->setPixmap(QPixmap::fromImage(qimg_crop45));

		// ================= ROI 70 =================
		Mat roi70 = img_cp.clone();

		// set ROI(X, Y, W, H)).
		Rect rect2(20, 70, 280, 100);

		// Crop ROI
		crop70 = roi70(rect2);

		// Convert Image
		QImage qimg_crop70 = convertOpenCVMatToQtQImage(crop70);

		// Display output
		ui.label_7->setPixmap(QPixmap::fromImage(qimg_crop70));

		// ================= ROI 80 =================
		Mat roi80 = img_cp.clone();

		// set ROI(X, Y, W, H)).
		Rect rect3(20, 80, 280, 100);

		// Crop ROI
		crop80 = roi45(rect3);

		// Convert Image
		QImage qimg_crop80 = convertOpenCVMatToQtQImage(crop80);

		// Display output
		ui.label_8->setPixmap(QPixmap::fromImage(qimg_crop80));

		// ================= ROI 100 =================
		Mat roi100 = img_cp.clone();

		// set ROI(X, Y, W, H)).
		Rect rect4(20, 100, 280, 100);

		// Crop ROI
		crop100 = roi100(rect4);

		// Convert Image
		QImage qimg_crop100 = convertOpenCVMatToQtQImage(crop100);

		// Display output
		ui.label_9->setPixmap(QPixmap::fromImage(qimg_crop100));

		// ================= ROI 110 =================
		Mat roi110 = img_cp.clone();

		// set ROI(X, Y, W, H)).
		Rect rect5(20, 110, 280, 100);

		// Crop ROI
		crop110 = roi110(rect5);

		// Convert Image
		QImage qimg_crop110 = convertOpenCVMatToQtQImage(crop110);

		// Display output
		ui.label_10->setPixmap(QPixmap::fromImage(qimg_crop110));
	}
}

void qt0515::saveCrop45() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);
	
	crop_img_path.append(token);
	crop_img_path.append("_crop1.");
	
	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop45);						// Save file
}

void qt0515::saveCrop70() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);

	crop_img_path.append(token);
	crop_img_path.append("_crop2.");

	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop70);						// Save file
}

void qt0515::saveCrop80() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);

	crop_img_path.append(token);
	crop_img_path.append("_crop3.");

	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop80);						// Save file
}

void qt0515::saveCrop100() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);

	crop_img_path.append(token);
	crop_img_path.append("_crop4.");

	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop100);						// Save file
}

void qt0515::saveCrop110() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);

	crop_img_path.append(token);
	crop_img_path.append("_crop5.");

	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop110);						// Save file
}

void qt0515::loadUserCrop() {
	Mat img;

	// update number of y for crop  
	spin_num = ui.spinBox->value();

	// Creat Image Path in Input Directory
	string img_path = path_add;
	img_path.append("//");
	img_path.append(fd.name);

	// Image read
	img = imread(img_path, 1);

	//// Just resize input image if you want
	//cv::resize(img, img, Size(640, 480));

	Mat img_cp = img.clone();

	Mat roi_user = img_cp.clone();

	// set ROI(X, Y, W, H)).
	Rect rect_user(20, spin_num, 280, 100);

	// Crop ROI
	crop_user = roi_user(rect_user);

	// Convert Image
	QImage qimg_crop_user = convertOpenCVMatToQtQImage(crop_user);

	// Display output
	ui.label_11->setPixmap(QPixmap::fromImage(qimg_crop_user));
}

void qt0515::saveUserCrop() {
	string crop_img_path = out_img_path;
	crop_img_path.append("//");

	char temp[260] = "";
	strcpy(temp, fd.name);

	char *str = temp;
	/*char *str = fd.name;*/
	int cnt = 0;
	char *context = NULL;
	char *token = strtok_s(str, ".", &context);

	crop_img_path.append(token);
	crop_img_path.append("_crop6.");

	token = strtok_s(NULL, ".", &context);
	crop_img_path.append(token);


	ui.listWidget->addItem(" [*]  Save " + QString::fromStdString(crop_img_path));

	// Mat img_rgb = img_cp.clone();
	// cv::cvtColor(img_rgb, img_rgb, CV_RGB2BGR);		// Convert RBG -> BGR
	imwrite(crop_img_path, crop_user);						// Save file
}

//void qt0515::pushbutton() {
//	QMessageBox::information(this, "Hello", "Good");
//
//	ui.label->setText(QString::number(i) + "th");
//
//	ui.listWidget->addItem(QString::number(i));
//
//	i++;
//}


//void qt0515::Display() {
//	// Image read
//	Mat img = imread("C:\\Users\\dotd\\workspace\\1.png", 1);
//
//	cv::resize(img, img, Size(320, 240));
//
//	// Conver Image
//	QImage qimgOutput = convertOpenCVMatToQtQImage(img);
//
//	// Display output
//	ui.label_2->setPixmap(QPixmap::fromImage(qimgOutput));
//}