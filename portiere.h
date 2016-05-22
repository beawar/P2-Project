#ifndef PORTIERE_H
#define PORTIERE_H

#include "giocatore.h"

class Portiere : public Giocatore
{
private:
    int tiriParati;
    int tiriRicevuti;
    int rigoriParati;
    int rigoriRicevuti;

public:
    Portiere(const QString& ="", const QString& ="", const QDate& = QDate::currentDate(), unsigned int = 0);

    unsigned int getTiriParati() const;
    unsigned int getTitiRicevuti() const;
    unsigned int getRigoriParati() const;
    unsigned int getRigoriRicevuti() const;

    unsigned int getGoalSubiti () const;
    unsigned int getRigoriSubiti () const;

    double getTiriParatiPerc() const;
    double getRigoriParatiPerc() const;

    void setTiroRicevuto( int = 1, const bool& = false);
    void setRigoreRicevuto(int =1, const bool& = false);

    virtual void clear();
};

#endif // PORTIERE_H
