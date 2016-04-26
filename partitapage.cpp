#include "partitapage.h"
#include "checklist.h"

PartitaPage::PartitaPage(SquadreModel *sm, ArbitriModel *am, QWidget *parent) :
    QWizardPage(parent), squadre(sm), arbitri(am)
{ 
    layout = new QVBoxLayout;

    createView();
    createLayout();

    setLayout(layout);
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

    squadra1List = new QListView;
    squadra1List->addScrollBarWidget(new CheckList(getHomeTeam()), Qt::AlignLeft);
    connect(squadra1ComboBox, SIGNAL(currentIndexChanged(int)), squadra1List, SLOT(update()));

    squadra2List = new QListView;
    squadra2List->addScrollBarWidget(new CheckList(getGuestTeam()), Qt::AlignLeft);
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

Squadra* PartitaPage::getHomeTeam() const{
    if(squadra1ComboBox->currentData().isValid()){
        return squadra1ComboBox->currentData();

    }
    else{
        return 0;
    }
}

Squadra* PartitaPage::getGuestTeam() const{
    if(squadra2ComboBox->currentData().isValid()){
        return squadra2ComboBox->currentData();
    }
    else{
        return 0;
    }
}

Arbitro* PartitaPage::getArbitro1() const{
    if(arbitro1ComboBox->currentData().isValid()){
        return arbitro1ComboBox->currentData();
    }
    else{
        return 0;
    }
}

Arbitro* PartitaPage::getArbitro2() const{
    if(arbitro2ComboBox->currentData().isValid()){
        return arbitro2ComboBox->currentData();
    }
    else{
        return 0;
    }
}

QString PartitaPage::getCategoria () const{
    return categoria->currentText();
}
