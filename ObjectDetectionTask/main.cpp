#include "ObjectDetectionTask.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ObjectDetectionTask w;
    w.show();
    return a.exec();
}
