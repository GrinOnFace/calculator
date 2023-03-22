#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_one, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("1");});
    connect(ui->btn_two, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("2");});
    connect(ui->btn_three, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("3");});
    connect(ui->btn_four, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("4");});
    connect(ui->btn_five, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("5");});
    connect(ui->btn_six, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("6");});
    connect(ui->btn_seven, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("7");});
    connect(ui->btn_eight, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("8");});
    connect(ui->btn_nine, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("9");});
    connect(ui->btn_zero, &QPushButton::clicked, this, [this]{MainWindow::on_btn_numbers_clicked("0");});

    //    connect(ui->btn_clear, &QPushButton::clicked, this, &MainWindow::on_btn_clear_clicked);
    //    connect(ui->btn_dot, &QPushButton::clicked, this, &MainWindow::on_btn_dot_clicked);
    //    connect(ui->btn_del, &QPushButton::clicked, this, &MainWindow::on_btn_del_clicked);
    //    connect(ui->btn_change_sign, &QPushButton::clicked, this, &MainWindow::on_btn_change_sign_clicked);

    connect(ui->btn_plus, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(PLUS);});
    connect(ui->btn_minus, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(MINUS);});
    connect(ui->btn_multiply, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(MULTIPLY);});
    connect(ui->btn_divide, &QPushButton::clicked, this, [this]{MainWindow::on_btn_sign_clicked(DIVIDE);});

    connect(ui->btn_equals, &QPushButton::clicked, this, &MainWindow::on_btn_equls_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::get_res_label () {
    return ui->result_label->text();
}

void MainWindow::set_res_label (QString new_label) {
    ui->result_label->setText(new_label);
}

void MainWindow::error_check (QString str) {
    if (str.contains('e')) {
        QMessageBox::critical(this, "Error", "e in label. Push AC or use sign buttons");
    } else if (str.length() == PRECISION){
        QMessageBox::critical(this, "Error", "Limit quantity of numbers");
    }
}

void MainWindow::set_css_btn_dot_enabled (bool status) {
    ui->btn_dot->setEnabled(status);
    if (status) {
        ui->btn_dot->setStyleSheet("QPushButton{border:none;color:white;}");
    } else {
        ui->btn_dot->setStyleSheet("QPushButton{border:none;color:black;}");
    }
}

void MainWindow::on_btn_numbers_clicked (QString number) {
    QString label = get_res_label();
    if (!label.contains("e")) {
        if(label == "0") {
            set_res_label(number);
        } else if (label == "-0") {
            set_res_label("-" + number);
        } else if (label.length() < PRECISION) {
            label = label + number;
            set_res_label(label);
        } else {
            error_check(label);
        }
    } else {
        error_check(label);
    }
}

void MainWindow::on_btn_clearAll_clicked()
{
    set_res_label("0");
    last_action = 0;
    calc_memory = 0;
    set_css_btn_dot_enabled(1);
}

void MainWindow::on_btn_clearOne_clicked()
{
    QString new_label = get_res_label();

    if (get_res_label().length() == 2 && get_res_label().contains("-")){
        new_label.remove(-1, 2);
    }
    if(!new_label.contains("e")){
        new_label.remove(-1, 1);
        if( !new_label.contains(".")) {
            set_css_btn_dot_enabled(1);
        }
    } else {
        error_check(new_label);
    }
    set_res_label(new_label);
}

void MainWindow::on_btn_change_sign_clicked()
{
    QString label = get_res_label();
    QString new_label;

    if(label.contains("-")) {
        new_label = label.remove(0, 1);
    } else if (label != "0" && !label.contains("-")){
        new_label = "-" + label;
    } else {
        new_label = "-0";
    }

    set_res_label(new_label);
}

void MainWindow::on_btn_dot_clicked()
{
    QString new_label = get_res_label();

    if (new_label.length() == 0) {
        set_res_label("0.");
        set_css_btn_dot_enabled(0);
    } else if (new_label.length() < PRECISION - 1 && !new_label.contains("e")) {
        new_label = new_label + ".";
        set_res_label(new_label);
        set_css_btn_dot_enabled(0);
    } else {
        error_check(new_label);
    }
}

void MainWindow::on_btn_sign_clicked (int sign) {
    QString label = get_res_label();
    double number = label.toDouble();
    set_res_label("");
    if (last_action == 0){
        last_action = sign;
        calc_memory = number;
    }
    else{
        action_in_calc_memory(number);
    }
    last_action = sign;
    set_css_btn_dot_enabled(1);
}

void MainWindow::on_btn_equls_clicked () {
    QString label = get_res_label();
    double number = label.toDouble();

    action_in_calc_memory(number);
    QString new_label = QString().setNum(calc_memory, 'g', PRECISION);

    set_res_label(new_label);

    if (get_res_label().contains(".")) {
        set_css_btn_dot_enabled(0);
    } else {
        set_css_btn_dot_enabled(1);
    }
    last_action = 0;

}

double MainWindow::action_in_calc_memory (double number) {
    switch (last_action) {
        case PLUS:
            calc_memory += number;
            break;
        case MINUS:
            calc_memory -= number;
            break;
        case MULTIPLY:
            calc_memory *= number;
            break;
        case DIVIDE:
            if(number != 0) {
                calc_memory = calc_memory / number;
            } else {
                QMessageBox::critical(this, "Error", "Don't divide to zero");
            }
            break;
        default:
            break;
    }
}
