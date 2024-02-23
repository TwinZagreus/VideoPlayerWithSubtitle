#include "assrender.h"

#include <QDebug>


void msg_callback(int level, const char *fmt, va_list va, void *data)
{
    Q_UNUSED(data)
    switch (level) {
    case 0: qCritical() << "libass:" << QString::vasprintf(fmt, va); break;
    case 1:
    case 2:
    case 3: qWarning() << "libass:" << QString::vasprintf(fmt, va); break;
    case 4:
    case 5:
    case 6: qInfo() << "libass:" << QString::vasprintf(fmt, va); break;
    case 7:
    default: qDebug() << "libass:" << QString::vasprintf(fmt, va); break;
    }
}

void print_font_providers(ASS_Library *ass_library)
{
    QMap<ASS_DefaultFontProvider, QString> font_provider_maps
        = {{ASS_FONTPROVIDER_NONE, "None"},
           {ASS_FONTPROVIDER_AUTODETECT, "Autodetect"},
           {ASS_FONTPROVIDER_CORETEXT, "CoreText"},
           {ASS_FONTPROVIDER_FONTCONFIG, "Fontconfig"},
           {ASS_FONTPROVIDER_DIRECTWRITE, "DirectWrite"}};

    ASS_DefaultFontProvider *providers;
    size_t providers_size = 0;
    ass_get_available_font_providers(ass_library, &providers, &providers_size);
    qDebug("Available font providers (%zu): ", providers_size);
    for (int i = 0; i < static_cast<int>(providers_size); i++) {
        qDebug() << font_provider_maps[providers[i]];
    }
    free(providers);
}

class AssRender::AssPrivate
{
public:
    explicit AssPrivate(char * assFilePath,AssRender *q)
        : q_ptr(q)
    {
        qInfo() << "ass_library_version: " << ass_library_version();

        //初始化ass库
        _assLibrary = ass_library_init();
        if (!_assLibrary) {
            qDebug()<<("ass_library_init failed!\n");
        }

        //列出并打印出当前libass库支持的所有字体提供者
        print_font_providers(_assLibrary);

        //捕获并处理任何输出的消息
        ass_set_message_cb(_assLibrary, msg_callback, nullptr);

        //控制 libass 是否应该尝试从字幕文件中提取字体信息
        ass_set_extract_fonts(_assLibrary, 1);

        _assRenderer = ass_renderer_init(_assLibrary);
        if (!_assRenderer) {
            printf("ass_renderer_init failed!\n");
        }

        //设置字幕渲染器的字体配置的函数
        ass_set_fonts(_assRenderer, nullptr, nullptr, 1, nullptr, 1);

        _accTrack = ass_read_file (_assLibrary, assFilePath, NULL);
        if (!_accTrack) {
            printf("track init failed!\n");
        }
    }
    ~AssPrivate()
    {
        ass_free_track(_accTrack);
        ass_renderer_done(_assRenderer);
        ass_clear_fonts(_assLibrary);
        ass_library_done(_assLibrary);
    }

    AssRender * q_ptr;

    ASS_Library * _assLibrary;
    ASS_Renderer * _assRenderer;
    ASS_Track * _accTrack ;
};


AssRender::AssRender(char * assFilePath,QObject *parent):
    QObject{parent},
    d_ptr(new AssPrivate(assFilePath,this))
{
    subtitle = assFilePath;
}

AssRender::~AssRender()
{

}

void AssRender::setSize(int frame_w, int frame_h)
{
    ass_set_storage_size(d_ptr->_assRenderer, frame_w, frame_h);
    ass_set_frame_size(d_ptr->_assRenderer, frame_w, frame_h);
}

ASS_Image * AssRender::renderFrameInMoment(long long now)
{
    return ass_render_frame(d_ptr->_assRenderer, d_ptr->_accTrack, now, NULL);
}

void AssRender::commentedOut()
{
    //    ASS_Style defaultStyle = {
    //        Name: "Default", // 字体名称，可以为空字符串
    //        FontName: "Arial", // 字体名称，这里使用Arial作为示例
    //        FontSize: 24.0, // 字体大小
    //        PrimaryColour: 0xFFF0000, // 主要颜色，这里使用白色
    //        SecondaryColour: 0xFFFF0000, // 次要颜色，这里使用黑色
    //        OutlineColour: 0xFFFF0000, // 轮廓颜色，这里使用黑色
    //        BackColour: 0x0000FF00, // 背景颜色，这里使用透明
    //        Bold: 1, // 是否加粗，1为加粗
    //        Italic: 0, // 是否斜体，0为不斜体
    //        Underline: 0, // 是否下划线，0为不下划线
    //        StrikeOut: 0, // 是否删除线，0为不删除
    //        ScaleX: 1.0, // 水平缩放比例
    //        ScaleY: 1.0, // 垂直缩放比例
    //        Spacing: 0.0, // 字符间距
    //        Angle: 0.0, // 字体旋转角度
    //        BorderStyle: 1, // 边框样式，1为实线
    //        Outline: 2.0, // 轮廓宽度
    //        Shadow: 2.0, // 阴影宽度
    //        Alignment: 5, // 水平和垂直对齐方式
    //        MarginL: 10, // 左边距
    //        MarginR: 10, // 右边距
    //        MarginV: 10, // 上边距
    //        Encoding: 0, // 字符编码
    //        treat_fontname_as_pattern: 0, // 字体名称处理方式
    //        Blur: 0.0, // 模糊效果
    //        Justify: ASS_JUSTIFY_CENTER // 文本对齐方式
    //    };
    //    // 初始化样式，如上面所示

    ////    ass_set_selective_style_override_enabled(ass_renderer, ASS_OverrideBits::ASS_OVERRIDE_BIT_COLORS);

    ////    ass_set_selective_style_override(ass_renderer, &defaultStyle);


    //    ass_process_force_style(track);

}





