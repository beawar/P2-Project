#include "stat.h"
#include <QVBoxLayout>

Stat::Stat(Squadra *s, QWidget *parent) :
    QWidget(parent), squadra(s)
{
    createHeader();

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(headerLayout);

    for(int i=0; i<squadra->size(); ++i){
        persona[i] = new LineStat(squadra->at(i), this);
        layout->addWidget(persona[i]);
    }

    setLayout(layout);
}

void Stat::createHeader(){
    headerLayout = new QHBoxLayout;

    numero = new QLabel("N°");
    numero->setBaseSize(100, 100);
    cognome = new QLabel(tr("Cognome"));
    cognome->setBaseSize(500, 100);
    nome = new QLabel(tr("Nome"));
    nome->setBaseSize(500, 100);
    ammo = new QLabel("Amm.");
    ammo->setBaseSize(100, 100);
    dueMin = new QLabel("2 Min.");
    dueMin->setBaseSize(200, 100);
    escl = new QLabel("Escl.");
    escl->setBaseSize(100, 100);
    reti = new QLabel("Reti (Rigori)");
    reti->setBaseSize(500, 100);
    perc = new QLabel("%");
    perc->setBaseSize(200, 100);

    headerLayout->addWidget(numero);
    headerLayout->addWidget(cognome);
    headerLayout->addWidget(nome);
    headerLayout->addWidget(ammo);
    headerLayout->addWidget(dueMin);
    headerLayout->addWidget(escl);
    headerLayout->addWidget(reti);
    headerLayout->addWidget(perc);
}

void Stat::updateDati(){
    for(int i=0; i<maxPersone;i++){
        persona[i]->updateDati();
    }
}
