/*
 * GuiConnectionManager.h
 *
 *  Created on: Jun 22, 2016
 *      Author: colman
 */

#ifndef GUICONNECTIONMANAGER_H_
#define GUICONNECTIONMANAGER_H_

#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<sys/socket.h>
#include<netdb.h>
#include <arpa/inet.h>

using namespace std;


class GuiConnectionManager
{
private:
    int sock;
    std::string address;
    int port;
    struct sockaddr_in server;

public:
    GuiConnectionManager();
    bool conn(string, int);
    bool send_data(string data);
    string receive(int);
};




#endif /* GUICONNECTIONMANAGER_H_ */
