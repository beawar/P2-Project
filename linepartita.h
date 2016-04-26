#ifndef LINEPARTITA_H
#define LINEPARTITA_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include "giocatore.h"
#include "portiere.h"
#include "allenatore.h"
#include "arbitro.h"
#include "pushbutton.h"

class LinePartita : public QWidget
{
    Q_OBJECT
private:
    Tesserato* tesserato;

    void createButtons();
    void createLayout();

    QLabel* info;
    QLabel* goalLabel;
    PushButton* tiroButton;
    QPushButton* rigoreButton;
    PushButton* ammoButton;
    PushButton* dueMinButton;
    PushButton* esclButton;

    QHBoxLayout* layout;

private slots:
    void rightclickAmmo();
    void rightclickdueMin();
    void rightclickEscl();
    void rightclickTiro();
    void rightclickRigore();

    void leftclickAmmo();
    void leftclickdueMin();
    void leftclickEscl();
    void leftclickTiro();
    void leftclickRigore();

public:
    explicit LinePartita(Tesserato* t, QWidget *parent = 0);

signals:
    void valueChanged();

public slots:

};

#endif // LINEPARTITA_H
