/* Subscriber class
Subscriber class. Subscriber class can inherit ISubscriber interface,
and Publisher class can inherit IPublisher interface, and the connection 
can be build over these interfaces utilizing Bridge pattern, but in that
step, there is no need to use.

Subsribers firstly created with a channel and topic. For the connection
of subscribers to the network of the channel, they must have unique ID
assigned by channel. The network has only one channel that regulates
the process. Subscribers only takes the messages having subscribed topic. 

********************author: Berkay Şahin********************

*/

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <vector>
#include <memory>
#include "Types.h"
#include "Channel.h"
#include "./../config.h"

using namespace std;

class Channel; 

class Subscriber {

    public:
        Subscriber();
        explicit Subscriber(Channel* _channel, const vector<string> _initialTopics);
        explicit Subscriber(Channel* _channel, const string _initialTopics);
        virtual ~Subscriber();

        bool subscribeTopic(const string _topic);
        bool subscribeTopic(const vector<string> _topics);
        // both types are OK for subscription

        int getID() const;
        bool connectNetwork(Channel* _channel); 
        void newMessage(const Types::Message& _message);
        void printSubscribedTopics() const;
        void printSavedMessages() const; // they need to be printed from the earliest to newest.
        void printLastReceived() const;
        void clearMessages();
        bool haveTopic(const string topic);
        void printAllMessages() const;

        vector<string> subscribedTopics;

        // test functions
#if TEST_FLAG 

#endif 

    private:
        Channel* channel = NULL;
        int ID = 0; // 0 ID means no assigned ID yet or there is not an existing network connection.
        Types::CircularMessageBuffer* messages;

};

#endif