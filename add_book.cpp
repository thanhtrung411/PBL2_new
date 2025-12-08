#include "add_book.h"
#include "ui_add_book.h"
#include "book.h"
#include "tree.h"
#include "global.h"
#include "my_string.h"
#include "my_file.h"
#include "my_time.h"
#include "global.h"

#include <QLineEdit>
#include <QDebug>
#include <QPalette>
#include <QMessageBox>
#include <QFileDialog>

add_book::add_book(QWidget *parent)
    : QMainWindow(parent)
    , ui_3(new Ui::add_book)
{
    ui_3->setupUi(this);
    set_the_loai_chuyen_nganh();
    ui_3->trang_them_sach->setCurrentIndex(0);
    ui_3->xoa_button->setVisible(false);
}

add_book::~add_book()
{
    delete ui_3;
}

static void markError(QLineEdit* w, const QString& msg) {
    w->clear();
    w->setPlaceholderText(msg);
    w->setStyleSheet("QLineEdit{border:2px solid #e53935;border-radius: 6px;}");
    QPalette pal = w->palette();
    pal.setColor(QPalette::PlaceholderText, QColor("#e53935"));
    w->setPalette(pal);
    w->setFocus();
}

static void clearError(QLineEdit* w) {
    w->setStyleSheet(R"(QLineEdit {
    background-color: #e8ecef; 
    border-radius: 8px; 
    border: 1px solid #E0E4E8; 
    padding: 8px 10px; 
    color: #1E1E1E; 
    font-size: 12px;
}

QLineEdit:hover {
    background-color: #E5E9ED;
}
QLineEdit:focus {
    background-color: #FFFFFF; 
    border: 1px solid #3498db; 
})");
    w->setPalette(QPalette());
}
void add_book::return_null_all(){
    ui_3->ID_Sach_input->clear();
    ui_3->ten_sach_input->clear();
    ui_3->tac_gia_input->clear();
    ui_3->nha_xuat_ban_input->clear();
    ui_3->nam_xuat_ban_input->clear();
    ui_3->so_trang_input->clear();
    ui_3->ISBN_input->clear();
    ui_3->language_input->clear();
    ui_3->tom_tat_input->clear();
    ui_3->link_png_layout->clear();
    ui_3->link_pdf_layout->clear();
    ui_3->the_loai_sach_input->setCurrentIndex(0);
    ui_3->chuyen_nganh_input->setCurrentIndex(0);

}

