#include "portiere.h"

Portiere::Portiere(const QString & n, const QString & c, const QDate & d, unsigned int num)
    : Giocatore(n, c, d, num), tiriParati(0), tiriRicevuti(0) {}

unsigned int Portiere::getTiriParati() const{
    return tiriParati;
}

unsigned int Portiere::getTitiRicevuti() const{
    return tiriRicevuti;
}

unsigned int Portiere::getRigoriParati() const{
    return rigoriParati;
}

unsigned int Portiere::getRigoriRicevuti() const{
    return rigoriRicevuti;
}

unsigned int Portiere::getGoalSubiti() const{
    return tiriRicevuti-tiriParati;
}

unsigned int Portiere::getRigoriSubiti() const{
    return rigoriRicevuti-rigoriParati;
}

double Portiere::getTiriParatiPerc() const{
    return (tiriParati*100)/tiriRicevuti;
}

double Portiere::getRigoriParatiPerc() const{
    return (rigoriParati*100)/rigoriRicevuti;
}

void Portiere::setTiroRicevuto(int x, const bool & parato){
    if(parato){
        tiriParati+x <0 ? tiriParati=0 : tiriParati+=x;
    }
    tiriRicevuti+x <0 ? tiriParati=0 : tiriParati+=x;
}

void Portiere::setRigoreRicevuto(int x, const bool & parato){
    if(parato){
        rigoriParati+x <0 ? rigoriParati=0 : rigoriParati+=x;
    }
    rigoriRicevuti+x <0 ? rigoriParati=0 : rigoriParati+=x;
    setTiroRicevuto(parato);
}

void Portiere::clear(){
    Giocatore::clear();
    tiriParati=0;
    tiriRicevuti=0;
}
