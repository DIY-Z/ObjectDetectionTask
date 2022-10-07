#include "ThreadGetCamPic.h"
#include <QImage>

ThreadGetCamPic::ThreadGetCamPic(QObject *parent)
	: QThread(parent)
{}

ThreadGetCamPic::~ThreadGetCamPic()
{
    if (!this->isInterruptionRequested()) //����߳�û��ֹͣ
    { 
        {
            QMutexLocker lock(&m_mux);
            m_bStop = true;
        }
        this->requestInterruption(); //���߳�ֹͣ��
        this->wait();  //Ȼ��wait
    }
}

void ThreadGetCamPic::run()
{

    cv::VideoCapture stVideoCapture;
    //bool bRet = stVideoCapture.open("D:\\FaceForensics++\\original_sequences\\youtube\\c23\\videos\\000.mp4");
    //TODO �������ǵ�Ҫ�Ե����ļ�ѡ������ʽ��ѡ��Ƶ�ļ�
    //bool bRet = stVideoCapture.open("D:\\PostGraduateCourses\\ComputerVision\\Task\\ch01_20180507080000.mp4");  //������ͷֻ��ĳ�0
    bool bRet = stVideoCapture.open(video_path);
    cv::Mat matTemp;
    cv::Mat view;                   //�ݴ��ȡ������Ƶ֡ͼ��,��������Ŀ����
    QImage imgTemp;

    m_bStop = false;
    while (!m_bStop) {
        stVideoCapture >> matTemp;
        if (matTemp.empty()) {
            //���û�д���Ƶ���õ�ͼ��,��ȴ�20ms�ټ���
            msleep(20);
            continue;
        }
        matTemp.copyTo(view);
        if (m_objectDetect)
        {
            //����Ŀ����
            objectDetection(view);
        }

        //BGRתΪRGB
        cvtColor(matTemp, matTemp, cv::COLOR_BGR2RGB);

        imgTemp = QImage(matTemp.data, matTemp.cols, matTemp.rows, matTemp.step, QImage::Format_RGB888).copy();
        //emit�ؼ������ڷ����ź�,�������ź�ʱ,imgTemp��ϢҲ��һ������
        emit sigSendCurImg(imgTemp);
        msleep(20);
    }


}

void ThreadGetCamPic::objectDetection(const cv::Mat& frame)
{
    YOLO yolo_model(yolo_nets);
    yolo_model.detect(frame);
    //BGRתΪRGB
    cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage imgTemp;
    imgTemp = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).copy();
    //
    emit sendDetectionRes(imgTemp);
    msleep(20);
}