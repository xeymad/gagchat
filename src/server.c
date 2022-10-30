/**
 * @file server.c
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
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "tcp_socket.h"

int main (int argc, char **argv)
{
    TCPSocket* sock=tcp_socket_create(SERVER,"");
    tcp_socket_server_listen(sock);
    printf("%s\n","Server running...waiting for connections.");
    int connfd = tcp_socket_server_accept(sock);
    printf("%s\n","Received request...");
    Message* msg = tcp_socket_recv_message(connfd);
    printf("%s\n","Received message: ");
    printf("%s: %s\n%d\n",msg->user,msg->text,msg->code);
    close(connfd);
    //destroy socket
    tcp_socket_destroy(sock);
}
