#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

enum Operation {
    PLUS = 1,
    MINUS,
    MULTIPLY,
    DIVIDE
};

#define PRECISION 15


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_clearAll_clicked();
    void on_btn_clearOne_clicked();
    void on_btn_change_sign_clicked();
    void on_btn_dot_clicked();
    void on_btn_numbers_clicked(QString number);
    void on_btn_sign_clicked(int sign);
    void on_btn_equls_clicked();

private:
    Ui::MainWindow *ui;

    double calc_memory = 0;
    int last_action = 0;

    QString validation_label (QString lable);
    QString get_res_label();
    void set_res_label(QString new_label);
    void error_check (QString str);
    void set_css_btn_dot_enabled (bool status);
    double action_in_calc_memory (double number);
};
#endif // MAINWINDOW_H
