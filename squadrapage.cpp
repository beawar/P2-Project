#include "squadrapage.h"

SquadraPage::SquadraPage(SquadreModel *sm, QWidget *parent) :
    QWizardPage(parent), squadre(sm)
{
    createEditor();
    createLayout();

    setLayout(layout);
    setWindowTitle(tr("Nuova squadra"));

}

void SquadraPage::createEditor(){
    nomeLabel = new QLabel(tr("Nome:"));
    nomeLabel->setAlignment(Qt::AlignCenter);
    nomeEdit = new QLineEdit;

    societaLabel = new QLabel(tr("Società:"));
    societaLabel->setAlignment(Qt::AlignCenter);
    societaEdit = new QLineEdit;

    insertButton = new QPushButton(tr("Inserisci"));
    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertTeam()));

    registerField("squadra.nome", nomeEdit);
    registerField("squadra.societa", societaEdit);
}

void SquadraPage::createLayout(){
    layout = new QVBoxLayout;


    QVBoxLayout* labelLayout = new QVBoxLayout;
    labelLayout->addWidget(nomeLabel);
    labelLayout->addWidget(societaLabel);

    QVBoxLayout* editLayout = new QVBoxLayout;
    editLayout->addWidget(nomeEdit);
    editLayout->addWidget(societaEdit);

    QHBoxLayout* editorLayout= new QHBoxLayout;
    editorLayout->addLayout(labelLayout);
    editorLayout->addLayout(editLayout);

    layout->addLayout(editorLayout, 1);
    layout->addWidget(insertButton, 0, Qt::AlignRight);
}

void SquadraPage::insertTeam(){
    squadre->addSquadra(new Squadra(nomeEdit->text(), societaEdit->text()));
    nomeEdit->clear();
    societaEdit->clear();
}

int SquadraPage::nextId() const{
    return -1;
}
