#include "newwizard.h"
#include <QMessageBox>


NewWizard::NewWizard(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizard(parent), squadre(sm), arbitri(am)
{
    if(!sm){
        sm = new SquadreModel;
    }
    if(!am){
        am = new ArbitriModel;
    }

    introP = new IntroPage(sm, am);
    personaP = new PersonaPage(sm, am);
    squadraP = new SquadraPage(sm);
    partitaP = new PartitaPage(sm, am);

    setPage(Page_Intro, introP);
    setPage(Page_Persona, personaP);
    setPage(Page_Squadra, squadraP);
    setPage(Page_Partita, partitaP);

    setStartId(Page_Intro);
    setWindowTitle(tr("Nuovo"));
    setMinimumSize(QSizePolicy::Fixed, QSizePolicy::Fixed);
    if(currentId() != Page_Partita){
        setMaximumSize(500, 360);
    }


    setDefaultProperty("QComboBox", "currentData", "currentIndexChanged");
}

Squadra* NewWizard::getHomeTeam() const{
    return partitaP->getHomeTeam();
}

Squadra* NewWizard::getGuestTeam() const{
    return partitaP->getGuestTeam();
}

Arbitro* NewWizard::getArbitro1() const{
    return partitaP->getArbitro1();
}

Arbitro* NewWizard::getArbitro2() const{
    return partitaP->getArbitro2();
}

void NewWizard::accept(){
    if(currentId() == Page_Partita){
        if(partitaP->validatePage()){
            if(partitaP->getCategoria() == tr("Regionale")){
                partitaP->getArbitro1()->addPRegionale();
                partitaP->getArbitro2()->addPRegionale();
            }
            else if(partitaP->getCategoria() == tr("Nazionale")){
                partitaP->getArbitro1()->addPNazionale();
                partitaP->getArbitro2()->addPNazionale();
            }
            else if(partitaP->getCategoria() == tr("Internazionale")){
                partitaP->getArbitro1()->addPInternaz();
                partitaP->getArbitro2()->addPInternaz();
            }
            emit partitaCreata();
        }
        else{
            QMessageBox::warning(this, tr("Informazioni invalide"), tr("Impossibile creare la partita. Ricontrollare le "
                                                                        "informazioni immesse"), QMessageBox::Ok);
        }
    }
    close();
}

