#include "tesserato.h"

Tesserato::Tesserato() {}

Tesserato::Tesserato(const QString& n, const QString& c, const QDate& d)
  : nome(n), cognome(c), annoNascita(d), checked(false) {}

QString Tesserato::getNome() const{
  return nome;
}

QString Tesserato::getCognome() const{
  return cognome;
}

QDate Tesserato::getAnno() const{
  return annoNascita;
}

void Tesserato::setNome(const QString &n){
  nome=n;
}

void Tesserato::setCognome(const QString &c){
   cognome=c;
}

void Tesserato::setAnno(const QDate &a){
  annoNascita=a;
}

bool Tesserato::operator ==(const Tesserato& t) const{
    return nome==t.nome && cognome==t.cognome && annoNascita==t.annoNascita;
}

bool Tesserato::operator !=(const Tesserato& t) const{
    return !(operator ==(t));
}

bool Tesserato::operator <(const Tesserato& t) const{
    if(cognome<t.cognome){
        return true;
    }
    else if(cognome==t.cognome && nome<t.nome){
        return true;
    }
    else if(cognome==t.cognome && nome==t.nome && annoNascita<t.annoNascita){
        return true;
    }
    else{
        return false;
    }
}

bool Tesserato::operator <=(const Tesserato& t) const{
    return (operator <(t)) || (operator ==(t));
}

bool Tesserato::operator >(const Tesserato& t) const{
    return !(operator <=(t));
}

bool Tesserato::operator >=(const Tesserato& t)const{
    return !(operator <(t));
}

void Tesserato::setChecked(const bool & b){
    checked = b;
}

bool Tesserato::isChecked() const{
    return checked;
}

QString Tesserato::getInfo() const{
    QString info;
    info.append(getCognome() + " ");
    info.append(getNome() + " ");
    return info;
}
