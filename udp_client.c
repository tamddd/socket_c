#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void){
  int sock;
  struct sockaddr_in s;
  int n;

  //udpソケットの作成
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  //ソケットの設定
  s.sin_family = AF_INET;
  s.sin_port = htons(8888);
  s.sin_len = sizeof(s);

  //宛先の設定
  n = inet_pton(AF_INET, "127.0.0.1", &s.sin_addr);
  if (n < 1){
    perror("inet_ptons");
    return 1;
  }

  //connectなしで、sendto
  n = sendto(sock, "TEST", 5,0, (struct sockaddr *)&s, sizeof(s));
  if (n < 1){
    perror("sendto");
    return 1;
  }

  close(sock);

  return 0;
}
