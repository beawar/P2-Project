#include "checklist.h"
#include <QVBoxLayout>

CheckList::CheckList(Squadra *s, QObject *parent) :
    QStringListModel(parent), squadra(s)
{
    /*if(squadra){
        for(int i=0; i<squadra->size(); ++i){
            strList.append(squadra->at(i)->getInfo());
        }
    }
    setStringList(strList);*/
}

Qt::ItemFlags CheckList::flags(const QModelIndex &index) const{
    if(index.isValid()){
        return QStringListModel::flags(index) | Qt::ItemIsUserCheckable;
    }
    return QStringListModel::flags(index);
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

