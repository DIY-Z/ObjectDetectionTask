#pragma once

#include <QThread>
#include <opencv2/opencv.hpp>
#include <QMutex>
#include "yolo.h"


class ThreadGetCamPic  : public QThread
{
	Q_OBJECT

public:
	ThreadGetCamPic(QObject *parent);
	~ThreadGetCamPic();

	void run();
	void objectDetection(const cv::Mat& frame);

	string video_path;

//signals是修饰信号函数的关键字
signals:
	void sigSendCurImg(const QImage& img);
	void sendDetectionRes(const QImage& img);
	
private:
	bool m_bStop = true;
	bool m_objectDetect = true;
	QMutex m_mux;	
};
