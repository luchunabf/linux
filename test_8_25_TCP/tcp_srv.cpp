#include <stdio.h>
#include "tcpsocket.hpp"
#include <sys/wait.h>

void sigcb(int no)
{
  while(waitpid(-1, NULL, WNOHANG) > 0);
}

int main(int argc, char* argv[])
{
  //判断参数
  if(argc != 3)
  {
    std::cout << "./tcp_srv ip port\n";
    return -1;
  }
  signal(SIGCHLD, sigcb);
  //创建监听套接字
  TcpSocket lst_sock;
  CHECK_RET(lst_sock.Socket());
  //为监听套接字棒子地址信息
  CHECK_RET(lst_sock.Bind(argv[1], argv[2]));
  //启用监听
  CHECK_RET(lst_sock.Listen());
  while(1)
  {
    //创建新套接字来进行客户端一对一服务
    TcpSocket clisock;
    bool ret = lst_sock.Accept(clisock);//重要：用原套接字accept的参数接收到新类
    if(ret == false)
    {
      continue;
    }
    if(fork() == 0)
    {
        while(1)
        {
              
    //通过新套接字来与客户端进行收发数据
    //接收数据
    std::string buf;
    ret = clisock.Recv(buf);
    if(ret == false)
    {
      clisock.Close();
      continue;
    }

    std::cout << "Client say: " << buf << std::endl;

    
    //发送数据
    buf.clear();
    std::cout << "Serve say: ";
    fflush(stdout);
    std::cin >> buf;
    clisock.Send(buf);
        }
        clisock.Close();
    }
    clisock.Close();
  }
  //关闭套接字
  lst_sock.Close();

  return 0;
}
