#include "stat.h"
#include <QVBoxLayout>

Stat::Stat(Squadra *s, QWidget *parent) :
    QWidget(parent), squadra(s)
{
    createHeader();

    QFont font;
    font.setBold(true);
    font.setItalic(true);
    font.setPointSize(18);
    squadraLabel = new QLabel(squadra->getNome(), this);
    squadraLabel->setFont(font);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(squadraLabel);
    layout->addLayout(headerLayout);

    int j = 0;
    for(int i=0; i<squadra->size(); ++i){
        if(squadra->at(i)->isChecked() && j<maxPersone){
            persona[j] = new LineStat(squadra->at(i), this);
            layout->addWidget(persona[j]);
            j++;
        }
    }
    persona[j-1]->setObjectName("LastPerson");

    setStyleSheet("LineStat {border-top: 1px groove grey }");
    setStyleSheet("LineStat#LastPerson {border-bottom: 1px groove grey }");
    setStyleSheet("Stat { background-image: url(:/images/images/Sfondo_logo.png) }");
    setLayout(layout);
}

void Stat::createHeader(){
    headerLayout = new QHBoxLayout;

    numero = new QLabel("N°", this);
    //numero->setMinimumSize(50, 50);
    cognome = new QLabel(tr("Cognome"), this);
    //cognome->setMinimumSize(100, 50);
    nome = new QLabel(tr("Nome"), this);
    //nome->setMinimumSize(100, 50);
    ammo = new QLabel(this);
    ammo->setPixmap(QPixmap(":/images/images/giallo.png").scaled(10, 10));
    //ammo->setMinimumSize(50, 50);
    dueMin = new QLabel(this);
    dueMin->setPixmap(QPixmap(":/images/images/two_fingers.png").scaled(10, 10));
    //dueMin->setMinimumSize(80, 50);
    escl = new QLabel(tr("Escl."), this);
    escl->setPixmap(QPixmap(":/images/images/rosso.png").scaled(10, 10));
    //escl->setMinimumSize(50, 50);
    reti = new QLabel(tr("Reti (Rigori)"), this);
    reti->setPixmap(QPixmap(":/images/images/footbal.png").scaled(10, 10));
    //reti->setMinimumSize(100, 50);
    parate = new QLabel(tr("Parate (Rigori)"), this);
    //parate->setMinimumSize(100, 50);
    perc = new QLabel("%", this);
    //perc->setMinimumSize(100, 50);
    parateperc = new QLabel(tr("% Parate"));
    //parateperc->setMinimumSize(100, 50);

    headerLayout->addWidget(numero);
    headerLayout->addWidget(cognome);
    headerLayout->addWidget(nome);
    headerLayout->addWidget(ammo);
    headerLayout->addWidget(dueMin);
    headerLayout->addWidget(escl);
    headerLayout->addWidget(reti);
    headerLayout->addWidget(parate);
    headerLayout->addWidget(perc);
    headerLayout->addWidget(parateperc);
}

void Stat::updateDati(){
    for(int i=0; i<maxPersone;i++){
        persona[i]->updateDati();
    }
}
