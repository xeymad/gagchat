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
#include <stdlib.h>
#include <string.h>
#include <assert.h>

TCPSocket* tcp_socket_create(ConnType type, char* server_ip){
    TCPSocket* tcp_socket = malloc(sizeof(TCPSocket));
    assert(tcp_socket!=NULL);
    if(type==CLIENT){
        tcp_socket->sockfd = socket (AF_INET, SOCK_STREAM, 0);
        assert(tcp_socket->sockfd>=0);
        //Creation of the socket
        memset(&(tcp_socket->servaddr), 0, sizeof(tcp_socket->servaddr));
        tcp_socket->servaddr.sin_family = AF_INET;
        tcp_socket->servaddr.sin_addr.s_addr= inet_addr(server_ip);
        tcp_socket->servaddr.sin_port =  htons(SERV_PORT);
    }
    //TODO: server impl
    return tcp_socket;
}

void tcp_socket_server_listen(TCPSocket* tcp_socket){
    //TODO: server impl
    return;
}

void tcp_socket_client_connect(TCPSocket* tcp_socket){
    connect(tcp_socket->sockfd, (struct sockaddr *) &(tcp_socket->servaddr), sizeof(tcp_socket->servaddr));
    assert(tcp_socket->sockfd>=0);
}

void tcp_socket_destroy(TCPSocket* tcp_socket){
    free(tcp_socket);
}