#include "arbitro.h"

Arbitro::Arbitro(const QString& nome, const QString& cognome, const QDate& nascita, const unsigned int &livello)
    :Tesserato(nome, cognome, nascita), livello(livello), partiteRegionali(0), partiteNazionali(0), partiteInternaz(0) {}

Arbitro::Arbitro(const Arbitro &a)
    : Tesserato(a.getNome(), a.getCognome(), a.getData()), livello(a.livello), partiteRegionali(a.partiteRegionali),
      partiteNazionali(a.partiteNazionali), partiteInternaz(a.partiteInternaz)
{
    setChecked(a.isChecked());
}

void Arbitro::modifica(const Tesserato &a){
    const Arbitro* aux = dynamic_cast<const Arbitro*>(&a);
    if(aux && *this != *aux){
        if(livello != aux->livello){
            setLivello(aux->livello);
        }
        if(partiteRegionali != aux->partiteRegionali){
            addPRegionale(aux->partiteRegionali);
            aumentaLivello();
        }
        if(partiteNazionali != aux->partiteNazionali){
            addPNazionale(aux->partiteNazionali);
            aumentaLivello();
        }
        if(partiteInternaz != aux->partiteInternaz){
            addPInternaz(aux->partiteInternaz);
            aumentaLivello();
        }
    }
    Tesserato::modifica(a);
}

unsigned int Arbitro::getLivello() const{
    return livello;
}

void Arbitro::setLivello(const unsigned int &l){
    livello=l;
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

void Arbitro::addPRegionale(int x){
    (partiteRegionali+x)<0 ? partiteRegionali=0 : partiteRegionali+=x;
    aumentaLivello();
}

void Arbitro::addPNazionale(int x){
    (partiteNazionali+x)<0 ? partiteNazionali=0 : partiteNazionali+=x;
    aumentaLivello();
}

void Arbitro::addPInternaz(int x){
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

Arbitro& Arbitro::operator =(const Arbitro& a){
    Tesserato::operator =(a);
    livello = a.livello;
    partiteRegionali = a.partiteRegionali;
    partiteNazionali = a.partiteNazionali;
    partiteInternaz = a.partiteInternaz;
    return *this;
}
