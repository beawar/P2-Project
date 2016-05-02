#ifndef SQUADREMODEL_H
#define SQUADREMODEL_H

#include <QAbstractTableModel>
#include <QVariant>
#include "squadra.h"

class SquadreModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    QList<Squadra*> squadre;
public:
    enum SquadraRoles {NomeRole = Qt::UserRole+1, SocietaRole, VittorieRole,
                      PareggiRole, SconfitteRole, PenalitaRole, PuntiRole};

    explicit SquadreModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Squadra* trova(const Squadra& s) const;
    void addSquadra(Squadra *);
    void addTesserato(Tesserato *, const Squadra&);
    bool modificaTesserato(const Squadra& , Tesserato *, const Tesserato&);

    unsigned int size() const;
    bool isEmpty() const;
    Squadra& operator [](int) const;
    Squadra* at(int i) const;

    void clear();
signals:

public slots:

};

#endif // SQUADREMODEL_H
