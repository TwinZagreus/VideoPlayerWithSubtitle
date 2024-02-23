#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QUrl>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "ffmpegrender.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
extern "C" {
#include "libass/ass.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _showLabel(new QLabel(this))
    , _swsCtx(nullptr)
{
    ui->setupUi(this);

    FfmpegRender render;
    QString filePath = "D:/000/h.mp4";
    AVFrame* firstframe = render.getFirstFrame(filePath.toUtf8().constData(), 10);

    showFrame(firstframe);

    _showLabel->show();
}

MainWindow::~MainWindow()
{
    delete ui;
    if (_swsCtx){
        sws_freeContext(_swsCtx);
    }

}

void MainWindow::showFrame(AVFrame *frame)
{
    if (!frame) return;

    if (!_swsCtx) {
        _swsCtx = sws_getContext(frame->width, frame->height, AV_PIX_FMT_YUV420P,
                                frame->width, frame->height, AV_PIX_FMT_RGB24,
                                SWS_BILINEAR, nullptr, nullptr, nullptr);
        if (!_swsCtx) return;
    }

    if (!_showLabel->pixmap().isNull()){
        _showLabel->setPixmap(QPixmap());
    }


    uint8_t* dest[4] = {0};
    int linesize[4] = {0};
    int width = frame->width;
    int height = frame->height;

    // 分配输出缓冲区
    int ret = av_image_alloc(dest, linesize, width, height, AV_PIX_FMT_RGB24, 1);

    qDebug()<<"av_image_alloc ret = "<<ret;

    // 将YUV图像转换成RGB格式
    sws_scale(_swsCtx, frame->data, frame->linesize, 0, frame->height, dest, linesize);

    // 将RGB数据转换成QImage
    QImage image(dest[0], width, height, linesize[0], QImage::Format_RGB888);

    // 显示图像
    _showLabel->setGeometry(0,0,width,height);
    _showLabel->setPixmap(QPixmap::fromImage(image));

    // 释放输出缓冲区
    av_freep(&dest[0]);
}

