#include "partitapage.h"
#include "checklist.h"

PartitaPage::PartitaPage(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizardPage(parent), squadre(sm), arbitri(am)
{ 
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
    squadra1ComboBox = new QComboBox;
    squadra1ComboBox->setModel(squadre);

    squadra2ComboBox = new QComboBox;
    squadra2ComboBox->setModel(squadre);

    arbitro1ComboBox = new QComboBox;
    arbitro1ComboBox->setModel(arbitri);

    arbitro2ComboBox = new QComboBox;
    arbitro2ComboBox->setModel(arbitri);

    squadra1 = new CheckList(squadre->at(squadra1ComboBox->currentIndex()));
    squadra2 = new CheckList(squadre->at(squadra2ComboBox->currentIndex()));

    squadra1List = new QListView;
    squadra1List->setModel(squadra1);
    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));
    connect(squadra1List, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(checkItem(CheckList*, QModelIndex)));
    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), squadra1List, SLOT(update()));

    squadra2List = new QListView;
    squadra2List->setModel(squadra2);
    connect(squadra2ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList()));
    connect(squadra1List, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(checkItem(CheckList*, QModelIndex)));
    connect(squadra2ComboBox, SIGNAL(currentIndexChanged(int)), squadra2List, SLOT(update()));

    categoriaLabel = new QLabel(tr("Categoria: "));

    categoria = new QComboBox(this);
    categoria->addItem(tr("Regionale"));
    categoria->addItem(tr("Nazionale"));
    categoria->addItem(tr("Internazionale"));

}

void PartitaPage::createLayout(){
    squadra1Group = new QGroupBox(tr("In Casa"));
    squadra2Group = new QGroupBox(tr("Ospiti"));
    arbitriGroup = new QGroupBox(tr("Arbitri"));

    QVBoxLayout* squadra1Layout = new QVBoxLayout;
    squadra1Layout->addWidget(squadra1ComboBox);
    squadra1Layout->addWidget(squadra1List);

    QVBoxLayout* squadra2Layout = new QVBoxLayout;
    squadra2Layout->addWidget(squadra2ComboBox);
    squadra2Layout->addWidget(squadra2List);

    QHBoxLayout* arbitriLayout = new QHBoxLayout;
    arbitriLayout->addWidget(arbitro1ComboBox);
    arbitriLayout->addWidget(arbitro2ComboBox);

    squadra1Group->setLayout(squadra1Layout);
    squadra2Group->setLayout(squadra2Layout);
    arbitriGroup->setLayout(arbitriLayout);

    QHBoxLayout* squadreLayout = new QHBoxLayout;
    squadreLayout->addWidget(squadra1Group);
    squadreLayout->addWidget(squadra2Group);

    QHBoxLayout* categoriaLayout = new QHBoxLayout;
    categoriaLayout->addWidget(categoriaLabel);
    categoriaLayout->addWidget(categoria);

    layout->addLayout(categoriaLayout);
    layout->addLayout(squadreLayout);
    layout->addWidget(arbitriGroup);
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
    squadra1->createList(squadre->at(squadra1ComboBox->currentIndex()));
    squadra2->createList(squadre->at(squadra2ComboBox->currentIndex()));
    emit update();
}

void PartitaPage::checkItem(CheckList* clist, QModelIndex index){
    bool ischeck = clist->data(index, Qt::CheckStateRole).toBool();
    if(ischeck){
        clist->setData(index, Qt::Unchecked, Qt::Unchecked);
    }
    else{
        clist->setData(index, Qt::Checked, Qt::Checked);
    }
    emit update();
}
