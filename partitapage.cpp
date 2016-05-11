#include "partitapage.h"
#include "checklist.h"
#include <QMessageBox>


PartitaPage::PartitaPage(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizardPage(parent), squadre(sm), arbitri(am),
    s1GiocChecked(0), s1AllChecked(0), s2GiocChecked(0), s2AllChecked(0)
{ 
    for(int i=0; i<squadre->size(); ++i){
        squadre->at(i)->sortByName();
    }
    layout = new QVBoxLayout;
    createView();
    createLayout();

    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setLayout(layout);

    registerField("partita.homeTeam", squadra1ComboBox);
    registerField("partita.guestTeam", squadra2ComboBox);
    registerField("partita.arbitro1", arbitro1ComboBox);
    registerField("partita.arbitro2", arbitro2ComboBox);
}

void PartitaPage::createView(){
    nomeButton = new QRadioButton(tr("Nome"), this);
    nomeButton->setChecked(true);
    numeroButton = new QRadioButton(tr("Numero"), this);

    squadra1ComboBox = new QComboBox;
    squadra1ComboBox->setModel(squadre);

    squadra2ComboBox = new QComboBox;
    squadra2ComboBox->setModel(squadre);

    arbitro1ComboBox = new QComboBox;
    arbitro1ComboBox->setModel(arbitri);

    arbitro2ComboBox = new QComboBox;
    arbitro2ComboBox->setModel(arbitri);

    squadra1 = new CheckList(squadre->at(squadra1ComboBox->currentIndex()), this);
    squadra2 = new CheckList(squadre->at(squadra2ComboBox->currentIndex()), this);

    squadra1List = new QListView;
    squadra1List->setModel(squadra1);

    squadra2List = new QListView;
    squadra2List->setModel(squadra2);

    categoriaLabel = new QLabel(tr("Categoria: "));

    categoria = new QComboBox(this);
    categoria->addItem(tr("Regionale"));
    categoria->addItem(tr("Nazionale"));
    categoria->addItem(tr("Internazionale"));

    connect(nomeButton, SIGNAL(clicked()), this, SLOT(sort()));
    connect(numeroButton, SIGNAL(clicked()), this, SLOT(sort()));

    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));
    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));
    connect(squadra1, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));
    //connect(squadra1List, SIGNAL(clicked(QModelIndex)), this, SLOT(checkItemS1(QModelIndex)));

    connect(squadra2ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra2List, SLOT(update()));
    connect(squadra2, SIGNAL(dataChanged(QModelIndex,QModelIndex)), squadra1List, SLOT(update()));
    //connect(squadra2List, SIGNAL(clicked(QModelIndex)), this, SLOT(checkItemS2(QModelIndex)));
}

void PartitaPage::createLayout(){
    squadra1Group = new QGroupBox(tr("In Casa"));
    squadra2Group = new QGroupBox(tr("Ospiti"));
    arbitriGroup = new QGroupBox(tr("Arbitri"));
    radioGroup = new QGroupBox(tr("Ordina per:"));

    QVBoxLayout* squadra1Layout = new QVBoxLayout;
    squadra1Layout->addWidget(squadra1ComboBox);
    squadra1Layout->addWidget(squadra1List);

    QVBoxLayout* squadra2Layout = new QVBoxLayout;
    squadra2Layout->addWidget(squadra2ComboBox);
    squadra2Layout->addWidget(squadra2List);

    QHBoxLayout* arbitriLayout = new QHBoxLayout;
    arbitriLayout->addWidget(arbitro1ComboBox);
    arbitriLayout->addWidget(arbitro2ComboBox);

    QVBoxLayout* radioLayout = new QVBoxLayout;
    radioLayout->addWidget(nomeButton);
    radioLayout->addWidget(numeroButton);

    squadra1Group->setLayout(squadra1Layout);
    squadra2Group->setLayout(squadra2Layout);
    arbitriGroup->setLayout(arbitriLayout);
    radioGroup->setLayout(radioLayout);

    QHBoxLayout* squadreLayout = new QHBoxLayout;
    squadreLayout->addWidget(squadra1Group);
    squadreLayout->addWidget(radioGroup);
    squadreLayout->addWidget(squadra2Group);

    QHBoxLayout* categoriaLayout = new QHBoxLayout;
    categoriaLayout->addWidget(categoriaLabel);
    categoriaLayout->addWidget(categoria);

    layout->addLayout(categoriaLayout);
    layout->addLayout(squadreLayout);
    layout->addWidget(arbitriGroup);
}

