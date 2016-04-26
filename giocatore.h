#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "tesserato.h"
#include "eccezioni.h"

class Giocatore : public Tesserato
{
private:
    unsigned int numero;
    int tiriSegnati;
    int tiriTotali;
    int rigoriSegnati;
    int rigoriTotali;
    bool ammonizione;
    int dueMinuti;
    bool esclusione;

public:
    static unsigned int max2Minuti;

    Giocatore(const QString& ="", const QString& ="", const QDate& = QDate::currentDate(), unsigned int = 0);

    unsigned int getNumero() const;
    unsigned int getTiriSegnati () const;
    unsigned int getTiriTotali () const;
    unsigned int getRigoriSegnati () const;
    unsigned int getRigoriTotali() const;
    double getTiriPerc () const;
    double getRigoriPerc () const;
    bool isAmmonito () const;
    int get2Minuti () const;
    bool isEscluso () const;

    void setNumero(unsigned int);
    void setTiro (int =1, const bool& =false);
    void setRigore (int =1, const bool& =false);
    void ammonito (const bool& =true) throw (Err_Ammonizione);
    void set2Minuti (int =1) throw (Err_DueMinuti);
    void escluso (const bool& =true) throw (Err_Esclusione);

    virtual bool operator ==(const Giocatore&) const;
    virtual bool operator !=(const Giocatore&) const;
    virtual bool operator <(const Giocatore&) const;
    virtual bool operator <=(const Giocatore&) const;
    virtual bool operator >(const Giocatore&) const;
    virtual bool operator >=(const Giocatore&) const;

    virtual QString getInfo() const;
    virtual void clear ();
};


#endif // GIOCATORE_H
