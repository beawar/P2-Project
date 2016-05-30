#include "allenatore.h"

unsigned int Allenatore::max2Minuti = 1;

Allenatore::Allenatore(const QString& nome, const QString& cognome, const QDate& nascita)
    :Tesserato(nome, cognome, nascita), ammonizione(false), dueMinuti(false), esclusione(false){}

Allenatore::Allenatore(const Allenatore& a){
   *this = a;
}

bool Allenatore::isAmmonito() const{
    return ammonizione;
}

int Allenatore::get2Minuti() const{
    return dueMinuti;
}

bool Allenatore::isEscluso() const{
    return esclusione;
}

void Allenatore::ammonito(const bool& add) throw(Err_Ammonizione){
    if(add){
        isAmmonito() ? throw Err_Ammonizione() : ammonizione=true;
    }
    else{
        ammonizione=false;
    }
}

void Allenatore::set2Minuti(const bool& add) throw(Err_DueMinuti){
    if(add){
        get2Minuti() == max2Minuti ? throw Err_DueMinuti(): ++dueMinuti;
    }
    else if(!add && get2Minuti()>0){
        --dueMinuti;
    }
}

void Allenatore::escluso(const bool& add) throw(Err_Esclusione){
    if(add){
        isEscluso() ? throw Err_Esclusione() : esclusione = true;
    }
    else{
        esclusione = false;
    }
}

Allenatore& Allenatore::operator =(const Allenatore& a){
    Tesserato::operator =(a);
    ammonizione = a.ammonizione;
    dueMinuti = a.dueMinuti;
    esclusione = a.esclusione;
    return *this;
}

QString Allenatore::getInfo() const{
    QString info;
    info.append("All   ");
    info.append(Tesserato::getInfo());
    return info;
}

void Allenatore::reset(){
    ammonizione = false;
    dueMinuti = 0;
    esclusione = false;
}
