#include "mainwindow.h"
#include <QFont>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QGridLayout>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), toolBar(0), newWizard(0),
  tabs(0), editor(0), fileOpen(""),  xml(&squadre, &arbitri)
{
    widget = new QWidget(this);
    QPixmap logo(":/images/images/HBStats_Icon_Sfondo.png");
    logo = logo.scaled(500, 500, Qt::KeepAspectRatio);
    QLabel* logoLabel = new QLabel(this);
    logoLabel->setPixmap(logo);

    QWidget* topFiller = new QWidget(this);
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget* bottomFiller = new QWidget(this);
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addWidget(logoLabel);
    layout->addWidget(bottomFiller);

    layout->setAlignment(logoLabel, Qt::AlignHCenter);

    widget->setLayout(layout);

    setCentralWidget(widget);

    createActions();
    createMenus();
    createToolBar();


    setWindowTitle("HandBall Stats by Beatrice Guerra");
    setMinimumSize(sizeHint());

    setMinimumSize(sizeHint());

}

void MainWindow::newFile(){
    if(newWizard){
        delete newWizard;
    }
    newWizard = new NewWizard(&squadre, &arbitri, this);
    newWizard->show();
    connect(newWizard, SIGNAL(partitaCreata()), this, SLOT(showPartita()));
    connect(newWizard, SIGNAL(squadraCreata()), this, SLOT(creaClassifica()));
}

void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Scegli un file da aprire"), QDir::currentPath(), "*.xml");
    if(!fileName.isNull()){
        if(!squadre.isEmpty()){
            squadre.clear();
        }
        if(!arbitri.isEmpty()){
            arbitri.clear();
        }
        try{
            xml.readFile(fileName);
            fileOpen = fileName;
            editAct->setEnabled(true);
        }
        catch(Err_Open e){
            QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nell'apertura del file"), QMessageBox::Ok);
            fileOpen = "";
        }
    }
}

void MainWindow::save(){
    if(!squadre.isEmpty() || !arbitri.isEmpty()){
        if(!fileOpen.isEmpty()){
            QFile file(fileOpen);
            if(file.open(QIODevice::WriteOnly)){
                try{
                    xml.writeFile(file);
                }
                catch(Err_Save e){
                    QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nel salvataggio del file"), QMessageBox::Ok);
                }
            }
            else{
                QMessageBox::warning(this, tr("Errore!"), tr("Impossibile salvare il file (modalità solo lettura)"), QMessageBox::Ok);
            }
            file.close();
        }
        else{
            saveAs();
        }
    }
}

void MainWindow::saveAs(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Salva come"), QDir::currentPath(), "*.xml");
    if(!fileName.isEmpty()){
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly)){
            try{
                xml.writeFile(file);
                fileOpen = fileName;
            }
            catch(Err_Save e){
                QMessageBox::critical(this, tr("Errore!"), tr("Si è verificato un errore nel salvataggio del file"), QMessageBox::Ok);
            }
        }
        else{
            QMessageBox::warning(this, tr("Errore!"), tr("Impossibile salavre il file (modalità solo lettura)"), QMessageBox::Ok);
        }
        file.close();
    }
}

void MainWindow::exportPng(){
    tabs->exportPng();
}


void MainWindow::edit(){
    if(editor){
        qDeleteAll(editor->children());
        delete editor;
    }
    editor = new Editor(&squadre, &arbitri, this);
    /* ----------------------------------------------------------------------------------------
    for(int i=0; i<squadre.size(); ++i){
        squadre.at(i)->sortByName();
    }
    -------------------------------------------------------------------------------------------*/
    connect(editor, SIGNAL(dataChanged()), this, SLOT(creaClassifica()));
    editor->show();
}

void MainWindow::about(){
    QMessageBox::about(this, "HandBall Stats", tr("HandBallStats è un applicativo per la gestione "
                                                  "di partite di pallamano, che permette di mantenere traccia "
                                                  "delle statistiche individuali e di squadra per ogni partita "
                                                  "giocata.\n ----------------------------------------------- \n"
                                                  "Versione 1.0 Copyright Beatrice Guerra"));
}

