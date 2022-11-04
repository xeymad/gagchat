/**
 * @file gui.c
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

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>

#include "gui.h"

/**
 * @brief set the color of text or background, apply a text style
 * 
 * @param color 
 */
void gui_set_color(char* color)
{
    printf("%s", color);
}

/**
 * @brief Print @param n time the string @param str
 * 
 * @param str string to print
 * @param n times
 */
void gui_print_n_times(char* str, int n)
{
    for(int i=0; i<n; i++)
        printf("%s", str);
}

/**
 * @brief Print the upper and lower separator of box
 * 
 */
void gui_print_horizontal_line()
{
    printf("+");
    gui_print_n_times("-", COLUMNS-2);
    printf("+\n");
}

/**
 * @brief Print the upper and lower separator of the text box
 * 
 * @param is_sender true if is a message receved, else false
 */
void gui_print_horizontal_msg_line(bool is_sender)
{
    if(!is_sender)
        gui_print_n_times(" ", WIDHT_SPACE);
    printf("+");
    gui_print_n_times("-", COLUMNS-WIDHT_SPACE-2);
    printf("+\n");
}

/**
 * @brief 
 * 
 * @param user 
 * @param is_sender true if is a message receved, else false
 */
void gui_print_user_msg(char* user, bool is_sender)
{
    if(is_sender)
    {
        gui_set_color(BGreen);
        printf("%s->\n", user);
    }
    else{
        gui_set_color(BBlue);
        int start = COLUMNS - strlen(user);
        printf("%*s", start, "<-");
        printf("%s\n", user);
    }
    gui_set_color(Color_Off);
}

void gui_print_msg(char* msg, bool is_sender)
{
    int len_msg = strlen(msg);
    double size = (double)len_msg / (double)(COLUMNS - WIDHT_SPACE - 4);
    int times = ceil(size);
    
    gui_print_horizontal_msg_line(is_sender);
    int flag = 0;
    
    while(times != 0)
    {
        if(strncmp(msg, " ", 1)==0)
            msg++;
        
        if(times != 1 && strncmp(msg + COLUMNS - WIDHT_SPACE - 5, " ", 1) && strncmp(msg + COLUMNS - WIDHT_SPACE - 4, " ", 1))
            flag = 1;
        else
            flag = 0;
        
        if(!is_sender)
            gui_print_n_times(" ", WIDHT_SPACE);
        printf("| %-*.*s", COLUMNS-WIDHT_SPACE-4-flag, COLUMNS-WIDHT_SPACE-4-flag, msg);
        if(flag)
            printf("-");
        printf(" |\n");
        msg = msg + (COLUMNS - WIDHT_SPACE - 4 - flag);
        times--;
    }

    gui_print_horizontal_msg_line(is_sender);
    printf("\n");
}

void gui_print_message(Message* msg, bool is_sender){
    gui_print_user_msg(msg->user, is_sender);
    
    gui_print_msg(msg->text, is_sender);

    gui_set_color(Color_Off);
}

void gui_clear_Screen()
{
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J\r";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void gui_print_line(char* line)
{
    gui_set_color(Color_Off);

    printf("%*s\r| ", COLUMNS, "|");

    printf("%-*.*s\n", COLUMNS-4, COLUMNS-4, line);
        
    gui_set_color(Color_Off);
}

void gui_print_menu(char* user){
    char tmp[COLUMNS];

    gui_clear_Screen();

    gui_print_horizontal_line();

    sprintf(tmp, "%sWelcome %s%s", BIWhite, Cyan, user);
    gui_print_line(tmp);

    gui_print_line(" ");
    gui_print_line("Make your choice, insert:");

    sprintf(tmp, " -%s%s%s%s", BIWhite, "show_all", Color_Off, "-> show all connected users");
    gui_print_line(tmp);

    sprintf(tmp, " -%s%s%s%s", BIWhite, "username", Color_Off, "-> open the chat with the user \"username\"");
    gui_print_line(tmp);

    gui_print_line("");

    gui_print_horizontal_line();

    printf("\nInsert-> ");
    fflush(stdout);
}

void gui_print_list_users_header()
{  
    char tmp[COLUMNS];

    gui_clear_Screen();

    gui_print_horizontal_line();

    sprintf(tmp, "%sList of all connected user", BIWhite);
    gui_print_line(tmp);

    gui_print_line(" ");

    fflush(stdout);
}

void gui_print_list_users_footer()
{  
    gui_print_line(" ");
    gui_print_horizontal_line();

    printf("\nInsert-> ");

    fflush(stdout);
}

void gui_print_list_user(char* user)
{
    char tmp[COLUMNS];
    sprintf(tmp, " ~ %s%s", ICyan, user);
    gui_print_line(tmp);
}