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

    punteggio = new QLabel(tr("%1 : %2").arg(QString::number(goalHome), QString::number(goalGuest)), this);
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
    bool portiereTrovato = false;

    for(int i=0; i<homeTeam->size(); ++i){
        if(homeTeam->at(i)->isChecked()){
            homeLines[i] = new LinePartita(homeTeam->at(i), this);
            if(dynamic_cast<Giocatore*>(homeTeam->at(i)) && giocatoriCount<maxGiocatori){
                homeRadio[giocatoriCount] = new QRadioButton(this);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(homeRadio[giocatoriCount]);
                lineLayout[giocatoriCount]->addWidget(homeLines[i], 0, Qt::AlignRight);

                homePortiere->addButton(homeRadio[giocatoriCount], i);
                connect(homePortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereHome()));

                if(!portiereTrovato && dynamic_cast<Portiere*>(homeTeam->at(i))){
                    homeRadio[giocatoriCount]->setChecked(true);
                    currentPortiereHome = i;
                    portiereTrovato = true;
                }

                homeLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                homeLayout->addWidget(homeLines[i], 0, Qt::AlignRight);

            }

            connect(homeLines[i], SIGNAL(tiro(int, bool)), this, SLOT(updatePunteggio()));
            connect(homeLines[i], SIGNAL(tiro(int, bool)), this, SLOT(tiroHome(int,bool)));
            connect(homeLines[i], SIGNAL(rigore(int,bool)), this, SLOT(updatePunteggio()));
            connect(homeLines[i], SIGNAL(rigore(int,bool)), this, SLOT(rigoreHome(int,bool)));
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(int i = 0; i<homeTeam->size() && !portiereTrovato; ++i){
            if(homeTeam->at(i)->isChecked() && dynamic_cast<Giocatore*>(homeTeam->at(i))){
                homePortiere->button(i)->setChecked(true);
                cambiaPortiereHome();
                portiereTrovato = true;
            }
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
    bool portiereTrovato = false;
    for(int i=0; i<guestTeam->size(); ++i){
        if(guestTeam->at(i)->isChecked()){
            guestLines[i] = new LinePartita(guestTeam->at(i), this);
            if(dynamic_cast<Giocatore*>(guestTeam->at(i)) && giocatoriCount<maxGiocatori){
                guestRadio[giocatoriCount] = new QRadioButton(this);
                lineLayout[giocatoriCount] = new QHBoxLayout;
                lineLayout[giocatoriCount]->addWidget(guestRadio[giocatoriCount]);
                lineLayout[giocatoriCount]->addWidget(guestLines[i], 0, Qt::AlignRight);

                guestPortiere->addButton(guestRadio[giocatoriCount], i);
                connect(guestPortiere->button(i), SIGNAL(clicked()), this, SLOT(cambiaPortiereGuest()));

                if(!portiereTrovato && dynamic_cast<Portiere*>(guestTeam->at(i))){
                    guestRadio[giocatoriCount]->setChecked(true);
                    currentPortiereGuest = i;
                    portiereTrovato = true;
                }

                guestLayout->addLayout(lineLayout[giocatoriCount]);
                giocatoriCount++;
            }
            else{
                guestLayout->addWidget(guestLines[i], 0, Qt::AlignRight);

            }

            connect(guestLines[i], SIGNAL(tiro(int, bool)), this, SLOT(updatePunteggio()));
            connect(guestLines[i], SIGNAL(tiro(int, bool)), this, SLOT(tiroGuest(int,bool)));
            connect(guestLines[i], SIGNAL(rigore(int,bool)), this, SLOT(updatePunteggio()));
            connect(guestLines[i], SIGNAL(rigore(int,bool)), this, SLOT(rigoreGuest(int,bool)));
        }
    }

    if(!portiereTrovato){
        QMessageBox::warning(this, tr("Nessun portiere disponibile"),
                             tr("In lista non è presente nessun portiere. "
                                "Verrà selezionato il primo giocatore disponibile."), QMessageBox::Ok);
        for(int i = 0; i<guestTeam->size() && !portiereTrovato; ++i){
            if(guestTeam->at(i)->isChecked() && dynamic_cast<Giocatore*>(guestTeam->at(i))){
                guestPortiere->button(i)->setChecked(true);
                cambiaPortiereGuest();
                portiereTrovato = true;
            }
        }
    }

    guestGroup->setLayout(guestLayout);
}

void Partita::updatePunteggio(){
    punteggio->setText(tr("%1 : %2").arg(QString::number(goalHome),
                                         QString::number(goalGuest)));
}

void Partita::tiroHome(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(currentPortiereGuest));
    if(p){
        bool parato = !segnato;
        p->addTiroRicevuto(val, parato);
    }
    emit dataChanged();
}

void Partita::rigoreHome(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(guestTeam->at(currentPortiereGuest));
    if(p){
        bool parato = !segnato;
        p->addRigoreRicevuto(val, parato);
    }
    emit dataChanged();
}

void Partita::tiroGuest(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(currentPortiereHome));
    if(p){
        bool parato = !segnato;
        p->addTiroRicevuto(val, parato);
    }
    emit dataChanged();
}

void Partita::rigoreGuest(int val, bool segnato){
    Portiere* p = dynamic_cast<Portiere*>(homeTeam->at(currentPortiereHome));
    if(p){
        bool parato = !segnato;
        p->addRigoreRicevuto(val, parato);
    }
    emit dataChanged();
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
            Tesserato* tesserato = homeTeam->at(homePortiere->checkedId());
            Portiere* portiere = static_cast<Portiere*>(homeTeam->at(homePortiere->checkedId()));
            delete tesserato;
            tesserato = new Portiere(*portiere);
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
            Tesserato* tesserato = guestTeam->at(guestPortiere->checkedId());
            Portiere* portiere = static_cast<Portiere*>(guestTeam->at(guestPortiere->checkedId()));
            delete tesserato;
            tesserato = new Portiere(*portiere);
            currentPortiereGuest = guestPortiere->checkedId();
        }
        else{
            guestPortiere->button(currentPortiereGuest)->setChecked(true);
        }
    }

}

void Partita::termina(){
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
}

void Partita::reset(){
    goalHome = 0;
    goalGuest = 0;

    for(int i = 0; i<homeTeam->size(); ++i){
        homeLines[i]->reset();
    }
}
