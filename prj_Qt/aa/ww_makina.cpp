#include "ww_makina.h"
#include "ui_ww_makina.h"
//#include "database.h"

#include <QtSql>
#include "dlgt_mkstok.h"
#include "ww_mkcins.h"
#include <QtGui>
#include <QMessageBox>
#include <QDataWidgetMapper>
#include <QFileDialog>


WW_Makina::WW_Makina(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WW_Makina)
{
    ui->setupUi(this);

    // Create the data model for DBTB_MKMARK
    createmodel_mkmark();

    // Create the data model for DBTB_MKMD
    createmodel_mkmodl();

    // Create the data model for DBTB_MKSTOK
    createmodel_mkstok();


}


void WW_Makina::createmodel_mkmark()
{
    // Create the data model for DBTB_MKMARK
    model_mkmark = new QSqlTableModel(ui->Table_DBTB_MKMARK);
    model_mkmark->setEditStrategy(QSqlTableModel::OnRowChange);
    model_mkmark->setTable("DBTB_MKMARK");

    // Set the localized header captions
    model_mkmark->setHeaderData(model_mkmark->fieldIndex("marka"),
				Qt::Horizontal, tr("MARKA"));

    // Populate the model
    if (!model_mkmark->select())
	{
	    showError(model_mkmark->lastError());
	    return;
	}
    // Set the model and hide the ID column
    ui->Table_DBTB_MKMARK->setModel(model_mkmark);
    ui->Table_DBTB_MKMARK->setColumnHidden(model_mkmark->fieldIndex("id_mkmark"), true);
    ui->Table_DBTB_MKMARK->setSelectionMode(QAbstractItemView::SingleSelection);
}

void WW_Makina::createmodel_mkmodl()
{
    // Create the data model for DBTB_MKMODL
    model_mkmodl = new QSqlTableModel(ui->Table_DBTB_MKMODL);
    model_mkmodl->setEditStrategy(QSqlTableModel::OnRowChange);
    model_mkmodl->setTable("DBTB_MKMODL");

    // Set the localized header captions
    model_mkmodl->setHeaderData(model_mkmodl->fieldIndex("model"),
				Qt::Horizontal, tr("MODEL"));

    // Populate the model
    if (!model_mkmodl->select())
	{
	    showError(model_mkmodl->lastError());
	    return;
	}

    // Set the model and hide the ID column
    ui->Table_DBTB_MKMODL->setModel(model_mkmodl);
    ui->Table_DBTB_MKMODL->setColumnHidden(model_mkmodl->fieldIndex("id_mkmodl"), true);
    ui->Table_DBTB_MKMODL->setSelectionMode(QAbstractItemView::SingleSelection);

}



////////////////////////////////////////////////////////////////////////////////////////////////////////

