#ifndef MOUSEHOOK_H
#define MOUSEHOOK_H
#include<windows.h>
#include <QObject>
class MouseHook:public QObject
{
public:
    MouseHook();
    ~MouseHook();
public:
    //钩子函数，处理键盘事件
    static LRESULT CALLBACK MouseHookEvent(int nCode, WPARAM wParam,
                                         LPARAM lParam);

    //设置回调函数，可以从外部设置，这样keyHookEvent处理的时候可以执行这个回调
    void SetMouseOnCallBack( void(*func)(int,int));
    void SetMouseOffCallBack( void(*func)(int,int));
    void SetMouseMoveCallBack( void(*func)(int,int));
private:
    static HHOOK mouse_hook_;//hook对象
    static void(*m_OnFunc)(int,int) ;//按下的回调,int代表键码
    static void(*m_OffFunc)(int,int) ;//抬起的回调,int代表键码
    static void(*m_MoveFunc)(int,int) ;//抬起的回调,int代表键码
};

// class QMouseEvent;
// class QWheelEvent;

/**
 *  全局鼠标事件单例信号类
 */
// class GlobalMouseEvent : public QObject
// {
//     Q_OBJECT
// public:
//     static GlobalMouseEvent* getInstance()
//     {
//         static GlobalMouseEvent mouseEvent;
//         return &mouseEvent;
//     }

//     static bool installMouseEvent();      // 安装全局鼠标事件监听器
//     static bool removeMouseEvent();       // 卸载全局鼠标事件监听器

// signals:
//     /**
//      * @brief 由于传递的是指针，为了保证不会出现内存泄露，需要在槽函数中delete。
//      *        建议此信号只绑定一次，因为如果绑定多次可能会出现一个槽函数里把信号delete了，另外一个槽函数还在使用，出现野指针，或者多个槽函数多次delete
//      */
//     void mouseEvent(QMouseEvent* event);
//     void wheelEvent(QWheelEvent* event);

// private:
//     GlobalMouseEvent(){}
// };

#endif // MOUSEHOOK_H
