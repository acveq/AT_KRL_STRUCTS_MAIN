#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QFileDialog"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQueryModel"
#include "QtSql/QSqlQuery"
#include <QtConcurrent/QtConcurrent>

class model_t;

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void prepareInterface();
private slots:
    void btnOpenDB_clicked();
    void btnReadTable_clicked();
    void btnReadColums_clicked();
    void btnReadClasses_clicked();
    void btnAddTrees_clicked();
    void btnExportDirS_clicked();
    void btnExportDirR_clicked();
    void btnExportDirP_clicked();
    void addLog(QString msg);
private:
    Ui::MainWindow *ui;
    QString fileName = "";

    QString mainTableName = "";
    QString idMainTableColumnName = "";
    QString tickMainTableColumnName = "";
    QString propertyMainTableColumnNames = "";
    QString classTable = "";
    QString nameClassTableColumn = "";

    model_t * model = nullptr;
    QSqlQueryModel* mainTableModel = nullptr;
    QSqlQueryModel * classTableModel = nullptr;
    QSqlDatabase maindb;


    QFuture<void> modelInitFuture;
    QFuture<void> modelSetnamesFuture;
};
#endif // MAINWINDOW_H
