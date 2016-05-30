#include "xmlhandler.h"
#include "squadra.h"
#include <QString>


XmlHandler::XmlHandler(SquadreModel *sm, ArbitriModel *am)
    :squadreModel(sm), arbitriModel(am)
{
    xmlWriter.autoFormatting();
}

void XmlHandler::writeFile(QFile& file) throw(Err_Save){
    xmlWriter.setDevice(&file);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("HandBallStat");

    writeItem();

    xmlWriter.writeEndDocument();

    if(xmlWriter.hasError()){
        throw Err_Save();
    }
    file.close();

}

void XmlHandler::writeItem(){
    for(int i=0; i<squadreModel->size(); ++i){
        Squadra* squadra = squadreModel->at(i);

        xmlWriter.writeStartElement("Squadra");
        xmlWriter.writeTextElement("Nome", squadra->getNome());
        if(squadra->getSocieta() != ""){
            xmlWriter.writeTextElement("Società", squadra->getSocieta());
        }
        xmlWriter.writeTextElement("Vittorie", QString::number(squadra->getVittorie()));
        xmlWriter.writeTextElement("Pareggi", QString::number(squadra->getPareggi()));
        xmlWriter.writeTextElement("Sconfitte", QString::number(squadra->getSconfitte()));
        xmlWriter.writeTextElement("Penalità", QString::number(squadra->getPenalita()));

        for(int j=0; j<squadra->size(); ++j){
            const Giocatore* giocatore = dynamic_cast<const Giocatore*>(squadra->at(j));
            if(giocatore){
                xmlWriter.writeStartElement("Giocatore");
                const Portiere* portiere = dynamic_cast<const Portiere*>(giocatore);
                if(portiere){
                    xmlWriter.writeStartElement(("Portiere"));
                }
                xmlWriter.writeTextElement("Nome", giocatore->getNome());
                xmlWriter.writeTextElement("Cognome", giocatore->getCognome());
                xmlWriter.writeTextElement("Numero", QString::number(giocatore->getNumero()));
                QString data = giocatore->getData().toString("dd/MM/yyyy");
                xmlWriter.writeTextElement("Nascita", data);
                if(portiere){
                    xmlWriter.writeEndElement();
                }
                xmlWriter.writeEndElement();
            }
            else{
                const Allenatore* all = dynamic_cast<const Allenatore*>(squadra->at(j));
                xmlWriter.writeStartElement("Allenatore");
                xmlWriter.writeTextElement("Nome", all->getNome());
                xmlWriter.writeTextElement("Cognome", all->getCognome());
                QString data = all->getData().toString("dd/MM/yyyy");
                xmlWriter.writeTextElement("Nascita", data);
                xmlWriter.writeEndElement();
            }
        }
        xmlWriter.writeEndElement();
    }

    for(int i=0; i<arbitriModel->size(); ++i){
        Arbitro* arbitro = arbitriModel->at(i);
        xmlWriter.writeStartElement("Arbitro");
        xmlWriter.writeTextElement("Nome", arbitro->getNome());
        xmlWriter.writeTextElement("Cognome", arbitro->getCognome());
        QString data = arbitro->getData().toString("dd/MM/yyyy");
        xmlWriter.writeTextElement("Nascita", data);
        xmlWriter.writeTextElement("Livello", QString::number(arbitro->getLivello()));
        xmlWriter.writeEndElement();
    }
}

void XmlHandler::readFile(const QString &filename) throw(Err_Open){
    if(!filename.isEmpty()){
        QFile file(filename);
        if (!file.open(QFile::ReadOnly | QFile::Text)){
            throw Err_Open();
        }
        xmlReader.setDevice(&file);
        xmlReader.readNext();
        while(!xmlReader.atEnd()){
            if(xmlReader.isStartElement()){
                if(xmlReader.name() == "Squadra"){
                    readSquadra();
                }
                else if(xmlReader.name() == "Arbitro"){
                    readArbitro();
                }
            }
            xmlReader.readNext();
        }

        file.close();

        if(xmlReader.hasError()){
            throw Err_Open();
        }
    }
}

