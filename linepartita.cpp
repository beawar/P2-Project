#include "linepartita.h"
#include <QMessageBox>
#include <QIcon>

LinePartita::LinePartita(Tesserato* t, QWidget *parent) :
    QWidget(parent), tesserato(t)
{
    info = new QLabel(t->getInfo());
    if(dynamic_cast<Giocatore*>(tesserato) || dynamic_cast<Allenatore*>(tesserato)){
        createButtons();
    }
    createLayout();
    setLayout(layout);
}

void LinePartita::createButtons(){
    ammoButton = new PushButton("./Images/giallo.png");
    ammoButton->resize(100, 100);
    connect(ammoButton, SIGNAL(clicked()), this, SLOT(leftclickAmmo()));
    connect(ammoButton, SIGNAL(rightClicked()), this, SLOT(rightclickAmmo()));

    dueMinButton = new PushButton("2'");
    dueMinButton->resize(100, 100);
    connect(dueMinButton, SIGNAL(clicked()), this, SLOT(leftclickdueMin()));
    connect(dueMinButton, SIGNAL(rightClicked()), this, SLOT(rightclickdueMin()));

    esclButton = new PushButton(QIcon("./Images/rosso.png"));
    esclButton->resize(100, 100);
    connect(esclButton, SIGNAL(clicked()), this, SLOT(leftclickEscl()));
    connect(esclButton, SIGNAL(rightClicked()), this, SLOT(rightclickEscl()));

    tiroButton = new PushButton(QIcon("./Images/ball.jpg"));
    tiroButton->resize(100, 100);
    tiroButton->setCheckable(true);
    connect(tiroButton, SIGNAL(clicked()), this, SLOT(leftclickTiro()));
    connect(tiroButton, SIGNAL(rightClicked()), this, SLOT(rightclickTiro()));

    rigoreButton = new PushButton("7m");
    rigoreButton->resize(100, 100);
    rigoreButton->setCheckable(true);
    connect(rigoreButton, SIGNAL(clicked()), this, SLOT(leftclickRigore()));
    connect(rigoreButton, SIGNAL(rightClicked()), this, SLOT(rightclickRigore()));

}

void LinePartita::createLayout(){

    layout = new QHBoxLayout;
    layout->addWidget(info);
    if(!dynamic_cast<Arbitro*>(tesserato)){
        Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
        if(g){
            goalLabel = new QLabel(QString::number(g->getTiriSegnati()));
            goalLabel->resize(200, 100);
            layout->addWidget(goalLabel);
            layout->addWidget(tiroButton);
        }
        else{
            layout->addStretch(400);
        }
        layout->addWidget(ammoButton);
        layout->addWidget(dueMinButton);
        layout->addWidget(esclButton);
    }
}

void LinePartita::rightclickAmmo(){
    ammoButton->autoFillBackground();
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
     update();
     emit valueChanged();
}

void LinePartita::leftclickAmmo(){
    ammoButton->setStyleSheet("background-color: yellow");
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->ammonito(true);
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
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Allenatore già ammonito"),
                                     QMessageBox::Cancel);
            }
        }
    }
     update();
     emit valueChanged();
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
     update();
     emit valueChanged();
}

void LinePartita::leftclickdueMin(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->set2Minuti();
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
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Questo allenatore ha già %1 esclusione temporanea").arg(QString::number(a->max2Minuti)),
                                     QMessageBox::Cancel);
            }
        }
    }
     update();
     emit valueChanged();
}

void LinePartita::rightclickEscl(){
    ammoButton->autoFillBackground();
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
     update();
     emit valueChanged();
}

void LinePartita::leftclickEscl(){
    ammoButton->setStyleSheet("background-color: red");
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g){
        try{
            g->escluso();
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
            }
            catch(Err_Ammonizione){
                QMessageBox::warning(this, tr("Errore"),
                                     tr("Allenatore già espulso"),
                                     QMessageBox::Cancel);
            }
        }
    }
     update();
     emit valueChanged();
}

void LinePartita::rightclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(tiroButton->isChecked()){
        g->setTiro(-1, true);
    }
    else{
        g->setTiro(-1, false);
    }
     update();
     emit valueChanged();
}

void LinePartita::leftclickTiro(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(tiroButton->isChecked()){
        g->setTiro(1, true);
    }
    else{
        g->setTiro(1, false);
    }
     update();
     emit valueChanged();
}

void LinePartita::rightclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g->isChecked()){
        g->setRigore(-1, false);
    }
    else{
        g->setRigore(-1, false);
    }
    update();
    emit valueChanged();
}

void LinePartita::leftclickRigore(){
    Giocatore* g = dynamic_cast<Giocatore*>(tesserato);
    if(g->isChecked()){
        g->setRigore(1, true);
    }
    else{
        g->setRigore(1, true);
    }
    update();
    emit valueChanged();
}

