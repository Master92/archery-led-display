/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   aipprotocol.h
 * Author: nils
 *
 * Created on 6. März 2016, 08:53
 */

#ifndef AIPPROTOCOL_H
#define AIPPROTOCOL_H

#include <string>

namespace aip {
    static const int PORT = 13337;
    
    static const int NEXT = 1;
    /**
     * 0: UPDATE\n
     * 1: time/10\n
     * 2: time rest\n
     * 3: color\n
     * 4: group\n
     * 5: end\n
     * 6: max_ends\n
     */
    static const int UPDATE = 2;
    
    __attribute_deprecated__
    static const int SHOOT_IN = 20;
    __attribute_deprecated__
    static const int WAINDOOR = 21;
    __attribute_deprecated__
    static const int WAOUTDOOR = 22;
    __attribute_deprecated__
    static const int LIGA = 23;
    __attribute_deprecated__
    static const int FINALE = 30;
    
    static const int COLOR_RED=100;
    static const int COLOR_YELLOW=101;
    static const int COLOR_GREEN=102;
    
    /**
     * The options are being transmitted in the following order:\n
     * ammount of ends [int]\n
     * preparation before each end [int]\n
     * duration of each end [int]\n
     * group (ab/cd) ['0'|'1']
     */
    static const int NEW_ROUND = 10;
    /**
     * Second character is an integer describing the length of the
     * following text message.
     */
    static const int RUNTEXT = 11;
    /**
     * Transmitted in 202_length_H_M_S
     */
    static const int TIMER = 12;
    /**
     * Format: +%Y%m%d%H%M%S
     */
    static const int SYNC = 13;
    
    static const int TIME = 14;
}

#endif /* AIPPROTOCOL_H */

