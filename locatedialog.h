#ifndef LOCATEDIALOG_H
#define LOCATEDIALOG_H

#include <QDialog>
#include <QModelIndex>

namespace Ui {
class LocateDialog;
}

class LocateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LocateDialog(QWidget *parent = nullptr);
    ~LocateDialog();

    void setRange(int rowMax, int columMax);

    void setRowColum(int rowNo, int cloumNo);

    void selectionChanged(const QModelIndex &current, const QModelIndex &previous);

    void closeEvent(QCloseEvent *) override;
    void showEvent(QShowEvent *) override;

signals:
    void actionEnabled(bool flag); // 确认action按钮是否生效
    void signalSetText(int row, int colum, QString text);

private slots:
    void on_btnSet_clicked();

private:
    Ui::LocateDialog *ui;
};

#endif // LOCATEDIALOG_H
