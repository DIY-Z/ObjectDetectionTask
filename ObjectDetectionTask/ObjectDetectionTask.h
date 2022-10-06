#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ObjectDetectionTask.h"
#include <opencv2/opencv.hpp>
#include "ThreadGetCamPic.h"

class ObjectDetectionTask : public QMainWindow
{
    Q_OBJECT

public:
    ObjectDetectionTask(QWidget *parent = nullptr);
    ~ObjectDetectionTask();

public slots:
    void onFreshCurImg(const QImage& img);
    void onOpenVideo();

private:
    Ui::ObjectDetectionTaskClass ui;

    QImage m_imgSrc;
    QImage m_img2Show;
    QPixmap m_pix2Show;

    ThreadGetCamPic m_stThreadGetCamPic;
};
