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

    for(int i=0; i<squadra->size(); ++i){
        persona[i] = new LineStat(squadra->at(i), this);
        layout->addWidget(persona[i]);
    }
    persona[squadra->size() - 1]->setObjectName("LastPerson");

    setStyleSheet("LineStat {border-top: 1px groove grey }");
    setStyleSheet("LineStat#LastPerson {border-bottom: 1px groove grey }");
    setStyleSheet("QWidget { background-image: url(qrc:/images/images/Sfondo.png) }");
    setLayout(layout);
}

void Stat::createHeader(){
    headerLayout = new QHBoxLayout;

    numero = new QLabel("N°", this);
    numero->setMinimumSize(50, 50);
    cognome = new QLabel(tr("Cognome"), this);
    cognome->setMinimumSize(100, 50);
    nome = new QLabel(tr("Nome"), this);
    nome->setMinimumSize(100, 50);
    ammo = new QLabel(tr("Amm."), this);
    ammo->setMinimumSize(50, 50);
    dueMin = new QLabel(tr("2 Min."), this);
    dueMin->setMinimumSize(80, 50);
    escl = new QLabel(tr("Escl."), this);
    escl->setMinimumSize(50, 50);
    reti = new QLabel(tr("Reti (Rigori)"), this);
    reti->setMinimumSize(100, 50);
    parate = new QLabel(tr("Parate (Rigori)"), this);
    parate->setMinimumSize(100, 50);
    perc = new QLabel("%", this);
    perc->setMinimumSize(100, 50);
    parateperc = new QLabel(tr("% Parate"));
    parateperc->setMinimumSize(100, 50);

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
