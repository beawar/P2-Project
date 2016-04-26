#include "squadrapage.h"

SquadraPage::SquadraPage(QWidget *parent) :
    QWizardPage(parent)
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

    registerField("squadra.nome*", nomeEdit);
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
}

int SquadraPage::nextId() const{
    return -1;
}
