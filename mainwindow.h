#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bussinessLogic.h"

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

    double calc_memory = NOTHING;
    int last_action = NOTHING;

    QString get_res_label();
    void set_res_label(QString new_label);

    void error_check (QString new_label);
    void validation_calc(action_obj temp);
    QString validation_label (QString new_label);
    action_obj structPrepare()
};
#endif // MAINWINDOW_H
