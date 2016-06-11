#include "newwizard.h"
#include <QMessageBox>


NewWizard::NewWizard(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizard(parent), squadre(sm), arbitri(am)
{
    if(!squadre){
        squadre = new SquadreModel;
    }
    if(!arbitri){
        arbitri = new ArbitriModel;
    }

    introP = new IntroPage(sm, am, this);
    personaP = new PersonaPage(sm, am, this);
    squadraP = new SquadraPage(sm, this);
    partitaP = new PartitaPage(sm, am, this);

    setPage(Page_Intro, introP);
    setPage(Page_Persona, personaP);
    setPage(Page_Squadra, squadraP);
    setPage(Page_Partita, partitaP);

    setStartId(Page_Intro);
    setWindowTitle(tr("Nuovo"));
    setMinimumSize(sizeHint());

    connect(personaP, SIGNAL(personaCreata()), this, SLOT(nuovaPersona()));
    connect(squadraP, SIGNAL(squadraCreata()), this, SLOT(nuovaSquadra()));

}

Squadra* NewWizard::getHomeTeam() const{
    return squadre->at(field("partita.homeTeam").toInt());
}

Squadra* NewWizard::getGuestTeam() const{
    return squadre->at(field("partita.guestTeam").toInt());
}

Arbitro* NewWizard::getArbitro1() const{
    return arbitri->at(field("partita.arbitro1").toInt());
}

Arbitro* NewWizard::getArbitro2() const{
    return arbitri->at(field("partita.arbitro2").toInt());
}

Arbitro::Categoria NewWizard::getCategoria() const{
    return partitaP->getCategoria();
}

void NewWizard::accept(){
    if(currentId() == Page_Partita){
        if(partitaP->validatePage()){
            emit partitaCreata();
            close();
        }
        else{
            QMessageBox::warning(this, tr("Informazioni invalide"), tr("Impossibile creare la partita. Ricontrollare le "
                                                                        "informazioni immesse"), QMessageBox::Ok);
        }
    }
    else{
        close();
    }
}

void NewWizard::nuovaSquadra(){
    emit squadraCreata();
    emit dataChanged(true);
}

void NewWizard::nuovaPersona(){
    emit dataChanged(true);
}

