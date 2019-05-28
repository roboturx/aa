#ifndef Tamamla_H
#define Tamamla_H
#include <QAbstractItemModel>
#include <QCompleter>
#include "globals.h"

class Tamamla
{
public:
    Tamamla(const QString& dosya);
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
    Hata(const QString& Baslik, const QString& Mesaj, const QString& Aciklama);

};


#endif // Tamamla_H
