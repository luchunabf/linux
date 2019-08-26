#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define CHECK_RET(q) if((q)==false){return -1;}

class TcpSocket
{
    private:
        int _sockfd;
    public:
        void SetFd(int fd) {
            _sockfd = fd;
        }
        int GetFd() {
            return _sockfd;
        }
        bool Socket() {
            _sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//在内核中创建套接字，就是一个struct socket结构体
																//建立进程与网卡之间的联系
																//但是返回值是int，返回的是文件描述符，只是一个套接字操作句柄
            if (_sockfd < 0) {
                std::cerr << "socket error\n";
                return false;
            }
            return true;
        }
        int str2int(const std::string &str){
            int num;
            std::stringstream tmp;
            tmp << str;
            tmp >> num;
            return num;
        }
        bool Bind(const std::string &ip, const std::string &port) {
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(str2int(port));
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            int ret = bind(_sockfd, (struct sockaddr*)&addr, len);//将_sockfd对应的socket结构体与addr地址绑定，
																  //表示该套接字的socket结构体应该处理特定ip地址中的特定port端口的数据
            if (ret < 0) {
                std::cerr << "bind error\n";
                return false;
            }
            return true;
        }
        bool Listen(const int backlog = 5) {
            //int listen(int sockfd, int backlog);
            //开始监听：通知操作系统，可以开始接收客户端的连接请求了，
            //并且完成三次握手建立连接过程
            //tcp的面向连接，有一个三次握手建立连接过程
            //backlog:客户端最大并发连接数（同一时间最多接收多少个客户端
            //新连接请求）
            int ret = listen(_sockfd, backlog);
            if (ret < 0) {
                std::cerr << "listen error\n";
                return false;
            }
            return true;
        }
        bool Connect(const std::string &srv_ip, const std::string &srv_port)//和bind参数相同，不过bind是绑定（自己）地址，connect是对端地址
		{
            //int connect(int sockfd, sockaddr *addr,socklen_t addrlen)
            //addr: 服务端地址信息
            //addrlen:  地址信息长度
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            addr.sin_port = htons(str2int(srv_port));
            addr.sin_addr.s_addr = inet_addr(srv_ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            int ret = connect(_sockfd, (struct sockaddr*)&addr, len);//想要建立与对端地址为addr的ip+端口的新连接
																	//_sockfd是创建套接字的返回句柄(int型)
																	//_sockfd这个句柄中包含了(struct sockaddr*)&addr结构体
																	//此地址是自己已经bind绑定的地址
																	//或者是由内核随机分配的地址
																	//而这里参数中的(struct sockaddr*)&addr表示的是想要建立连接的对端地址信息
            if (ret < 0) {
                std::cerr << "connect error\n";
                return false;
            }
            return true;
        }
        bool Accept(TcpSocket &clisock, std::string *ip = NULL, uint16_t *port = NULL) //注意参数
		{
            //int accept(int sockfd, sockaddr *addr, socklen_t *addrlen)
            //sockfd:   监听套接字描述符
            //addr：    客户端地址信息
            //addrlen： 地址信息长度
            //返回值：返回新建连接的socket描述符-与客户端进行数据通信
            struct sockaddr_in cliaddr;
            socklen_t len = sizeof(struct sockaddr_in);
			int newfd = accept(_sockfd, (sockaddr*)&cliaddr, &len);//新创建一个套接字来专门和这个cliaddr地址的客户端进行收发数据处理
											//参数(sockaddr*)&cliaddr是输出参数，
											//表示接下来让该_sockfd套接字与该cliaddr地址进行一对一数据收发
			if (newfd < 0) {
                std::cerr << "accept error\n";
                return false;
            }
            clisock.SetFd(newfd);//参数clisock也是一个输出参数，接收新的套接字描述符newfd
								 //保存到新类clisock中，后续操作针对clisock类就相当于操作新的套接字描述符newfd
			
			//当ip，port两个参数传空时，用accept函数中的输出参数里面的地址的ip+port进行赋值即可
            if (ip != NULL) {
                *ip = inet_ntoa(cliaddr.sin_addr);
            }
            if (port != NULL) {
                *port = ntohs(cliaddr.sin_port);
            }
            return true;
        }
        bool Send(std::string &data) {
            //ssize_t send(int sockfd, void *buf, size_t len, int flags)
            //sockfd: 套接字描述符（服务端是新建连接的socket描述符）
            //buf： 要发送的数据
            //len： 要发送的数据长度
            //flags：   0-默认阻塞发送
            //返回值： 成功-返回实际发送的数据长度；失败-返回-1
            int ret = send(_sockfd, &data[0], data.size(), 0);
            if (ret < 0) {
                std::cerr << "send error\n";
                return false;
            }
            return true;
        }
        bool Recv(std::string &buf) {
            //ssize_t recv(int sockfd, void *buf, size_t len, int flags)
            //flags:
            //  0-默认阻塞接收
            //  MSG_PEEK：从缓冲区取数据，但是数据并不从缓冲区移除
            //返回值：>0:实际接收的数据长度 ==0：连接断开   <0:错误
            char tmp[4096];
            int ret = recv(_sockfd, tmp, 4096, 0);
            if (ret < 0) {
                std::cerr << "recv error\n";
                return false;
            }else if (ret == 0) {
                std::cerr << "connect shutdown\n";
                return false;
            }
            buf.assign(tmp, ret);
            return true;
        }
        bool Close() {
            close(_sockfd);
        }
};
