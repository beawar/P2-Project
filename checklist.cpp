#include "checklist.h"
#include <QStandardItem>

CheckList::CheckList(Squadra *s, QWidget *parent) :
    QWidget(parent), squadra(s)
{
    if(squadra){
        for(int i=0; i<squadra->size(); ++i){
            checkBox[i] = new QCheckBox(squadra->at(i)->getInfo());
            connect(checkBox[i], SIGNAL(clicked()), this, SLOT(checkItem(i)));

        }
    }
}

void CheckList::checkItem(int index){
    squadra->at(index)->setChecked(checkBox[index]->isChecked());
}

