#include "stylesCss.h"

void set_css_btn_dot_enabled (bool status, QPushButton *btn_dot) {
    btn_dot->setEnabled(status);
    if (status) {
        btn_dot->setStyleSheet("QPushButton{border:none;color:white;}");
    } else {
        btn_dot->setStyleSheet("QPushButton{border:none;color:black;}");
    }
}
