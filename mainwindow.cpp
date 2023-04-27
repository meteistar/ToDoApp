#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
{
    ui->setupUi(this);
    connect(ui->addtaskButton, &QPushButton::clicked,
            this, &MainWindow::addTask);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask()
{
    bool ok;
    QString name = QInputDialog::getText(this,
                                tr("Add Task"),
                                tr("Task Name"),
                                QLineEdit::Normal,
                                tr("Untitled Task"), &ok);
    if(ok && !name.isEmpty()){
        qDebug()<< "Adding new task";
        Task* task = new Task(name);
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
    }
}

