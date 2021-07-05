#ifndef QRPLUSPLUS_H
#define QRPLUSPLUS_H

#include <QtWidgets>
#include "ui_qrplusplus.h"

class QRplusplus : public QMainWindow {
	Q_OBJECT

public:
    QRplusplus(QWidget *parent = nullptr);
	~QRplusplus();

private:
	// Default Qt ui class

    QComboBox *comboBox_color;
    QPushButton *exitButton;
    QLineEdit *userTextInput;
    QPushButton *generateButton;
    QPushButton *browseButton;
    QPushButton *clearButton;
    QLineEdit *lineEdit_fileDirectory;
    QSpinBox *spinBox_borderSize;

    QVBoxLayout *lay;

   // Ui::QRplusplusClass ui;

	// Member data
	QString dir;
	std::string fileDirectory;

	// Getter
	std::string getColor();
    int getBorderSize() { return spinBox_borderSize->value(); }

	// Member functions
	void openWeb();
	void openGithub();
	void openFile() { QDesktopServices::openUrl(QUrl::fromLocalFile(dir)); }
	void doneDialog();
	void aboutQt() { QApplication::aboutQt(); }
	void nayukiDialog();
	void aboutDialog();

	// UI Initialization Functions
	void initMenuBar();
	void initFileDirectory();
	void initPushButton();
	void initColorComboBox();
	void initStatusBar();

	// Qt Slots
	private slots:
		void enableButton();
		void selectDirectory();
		void generateQR();
		void exitApp();
        //void on_generateButton_clicked();
};

#endif // QRPLUSPLUS_H
