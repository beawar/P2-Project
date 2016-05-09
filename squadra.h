#ifndef SQUADRA_H
#define SQUADRA_H

#include <QString>
#include "vettore.h"
#include "eccezioni.h"
#include "tesserato.h"
#include "giocatore.h"
#include "arbitro.h"
#include "portiere.h"
#include "allenatore.h"

class Squadra
{
private:
    QString nome;
    QString societa;
    Vettore<Tesserato*> tesserati;

    int vittorie;
    int pareggi;
    int sconfitte;

    unsigned int penalita;

    static unsigned int maxAmmonizioni;
    static unsigned int maxEsclusioni;
    static unsigned int puntiVittoria;
    static unsigned int puntiPareggio;

public:
    Squadra(const QString& = "");
    Squadra(const QString&, const QString&);

    QString getNome () const;
    QString getSocieta () const;
    unsigned int getVittorie() const;
    unsigned int getPareggi() const;
    unsigned int getSconfitte() const;

    void setNome (const QString&);
    void setSocieta(const QString&);
    void addVittoria (const int& =1);
    void addPareggio(const int& =1);
    void addSconfitta(const int& =1);

    void addPenalita(const unsigned int&);
    void removePenalita (const unsigned int&);
    int getPenalita() const;

    int getPunti() const;

    unsigned int getTiriSegnati() const;
    unsigned int getGoalSubiti() const;
    unsigned int getTiriTotali() const;
    unsigned int getRigoriSegnati() const;
    unsigned int getRigoriSubiti() const;
    unsigned int getRigoriTotali() const;

    double getTiriPerc() const;
    double getRigoriPerc() const;
    int getDifferenzaReti() const;

    void addTesserato (Tesserato*) throw(Err_Tesserato);
    void changeTesserato(Tesserato*, const Tesserato&);
    void removeTesserato(Tesserato &);

    Tesserato* trova(Tesserato &) const;
    Tesserato* at (int) const;
    Tesserato& operator [] (int) const;
    bool operator == (const Squadra&) const;
    void sortByName();
    void sortByNumber();

    void clear();
    void clearAll();

    unsigned int size() const;
};


#endif // SQUADRA_H
