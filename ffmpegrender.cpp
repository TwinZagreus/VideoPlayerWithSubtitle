#include "ffmpegrender.h"




FfmpegRender::FfmpegRender()
{

}

AVFrame *FfmpegRender::getFirstFrame(const char *filePath, int frameIndex)
{
    AVFormatContext* fmtCtx = nullptr;
    // 打开视频文件，并将相关信息存储在 AVFormatContext 结构体中
    avformat_open_input(&fmtCtx, filePath, NULL, NULL);
    // 读取媒体文件的流信息，填充 AVFormatContext 结构体
    avformat_find_stream_info(fmtCtx, NULL);


    //这个部分是用于查找视频流并为其分配解码器上下文。
    //循环遍历 AVFormatContext 中的流，检查每个流的类型是否为视频流。
    //如果是视频流，则查找相应的解码器（根据流中的编解码器ID），分配解码器上下文，并将流的参数复制到解码器上下文中。
    int videoStreamIndex;
    AVCodecContext* vcodecCtx = nullptr;
    for (int i = 0; i < fmtCtx->nb_streams; i++) {
        AVStream* stream = fmtCtx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            const AVCodec* codec = avcodec_find_decoder(stream->codecpar->codec_id);
            videoStreamIndex = i;
            vcodecCtx = avcodec_alloc_context3(codec);
            avcodec_parameters_to_context(vcodecCtx, fmtCtx->streams[i]->codecpar);
            avcodec_open2(vcodecCtx, codec, NULL);
        }
    }

    int n = 0; // 用于计数处理的帧数
    while (1) {
        AVPacket* packet = av_packet_alloc();
        int ret = av_read_frame(fmtCtx, packet);
        if (ret == 0 && packet->stream_index == videoStreamIndex) {
            ret = avcodec_send_packet(vcodecCtx, packet);
            if (ret == 0) {
                AVFrame* frame = av_frame_alloc();
                ret = avcodec_receive_frame(vcodecCtx, frame);
                if (ret == 0) {
                    n++;
                    if (n == frameIndex) {
                        av_packet_unref(packet);
                        avcodec_free_context(&vcodecCtx);
                        avformat_close_input(&fmtCtx);
                        return frame;
                    }
                    else {
                        av_frame_unref(frame);
                    }
                }
                else if (ret == AVERROR(EAGAIN)) {
                    av_frame_unref(frame);
                    continue;
                }
            }
        }

        av_packet_unref(packet);
    }
}
