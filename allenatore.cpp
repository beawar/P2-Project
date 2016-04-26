#include "allenatore.h"

unsigned int Allenatore::max2Minuti = 1;

Allenatore::Allenatore(const QString& n, const QString& c, const QDate& d)
    :Tesserato(n, c, d), ammonizione(false), dueMinuti(false), esclusione(false){}

bool Allenatore::isAmmonito() const{
    return isAmmonito();
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

QString Allenatore::getInfo() const{
    QString info;
    info.append("All   ");
    info.append(Tesserato::getInfo());
    return info;
}

void Allenatore::clear(){
    ammonizione = false;
    dueMinuti = 0;
    esclusione = false;
}
