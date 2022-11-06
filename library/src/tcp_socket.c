/**
 * @file tcp_socket.c
 * @author Giuseppe Gambardella (g.gambardella23@studenti.unisa.it)
 * @brief
 * @version 0.1
 * @date 2022-10-30
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
#include "tcp_socket.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/**
 * @brief Creates a TCPSocket and pass its pointer.
 *
 * @param type the TCPSocket type (client or server)
 * @param server_ip if type = CLIENT, is mandatory to specify
 * the server's ip address formatted as string.
 * @return TCPSocket* pointer to TCPSocket struct
 */
TCPSocket *tcp_socket_create(ConnType type, char *server_ip)
{
    TCPSocket *tcp_socket = malloc(sizeof(TCPSocket));
    assert(tcp_socket != NULL);
    tcp_socket->sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(tcp_socket->sockfd >= 0);
    memset(&(tcp_socket->servaddr), 0, sizeof(tcp_socket->servaddr));
    if (type == CLIENT)
    {
        // Client socket
        tcp_socket->servaddr.sin_family = AF_INET;
        tcp_socket->servaddr.sin_addr.s_addr = inet_addr(server_ip);
        tcp_socket->servaddr.sin_port = htons(SERV_PORT);
        return tcp_socket;
    }
    // Server socket
    else
    {
        tcp_socket->servaddr.sin_family = AF_INET;
        tcp_socket->servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        tcp_socket->servaddr.sin_port = htons(SERV_PORT);
        return tcp_socket;
    }
}

/**
 * @brief Configures the server in listening mode.
 *
 * @param tcp_socket pointer to TCPSocket struct.
 */
void tcp_socket_server_listen(TCPSocket *tcp_socket)
{
    bind(tcp_socket->sockfd, (struct sockaddr *)&(tcp_socket->servaddr), sizeof(tcp_socket->servaddr));
    listen(tcp_socket->sockfd, LISTENQ);
}

/**
 * @brief Accepts a connection from a requesting client.
 *
 * @param tcp_socket pointer to TCPSocket struct.
 * @return int the connection file descriptor.
 */
int tcp_socket_server_accept(TCPSocket *tcp_socket)
{
    struct sockaddr_in cliaddr;
    int clilen = sizeof(cliaddr);
    return accept(tcp_socket->sockfd, (struct sockaddr *)&cliaddr, &clilen);
}

/**
 * @brief Connects the client to the specified TCPSocket.
 *
 * @param tcp_socket pointer to TCPSocket struct.
 */
void tcp_socket_client_connect(TCPSocket *tcp_socket)
{
    connect(tcp_socket->sockfd, (struct sockaddr *)&(tcp_socket->servaddr), sizeof(tcp_socket->servaddr));
    assert(tcp_socket->sockfd >= 0);
}

/**
 * @brief Sends a Message on TCPSocket.
 *
 * @param connection_fd connection file descriptor. If client, it is
 * param sockfd of TCPSocket. If server, it is obtained by the output of
 * tcp_socket_server_accept function.
 * @param message the Message to send.
 * @return int On success, returns the number of bytes sent. On
 * error, -1 is returned, and errno is set to indicate the error.
 */
int tcp_socket_send_message(int connection_fd, Message *message)
{
    return send(connection_fd, (void *)message, sizeof(Message), 0);
}

/**
 * @brief Receives a Message from TCPSocket.
 *
 * @param connection_fd connection file descriptor. If client, it is
 * param sockfd of TCPSocket. If server, it is obtained by the output of
 * tcp_socket_server_accept function.
 * @param message pointer to the message to receive.
 * @return int returns the number of bytes received, or -1 if an
 * error occurred.  In the event of an error, errno is set to
 * indicate the error.
 */
int tcp_socket_recv_message(int connection_fd, Message *message)
{
    return recv(connection_fd, (void *)message, sizeof(Message), 0);
}

/**
 * @brief Destroys a TCPSocket.
 *
 * @param tcp_socket the TCPSocket reference to destroy.
 */
void tcp_socket_destroy(TCPSocket *tcp_socket)
{
    close(tcp_socket->sockfd);
    free(tcp_socket);
}