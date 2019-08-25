#include <iostream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define CHECK_RET(q) if((q)==false){return -1;}

class UdpSocket{
    private:
        int _sockfd;
    public: 
        bool Socket() {
            //int socket(int domain, int type, int protocol);
            _sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
            if (_sockfd < 0) {
                std::cerr << "socket error\n";
                return false;
            }
            return true;
        }
        bool Bind(const std::string &ip, const uint16_t port) {
            //bind(int sockfd, struct sockaddr *addr,socklen_t addrlen)
            struct sockaddr_in addr;
            addr.sin_family = AF_INET;
            //uint16_t htons(uint16_t hostshort);
            //将主机字节序的16位数据，转换位网络字节序数据返回
            addr.sin_port = htons(9000);
            //192.168.122.132 -> 0xc0a87a84
            //in_addr_t inet_addr(const char *cp);
            //将点分十进制字符串IP地址转换为网络字节序IP地址
            addr.sin_addr.s_addr = inet_addr(ip.c_str());
            int ret;//返回值，仅仅用来判断bind是否成功
            socklen_t len = sizeof(struct sockaddr_in);
            ret = bind(_sockfd, (struct sockaddr*)&addr, len);
            if (ret < 0) {
                std::cerr << "bind error\n";
                return false;
            }
            return true;
        }
        bool Send(const std::string &data, const std::string &peer_ip, const uint16_t peer_port) 
									//给对端peer_ip的peer_port端口发送data数据
		{
            //ssize_t sendto(int sockfd, const void *buf, size_t len, 
            //int flags,struct sockaddr *dest_addr, socklen_t addrlen);
            struct sockaddr_in addr;//定义一个结构体struct sockaddr_in addr，
									//然后用要发送到的对端ip地址和对端ip地址中的port端口号
									//分别对addr.sin_family，addr.sin_port，addr.sin_addr.s_addr进行赋值
            addr.sin_family = AF_INET;
            addr.sin_port = htons(peer_port);
            addr.sin_addr.s_addr = inet_addr(peer_ip.c_str());
            socklen_t len = sizeof(struct sockaddr_in);
            int ret = sendto(_sockfd, &data[0], data.size(), 0, (struct sockaddr*) &addr, len);
													//通过_sockfd对应的socket结构体中的源ip的源端口
													//将data中data.size()长度的数据发送到对端地址(struct sockaddr*) &addr
													//对端是以(struct sockaddr*) &addr为地址的主机
													//通过最后一个参数len和地址类型struct sockaddr_in addr
													//可以判断出目的ip地址和目的port端口
													//就完成了数据从源ip地址的port端口到目的端ip地址的port端口的发送
            if (ret < 0) {
                std::cerr << "sendto error\n";
                return false;
            }
            return true;
        }
        bool Recv(std::string &buf, std::string &peer_ip, uint16_t &peer_port)
											//Recv中参数均为输出参数
											//定义一个结构体struct sockaddr_in peer_addr来接收该数据是从哪个ip地址的哪个port端口发送过来的
		{
            //ssize_t recvfrom(int sockfd, void *buf, size_t len, 
            //int flags,struct sockaddr *src_addr, socklen_t *addrlen)
            //成功：返回实际接收的数据长度 ， 失败：-1
            struct sockaddr_in peer_addr;//定义一个结构体struct sockaddr_in peer_addr来接收该数据是从哪个ip地址的哪个port端口发送过来的
            socklen_t len = sizeof(struct sockaddr_in);
            char tmp[4096] = {0};
            int ret = recvfrom(_sockfd, tmp, 4096, 0, (struct sockaddr*)&peer_addr, &len);
											//从_sockfd中对应的socket结构体的接收队列中，取出一条数据放到tmp中，
											//然后保存发送端的地址到参数[结构体(struct sockaddr*)&peer_addr]中
											//通过对(struct sockaddr*)&peer_addr对端（发送端）地址的解析
											//对三个参数进行输出
											//将对端地址peer_ip和对端端口号peer_port赋值
											//将tmp中的数据放入到buf中
            if (ret < 0) {
                std::cerr << "recvfrom error\n";
                return false;
            }
            //char *inet_ntoa(struct in_addr in);
            //将网络字节序IP地址转换为点分十进制字符串IP地址
            //uint16_t ntohs(uint16_t netshort);
            //将网络字节序的16位数据转换为主机字节序数据
            peer_ip = inet_ntoa(peer_addr.sin_addr);
            peer_port = ntohs(peer_addr.sin_port);
            buf.assign(tmp, ret);
            return true;
        }
        void Close() {
            close(_sockfd);
        }
};
