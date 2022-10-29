/**
 * @file tcp_socket.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Implementation of tcp socket.
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
#include <sys/socket.h>

#ifndef SERV_PORT
    #define SERV_PORT 3000 //Server open port
#endif


typedef struct STCPSocket{
    int sockfd; //File Descriptor of the socket
    struct sockaddr_in servaddr; //Server's address.
}TCPSocket;

/**
 * @brief Creates a TCPSocket and pass its pointer.
 * 
 * @param server_ip The server ip formatted as string.
 * @return TCPSocket* pointer to TCPSocket.
 */
TCPSocket* tcp_socket_create(char* server_ip);

/**
 * @brief Connects the client to the specified TCPSocket.
 * 
 * @param tcp_socket pointer to TCPSocket struct.
 */
void tcp_socket_connect(TCPSocket* tcp_socket);