#ifndef ARBITRO_H
#define ARBITRO_H

#include "tesserato.h"

class Arbitro : public Tesserato
{
private:
    unsigned livello;
    int partiteRegionali;
    int partiteNazionali;
    int partiteInternaz;

    void aumentaLivello ();
public:
    enum Categoria{regionale, nazionale, internazionale};

    Arbitro(const QString& nome="", const QString& cognome="",
            const QDate& nascita=QDate::currentDate(), const unsigned int& livello= 0);
    Arbitro(const Arbitro& a);

    virtual void modifica(const Tesserato& a);

    unsigned int getLivello () const;

    void setLivello (const unsigned int & l);
    void addPartita (Categoria cat, int x =1);

    unsigned int getPartite() const;

    Arbitro& operator =(const Arbitro& a);

    virtual void reset(){}

};


#endif // ARBITRO_H
