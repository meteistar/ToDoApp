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

void MainWindow::updateStatus()
{
    int completedCount = 0;
    for(auto t: mTasks){
        if(t->isCompleted()){
            completedCount++;
        }
    }
    int todoCount = mTasks.size() - completedCount;
    ui->statusLabel->setText(
                QString("Status : %1 todo / %2 completed")
                .arg(todoCount)
                .arg(completedCount));
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
        connect(task, &Task::removed,
                this, &MainWindow::removeTask);
        connect(task, &Task::statusChecked,
                this, &MainWindow::taskStatusChanged);
        mTasks.append(task);
        ui->tasksLayout->addWidget(task);
    }
    updateStatus();
}

void MainWindow::removeTask(Task *task)
{
    mTasks.removeOne(task);
    ui->tasksLayout->removeWidget(task);
    task->setParent(0);
    delete task;
    updateStatus();
}

void MainWindow::taskStatusChanged(Task *task)
{
    updateStatus();
}

