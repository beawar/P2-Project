#include "squadremodel.h"
#include <typeinfo>

SquadreModel::SquadreModel(QObject *parent) :
    QAbstractListModel(parent) {}

int SquadreModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return squadre.count();
}

QVariant SquadreModel::data(const QModelIndex &index, int role) const{
    if(index.row()<0 || index.row()>=squadre.count()){
        return QVariant::Invalid;
    }

    const Squadra* squadra = squadre[index.row()];
    if(role == Qt::DisplayRole){
        return squadra->getNome();
    }
    else if(role == SquadraRole){
        return squadra;
    }
    else if(role == TesseratoRole){

    }
    else{
        return QVariant::Invalid;
    }
}

QVariant SquadreModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal){
        Q_UNUSED(section);
        if(role == NomeRole)
            return tr("Squadra");
        else if(role == SocietaRole){
            return tr("Società");
        }
    }
    return "";
}

bool SquadreModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid()){
        switch(role){
        case NomeRole:
        {
            QString n = value.toString();
            if(squadre[index.row()]->getNome() != n){
                squadre[index.row()]->setNome(n);
                emit QAbstractListModel::dataChanged(index, index);
                return true;
            }
            else{
                return false;
            }
        }
        case SocietaRole:
        {
            QString s = value.toString();
            if(squadre[index.row()]->getNome() != s){
                squadre[index.row()]->setSocieta(s);
                emit QAbstractListModel::dataChanged(index, index);
                return true;
            }
            else{
                return false;
            }
        }

        default:
            return false;
        }
    }
    else{
        return false;
    }

}

Qt::ItemFlags SquadreModel::flags(const QModelIndex &index) const{
    if(index.isValid()){
        return (QAbstractListModel::flags(index) | Qt::ItemIsEditable);
    }
    else{
        return Qt::NoItemFlags;
    }
}

Squadra* SquadreModel::trova(const Squadra &s) const{
    for(QList<Squadra*>::ConstIterator it = squadre.constBegin(); it!=squadre.constEnd(); ++it){
        if(**it == s){
            return *it;
        }
    }
    return 0;
}

void SquadreModel::addSquadra(Squadra* s){
    bool inserito = false;
    for(QList<Squadra*>::iterator it = squadre.begin(); it != squadre.end() && !inserito; ++it){
        if(s->getNome() < (*it)->getNome()){
            squadre.insert(it, s);
            inserito = true;
        }
    }
    if(!inserito){
        squadre.push_back(s);
    }
}

void SquadreModel::addTesserato(Tesserato* t, const Squadra& s){
    for(QList<Squadra*>::iterator it = squadre.begin(); it!=squadre.end(); ++it){
        if((*it)->getNome() == s.getNome()){
            (*it)->addTesserato(t);

        }
    }
}

bool SquadreModel::modificaTesserato(const Squadra& squadra, Tesserato* vecchio,  const Tesserato & nuovo){
    for(QList<Squadra*>::iterator it=squadre.begin(); it!=squadre.end(); ++it){
        if(**it == squadra && (*it)->trova(*vecchio)){
            (*it)->changeTesserato(vecchio, nuovo);
            return true;
        }
    }
    return false;
}

unsigned int SquadreModel::size() const{
    return squadre.size();
}

bool SquadreModel::isEmpty() const{
    return squadre.isEmpty();
}

Squadra* SquadreModel::at(int i) const{
    if(i>=0){
        return squadre.at(i);
    }
    else{
        return 0;
    }
}

void SquadreModel::clear(){
    squadre.clear();
}
