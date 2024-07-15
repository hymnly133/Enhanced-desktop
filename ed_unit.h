#ifndef ED_UNIT_H
#define ED_UNIT_H
#include "qgraphicseffect.h"
#include "qpropertyanimation.h"
#include "style.h"
#include <QWidget>
#include<qlabel.h>
#include <QVariant>
class ED_Layout;

class ED_Unit : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int colorAlpha MEMBER colorAlpha NOTIFY alpha_changed )
    Q_PROPERTY(QColor mainColor MEMBER mainColor NOTIFY mainColor_changed WRITE setMainColor)
    Q_PROPERTY(double scale MEMBER scale NOTIFY scale_changed WRITE setScale)
    Q_PROPERTY(double scaleFix MEMBER scaleFix NOTIFY scaleFix_changed WRITE setScaleFix)
public:
    enum ED_TYPE {Unit,Container};
    ED_TYPE type = Unit;
    ED_Layout* edlayout;
    bool moving = false;
    bool premove = false;
    bool showRect = true;
    bool showLight = true;
    bool showSide = true;
    bool onmouse = false;
    bool deepColor = false;
    bool dark = false;
    double scaleFix = 1.0;
    double scale = 1.0;
    QPoint relativeP;
    QColor mainColor;
    QPropertyAnimation* alphaAnimation;
    QPropertyAnimation* scaleFixAnimation;
    int sizeX = 1;
    int sizeY = 1;
    int ind;
    int aim_alpha(){
        if(onmouse){
            if(deepColor) return active_alpha_deep;
            else return active_alpha;
        }
        else{
            if(deepColor) return sleep_alpha_deep;
            else return sleep_alpha;
        }
    }
    double aim_scaleFix(){
        if(onmouse){
            return scale_fix_ratio;
        }
        else{
            return 1.0;
        }
    }
    int colorAlpha;
    bool alwaysShow = false;
    bool simpleMode = false;

    int indX = -1;
    int indY = -1;


    QGraphicsDropShadowEffect* shadow_main_color;

    explicit ED_Unit();
    explicit ED_Unit(QWidget *parent,int sizex,int sizey);
    ED_Unit(const ED_Unit &other)
        :ED_Unit(other.parentWidget(),other.sizeX,other.sizeY)
    {

    }
    void removeFromLayout();

    virtual void setupMenu();


    virtual void update_after_resize();
    virtual void double_click_action();
    virtual void single_click_action();
    virtual void mouse_move_action();
    virtual void mouse_release_action();
    virtual void mouse_enter_action();
    virtual void mouse_leave_action();
    virtual void setBlockSize(int w,int h);


    virtual void whenSimpleModeChange(bool val);
    virtual void whenScaleChange(double val);
    virtual void whenMainColorChange(QColor val);


    virtual void ed_update();

    virtual QJsonObject to_json();
    virtual void load_json(QJsonObject rootObject);

    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *) override;                      //进入QWidget瞬间事件
    void leaveEvent(QEvent *) override;                      //离开QWidget瞬间事件
    void paintEvent(QPaintEvent *event) override;
    void changeSimpleMode();

    void setMainColor(QColor color);
    virtual void setSimpleMode(bool);
    virtual void setScale(double val);
    virtual void setScaleFix(double val);
    QColor mainColor_Alphaed();


    void updata_animation();

public: signals:
    void alpha_changed(int);
    void mainColor_changed(QColor);
    void scale_changed(double);
    void scaleFix_changed(double);

};
Q_DECLARE_METATYPE(ED_Unit);

#endif // ED_UNIT_H
