// #include "dsvideoplayer.h"
// #include <QDebug>
// #include <QResizeEvent>

// DSVideoPlayer::DSVideoPlayer(QWidget *parent) :
//     QWidget(parent),
//     graphBuilder(nullptr),
//     mediaControl(nullptr),
//     videoWindow(nullptr),
//     mediaEvent(nullptr),
//     mediaSeeking(nullptr)
// {
//     CoInitialize(nullptr);
// }

// DSVideoPlayer::~DSVideoPlayer()
// {
//     if (mediaControl) {
//         mediaControl->Release();
//     }
//     if (videoWindow) {
//         videoWindow->Release();
//     }
//     if (mediaEvent) {
//         mediaEvent->Release();
//     }
//     if (mediaSeeking) {
//         mediaSeeking->Release();
//     }
//     if (graphBuilder) {
//         graphBuilder->Release();
//     }
//     CoUninitialize();
// }

// bool DSVideoPlayer::loadFile(const QString &fileName)
// {
//     if (graphBuilder) {
//         graphBuilder->Release();
//         graphBuilder = nullptr;
//     }

//     HRESULT hr = CoCreateInstance(CLSID_FilterGraph, nullptr, CLSCTX_INPROC_SERVER,
//                                   IID_IGraphBuilder, (void**)&graphBuilder);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to create filter graph";
//         return false;
//     }

//     hr = graphBuilder->QueryInterface(IID_IMediaControl, (void**)&mediaControl);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to get media control";
//         return false;
//     }

//     hr = graphBuilder->QueryInterface(IID_IVideoWindow, (void**)&videoWindow);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to get video window";
//         return false;
//     }

//     hr = graphBuilder->QueryInterface(IID_IMediaEventEx, (void**)&mediaEvent);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to get media event";
//         return false;
//     }

//     hr = graphBuilder->QueryInterface(IID_IMediaSeeking, (void**)&mediaSeeking);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to get media seeking";
//         return false;
//     }

//     hr = graphBuilder->RenderFile(fileName.toStdWString().c_str(), nullptr);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to render file";
//         return false;
//     }

//     hr = videoWindow->put_Owner((OAHWND)this->winId());
//     if (FAILED(hr)) {
//         qDebug() << "Failed to set owner";
//         return false;
//     }

//     hr = videoWindow->put_WindowStyle(WS_CHILD | WS_CLIPSIBLINGS);
//     if (FAILED(hr)) {
//         qDebug() << "Failed to set window style";
//         return false;
//     }

//     resizeEvent(nullptr);
//     return true;
// }

// void DSVideoPlayer::play()
// {
//     if (mediaControl) {
//         mediaControl->Run();
//         qDebug() << "Video playing";
//     }
// }

// void DSVideoPlayer::pause()
// {
//     if (mediaControl) {
//         mediaControl->Pause();
//         qDebug() << "Video paused";
//     }
// }

// void DSVideoPlayer::stop()
// {
//     if (mediaControl) {
//         mediaControl->Stop();
//         qDebug() << "Video stopped";
//     }
// }

// void DSVideoPlayer::resizeEvent(QResizeEvent *event)
// {
//     if (videoWindow) {
//         videoWindow->SetWindowPosition(0, 0, width(), height());
//         qDebug() << "Video resized";
//     }
//     QWidget::resizeEvent(event);
// }
