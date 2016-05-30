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

    Giocatore(const QString& nome="", const QString& cognome="",
              const QDate& nascita= QDate::currentDate(), unsigned int num= 0);
    Giocatore(const Giocatore& g);

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

    void setNumero(unsigned int n);
    void addTiro (int x =1, const bool& segnato =false);
    void addRigore (int x =1, const bool& segnato =false);
    void ammonito (const bool& add =true) throw (Err_Ammonizione);
    void add2Minuti (int x =1) throw (Err_DueMinuti);
    void escluso (const bool& add =true) throw (Err_Esclusione);

    virtual void modifica(const Giocatore& g);

    virtual Giocatore& operator = (const Giocatore& g);

    virtual bool operator ==(const Giocatore& g) const;
    virtual bool operator !=(const Giocatore& g) const;
    virtual bool operator <(const Giocatore& g) const;
    virtual bool operator <=(const Giocatore& g) const;
    virtual bool operator >(const Giocatore& g) const;
    virtual bool operator >=(const Giocatore& g) const;

    virtual QString getInfo() const;
    virtual void reset();
};


#endif // GIOCATORE_H
