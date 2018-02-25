#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common/index/index_interface.hpp"

#include <QStringListModel>

#include <queue>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listView_results->setModel(new QStringListModel(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_search_clicked()
{
    const auto query = ui->lineEdit_query->text().split(' ');
    std::vector<std::string> words;

    std::transform(query.begin(), query.end(),
                   std::back_inserter(words),
                   [](const QString& word) { return word.toStdString(); });


    const auto index_response = usl::common::index::index_interface{ "tcp://localhost:5552" }.get_results(words);

    auto model = ui->listView_results->model();
    model->removeRows(0, model->rowCount());

    QStringList list;

    for(const auto& url_and_rank : index_response)
    {
        list.append(QString::number(url_and_rank.first) + ':' + QString::number(url_and_rank.second));
    }

    static_cast<QStringListModel*>(model)->setStringList(list);
}
