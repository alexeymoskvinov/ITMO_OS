#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "wrappers.h"
#include <iostream>
#include <string>
#include <vector>

void parse(std::vector<char *> &strs, char str[]) {
    char *substr = strtok(str, " ");
    while (substr) {
        strs.push_back(substr);
        substr = strtok(NULL, " ");
    }
}

int main(int argc, char *argv[]) {
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);

    Bind(server, (struct sockaddr *)&adr, sizeof(adr));

    Listen(server, 5);

    socklen_t adrlen = sizeof(adr);
    int sock = Accept(server, (struct sockaddr *)&adr, &adrlen);

    char buf[256];

    read(sock, buf, 256);
    std::vector<char *> strs;
    parse(strs, buf);
    strs.push_back(NULL);
    std::cout << "Parent: "<< getuid() << '\n';
    pid_t pr = fork();
    if (pr == 0) {
        uid_t uid = std::stoll(strs.front());
        char **args = &strs[1];
        setuid(uid);
        std::cout << "Child: "<< getuid() << '\n';
        execv(args[0], args);
        exit(0);
    }

    close(sock);
    close(server);
    return 0;
}