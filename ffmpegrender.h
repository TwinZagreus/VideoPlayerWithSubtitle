#ifndef FFMPEGRENDER_H
#define FFMPEGRENDER_H

extern "C" {
#include <libavcodec/avcodec.h>
#pragma comment(lib, "avcodec.lib")

#include <libavformat/avformat.h>
#pragma comment(lib, "avformat.lib")

#include <libavutil/imgutils.h>
#pragma comment(lib, "avutil.lib")

}


class FfmpegRender
{
public:
    FfmpegRender();
    AVFrame* getFirstFrame(const char* filePath, int frameIndex);

};

#endif // FFMPEGRENDER_H
