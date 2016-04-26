#ifndef SQUADRAPAGE_H
#define SQUADRAPAGE_H

#include <QWizardPage>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>

class SquadraPage : public QWizardPage
{
    Q_OBJECT
private:
    void createEditor();
    void createLayout();

    QVBoxLayout* layout;

    QLabel* nomeLabel;
    QLabel* societaLabel;
    QLineEdit* nomeEdit;
    QLineEdit* societaEdit;

private slots:


public:
    explicit SquadraPage(QWidget *parent = 0);

    int nextId() const;

signals:

public slots:

};

#endif // SQUADRAPAGE_H
