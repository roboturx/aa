#include <QtWidgets>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "qrplusplus.h"
#include "QrCode.hpp"
#include <QtSvg/QSvgRenderer>
/*
* Default Constructor with initial setup.
*/
QRplusplus::QRplusplus(QWidget *parent) : QMainWindow(parent) {
    //ui.setupUi(this);
    QWidget *x;
    x = new QWidget;

    lay = new QVBoxLayout;
    x->setLayout (lay);
    this->setCentralWidget (x);
    //initMenuBar();
    initFileDirectory();
    initPushButton();
    initColorComboBox();
    initStatusBar();
}

/*
* Default Destructor
*/
QRplusplus::~QRplusplus(){
    // pass
}


/*
* Display 'Done' dialog with text to be encoded.
*/
void QRplusplus::doneDialog() {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    QString msg = "Done!\n\nText to be encoded: \n" +
            userTextInput->text ();
    msgBox.setText(msg);
    msgBox.exec();
}

/*
* Display 'About Nayuki's QR Code Generator Library' Dialog.
*/


/*
* Display true 'About' dialog.
*/

// ===================================
//			Qt Slots
// ===================================

/*
* When user open a program, by default, these buttons are disabled.
* enableButton() is a function to enable generateButton and clearButton
* if user enter any text in userTextInput textbox.
*/
void QRplusplus::enableButton() {
    generateButton->setEnabled(!(userTextInput->text().isEmpty()));
    clearButton->setEnabled(!(userTextInput->text().isEmpty()));
}

/*
* This function enables user to select a directory.
* By default, the dialog appear with current directory.
* Update file directory lineEdit and shows in the program.
*/
void QRplusplus::selectDirectory() {
    dir = QFileDialog::getExistingDirectory(this,
                                            tr("Select Directory"), QDir::currentPath());
    lineEdit_fileDirectory->setText(dir);
}

/*
* Function to receive a text from userTextInput textbox.
* qrcodegen library will tranforms a text into QR Code as SVG format.
* Then, save generated SVG XML as a file, doneDialog will be appeared.
*/
void QRplusplus::generateQR() {
    // Convert from QString to const char*
    qDebug()<<"generate";
    QString msgfromtextbox = userTextInput->text();
    std::string stringtext = msgfromtextbox.toStdString();
    //qDebug()<<stringtext;
    const char *text = stringtext.c_str();

    // Encode text into SVG XML format
    const qrcodegen::QrCode::Ecc &errCorLvl =
            qrcodegen::QrCode::Ecc::LOW;
    const qrcodegen::QrCode qr =
            qrcodegen::QrCode::encodeText(text, errCorLvl);

    // Save SVG XML into file
    std::ofstream myfile;

    myfile.open(dir.toStdString() + "/QRcode_output.svg");
    qDebug()<<&myfile;

    //  myfile << qr.toSvgString(QRplusplus::getBorderSize(),
    // QRplusplus::getColor()) << std::endl;

    myfile << qr.toSvgString (3,"3F51B5") << std::endl;




    this->setWindowIcon (QIcon("/QRcode_output.svg")
                         .pixmap(QSize(100,100)));

    // Display doneDialog
    //QRplusplus::doneDialog();

/*    QSvgRenderer renderer("");
    QPixmap pm(300, 300);
    pm.fill(Qt::white);
    QPainter painter(&pm);
    renderer.render(&painter, pm.rect());
*/
    myfile.close();
    qDebug()<<"Done";
}

/*
* A function to quit an application.
*/
void QRplusplus::exitApp() {
    QApplication::exit();
}

// ===================================
//			Getter Functions
// ===================================

/*
* Get current index from combobox_color and return its color in std::string format
* By default, it have 14 colors to choose. (Color palette from Android Material Design)
@return Hex color code without '#' symbol
*/
std::string QRplusplus::getColor()
{
    // Get current index from comboBox_color
    int index = comboBox_color->currentIndex();

    // Return the color from index
    switch (index)
    {
    case 0:
        return "000000"; 	// Black (Default)
            break;
    case 1:
        return "F44336";  	// Red
            break;
    case 2:
        return "E91E63";   // Pink
            break;
    case 3:
        return "9C27B0";   // Purple
            break;
    case 4:
        return "673AB7";   // Deep Purple
            break;
    case 5:
        return "3F51B5";   // Indigo
            break;
    case 6:
        return "2196F3";   // Blue
            break;
    case 7:
        return "00BCD4";   // Cyan
            break;
    case 8:
        return "009688";   // Teal
            break;
    case 9:
        return "4CAF50";   // Green
            break;
    case 10:
        return "FF9800";   // Orange
            break;
    case 11:
        return "FF5722";   // Deep Orange
            break;
    case 12:
        return "795548";   // Brown
            break;
    case 13:
        return "4B4B4B";   // Grey
            break;
    default:
        return "4B4B4B";

        break;
    }
}

// ===================================
//			UI Initialization
// ===================================

