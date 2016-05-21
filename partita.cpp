#include "partita.h"
#include <QFont>

Partita::Partita(Squadra *home, Squadra *guest, Arbitro *a1, Arbitro *a2, QWidget *parent) :
    QWidget(parent), homeTeam(home), guestTeam(guest)
{
    mainLayout = new QVBoxLayout();

    QLabel* homeName = new QLabel(homeTeam->getNome(), this);
    homeName->setAlignment(Qt::AlignRight);
    QLabel* guestName = new QLabel(guestTeam->getNome(), this);
    guestName->setAlignment(Qt::AlignLeft);

    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    homeName->setFont(font);
    guestName->setFont(font);

    punteggio = new QLabel(tr("%1 : %2").arg(homeTeam->getTiriSegnati()).arg(guestTeam->getTiriSegnati()), this);
    punteggio->setAlignment(Qt::AlignHCenter);
    punteggio->setFont(font);

    QLabel* arbitriLabel = new QLabel(tr("Arbitri:"), this);
    QFont corsivo;
    corsivo.setPointSize(20);
    corsivo.setItalic(true);
    corsivo.setBold(true);
    arbitriLabel->setFont(corsivo);

    QFont arbitriFont;
    arbitriFont.setPointSize(15);

    QString arb1str = a1->getCognome() + " " + a1->getNome();
    QLabel* arbitro1Label = new QLabel(arb1str, this);
    arbitro1Label->setFont(arbitriFont);

    QString arb2str = a2->getCognome() + " " + a2->getNome();
    QLabel* arbitro2Label = new QLabel(arb2str, this);
    arbitro2Label->setFont(arbitriFont);

    createHomeLayout();
    createGuestLayout();

    QHBoxLayout* goals = new QHBoxLayout();
    goals->addWidget(homeName);
    goals->addWidget(punteggio);
    goals->addWidget(guestName);

    QHBoxLayout* teams = new QHBoxLayout();
    teams->addWidget(homeGroup);
    teams->addWidget(guestGroup);

    QHBoxLayout* arbitriLayout = new QHBoxLayout();
    arbitriLayout->addWidget(arbitriLabel);
    arbitriLayout->addWidget(arbitro1Label);
    arbitriLayout->addWidget(arbitro2Label);

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
    homeGroup = new QGroupBox(this);

    QVBoxLayout* homeLayout = new QVBoxLayout();

    for(int i=0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[i] = new LinePartita(homeTeam->at(i), this);
            connect(homeLines[i], SIGNAL(tiro(bool)), this, SLOT(updatePunteggio(bool)));
            homeLayout->addWidget(homeLines[i]);
        }
    }

    homeGroup->setLayout(homeLayout);

}

void Partita::createGuestLayout(){
    guestGroup = new QGroupBox(this);

    QVBoxLayout* guestLayout = new QVBoxLayout();

    for(int i=0; i<guestTeam->size(); ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines[i] = new LinePartita(guestTeam->at(i), this);
            connect(guestLines[i], SIGNAL(LinePartita::tiro(bool)), this, SLOT(updatePunteggio(bool)));
            guestLayout->addWidget(guestLines[i]);
        }
    }

    guestGroup->setLayout(guestLayout);
}

void Partita::updatePunteggio(){
    punteggio->setText(tr("%1 : %2").arg(homeTeam->getTiriSegnati()).arg(guestTeam->getTiriSegnati()));
}
