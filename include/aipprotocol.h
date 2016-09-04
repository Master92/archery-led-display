//  Copyright (C) 2016 Nils Friedchen <nils.friedchen@googlemail.com>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program; if not, write to the Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA,
//  or see see <http://gnu.org/licenses/gpl-2.0.txt>

#ifndef AIPPROTOCOL_H
#define AIPPROTOCOL_H

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
    
    static const int ADD_END = 15;
    
    static const int DEL_END = 16;
}

#endif /* AIPPROTOCOL_H */

