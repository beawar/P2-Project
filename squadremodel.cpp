#include "squadremodel.h"
#include <typeinfo>

SquadreModel::SquadreModel(QObject *parent) :
    QAbstractListModel(parent) {}

int SquadreModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return squadre.count();
}

int SquadreModel::columnCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return 7;
}

QVariant SquadreModel::data(const QModelIndex &index, int role) const{
    if(index.row()<0 || index.row()>=squadre.count()){
        return QVariant::Invalid;
    }

    const Squadra* squadra = squadre[index.row()];
    if(role == Qt::DisplayRole){
        return squadra->getNome();
    }
    else if(role == NomeRole){
        return squadra->getNome();
    }
    else if(role == SocietaRole){
        return squadra->getSocieta();
    }
    else if(role == VittorieRole){
        return squadra->getVittorie();
    }
    else if(role == PareggiRole){
        return squadra->getPareggi();
    }
    else if(role == SconfitteRole){
        return squadra->getSconfitte();
    }
    else if(role == PenalitaRole){
        return squadra->getPenalita();
    }
    else if(role == PuntiRole){
        return squadra->getPunti();
    }
    else{
        return QVariant::Invalid;
    }
}

QVariant SquadreModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole){
        switch(section){
            case 0:
                return tr("Squadra");
            case 1:
                return tr("Società");
            case 2:
                return tr("V");
            case 3:
                return tr("P");
            case 4:
                return tr("S");
            case 5:
                return tr("Pt");
            case 6:
                return tr("Pen");
            default:
                return "";
        }
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

Squadra& SquadreModel::operator [] (int i) const{
    return *(squadre[i]);
}
Squadra* SquadreModel::at(int i) const{
    if(i>0 && i<=squadre.size()){
        return squadre.at(i);
    }
    else{
        return 0;
    }
}

void SquadreModel::clear(){
    squadre.clear();
}