void MainWindow::aboutQt(){
    QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::showPartita(){
    Squadra* home = newWizard->getHomeTeam();
    Squadra* guest = newWizard->getGuestTeam();
    Arbitro* a1 = newWizard->getArbitro1();
    Arbitro* a2 = newWizard->getArbitro2();

    if(tabs){
        qDeleteAll(tabs->children());
        delete tabs;
    }
    tabs = new Tabs(home, guest, a1, a2, this);

    classificaAct->setEnabled(false);
    exportAct->setEnabled(true);
    resetPartitaAct->setEnabled(true);
    closePartitaAct->setEnabled(true);

    connect(exportAct, SIGNAL(triggered()), tabs, SLOT(exportPng()));
    connect(resetPartitaAct, SIGNAL(triggered()), tabs, SLOT(reset()));

    setCentralWidget(tabs);
    setMinimumSize(sizeHint());
}

void MainWindow::createActions(){
    newAct = new QAction(QIcon(":/images/images/new.png"), tr("&Nuovo"), this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(QIcon(":/images/images/open.png"), tr("&Apri"), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(QIcon(":/images/images/save.png"), tr("&Salva"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Salva &come"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exportAct = new QAction(QIcon(":/images/images/export.png"), tr("Esporta"), this);
    exportAct->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAct->setEnabled(false);

    editAct = new QAction(QIcon(":/images/images/edit.png"), tr("E&dita"), this);
    editAct->setEnabled(false);
    connect(editAct, SIGNAL(triggered()), this, SLOT(edit()));

    exitAct = new QAction(QIcon(":/images/images/quit.png"), tr("&Esci"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About HBStats"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("&Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    resetPartitaAct = new QAction(QIcon(":/images/images/reset.png"), tr("Reset Partita"), this);
    resetPartitaAct->setEnabled(false);

    closePartitaAct = new QAction(QIcon(":/images/images/termina.png"), tr("Termina Partita"), this);
    closePartitaAct->setEnabled(false);
    connect(closePartitaAct, SIGNAL(triggered()), this, SLOT(terminaPartita()));

    classificaAct = new QAction(QIcon(":/images/images/cup.png"), tr("Mostra classifica"), this);
    classificaAct->setEnabled(false);
    connect(classificaAct, SIGNAL(triggered()), this, SLOT(creaClassifica()));

}

void MainWindow::createMenus(){
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(exportAct);
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Modifica"));
    editMenu->addAction(editAct);
    editMenu->addSeparator();
    editMenu->addAction(resetPartitaAct);
    editMenu->addAction(closePartitaAct);
    editMenu->addSeparator();
    editMenu->addAction(classificaAct);

    helpMenu = menuBar()->addMenu(tr("&Aiuto"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::createToolBar(){
    toolBar = addToolBar(tr("Partita"));
    toolBar->addAction(exportAct);
    toolBar->addAction(editAct);
    toolBar->addAction(resetPartitaAct);
    toolBar->addAction(closePartitaAct);
}

void MainWindow::creaClassifica(){

    delete widget->layout();

    QFont font;
    font.setBold(true);
    font.setPointSize(16);

    QLabel* header[8];
    header[0] = new QLabel("N°", this);
    header[1] = new QLabel(tr("Nome"), this);
    header[2] = new QLabel(tr("Punti"), this);
    header[3] = new QLabel(tr("V"), this); //Vittorie
    header[4] = new QLabel(tr("P"), this); //Pareggi
    header[5] = new QLabel(tr("S"), this); //Sconfitte
    header[6] = new QLabel(tr("Pen"), this); //Penalità
    header[7] = new QLabel(tr("DR"), this); //Differenza Reti

    squadre.sort();

    QLabel* teamsLabel[squadre.size()][8];

    for(int i=0; i<squadre.size(); ++i){
        teamsLabel[i][0] = new QLabel(QString::number(i+1), this);
        teamsLabel[i][1] = new QLabel(squadre.at(i)->getNome());
        teamsLabel[i][2] = new QLabel(QString::number(squadre.at(i)->getPunti()), this);
        teamsLabel[i][3] = new QLabel(QString::number(squadre.at(i)->getVittorie()), this);
        teamsLabel[i][4] = new QLabel(QString::number(squadre.at(i)->getPareggi()), this);
        teamsLabel[i][5] = new QLabel(QString::number(squadre.at(i)->getSconfitte()), this);
        teamsLabel[i][6] = new QLabel(QString::number(squadre.at(i)->getPenalita()), this);
        teamsLabel[i][7] = new QLabel(QString::number(squadre.at(i)->getDifferenzaReti()), this);
    }

    QGridLayout* classifica = new QGridLayout;
    for(int i=0; i<8; ++i){
        header[i]->setFont(font);
        header[i]->setAlignment(Qt::AlignHCenter);
        classifica->addWidget(header[i], 1, i+1);
    }


    font.setBold(false);
    for(int i=0; i<squadre.size(); ++i){
        for(int j=0; j<8; ++j){
            teamsLabel[i][j]->setFont(font);
            teamsLabel[i][j]->setAlignment(Qt::AlignHCenter);
            classifica->addWidget(teamsLabel[i][j], i+2, j+1);
        }
    }

    QWidget* topFiller = new QWidget(this);
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QWidget* bottomFiller = new QWidget(this);
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QHBoxLayout* classificaLayout = new QHBoxLayout;
    classificaLayout->addStretch(20);
    classificaLayout->addLayout(classifica);
    classificaLayout->addStretch(20);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addLayout(classificaLayout);
    layout->addWidget(bottomFiller);

    classifica->setAlignment(layout, Qt::AlignHCenter);

    widget->setLayout(layout);
}

void MainWindow::terminaPartita(){
    classificaAct->setEnabled(true);
    tabs->termina();
}
