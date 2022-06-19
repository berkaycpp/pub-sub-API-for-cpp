/* 
Publisher class. Publisher class can inherit IPublisher interface,
and Subscriber class can inherit ISubscriber interface, and the connection 
can be build over these interfaces utilizing Bridge pattern, but in that
step, there is no need to use.

********************author: Berkay Şahin********************

*/

#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Channel.h"
#include "Types.h"
#include <string>

using namespace std;

class Channel;

class Publisher {

    public:
        Publisher(Channel* _channel);
        virtual ~Publisher();

        void publishMessage(const string payload, const string topic);

    private:
        void insertTime() const;

        Channel* channel = NULL;
        Types::Message* messageSent; // each published message is packed here, and then sent to channel.
};

#endif