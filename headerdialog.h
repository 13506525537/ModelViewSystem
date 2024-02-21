#ifndef HEADERDIALOG_H
#define HEADERDIALOG_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class HeaderDialog;
}

class HeaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HeaderDialog(QWidget *parent = nullptr);
    ~HeaderDialog();

    void setStringList(const QStringList& strList);

    QStringList getHeaderList();

private:
    Ui::HeaderDialog *ui;

    QStringListModel* model;


};

#endif // HEADERDIALOG_H
