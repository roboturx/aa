#ifndef MW_DEPO_H
#define MW_DEPO_H

#include <QWidget>
#include <globals.h>

namespace Ui {
class MW_depo;
}

class MW_depo : public QWidget
{
    Q_OBJECT

public:
    explicit MW_depo(QWidget *parent = 0);
    ~MW_depo();

private:
    Ui::MW_depo *ui;
    void cr_Depo();
    void cr_DockWindows();
    void cr_StatusBar();
    void depo_Ekle() ;
    void depo_() ;

public:
    QLabel *myLabel;   //resim

    QDockWidget *mw_dock1, * mw_dock2;



};

#endif // MW_DEPO_H
