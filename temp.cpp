#include "temp.h"
#include "ui_temp.h"

Temp::Temp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Temp)
{
    ui->setupUi(this);

    //    QStringList app;
    //    app.append("aaaa");
    //    app.append("bbbb");

    //    for(QString & item:app){
    //        item =item+"sss";
    //    }

    //    for(const QString & item:app){
    //        item =item+"gjhj";
    //        qDebug()<<item;
    //    }


    //    // 打开文件选择窗口
    //    QString filePath =  QFileDialog::getOpenFileName(nullptr, "选择文件", QDir::homePath(), "All Files (*)");

    //    // 输出选择的文件路径
    //    if (!filePath.isEmpty()) {
    //        qDebug() << "Selected file:" << filePath;
    //    } else {
    //        qDebug() << "No file selected.";
    //    }

    //    QFileInfo fileInfo(filePath);
    //    QString name = fileInfo.fileName();

    //    int lastDotIndex = name.lastIndexOf('.');
    //    if (lastDotIndex != -1) {
    //        // 截取"."右边的所有字符
    //        qDebug() << "Original String: " << name;
    //        name = name.left(lastDotIndex);
    //        qDebug() << "Right of Last Dot: " << name;
    //    } else {
    //        qDebug() << "No dot found in the string.";
    //    }
    //    qDebug()<<__FUNCTION__<<__LINE__<<"fileInfo.baseName():"<<name;



    //    QHBoxLayout * work = new QHBoxLayout(this);
    //    QLabel * showTi = new QLabel(name,this);
    //    showTi->setFixedWidth(500);
    //    work->addWidget(showTi);


}

Temp::~Temp()
{
    delete ui;
}
