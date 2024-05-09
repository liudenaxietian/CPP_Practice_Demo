#include <stdio.h>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <winsock.h>
#include <psdk_inc/_wsadata.h>
#pragma comment(lib, "ws2_32.lib") // 加载 ws2_32.dll

#define BUF_SIZE 100

struct Message
{
    std::string topic;
    std::string content;
};

class Subscriber
{
public:
    Subscriber(const std::string &name) : name_(name){};

    void recvMessage(const Message &msg)
    {
        std::cout << "name: " << name_ << " recv message topic: " << msg.topic << " message content: " << msg.content << std::endl;
    }

private:
    std::string name_;
};

class MessageRouter
{
public:
    void subscribe(Subscriber *sub, const std::string &topic)
    {
        subscribers_[topic].emplace_back(sub);
    }

    void publish(const Message &message)
    {

        // 方式一:

        // for (auto &topic : subscribers_)
        // {
        //     if (topic.first == message.topic)
        //     {
        //         for (auto sub : topic.second)
        //         {
        //             sub->recvMessage(message);
        //         }
        //     }
        // }

        // 方式二
        const std::string &topic = message.topic;
        if (subscribers_.find(topic) != subscribers_.end())
        {
            for (auto &sub : subscribers_[topic])
            {
                sub->recvMessage(message);
            }
        }
    }

private:
    std::unordered_map<std::string, std::vector<Subscriber *>> subscribers_;
};

int main()
{

    MessageRouter router;

    Subscriber subscriber1("Subscriber 1");
    Subscriber subscriber2("Subscriber 2");
    Subscriber subscriber3("Subscriber 3");

    router.subscribe(&subscriber1, "news");
    router.subscribe(&subscriber2, "sport");
    router.subscribe(&subscriber3, "news");

    // const Message &msg = {"news", "this is a news"};

    // router.publish(msg);

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in sockAddr;

    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = PF_INET;                     // 使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // 具体的IP地址
    sockAddr.sin_port = htons(1234);                   // 端口
    bind(servSock, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

    listen(servSock, 20);

    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    char buffer[BUF_SIZE] = {0}; // 缓冲区
    while (1)
    {
        SOCKET clntSock = accept(servSock, (SOCKADDR *)&clntAddr, &nSize);
        int strLen = recv(clntSock, buffer, BUF_SIZE, 0); // 接收客户端发来的数据
        if(strLen < 0){
            continue;
        }

        //处理消息 
        std::string  messageContent(buffer,strLen);
        std::string messageTopic = "unknown";


        //解析消息,假设消息内容为"topic":"content"
        std::size_t separatorPos = messageContent.find(":");

        if(separatorPos != std::string::npos){
            messageTopic = messageContent.substr(0,separatorPos);
            messageContent = messageContent.substr(separatorPos+1);
        }

        Message message ={messageTopic,messageContent};

        router.publish(message);

        std::cout<<"Received TCP message: " << messageContent << " from " <<inet_ntoa(clntAddr.sin_addr) << " : " <<ntohs(clntAddr.sin_port)<<std::endl; 

        // send(clntSock, buffer, strLen, 0);                // 将数据原样返回
        // closesocket(clntSock);                            // 关闭套接字
        // memset(buffer, 0, BUF_SIZE);                      // 重置缓冲区
    }

    // 关闭套接字
    closesocket(servSock);
    // 终止 DLL 的使用
    WSACleanup();
    return 0;
}