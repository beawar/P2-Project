#include "editor.h"

Editor::Editor(SquadreModel*sm, ArbitriModel*am, QWidget *parent) :
    QDialog(parent), squadre(sm), arbitri(am)
{   
    createMainEditor();
    createTesseratoEditor();
    createSquadraEditor();
    createArbitroEditor();

    mainWidget =
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(radioGroup);
    mainLayout->addWidget(tesseratoWidget);
    mainLayout->addWidget(squadraWidget);
    mainLayout->addWidget(arbitroWidget);
    mainLayout->addLayout(pushLayout);
    pushLayout->setAlignment(mainLayout, Qt::AlignBottom);


    //updateLayout();

    setWindowTitle(tr("Editor"));
    setMinimumSize(sizeHint());
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void Editor::createMainEditor(){
    QRadioButton* tesseratoRadio = new QRadioButton(tr("Tesserati"), this);
    tesseratoRadio->setChecked(true);
    QRadioButton* squadraRadio = new QRadioButton(tr("Squadre"), this);
    QRadioButton* arbitroRadio = new QRadioButton(tr("Arbiri"), this);

    radioButtonGroup = new QButtonGroup(this);
    radioButtonGroup->addButton(tesseratoRadio, id_tesserato);
    radioButtonGroup->addButton(squadraRadio, id_squadra);
    radioButtonGroup->addButton(arbitroRadio, id_arbitro);
    connect(radioButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(updateLayout()));

    QPushButton* insertButton = new QPushButton(tr("Inserisci"), this);
    QPushButton* removeButton = new QPushButton(tr("Elimina"), this);
    QPushButton* okButton = new QPushButton(tr("Ok"), this);

    connect(insertButton, SIGNAL(clicked()), this, SLOT(modifica()));
    connect(removeButton, SIGNAL(clicked()), this, SLOT(rimuovi()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(close()));

    listView = new QListView(this);
    connect(listView->selectionModel(), SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this, SLOT(itemSelected(QModelIndex, QModelIndex)));

    QHBoxLayout* radioLayout = new QHBoxLayout(this);
    radioLayout->addWidget(radioButtonGroup->button(id_tesserato));
    radioLayout->addWidget(radioButtonGroup->button(id_squadra));
    radioLayout->addWidget(radioButtonGroup->button(id_arbitro));

    radioGroup = new QGroupBox(tr("Scegli cosa modificare:"), this);
    radioGroup->setLayout(radioLayout);

    pushLayout = new QHBoxLayout(this);
    pushLayout->addWidget(insertButton);
    pushLayout->addWidget(removeButton);
    pushLayout->addWidget(okButton);
}

void Editor::createTesseratoEditor(){
    squadraLabel = new QLabel(tr("Squadra:"), this);
    squadreComboBox = new QComboBox(this);
    squadreComboBox->setModel(squadre);
    connect(squadreComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateList(int)));

    tesserati = new CheckList(squadre->at(squadreComboBox->currentIndex()), false, this);

    nomeTLabel = new QLabel(tr("Nome:"), this);
    nomeTEdit = new QLineEdit(this);

    cognomeTLabel = new QLabel(tr("Cognome:"), this);
    cognomeTEdit = new QLineEdit(this);

    dataTLabel = new QLabel(tr("Data di nascita:"), this);
    dataTEdit = new QDateEdit(this);
    dataTEdit->setMaximumDate(QDate::currentDate());
    dataTEdit->setDisplayFormat("dd/MM/yyyy");

    numeroLabel = new QLabel(tr("Numero:"), this);
    numeroEdit = new QSpinBox(this);
    numeroEdit->setRange(1, 99);

    QGridLayout* gridTLayout = new QGridLayout(this);
    gridTLayout->addWidget(nomeTLabel, 1, 1);
    gridTLayout->addWidget(nomeTEdit, 1, 2, 1, 2);
    gridTLayout->addWidget(cognomeTLabel, 2, 1);
    gridTLayout->addWidget(cognomeTEdit, 2, 2, 1, 2);
    gridTLayout->addWidget(dataTLabel, 3, 1);
    gridTLayout->addWidget(dataTEdit, 3, 2);
    gridTLayout->addWidget(numeroLabel, 4, 1);
    gridTLayout->addWidget(numeroEdit, 4, 2);

    QHBoxLayout* comboBoxLayout = new QHBoxLayout(this);
    comboBoxLayout->addWidget(squadraLabel);
    comboBoxLayout->addWidget(squadreComboBox);

    QVBoxLayout* listaLayout = new QVBoxLayout(this);
    listaLayout->addLayout(comboBoxLayout);
    listaLayout->addWidget(listView);

    QHBoxLayout* tesseratoLayout = new QHBoxLayout(this);
    tesseratoLayout->addLayout(gridTLayout);
    tesseratoLayout->addLayout(listaLayout);

    tesseratoWidget = new QWidget(this);
    tesseratoWidget->setLayout(tesseratoLayout);
    tesseratoWidget->setMaximumSize(tesseratoWidget->sizeHint());
}

void Editor::createSquadraEditor(){
    nomeSLabel = new QLabel(tr("Nome:"), this);
    nomeSLabel->setAlignment(Qt::AlignLeft);
    nomeSEdit = new QLineEdit(this);

    societaLabel = new QLabel(tr("Società:"), this);
    societaLabel->setAlignment(Qt::AlignLeft);
    societaEdit = new QLineEdit(this);

    penalitaLabel = new QLabel(tr("Penalità;"), this);
    penalitaLabel->setAlignment(Qt::AlignLeft);
    penalitaEdit = new QSpinBox(this);
    penalitaEdit->setRange(0, +99);

    QGridLayout* gridSLayout = new QGridLayout(this);
    gridSLayout->addWidget(nomeSLabel, 1, 1);
    gridSLayout->addWidget(nomeSEdit, 1, 2, 1, 2);
    gridSLayout->addWidget(societaLabel, 2, 1);
    gridSLayout->addWidget(societaEdit, 2, 2, 1, 2);
    gridSLayout->addWidget(penalitaLabel, 3, 1);
    gridSLayout->addWidget(penalitaEdit, 3, 2);

    QHBoxLayout* squadraLayout = new QHBoxLayout(this);
    squadraLayout->addWidget(listView);
    squadraLayout->addLayout(gridSLayout);

    squadraWidget = new QWidget(this);
    squadraWidget->setLayout(squadraLayout);
}

void Editor::createArbitroEditor(){
    nomeALabel = new QLabel(tr("Nome:"), this);
    nomeAEdit = new QLineEdit(this);

    cognomeALabel = new QLabel(tr("Cognome:"), this);
    cognomeAEdit = new QLineEdit(this);

    dataALabel = new QLabel(tr("Data di nascita:"), this);
    dataAEdit = new QDateEdit(this);
    dataAEdit->setMaximumDate(QDate::currentDate());
    dataAEdit->setDisplayFormat("dd/MM/yyyy");

    livelloLabel = new QLabel(tr("Livello:"), this);
    livelloEdit = new QSpinBox(this);
    livelloEdit->setRange(0, 3);

    QGridLayout* gridALayout = new QGridLayout(this);
    gridALayout->addWidget(nomeALabel, 1, 1);
    gridALayout->addWidget(nomeAEdit, 1, 2, 1, 2);
    gridALayout->addWidget(cognomeALabel, 2, 1);
    gridALayout->addWidget(cognomeAEdit, 2, 2, 1, 2);
    gridALayout->addWidget(dataALabel, 3, 1);
    gridALayout->addWidget(dataAEdit, 3, 2);
    gridALayout->addWidget(livelloLabel, 4, 1);
    gridALayout->addWidget(livelloEdit, 4, 2);

    QHBoxLayout* arbitroLayout = new QHBoxLayout(this);
    arbitroLayout->addWidget(listView);
    arbitroLayout->addLayout(gridALayout);

    arbitroWidget = new QWidget(this);
    arbitroWidget->setLayout(arbitroLayout);

}

void Editor::modifica(){
    switch(radioButtonGroup->checkedId()){
        case id_tesserato:
            modificaTesserato();
            break;
        case id_squadra:
            modificaSquadra();
            break;
        case id_arbitro:
            modificaArbitro();
            break;
    }
    updateList(squadreComboBox->currentIndex());
}

void Editor::modificaTesserato(){
    Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
    int index = listView->selectionModel()->currentIndex().row();
    Giocatore* gioc = dynamic_cast<Giocatore*>(squadra->at(index));
    if(gioc){
        Giocatore g;
        g.setNome(nomeTEdit->text());
        g.setCognome(cognomeTEdit->text());
        g.setNumero(numeroEdit->value());
        squadra->modificaTesserato(gioc, g);
    }
    else{
        Allenatore* all = dynamic_cast<Allenatore*>(squadra->at(index));
        if(all){
            Allenatore a;
            a.setNome(nomeTEdit->text());
            a.setCognome(cognomeTEdit->text());
            squadra->modificaTesserato(all, a);
        }
    }
    updateList(squadreComboBox->currentIndex());
}

void Editor::modificaSquadra(){
    int index = listView->selectionModel()->currentIndex().row();
    Squadra nuova;
    nuova.setNome(nomeSEdit->text());
    nuova.setSocieta(societaEdit->text());
    nuova.addPenalita(penalitaEdit->value());
    squadre->modificaSquadra(squadre->at(index), nuova);
    updateList(INT_MIN);
}

void Editor::modificaArbitro(){
    int index = listView->selectionModel()->currentIndex().row();
    Arbitro* arb = arbitri->at(index);
    Arbitro a;
    a.setNome(nomeTEdit->text());
    a.setCognome(cognomeTEdit->text());
    a.setLivello(livelloEdit->value());
    arbitri->modificaArbitro(arb, a);
    updateList(INT_MIN);
}

void Editor::rimuovi(){
    switch(radioButtonGroup->checkedId()){
        case id_tesserato:
            rimuoviTesserato();
            break;
        case id_squadra:
            rimuoviSquadra();
            break;
        case id_arbitro:
            rimuoviArbitro();
            break;
        default:
            break;
    }
}

void Editor::rimuoviTesserato(){
    Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
    int index = listView->selectionModel()->currentIndex().row();
    squadra->removeTesserato(squadra->at(index));
    updateList(squadreComboBox->currentIndex());
}

void Editor::rimuoviSquadra(){
    int index = listView->selectionModel()->currentIndex().row();
    squadre->removeSquadra(squadre->at(index));
    updateList(INT_MIN);
}

void Editor::rimuoviArbitro(){
    int index = listView->selectionModel()->currentIndex().row();
    arbitri->removeArbitro(arbitri->at(index));
    updateList(INT_MIN);
}

void Editor::updateList(int index){
    switch(radioButtonGroup->checkedId()){
        case id_tesserato:
            tesserati->createList(squadre->at(index));
            listView->setModel(tesserati);
            break;
        case id_squadra:
            listView->setModel(squadre);
            break;
        case id_arbitro:
            listView->setModel(arbitri);
            break;
        default:
            break;
    }
    update();
}

void Editor::updateLayout(){

    switch (radioButtonGroup->checkedId()) {
        case id_tesserato:
            tesseratoWidget->setVisible(true);
            squadraWidget->hide();
            arbitroWidget->hide();
            break;
        case id_squadra:
            tesseratoWidget->hide();
            squadraWidget->setVisible(true);
            arbitroWidget->hide();
            break;
        case id_arbitro:
            tesseratoWidget->hide();
            squadraWidget->hide();
            arbitroWidget->setVisible(true);
            break;
        default:
            tesseratoWidget->hide();
            squadraWidget->hide();
            arbitroWidget->hide();
            break;
    }
    updateList(squadreComboBox->currentIndex());
}

void Editor::itemSelected(QModelIndex current, QModelIndex previous){
    Q_UNUSED(previous);
    if(!current.isValid()){
        switch (radioButtonGroup->checkedId()) {
            case id_tesserato:
                nomeTEdit->clear();
                cognomeTEdit->clear();
                dataTEdit->clear();
                numeroEdit->clear();
            break;
            case id_squadra:
                nomeSEdit->clear();
                societaEdit->clear();
                penalitaEdit->clear();
                break;
            case id_arbitro:
                nomeAEdit->clear();
                cognomeAEdit->clear();
                dataAEdit->clear();
                livelloEdit->clear();
                break;
            default:
            break;
        }
    }
    else{
        Squadra* squadra = squadre->at(squadreComboBox->currentIndex());
        switch(radioButtonGroup->checkedId()){
            case id_tesserato:
            {
                nomeTEdit->setText(squadra->at(current.row())->getNome());
                cognomeTEdit->setText(squadra->at(current.row())->getCognome());
                dataTEdit->setDate(squadra->at(current.row())->getAnno());
                Giocatore* g = dynamic_cast<Giocatore*>(squadra->at(current.row()));
                if(g){
                    numeroEdit->setEnabled(true);
                    numeroEdit->setValue(g->getNumero());
                }
                else{
                    numeroEdit->setDisabled(true);
                }
            }
            break;
            case id_squadra:
                nomeSEdit->setText(squadre->at(current.row())->getNome());
                societaEdit->setText(squadre->at(current.row())->getSocieta());
                penalitaEdit->setValue(squadre->at(current.row())->getPenalita());
            break;
            case id_arbitro:
                nomeAEdit->setText(arbitri->at(current.row())->getNome());
                cognomeAEdit->setText(arbitri->at(current.row())->getCognome());
                dataAEdit->setDate(arbitri->at(current.row())->getAnno());
                livelloEdit->setValue(arbitri->at(current.row())->getLivello());
            break;
            default:
            break;
        }
    }
}
