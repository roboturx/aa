#ifndef hC_MKN_H
#define hC_MKN_H

#include "globals.h"
#include "mkn_cinsi.h"
#include "mkn_marka.h"
#include "mkn_modeli.h"

class SKGComboBox;
namespace nSMkn {
class hC_MKN;
}


class hC_MKN : public QWidget
{
    Q_OBJECT
public:
    explicit hC_MKN(QWidget *parent = nullptr);
    ~hC_MKN();
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
    hC_Tv                    * MKNtview    {} ;
    QSqlRelationalTableModel * MKNmodel    {} ;
    QItemSelectionModel      * MKNslctnMdl {} ;
    QDataWidgetMapper        * MKNmapper   {} ;

    QWidget * winWdgt  {} ;
    QLabel  * winLabel {} ;
    QLabel  * winRsm   {} ;

    /// mkn variables
    // QString *processMKN;
    QString *MKNid{};
    QLineEdit *led_barkod{};
    QLineEdit *led_malzeme{};
    QLineEdit *led_mknKurumno{};
    QLineEdit *led_mknPlaka{};

    hC_Le *lE_cins ;
    hC_Le *lE_mark ;
    hC_Le *lE_modl ;
    QSpinBox *spn_mknYil{};
    QComboBox *cbx_mknYkt;
    QComboBox *cbx_mknSurucu;
    QComboBox *cbx_mknBirim;
    QComboBox *cbx_mknByer;

    QLineEdit *led_mknSase{};
    QLineEdit *led_mknMotor{};
    QLineEdit *led_mknMtip{};
    QDateTimeEdit *clndr_mknSurucutar{} ;
    QTextEdit *ted_mknAcklm{};

    void    mkn_setup () ;
    QString mkn_VTd   () ;
    void    mkn_model () ;

private:
    void mkn_wdgt  () ;
    void mkn_map   () ;
    void mkn_ui    () ;
    void mkn_view  () ;
    void mkn_kntrl () ;

signals:
    void sgnMkn (QString);
};


#endif // hC_MKN_H
