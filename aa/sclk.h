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

public:

    hC_Tv                    * SCLKtview    {} ;
    QSqlRelationalTableModel * SCLKmodel    {} ;
    QItemSelectionModel      * SCLKslctnMdl {} ;
    QDataWidgetMapper        * SCLKmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;

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

    void    sclk_setup () ;
    QString sclk_VTd   () ;
    void    sclk_model () ;


private:
    void sclk_wdgt()  ;
    void sclk_map()  ;
    void sclk_ui()   ;
    void sclk_view() ;
    void sclk_kntrl();


public:


};


#endif // SCLK_H