void add_book::on_them_button_clicked()
{
    long long id;
    string id_book = ui_3->ID_Sach_input->text().trimmed().toUtf8().toStdString();
    string ten_sach = ui_3->ten_sach_input->text().trimmed().toUtf8().toStdString();
    string tac_gia = ui_3->tac_gia_input->text().trimmed().toUtf8().toStdString();
    string nha_xuat_ban = ui_3->nha_xuat_ban_input->text().trimmed().toUtf8().toStdString();
    int nam_xuat_ban = ui_3->nam_xuat_ban_input->text().trimmed().toUtf8().toInt();
    int so_trang = ui_3->so_trang_input->text().trimmed().toUtf8().toInt();
    string ISBN = ui_3->ISBN_input->text().trimmed().toUtf8().toStdString();
    string ngon_ngu = ui_3->language_input->text().trimmed().toUtf8().toStdString();
    string tom_tat = ui_3->tom_tat_input->toPlainText().trimmed().toUtf8().toStdString();
    string link_png_ = ui_3->link_png_layout->text().trimmed().toUtf8().toStdString();
    string link_pdf_ = ui_3->link_pdf_layout->text().trimmed().toUtf8().toStdString();
    string the_loai = ui_3->the_loai_sach_input->currentText().trimmed().toStdString();
    string chuyen_nganh = ui_3->chuyen_nganh_input->currentText().trimmed().toStdString();
    bool is_read = true;
    bool is_borrow = true;
    bool is_download = true;
    int limit_borrow = ui_3->so_ngay_muon_input->value();
    int number_of_book = ui_3->number_of_book->value();
    string date_created;
    string user_created;
    int check = 1;
    if (ten_sach.empty()){
        markError(ui_3->ten_sach_input,"Vui lòng nhập tên sách");
        check = 0;
    }
    else clearError(ui_3->ten_sach_input);
    if (tac_gia.empty()){
        markError(ui_3->tac_gia_input,"Vui lòng nhập tác giả");
        check = 0;
    }
    else clearError(ui_3->tac_gia_input);
    if (nam_xuat_ban <= 0){
        markError(ui_3->nam_xuat_ban_input,"Vui lòng nhập năm xuất bản");
        check = 0;
    }
    else clearError(ui_3->nam_xuat_ban_input);
    if (ui_3->the_loai_sach_input->currentIndex() == 0){
        check = 0;
    }
    else;
    if (ui_3->chuyen_nganh_input->currentIndex() == 0){
        check = 0;
    }
    else;
    if (nha_xuat_ban.empty()){
        markError(ui_3->nha_xuat_ban_input,"Vui lòng nhập nhà xuất bản");
        check = 0;
    }
    else clearError(ui_3->nha_xuat_ban_input);
    if (so_trang <= 0){
        markError(ui_3->so_trang_input,"Vui lòng nhập số trang");
        check = 0;
    }
    else clearError(ui_3->so_trang_input);
    if (ngon_ngu.empty()){
        markError(ui_3->language_input,"Vui lòng nhập ngôn ngữ");
        check = 0;
    }
    else clearError(ui_3->language_input);
    if (tom_tat.empty()){
        check = 0;
    }
    else;
    if (check){
        book b;
        b.set_ID(to_long_long(id_book));
        b.set_Name(ten_sach);
        b.set_Author(tac_gia);
        int the_loai_id;
        the_loai_data.return_id(the_loai, the_loai_id);
        b.set_The_loai_ID(the_loai_id);
        b.set_NXB(nha_xuat_ban);
        b.set_NamXB(nam_xuat_ban);
        b.set_So_trang(so_trang);
        b.set_ISBN(ISBN);
        b.set_Language(ngon_ngu);
        int chuyen_nganh_id;
        chuyen_nganh_data.return_id(chuyen_nganh, chuyen_nganh_id);
        b.set_Chuyen_nganh_ID(chuyen_nganh_id);
        b.set_Tom_tat(tom_tat);
        my_time d = my_time::now();
        b.set_is_Borrow(is_borrow);
        b.set_is_Download(is_download);
        b.set_is_Read_online(is_read);
        b.set_tong_sach(number_of_book);
        b.set_limit_borrow(limit_borrow);
        b.set_tong_sach_ranh(number_of_book);
        b.set_Date_created(d);
        b.set_Created_by(acc_sign_in.get_ten_dang_nhap());
        QString path = getDataFilePath("png_background\\");
        if (!link_png_.empty()){
            copy_file(link_png_,path.toStdString() + to_string(b.get_ID()) + ".png");
        }
        QString rel = QDir::current().relativeFilePath(path);
        qDebug() << rel;
        b.set_Link_png(rel.toStdString()+ "/" + to_string(b.get_ID()) + ".png");
        
        path = getDataFilePath("pdf_book\\");
        if (!link_pdf_.empty()){
            copy_file(link_pdf_,path.toStdString() + to_string(b.get_ID()) + ".pdf");
        }
        rel = QDir::current().relativeFilePath(path);
        b.set_Link_pdf(rel.toStdString() +"/"+ to_string(b.get_ID()) + ".pdf");
        if (is_chinh_sua_mode) {
            // Chế độ chỉnh sửa: chỉ update thông tin sách
            book_data.update(b,b);
            
            // Xóa toàn bộ bản sao cũ
            book_copy_data.remove_by_book_id(b.get_ID());
            // Tạo lại bản sao mới theo số lượng hiện tại
            int so_luong_moi = ui_3->number_of_book->value();
            for (int i = 0; i < so_luong_moi; i++) {
                Book_copies bc;
                long long id_copy = book_copy_data.find_max_id() + 1;
                bc.set_id(id_copy);
                bc.set_id_book(b.get_ID());
                bc.set_status(is_read ? "available" : "not available");
                book_copy_data.insert(bc);
            }
            ghi_copy_book(book_copy_data);
            ghi_book(book_data);
            QMessageBox box(this);
            box.setWindowTitle("Thông báo");
            box.setText("Cập nhật sách thành công!");
            box.setStyleSheet(R"(
            QMessageBox { background: rgb(243,246,255); }
            QMessageBox QLabel { color:#0868ad; }
            QMessageBox QPushButton {
            background:#fff; color:#0868ad;
            border:1px solid #d0d0d0; border-radius:8px; padding:6px 12px;
            }
            QMessageBox QPushButton:hover  { background:#f5f5f5; }
            QMessageBox QPushButton:default{ border-color:#0078d7; }
            )");
            box.exec();
        } else {
            // Chế độ thêm mới: insert như bình thường
            book_data.insert(b);
            for (int i = 0; i < ui_3->number_of_book->value(); i++) {
            Book_copies bc;
            long long id_copy = book_copy_data.find_max_id() + 1;
            bc.set_id(id_copy);
            bc.set_id_book(b.get_ID());
            if (is_read) {
                bc.set_status("available");
            } else {
                bc.set_status("not available");
            }
            book_copy_data.insert(bc);
            }
            record.log_action(acc_sign_in.get_ten_dang_nhap(), ActionType::ADD_BOOK, b.get_ID(), "Đã thêm sách " + to_stringll_(b.get_ID()) + " - " + b.get_Name());
            ghi_copy_book(book_copy_data);
            ghi_book(book_data);
            QMessageBox box(this);
            box.setWindowTitle("Thông báo");
            box.setText("Thêm sách thành công!");
            box.setStyleSheet(R"(
            QMessageBox { background: rgb(243,246,255); }
            QMessageBox QLabel { color:#0868ad; }
            QMessageBox QPushButton {
            background:#fff; color:#0868ad;
            border:1px solid #d0d0d0; border-radius:8px; padding:6px 12px;
            }
            QMessageBox QPushButton:hover  { background:#f5f5f5; }
            QMessageBox QPushButton:default{ border-color:#0078d7; }
            )");
            box.exec();
        }
        //box.setIconPixmap(QPixmap(":/icons/icons_/error.png").scaled(16,16, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        if (is_file_mode) {
            // Tăng index lên để sang cuốn tiếp theo
            STT++;

            // Kiểm tra xem còn sách trong list không
            if (STT < book_add.count_data()) {
                // Vẫn còn -> Load cuốn tiếp theo lên form
                hien_thi_sach_theo_file(book_add[STT]);
                
                // Cập nhật tiêu đề window hoặc label nào đó cho ngầu (tuỳ chọn)
                this->setWindowTitle(QString("Đang nhập cuốn %1 / %2")
                                     .arg(STT + 1)
                                     .arg(book_add.count_data()));
            } 
            else {
                // Hết sách -> Tắt chế độ file mode
                is_file_mode = false;
                book_add.clear();
                return_null_all(); // Xóa trắng form
                QMessageBox::information(this, "Hoàn tất", "Đã nhập hết danh sách sách từ file!");
                this->setWindowTitle("Quản lý thư viện");
            }
        } 
        else {
            // Nếu nhập tay bình thường thì xoá trắng form như cũ
            if (!is_chinh_sua_mode) return_null_all();
        }
    }
    else {
        return;
    }
}

//string user_nguoi_dung = ui_2->user_input->text().trimmed().toUtf8().toStdString();

void add_book::on_chuyen_nganh_input_textActivated(const QString &arg1){
    set_ID_book();
}


void add_book::on_the_loai_sach_input_textActivated(const QString &arg1){
    set_ID_book();
}

void add_book::set_ID_book(){
    string chuyen_nganh_ = ui_3->chuyen_nganh_input->currentText().toStdString();
    string the_loai_ = ui_3->the_loai_sach_input->currentText().toStdString();
    if (ui_3->chuyen_nganh_input->currentIndex() == 0) return;
    if (ui_3->the_loai_sach_input->currentIndex() == 0) return;
    if (is_chinh_sua_mode){
        int chuyen_nganh_id_temp;
        chuyen_nganh_data.return_id(chuyen_nganh_, chuyen_nganh_id_temp);
        int the_loai_id_temp;
        the_loai_data.return_id(the_loai_, the_loai_id_temp);
        
        if (book_chinh_sua.get_Chuyen_nganh_ID() == chuyen_nganh_id_temp &&
            book_chinh_sua.get_The_loai_ID() == the_loai_id_temp){
            ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(book_chinh_sua.get_ID())));
            return;
        }
    }
    int The_loai_ID;
    the_loai_data.return_id(the_loai_,The_loai_ID);
    int Chuyen_nganh_ID;
    chuyen_nganh_data.return_id(chuyen_nganh_, Chuyen_nganh_ID);
    if (chuyen_nganh_ == "Khác..."){
        Chuyen_nganh_ID = 99;
    }
    my_time now = my_time::now();
    long long ID_CN_temp;
    if (Chuyen_nganh_ID < 10){
        ID_CN_temp = Chuyen_nganh_ID *1000000;
    }
    else {
        ID_CN_temp = Chuyen_nganh_ID *1000000;
    }
    if (the_loai_ == "Khác..."){
        The_loai_ID = 8;
        BST_Book b;
        book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b,book_data);
        long long max_id = b.find_max_id();
        if ((max_id - 99999 & 100000) == 0 && max_id > 0){
            The_loai_ID = 9;
            BST_Book b_;
            book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b_,book_data);
            long long max_id_ = b_.find_max_id();
            if ((max_id_ - 99999 & 100000) == 0 && max_id_ > 0){
                ui_3->ID_Sach_input->clear();
                ui_3->ID_Sach_input->setPlaceholderText("Hết mã ID cho chuyên ngành này");
                return;
            }
            else{
                long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
                if (max_id_ < ID_temp -1){
                    ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(ID_temp)));
                    return;
                }
                else {
                    long long new_id = max_id_ + 1;
                    ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(new_id)));
                    return;
                }
            }
        }
        else{
            long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
            if (max_id < ID_temp -1){
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(ID_temp)));
                return;
            }
            else {
                long long new_id = max_id + 1;
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(new_id)));
                return;
            }
        }
    }
    else{
        BST_Book b;
        book_data.tong_hop_sach_TL_CN(The_loai_ID, Chuyen_nganh_ID, b,book_data);
        long long max_id = b.find_max_id();
        if ((max_id - 99999 & 100000) == 0 && max_id > 0){
            ui_3->ID_Sach_input->clear();
            ui_3->ID_Sach_input->setPlaceholderText("Hết mã ID cho chuyên ngành này");
            return;
        }
        else{
            long long ID_temp = (long long)now.get_year() * 100000000LL + ID_CN_temp + The_loai_ID * 100000 + 1;
            if (max_id < ID_temp -1){
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_string(ID_temp)));
                return;
            }
            else {
                long long new_id = max_id + 1;
                ui_3->ID_Sach_input->setText(QString::fromStdString(to_string(new_id)));
                return;
            }
        }
    }
}

