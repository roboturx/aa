#ifndef FRM_PR_H
#define FRM_PR_H

#include <QWidget>
#include <QSqlTableModel>
#include "dbase.h"

namespace Ui {
    class frm_pr;
}

class frm_pr : public QWidget
{
	Q_OBJECT

    public:
	explicit frm_pr(QWidget *parent = 0);
	~frm_pr();

    private slots:

	void on_pB_EK_clicked();
	void on_pB_SL_clicked();
	void on_pB_RP_clicked();
//	void on_pB_KY_clicked();
//	void on_tableView_pr_activated(const QModelIndex &index);

protected:
	 void showEvent(QShowEvent *);

    private:

	Ui::frm_pr *ui;

    DBase        *db;
	QSqlTableModel  *model;

	/* Also present are two methods that form
	 * the model and appearance TW_PR
	 * */
	void setupModel();
	void createUI();
	bool insertIntoTable(const QVariantList &data);

};

#endif // FRM_PR_H
