/**
 * @file client.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief 
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

/**
 * @brief thread for message receiving.
 * 
 */
void* client_message_receiver(void *args);

/**
 * @brief sends a message to the specified user using 
 * the server's tcp socket.
 * 
 * @param tcp_socket the server's socket.
 * @param to_user user to forward message.
 * @param message the message text to forward.
 */
void client_message_sender(int tcp_socket, char* to_user, char* message);