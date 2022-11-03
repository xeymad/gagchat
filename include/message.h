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

#ifndef USR_MAXLEN
    #define USR_MAXLEN 64 
#endif
#ifndef TXT_MAXLEN
    #define TXT_MAXLEN 1024 
#endif

/**
 * @brief Message Codes for protocol.
 * 
 */
#define MESSAGE        0    // Normal message directed to user.
#define MSG_CLI_CREATE 1    // Request for creating a new user.
#define MSG_SRV_USRACK 2    // User is accepted by the server.
#define MSG_SRV_USRNCK 3    // User is NOT accepted by the server.


/**
 * @brief struct exchanged by parties for gagchat
 * 
 */
#ifndef MESSAGE_STRUCT
typedef struct SMessage{
    char user[USR_MAXLEN]; //Username is a string with a maximum length of 64 characters.
    char text[TXT_MAXLEN]; //Message text is a string with a maximum length of 1024 characters.
    int code; //Error code is represented by integer.
} Message;
#endif

/**
 * @brief Creates an empty message.
 * 
 * @return Message* pointer to the Empty message.
 */
Message* message_create();

/**
 * @brief Constructs a basic exchangeable message.
 * 
 * @param user Username
 * @param text Message text
 * @return void
 */
void message_constructor(Message* message,char *user, char* text);

/**
 * @brief Constructs a code message.
 * 
 * @param user Username
 * @param text Message text
 * @param code code to append
 * @return void
 */
void message_code_constructor(Message* message, char *user, char* text, int code);

/**
 * @brief Destroys a Message.
 * 
 * @param message the Message reference to destroy.
 */
void message_destroy(Message* message);