/**
 * @file infohashtable.c
 * @author Gianluca (g.canzolino3@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022 - All Rights Reserved
 * 
 * This file is part of gagchat.
 * gagchat is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * gagchat is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with gagchat. If not, see <http://www.gnu.org/licenses/>.
 * 
 */

#include <stdlib.h>
#include <stdbool.h>
#include "infoHashtable.h"

/**
 * @brief check if frist value is equal to the second value
 * 
 * @return bool 
 */
bool infoEqual (TInfoHashtable val1, TInfoHashtable val2){
    // deprecated
    return false;
}

/**
 * @brief check if frist value is greater to the second value
 * 
 * @return bool 
 */
bool infoGreater (TInfoHashtable val1, TInfoHashtable val2){
    // deprecated
    return false;
}

/**
 * @brief check if frist value is less to the second value
 * 
 * @return bool 
 */
bool infoLess (TInfoHashtable val1, TInfoHashtable val2){
    // deprecated
    return false;
}

/**
 * @brief structured print of the value
 * 
 */
void infoPrint (TInfoHashtable val1){
    // deprecated
}


u_int64_t keyHash (TKeyHashtable key){
    u_int64_t hash = FNV_OFFSET;
    
    //h(x)
    for (const char* p = key; *p; p++) {
        hash ^= (u_int64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }

    return hash;
}

u_int64_t keyHashD (TKeyHashtable key){
    
    u_int64_t hash2 = FNV_OFFSET;

    //d(x)
    for (const char* p = key; *p; p++) {
        hash2 ^= (u_int64_t)(unsigned char)(*p);
        hash2 *= FNV_PRIME_2;
    }

    //printf("key: %s -- h(x): %lu - d(x) = %lu\n", key, hash, hash2);
    return hash2;
}

u_int64_t keyHashExpande (TKeyHashtable key, u_int64_t hash, int j){
    
    u_int64_t hash2 = FNV_OFFSET;

    //d(x)
    for (const char* p = key; *p; p++) {
        hash2 ^= (u_int64_t)(unsigned char)(*p);
        hash2 *= FNV_PRIME_2;
    }

    //printf("key: %s -- h(x): %lu - d(x) = %lu\n", key, hash, hash2);
    return hash + j*hash2;
}





