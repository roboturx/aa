#ifndef CW_PER_MAP_H
#define CW_PER_MAP_H

#include "globals.h"

namespace Ui {
class CW_per_MAP;
}

class CW_per_MAP : public QDialog
{
    Q_OBJECT

public:
    explicit CW_per_MAP();
    ~CW_per_MAP();

signals:
    void Refresh();
private slots:
    void updateButtons(int row);
    void on_btnDelete_clicked();
    void on_btnUpdate_clicked();
    void on_btnAdd_clicked();
 //   void on_btnRefresh_clicked();

private:
    void setupModel();
    void setupView();



   // QItemSelectionModel *selectionModel;

public:
     void loadClsn(const int index);
    void setupMap();
    QSqlTableModel *modell;
    QDataWidgetMapper *map_per;

    QPushButton *nextButton ;
    QPushButton *previousButton;

    QPushButton *pb_ekle;
    QPushButton *pb_sil;
    QPushButton *pb_duzenle;
    int meslekIndex;
    QComboBox *cb_meslek;
    QLineEdit *le_isim;
    QLineEdit *le_soyad ;

    QLineEdit *le_bolum;
    QLineEdit *le_gorev ;
    QLineEdit *le_adres;
    QLineEdit *le_sehir ;
    QLineEdit *le_tel_cep;
    QLineEdit *le_tel_ev ;

    QLineEdit *le_eposta ;
    QLineEdit *le_username;
    QLineEdit *le_password ;
    QLineEdit *le_yetki;




};

#endif // CW_PER_MAP_H
