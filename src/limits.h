//
// Created by Steven Imle on 11/27/16.
//

#ifndef INC_4_LIMITS_H
#define INC_4_LIMITS_H

#include "types_data.h"

const reg_addr REGISTER_COUNT = 32;
const reg_addr REGISTER_COUNT_FP = 32;

const reg_addr MIN_ADDRESS = 0;
const reg_addr MAX_ADDRESS = REGISTER_COUNT - 1;
const reg_addr MIN_ADDRESS_FP = MAX_ADDRESS + 1;
const reg_addr MAX_ADDRESS_FP = REGISTER_COUNT_FP - 1;

const reg_addr INVALID_REGISTER = MAX_ADDRESS_FP + 1;

#endif //INC_4_LIMITS_H
