#include <unistd.h>
#include <sys/types.h> /* basic system data types */
#include <sys/socket.h> /* basic socket definitions */
#include <netinet/in.h> /* sockaddr_in{} and other Internet defns */
#include <arpa/inet.h> /* inet(3) functions */
#include <netdb.h> /*gethostbyname function */
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#define MAXLINE 1024
void handle(int connfd);
int main(int argc, char **argv)
{
    printf("client start:%s\n","sswsss");
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(server_addr.sin_zero),8);
    
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket error");
        return 1;
    }
    char recv_msg[1024];
    char reply_msg[1024];
    
    if (connect(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))==0) {
        //connect 成功之后，其实系统将你创建的socket绑定到一个系统分配的端口上，且其为全相关，包含服务器端的信息，可以用来和服务器端进行通信。
        while (1) {
            bzero(recv_msg, 1024);
            bzero(reply_msg, 1024);
            long byte_num = recv(server_socket,recv_msg,1024,0);
            if(byte_num>0)
            {
                recv_msg[byte_num] = '\0';
                printf("server said:%s\n",recv_msg);
            }
            //scanf("%s",reply_msg);
            //if (send(server_socket, reply_msg, 1024, 0) == -1) {
            if (send(server_socket, "测试程序发送的测试消息！", 1024, 0) == -1) {
                perror("send error");
                break;
            }
            
            sleep(2);
        }
    }
    return 0;
}
