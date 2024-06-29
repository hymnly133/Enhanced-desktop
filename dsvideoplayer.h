// #ifndef DSVIDEOPLAYER_H
// #define DSVIDEOPLAYER_H

// #include <dshow.h>
// #include <QObject>
// #include <QWidget>

// class DSVideoPlayer : public QWidget
// {
//     Q_OBJECT
// public:
//     explicit DSVideoPlayer(QWidget *parent = nullptr);
//     ~DSVideoPlayer();
//     bool loadFile(const QString &fileName);
//     void play();
//     void pause();
//     void stop();

// protected:
//     void resizeEvent(QResizeEvent *event) override;

// private:
//     IGraphBuilder *graphBuilder;
//     IMediaControl *mediaControl;
//     IVideoWindow *videoWindow;
//     IMediaEventEx *mediaEvent;
//     IMediaSeeking *mediaSeeking;
// };

// #endif // DSVIDEOPLAYER_H
