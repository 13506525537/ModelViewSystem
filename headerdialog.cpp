#include "headerdialog.h"
#include "ui_headerdialog.h"

HeaderDialog::HeaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HeaderDialog)
{
    ui->setupUi(this);

    model = new QStringListModel(this);

    ui->listView->setModel(model);
}

HeaderDialog::~HeaderDialog()
{
    delete ui;
}

void HeaderDialog::setStringList(const QStringList &strList)
{
    model->removeRows(0, model->rowCount());
    model->setStringList(strList);
}

QStringList HeaderDialog::getHeaderList()
{
    return model->stringList();
}
