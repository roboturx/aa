#ifndef Tamamla_H
#define Tamamla_H
#include <QAbstractItemModel>
#include <QCompleter>
#include "globals.h"

class Tamamla
{
public:
    Tamamla(QString dosya);
    QAbstractItemModel *modelFromFile(const QString& fileName);
    QCompleter *completer;
};

namespace hata{class Hata;}

class Hata : public QDialog
{
public:
    explicit Hata(QDialog *parent = nullptr);
    Hata(QString Baslik);
    Hata(QString Baslik, QString Mesaj );
    Hata(QString Baslik, QString Mesaj, QString Aciklama);

};


#endif // Tamamla_H
