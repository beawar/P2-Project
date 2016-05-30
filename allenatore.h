#ifndef ALLENATORE_H
#define ALLENATORE_H

#include "tesserato.h"
#include "eccezioni.h"

class Allenatore : public Tesserato
{
private:
    bool ammonizione;
    int dueMinuti;
    bool esclusione;
public:
    static unsigned int max2Minuti;

    Allenatore(const QString& nome="", const QString& cognome="", const QDate& nascita=QDate::currentDate());
    Allenatore(const Allenatore& a);

    bool isAmmonito () const;
    int get2Minuti () const;
    bool isEscluso () const;

    void ammonito (const bool& add =true) throw (Err_Ammonizione);
    void set2Minuti (const bool& add = true) throw (Err_DueMinuti);
    void escluso (const bool& add =true) throw (Err_Esclusione);

    virtual Allenatore& operator =(const Allenatore& a);

    virtual QString getInfo() const;
    virtual void reset();
};



#endif // ALLENATORE_H
