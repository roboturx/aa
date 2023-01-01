#include <QString>
#include <QObject>
class MyClass : public QObject
{
public:
MyClass( const QString& text, QObject *parent = 0 );
const QString& text() const;
void setText( const QString& text );
int getLengthOfText() const;
private:
QString m_text;
 };
