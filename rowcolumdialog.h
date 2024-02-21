#ifndef ROWCOLUMDIALOG_H
#define ROWCOLUMDIALOG_H

#include <QDialog>

namespace Ui {
class RowColumDialog;
}

class RowColumDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RowColumDialog(QWidget *parent = nullptr);
    ~RowColumDialog();

    // 显示时设置输入框
    void setRowColum(int row, int colum);

    int row();

    int colum();
private:
    Ui::RowColumDialog *ui;
};

#endif // ROWCOLUMDIALOG_H
