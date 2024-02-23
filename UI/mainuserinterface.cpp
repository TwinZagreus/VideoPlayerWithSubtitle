#include "mainuserinterface.h"
#include "ui_mainuserinterface.h"

#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QDialog>

MainUserInterface::MainUserInterface(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUserInterface)
{
    ui->setupUi(this);

    // 创建一个布局并将视频小部件添加到其中
    QVBoxLayout *layout = new QVBoxLayout(ui->mainUI);
    // 设置窗口的布局
    ui->mainUI->setLayout(layout);

    // 创建一个视频播放器
    QMediaPlayer *player = new QMediaPlayer(this);
    QVideoWidget *videoWidget = new QVideoWidget(this);

    layout->addWidget(videoWidget);
    // 设置视频输出到视频小部件
    player->setVideoOutput(videoWidget);

    // 加载并播放视频文件
    QString filePath = "D:/000/h.mp4";
    player->setSource(QUrl::fromLocalFile(filePath));
    player->play();



  // 创建一个悬浮窗口
    overlayDialog = new QDialog(videoWidget); // 将 QVideoWidget 作为父窗口
    overlayDialog->setWindowFlags(overlayDialog->windowFlags() | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus );

    // 创建一个 QLabel 作为悬浮窗口的内容
    QLabel *overlayLabel = new QLabel("悬浮标签", overlayDialog);
    overlayLabel->setStyleSheet("background-color: rgba(255, 255, 255, 150);"); // 设置半透明背景

    // 创建一个布局并添加 QLabel
    QVBoxLayout *overlayLayout = new QVBoxLayout(overlayDialog);
    overlayLayout->addWidget(overlayLabel);
    overlayDialog->setLayout(overlayLayout);


    // 你可以根据需要调整位置

    // 显示悬浮窗口
    overlayDialog->show();


}

MainUserInterface::~MainUserInterface()
{
    delete ui;
}

void MainUserInterface::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    qDebug()<<this->pos();
    overlayDialog->move(this->pos().x(), this->pos().y());
}

void MainUserInterface::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    qDebug()<<this->pos();
    overlayDialog->move(this->pos().x(), this->pos().y());
}

void MainUserInterface::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);
    qDebug()<<this->pos();
    overlayDialog->move(this->pos().x()+100, this->pos().y()+100);
}
