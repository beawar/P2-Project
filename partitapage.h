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
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "tabs.h"

class PartitaPage : public QWizardPage
{
    Q_OBJECT
private:
    void createView();
    void createLayout();
    void creaPartita();

    SquadreModel* squadre;
    ArbitriModel* arbitri;
    Squadra* home, *guest;

    QVBoxLayout* layout;

    QGroupBox* squadra1Group;
    QGroupBox* squadra2Group;
    QGroupBox* arbitriGroup;

    QComboBox* squadra1ComboBox;
    QComboBox* squadra2ComboBox;
    QComboBox* arbitro1ComboBox;
    QComboBox* arbitro2ComboBox;

    QLabel* categoriaLabel;
    QComboBox* categoria;

    QListView* squadra1List;
    QListView* squadra2List;
public:
    explicit PartitaPage(SquadreModel* sm, ArbitriModel* am, QWidget *parent = 0);

    int nextId() const;
    bool validatePage() const;

    Squadra* getHomeTeam() const;
    Squadra* getGuestTeam() const;
    Arbitro* getArbitro1() const;
    Arbitro* getArbitro2() const;
    QString getCategoria() const;


signals:

public slots:

};

#endif // PARTITAPAGE_H
