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
    Arbitro(const QString& nome="", const QString& cognome="",
            const QDate& nascita=QDate::currentDate(), const unsigned int& livello= 0);
    Arbitro(const Arbitro& a);

    virtual void modifica(const Arbitro& a);

    unsigned int getLivello () const;

    void setLivello (const unsigned int & l);
    void addPRegionale (int x =1);
    void addPNazionale(int x =1);
    void addPInternaz(int x =1);

    unsigned int getPartite() const;

    virtual Arbitro& operator =(const Arbitro& a);

    virtual void reset(){}

};


#endif // ARBITRO_H
