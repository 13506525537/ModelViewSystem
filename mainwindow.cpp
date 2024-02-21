#include "mainwindow.h"
#include "ui_mainwindow.h"

// QStandItemModel 是标准的以项数据为基础的标准数据模型类，通常与QTableView组合成MV结构，实现通用的二维数据管理功能
// 每个项是一个QStandardItem类的变量，用于储存项的数据、字体格式、对齐方式等

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initUI();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // 添加下方状态栏
    currentPathLabel = new QLabel("当前文件:", this);
    currentPathLabel->setMinimumWidth(400);
    currentItemLabel = new QLabel("当前单元格:", this);
    currentItemLabel->setMinimumWidth(200);
    currentContextLabel = new QLabel("单元格内容:", this);
    currentContextLabel->setMinimumWidth(200);
    ui->statusbar->addWidget(currentPathLabel);
    ui->statusbar->addWidget(currentItemLabel);
    ui->statusbar->addWidget(currentContextLabel);

    // 创建模型对象和选择对象
    model = new QStandardItemModel(this);
    selection = new QItemSelectionModel(model);
    ui->tableView->setModel(model);
    ui->tableView->setSelectionModel(selection);

    // 设置tableView每栏延伸
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->plainTextEdit->setReadOnly(true);

}

void MainWindow::strListToModel(const QStringList &strList)
{
    // 添加表头
    QStringList headerList = strList.at(0).split(QRegExp("\\s+"));
    model->setHorizontalHeaderLabels(headerList);

    // 循环添加项
    for(int i=1; i<strList.length();i++){
        QStringList tempList = strList.at(i).split(QRegExp("\\s+"));

        for(int j=0; j<tempList.length(); j++){
            model->setItem(i-1, j, new QStandardItem(tempList.at(j)));
        }
    }

}

// 打开文件
void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, "打开", QDir::currentPath(), tr("All(*.*);;Images(*.jpg, *.png)"));
    if (path == ""){
        return;
    }
    model->clear();
    selection->clear();
    ui->plainTextEdit->clear();

    QStringList strList;
    // 打开文件
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)){
        currentPathLabel->setText("当前文件:"+ path);
        QTextStream stream(&file);
        stream.setCodec("UTF-8");

        while(!stream.atEnd()){
            QString temp = stream.readLine();
            strList.append(temp);
            ui->plainTextEdit->appendPlainText(temp); // 逐行读取
        }
        file.close();
    }

    strListToModel(strList);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentItemLabel->setText(QString("当前单元格: %1行 %2列").arg(index.row()+1).arg(index.column()+1));
    currentContextLabel->setText(QString("单元格内容: %1").arg(index.data().toString()));
}

// 模型转到Text视图
void MainWindow::on_actionModelToView_triggered()
{
    // 清空
    ui->plainTextEdit->clear();

    // 转化头文件
    int count = ui->tableView->horizontalHeader()->count();
    QString str;
    for (int i= 0;i < count; i++) {
        str += model->horizontalHeaderItem(i)->text();
        str += "\t";
    }
    ui->plainTextEdit->appendPlainText(str);

    // 转化item内容
    for (int i=0; i< model->rowCount(); i++) {
        str = "";
        for (int j=0; j<count; j++) {
            QStandardItem* tempItem = model->item(i, j);
            str += tempItem->text();
            str += "\t";
        }
        ui->plainTextEdit->appendPlainText(str);
    }
}

// 添加行
void MainWindow::on_actionNew_triggered()
{
    int cloum = model->columnCount();
    if (cloum == 0){
        QMessageBox::information(this, "提示", "请先打开表");
        return; // 如果没有表头，则不增加一行
    }

    QList<QStandardItem*> itemList;
    for (int i = 0; i<cloum; i++) {
        itemList.append(new QStandardItem("0"));
    }

    model->appendRow(itemList);

    // 添加后将选项设置到新增行
    QModelIndex index = model->index(model->rowCount()-1, 0);
    selection->clearSelection();
    selection->setCurrentIndex(index, QItemSelectionModel::Select);
}

// 插入行
void MainWindow::on_actionInsert_triggered()
{
    int cloum = model->columnCount();
    if (cloum == 0){
        QMessageBox::information(this, "提示", "请先打开表");
        return; // 如果没有表头，则不增加一行
    }

    QModelIndex index = selection->currentIndex(); // 获取当前选择项

    QList<QStandardItem*> itemList;
    for (int i = 0; i<cloum; i++) {
        itemList.append(new QStandardItem("0"));
    }

    model->insertRow(index.row(), itemList);

    // 将选项设置到新增项
    selection->clearSelection();
    selection->setCurrentIndex(index, QItemSelectionModel::Select);
}

// 删除行
void MainWindow::on_actionDel_triggered()
{
    QModelIndex index = selection->currentIndex();
    model->removeRow(index.row());
    selection->clear();
}

// 居右
void MainWindow::on_actionLeft_triggered()
{
    QModelIndexList modelList = selection->selectedIndexes();
    foreach(const QModelIndex &index, modelList){
        model->item(index.row(), index.column())->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    }
}

// 居中
void MainWindow::on_actionMid_triggered()
{
    QModelIndexList modelList = selection->selectedIndexes();
    foreach(const QModelIndex &index, modelList){
        model->item(index.row(), index.column())->setTextAlignment(Qt::AlignCenter);
    }
}

// 居右
void MainWindow::on_actionRight_triggered()
{
    QModelIndexList modelList = selection->selectedIndexes();
    foreach(const QModelIndex &index, modelList){
        model->item(index.row(), index.column())->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    }
}

// 加粗
void MainWindow::on_actionBlod_triggered(bool checked)
{
    QModelIndexList modelList = selection->selectedIndexes();
    foreach(const QModelIndex &index, modelList){
        QFont itemFont = model->item(index.row(), index.column())->font();
        itemFont.setBold(checked);
        model->item(index.row(), index.column())->setFont(itemFont);
    }
}


void MainWindow::on_actionSave_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, "请选择保存文件", QDir::currentPath(), "Text(*.txt)");
    if (path != ""){
        on_actionModelToView_triggered();
        QString str = ui->plainTextEdit->toPlainText();
        QFile file(path);
        if (file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)){ // 以只写，Txt格式，覆盖方式打开
            QTextStream stream(&file);
            stream.setCodec("utf-8");
            stream << str;
            file.close();
            QMessageBox::information(this, "提示", "文件保存成功");
        }
        else{
            QMessageBox::warning(this, "警告", "文件保存失败");
        }
    }
}