void add_book::set_the_loai_chuyen_nganh(){
    ui_3->the_loai_sach_input->clear();
    ui_3->chuyen_nganh_input->clear();
    ui_3->the_loai_sach_input->addItem("Vui lòng chọn thể loại sách...");
    ui_3->chuyen_nganh_input->addItem("Vui lòng chọn chuyên ngành...");
    for (int i = 0 ; i < the_loai_data.count_data() ; i++){
        ui_3->the_loai_sach_input->addItem(the_loai_data[i].get_name().c_str());
    }
    for (int i = 0 ; i < chuyen_nganh_data.count_data() ; i++){
        ui_3->chuyen_nganh_input->addItem(chuyen_nganh_data[i].get_name().c_str());
    }
    ui_3->the_loai_sach_input->addItem("Khác...");
    ui_3->chuyen_nganh_input->addItem("Khác...");
    ui_3->the_loai_sach_input->setCurrentIndex(0);
    ui_3->chuyen_nganh_input->setCurrentIndex(0);

}
void add_book::on_link_png_button_clicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Chọn ảnh"),
        QDir::homePath(),                                 // thư mục mở đầu
        tr("Ảnh (*.png *.jpg *.jpeg *.bmp *.gif);;Tất cả (*)")
        );
    if (fn.isEmpty()) return;

    // (tuỳ) lưu đường dẫn tương đối so với thư mục làm việc
    QString rel = QDir::current().relativeFilePath(fn);
    ui_3->link_png_layout->setText(rel);
}


