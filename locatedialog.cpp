#include "locatedialog.h"
#include "ui_locatedialog.h"

LocateDialog::LocateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocateDialog)
{
    ui->setupUi(this);
    // 初始化设置阻塞模式
    this->setModal(false);
    this->setWindowFlag(Qt::WindowStaysOnTopHint);
}

LocateDialog::~LocateDialog()
{
    delete ui;
}

void LocateDialog::setRange(int rowMax, int columMax)
{
    ui->spinBoxRow->setRange(0, rowMax-1);
    ui->spinBoxColum->setRange(0, columMax-1);
}

void LocateDialog::setRowColum(int rowNo, int cloumNo)
{
    ui->spinBoxRow->setValue(rowNo);
    ui->spinBoxColum->setValue(cloumNo);
}

void LocateDialog::selectionChanged(const QModelIndex &current, const QModelIndex &previous)
{
    #define UNUSE(previous);
    ui->spinBoxRow->setValue(current.row());
    ui->spinBoxColum->setValue(current.column());

}

void LocateDialog::closeEvent(QCloseEvent *)
{
    emit actionEnabled(true);
}

void LocateDialog::showEvent(QShowEvent *)
{
    emit actionEnabled(false);
}

void LocateDialog::on_btnSet_clicked()
{
    emit signalSetText(ui->spinBoxRow->value(), ui->spinBoxColum->value(), ui->lineEdit->text());
}

