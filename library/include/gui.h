/**
 * @file gui.h
 * @author Gianluca (g.canzolino3@studenti.unisa.it)
 * @brief 
 * @version 0.1
 * @date 2022-11-03
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

#ifndef GUI_H
#define GUI_H

#include <stdbool.h>
#include "message.h"

// Screen size
#define WIDHT_SPACE 15
#define COLUMNS 80 //num of chars in a row
#define ROWS 20

// Reset
#define Color_Off  "\033[0m"       // Text Reset

// Regular Colors
#define Black  "\033[30m"        // Black
#define Red  "\033[31m"          // Red
#define Green  "\033[32m"        // Green
#define Yellow  "\033[33m"       // Yellow
#define Blue  "\033[34m"         // Blue
#define Purple  "\033[35m"       // Purple
#define Cyan  "\033[36m"         // Cyan
#define White  "\033[37m"        // White

// Bold
#define BBlack  "\033[1;30m"       // Black
#define BRed  "\033[1;31m"         // Red
#define BGreen  "\033[1;32m"       // Green
#define BYellow  "\033[1;33m"      // Yellow
#define BBlue  "\033[1;34m"        // Blue
#define BPurple  "\033[1;35m"      // Purple
#define BCyan  "\033[1;36m"        // Cyan
#define BWhite  "\033[1;37m"       // White

// Underline
#define UBlack  "\033[4;30m"       // Black
#define URed  "\033[4;31m"         // Red
#define UGreen  "\033[4;32m"       // Green
#define UYellow  "\033[4;33m"      // Yellow
#define UBlue  "\033[4;34m"        // Blue
#define UPurple  "\033[4;35m"      // Purple
#define UCyan  "\033[4;36m"        // Cyan
#define UWhite  "\033[4;37m"       // White

// Background
#define On_Black  "\033[40m"       // Black
#define On_Red  "\033[41m"         // Red
#define On_Green  "\033[42m"       // Green
#define On_Yellow  "\033[43m"      // Yellow
#define On_Blue  "\033[44m"        // Blue
#define On_Purple  "\033[45m"      // Purple
#define On_Cyan  "\033[46m"        // Cyan
#define On_White  "\033[47m"       // White

// High Intensty
#define IBlack  "\033[90m"       // Black
#define IRed  "\033[91m"         // Red
#define IGreen  "\033[92m"       // Green
#define IYellow  "\033[93m"      // Yellow
#define IBlue  "\033[94m"        // Blue
#define IPurple  "\033[95m"      // Purple
#define ICyan  "\033[96m"        // Cyan
#define IWhite  "\033[97m"       // White

// Bold High Intensty
#define BIBlack  "\033[1;90m"      // Black
#define BIRed  "\033[1;91m"        // Red
#define BIGreen  "\033[1;92m"      // Green
#define BIYellow  "\033[1;93m"     // Yellow
#define BIBlue  "\033[1;94m"       // Blue
#define BIPurple  "\033[1;95m"     // Purple
#define BICyan  "\033[1;96m"       // Cyan
#define BIWhite  "\033[1;97m"      // White

// High Intensty backgrounds
#define On_IBlack  "\033[100m"   // Black
#define On_IRed  "\033[101m"     // Red
#define On_IGreen  "\033[102m"   // Green
#define On_IYellow  "\033[103m"  // Yellow
#define On_IBlue  "\033[104m"    // Blue
#define On_IPurple  "\033[195m"  // Purple
#define On_ICyan  "\033[106m"    // Cyan
#define On_IWhite  "\033[107m"   // White

/**
 * @brief 
 * 
 * @param msg 
 * @param receved 
 */
void gui_print(Message* msg, bool receved);

#endif