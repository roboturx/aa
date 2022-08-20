#ifndef ALT_KEY_HPP
#define ALT_KEY_HPP



#include <QCoreApplication> // For Q_DECLARE_TR_FUNCTIONS
#include <QList>
#include <QPair>
#include <QStringList>


class QAction;
class QWidget;


namespace AQP {

/*
    The original Alphabet QString constant wasn't translatable because
    it is translated before the application has a chance to load its
    translations. An ideal solution would be to make Alphabet a function
    that returns the string, but that would break the Alt_Key module's
    API. Konrad Rosenbaum spotted these problems and came up with this
    class as a solution. Thanks to the _Alphabet class the Alphabet can
    be translated and can also be used pretty well everywhere a string
    is required, thus preserving the Alt_Key module's API.
*/
class _Alphabet
{
    Q_DECLARE_TR_FUNCTIONS(_Alphabet);
public:
    _Alphabet() {}
    operator QString() const {
            return tr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                      "Accelerator Keys"); }
};

const _Alphabet Alphabet;

QStringList accelerated(const QStringList &strings,
                        const QString &alphabet=Alphabet);
void accelerateMenu(QWidget *menuOrMenuBar,
                    const QString &alphabet=Alphabet);
void accelerateActions(QList<QAction*> actions,
                       const QString &alphabet=Alphabet);
void accelerateWidget(QWidget *widget, const QString &alphabet=Alphabet);
void accelerateWidgets(QList<QWidget*> widgets,
                       const QString &alphabet=Alphabet);

bool isValid(const QStringList &listOfStrings,
             QPair<int, int> *where=0, const QString &alphabet=Alphabet);
int numberAccelerated(const QStringList &listOfStrings);
double quality(const QStringList &listOfStrings);

} // namespace AQP

#endif // ALT_KEY_HPP
