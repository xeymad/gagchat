/**
 * @file tcp_socket.h
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief Implementation of tcp socket both for client and server.
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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "message.h"


#ifndef SERV_PORT
    #define SERV_PORT 3000 //Server open port
#endif
#ifndef LISTENQ
    #define LISTENQ 10 //Max acceptables clients
#endif

typedef enum EConnType{CLIENT, SERVER} ConnType;

typedef struct STCPSocket{
    int sockfd; //File Descriptor of the socket
    struct sockaddr_in servaddr; //Server's address.
}TCPSocket;

/**
 * @brief Creates a TCPSocket and pass its pointer.
 * 
 * @param type the TCPSocket type (client or server)
 * @param server_ip if type = CLIENT, is mandatory to specify
 * the server's ip address formatted as string.
 * @return TCPSocket* pointer to TCPSocket struct
 */
TCPSocket* tcp_socket_create(ConnType type, char* server_ip);

/**
 * @brief Configures the server in listening mode.
 * 
 * @param tcp_socket pointer to TCPSocket struct.
 */
void tcp_socket_server_listen(TCPSocket* tcp_socket);

/**
 * @brief Accepts a connection from a requesting client.
 * 
 * @param tcp_socket pointer to TCPSocket struct.
 * @return int the connection file descriptor.
 */
int tcp_socket_server_accept(TCPSocket* tcp_socket);

/**
 * @brief Connects the client to the specified TCPSocket.
 * 
 * @param tcp_socket pointer to TCPSocket struct.
 */
void tcp_socket_client_connect(TCPSocket* tcp_socket);

/**
 * @brief Sends a Message on TCPSocket.
 * 
 * @param connection_fd connection file descriptor. If client, it is
 * param sockfd of TCPSocket. If server, it is obtained by the output of
 * tcp_socket_server_accept function.
 * @param message the Message to send.
 * @return int On success, these calls return the number of bytes sent. On
 * error, -1 is returned, and errno is set to indicate the error.
 */
int tcp_socket_send_message(int connection_fd, Message* message);

/**
 * @brief Receives a Message from TCPSocket.
 * 
 * @param connection_fd connection file descriptor. If client, it is
 * param sockfd of TCPSocket. If server, it is obtained by the output of
 * tcp_socket_server_accept function.
 * @return Message* pointer to received message.
 */
Message* tcp_socket_recv_message(int connection_fd);

/**
 * @brief Destroys a TCPSocket.
 * 
 * @param tcp_socket the TCPSocket reference to destroy.
 */
void tcp_socket_destroy(TCPSocket* tcp_socket);