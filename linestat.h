#ifndef LINESTAT_H
#define LINESTAT_H

#include <QWidget>
#include "tesserato.h"
#include "giocatore.h"
#include "allenatore.h"
#include <QLabel>
#include <QHBoxLayout>

class LineStat : public QWidget
{
    Q_OBJECT
private:
    const Tesserato* tess;

    void createLabels();

    QLabel* nome;
    QLabel* cognome;
    QLabel* numero;
    QLabel* ammo;
    QLabel* dueMin;
    QLabel* escl;
    QLabel* reti;
    QLabel* perc;
public:
    explicit LineStat(const Tesserato* t, QWidget *parent = 0);

signals:

public slots:
    void updateDati();

};

#endif // LINESTAT_H
