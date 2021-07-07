    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    counter(0)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QPushButton *button = new QPushButton(this);            // create a button
    button->setText("Button " + QString::number(counter));  // Set in it the text
    counter++;                                              // increment counter
    ui->verticalLayout->addWidget(button);                  // Put the button in the vertical layout

    // In lambda we grab the external pointer of variables from MainWindow,
    // Allow use variables ui, as well as the very key button
    connect(button, &QPushButton::clicked, [this, button](){
        ui->label->setText(button->text());
    });
}
