#include "stat.h"
#include <QVBoxLayout>

Stat::Stat(Squadra *s, QWidget *parent) :
    QWidget(parent), squadra(s)
{   
    setStyleSheet("background-image: url(:/images/images/Sfondo_logo.png)");
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
    for(int i=0; i<squadra->size() && j<maxPersone; ++i){
        if(squadra->at(i)->isChecked()){
            persona[j] = new LineStat(squadra->at(i), this);
            persona[j]->setAttribute(Qt::WA_NoSystemBackground);
            /*persona[j]->setStyleSheet("font-size: 10pt;"
                                      "text-align: center center;"
                                      "color: white;");
            */
            layout->addWidget(persona[j]);
            j++;
        }
    }
    persona[j-1]->setObjectName("LastPerson");
    setLayout(layout);

}

void Stat::createHeader(){
    headerLayout = new QHBoxLayout;

    numero = new QLabel("N°", this);
    numero->setMinimumSize(30, 30);

    QFont bold = numero->font();
    bold.setBold(true);
    numero->setFont(bold);

    cognome = new QLabel(tr("Cognome"), this);
    cognome->setMinimumSize(100, 30);
    cognome->setFont(bold);

    nome = new QLabel(tr("Nome"), this);
    nome->setMinimumSize(100, 30);
    nome->setFont(bold);

    ammo = new QLabel(this);
    ammo->setPixmap(QPixmap(":/images/images/giallo.png").scaled(30, 30));
    ammo->setMinimumSize(30, 30);
    ammo->setAlignment(Qt::AlignHCenter);

    dueMin = new QLabel(this);
    dueMin->setPixmap(QPixmap(":/images/images/two_fingers.png").scaled(30, 30));
    dueMin->setMinimumSize(80, 30);
    dueMin->setAlignment(Qt::AlignHCenter);

    escl = new QLabel(this);
    escl->setPixmap(QPixmap(":/images/images/rosso.png").scaled(30, 30));
    escl->setMinimumSize(30, 30);
    escl->setAlignment(Qt::AlignHCenter);

    reti = new QLabel(this);
    reti->setPixmap(QPixmap(":/images/images/footbal.png").scaled(30, 30));
    reti->setMinimumSize(100, 30);
    reti->setAlignment(Qt::AlignHCenter);

    parate = new QLabel(this);
    parate->setPixmap(QPixmap(":/images/images/portiere.png").scaled(30, 30));
    parate->setMinimumSize(100, 30);
    parate->setAlignment(Qt::AlignHCenter);

    perc = new QLabel(this);
    perc->setPixmap(QPixmap(":/images/images/footbal_perc.png").scaled(30, 30));
    perc->setMinimumSize(100, 30);
    perc->setAlignment(Qt::AlignHCenter);

    parateperc = new QLabel(this);
    parateperc->setPixmap(QPixmap(":/images/images/portiere_perc.png").scaled(30, 30));
    parateperc->setMinimumSize(100, 50);
    parateperc->setAlignment(Qt::AlignHCenter);

    headerLayout->addWidget(numero);
    headerLayout->addWidget(cognome);
    headerLayout->addWidget(nome);
    headerLayout->addWidget(ammo);
    headerLayout->addWidget(dueMin);
    headerLayout->addWidget(escl);
    headerLayout->addWidget(reti);
    headerLayout->addWidget(perc);
    headerLayout->addWidget(parate);
    headerLayout->addWidget(parateperc);
}

void Stat::updateDati(){
    int j = 0;
    bool last = false;
    for(int i=0; i<squadra->size() && !last; ++i){
        if(squadra->at(i)->isChecked()){
            persona[j]->updateDati(squadra->at(i));
            if(persona[j]->objectName() == "LastPerson"){
                last = true;
            }
            j++;
        }
    }
    update();
}
