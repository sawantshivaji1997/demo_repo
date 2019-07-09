#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<string.h>
#include<iostream>
#include"addressbook.pb.h"
#define PORT 8080
using namespace std;
void PromptForAddress(tutorial::Person* person){

    cout<<"Enter name: ";
    getline(cin,*person->mutable_name());

    cout<<"Enter email address";
    string email;
    getline(cin,email);
    if(!email.empty())
    {
        person->set_email(email);
    }
}


int main()
{
    int sock=0 ,valread;
    struct sockaddr_in serv_addr;
    char buffer[1024]={0};

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);

    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0)
    {
        printf("Invalid address / Address not supported\n");
    }
    if(connect(sock,(struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
    {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Connection established\n");
    }

    tutorial::AddressBook address_book;
    string msg;
    PromptForAddress(address_book.add_people());
    if(!address_book.SerializeToString(&msg))
    {
        cerr<<"failed to serializz the data";
        return -1;
    }
    send(sock,msg.c_str(),strlen(msg.c_str()),0);

    return 0;
}
