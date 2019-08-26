#include <signal.h>
#include "tcpsocket.hpp"
#include <stdio.h>
void sigcb(int signo)
{
    printf("receive a SIGPIPE ---connect shutdown\n");
}
int main(int argc, char* argv[])
{
  if(argc!=3)
  {
    std::cerr<< "./tcp_cli ip port\n";
    return -1;
  }
  signal(SIGPIPE,sigcb);
  TcpSocket sock;
  //创建套接字
  CHECK_RET(sock.Socket());
  //客户端无需自己绑定地址
  //向服务端发起连接请求
  CHECK_RET(sock.Connect(argv[1],argv[2]));//这里的rgv[1],argv[2]是指服务端的ip/port，通过参数传递
  while(1)
  {
    //发送数据
    std::string buf;
    std::cout << "Client say: " << std::endl;
    fflush(stdout);
    std::cin >> buf;
    sock.Send(buf);
    //接收数据
    buf.clear();
    sock.Recv(buf);
    std::cout << "Serve say: "<< buf << std::endl;
  }
  //关闭套接字
  sock.Close();
  return 0;
}
