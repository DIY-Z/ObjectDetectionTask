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

    void onShowDetectionRes(const QImage& img);

private:
    Ui::ObjectDetectionTaskClass ui;

    QImage m_imgSrc;
    QImage m_img2Show;
    QPixmap m_pix2Show;

    QImage m_imgSrcDetectionRes;
    QImage m_img2ShowDetectionRes;
    QPixmap m_pix2ShowDetectionRes;

    ThreadGetCamPic m_stThreadGetCamPic;
};
