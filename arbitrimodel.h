#ifndef ARBITRIMODEL_H
#define ARBITRIMODEL_H

#include <QAbstractListModel>
#include <QList>
#include "arbitro.h"

class ArbitriModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<Arbitro*> arbitri;
public:
    enum {ArbitroRole = Qt::UserRole+1};

    explicit ArbitriModel(QObject *parent = 0);

    int rowCount(const QModelIndex& parent = QModelIndex()) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    void addArbitro(Arbitro* a);
    unsigned int size() const;
    Arbitro* trova(const Arbitro&) const;
    Arbitro* at(int i) const;
    bool isEmpty() const;

    void clear();
signals:

public slots:

};

#endif // ARBITRIMODEL_H
