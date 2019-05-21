#ifndef AnaPencere_H
#define AnaPencere_H
#include <QMainWindow>

namespace Ui {
class AnaPencere;
}

class AnaPencere : public QMainWindow
{
    Q_OBJECT

public:
    explicit AnaPencere(QWidget *parent = 0);
    ~AnaPencere();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AnaPencere *ui;
};
#endif // AnaPencere_H
