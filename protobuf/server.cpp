#include<bits/stdc++.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<string.h>
#include"addressbook.pb.h"
#define PORT 8080
using namespace std;
int main()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt=1;
    int addrlen=sizeof(address);
    char buffer[1024]={0};

    if((server_fd=socket(AF_INET,SOCK_STREAM,0))==0)
    {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if(setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR | SO_REUSEPORT,&opt,sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_addr.s_addr=INADDR_ANY;
    address.sin_port=htons(PORT);

    if(bind(server_fd,(struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    else{
        printf("Binded\n");
    }


    if(listen(server_fd,3)<0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Listening\n");
    }

    if((new_socket=accept(server_fd,(struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Connection accepted\n");
    }
    tutorial::AddressBook address_book;
    valread=read(new_socket,buffer,1024);
    printf("%s\n",buffer);
    string str(buffer);
    address_book.ParseFromString(str);
    cout<<address_book.people_size()<<endl;
    const tutorial::Person& person=address_book.people(int(0));
    cout<<person.name()<<endl;
    cout<<person.email()<<endl;
    string count="Letter count: "+to_string(str.length());
    send(new_socket,count.c_str(),strlen(count.c_str()),0);

    return 0;
}
