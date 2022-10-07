#include "ObjectDetectionTask.h"
#include <QFileDialog>


ObjectDetectionTask::ObjectDetectionTask(QWidget *parent)
    : QMainWindow(parent)
    , m_stThreadGetCamPic(this)
{
    ui.setupUi(this);

    connect(&m_stThreadGetCamPic, &ThreadGetCamPic::sigSendCurImg, this, &ObjectDetectionTask::onFreshCurImg);
    connect(ui.openVideoBtn, &QPushButton::clicked, this, &ObjectDetectionTask::onOpenVideo);

    connect(&m_stThreadGetCamPic, &ThreadGetCamPic::sendDetectionRes, this, &ObjectDetectionTask::onShowDetectionRes);
}

ObjectDetectionTask::~ObjectDetectionTask()
{}

void ObjectDetectionTask::onFreshCurImg(const QImage& img)
{
    m_imgSrc = img.copy();   //�������Ƶ�е�֡ͼ���������ͷ�ĵ�����Ƶ��ͼ��֡���ô��Ļ�,�����Ƚ����ݴ�

    m_img2Show = m_imgSrc.scaled(ui.orginVideoLabel->size(), Qt::KeepAspectRatio, Qt::FastTransformation);

    m_pix2Show = QPixmap::fromImage(m_img2Show);

    ui.orginVideoLabel->setPixmap(m_pix2Show);
}

void ObjectDetectionTask::onOpenVideo()
{
    QString strFileName = QFileDialog::getOpenFileName(this,
        tr("Open Video"), "/home/", tr("Image Files (*.mp4)"));
    if (strFileName.isEmpty()) {
        return;
    }
    m_stThreadGetCamPic.video_path = strFileName.toLocal8Bit().data();
    
    //��������߳�
    m_stThreadGetCamPic.start();
}

void ObjectDetectionTask::onShowDetectionRes(const QImage& img)
{
    m_imgSrcDetectionRes = img.copy();
    m_img2ShowDetectionRes = m_imgSrcDetectionRes.scaled(ui.detectionResultLable->size(), Qt::KeepAspectRatio, Qt::FastTransformation);
    m_pix2ShowDetectionRes = QPixmap::fromImage(m_img2ShowDetectionRes);
    ui.detectionResultLable->setPixmap(m_pix2ShowDetectionRes);
}
