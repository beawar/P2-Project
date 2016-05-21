#include "giocatore.h"

unsigned int Giocatore::max2Minuti = 3;

Giocatore::Giocatore(const QString& n, const QString& c, const QDate& d, unsigned int num)
  :Tesserato(n, c, d), numero(num), tiriSegnati(0), tiriTotali(0), rigoriSegnati(0),
    rigoriTotali(0), ammonizione(false), dueMinuti(0), esclusione(0) {}

unsigned int Giocatore::getNumero() const{
    return numero;
}

unsigned int Giocatore::getTiriSegnati() const{
  return tiriSegnati;
}

unsigned int Giocatore::getTiriTotali() const{
  return tiriTotali;
}

unsigned int Giocatore::getRigoriSegnati() const{
  return rigoriSegnati;
}

unsigned int Giocatore::getRigoriTotali() const{
  return rigoriTotali;
}

double Giocatore::getTiriPerc() const{
  return tiriSegnati*100/tiriTotali;
}

double Giocatore::getRigoriPerc() const{
  return rigoriSegnati*100/rigoriTotali;
}

bool Giocatore::isAmmonito() const{
  return ammonizione;
}

int Giocatore::get2Minuti() const{
  return dueMinuti;
}

bool Giocatore::isEscluso() const{
  return esclusione;
}

void Giocatore::setNumero(unsigned int n){
    numero=n;
}

void Giocatore::setTiro(int x, const bool& segnato){
    if(segnato){
        (tiriSegnati+x)<0 ? tiriSegnati=0 : tiriSegnati+=x;
    }
    (tiriTotali+x)<0 ? tiriTotali=0 : tiriSegnati+=x;
}

void Giocatore::setRigore(int x, const bool& segnato){
    if(segnato){
        (rigoriSegnati+x)<0 ? rigoriSegnati=0 : rigoriSegnati+=x;
    }
    (rigoriTotali+x)<0 ? rigoriTotali=0 : rigoriTotali+=x ;
    setTiro(x, segnato);
}

void Giocatore::ammonito(const bool& add) throw(Err_Ammonizione){
    if(add){
        isAmmonito() ? throw Err_Ammonizione() : ammonizione=true;
    }
    else{
        ammonizione=false;
    }
}

void Giocatore::set2Minuti(int x) throw(Err_DueMinuti){
    (dueMinuti+x <0 || dueMinuti+x>3) ? throw Err_DueMinuti(): dueMinuti+=x;
}

void Giocatore::escluso(const bool& add) throw(Err_Esclusione){
    if(add){
        isEscluso() ? throw Err_Esclusione() : esclusione = true;
    }
    else{
        esclusione = false;
    }
}

void Giocatore::modifica(const Giocatore &g){
    if(*this != g){
        Tesserato::modifica(g);
        if(numero != g.numero){
            setNumero(g.numero);
        }
    }
}

bool Giocatore::operator ==(const Giocatore& t) const{
    return Tesserato::operator ==(t) && numero==t.numero;
}

bool Giocatore::operator !=(const Giocatore& t) const{
    return !(operator ==(t));
}

bool Giocatore::operator <(const Giocatore& t) const{
    if(Tesserato::operator <(t)){
        return true;
    }
    else if(Tesserato::operator ==(t) && numero<t.numero){
        return true;
    }
    else{
        return false;
    }
}

bool Giocatore::operator <=(const Giocatore& t) const{
    return (operator <(t)) || (operator ==(t));
}

bool Giocatore::operator >(const Giocatore& t) const{
    return !(operator <=(t));
}

bool Giocatore::operator >=(const Giocatore& t) const{
    return !(operator <(t));
}

QString Giocatore::getInfo() const{
    QString info;
    if(getNumero() < 10){
        info.append("  ");
    }
    info.append(QString::number(getNumero()) + "   ");
    info.append(Tesserato::getInfo());
    return info;
}

void Giocatore::clear(){
    tiriSegnati = 0;
    tiriTotali = 0;
    rigoriSegnati = 0;
    rigoriTotali = 0;
    ammonizione = false;
    dueMinuti = 0;
    esclusione = false;
}
