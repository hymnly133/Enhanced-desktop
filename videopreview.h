#ifndef VIDEOPREVIEW_H
#define VIDEOPREVIEW_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVBoxLayout> // 确保包含 QVBoxLayout 的头文件

class VideoPreview : public QWidget
{
    Q_OBJECT
public:
    explicit VideoPreview(QWidget *parent = nullptr);
    ~VideoPreview();

    void playVideo(const QString &filePath);

private:
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QVBoxLayout *layout; // 新增 QVBoxLayout 成员
};

#endif // VIDEOPREVIEW_H
