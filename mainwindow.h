#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QString>
#include <QToolBar>
#include <QLabel>
#include <QVBoxLayout>
#include "newwizard.h"
#include "squadremodel.h"
#include "arbitrimodel.h"
#include "xmlhandler.h"
#include "tabs.h"
#include "editor.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
    void createActions();
    void createMenus();

    QWidget* widget;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* helpMenu;

    Tabs* tabs;
    Editor* editor;

    QAction* newAct;
    QAction* openAct;
    QAction* saveAct;
    QAction* saveAsAct;
    QAction* exportAct;
    QAction* exitAct;
    QAction* editAct;
    QAction* aboutAct;
    QAction* aboutQtAct;

    SquadreModel squadre;
    ArbitriModel arbitri;

    QString fileOpen;
    XmlHandler xml;

    NewWizard* newWizard;

private slots:
    void newFile();
    void open();
    void save();
    void saveAs();
    void exportPng();
    void edit();
    void about();
    void aboutQt();
    void showPartita();
    void creaClassifica();

public:
  explicit MainWindow(QWidget *parent = 0);

signals:

public slots:

};

#endif // MAINWINDOW_H
