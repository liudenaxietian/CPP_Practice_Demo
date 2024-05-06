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
    const string& getName()const {
        return name_;
    }
private:
    string name_;
    vector<string> subScribers_;
};
