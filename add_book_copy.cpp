#include "add_book_copy.h"
#include "ui_add_book_copy.h"
#include "book.h"
#include "global.h"
#include "tree.h"
#include <QVariant>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>


add_book_copy::add_book_copy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::add_book_copy)
{
    ui->setupUi(this);
    QHeaderView *header = ui->danh_sach_ban_sao->horizontalHeader();
    header->setStretchLastSection(false);

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header->setSectionResizeMode(1, QHeaderView::Stretch);
    set_up();
}

add_book_copy::~add_book_copy()
{
    delete ui;
}

void add_book_copy::set_up(){
    ui->ten_dau_sach->clear();
    book_data.traverse_ascending([this](book& b){
        QString text = QString::fromStdString(std::to_string(b.get_ID()) + " - " + b.get_Name());
        ui->ten_dau_sach->addItem(text, QVariant::fromValue(b.get_ID()));
    });
}
void add_book_copy::on_so_ban_sao_valueChanged(int arg1)
{
    while (ui->danh_sach_ban_sao->rowCount() > 0) {
        ui->danh_sach_ban_sao->removeRow(0);
    }
    bc.clear();
    long long book_id = ui->ten_dau_sach->currentData().toLongLong();
    auto setText = [&](int row, int col, const QString &text, bool center = false) {
        QTableWidgetItem *item = new QTableWidgetItem(text);
        if (center)
            item->setTextAlignment(Qt::AlignCenter);
        ui->danh_sach_ban_sao->setItem(row, col, item);
    };
    for (int i = 0;i < arg1;i++){
        Book_copies bcp;
        bcp.set_id(book_copy_data.find_max_id() + 1 + i);
        bcp.set_id_book(book_id);
        bcp.set_status("available");
        bcp.set_ghi_chu("");
        bc.insert(bcp);
        int row = ui->danh_sach_ban_sao->rowCount();
        ui->danh_sach_ban_sao->insertRow(row);
        setText(row, 0, QString::fromStdString( "BS-" + std::to_string(bcp.get_id())), true);
        setText(row, 1, QString::fromStdString(ui->ten_dau_sach->currentText().toStdString()), true);
    }
}
void add_book_copy::on_ten_dau_sach_activated(int index)
{
    on_so_ban_sao_valueChanged(ui->so_ban_sao->value());
}


void add_book_copy::on_them_button_clicked()
{
    if (ui->so_ban_sao->value() <= 0) {
        QMessageBox::warning(this, "Lỗi", "Số bản sao phải lớn hơn 0!");
        return;
    }
    bc.traverse_ascending([this](Book_copies &bcp){
        record.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::ADD_BOOK_COPY, bcp.get_id(), "Đã thêm bản sao " + to_stringll_(bcp.get_id()) + " - " + to_stringll_(bcp.get_id_book()));
        book_copy_data.insert(bcp);
    });
    ghi_copy_book(book_copy_data);
    on_so_ban_sao_valueChanged(0);
    QMessageBox::information(this, "Thành công", "Thêm bản sao sách thành công!");
}

