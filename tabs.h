#ifndef TABS_H
#define TABS_H

#include <QTabWidget>
#include <QAction>
#include "stat.h"
#include "squadra.h"
#include "partita.h"

class Tabs : public QTabWidget
{
    Q_OBJECT
private:
    Squadra* team1;
    Squadra* team2;
    Arbitro* a1;
    Arbitro* a2;

    QString pngOpen1;
    QString pngOpen2;

    Stat* statTeam1;
    Stat* statTeam2;
    Partita* partita;


public:
    explicit Tabs(Squadra *s1, Squadra *s2, Arbitro *arb1, Arbitro *arb2, QWidget *parent = 0);

signals:

public slots:
    void exportPng();
    void reset();
    void termina();
};

#endif // TABS_H
