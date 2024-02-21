#include "rowcolumdialog.h"
#include "ui_rowcolumdialog.h"

RowColumDialog::RowColumDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RowColumDialog)
{
    ui->setupUi(this);
}

RowColumDialog::~RowColumDialog()
{
    delete ui;
}

void RowColumDialog::setRowColum(int row, int colum)
{
    ui->spinBoxRow->setValue(row);
    ui->spinBoxColum->setValue(colum);
}

int RowColumDialog::row()
{
    return ui->spinBoxRow->value();
}

int RowColumDialog::colum()
{
    return ui->spinBoxColum->value();
}
