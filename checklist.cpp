#include "checklist.h"
#include <QVBoxLayout>
#include "squadremodel.h"

CheckList::CheckList(Squadra *s, QObject *parent) :
    QStringListModel(parent), squadra(s)
{
    if(squadra){
        for(int i=0; i<squadra->size(); ++i){
            strList<<(squadra->at(i)->getInfo());
        }
    }
    setStringList(strList);
}

Qt::ItemFlags CheckList::flags(const QModelIndex &index) const{
    if(index.isValid()){
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemNeverHasChildren;
    }
}

QVariant CheckList::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    else if(role == Qt::CheckStateRole){
        return squadra->at(index.row())->isChecked();
    }
    else{
        return QStringListModel::data(index, role);
    }
}

bool CheckList::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid() || role == Qt::CheckStateRole){
        return false;
    }
    else if(value == Qt::Checked){
        squadra->at(index.row())->setChecked(true);
        return true;
    }
    else if(value == Qt::Unchecked){
        squadra->at(index.row())->setChecked(false);
        return true;
    }
    else{
        return false;
    }

}

void CheckList::createList(Squadra *s){
    if(s){
        strList.clear();
        squadra = s;
        for(int i=0; i<squadra->size(); ++i){
            strList.push_back(squadra->at(i)->getInfo());
        }
        setStringList(strList);
    }
}