/*
* A function to initialize a menu bar.
*/
void QRplusplus::initMenuBar() {
    // Menu 'File'


    //    connect(ui.actionBrowse, &QAction::triggered, this, &QRplusplus::selectDirectory);
    //	connect(ui.actionOpen, &QAction::triggered, this, &QRplusplus::openFile);
    //	connect(ui.actionExit, &QAction::triggered, this, &QRplusplus::exitApp);

    // Menu 'About'
    /*	connect(ui.actionWebsite, &QAction::triggered, this, &QRplusplus::openWeb);
    connect(ui.actionGithub, &QAction::triggered, this, &QRplusplus::openGithub);
    connect(ui.actionAbout_Qt, &QAction::triggered, this, &QRplusplus::aboutQt);
    connect(ui.actionAbout_Nayuki, &QAction::triggered, this, &QRplusplus::nayukiDialog);
    connect(ui.actionAbout, &QAction::triggered, this, &QRplusplus::aboutDialog);
*/
}

/*
* A function to initialize file directory lineEdit.
@param dir	current path (system default)
*/
void QRplusplus::initFileDirectory() {

    lineEdit_fileDirectory = new QLineEdit(this);

    lay->addWidget (lineEdit_fileDirectory);
    // File directory
    qDebug()<<"1 init dir ";
    dir = QDir::currentPath();

    lineEdit_fileDirectory->setText(dir);

}

/*
* A function to initialize all pushButton.
*/
void QRplusplus::initPushButton() {
    // Push Button
    qDebug()<<"2 init push";

    exitButton = new QPushButton("Çıkış",this);
    lay->addWidget (exitButton);
    connect(exitButton, SIGNAL(clicked()), this, SLOT(exitApp()));

    generateButton= new QPushButton("oluştur",this);
    lay->addWidget (generateButton);
    connect(generateButton, SIGNAL(clicked()), this, SLOT(generateQR()));

    browseButton= new QPushButton("browse ",this);
    lay->addWidget (browseButton);
    connect(browseButton, SIGNAL(clicked()), this, SLOT(selectDirectory()));

    clearButton= new QPushButton("clear ",this);
    lay->addWidget (clearButton);

    userTextInput    = new QLineEdit (this);
    lay->addWidget (userTextInput);
    connect(userTextInput, &QLineEdit::textChanged, this,
            &QRplusplus::enableButton );


}

/*
* Colorize each color in comboBox_color combobox.
* First parameter represent the index of comboBox_color.
*/
void QRplusplus::initColorComboBox() {

    qDebug()<<"3 init color";
    spinBox_borderSize = new QSpinBox (this);
    lay->addWidget (spinBox_borderSize);

    comboBox_color = new QComboBox(this);
    lay->addWidget (comboBox_color);

    comboBox_color->setItemData(1, QBrush(QColor(244, 67, 54)), Qt::TextColorRole); // Red
    comboBox_color->setItemData(2, QBrush(QColor(233, 30, 99)), Qt::TextColorRole); // Pink
    comboBox_color->setItemData(3, QBrush(QColor(156, 39, 176)), Qt::TextColorRole); // Purple
    comboBox_color->setItemData(4, QBrush(QColor(103, 58, 183)), Qt::TextColorRole); // Deep Purple
    comboBox_color->setItemData(5, QBrush(QColor(63, 81, 181)), Qt::TextColorRole); // Indigo
    comboBox_color->setItemData(6, QBrush(QColor(33, 150, 243)), Qt::TextColorRole); // Blue
    comboBox_color->setItemData(7, QBrush(QColor(0, 188, 212)), Qt::TextColorRole); // Cyan
    comboBox_color->setItemData(8, QBrush(QColor(0, 150, 136)), Qt::TextColorRole); // Teal
    comboBox_color->setItemData(9, QBrush(QColor(76, 175, 80)), Qt::TextColorRole); // Green
    comboBox_color->setItemData(10, QBrush(QColor(255, 152, 0)), Qt::TextColorRole); // Orange
    comboBox_color->setItemData(11, QBrush(QColor(255, 87, 34)), Qt::TextColorRole); // Deep Orange
    comboBox_color->setItemData(12, QBrush(QColor(121, 85, 72)), Qt::TextColorRole); // Brown
    comboBox_color->setItemData(13, QBrush(QColor(75, 75, 75)), Qt::TextColorRole); // Grey
}

/*
* A function to initialize status bar.
* Tooltip is a help text which tell user the function of each section of the program.
*/
void QRplusplus::initStatusBar() {
    // Status Bar

    qDebug()<<"4 init stst";
    //   ui.statusBar->showMessage("Status: Ready");

    // Tooltip
    //	groupDirectory->setStatusTip("Select save file location.");
    //	groupInput->setStatusTip("Enter your text to be put into the QR Code.");
    //	groupCustomize->setStatusTip("Select QR Code Sizes and Colors.");
    generateButton->setStatusTip("Click to generate a QR Code.");
    exitButton->setStatusTip("Exit an application.");
}
