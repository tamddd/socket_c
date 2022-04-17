#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


int main(){
  int sock0;
  struct sockaddr_in addr;
  struct sockaddr_in client;
  socklen_t len;
  int sock1, sock2;

  //受信ソケットの作成
  sock0 = socket(AF_INET, SOCK_STREAM, 0);

  //ソケットの設定
  addr.sin_family = AF_INET;
  //ポート番号は8888
  addr.sin_port = htons(8888);
  addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_len = sizeof(addr);

  //接続を受け付けるIPアドレスを設定している。
  //ソケットをポートに関連付け
  //指定されたポート番号（ここでは８８８８番）で接続要求を待つ
  bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

  //接続要求待ちにする
  listen(sock0, 5);

  //クライアントからの接続要求の受け付け
  len = sizeof(client);
  //acceptがTCP接続から新たなソケットを作成
  sock1 = accept(sock0, (struct sockaddr *)&client, &len);
  //HELLOを送信
  write(sock1, "HELLO", 6);
  //sock1(クライアント) 接続終了
  close(sock1);

  //accept
  len = sizeof(client);
  sock2 = accept(sock0, (struct sockaddr *)&client, &len);
  //5文字送信
  write(sock2, "HOGE", 5);

  //sock2（クライアント） 接続終了
  close(sock2);

  //sock0（クライアント） 接続終了
  close(sock0);

  return 0;
}