void add_book::on_link_pdf_button_clicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Chọn file"),
        QDir::homePath(),
        tr("PDF (*.pdf);;Tất cả (*)")
        );
    if (fn.isEmpty()) return;
    QString rel = QDir::current().relativeFilePath(fn);
    ui_3->link_pdf_layout->setText(rel);
}

void add_book::on_the_loai_sach_input_activated(int index)
{

}


void add_book::on_file_mau_csv_clicked()
{
    this->setStyleSheet(
    "QMessageBox { background-color: #f0f0f0; }"
    "QMessageBox QLabel { color: #1E1E1E; }"
    "QMessageBox QPushButton {"
        "background-color: #3498db; color: white; "
        "border-radius: 6px; padding: 6px 25px; "
        "min-width: 60px; outline: none; border: none;"
    "}"
    "QMessageBox QPushButton:hover { background-color: #2980b9; }"
    "QMessageBox QPushButton:pressed { background-color: #1f618d; }"
    );
    QString sourceFile = getDataFilePath("data/book_template.csv");
    
    QString saveFilePath = QFileDialog::getSaveFileName(
        this,
        tr("Lưu file mẫu"),
        QDir::homePath() + "/book_template.csv",
        tr("CSV (*.csv);;Tất cả (*)")
    );
    
    if (saveFilePath.isEmpty()) return;
    
    if (!QFile::exists(sourceFile)) {
        QMessageBox::warning(this, "Lỗi", "Không tìm thấy file mẫu!");
        return;
    }
    
    if (QFile::exists(saveFilePath)) {
        QFile::remove(saveFilePath);
    }
    
    if (QFile::copy(sourceFile, saveFilePath)) {
        QMessageBox::information(this, "Thành công", "Đã lưu file mẫu tại: " + saveFilePath);
    } else {
        QMessageBox::warning(this, "Lỗi", "Không thể lưu file mẫu!");
    }
}


