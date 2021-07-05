#ifndef WW_MAKINA_H
#define WW_MAKINA_H

//#include <QWidget>
//#include <QDataWidgetMapper>
//#include <QtSql>

#include "main/globals.h"

#include "ui_ww_makina.h"


namespace Ui {
    class WW_Makina;
}

class WW_Makina : public QWidget
{
	Q_OBJECT

    public:
	explicit WW_Makina(QWidget *parent = 0);
	~WW_Makina();

    private slots:
	void resim(QModelIndex   );
	void ww_mkcins();

	void on_pushButton_3_clicked();

	void on_pushButton_clicked();

    private:
	Ui::WW_Makina *ui;

	int mkcins_idx;	//
	int mkmark_idx;	//
	int mkmdl_idx;	//
	QDataWidgetMapper *mapper;

    private:
	void createmodel_mkstok();
	//void createmodel_mkcins();
	void createmodel_mkmark();
	void createmodel_mkmodl();
	void showError(const QSqlError &err);


	QSqlRelationalTableModel *model_mkstok;
	QSqlTableModel *model_mkcins;
	QSqlTableModel *model_mkmark;
	QSqlTableModel *model_mkmodl;

};

#endif // WW_MAKINA_H
