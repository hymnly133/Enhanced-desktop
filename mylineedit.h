#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>


class MyLineEdit : public QWidget
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = nullptr);
    ~MyLineEdit();

public:
    //设置文本和获取文本的方法
    void setLabelInfo(QString s);
    void setText(QString s);
    QString labelInfo();
    QString text();

private:
    QLabel *m_label;
    QLineEdit *m_lineEidt;
    QHBoxLayout *m_layout;
    //初始化内部控件
    void init();
};
#endif // MYLINEEDIT_H
