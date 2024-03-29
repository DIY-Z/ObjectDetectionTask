#include "ThreadGetCamPic.h"
#include <QImage>

ThreadGetCamPic::ThreadGetCamPic(QObject *parent)
	: QThread(parent)
{}

ThreadGetCamPic::~ThreadGetCamPic()
{
    if (!this->isInterruptionRequested()) //如果线程没有停止
    { 
        {
            QMutexLocker lock(&m_mux);
            m_bStop = true;
        }
        this->requestInterruption(); //将线程停止掉
        this->wait();  //然后wait
    }
}

void ThreadGetCamPic::run()
{

    cv::VideoCapture stVideoCapture;
    //bool bRet = stVideoCapture.open("D:\\FaceForensics++\\original_sequences\\youtube\\c23\\videos\\000.mp4");
    //TODO 这里后面记得要以弹出文件选择框的形式来选视频文件
    //bool bRet = stVideoCapture.open("D:\\PostGraduateCourses\\ComputerVision\\Task\\ch01_20180507080000.mp4");  //打开摄像头只需改成0
    bool bRet = stVideoCapture.open(video_path);
    cv::Mat matTemp;
    cv::Mat view;                   //暂存读取到的视频帧图像,将其用于目标检测
    QImage imgTemp;

    m_bStop = false;
    while (!m_bStop) {
        stVideoCapture >> matTemp;
        if (matTemp.empty()) {
            //如果没有从视频中拿到图像,则等待20ms再继续
            msleep(20);
            continue;
        }
        matTemp.copyTo(view);
        if (m_objectDetect)
        {
            //进行目标检测
            objectDetection(view);
        }

        //BGR转为RGB
        cvtColor(matTemp, matTemp, cv::COLOR_BGR2RGB);

        imgTemp = QImage(matTemp.data, matTemp.cols, matTemp.rows, matTemp.step, QImage::Format_RGB888).copy();
        //emit关键字用于发出信号,当发送信号时,imgTemp信息也会一并发出
        emit sigSendCurImg(imgTemp);
        msleep(20);
    }


}

void ThreadGetCamPic::objectDetection(const cv::Mat& frame)
{
    YOLO yolo_model(yolo_nets);
    yolo_model.detect(frame);
    //BGR转为RGB
    cvtColor(frame, frame, cv::COLOR_BGR2RGB);
    QImage imgTemp;
    imgTemp = QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888).copy();
    //
    emit sendDetectionRes(imgTemp);
    msleep(20);
}