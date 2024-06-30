#include "videopreview.h"

VideoPreview::VideoPreview(QWidget *parent) :
    QWidget(parent),
    mediaPlayer(new QMediaPlayer(this)),
    videoWidget(new QVideoWidget(this))
{
    mediaPlayer->setVideoOutput(videoWidget);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    setLayout(layout);
}

VideoPreview::~VideoPreview()
{
    delete mediaPlayer;
    delete videoWidget;
}

void VideoPreview::playVideo(const QString &filePath)
{
    mediaPlayer->setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer->play();
}
