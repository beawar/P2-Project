#include "linepartita.h"
#include <QMessageBox>
#include <QIcon>

LinePartita::LinePartita(Tesserato* t, QWidget *parent) :
    QWidget(parent), tesserato(t)
{
    numeroLabel = new QLabel(this);
    numeroLabel->setMinimumSize(50, 50);
    numeroLabel->setMaximumSize(50, 50);
    nomeLabel = new QLabel(t->getCognome() + " " + t->getNome(), this);
    nomeLabel->setMinimumSize(200, 50);
    nomeLabel->setMaximumSize(200, 50);
    goalLabel = new QLabel(this);
    goalLabel->setMinimumSize(50, 50);
    goalLabel->setMaximumSize(50, 50);
    if(dynamic_cast<Giocatore*>(tesserato) || dynamic_cast<Allenatore*>(tesserato)){
        createButtons();
    }
    createLayout();
    setLayout(layout);
}

void LinePartita::createButtons(){
    ammoButton = new PushButton(QIcon(":/images/giallo"), "", this);
    ammoButton->setMinimumSize(50, 50);
    ammoButton->setMaximumSize(50, 50);
    connect(ammoButton, SIGNAL(clicked()), this, SLOT(leftclickAmmo()));
    connect(ammoButton, SIGNAL(rightClicked()), this, SLOT(rightclickAmmo()));

    dueMinButton = new PushButton("2'", this);
    dueMinButton->setMinimumSize(50, 50);
    dueMinButton->setMaximumSize(50, 50);
    connect(dueMinButton, SIGNAL(clicked()), this, SLOT(leftclickdueMin()));
//TO DO: DOUBLE CLICK
    connect(dueMinButton, SIGNAL(rightClicked()), this, SLOT(rightclickdueMin()));

    esclButton = new PushButton(QIcon(":/images/rosso"), "", this);
    esclButton->setMinimumSize(50, 50);
    esclButton->setMaximumSize(50, 50);
    connect(esclButton, SIGNAL(clicked()), this, SLOT(leftclickEscl()));
//TO DO: DOUBLE CLICK
    connect(esclButton, SIGNAL(rightClicked()), this, SLOT(rightclickEscl()));

    tiroButton = new PushButton(QIcon(":/images/palla"), "", this);
    tiroButton->setMinimumSize(50, 50);
    tiroButton->setMaximumSize(50, 50);
    connect(tiroButton, SIGNAL(clicked()), this, SLOT(leftclickTiro()));
//TO DO: DOUBLE CLICK
    connect(tiroButton, SIGNAL(rightClicked()), this, SLOT(rightclickTiro()));

    rigoreButton = new PushButton("7m", this);
    rigoreButton->setMinimumSize(50, 50);
    rigoreButton->setMaximumSize(50, 50);
    connect(rigoreButton, SIGNAL(clicked()), this, SLOT(leftclickRigore()));
//TO DO: DOUBLE CLICK
    connect(rigoreButton, SIGNAL(rightClicked()), this, SLOT(rightclickRigore()));

}

void LinePartita::createLayout(){

    layout = new QHBoxLayout();
    layout->addWidget(numeroLabel);
    layout->addWidget(nomeLabel);
    if(!dynamic_cast<Arbitro*>(tesserato)){
        layout->addWidget(goalLabel);
        layout->addWidget(tiroButton);
        layout->addWidget(rigoreButton);
        layout->addWidget(ammoButton);
        layout->addWidget(dueMinButton);
        layout->addWidget(esclButton);
        Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
        if(g){
            numeroLabel->setText(QString::number(g->getNumero()));
            goalLabel->setText(QString::number(g->getTiriSegnati()));
        }
        else{
            numeroLabel->setText(tr("All"));
        }
    }
}

void LinePartita::rightclickAmmo(){
    ammoButton->setStyleSheet("background-color: ");
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        g->ammonito(false);
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            a->ammonito(false);
        }
    }
    emit ammonizione(false);
    update();
}

void LinePartita::leftclickAmmo(){
    ammoButton->setStyleSheet("background-color: yellow");
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->ammonito(true);
            emit ammonizione(true);
        }
        catch(Err_Ammonizione e){
            QMessageBox::warning(this, tr("Errore"),
                                 tr("Giocatore già ammonito"),
                                 QMessageBox::Cancel);
        }
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            try{
                a->ammonito(true);
                emit ammonizione(true);
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Allenatore già ammonito"),
                                     QMessageBox::Cancel);
            }
        }
    }
    update();
}

void LinePartita::rightclickdueMin(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        g->set2Minuti(-1);
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            a->set2Minuti(false);
        }
    }
    emit dueMinuti(false);
    update();
}

void LinePartita::leftclickdueMin(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->set2Minuti();
            emit dueMinuti(true);
        }
        catch(Err_DueMinuti e){
            QMessageBox::warning(this, tr("Errore"),
                                 tr("Questo giocatore ha già %1 esclusioni temporanee").arg(QString::number(g->max2Minuti)),
                                 QMessageBox::Cancel);
        }
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            try{
                a->set2Minuti(true);
                emit dueMinuti(true);
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Questo allenatore ha già %1 esclusione temporanea").arg(QString::number(a->max2Minuti)),
                                     QMessageBox::Cancel);
            }
        }
    }
    update();
}

void LinePartita::rightclickEscl(){
    esclButton->autoFillBackground();
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        g->escluso(false);
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            a->escluso(false);
        }
    }
    emit esclusione(false);
    update();
}

void LinePartita::leftclickEscl(){
    esclButton->setStyleSheet("background-color: red");
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->escluso();
            emit esclusione(true);
        }
        catch(Err_Esclusione e){
            QMessageBox::warning(this, tr("Errore"),
                                 tr("Giocatore già espulso"),
                                 QMessageBox::Cancel);
        }
    }
    else{
        Allenatore* a = dynamic_cast<Allenatore*>(tesserato);
        if(a){
            try{
                a->set2Minuti(true);
                emit esclusione(true);
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Allenatore già espulso"),
                                     QMessageBox::Cancel);
            }
        }
    }
    update();
}

void LinePartita::rightclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(tiroButton->isChecked()){
        g->setTiro(-1, true);
        emit tiro(-1, true);
    }
    else{
        g->setTiro(-1, false);
        emit tiro(-1, false);
    }
    update();
}

void LinePartita::leftclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(tiroButton->isChecked()){
        g->setTiro(1, true);
        emit tiro(1, true);
    }
    else{
        g->setTiro(1, false);
        emit tiro(1, false);
    }
    update();
}

void LinePartita::rightclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g->isChecked()){
        g->setRigore(-1, true);
        emit rigore(-1, true);
    }
    else{
        g->setRigore(-1, false);
        emit rigore(-1, false);
    }
    update();
}

void LinePartita::leftclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g->isChecked()){
        g->setRigore(1, true);
        emit rigore(1, true);
    }
    else{
        g->setRigore(1, false);
        emit rigore(1, false);
    }
    update();
}

