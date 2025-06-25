#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 4412
#define BUFFER_SIZE 1024

// 线程参数结构
typedef struct {
  int client_sock;
} thread_args_t;

// 接收消息并广播到所有客户端的线程函数
void *thread_func(void *args) {
thread_args_t *thread_args = (thread_args_t *)args;
  int client_sock = thread_args->client_sock;
  char buffer[BUFFER_SIZE];
  int bytes_received;

  while ((bytes_received = recv(client_sock, buffer, BUFFER_SIZE, 0)) > 0) {
    // 将消息广播到所有连接的客户端
    //fputc(bytes_received,stdout);
    
  }

  // 关闭连接套接字
  close(client_sock);
  free(thread_args);
  pthread_exit(NULL);
}

int main() {
  // 创建监听套接字
  int listen_sock = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_sock == -1) {
    perror("socket");
    exit(1);
  }

  // 绑定监听套接字
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(PORT);
  if (bind(listen_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
    perror("bind");
    exit(1);
  }

  // 设置监听状态
  if (listen(listen_sock, 5) == -1) {
    perror("listen");
    exit(1);
  }

  // 循环接受连接请求
  while (1) {
    // 接受来自客户端的连接请求
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    puts("Waiting for Connect");
    int client_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &client_len);
    if (client_sock == -1) {
      perror("accept");
      continue;
    }
    puts("Connected from client");
    // 创建一个新的线程来处理该客户端
    thread_args_t *thread_args = (thread_args_t *)malloc(sizeof(thread_args_t));
    thread_args->client_sock = client_sock;
    pthread_t thread_id;
    if (pthread_create(&thread_id, NULL, thread_func, (void *)thread_args) != 0) {
      perror("pthread_create");
      close(client_sock);
      free(thread_args);
    }
  }

  // 关闭监听套接字
  close(listen_sock);

  return 0;
}
