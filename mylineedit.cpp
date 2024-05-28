#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent):
    QWidget(parent)
{
    this->init();
}

MyLineEdit::~MyLineEdit()
{

}

void MyLineEdit::init()
{
    m_label = new QLabel();
    m_lineEidt = new QLineEdit();
    m_layout = new QHBoxLayout();

    //在这里可以设置组合控件内部的格式

    //简单设置下字体样式等
    m_label->setStyleSheet("color:rgb(128,128,128);font-family:'SimSun'");
    m_label->setObjectName("MS");
    m_lineEidt->setAlignment(Qt::AlignCenter);
    //固定Label的宽度，可以帮助对齐
    m_label->setFixedWidth(100);
    //将控件加入布局
    m_layout->addWidget(m_label);
    m_layout->addWidget(m_lineEidt);
    m_layout->setStretch(0,0);
    m_layout->setStretch(1,1);
    //设置内部无间隔
    setContentsMargins(0,0,0,0);
    //应用布局
    setLayout(m_layout);
}
//设置Label内容
void MyLineEdit::setLabelInfo(QString s)
{
    m_label->setText(s);
}
//设置输入框内容
void MyLineEdit::setText(QString s)
{
    m_lineEidt->setText(s);
}
//获取Label内容
QString MyLineEdit::labelInfo(){
    return m_label->text();
}
//获取输入框内容
QString MyLineEdit::text(){
    return m_lineEidt->text();
}
