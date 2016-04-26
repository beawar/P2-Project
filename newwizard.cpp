#include "newwizard.h"


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
    squadraP = new SquadraPage;
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
    if(currentId() == Page_Persona){
        if(field("persona.giocatore").toBool()){
            Giocatore* t = new Giocatore;
            t->setNome(field("persona.nome").toString());
            t->setCognome(field("persona.cognome").toString());
            t->setAnno(field("persona.data").toDate());
            t->setNumero(field("persona.numero").toInt());
            squadre->addTesserato(t, Squadra(field("persona.squadra").toString()));
        }
        else if(field("persona.allenatore").toBool()){
            Allenatore* t = new Allenatore;
            t->setNome(field("persona.nome").toString());
            t->setCognome(field("persona.cognome").toString());
            t->setAnno(field("persona.data").toDate());
            squadre->addTesserato(t, Squadra(field("persona.squadra").toString()));
        }
        else if(field("persona.arbitro").toBool()){
            Arbitro* t = new Arbitro;
            t->setNome(field("persona.nome").toString());
            t->setCognome(field("persona.cognome").toString());
            t->setAnno(field("persona.data").toDate());
            t->setLivello(field("persona.livello").toInt());
            arbitri->addArbitro(t);
        }
    }
    else if(currentId() == Page_Squadra){
        Squadra* s = new Squadra;
        s->setNome(field("squadra.nome").toString());
        s->setSocieta(field("squadra.societa").toString());
        squadre->addSquadra(s);
    }
    else if(currentId() == Page_Partita){
        emit partitaCreata();
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
    }
    close();
}

