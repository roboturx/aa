#ifndef SCLK_H
#define SCLK_H

#include "globals.h"
//#include "hc_.h"

namespace nSSclk {
class hC_SCLK;
}

class hC_SCLK : public QWidget
{
    Q_OBJECT

public:
    explicit hC_SCLK(QWidget *parent = nullptr);
    ~hC_SCLK();

    ////////////////////////////////////////////////
    hC_Tv                    * tb_view    {} ;
    QItemSelectionModel      * tb_slctnMdl {} ;
    QSqlRelationalTableModel * tb_model    {} ;
    QDataWidgetMapper        * tb_mapper   {} ;


    QString                  * tb_name     {} ;
    hC_ArrD                  * tb_flds   {} ;
    QString                  * tb_ndex     {} ;
    QList <QWidget*>         * tb_wdgts    {} ;

    QWidget                  * win_Wdgt  {} ;
    QLabel                   * win_Label {} ;
    QLabel                   * win_Rsm   {} ;
/////////////////////////////////////////////////

    // SC variable

    QLineEdit *lE_SCno{};
    QDateTimeEdit *dE_SCtarih{};
    QComboBox *cbx_SCbirim{};
    QComboBox *cbx_SCusta{};
    QLineEdit *lE_SCsaat{};
    QLineEdit *lE_SCucret{};
    QComboBox *cbx_SCucrettip{};
    QLineEdit *lE_SCaciklama{};
    QString *SCdet_idno{};
    QString *SCdetno{};
    QString *SCno{};

    void    setup () ;

private:
    void wdgt()  ;
    void ui()   ;
    void kntrl();

};

#endif // SCLK_H
