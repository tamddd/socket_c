#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
  /* code */

  struct sockaddr_in server;
  int sock;
  char buf[32];
  int n;

  //ソケット作成
  sock = socket(AF_INET, SOCK_STREAM, 0);
  //サーバーの準備 (serverは構造体)
  server.sin_family = AF_INET;
  //接続先の指定　(8888番)
  server.sin_port = htons(8888);
  server.sin_len = sizeof(server);

  inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

  server.sin_len = sizeof(server);

  //サーバーに接続
  //第二引数に接続相手の情報 -> TCP接続先の指定
  if (connect(sock, (struct sockaddr *)&server, sizeof(server)) != 0){
    // 接続成功
    perror("connect!!!");
    return 1;
  }

  //データ受信
  memset(buf, 0, sizeof(buf));
  n = read(sock, buf, sizeof(buf));

  printf("%d, %s\n", n, buf);
  //sock （クライアント）　接続終了
  close(sock);

  return 0;
}
