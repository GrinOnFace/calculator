#ifndef BUSSINESSLOGIC_H
#define BUSSINESSLOGIC_H

enum Operation {
    PLUS = 1,
    MINUS,
    MULTIPLY,
    DIVIDE
};

#define ERROR 99999e-99
#define NOTHING 0

struct action_obj{
    double memory;
    double number;
    int sign;
};

double action_in_calc_memory (action_obj calcObject);

#endif // BUSSINESSLOGIC_H
