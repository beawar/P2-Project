#include "linestat.h"
#include <QString>

LineStat::LineStat(Tesserato*t, QWidget *parent) :
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
    hbLayout->addWidget(parate);
    hbLayout->addWidget(paratePerc);

    setLayout(hbLayout);
    setAutoFillBackground(true);

}

void LineStat::createLabels(){
    cognome = new QLabel(tess->getCognome(), this);
    cognome->setMinimumSize(100, 20);
    nome = new QLabel(tess->getNome(), this);
    nome->setMinimumSize(100, 20);
    numero = new QLabel(this);
    numero->setMinimumSize(30, 20);
    numero->setStyleSheet("color: white;"
                          "font-weight: bold;"
                          "background-color: navy;"
                          "border 1px solid white;");
    numero->setAlignment(Qt::AlignHCenter);

    ammo = new QLabel(this);
    ammo->setMinimumSize(20, 20);
    dueMin = new QLabel(this);
    dueMin->setMinimumSize(80, 20);
    escl = new QLabel(this);
    escl->setMinimumSize(20, 20);
    reti = new QLabel(this);
    reti->setMinimumSize(100, 20);
    parate = new QLabel(this);
    parate->setMinimumSize(100, 20);
    perc = new QLabel(this);
    perc->setMinimumSize(100, 20);
    paratePerc = new QLabel(this);
    paratePerc->setMinimumSize(100, 20);
    const Giocatore* g = dynamic_cast<const Giocatore*>(tess);
    if(g){
        numero->setText(QString::number(g->getNumero()));
    }
    else{
        numero->setText("All");
    }
}

void LineStat::updateDati(Tesserato* t){
    Giocatore* g = dynamic_cast<Giocatore*>(t);
    if(g){
        numero->setText(QString::number(g->getNumero()));
        reti->setText(tr("%1/%2 (%3/%4)").arg(QString::number(g->getTiriSegnati()),
                                              QString::number(g->getTiriTotali()),
                                              QString::number(g->getRigoriSegnati()),
                                              QString::number(g->getRigoriTotali())));
        perc->setText(tr("%1 (%2)").arg(QString::number(g->getTiriPerc()),
                                        QString::number(g->getRigoriPerc())));
        if(g->isAmmonito()){
            ammo->setText("X");
        }
        else{
            ammo->clear();
        }

        switch(g->get2Minuti()){
            case 1:
                dueMin->setText("X");
                break;
            case 2:
                dueMin->setText("XX");
                break;
            case 3:
                dueMin->setText("XXX");
                break;
            default:
                dueMin->clear();
                break;
        }

        if(g->isEscluso()){
            escl->setText("X");
        }
        else{
            escl->clear();
        }

        Portiere* p = dynamic_cast<Portiere*>(g);
        if(p){
            parate->setText(tr("%1/%2 (%3/%4)").arg(QString::number(p->getTiriParati()),
                                                    QString::number(p->getTiriRicevuti()),
                                                    QString::number(p->getRigoriParati()),
                                                    QString::number(p->getRigoriRicevuti())));
            paratePerc->setText(tr("%1 (%2)").arg(QString::number(p->getTiriParatiPerc()),
                                                  QString::number(p->getRigoriParatiPerc())));
        }
    }
    else{
        Allenatore* all = dynamic_cast<Allenatore*>(t);
        if(all){
            if(all->isAmmonito()){
                ammo->setText("X");
            }
            else{
                ammo->clear();
            }
            if(all->get2Minuti() == 1){
                dueMin->setText("X");
            }
            else{
                dueMin->clear();
            }
            if(all->isEscluso()){
                escl->setText("X");
            }
            else{
                escl->clear();
            }
        }
    }
    update();
}
