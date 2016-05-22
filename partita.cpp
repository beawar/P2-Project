#include "partita.h"
#include <QFont>
#include <QRadioButton>
#include <QMessageBox>

Partita::Partita(Squadra *home, Squadra *guest, Arbitro *a1, Arbitro *a2, QWidget *parent) :
    QWidget(parent), homeTeam(home), guestTeam(guest),
    goalHome(0), goalGuest(0), currentPortiereHome(0), currentPortiereGuest(0)
{
    mainLayout = new QVBoxLayout;

    QLabel* homeName = new QLabel(homeTeam->getNome(), this);
    homeName->setAlignment(Qt::AlignHCenter);
    QLabel* guestName = new QLabel(guestTeam->getNome(), this);
    guestName->setAlignment(Qt::AlignHCenter);

    QFont font;
    font.setBold(true);
    font.setPointSize(30);
    homeName->setFont(font);
    guestName->setFont(font);


    punteggio = new QLabel(tr("%1 : %2").arg(goalHome, goalGuest), this);

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

    QHBoxLayout* goalsLayout = new QHBoxLayout;
    goalsLayout->addWidget(homeName);
    goalsLayout->addWidget(punteggio);
    goalsLayout->addWidget(guestName);

    QGroupBox* goalsGroup = new QGroupBox(this);
    goalsGroup->setLayout(goalsLayout);
    goalsGroup->setObjectName("goalsGroup");
    setStyleSheet("QGroupBox#goalsGroup {border: 2px solid black } ");

    QHBoxLayout* teams = new QHBoxLayout;
    teams->addWidget(homeGroup);
    teams->addWidget(guestGroup);

    QHBoxLayout* arbitriLayout = new QHBoxLayout;
    arbitriLayout->addWidget(arbitriLabel);
    arbitriLayout->addWidget(arbitro1Label);
    arbitriLayout->addWidget(arbitro2Label);

    mainLayout->addWidget(goalsGroup);
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
    homePortiere = new QButtonGroup(this);
    QVBoxLayout* homeLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout[maxGiocatori];
    QRadioButton* homeRadio[maxGiocatori];

    int giocatoriCount = 0;
    for(int i=0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[i] = new LinePartita(homeTeam->at(i), this);
            if(dynamic_cast<Giocatore*>(homeTeam->at(i)) && giocatoriCount<maxGiocatori){
                homeRadio[giocatoriCount] = new QRadioButton(this);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(homeRadio[giocatoriCount]);
                lineLayout[giocatoriCount]->addWidget(homeLines[i], 0, Qt::AlignRight);

                homePortiere->addButton(homeRadio[giocatoriCount], i);

                homeLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                homeLayout->addWidget(homeLines[i], 0, Qt::AlignRight);

            }

            connect(homeLines[i], SIGNAL(tiro(int, bool)), this, SLOT(updatePunteggio()));
            connect(homeLines[i], SIGNAL(tiro(int, bool)), this, SLOT(tiroHome(int,bool)));
            connect(homeLines[i], SIGNAL(rigore(int,bool)), this, SLOT(rigoreHome(int,bool)));
            connect(homeLines[i], SIGNAL(ammonizione(bool)), this, SLOT(ammonizioneHome(bool)));
            connect(homeLines[i], SIGNAL(dueMinuti(bool)), this, SLOT(dueMinutiHome(bool)));
            connect(homeLines[i], SIGNAL(esclusione(bool)), this, SLOT(esclusioneHome(bool)));
            connect(homePortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereHome()));
        }
    }

    homeGroup->setLayout(homeLayout);

}

void Partita::createGuestLayout(){
    guestGroup = new QGroupBox(this);
    guestPortiere = new QButtonGroup(this);
    QVBoxLayout* guestLayout = new QVBoxLayout;
    QHBoxLayout* lineLayout[maxGiocatori];
    QRadioButton* guestRadio[maxGiocatori];

    int giocatoriCount = 0;
    for(int i=0; i<guestTeam->size(); ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines[i] = new LinePartita(guestTeam->at(i), this);
            if(dynamic_cast<Giocatore*>(guestTeam->at(i)) && giocatoriCount<maxGiocatori){
                guestRadio[giocatoriCount] = new QRadioButton(this);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(guestRadio[giocatoriCount]);
                lineLayout[giocatoriCount]->addWidget(guestLines[i], 0, Qt::AlignRight);

                guestPortiere->addButton(guestRadio[giocatoriCount], i);

                guestLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                guestLayout->addWidget(guestLines[i], 0, Qt::AlignRight);

            }

            connect(guestLines[i], SIGNAL(tiro(int, bool)), this, SLOT(updatePunteggio()));
            connect(guestLines[i], SIGNAL(tiro(int, bool)), this, SLOT(tiroGuest(int,bool)));
            connect(guestLines[i], SIGNAL(rigore(int,bool)), this, SLOT(rigoreGuest(int,bool)));
            connect(guestLines[i], SIGNAL(ammonizione(bool)), this, SLOT(ammonizioneGuest(bool)));
            connect(guestLines[i], SIGNAL(dueMinuti(bool)), this, SLOT(dueMinutiGuest(bool)));
            connect(guestLines[i], SIGNAL(esclusione(bool)), this, SLOT(esclusioneGuest(bool)));
            connect(guestPortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereGuest()));
        }
    }

    guestGroup->setLayout(guestLayout);
}

