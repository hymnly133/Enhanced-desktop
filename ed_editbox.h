#ifndef ED_EDITBOX_H
#define ED_EDITBOX_H

#include "ed_unit.h"
#include <QWidget>

class ED_EditBox : public ED_Unit
{
    Q_OBJECT
public:
    explicit ED_EditBox(QWidget *parent = nullptr);

signals:
};

#endif // ED_EDITBOX_H
