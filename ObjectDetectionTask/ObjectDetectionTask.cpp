#include "ObjectDetectionTask.h"

ObjectDetectionTask::ObjectDetectionTask(QWidget *parent)
    : QMainWindow(parent)
    , m_stThreadGetCamPic(this)
{
    ui.setupUi(this);

    connect(&m_stThreadGetCamPic, &ThreadGetCamPic::sigSendCurImg, this, &ObjectDetectionTask::onFreshCurImg);
    connect(ui.openVideoBtn, &QPushButton::clicked, this, &ObjectDetectionTask::onOpenVideo);
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
    //��������߳�
    m_stThreadGetCamPic.start();
}
