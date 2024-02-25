#include "mainuserinterface.h"
#include "ui_mainuserinterface.h"


#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include <QMediaMetaData>
#include <QFileDialog>
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
    _player = new QMediaPlayer(this);
    _videoWidget = new QVideoWidget(this);

    layout->addWidget(_videoWidget);
    // 设置视频输出到视频小部件
    _player->setVideoOutput(_videoWidget);
    // 加载并播放视频文件
    QString filePath = "D:/000/h.mp4";
    _player->setSource(QUrl::fromLocalFile(filePath));
    _player->play();
//    player->setPosition(10);
//    player->pause();


    QPushButton * CHANGEGsource = new QPushButton();
    connect(CHANGEGsource, &QPushButton::clicked, [this]() {
        // 打开文件选择对话框
        QString filePath = QFileDialog::getOpenFileName(this, "Open File", "", "All Files (*);;Text Files (*.txt)");

        // 检查用户是否选择了文件
        if (!filePath.isEmpty()) {
            // 用户选择了文件，执行你需要的操作
            qDebug() << "Selected file:" << filePath;
            _player->setSource(QUrl::fromLocalFile(filePath));
            _player->play();
            // 例如，你可以在这里加载文件内容
        }
    });

    layout->addWidget(CHANGEGsource);

    createOverlayDialog();
}

MainUserInterface::~MainUserInterface()
{
    delete ui;
}

void MainUserInterface::createOverlayDialog()
{
  // 创建一个悬浮窗口
    _overlayDialog = new QDialog(this); // 将 QVideoWidget 作为父窗口
    _overlayDialog->setAttribute(Qt::WA_TranslucentBackground);
    _overlayDialog->setWindowFlags(_overlayDialog->windowFlags() | Qt::FramelessWindowHint | Qt::WindowDoesNotAcceptFocus );

    // 创建一个 QLabel 作为悬浮窗口的内容
    _overlayLabel = new MultiPixmapLabel(_overlayDialog);
    _overlayLabel->setStyleSheet("background-color: rgba(255, 255, 255, 100);"); // 设置半透明背景
    _overlayLabel->setFixedSize(600,600);

    AssRender test("D:/000/stantass.ass");
    test.setSize(600,600);
    ASS_Image *img = test.renderFrameInMoment(6000);


    int n = 1;
    while(img){
        AssRenderLabel arl = test.assImageToQImage(img);
        _overlayLabel ->addPixmap(arl);
        img = img->next;
        n++;
    }


    // 创建一个布局并添加 QLabel
    _overlayLayout = new QVBoxLayout(_overlayDialog);
    _overlayLayout->addWidget(_overlayLabel);
    _overlayDialog->setLayout(_overlayLayout);

    // 显示悬浮窗口
    _overlayDialog->show();
}

void MainUserInterface::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    qDebug()<<this->pos();
    _overlayDialog->move(this->pos().x(), this->pos().y());
}

void MainUserInterface::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    qDebug()<<this->pos();
    _overlayDialog->move(this->pos().x(), this->pos().y());
}

void MainUserInterface::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);
    qDebug()<<this->pos();
    _overlayDialog->move(this->pos().x(), this->pos().y());

    // 获取所有元数据
//    QMediaMetaData metaData = _player->metaData();
//    QVariant frameRate =metaData.value(QMediaMetaData::Key::VideoFrameRate);
//    QVariant bitRate  = metaData.value(QMediaMetaData::Key::VideoBitRate);

//    qDebug()<<"frameRate"<<frameRate;
//    qDebug()<<"bitRate"<<bitRate;

}
