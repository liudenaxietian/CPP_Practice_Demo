#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

struct message
{
    string topic;
    string content;
};

class subScriber
{
public:
    subScriber(string name) : name_(name){};
    void subscriber(string topic)
    {
        subScribers_.push_back(topic);
    }

    void recvMsg(const string &msg)
    {
        cout << "subscriber:" << name_ << " recv message:" << msg << endl;
    }
    const string &getName() const
    {
        return name_;
    }

    const vector<string> &getsubscribers()
    {
        return subScribers_;
    }

private:
    string name_;
    vector<string> subScribers_;
};

class Publisher
{
public:
    void registe(subScriber *sub)
    {
        subscribers_.push_back(sub);
    }

    void publish(const message &msg)
    {
        for (auto &sub : subscribers_)
        {
            for (auto topic : sub->getsubscribers())
            {
                if (topic == msg.topic)
                {
                    sub->recvMsg(msg.content);
                }
            }
        }
    }

private:
    vector<subScriber *> subscribers_;
};


int main(){

    subScriber s1("subscriber1");
    subScriber s2("subscriber2");
    subScriber s3("subscriber3");
    s1.subscriber("baskball");
    s2.subscriber("pingpong");
    s3.subscriber("baskball");

    Publisher pub;
    pub.registe(&s1);
    pub.registe(&s2);
    pub.registe(&s3);

    message msg{"baskball","sljdflaskdf"};

    pub.publish(msg);

    return 0;    
}