void add_book::on_nhap_file_clicked()
{
    QString fn = QFileDialog::getOpenFileName(
        this,
        tr("Chọn file CSV"),
        QDir::homePath(),
        tr("CSV (*.csv);;Tất cả (*)")
    );
    
    if (fn.isEmpty()) return;
    
    QFile file(fn);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Lỗi", "Không thể mở file!");
        return;
    }
    
    QTextStream in(&file);
    // Bỏ qua dòng tiêu đề
    if (!in.atEnd()) {
        in.readLine();
    }
    
    int successCount = 0;
    int failCount = 0;
    long long id = 0;
    while (!in.atEnd()) {
        id++;
        QString line = in.readLine();
        QStringList fields = line.split(',');
        
        if (fields.size() < 9) {
            failCount++;
            continue;
        }
        
        try {
            book b;
            b.set_Name(fields[0].trimmed().toStdString());
            b.set_Author(fields[1].trimmed().toStdString());
            b.set_NXB(fields[2].trimmed().toStdString());
            b.set_NamXB(fields[3].trimmed().toInt());
            b.set_So_trang(fields[4].trimmed().toInt());
            b.set_ISBN(fields[5].trimmed().toStdString());
            b.set_Language(fields[6].trimmed().toStdString());
            b.set_Tom_tat(fields[7].trimmed().toStdString());
            int the_loai_id;
            the_loai_data.return_id(fields[8].trimmed().toStdString(), the_loai_id);
            b.set_The_loai_ID(the_loai_id);
            
            int chuyen_nganh_id;
            chuyen_nganh_data.return_id(fields[9].trimmed().toStdString(), chuyen_nganh_id);
            b.set_Chuyen_nganh_ID(chuyen_nganh_id);
            
            b.set_tong_sach(fields[10].trimmed().toInt());
            
            my_time d = my_time::now();
            b.set_Date_created(d);
            b.set_Created_by(acc_sign_in.get_ten_dang_nhap());
            
            // Tạo ID tự động
            long long ID_temp = id;
            b.set_ID(ID_temp);
            
            book_add.insert(b);        
            successCount++;
        } catch (...) {
            failCount++;
        }
    }
    
    file.close();
    
    QMessageBox::information(this, "Hoàn thành", 
        QString("Nhập thành công: %1 sách\nThất bại: %2 sách")
        .arg(successCount).arg(failCount));
    ui_3->trang_them_sach->setCurrentIndex(0);
    hien_thi_sach_theo_file(book_add[0]);
}

void add_book::set_up_file_mode(){
    is_file_mode = true;
    ui_3->trang_them_sach->setCurrentIndex(1);
    ui_3->xoa_button->setVisible(true);
}

