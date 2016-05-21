#ifndef PARTITA_H
#define PARTITA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include "squadra.h"
#include "arbitro.h"
#include "linepartita.h"

class Partita : public QWidget
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void createHomeLayout();
    void createGuestLayout();

    QVBoxLayout* mainLayout;

    Squadra* homeTeam;
    Squadra* guestTeam;

    LinePartita* homeLines[maxGiocatori+maxAllenatori];
    LinePartita* guestLines[maxGiocatori+maxAllenatori];

    QGroupBox* homeGroup;
    QGroupBox* guestGroup;

    QLabel* punteggio;

public:
    explicit Partita(Squadra* home, Squadra* guest, Arbitro* a1, Arbitro* a2, QWidget *parent = 0);
    Squadra* getHomeTeam() const;
    Squadra* getGuestTeam() const;

signals:

private slots:
    void updatePunteggio();

public slots:

};

#endif // PARTITA_H
