#ifndef HC_TEXTEDIT_H
#define HC_TEXTEDIT_H

#include "libs/globals.h"


class hC_TextEdit : public QMainWindow
{
    Q_OBJECT
public:
    hC_TextEdit(QWidget *parent = nullptr);

    bool load(const QString &f);

    QTextEdit *getTextEdit() const;
    void setTextEdit(QTextEdit *newTextEdit);

public slots:
    void fileNew();

//signals:
//    void textChanged(QTextEdit);

protected:
    void closeEvent(QCloseEvent *e) override;

private slots:
    void fileOpen();
    bool fileSave();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();

    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void underlineColor();
    void textAlign(QAction *a);
    void setChecked(bool checked);
    void indent();
    void unindent();

    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();
    void about();

private:
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);
    void modifyIndentation(int amount);

    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionSave;
    QAction *actionTextBold;
    QAction *actionTextUnderline;
    QAction *actionTextItalic;
    QAction *actionTextColor;
    QAction *actionUnderlineColor;
    QAction *actionAlignLeft;
    QAction *actionAlignCenter;
    QAction *actionAlignRight;
    QAction *actionAlignJustify;
    QAction *actionIndentLess;
    QAction *actionIndentMore;
    QAction *actionToggleCheckState;
    QAction *actionUndo;
    QAction *actionRedo;
#ifndef QT_NO_CLIPBOARD
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
#endif

    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QString fileName;
    QTextEdit *textEdit;
};


#endif // HC_TEXTEDIT_H