void WW_Makina::createmodel_mkstok()
{
    // Create the data model for DBTB_MKSTOK
    model_mkstok = new QSqlRelationalTableModel(ui->Table_DBTB_MKSTOK);
    model_mkstok->setEditStrategy(QSqlTableModel::OnFieldChange); // :OnRowChange);
    model_mkstok->setTable("dbtb_mkstok");
    model_mkstok->setJoinMode(QSqlRelationalTableModel::LeftJoin);

    // Remember the indexes of the columns
    // combobox fields
    mkcins_idx = model_mkstok->fieldIndex("cinsi");	//dbtb_mkcins
    mkmark_idx = model_mkstok->fieldIndex("marka");	//dbtb_mkmark
    mkmdl_idx = model_mkstok->fieldIndex("modeli");	//dbtb_mkmodl

    // Set the relations to the other database tables
    model_mkstok->setRelation(mkcins_idx,
			      QSqlRelation("DBTB_MKCINS", "id_mkcins", "cinsi"));

    model_mkstok->setRelation(mkmark_idx,
			      QSqlRelation("DBTB_MKMARK", "id_mkmark", "marka"));

    model_mkstok->setRelation(mkmdl_idx,
			      QSqlRelation("DBTB_MKMODL", "id_mkmodl", "modeli"));

    // Set the localized header captions
    model_mkstok->setHeaderData(1, Qt::Horizontal, tr("İ-Ö-İ No"));
    model_mkstok->setHeaderData(2, Qt::Horizontal, tr("PLAKA"));
    model_mkstok->setHeaderData(mkcins_idx, Qt::Horizontal, tr("CİNSİ"));
    model_mkstok->setHeaderData(4, Qt::Horizontal, tr("MARKA"));
    model_mkstok->setHeaderData(mkmdl_idx, Qt::Horizontal, tr("MODELİ"));
    model_mkstok->setHeaderData(6, Qt::Horizontal, tr("YILI"));
    model_mkstok->setHeaderData(7, Qt::Horizontal, tr("ŞASE NO"));
    model_mkstok->setHeaderData(8, Qt::Horizontal, tr("MOTOR NO"));
    model_mkstok->setHeaderData(9, Qt::Horizontal, tr("BULUNDUĞU YER"));
    model_mkstok->setHeaderData(10, Qt::Horizontal, tr("RESİM"));
    model_mkstok->setHeaderData(11, Qt::Horizontal, tr("DURUM"));

    // Populate the model_mkstok
    if (!model_mkstok->select())
	{
	    showError(model_mkstok->lastError());
	    return;
	}

    // Set the model_mkstok and hide the ID column
    ui->Table_DBTB_MKSTOK->setModel(model_mkstok);
    ui->Table_DBTB_MKSTOK->setItemDelegate(new MakinaDelegate(ui->Table_DBTB_MKSTOK));
    ui->Table_DBTB_MKSTOK->setColumnHidden(model_mkstok->fieldIndex("id_mkstok"), true);
    ui->Table_DBTB_MKSTOK->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Table_DBTB_MKSTOK->setSelectionBehavior(QAbstractItemView::SelectItems);

    // Initialize the CİNSİ combo box in table view
    ui->ledit_cins->setModel(model_mkstok->relationModel(mkcins_idx));
    ui->ledit_cins->setModelColumn(model_mkstok->
				   relationModel(mkcins_idx)->fieldIndex("cinsi"));

    // Initialize the CİNSİ combo box in table view
    ui->ledit_marka->setModel(model_mkstok->relationModel(mkmark_idx));
    ui->ledit_marka->setModelColumn(model_mkstok->
				    relationModel(mkmark_idx)->fieldIndex("marka"));

    // Initialize the MODEL combo box in table view
    ui->ledit_model->setModel(model_mkstok->relationModel(mkmdl_idx));
    ui->ledit_model->setModelColumn(model_mkstok->
				    relationModel(mkmdl_idx)->fieldIndex("modeli"));


    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model_mkstok);
    mapper->setItemDelegate(new MakinaDelegate(this));
    mapper->addMapping(ui->ledit_ioi, model_mkstok->fieldIndex("ioi_no"));
    mapper->addMapping(ui->ledit_plaka, model_mkstok->fieldIndex("plaka"));
    mapper->addMapping(ui->ledit_cins, mkcins_idx);
    mapper->addMapping(ui->ledit_marka, mkmark_idx);
    mapper->addMapping(ui->ledit_model, mkmdl_idx);
    mapper->addMapping(ui->ledit_yil, model_mkstok->fieldIndex("yil"));
    mapper->addMapping(ui->ledit_sase, model_mkstok->fieldIndex("saseno"));
    mapper->addMapping(ui->ledit_motor, model_mkstok->fieldIndex("motorno"));
    mapper->addMapping(ui->ledit_byer, model_mkstok->fieldIndex("byer"));
    mapper->addMapping(ui->lbl_foto, model_mkstok->fieldIndex("resim"));
    mapper->addMapping(ui->ledit_rating, model_mkstok->fieldIndex("rating"));


    connect(ui->Table_DBTB_MKSTOK->selectionModel(),
	    SIGNAL(currentColumnChanged(QModelIndex,QModelIndex)),
	    mapper, SLOT(setCurrentModelIndex(QModelIndex)));
    connect(ui->Table_DBTB_MKSTOK->selectionModel(),
	    SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
	    mapper, SLOT(setCurrentModelIndex(QModelIndex)));

    // resim göster
    connect(ui->Table_DBTB_MKSTOK->selectionModel(),
	    SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
	    this, SLOT(resim(QModelIndex )));
    // cins editor
    connect(ui->tbtn_cins, SIGNAL( clicked() ),  this,
	    SLOT( ww_mkcins() ));


    ui->Table_DBTB_MKSTOK->setCurrentIndex(model_mkstok->index(0, 0));
}

void WW_Makina::ww_mkcins()
{
    WW_Mkcins *w = new WW_Mkcins;
    w->setModal(true);
    w->show();
    model_mkstok->select();

}

void WW_Makina::resim(QModelIndex   )
{
    // makina stok tablosundan resim gösterme

    // view row unu tespit et
    int rowidx = ui->Table_DBTB_MKSTOK->
            selectionModel()->currentIndex().row();

    // row, xolumn daki veriyi bytearray a at
    QByteArray outByteArray = ui->Table_DBTB_MKSTOK->
        model()->index(rowidx,11).data().toByteArray();

    QPixmap outPixmap = QPixmap();
    outPixmap.loadFromData( outByteArray  );
    ui->lbl_foto->setPixmap( outPixmap );
    ui->lbl_foto->setScaledContents( true );
    ui->lbl_foto->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
    ui->lbl_foto->show();
}




void WW_Makina::showError(const QSqlError &err)
{
    QMessageBox::critical(this, "Unable to initialize Database",
			  "Error initializing database:\n \n ***  " + err.text()+"  ***");
}


WW_Makina::~WW_Makina()
{
    delete ui;
}

void WW_Makina::on_pushButton_3_clicked()
{
    // makina stok resim ekle
    QString myfile = QFileDialog::getOpenFileName(this,
         tr("Resim Aç"), "/home/mr/a/aa/rsm",
         tr("Resim Dosyaları (*.png *.jpg *.bmp *.jpeg)"
         " ;; Tüm Dosyalar (*,*)"));
    if (myfile == "")
        return;

    QImage image(myfile);
    ui->lbl_foto->setPixmap(QPixmap::fromImage(image));
    QByteArray inByteArray;
    QFile file(  myfile ); //dosyayı açmak için al

    if ( file.open(QIODevice::ReadOnly))
    {
        //qDebug ()<<"file read";
        inByteArray = file.readAll();

        // table view de hangi rowdayız ?
        QModelIndex index = ui->Table_DBTB_MKSTOK->currentIndex();
        int row = index.row() ;
        // o row daki bilgelere ulaşalım
        model_mkstok->setData(model_mkstok->
                    index(row, 11),inByteArray);
        model_mkstok->submitAll();

    }

}

void WW_Makina::on_pushButton_clicked()
{
    // makina stok ekle
    int row = mapper->currentIndex();
    mapper->submit();

    model_mkstok->beginInsertRows();
    model_mkstok->insertRow(row);
    model_mkstok->endInsertRows();

    mapper->setCurrentIndex(row);
    model_mkstok->submitAll();
    }


