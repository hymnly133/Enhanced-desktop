#ifndef MOUSEHOOK_H
#define MOUSEHOOK_H
#include<windows.h>
#include <functional>
class MouseHook
{
public:
    MouseHook();
public:
    //钩子函数，处理键盘事件
    static LRESULT CALLBACK keyHookEvent(int nCode, WPARAM wParam,
                                         LPARAM lParam);

    //设置回调函数，可以从外部设置，这样keyHookEvent处理的时候可以执行这个回调
    void SetKeyPressCallBack( std::function<void(int)> func);
    void SetKeyReleaseCallBack( std::function<void(int)> func);
private:
    static HHOOK keyborard_hook_;//hook对象
    static std::function<void(int)> m_pressFunc;//按下的回调,int代表键码
    static std::function<void(int)> m_releaseFunc;//抬起的回调,int代表键码
};

#endif // MOUSEHOOK_H
