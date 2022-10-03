#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>

QSerialPort *serial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    serial->setPortName ("/dev/ttyUSB[01]");
    serial->setBaudRate (QSerialPort::Baud9600);
    serial->setDataBits (QSerialPort::Data8);
    serial->setParity (QSerialPort::NoParity);
    serial->setStopBits (QSerialPort::OneStop);
    serial->setFlowControl (QSerialPort::NoFlowControl);
    serial->open (QIODevice::ReadWrite);
    serial->write ("ok");

    connect (serial, &QSerialPort::readyRead,
            this, &MainWindow::serialReceived);
}



MainWindow::~MainWindow()
{
    delete ui;
    serial->close ();
}

void MainWindow::serialReceived()
{
    ui->label->setText (serial->readAll ());
}

