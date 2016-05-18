#include "checklist.h"
#include <QVBoxLayout>
#include "squadremodel.h"

CheckList::CheckList(Squadra *s, bool checkable, QObject *parent) :
    QStringListModel(parent), squadra(s), checkableItems(checkable)
{
    if(squadra){
        for(int i=0; i<squadra->size(); ++i){
            strList.push_back(squadra->at(i)->getInfo());
            if(dynamic_cast<Portiere*>(squadra->at(i))){
                strList.push_back(tr(" (P)"));
            }
        }
    }
    setStringList(strList);
}

Qt::ItemFlags CheckList::flags(const QModelIndex &index) const{
    if(index.isValid()){
        if(itemsAreCheckable()){
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemNeverHasChildren;
        }
        else{
            return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemNeverHasChildren;
        }
    }
}

QVariant CheckList::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    else if(itemsAreCheckable() && role == Qt::CheckStateRole){
        return squadra->at(index.row())->isChecked() ?
                    Qt::Checked : Qt::Unchecked;
    }
    else if(role == Qt::DisplayRole){
        if(index.row()<strList.size()){
            return strList[index.row()];
        }
    }
    return QVariant();
}

bool CheckList::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid()){
        return false;
    }
    else if(itemsAreCheckable() && role == Qt::CheckStateRole){
        if(value == Qt::Checked){
            squadra->at(index.row())->setChecked(true);
            emit dataChanged(index, index);
            return true;
        }
        else if(value == Qt::Unchecked){
            squadra->at(index.row())->setChecked(false);
            emit dataChanged(index, index);
            return true;
        }
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

bool CheckList::itemsAreCheckable() const{
    return checkableItems;
}
