#include "udpsocket.hpp"
#include <sstream>

int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        std::cerr << "./udp_srv 192.168.80.128 9000\n";
        return -1;
    }
	//用ip和port来接收cin输入的ip和port
    uint16_t port;
    std::string ip = argv[1];
    std::stringstream tmp;
    tmp << argv[2];
    tmp >> port;

    UdpSocket sock;
    CHECK_RET(sock.Socket());
    CHECK_RET(sock.Bind(ip, port));

    while(1) {
        std::string buf;
        std::string peer_ip;
        uint16_t peer_port;
        sock.Recv(buf, peer_ip, peer_port);//Recv中的buf，ip和port都是输出参数，故定义三个变量来接受
											//表示从哪个ip的哪个端口发送到的数据，存到buf中
        std::cout << "client-["<<peer_ip<<":"<<peer_port<<"] say:"
            <<buf<<std::endl;

        buf.clear();
        std::cin >> buf;
        sock.Send(buf, peer_ip, peer_port);//将buf中的数据通过socket对应的结构体发送到peer_ip主机的peer_port端口
    }
    sock.Close();
}

