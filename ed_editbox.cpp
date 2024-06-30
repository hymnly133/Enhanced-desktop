#include "ed_editbox.h"
#include "mainwindow.h"
#include "qmessagebox.h"
#include"qcheckbox.h"
#include"QSlider"

ED_EditBox::ED_EditBox(QWidget *parent)
    : ED_Unit(parent,3,2)
{
    type = Unit;
    settings= new QHBoxLayout(this);

    overall = new QVBoxLayout(this);
    settings->addLayout(overall);

    QCheckBox *checkBox1 = new QCheckBox(this);             //创建QCheckBox对象
    checkBox1->setText("背景透视");
    checkBox1->setChecked(enable_background_transparent);
    overall->addWidget(checkBox1);
    connect(checkBox1, &QCheckBox::clicked, this, [](bool checked) {
        pmw->setTransparent(checked);
    });

    QCheckBox *checkBox2 = new QCheckBox(this);
    checkBox2->setText("背景模糊");
    checkBox2->setChecked(enable_background_blur);
    overall->addWidget(checkBox2);
    connect(checkBox2, &QCheckBox::clicked, this, [](bool checked) {
        pmw->setBlur(checked);
    });

    QCheckBox *checkBox3 = new QCheckBox(this);
    checkBox3->setText("特效追踪");
    checkBox3->setChecked(enable_light_track);
    overall->addWidget(checkBox3);
    connect(checkBox3, &QCheckBox::clicked, this, [](bool checked) {
        enable_light_track = checked;
    });

    paint =  new QVBoxLayout(this);
    settings->addLayout(paint);

    QCheckBox *checkBox4 = new QCheckBox(this);
    checkBox4->setText("绘制边框");
    checkBox4->setChecked(ShowSide);
    paint->addWidget(checkBox4);
    connect(checkBox4, &QCheckBox::clicked, this, [](bool checked) {
        ShowSide = checked;
    });


    QCheckBox *checkBox5 = new QCheckBox(this);
    checkBox5->setText("绘制矩形");
    checkBox5->setChecked(ShowRect);
    paint->addWidget(checkBox5);
    connect(checkBox5, &QCheckBox::clicked, this, [](bool checked) {
        ShowRect = checked;
    });


    QCheckBox *checkBox6 = new QCheckBox(this);
    checkBox6->setText("绘制光效");
    checkBox6->setChecked(ShowLight);
    paint->addWidget(checkBox6);
    connect(checkBox6, &QCheckBox::clicked, this, [](bool checked) {
        ShowLight = checked;
    });

    QCheckBox *checkBox7 = new QCheckBox(this);
    checkBox7->setText("大图标填充");
    checkBox7->setChecked(image_alpha);
    overall->addWidget(checkBox7);
    connect(checkBox7, &QCheckBox::clicked, this, [](bool checked) {
        image_alpha = checked;
    });

    QSlider* scale_Slider = new QSlider(this);
    scale_Slider->setRange(0, 100);
    connect(scale_Slider, &QSlider::valueChanged, this, [](int val) {
        pmw->setScale(1.0*val/100);
    });
    settings->addWidget(scale_Slider);

    QPushButton *button = new QPushButton("选择背景", this);
    paint->addWidget(button);
    connect(button, &QPushButton::clicked, this, []() {
        // 点击按钮后的处理逻辑
        pmw->onSelectBackground();
    });
}
