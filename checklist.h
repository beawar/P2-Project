#ifndef CHECKLIST_H
#define CHECKLIST_H

#include <QWidget>
#include <QCheckBox>
#include <QScrollArea>
#include "squadra.h"

class CheckList : public QWidget
{
    Q_OBJECT
private:
    Squadra* squadra;
    QCheckBox* checkBox[];
    QScrollArea* scrollArea;

public:
    explicit CheckList(Squadra* s, QWidget *parent = 0);

private slots:
    void checkItem(int index);

};

#endif // CHECKLIST_H
