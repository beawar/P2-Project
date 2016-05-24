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

    Allenatore(const QString& ="", const QString& ="", const QDate& =QDate::currentDate());

    bool isAmmonito () const;
    int get2Minuti () const;
    bool isEscluso () const;

    void ammonito (const bool& =true) throw (Err_Ammonizione);
    void set2Minuti (const bool& = true) throw (Err_DueMinuti);
    void escluso (const bool& =true) throw (Err_Esclusione);

    virtual QString getInfo() const;
    virtual void reset();
};



#endif // ALLENATORE_H
