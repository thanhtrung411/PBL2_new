#include "book.h"
#include <iostream>
using namespace std;

book::book(){
    id_book = "";
    ten_sach = "";
    tac_gia = "";
    the_loai = "";
    nha_xuat_ban = "";
    nam_xuat_ban = "";
    so_trang = "";
    ISBN = "";
    ngon_ngu = "";
    tu_khoa = "";
    chuyen_nganh = "";
    don_gia = "null";
    tom_tat = "";
    link_png = "null";
    link_pdf = "null";
    type_book = "null";
    tinh_trang = "0";
    date_created = "";
    admin_created = "";
}

book::book(string id_book, string ten_sach, string tac_gia, string the_loai, string nha_xuat_ban, string nam_xuat_ban, string so_trang, string ISBN, string ngon_ngu, string tu_khoa, string chuyen_nganh, string don_gia, string tom_tat, string link_png, string link_pdf, string type_book, string tinh_trang, string date_created, string admin_created){
    this->id_book = id_book;
    this->ten_sach = ten_sach;
    this->tac_gia = tac_gia;
    this->the_loai = the_loai;
    this->nha_xuat_ban = nha_xuat_ban;
    this->nam_xuat_ban = nam_xuat_ban;
    this->so_trang = so_trang;
    this->ISBN = ISBN;
    this->ngon_ngu = ngon_ngu;
    this->tu_khoa = tu_khoa;
    this->chuyen_nganh = chuyen_nganh;
    this->don_gia = don_gia;
    this->tom_tat = tom_tat;
    this->link_png = link_png;
    this->link_pdf = link_pdf;
    this->type_book = type_book;
    this->tinh_trang = tinh_trang;
    this->date_created = date_created;
    this->admin_created = admin_created;
}

book::~book(){}
void book::set_id_book(string id_book){
    this->id_book = id_book;
}
void book::set_name_book(string ten_sach){
    this->ten_sach = ten_sach;
}
void book::set_tac_gia(string tac_gia){
    this->tac_gia = tac_gia;
}
void book::set_the_loai(string the_loai){
    this->the_loai = the_loai;
}
void book::set_nha_xuat_ban(string nha_xuat_ban){
    this->nha_xuat_ban = nha_xuat_ban;
}
void book::set_nam_xuat_ban(string nam_xuat_ban){
    this->nam_xuat_ban = nam_xuat_ban;
}
void book::set_so_trang(string so_trang){
    this->so_trang = so_trang;
}
void book::set_ISBN(string ISBN){
    this->ISBN = ISBN;
}
void book::set_ngon_ngu(string ngon_ngu){
    this->ngon_ngu = ngon_ngu;
}
void book::set_tu_khoa(string tu_khoa){
    this->tu_khoa = tu_khoa;
}
void book::set_chuyen_nganh(string chuyen_nganh){
    this->chuyen_nganh = chuyen_nganh;
}
void book::set_don_gia(string don_gia){
    this->don_gia = don_gia;
}
void book::set_tom_tat(string tom_tat){
    this->tom_tat = tom_tat;
}
void book::set_type_book(string type_book){
    this->type_book = type_book;
}
void book::set_tinh_trang(string tinh_trang){
    this->tinh_trang = tinh_trang;
}
void book::set_link_png(string link_png){
    this->link_png = link_png;
}
void book::set_link_pdf(string link_pdf){
    this->link_pdf = link_pdf;
}
void book::set_date_created(string date_created){
    this->date_created = date_created;
}
void book::set_admin_created(string admin_created){
    this->admin_created = admin_created;
}
string book::get_id_book(){
    return id_book;
}
string book::get_name_book(){
    return ten_sach;
}
string book::get_tac_gia(){
    return tac_gia;
}
string book::get_the_loai(){
    return the_loai;
}
string book::get_nha_xuat_ban(){
    return nha_xuat_ban;
}
string book::get_nam_xuat_ban(){
    return nam_xuat_ban;
}
string book::get_so_trang(){
    return so_trang;
}
string book::get_ISBN(){
    return ISBN;
}
string book::get_ngon_ngu(){
    return ngon_ngu;
}
string book::get_tu_khoa(){
    return tu_khoa;
}
string book::get_chuyen_nganh(){
    return chuyen_nganh;
}
string book::get_don_gia(){
    return don_gia;
}
string book::get_tom_tat(){
    return tom_tat;
}
string book::get_type_book(){
    return type_book;
}
string book::get_tinh_trang(){
    return tinh_trang;
}
string book::get_link_png(){
    return link_png;
}
string book::get_link_pdf(){
    return link_pdf;
}
string book::get_date_created(){
    return date_created;
}
string book::get_admin_created(){
    return admin_created;
}
string book::get_id_book() const {
    return id_book;
}
string book::get_name_book() const {
    return ten_sach;
}
string book::get_tac_gia() const {
    return tac_gia;
}
string book::get_the_loai() const {
    return the_loai;
}
string book::get_nha_xuat_ban() const {
    return nha_xuat_ban;
}
string book::get_nam_xuat_ban() const {
    return nam_xuat_ban;
}
string book::get_so_trang() const {
    return so_trang;
}
string book::get_ISBN() const {
    return ISBN;
}
string book::get_ngon_ngu() const {
    return ngon_ngu;
}
string book::get_tu_khoa() const {
    return tu_khoa;
}
string book::get_chuyen_nganh() const {
    return chuyen_nganh;
}
string book::get_don_gia() const {
    return don_gia;
}
string book::get_tom_tat() const {
    return tom_tat;
}
string book::get_type_book() const {
    return type_book;
}
string book::get_tinh_trang() const {
    return tinh_trang;
}
string book::get_link_png() const {
    return link_png;
}
string book::get_link_pdf() const {
    return link_pdf;
}
string book::get_date_created() const {
    return date_created;
}
string book::get_admin_created() const {
    return admin_created;
}
