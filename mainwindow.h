#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDebug"
#include "QFileDialog"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQueryModel"
#include "QtSql/QSqlQuery"

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
private slots:
    void btnOpenDB_clicked();
    void btnReadTable_clicked();
    void btnReadClasses_clicked();
    void btnAddTrees_clicked();
    void btnExportDirS_clicked();
    void btnExportDirR_clicked();
    void btnExportDirP_clicked();
    void addLog(QString msg);
private:
    QString fileName = "";
    QSqlDatabase maindb;
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
