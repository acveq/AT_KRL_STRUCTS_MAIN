#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->setWindowTitle("TEST AT KRL STRUCTS");
    connect(ui->btnOpenDB, &QPushButton::clicked, this, &MainWindow::btnOpenDB_clicked);
    connect(ui->btnReadTable, &QPushButton::clicked, this, &MainWindow::btnReadTable_clicked);
    connect(ui->btnReadClasses, &QPushButton::clicked, this, &MainWindow::btnReadClasses_clicked);
    connect(ui->btnAddTrees, &QPushButton::clicked, this, &MainWindow::btnAddTrees_clicked);
    connect(ui->btnExportDirS, &QPushButton::clicked, this, &MainWindow::btnExportDirS_clicked);
    connect(ui->btnExportDirR, &QPushButton::clicked, this, &MainWindow::btnExportDirR_clicked);
    connect(ui->btnExportDirP, &QPushButton::clicked, this, &MainWindow::btnExportDirP_clicked);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::btnOpenDB_clicked(){
    fileName = QFileDialog::getOpenFileName(this,
                                            tr("Database"), "C://", tr("DB with timestamp (*.sqlite)"));
    qDebug()<<fileName;
    ui->teDBFile->setPlainText(fileName);
    fileName = ui->teDBFile->toPlainText();
    if (fileName == "") {
        addLog("Empty database name");
    } else {
        addLog("Open database " + fileName);

        ui->btnReadTable->setEnabled(true);
    }
}
void MainWindow::btnReadTable_clicked(){
    fileName = ui->teDBFile->toPlainText();
    maindb = QSqlDatabase::addDatabase("QSQLITE");
    maindb.setDatabaseName(fileName);
    if(!maindb.open()){
        addLog("Cant open DB");
    }
    else{
        addLog("DB successfully opened");
    }
    mainTableName = ui->teAttrName->toPlainText();
    mainTableModel = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(maindb);
    qry->prepare("Select * FROM "+mainTableName);
    qry->exec();
    mainTableModel->setQuery(*qry);
    ui->tableView->setModel(mainTableModel);
    addLog("Main table loaded");
    addLog("Added data to Table View");
}
void MainWindow::btnReadClasses_clicked(){
    addLog("Read classes table");
    classTableName = ui->teClassTable->toPlainText();
    classTableModel = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(maindb);
    qry->prepare("Select * FROM "+classTableName);
    qry->exec();
    classTableModel->setQuery(*qry);
    addLog("Classes table loaded");
}
void MainWindow::btnAddTrees_clicked(){
    addLog("Now need to create " +QString::number(ui->sbTreeCount->value()) + " trees ");
    addLog("Need to validate both tables");
    if(mainTableModel != nullptr && classTableModel != nullptr){
        if(mainTableModel->rowCount() > 0 && classTableModel->rowCount() >  0){
            maindb.close();
            addLog("BOTH TABLES are validated");
            dw_t = new database_wrapper_t;
            addLog(dw_t->init_database(fileName.toStdString()));
            addLog(dw_t->save_mapping(classTableName, ui->tePK->toPlainText(), ui->teColumnTick->toPlainText(), ui->teAllAttrs->toPlainText(), classTableName, ui->teClassColumn->toPlainText()));
        }
        else{
            addLog("ERROR: Main table is NOT validated");
            addLog("ERROR: Class table is NOT validated");
            addLog("Cant create " + QString::number(ui->sbTreeCount->value()) + " trees. Check logs");
        }
    }
    else{
        addLog("ERROR: cant load table");
    }
}
void MainWindow::btnExportDirS_clicked(){

}
void MainWindow::btnExportDirR_clicked(){

}
void MainWindow::btnExportDirP_clicked(){

}
void MainWindow::addLog(QString msg){
    ui->teLog->append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss ")+msg);
}
