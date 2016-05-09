#include "tabs.h"
#include <QPixmap>

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
    }
}

void Tabs::exportPng(){
    if(statTeam1 && statTeam2){
        QPixmap pixmap1(statTeam1->rect().size());
        statTeam1->render(&pixmap1, QPoint(), QRegion(statTeam1->rect()));
        pixmap1.save(tr("./Images/%1.png").arg(team1->getNome()));

        QPixmap pixmap2(statTeam2->rect().size());
        statTeam2->render(&pixmap2, QPoint(), QRegion(statTeam2->rect()));
        pixmap2.save(tr("./Images/%1.png").arg(team2->getNome()));
    }
}
