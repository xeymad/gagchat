/**
 * @file message.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Definition of struct Message.
 * @version 0.1
 * @date 2022-10-28
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


#define USR_MAXLEN 256 
#define TXT_MAXLEN 4096 

/**
 * @brief struct exchanged by parties for gagchat
 * 
 */
typedef struct SMessage{
    char user[USR_MAXLEN]; //Username is a string with a maximum length of 256 characters.
    char text[TXT_MAXLEN]; //Message text is a string with a maximum length of 4096 characters.
    int code; //Error code is represented by integer.
} Message;

/**
 * @brief Creates a basic exchangeable message.
 * 
 * @param user Username
 * @param text Message text
 * @return Message 
 */
Message message_constructor(char *user, char* text);

/**
 * @brief Creates an error message.
 * 
 * @param user Username
 * @param text Message text
 * @param code Error code
 * @return Message 
 */
Message message_err_constructor(char *user, char* text, int code);