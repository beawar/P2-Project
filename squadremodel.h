#ifndef SQUADREMODEL_H
#define SQUADREMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include "squadra.h"

class SquadreModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<Squadra*> squadre;
public:
    enum SquadraRoles {SquadraRole = Qt::UserRole+1, TesseratoRole, NomeRole, SocietaRole};

    explicit SquadreModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

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
