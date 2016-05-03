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
}

void PartitaPage::createView(){
    squadra1ComboBox = new QComboBox;
    squadra1ComboBox->setModel(squadre);

    squadra2ComboBox = new QComboBox;
    squadra2ComboBox->setModel(squadre);

    arbitro1ComboBox = new QComboBox;
    arbitro1ComboBox->setModel(arbitri);
    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));

    arbitro2ComboBox = new QComboBox;
    arbitro2ComboBox->setModel(arbitri);

    squadra1 = new CheckList(squadre->at(squadra1ComboBox->currentIndex()));
    squadra2 = new CheckList(squadre->at(squadra2ComboBox->currentIndex()));

    squadra1List = new QListView;
    QStringList sl;

    if(squadra1ComboBox->currentData().isValid()){
        for(int i=0; i<squadre->at(squadra1ComboBox->currentIndex())->size(); ++i){
            sl.insert(i, squadre->at(squadra1ComboBox->currentIndex())->at(i)->getInfo());
        }
    }
    squadra1->setStringList(sl);
    squadra1List->setModel(squadra1);

    squadra2List = new QListView;
    squadra2List->setModel(squadra2);
    connect(squadra2ComboBox, SIGNAL(currentIndexChanged(int)), squadra2List, SLOT(update()));

    categoriaLabel = new QLabel(tr("Categoria: "));

    categoria = new QComboBox(this);
    categoria->addItem(tr("Regionale"));
    categoria->addItem(tr("Nazionale"));
    categoria->addItem(tr("Internazionale"));

    registerField("partita.homeTeam", squadra1ComboBox);
    registerField("partita.guestTeam", squadra2ComboBox);
    registerField("partita.arbitro1", arbitro1ComboBox);
    registerField("partita.arbitro2", arbitro2ComboBox);

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
