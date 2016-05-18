#include "arbitro.h"

Arbitro::Arbitro(const QString& n, const QString& c, const QDate& d, const unsigned int &l)
    :Tesserato(n, c, d), livello(l), partiteRegionali(0), partiteNazionali(0), partiteInternaz(0) {}

void Arbitro::modifica(const Arbitro&a){
    if(*this != a){
        Tesserato::modifica(a);
        if(livello != a.livello){
            setLivello(a.livello);
        }
        if(partiteRegionali != a.partiteRegionali){
            addPRegionale(a.partiteRegionali);
            aumentaLivello();
        }
        if(partiteNazionali != a.partiteNazionali){
            addPNazionale(a.partiteNazionali);
            aumentaLivello();
        }
        if(partiteInternaz != a.partiteInternaz){
            addPInternaz(a.partiteInternaz);
            aumentaLivello();
        }

    }
}

unsigned int Arbitro::getLivello() const{
    return livello;
}

void Arbitro::setLivello(const unsigned int &x){
    livello=x;
    switch(livello){
    case 1:
        partiteInternaz = 2;
        partiteNazionali = 5;
        partiteRegionali = 10;
        break;
    case 2:
        partiteInternaz = 5;
        partiteNazionali = 10;
        partiteRegionali = 20;
        break;
    case 3:
        partiteInternaz = 10;
        partiteNazionali = 20;
        partiteRegionali = 20;
        break;
    default:
        break;
    }
}

void Arbitro::addPRegionale(const int &x){
    (partiteRegionali+x)<0 ? partiteRegionali=0 : partiteRegionali+=x;
    aumentaLivello();
}

void Arbitro::addPNazionale(const int &x){
    (partiteNazionali+x)<0 ? partiteNazionali=0 : partiteNazionali+=x;
    aumentaLivello();
}

void Arbitro::addPInternaz(const int &x){
    (partiteInternaz+x)<0 ? partiteInternaz=0 : partiteInternaz+=x;
    aumentaLivello();
}

unsigned int Arbitro::getPartite() const{
    return partiteRegionali+partiteNazionali+partiteInternaz;
}

void Arbitro::aumentaLivello(){
    if(partiteInternaz>=10 || partiteNazionali>=20){
        livello = 3;
    }
    else if(partiteInternaz>=5 || partiteNazionali>=10 || partiteRegionali>=20){
        livello = 2;
    }
    else if(partiteInternaz>=2 || partiteNazionali>=5 || partiteRegionali>=10){
        livello = 1;
    }
    else{
        livello = 0;
    }
}
