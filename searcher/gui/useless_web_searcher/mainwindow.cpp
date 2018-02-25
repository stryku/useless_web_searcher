#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "common/index/index_interface.hpp"
#include "common/db/url_db_interface.hpp"

#include <QStringListModel>
#include <QDesktopServices>
#include <QUrl>

#include <chrono>
#include <map>
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


    auto start = std::chrono::system_clock::now();

    ui->label_status->setText("Fetching results...");

    const auto index_response = usl::common::index::index_interface{ "tcp://localhost:5552" }.get_results(words);

    auto model = ui->listView_results->model();
    model->removeRows(0, model->rowCount());

    QStringList list;

    using rank_to_id_t = std::multimap<double, usl::common::db::url_id_t, std::greater<double>>;
    rank_to_id_t rank_to_id;

    for(const auto& url_and_rank : index_response)
    {
        rank_to_id.insert(rank_to_id_t::value_type{ url_and_rank.second, url_and_rank.first });
    }

    usl::common::db::url_db_interface db_interface{ "tcp://localhost:5553" };

    for(const auto& rank_and_url : rank_to_id)
    {
        const auto url = db_interface.get(rank_and_url.second);
        list.append(QString::fromStdString(url));
    }

    auto end = std::chrono::system_clock::now();

    const auto diff = end - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();

    static_cast<QStringListModel*>(model)->setStringList(list);
    ui->label_status->setText(QString{"Ready. %1 results in: %2ms"}.arg(list.size()).arg(ms));
}

void MainWindow::on_listView_results_doubleClicked(const QModelIndex &index)
{
    const auto url = index.data(Qt::DisplayRole).toString();
    QDesktopServices::openUrl(QUrl(url));
}
