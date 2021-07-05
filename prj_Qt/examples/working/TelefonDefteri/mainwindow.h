#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>
#include <QRect>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btn_kaydet_clicked();
    void on_tbl_liste_doubleClicked(const QModelIndex &index);
    void on_btn_yeni_clicked();
    void on_btn_sil_clicked();
    void on_btn_sil_2_clicked();
    void on_txt_ara_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void resizeEvent(QResizeEvent* evt) Q_DECL_OVERRIDE;
    void listele(QString sql);
};

#endif // MAINWINDOW_H
