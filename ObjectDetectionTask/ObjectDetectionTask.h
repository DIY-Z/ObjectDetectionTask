#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ObjectDetectionTask.h"

class ObjectDetectionTask : public QMainWindow
{
    Q_OBJECT

public:
    ObjectDetectionTask(QWidget *parent = nullptr);
    ~ObjectDetectionTask();

private:
    Ui::ObjectDetectionTaskClass ui;
};