void XmlHandler::readSquadra(){
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Squadra");
    Squadra* squadra = new Squadra;
    while(!xmlReader.isEndElement()){
        if(xmlReader.name() == "Nome"){
            QString nome = xmlReader.readElementText();
            squadra->setNome(nome);
            squadreModel->addSquadra(squadra);
        }
        else if(xmlReader.name() == "Società"){
            QString societa = xmlReader.readElementText();
            squadra->setSocieta(societa);
        }
        else if(xmlReader.name() == "Vittorie"){
            QString vittorie = xmlReader.readElementText();
            squadra->addVittoria(vittorie.toInt());
        }
        else if(xmlReader.name() == "Pareggi"){
            QString pareggi = xmlReader.readElementText();
            squadra->addPareggio(pareggi.toInt());
        }
        else if(xmlReader.name() == "Sconfitte"){
            QString sconfitte = xmlReader.readElementText();
            squadra->addSconfitta(sconfitte.toInt());
        }
        else if(xmlReader.name() == "Penalità"){
            QString penalita = xmlReader.readElementText();
            squadra->addPenalita(penalita.toInt());
        }
        else if(xmlReader.isStartElement() && xmlReader.name() == "Giocatore"){
            readGiocatore(*squadra);
        }
        else if(xmlReader.isStartElement() && xmlReader.name() == "Allenatore"){
            readAllenatore(*squadra);
        }
        xmlReader.readNext();
    }

}

void XmlHandler::readGiocatore(const Squadra& squadra){
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Giocatore");

    Giocatore* giocatore;
    bool portiere = false;

    while(!xmlReader.isEndElement()){
        if(xmlReader.name() == "Portiere"){
            giocatore = new Portiere;
            portiere = true;
        }
        else if(xmlReader.name() == "Nome"){
            if(!portiere){
                giocatore = new Giocatore;
            }
            QString nome = xmlReader.readElementText();
            giocatore->setNome(nome);
        }
        else if(xmlReader.name() == "Cognome"){
            QString cognome = xmlReader.readElementText();
            giocatore->setCognome(cognome);
        }
        else if(xmlReader.name() == "Numero"){
            QString numero = xmlReader.readElementText();
            giocatore->setNumero(numero.toUInt());
        }
        else if(xmlReader.name() == "Nascita"){
            QString data = xmlReader.readElementText();
            giocatore->setData(QDate::fromString(data, "dd/MM/yyyy"));
        }
        xmlReader.readNext();
    }
    squadreModel->addTesserato(giocatore, squadra);
    if(portiere){
        xmlReader.readNext();
    }
}

void XmlHandler::readAllenatore(const Squadra& squadra){
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Allenatore");
    Allenatore* allenatore = new Allenatore;

    while(!xmlReader.isEndElement()){
        if(xmlReader.name() == "Nome"){
            QString nome = xmlReader.readElementText();
            allenatore->setNome(nome);
        }
        else if(xmlReader.name() == "Cognome"){
            QString cognome = xmlReader.readElementText();
            allenatore->setCognome(cognome);
        }
        else if(xmlReader.name() == "Nascita"){
            QString data = xmlReader.readElementText();
            allenatore->setData(QDate::fromString(data, "dd/MM/yyyy"));
        }
        xmlReader.readNext();
    }
    squadreModel->addTesserato(allenatore, squadra);
}

void XmlHandler::readArbitro(){
    Q_ASSERT(xmlReader.isStartElement() && xmlReader.name() == "Arbitro");
    Arbitro* arbitro = new Arbitro;

    while(!xmlReader.isEndElement()){
        if(xmlReader.name() == "Nome"){
            QString nome = xmlReader.readElementText();
            arbitro->setNome(nome);
        }
        else if(xmlReader.name() == "Cognome"){
            QString cognome = xmlReader.readElementText();
            arbitro->setCognome(cognome);
        }
        else if(xmlReader.name() == "Nascita"){
            QString data = xmlReader.readElementText();
            arbitro->setData(QDate::fromString(data, "dd/MM/yyyy"));
        }
        else if(xmlReader.name() == "livello"){
            QString livello = xmlReader.readElementText();
            arbitro->setLivello(livello.toUInt());
        }
        xmlReader.readNext();
    }
    arbitriModel->addArbitro(arbitro);
}
