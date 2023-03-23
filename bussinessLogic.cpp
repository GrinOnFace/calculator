#include "bussinessLogic.h"

double action_in_calc_memory (action_obj calcObject) {
    double res = NOTHING;
    switch (calcObject.sign) {
        case PLUS:
            res = calcObject.memory + calcObject.number;
            break;
        case MINUS:
            res = calcObject.memory - calcObject.number;
            break;
        case MULTIPLY:
            res = calcObject.memory * calcObject.number;
            break;
        case DIVIDE:
            if(calcObject.number != 0) {
                res = calcObject.memory / calcObject.number;
            } else {
                res = ERROR;
            }
    }
    return res;
}
