#include "cw_gelir.h"
#include "globals.h"

CW_gelir::CW_gelir(QWidget *parent) : QWidget(parent)
{
    qDebug ()  <<"cw gelir 001 ";
        this->setupModel();
        this->createUI();

}

CW_gelir::~CW_gelir()
= default;




/* Method for initializing data representation pmodel * */
void CW_gelir::setupModel()
{

    QString tableName = "dbtb_gelir";
    QStringList fieldList;
   // fieldList.append("Kod");
    fieldList.append("Tarih");
    fieldList.append("Gelir Tipi");
    fieldList.append("Açıklama");
    fieldList.append("Miktar");

    model = new QSqlTableModel();
    model->setTable(tableName);

    /// Set the columns names in a table with sorted data
    ///
    ///
    for(int i = 0, j = 0; i < model->columnCount()-2; i++, j++){
        model->setHeaderData(i,Qt::Horizontal,fieldList[j]);
    }

    // Set Sort Ascending steering column data
    model->setSort(2,Qt::AscendingOrder);

    // her field değişiminde dosya yazılacak
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


}

/* user interface */
void CW_gelir::createUI()
{
    tV_gelir->setModel(model);

    // Hide the column id Records
    tV_gelir->setColumnHidden(0, true);
    // Allow the selection of lines
    tV_gelir->setSelectionBehavior
            (QAbstractItemView::SelectItems);
    // Set selection mode, only one row in table
    tV_gelir->setSelectionMode
            (QAbstractItemView::SingleSelection);
    // Set the size of the columns by content
    tV_gelir->resizeRowsToContents ();
    tV_gelir->resizeColumnsToContents();
    tV_gelir->setStyleSheet ("background-color: darkgreen;"
                               "color : yellow;");

    tV_gelir->setEditTriggers
            (QAbstractItemView::DoubleClicked |
             QAbstractItemView::SelectedClicked |
             QAbstractItemView::EditKeyPressed);

   tV_gelir->horizontalHeader()->
            setStretchLastSection(true);
    tV_gelir->horizontalHeader()->
            resizeContentsPrecision();

    tV_gelir->setColumnWidth(0, this->width()/7);
    tV_gelir->setColumnWidth(1, this->width()/7);
    tV_gelir->setColumnWidth(2, this->width()/7);
    tV_gelir->setColumnWidth(3, this->width()/7);
    tV_gelir->setColumnWidth(4, this->width()/7);
    tV_gelir->setColumnWidth(5, this->width()/7);
    tV_gelir->setColumnWidth(6, this->width()/7);
    tV_gelir->setColumnWidth(7, this->width()/20);
    tV_gelir->setColumnWidth(8, this->width()/20);
    tV_gelir->setColumnWidth(9, this->width()/20);
    tV_gelir->setColumnWidth(10, this->width()/20);
    tV_gelir->setColumnWidth(11, this->width()/20);
    tV_gelir->setColumnWidth(12, this->width()/20);

    ///////////////////////////////////////////////////////

    map_gelir = new QDataWidgetMapper(this);
    map_gelir->setModel(model);

    //map_gelir->setItemDelegate(new MakinaDelegate(this));
//    map_gelir->addMapping(lE_isim, model->fieldIndex("isim"));

  //  map_gelir->addMapping(lE_soyad, model->fieldIndex("soyad"));
    // map_gelir->addMapping(ui-dit_cins, mkcins_idx);
    // map_gelir->addMapping(ui->ledit_marka, mkmark_idx);
    // map_gelir->addMapping(ui->ledit_pmodel, mkmdl_idx);
   // map_gelir->addMapping(ui->lE_bolum, model->fieldIndex("bolum"));
  //  map_gelir->addMapping(ui->lE_meslek, model->fieldIndex("meslek"));
   // map_gelir->addMapping(ui->lE_gorev, model->fieldIndex("gorev"));
   // map_gelir->addMapping(ui->lE_adres, model->fieldIndex("adres"));
   // map_gelir->addMapping(ui->lE_sehir, model->fieldIndex("sehir"));
   // map_gelir->addMapping(ui->lE_telcep, model->fieldIndex("tel_cep"));
  //  map_gelir->addMapping(ui->lE_telev, model->fieldIndex("tel_ev"));

    connect(tV_gelir->selectionModel(),
            SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
            map_gelir, SLOT(setCurrentModelIndex(QModelIndex)));
    connect(tV_gelir->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            map_gelir, SLOT(setCurrentModelIndex(QModelIndex)));

    // resim göster
    connect(tV_gelir->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this, SLOT(resim(QModelIndex )));
    // cins editor
    // connect(ui->tbtn_cins, SIGNAL( clicked() ),  this,
    // SLOT( ww_mkcins() ));

    tV_gelir->setCurrentIndex(model->index(0, 0));

    ///////////////////////////////////////////////////////



    model->select(); // Fetches the data from the table

}

// personel silme
void CW_gelir::on_pB_SL_clicked()
{
    QModelIndex sample = tV_gelir->currentIndex();
    if( sample.row() >= 0 )
    {

        qDebug()<<"xxxxxxx"    <<
                  "sample isvalid - "<<  sample.isValid();
        qDebug()<<"sample - row "<<  sample.row() ;
        qDebug()<<"sample pmodel row count- "<<
                  sample.model()->rowCount();
        qDebug()<<"pmodel column count- "<<
                  sample.model()->columnCount();

        //       tV_gelir->selectionModel()->setCurrentIndex
        //             (sample,QItemSelectionModel::NoUpdate);

        QSqlRecord rec = model->record();


        qDebug()<<"rec val 0- "<< rec.value(0).toString();
        qDebug()<<"fieldname - "<< rec.fieldName(1);
        qDebug()<<"f val tostr  - "<< rec.field(2).value().toString();
        QString val = rec.value(1).toString();// +" "+
        QMessageBox::StandardButton dlg;
        qDebug()<<"silinecek rec val 1 - "<< val;

        dlg = QMessageBox::question(this,
                                    "KAYIT SİL",  val ,// + "\n isimli personelin kaydı silinsin mi? ?" ,
                                    QMessageBox::Yes | QMessageBox::No);


        if(dlg == QMessageBox::Yes)
        {
            // remove the current index
            // pmodel->beginRemoveColumn();
            model->removeRow(sample.row());
            //pmodel->endRemoveColumns();
            model->select();
        }
    }



}




void CW_gelir::on_pB_EK_clicked()
{
    // ui->groupBox_2->show();
    //    ui->groupBox->hide();

    QSqlRecord rec = model->record();

    // insert a new record (-1)
    if ( ! model->insertRecord(-1,rec))
    {
        qDebug() << "100111 -  HATA - kayıt eklenemedi "
                    ;
    }
    else
        qDebug() << "100111 - Kayıt personele eklendi ";
    model->select();

}



void CW_gelir::on_chbx_detay_stateChanged()
{
   /* if (groupBox_2->isHidden() )
    {
        ui->groupBox_2-> show();
    }
    else
    {
        ui->groupBox_2->hide();
    }
*/
}