void add_book::hien_thi_sach_theo_file(book b){
    ui_3->ten_sach_input->setText(QString::fromStdString(b.get_Name()));
    ui_3->tac_gia_input->setText(QString::fromStdString(b.get_Author()));
    ui_3->nha_xuat_ban_input->setText(QString::fromStdString(b.get_NXB()));
    ui_3->nam_xuat_ban_input->setText(QString::number(b.get_NamXB()));
    ui_3->so_trang_input->setText(QString::number(b.get_So_trang()));
    ui_3->ISBN_input->setText(QString::fromStdString(b.get_ISBN()));
    ui_3->language_input->setText(QString::fromStdString(b.get_Language()));
    ui_3->tom_tat_input->setPlainText(QString::fromStdString(b.get_Tom_tat()));
    int the_loai_id = b.get_The_loai_ID();
    string the_loai_name;
    the_loai_data.return_name(the_loai_id, the_loai_name);
    int index_tl = ui_3->the_loai_sach_input->findText(QString::fromStdString(the_loai_name));
    if (index_tl != -1){
        ui_3->the_loai_sach_input->setCurrentIndex(index_tl);
    }
    int chuyen_nganh_id = b.get_Chuyen_nganh_ID();
    string chuyen_nganh_name;
    chuyen_nganh_data.return_name(chuyen_nganh_id, chuyen_nganh_name);
    int index_cn = ui_3->chuyen_nganh_input->findText(QString::fromStdString(chuyen_nganh_name));
    if (index_cn != -1){
        ui_3->chuyen_nganh_input->setCurrentIndex(index_cn);
    }
    ui_3->number_of_book->setValue(b.get_tong_sach());
    ui_3->so_ngay_muon_input->setValue(b.get_limit_borrow());
}

void add_book::set_up_chinh_sua_mode(book b){
    is_chinh_sua_mode = true;
    this->book_chinh_sua = b;
    ui_3->trang_them_sach->setCurrentIndex(0);
    ui_3->them_sach_layout->setText("Chỉnh sửa sách");
    ui_3->them_button->setText("Lưu thay đổi");
    ui_3->ID_Sach_input->setText(QString::fromStdString(to_stringll_(b.get_ID())));
    ui_3->ten_sach_input->setText(QString::fromStdString(b.get_Name()));
    ui_3->tac_gia_input->setText(QString::fromStdString(b.get_Author()));
    ui_3->nha_xuat_ban_input->setText(QString::fromStdString(b.get_NXB()));
    ui_3->nam_xuat_ban_input->setText(QString::number(b.get_NamXB()));
    ui_3->so_trang_input->setText(QString::number(b.get_So_trang()));
    ui_3->ISBN_input->setText(QString::fromStdString(b.get_ISBN()));
    ui_3->language_input->setText(QString::fromStdString(b.get_Language()));
    ui_3->tom_tat_input->setPlainText(QString::fromStdString(b.get_Tom_tat()));
    int the_loai_id = b.get_The_loai_ID();
    string the_loai_name;
    the_loai_data.return_name(the_loai_id, the_loai_name);
    int index_tl = ui_3->the_loai_sach_input->findText(QString::fromStdString(the_loai_name));
    if (index_tl != -1){
        ui_3->the_loai_sach_input->setCurrentIndex(index_tl);
    }
    int chuyen_nganh_id = b.get_Chuyen_nganh_ID();
    string chuyen_nganh_name;
    chuyen_nganh_data.return_name(chuyen_nganh_id, chuyen_nganh_name);
    int index_cn = ui_3->chuyen_nganh_input->findText(QString::fromStdString(chuyen_nganh_name));
    if (index_cn != -1){
        ui_3->chuyen_nganh_input->setCurrentIndex(index_cn);
    }
    ui_3->number_of_book->setValue(b.get_tong_sach());
    ui_3->so_ngay_muon_input->setValue(b.get_limit_borrow());
}

void add_book::on_xoa_button_clicked()
{
    if (is_file_mode) {
        // Tăng index lên để sang cuốn tiếp theo
        STT++;

        // Kiểm tra xem còn sách trong list không
        if (STT < book_add.count_data()) {
            // Vẫn còn -> Load cuốn tiếp theo lên form
            hien_thi_sach_theo_file(book_add[STT]);
            
            // Cập nhật tiêu đề window hoặc label nào đó cho ngầu (tuỳ chọn)
            this->setWindowTitle(QString("Đang nhập cuốn %1 / %2")
                                    .arg(STT + 1)
                                    .arg(book_add.count_data()));
        } 
        else {
            // Hết sách -> Tắt chế độ file mode
            is_file_mode = false;
            book_add.clear();
            return_null_all(); // Xóa trắng form
            QMessageBox::information(this, "Hoàn tất", "Đã nhập hết danh sách sách từ file!");
            this->setWindowTitle("Quản lý thư viện");
        }
    }
}

