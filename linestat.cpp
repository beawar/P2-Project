#include "linestat.h"
#include <QString>

LineStat::LineStat(const Tesserato *t, QWidget *parent) :
    QWidget(parent), tess(t)
{
    createLabels();
    QHBoxLayout* hbLayout = new QHBoxLayout;

    hbLayout->addWidget(numero);
    hbLayout->addWidget(cognome);
    hbLayout->addWidget(nome);
    hbLayout->addWidget(ammo);
    hbLayout->addWidget(dueMin);
    hbLayout->addWidget(escl);
    hbLayout->addWidget(reti);
    hbLayout->addWidget(perc);

    setLayout(hbLayout);
    setStyleSheet("QLabel { color: white; font 12pt; }");
}

void LineStat::createLabels(){
    cognome = new QLabel(tess->getCognome(), this);
    cognome->setMinimumSize(100, 50);
    nome = new QLabel(tess->getNome(), this);
    nome->setMinimumSize(100, 50);
    numero = new QLabel(this);
    numero->setMinimumSize(50, 50);
    numero->setMaximumSize(numero->minimumSize());
    numero->setStyleSheet("font: bold 12pt;"
                          "color: white;"
                          "background-color: navy;"
                          "border 1px solid black;");

    ammo = new QLabel(this);
    ammo->setMinimumSize(50, 50);
    dueMin = new QLabel(this);
    dueMin->setMinimumSize(80, 50);
    escl = new QLabel(this);
    escl->setMinimumSize(50, 50);
    reti = new QLabel(this);
    reti->setMinimumSize(100, 50);
    parate = new QLabel(this);
    parate->setMinimumSize(100, 50);
    perc = new QLabel(this);
    perc->setMinimumSize(200, 50);
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
        const Portiere* p = dynamic_cast<const Portiere*>(g);
        if(p){
            parate->setText(tr("%1 / %2 (%3 / %4)")
                            .arg(p->getTiriParati(),
                                 p->getTitiRicevuti(),
                                 p->getRigoriParati(),
                                 p->getRigoriRicevuti()));
            paratePerc->setText(tr("%1% (%2%)")
                                .arg(p->getTiriParatiPerc(),
                                     p->getRigoriParatiPerc()));
        }
    }
    else{
        const Allenatore* all = dynamic_cast<const Allenatore*>(tess);
        if(all){
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
}