Squadra* PartitaPage::homeTeam() const{
    return squadre->at(squadra1ComboBox->currentIndex());
}

Squadra* PartitaPage::guestTeam() const{
    return squadre->at(squadra2ComboBox->currentIndex());
}

int PartitaPage::nextId() const{
    return -1;
}

bool PartitaPage::validatePage() const{
    if(squadra1ComboBox->currentText() == squadra2ComboBox->currentText()){
        return false;
    }
    else if(arbitro1ComboBox->currentText() == arbitro2ComboBox->currentText()){
        return false;
    }
    else{
        return true;
    }

}


QString PartitaPage::getCategoria() const{
    return categoria->currentText();
}

void PartitaPage::updateList(){
    if(squadra1ComboBox->currentIndex() != -1){
        squadra1->createList(squadre->at(squadra1ComboBox->currentIndex()));
    }
    if(squadra2ComboBox->currentIndex() != -1){
        squadra2->createList(squadre->at(squadra2ComboBox->currentIndex()));
    }
}

void PartitaPage::checkItemS1(QModelIndex index){
    bool ischeck = squadra1->data(index, Qt::CheckStateRole).toBool();
    if(ischeck){
            if(dynamic_cast<Giocatore*>(homeTeam()->at(index.row()))){
                s1GiocChecked--;
            }
            else if(dynamic_cast<Allenatore*>(homeTeam()->at(index.row()))){
                s1AllChecked--;
            }   
        squadra1->setData(index, Qt::Unchecked, Qt::CheckStateRole);
    }
    else{
        bool ok = false;
        if(dynamic_cast<Giocatore*>(homeTeam()->at(index.row())) && s1GiocChecked<maxGiocatori){
            s1GiocChecked++;
            ok = true;
        }
        else if(dynamic_cast<Allenatore*>(homeTeam()->at(index.row())) && s1AllChecked<maxAllenatori){
            s1AllChecked++;
            ok = true;
        }
        if(ok){
            squadra1->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else{
            QMessageBox::warning(this, tr("Numero massimo raggiunto"),
                                 tr("E' stato raggiunto il numero massimo di giocatori (%1) "
                                    "o allenatori (%2) consentiti a referto").arg(maxGiocatori, maxAllenatori));
        }
    }

}

void PartitaPage::checkItemS2(QModelIndex index){
    bool ischeck = squadra2->data(index, Qt::CheckStateRole).toBool();
    if(ischeck){
        if(dynamic_cast<Giocatore*>(guestTeam()->at(index.row()))){
            s2GiocChecked--;
        }
        else if(dynamic_cast<Allenatore*>(guestTeam()->at(index.row()))){
            s2AllChecked--;
        }
        squadra2->setData(index, Qt::Unchecked, Qt::CheckStateRole);
    }
    else{
        bool ok = false;
        if(dynamic_cast<Giocatore*>(guestTeam()->at(index.row())) && s2GiocChecked<maxGiocatori){
            s2GiocChecked++;
            ok = true;
        }
        else if(dynamic_cast<Allenatore*>(guestTeam()->at(index.row())) && s2AllChecked<maxAllenatori){
            s2AllChecked++;
            ok = true;
        }
        if(ok){
            squadra2->setData(index, Qt::Checked, Qt::CheckStateRole);
        }
        else{
            QMessageBox::warning(this, tr("Numero massimo raggiunto"),
                                 tr("E' stato raggiunto il numero massimo di giocatori (%1) "
                                    "o allenatori (%2) consentiti a referto").arg(maxGiocatori, maxAllenatori));
        }
    }
}

void PartitaPage::sort(){
    if(nomeButton->isChecked()){
        for(int i=0; i<squadre->size(); ++i){
            squadre->at(i)->sortByName();
        }
    }
    else if(numeroButton->isChecked()){
        for(int i=0; i<squadre->size(); ++i){
            squadre->at(i)->sortByNumber();
        }
    }

    updateList();
}
