#include <stdio.h>   
#include <netdb.h>   
#include <stdlib.h>   
#include <arpa/inet.h>

int main(int argc, char *argv[])
{   
    if(argc == 1)   {   
        printf("USAGE: getip <server name>\nFor example:\n    getip www.google.com\n");   
        exit(1);   
    }   

    struct addrinfo *res;   
    int succ = getaddrinfo(argv[1], NULL, NULL, &res);   
    if(succ != 0) {   
        printf("Can't get address info! error code = %d", succ);   
        exit(succ);   
    }   
    
    struct sockaddr_in *sinp;   
    const char *addr;   
    char abuf[INET_ADDRSTRLEN];   

    struct addrinfo *pt = res;   
    for(pt = res; pt != NULL; pt = pt->ai_next){   
        sinp = (struct sockaddr_in *)pt->ai_addr;   
        addr = (const char *)inet_ntop(AF_INET, &sinp->sin_addr, abuf, INET_ADDRSTRLEN);   
        printf("IP = %s\n", addr);   
    }   

    return 0;
} 
