#include "tabs.h"
#include <QPixmap>
#include <QDir>
#include <QFile>
#include <QFileDialog>

Tabs::Tabs(Squadra *s1, Squadra *s2, Arbitro *arb1, Arbitro *arb2, QWidget *parent) :
    QTabWidget(parent), team1(s1), team2(s2), a1(arb1), a2(arb2),
    statTeam1(0), statTeam2(0), partita(0)
{
    if(team1 && team2 && a1 && a2){
        statTeam1 = new Stat(team1);
        statTeam2 = new Stat(team2);
        partita = new Partita(team1, team2, a1, a2);

        addTab(partita, tr("Partita"));
        addTab(statTeam1, team1->getNome());
        addTab(statTeam2, team2->getNome());

        pngOpen1 = "";
        pngOpen2 = "";

        connect(partita, SIGNAL(tiroHm(int,bool)), statTeam1, SLOT(updateDati()));
        connect(partita, SIGNAL(ammonizioneHm(bool)), statTeam1, SLOT(updateDati()));
        connect(partita, SIGNAL(dueMinutiHm(bool)), statTeam1, SLOT(updateDati()));
        connect(partita, SIGNAL(esclusioneHm(bool)), statTeam1, SLOT(updateDati()));

        connect(partita, SIGNAL(ammonizioneGst(bool)), statTeam2, SLOT(updateDati()));
        connect(partita, SIGNAL(dueMinutiGst(bool)), statTeam2, SLOT(updateDati()));
        connect(partita, SIGNAL(esclusioneGst(bool)), statTeam2, SLOT(updateDati()));

    }
}

void Tabs::exportPng(){
    if(statTeam1 && statTeam2){
        QPixmap pixmap1(statTeam1->rect().size());
        statTeam1->render(&pixmap1, QPoint(), QRegion(statTeam1->rect()));

        if(!pngOpen1.isEmpty()){
            QFile file(pngOpen1);
            pixmap1.save(&file, "PNG");
            file.close();
        }
        else{
            QString filename = QFileDialog::getSaveFileName(this, tr("Esporta come"), QDir::currentPath(), "*.png");
            if(!filename.isEmpty()){
                QFile file(filename);
                pixmap1.save(&file, "PNG");
                pngOpen1 = filename;
                file.close();
            }
        }

        QPixmap pixmap2(statTeam2->rect().size());
        statTeam2->render(&pixmap2, QPoint(), QRegion(statTeam2->rect()));
        if(!pngOpen2.isEmpty()){
            QFile file(pngOpen1);
            pixmap2.save(&file, "PNG");
            file.close();
        }
        else{
            QString filename = QFileDialog::getSaveFileName(this, tr("Esporta come"), QDir::currentPath(), "*.png");
            if(!filename.isEmpty()){
                QFile file(filename);
                pixmap2.save(&file, "PNG");
                pngOpen2 = filename;
                file.close();
            }
        }
    }
}


void Tabs::reset(){
    partita->reset();
    statTeam1->updateDati();
    statTeam2->updateDati();
}

void Tabs::termina(){
    partita->termina();
    partita->setEnabled(false);
}
