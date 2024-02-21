#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QRegExp>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 初始化
    void initUI();

    // 从字符串List转化为模型
    void strListToModel(const QStringList &strList);

private slots:
    void on_actionOpen_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_actionModelToView_triggered();

    void on_actionNew_triggered();

    void on_actionInsert_triggered();

    void on_actionDel_triggered();

    void on_actionLeft_triggered();

    void on_actionMid_triggered();

    void on_actionRight_triggered();

    void on_actionBlod_triggered(bool checked);

    void on_actionSave_triggered();

private:
    Ui::MainWindow *ui;

    // 创建下方状态栏label
    QLabel* currentPathLabel;
    QLabel* currentItemLabel;
    QLabel* currentContextLabel;

    // 创建模型类和选择模型类
    QStandardItemModel* model;
    QItemSelectionModel* selection;
};

#endif // MAINWINDOW_H
