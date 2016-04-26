#include "arbitrimodel.h"

ArbitriModel::ArbitriModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int ArbitriModel::rowCount(const QModelIndex &parent) const{
    Q_UNUSED(parent);
    return arbitri.count();
}

QVariant ArbitriModel::data(const QModelIndex &index, int role) const{

    if(index.row()<0 || index.row()>=arbitri.count()){
        return QVariant::Invalid;
    }

    Arbitro* arbitro = arbitri[index.row()];
    if(role == Qt::DisplayRole){
        return QString(arbitro->getNome() + arbitro->getCognome());
    }
    else if(role == ArbitroRole){
        return arbitro;
    }
    else{
        return QVariant::Invalid;
    }
}

QVariant ArbitriModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(orientation == Qt::Horizontal){
        Q_UNUSED(section);
        if(role == NomeRole)
            return tr("Nome");
        else if(role == CognomeRole){
            return tr("Cognome");
        }
        else if(role == DataRole){
            return tr("Data di Nascita");
        }
        else if(role == LivelloRole){
            return tr("Livello");
        }
    }
    return "";
}

bool ArbitriModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(index.isValid()){
        switch(role){
        case NomeRole:
        {
            QString s = value.toString();
            if(arbitri[index.row()]->getNome() != s){
                arbitri[index.row()]->setNome(s);
                emit QAbstractListModel::dataChanged(index, index);
                return true;
            }
            else{
                return false;
            }
        }
        case CognomeRole:
        {
            QString s = value.toString();
            if(arbitri[index.row()]->getCognome() != s){
                arbitri[index.row()]->setCognome(s);
                emit QAbstractListModel::dataChanged(index, index);
                return true;
            }
            else{
                return false;
            }
        }
        case LivelloRole:
        {
            unsigned int liv = value.toUInt();
            if(arbitri[index.row()]->getLivello() != liv){
                arbitri[index.row()]->setLivello(liv);
                emit QAbstractListModel::dataChanged(index, index);
                return true;
            }
            else{
                return false;
            }
        }
        case DataRole:
        {
            QDate data = value.toDate();
            if(arbitri[index.row()]->getAnno() != data){
                arbitri[index.row()]->setAnno(data);
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

Qt::ItemFlags ArbitriModel::flags(const QModelIndex &index) const{
    if(index.isValid()){
        return (QAbstractListModel::flags(index) | Qt::ItemIsEditable);
    }
    else{
        return Qt::NoItemFlags;
    }
}

void ArbitriModel::addArbitro(Arbitro *a){
    arbitri.push_back(a);
}

unsigned int ArbitriModel::size() const{
    return arbitri.size();
}

Arbitro* ArbitriModel::trova(const Arbitro &a) const{
    for(QList<Arbitro*>::ConstIterator it = arbitri.constBegin(); it<arbitri.constEnd(); ++it){
        if(**it == a){
            return *it;
        }
    }
    return 0;
}

Arbitro* ArbitriModel::at(int i) const{
    if(i>=0){
        return arbitri.at(i);
    }
    else{
        return 0;
    }
}

bool ArbitriModel::isEmpty() const{
    return arbitri.isEmpty();
}

void ArbitriModel::clear(){
    arbitri.clear();
}
