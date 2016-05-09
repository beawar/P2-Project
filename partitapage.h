#ifndef PARTITAPAGE_H
#define PARTITAPAGE_H

#include <QWizardPage>
#include <QListView>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>
#include <QRadioButton>
#include "checklist.h"
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "tabs.h"

class PartitaPage : public QWizardPage
{
    Q_OBJECT
private:
    enum {maxGiocatori = 14, maxAllenatori = 2};
    void createView();
    void createLayout();
    Squadra* homeTeam() const;
    Squadra* guestTeam() const;

    SquadreModel* squadre;
    ArbitriModel* arbitri;

    QVBoxLayout* layout;

    QGroupBox* squadra1Group;
    QGroupBox* squadra2Group;
    QGroupBox* arbitriGroup;
    QGroupBox* radioGroup;

    QRadioButton* nomeButton;
    QRadioButton* numeroButton;

    QComboBox* squadra1ComboBox;
    QComboBox* squadra2ComboBox;
    QComboBox* arbitro1ComboBox;
    QComboBox* arbitro2ComboBox;

    QLabel* categoriaLabel;
    QComboBox* categoria;

    QListView* squadra1List;
    QListView* squadra2List;

    CheckList* squadra1;
    CheckList* squadra2;

    int s1GiocChecked;
    int s1AllChecked;
    int s2GiocChecked;
    int s2AllChecked;

private slots:
    void updateList();
    void checkItem(CheckList* clist, QModelIndex index);
    void sort();

public:
    explicit PartitaPage(SquadreModel* sm, ArbitriModel* am, QWidget *parent = 0);

    int nextId() const;
    bool validatePage() const;

    QString getCategoria() const;


signals:

public slots:

};

#endif // PARTITAPAGE_H
