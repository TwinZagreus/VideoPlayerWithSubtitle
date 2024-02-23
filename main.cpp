#include "mainwindow.h"

#include <QApplication>
#include <QFile>

extern "C" {
#include "libass/ass.h"
#include "libass/ass_types.h"
}

#include "AssRender/assrender.h"
#include "UI/mainuserinterface.h"



// 将 ASS_Image 结构转换为 QImage 对象
QImage assImageToQImageSecond(const ASS_Image *image) {
    if (!image){
        return QImage(); // 返回空 QImage
    }
    if (image->w <= 0 || image->h <= 0){
        return QImage(); // 如果宽度或高度为0，返回空 QImage
    }
    // 从ASS_Image的color成员获取RGBA值
    uint32_t rgba = image->color;
    uint red = (rgba >> 24) & 0xFF; // 获取红色分量
    uint green = (rgba >> 16) & 0xFF; // 获取绿色分量
    uint blue = (rgba >> 8) & 0xFF; // 获取取蓝色分量


    QImage qimage(image->w, image->h, QImage::Format_ARGB32);
    uint32_t *data = (uint32_t *)qimage.bits();

    switch (image->type) {
    case ASS_Image::IMAGE_TYPE_CHARACTER:
        qDebug()<<"character rgb:"<<red<<green<<blue;
        // 字符图像，直接使用color字段作为颜色
        for (int y = 0; y < image->h; ++y) {
            for (int x = 0; x < image->w; ++x) {
                uint index = y * image->stride + x;
                uint alpha = image->bitmap[index];
                data[y * image->w + x] = qRgba(
                    red, // R
                    green, // G
                    blue,        // B
                    alpha              // A
                    );
            }
        }
        break;
    case ASS_Image::IMAGE_TYPE_OUTLINE:
        qDebug()<<"outline rgb:"<<red<<green<<blue;
        // 轮廓图像，需要根据轮廓颜色和alpha值来设置像素
        // ...（处理轮廓图像的代码，类似于上面的示例）
        for (int y = 0; y < image->h; ++y) {
            for (int x = 0; x < image->w; ++x) {
                uint index = y * image->stride + x;
                uint alpha = image->bitmap[index];
                //uint alphaValue = (alpha * (red + green + blue) / 3) / 255; // 简单的灰度转换
                // 设置像素值
                data[y * image->w + x] = qRgba(red, green, blue, alpha);
            }
        }
        break;
    case ASS_Image::IMAGE_TYPE_SHADOW:
        qDebug()<<"shadow rgb:"<<red<<green<<blue;
        // 阴影图像，通常不需要处理，因为阴影通常在渲染时由视频播放器处理
        // 如果需要保存阴影图像，可以在这里添加处理逻辑
        for (int y = 0; y < image->h; ++y) {
            for (int x = 0; x < image->w; ++x) {
                uint index = y * image->stride + x;
                uint alpha = image->bitmap[index];
                //uint alphaValue = (alpha * (red + green + blue) / 3) / 255; // 简单的灰度转换
                // 设置像素值
                data[y * image->w + x] = qRgba(red, green, blue, alpha);
            }
        }
        break;
    default:
        // 如果有未知的图像类型，可以在这里处理
        break;
    }
    return qimage;
}

// 将 QImage 保存为本地 PNG 文件
void saveImageAsPng(const QImage &image, const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << file.errorString();
        return;
    }

    if (!image.save(&file, "PNG")) {
        qWarning() << "Failed to save image to" << filename;
        return;
    }

    qDebug() << "Image saved to" << filename;
}

// 示例函数，将 ASS_Image 结构保存为本地 PNG 文件
void saveAssImageAsPng(const ASS_Image *image, const QString &filename) {
    QImage qImage = assImageToQImageSecond(image);
    saveImageAsPng(qImage, filename);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    AssRender test("D:/000/stantass.ass");
//    test.setSize(600,600);
//    ASS_Image *img = test.renderFrameInMoment(6000);

//    int n = 1;
//    while(img){
//        QString fileName = "C:/Users/TTZ/Pictures/ass-test-"+QString::number(n)+".png";
//        saveAssImageAsPng(img, fileName);
//        img = img->next;
//        n++;
//    }


    MainUserInterface mui;
    mui.show();

    return a.exec();
}
