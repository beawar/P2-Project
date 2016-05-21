#include "linestat.h"
#include <QString>

LineStat::LineStat(const Tesserato *t, QWidget *parent) :
    QWidget(parent), tess(t)
{
    createLabels();
    QHBoxLayout* hbLayout = new QHBoxLayout();

    hbLayout->addWidget(numero);
    hbLayout->addWidget(cognome);
    hbLayout->addWidget(nome);
    hbLayout->addWidget(ammo);
    hbLayout->addWidget(dueMin);
    hbLayout->addWidget(escl);
    hbLayout->addWidget(reti);
    hbLayout->addWidget(perc);

    setLayout(hbLayout);
}

void LineStat::createLabels(){
    cognome = new QLabel(tess->getCognome(), this);
    cognome->setBaseSize(500, 100);
    nome = new QLabel(tess->getNome(), this);
    nome->setBaseSize(500, 100);
    numero = new QLabel(this);
    numero->setBaseSize(100, 100);
    ammo = new QLabel(this);
    ammo->setBaseSize(100, 100);
    dueMin = new QLabel(this);
    dueMin->setBaseSize(200, 100);
    escl = new QLabel(this);
    escl->setBaseSize(100, 100);
    reti = new QLabel(this);
    reti->setBaseSize(500, 100);
    perc = new QLabel(this);
    perc->setBaseSize(200, 100);
    const Giocatore* g = dynamic_cast<const Giocatore*>(tess);
    if(g){
        numero->setText(QString::number(g->getNumero()));
    }
    else{
        numero->setText("All");
    }
}

void LineStat::updateDati(){

    const Giocatore* g = dynamic_cast<const Giocatore*>(tess);
    if(g){
        numero->setText(QString::number(g->getNumero()));
        QString tiri = tr("%1 / %2 (%3 / %4)").arg(g->getTiriSegnati()).arg(g->getTiriTotali()).arg(g->getRigoriSegnati()).arg(g->getRigoriTotali());
        reti->setText(tiri);
        QString percentuali = tr("%1 (%2)").arg(g->getTiriPerc()).arg(g->getRigoriPerc());
        perc->setText(percentuali);
        if(g->isAmmonito()){
            ammo->setText("X");
        }
        for(int i=0; i<g->get2Minuti(); ++i){
            dueMin->setText(dueMin->text().append("X"));
        }
        if(g->isEscluso()){
            escl->setText("X");
        }
    }
    else{
        const Allenatore* all = dynamic_cast<const Allenatore*>(tess);
        if(all->isAmmonito()){
            ammo->setText("X");
        }
        for(int i=0; i<all->get2Minuti(); ++i){
            dueMin->setText(dueMin->text().append("X"));
        }
        if(all->isEscluso()){
            escl->setText("X");
        }
    }
}