void Partita::updatePunteggio(){
    punteggio->setText(tr("%1 : %2").arg(goalHome, goalGuest));
}

void Partita::tiroHome(int val, bool aggiunto){
    emit tiroHm(val, aggiunto);
}

void Partita::rigoreHome(int val, bool aggiunto){
    emit rigoreHm(val, aggiunto);
}

void Partita::ammonizioneHome(bool aggiunto){
    emit ammonizioneHm(aggiunto);
}

void Partita::dueMinutiHome(bool aggiunto){
    emit dueMinutiHm(aggiunto);
}

void Partita::esclusioneHome(bool aggiunto){
    emit esclusioneHm(aggiunto);
}

void Partita::tiroGuest(int val, bool aggiunto){
    emit tiroGst(val, aggiunto);
}

void Partita::rigoreGuest(int val, bool aggiunto){
    emit rigoreGst(val, aggiunto);
}

void Partita::ammonizioneGuest(bool aggiunto){
    emit ammonizioneGst(aggiunto);
}

void Partita::dueMinutiGuest(bool aggiunto){
    emit dueMinutiGst(aggiunto);
}

void Partita::esclusioneGuest(bool aggiunto){
    emit esclusioneGst(aggiunto);
}

void Partita::cambiaPortiereHome(){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(homePortiere->checkedId()));
    if(p){
        currentPortiereHome = homePortiere->checkedId();
    }
    else{
        int ret = QMessageBox::warning(this, tr("Conversione necessaria"),
                                       tr("Il giocatore selezionato non è memorizzato come portire."
                                          "Per renderlo il portiere corrente è necessaria una conversione.\n"
                                          "Continuare?"),
                                       QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            Giocatore* temp = dynamic_cast<Giocatore*>(homeTeam->at(homePortiere->checkedId()));
            homeTeam->at(homePortiere->checkedId()) = new Portiere;
            homeTeam->at(homePortiere->checkedId()) = *temp;
            delete temp;
            currentPortiereHome = homePortiere->checkedId();
        }
        else{
            homePortiere->button(currentPortiereHome)->setChecked(true);
        }
    }
}

void Partita::cambiaPortiereGuest(){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(guestPortiere->checkedId()));
    if(p){
        currentPortiereGuest = guestPortiere->checkedId();
    }
    else{
        int ret = QMessageBox::warning(this, tr("Conversione necessaria"),
                                       tr("Il giocatore selezionato non è memorizzato come portire."
                                          "Per renderlo il portiere corrente è necessaria una conversione.\n"
                                          "Continuare?"),
                                       QMessageBox::Ok | QMessageBox::Cancel);
        if(ret == QMessageBox::Ok){
            Giocatore* temp = guestTeam->at(guestPortiere->checkedId());
            guestTeam->at(guestPortiere->checkedId()) = new Portiere(*temp);
            delete temp;
            currentPortiereGuest= guestPortiere->checkedId();
        }
        else{
            guestPortiere->button(currentPortiereGuest)->setChecked(true);
        }
    }

}

void Partita::terminaPartita(){
    if(goalHome > goalGuest){
        homeTeam->addVittoria(1, goalHome, goalGuest);
        guestTeam->addSconfitta(1, goalGuest, goalHome);
    }
    else if(goalHome == goalGuest){
        homeTeam->addPareggio(goalHome);
        guestTeam->addPareggio(goalGuest);
    }
    else{
        homeTeam->addSconfitta(1, goalHome, goalGuest);
        guestTeam->addVittoria(1, goalGuest, goalHome);
    }
    emit partitaTerminata();
}
