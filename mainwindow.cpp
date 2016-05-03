#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QFont>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QTableView>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), tabs(0), fileOpen(tr("Senza Titolo")),  xml(&squadre, &arbitri)
{
    QWidget* widget = new QWidget;
    setCentralWidget(widget);

    QWidget* topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QLabel* appLabel = new QLabel("Handball Stats by Beatrice Guerra");
    appLabel->setAlignment(Qt::AlignCenter);
    QFont font = appLabel->font();
    font.setPointSize(20);
    font.setBold(true);
    appLabel->setFont(font);

    QWidget* bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(topFiller);
    layout->addWidget(appLabel);
    layout->addWidget(bottomFiller);
    widget->setLayout(layout);

    createActions();
    createMenus();

    setWindowTitle("HandBall Stats by Beatrice Guerra");
    setMinimumSize(sizeHint());

    resize(720, 560);

}

void MainWindow::newFile(){
    NewWizard* newWizard = new NewWizard(&squadre, &arbitri, this);
    newWizard->show();
    tabs = new Tabs(newWizard->getHomeTeam(), newWizard->getGuestTeam(),
                    newWizard->getArbitro1(), newWizard->getArbitro2(), this);
    connect(newWizard, SIGNAL(partitaCreata()), this, SLOT(showPartita()));
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
            creaClassifica();
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
            emit saveAs();
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
                file.close();
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


void MainWindow::edit(){

}

void MainWindow::about(){

}

void MainWindow::aboutQt(){

}

void MainWindow::showPartita(){
    tabs->newPartita();
    exportAct->setEnabled(true);
    setCentralWidget(tabs);
    //tabs->show();
}

void MainWindow::createActions(){
    newAct = new QAction(tr("&Nuovo"), this);
    newAct->setShortcut(QKeySequence::New);
    connect(newAct, SIGNAL(triggered()), this, SLOT(newFile()));

    openAct = new QAction(tr("&Apri"), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Salva"), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    saveAsAct = new QAction(tr("Salva &come"), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), this, SLOT(saveAs()));

    exportAct = new QAction(tr("Esporta"), this);
    exportAct->setShortcut(QKeySequence(tr("Ctrl+E")));
    exportAct->setEnabled(false);
    connect(exportAct, SIGNAL(triggered()), tabs, SLOT(exportPng()));

    editAct = new QAction(tr("E&dita"), this);
    connect(editAct, SIGNAL(triggered()), this, SLOT(edit()));

    exitAct = new QAction(tr("&Esci"), this);
    exitAct->setShortcut(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&?"), this);
    connect(openAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("&Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

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

    helpMenu = menuBar()->addMenu(tr("&Aiuto"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

void MainWindow::creaClassifica(){
    QTableView* tableView = new QTableView(this);
    tableView->setModel(&squadre);

}

