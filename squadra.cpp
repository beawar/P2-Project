#include "squadra.h"
#include "allenatore.h"

unsigned int Squadra::maxAmmonizioni = 3;
unsigned int Squadra::maxEsclusioni = 4;
unsigned int Squadra::puntiVittoria = 3;
unsigned int Squadra::puntiPareggio = 1;

Squadra::Squadra(const QString& n)
    :nome(n), societa(n), tesserati(), vittorie(0), pareggi(0), sconfitte(0), penalita(0) {}

Squadra::Squadra(const QString& n, const QString& s)
    : nome(n), societa(s), tesserati(), vittorie(0), pareggi(0), sconfitte(0), penalita(0) {}

QString Squadra::getNome() const{
    return nome;
}

QString Squadra::getSocieta() const{
    return societa;
}

unsigned int Squadra::getVittorie() const{
    return vittorie;
}

unsigned int Squadra::getPareggi() const{
    return pareggi;
}

unsigned int Squadra::getSconfitte() const{
    return sconfitte;
}

void Squadra::setNome(const QString &n){
    nome = n;
}

void Squadra::setSocieta(const QString &s){
    societa = s;
}

void Squadra::addVittoria(const int & x){
    vittorie+x <0 ? vittorie=0 : vittorie+=x;
}

void Squadra::addPareggio(const int & x){
    pareggi+x <0 ? pareggi=0 : pareggi+=x;
}

void Squadra::addSconfitta(const int & x){
    sconfitte+x <0 ? sconfitte=0 : sconfitte+=x;
}

void Squadra::addPenalita(const unsigned int & x){
    penalita+=x;
}

void Squadra::removePenalita(const unsigned int & x){
    penalita-=x;
}

int Squadra::getPenalita() const{
    return penalita;
}

int Squadra::getPunti() const{
    return (vittorie*puntiVittoria)
            + (pareggi*puntiPareggio)
            - penalita;
}

unsigned int Squadra::getTiriSegnati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getTiriSegnati();
        }
    }
    return tot;
}

 unsigned int Squadra::getGoalSubiti() const{
     unsigned int tot=0;
     for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
         Portiere* p = dynamic_cast<Portiere*>(*cit);
         if(p){
             tot+= p->getGoalSubiti();
         }
     }
     return tot;
 }

unsigned int Squadra::getTiriTotali() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
        Giocatore* g = dynamic_cast<Giocatore*>(*cit);
        if(g){
            tot+= g->getTiriTotali();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriSegnati() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getRigoriSegnati();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriSubiti() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
        Portiere* p = dynamic_cast<Portiere*>(*cit);
        if(p){
            tot+= p->getRigoriSubiti();
        }
    }
    return tot;
}

unsigned int Squadra::getRigoriTotali() const{
    unsigned int tot=0;
    for(Vettore<Tesserato*>::const_iterator cit; cit<tesserati.cend(); ++cit){
        const Giocatore* g = dynamic_cast<const Giocatore*>(*cit);
        if(g){
            tot+= g->getRigoriTotali();
        }
    }
    return tot;
}

double Squadra::getTiriPerc() const{
    return getTiriSegnati()*100 /getTiriTotali();
}

double Squadra::getRigoriPerc() const{
    return getRigoriSegnati()*100 /getRigoriTotali();
}

int Squadra::getDifferenzaReti() const{
    return getTiriSegnati() - getGoalSubiti();
}

void Squadra::addTesserato(Tesserato *t) throw(Err_Tesserato){
    if(!dynamic_cast<const Arbitro*>(t)){
        if(trova(*t)){
            throw Err_Tesserato();
        }
        else{
            tesserati.push_back(t);
        }
    }
    else{
        throw Err_Tesserato();
    }
}

void Squadra::changeTesserato(Tesserato* cur, const Tesserato & n){
    Tesserato* nuovo = const_cast<Tesserato*>(&n);
    delete cur;
    cur = nuovo;
}

void Squadra::removeTesserato(Tesserato& t){
    if(trova(t)){
        tesserati.erase(&t);
    }
}

Tesserato* Squadra::trova(Tesserato& t) const{
    for(Vettore<Tesserato*>::iterator it=tesserati.begin(); it<tesserati.end(); ++it){
        if(**it == t){
            return *it;
        }
    }
    return 0;
}

Tesserato* Squadra::at (int i) const{
    return tesserati.at(i);
}

bool Squadra::operator ==(const Squadra& s) const{
    if(tesserati.size() != s.tesserati.size()){
        return false;
    }
    else{
        for(int i=0; i<tesserati.size(); ++i){
            if(*(tesserati.at(i)) != *(s.at(i))){
                return false;
            }
        }
        return true;
    }
}

void Squadra::sortByName(){
    Vettore<Tesserato*>::iterator it = tesserati.begin();
    for(; it<tesserati.end(); ++it){
        Giocatore* g1 = dynamic_cast<Giocatore*>(*it);
        if(g1){
            Giocatore* g2 = dynamic_cast<Giocatore*>(*it);
            if(g2 && *g1 > *g2){
                Giocatore* temp = g1;
                g1 = g2;
                g2 = temp;
            }
        }
        else{
            Allenatore* all1 = dynamic_cast<Allenatore*>(*it);
            bool inserito = false;
            for(Vettore<Tesserato*>::iterator it2=tesserati.end()-1; it2>it && !inserito; --it2){
                Allenatore* all2 = dynamic_cast<Allenatore*>(*it2);
                if(all2 && *all1 > *all2){
                    Allenatore aux = *all1;
                    it = tesserati.erase(it);
                    ++it2;
                    it2 = tesserati.insert(it2, &aux);
                    inserito = true;
                }
            }
        }
    }
}

void Squadra::sortByNumber(){
    Vettore<Tesserato*>::iterator it = tesserati.begin();
    for(; it<tesserati.end(); ++it){
        Giocatore* g1 = dynamic_cast<Giocatore*>(*it);
        if(g1){
            Giocatore* g2 = dynamic_cast<Giocatore*>(*it);
            if(g2 && g1->getNumero() > g2->getNumero()){
                Giocatore* temp = g1;
                g1 = g2;
                g2 = temp;
            }
        }
        else{
            Allenatore* all1 = dynamic_cast<Allenatore*>(*it);
            bool inserito = false;
            for(Vettore<Tesserato*>::iterator it2=tesserati.end()-1; it2>it && !inserito; --it2){
                Allenatore* all2 = dynamic_cast<Allenatore*>(*it2);
                if(all2 && *all1 > *all2){
                    Allenatore aux = *all1;
                    it = tesserati.erase(it);
                    ++it2;
                    it2 = tesserati.insert(it2, &aux);
                    inserito = true;
                }
            }
        }
    }
}

void Squadra::clear(){
    vittorie = 0;
    pareggi = 0;
    sconfitte = 0;
    penalita = 0;
}

unsigned int Squadra::size() const{
    return tesserati.size();
}
