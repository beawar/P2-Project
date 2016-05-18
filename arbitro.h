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
    Arbitro(const QString& ="", const QString& ="", const QDate& =QDate::currentDate(), const unsigned int& = 0);

    virtual void modifica(const Arbitro&);

    unsigned int getLivello () const;

    void setLivello (const unsigned int &);
    void addPRegionale (const int& =1);
    void addPNazionale(const int& =1);
    void addPInternaz(const int& =1);

    unsigned int getPartite() const;

    virtual void clear(){}

};


#endif // ARBITRO_H
