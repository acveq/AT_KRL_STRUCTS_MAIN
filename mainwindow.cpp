#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include "model_t.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    prepareInterface();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::prepareInterface(){
    this->setWindowTitle("TEST AT KRL STRUCTS");
    connect(ui->btnOpenDB, &QPushButton::clicked, this, &MainWindow::btnOpenDB_clicked);
    connect(ui->btnReadTable, &QPushButton::clicked, this, &MainWindow::btnReadTable_clicked);
    connect(ui->btnReadColums, &QPushButton::clicked, this, &MainWindow::btnReadColums_clicked);
    connect(ui->btnReadClasses, &QPushButton::clicked, this, &MainWindow::btnReadClasses_clicked);
    connect(ui->btnAddTrees, &QPushButton::clicked, this, &MainWindow::btnAddTrees_clicked);
    connect(ui->btnExportDirS, &QPushButton::clicked, this, &MainWindow::btnExportDirS_clicked);
    connect(ui->btnExportDirR, &QPushButton::clicked, this, &MainWindow::btnExportDirR_clicked);
    connect(ui->btnExportDirP, &QPushButton::clicked, this, &MainWindow::btnExportDirP_clicked);
}

void MainWindow::btnOpenDB_clicked(){
    fileName = QFileDialog::getOpenFileName(this, tr("Database"), "C://", tr("DB with timestamp (*.sqlite)"));
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
    if(!maindb.open())
        addLog("Cant open DB");
    else
        addLog("DB successfully opened");

    mainTableName = ui->teAttrName->toPlainText();
    mainTableModel = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(maindb);
    qry->prepare("Select * FROM "+mainTableName);
    qry->exec();
    mainTableModel->setQuery(*qry);
    if(mainTableModel->rowCount() > 0){
        addLog("Main table loaded");
        addLog("Added data to table viewer");
        ui->tableView->setModel(mainTableModel);
    }
    else{
        addLog("Error while loading main table");
    }
}
void MainWindow::btnReadColums_clicked(){
    idMainTableColumnName = ui->tePK->toPlainText();
    tickMainTableColumnName = ui->teColumnTick->toPlainText();
    propertyMainTableColumnNames = ui->teAllAttrs->toPlainText();
    addLog("Attributes added");
}
void MainWindow::btnReadClasses_clicked(){
    addLog("Read classes table");
    classTable = ui->teClassTable->toPlainText();
    nameClassTableColumn = ui->teClassColumn->toPlainText();

    classTableModel = new QSqlQueryModel();
    QSqlQuery *qry = new QSqlQuery(maindb);
    qry->prepare("Select * FROM "+classTable);
    qry->exec();
    classTableModel->setQuery(*qry);
    if(classTableModel->rowCount() >  0){
        addLog("Classes table loaded");
    }
    else{
        addLog("Error while loading class table");
    }
}

void MainWindow::btnAddTrees_clicked(){
    addLog("Need to create " +QString::number(ui->sbTreeCount->value()) + " trees ");
    addLog("Need to validate both tables");
    int treesSize = ui->sbTreeCount->value();

    if(mainTableModel != nullptr && classTableModel != nullptr){
        if(mainTableModel->rowCount() > 0 && classTableModel->rowCount() >  0){
            maindb.close();
            addLog("BOTH TABLES are validated");
            if(model != nullptr)
                delete model;

            // everything is ready to work with model
            model = new model_t;

            QStringList names;
            names.append(mainTableName);
            names.append(idMainTableColumnName);
            names.append(tickMainTableColumnName);
            names.append(propertyMainTableColumnNames);
            names.append(classTable);
            names.append(nameClassTableColumn);
            model->init(fileName.toStdString(), names);

            int i = 0;
            while(i < treesSize){
                qDebug()<<"add tree";
                model->add_tree();
                i++;
            }
            //modelInitFuture = QtConcurrent::run(static_cast<model_t*>(model), &model_t::init, fileName.toStdString(), names);
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
    std::ofstream sout(ui->teExportDirS->toPlainText().toStdString());
    sout << model->serialize();
    sout.close();
}
void MainWindow::btnExportDirR_clicked(){
    std::ofstream textout(ui->teExportDirR->toPlainText().toStdString());
    std::ofstream innerout(ui->ExportDirP->toPlainText().toStdString());
    std::ofstream xmlout("C://results/xmlout.xml");
    model->rulealize(textout, innerout, xmlout);
}
void MainWindow::btnExportDirP_clicked(){

}
void MainWindow::addLog(QString msg){
    ui->teLog->append(QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss ")+msg);
}
