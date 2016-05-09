#include "partita.h"
#include <QFont>

Partita::Partita(Squadra *home, Squadra *guest, Arbitro *a1, Arbitro *a2, QWidget *parent) :
    QWidget(parent), homeTeam(home), guestTeam(guest)
{
    mainLayout = new QVBoxLayout;

    QLabel* homeName = new QLabel(homeTeam->getNome());
    homeName->setAlignment(Qt::AlignRight);
    QLabel* guestName = new QLabel(guestTeam->getNome());
    guestName->setAlignment(Qt::AlignLeft);

    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    homeName->setFont(font);
    guestName->setFont(font);

    punteggio = new QLabel(tr("%1 : %2").arg(homeTeam->getTiriSegnati()).arg(guestTeam->getTiriSegnati()));
    punteggio->setAlignment(Qt::AlignHCenter);
    punteggio->setFont(font);

    QLabel* arbitriLabel = new QLabel(tr("Arbitri"));
    QFont corsivo;
    corsivo.setPointSize(20);
    corsivo.setItalic(true);
    corsivo.setBold(true);
    arbitriLabel->setFont(corsivo);

    LinePartita* arbitro1 = new LinePartita(a1, this);
    LinePartita* arbitro2 = new LinePartita(a2, this);

    createHomeLayout();
    createGuestLayout();

    QHBoxLayout* goals = new QHBoxLayout;
    goals->addWidget(homeName, 1);
    goals->addWidget(punteggio, 1);
    goals->addWidget(guestName);

    QHBoxLayout* teams = new QHBoxLayout;
    teams->addWidget(homeGroup);
    teams->addWidget(guestGroup);

    QHBoxLayout* arbitriLayout = new QHBoxLayout;
    arbitriLayout->addWidget(arbitriLabel);
    arbitriLayout->addWidget(arbitro1);
    arbitriLayout->addWidget(arbitro2);

    mainLayout->addLayout(goals);
    mainLayout->addLayout(teams);
    mainLayout->addLayout(arbitriLayout);

    setLayout(mainLayout);

}

Squadra* Partita::getHomeTeam() const{
    return homeTeam;
}

Squadra* Partita::getGuestTeam() const{
    return guestTeam;
}

void Partita::createHomeLayout(){
    homeGroup = new QGroupBox;

    QVBoxLayout* homeLayout = new QVBoxLayout;

    for(int i=0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[i] = new LinePartita(homeTeam->at(i), this);
            connect(homeLines[i], SIGNAL(LinePartita::valueChanged()), this, SLOT(update()));
            homeLayout->addWidget(homeLines[i]);
        }
    }

    homeGroup->setLayout(homeLayout);

}

void Partita::createGuestLayout(){
    guestGroup = new QGroupBox;

    QVBoxLayout* guestLayout = new QVBoxLayout;

    for(int i=0; i<guestTeam->size(); ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines[i] = new LinePartita(guestTeam->at(i), this);
            connect(guestLines[i], SIGNAL(LinePartita::valueChanged()), this, SLOT(update()));
            guestLayout->addWidget(guestLines[i]);
        }
    }

    guestGroup->setLayout(guestLayout);
}
