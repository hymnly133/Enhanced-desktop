#include "ed_block.h"
#include "QWidget"
#include"QProcess"
#include "qboxlayout.h"
#include"SysFunctions.h"
#include "qfileinfo.h"
#include "qlabel.h"
#include"QDebug"
#include"QUrl"
#include"QDesktopServices"
#include"QTextCodec"
#include "qpainter.h"
#include"QGraphicsDropShadowEffect"
int ED_BLOCK::default_size = 48;
ED_BLOCK::ED_BLOCK(QWidget *parent, QPixmap image, QString _name, QString _cmd, int sizex, int sizey)
    : ED_Unit(parent,sizex,sizey),previewWidget(new FilePreviewWidget(this))
{
    type =Block;
    cmd = _cmd;
    cmd = QString("file:///")+cmd;
    name = _name;
    // 初始化内部组件
    vl = new QVBoxLayout(this);
    vl->setContentsMargins(5,5,5,5);
    vl->addSpacing(0);


    gv = new PictureBox(this,1.0);
    lb = new QLabel(this);
    lb->adjustSize();

    // 显示图标
    gv->setMode(PictureBox::FIX_SIZE_CENTRED);
    double defaultRatio = (double)default_size/image.size().width();
    iconmap=image;
    setMainColor(pixmapMainColor(iconmap,sleep_color_ratio));

    (( QGraphicsDropShadowEffect*)graphicsEffect())->setColor(mainColor);
    gv->setImage(image,1.0,defaultRatio);
    gv->setBackground(QBrush (QColor(0,0,0,0)));
    vl->setAlignment(Qt::AlignHCenter);

    // 添加布局
    vl->addStretch();
    vl->addWidget(gv);
    vl->setAlignment(gv,Qt::AlignHCenter);
    vl->addWidget(lb);
    vl->setAlignment(lb,Qt::AlignHCenter);
    vl->addStretch();

    // 显示名字
    lb->setAlignment(Qt::AlignHCenter);
    lb->setFont(QFont("MiSans",10,40));
    lb->setFixedWidth(width()-5);

    lb->setText(elidedLineText(lb,3,name));
    QGraphicsDropShadowEffect* effect0 = new QGraphicsDropShadowEffect;
    auto tem = mainColor;
    tem.setAlpha(icon_shadow_alpha);
    effect0->setColor(tem);
    effect0->setBlurRadius(10);   //模糊半径
    effect0->setOffset(10);;      //偏移量
    lb->setGraphicsEffect(effect0);

    QGraphicsDropShadowEffect* effect1 = new QGraphicsDropShadowEffect;
    effect1->setColor(tem);
    effect1->setBlurRadius(icon_shadow_blur_radius);   //模糊半径
    effect1->setOffset(0,0);      //偏移量
    gv->setGraphicsEffect(effect1);



    // 给当前窗口添加QAction对象
}

void ED_BLOCK::double_click_action(){
    //最终双击执行
    ED_Unit::double_click_action();
    qDebug("cmd = %s",qPrintable(cmd));
    QDesktopServices::openUrl(QUrl(cmd));
}

void ED_BLOCK::update_after_resize(){
    ED_Unit::update_after_resize();
    lb->setFixedWidth(width()-5);
    lb->setText(elidedLineText(lb,4,name));
}
void ED_BLOCK::mouse_enter_action(){
    ED_Unit::mouse_enter_action();
    mainColor = pixmapMainColor(iconmap,active_color_ratio);

    //文件预览
    QFileInfo fileInfo(cmd.mid(8)); // 去掉 "file:///"
    if (fileInfo.isFile() && (fileInfo.suffix() == "txt" || fileInfo.suffix() == "png")) {
        if (fileInfo.suffix() == "txt") {
            QFile file(fileInfo.filePath());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                in.setCodec("UTF-8"); // 新增：设置为UTF-8编码
                QString content = in.readAll();
                file.close();

                // 如果UTF-8读取失败，尝试其他编码
                if (content.contains(QChar(0xFFFD))) { // 检查是否有替换字符
                    file.open(QIODevice::ReadOnly | QIODevice::Text);
                    in.setCodec("GBK"); // 尝试GBK编码
                    content = in.readAll();
                    file.close();
                }

                // 限制预览内容的长度
                if (content.length() > 1000) {
                    content = content.left(1000) + "\n...";
                }

                previewWidget->setText(content);
            }
        } else if (fileInfo.suffix() == "png") {
            QImage image(fileInfo.filePath());
            previewWidget->setImage(image);
        }
        previewWidget->move(mapToGlobal(QPoint(0, height())));
        previewWidget->show();
    }
}

void ED_BLOCK::mouse_leave_action(){
    //最终移动执行
    ED_Unit::mouse_leave_action();

    mainColor = pixmapMainColor(iconmap,sleep_color_ratio);
    //文件预览
    previewWidget->hide();
}
void ED_BLOCK::paintEvent(QPaintEvent *event)
{
    ED_Unit::paintEvent(event);
    QColor alphaed = QColor(mainColor.red(),mainColor.green(),mainColor.blue(),aim_Alpha);
    paintRect(this,alphaed);
    paintLight(this,alphaed);
}
void ED_BLOCK::whenSimpleModeChange(bool val){
    ED_Unit::whenSimpleModeChange(val);
    lb->setVisible(!val);
}

void ED_BLOCK::whenScaleChange(float val){
    ED_Unit::whenSimpleModeChange(val);
    gv->setScale(val);
}
