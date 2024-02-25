#ifndef ASSRENDER_H
#define ASSRENDER_H

#include <QScopedPointer>
#include <QObject>
#include <QImage>


extern "C" {
#include <ass/ass.h>
}

#include "assdata.h"


struct AssRenderLabel {
    QImage _labelImage;     // 字幕label
    int _x;          // 位置x
    int _y;          // 位置y
};

class AssRender: public QObject
{
public:
    explicit AssRender(char * assFilePath, QObject *parent = nullptr);
    ~AssRender() override;

    void setSize (int frame_w, int frame_h);
    ASS_Image * renderFrameInMoment(long long now = 0);

    AssRenderLabel assImageToQImage(const ASS_Image *image);


    const char* subtitle = "D:\\train\\c++\\VideoPlayerWithSubtitle\\subtitle.ass";


private :
    class AssPrivate;
    QScopedPointer<AssPrivate> d_ptr;
    void commentedOut();
};

#endif // ASSRENDER_H
