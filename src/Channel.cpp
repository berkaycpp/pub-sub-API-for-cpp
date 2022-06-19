#include "Channel.h"

Channel::Channel() {

}

Channel::~Channel() {

}

int Channel::attach(Subscriber* _sub) {
    channelMutex.lock();
    subscribers.push_back(_sub);
    int i=1;
    while(i<=MAX_ID) {
        if(std::find(subscriberIDs.begin(), subscriberIDs.end(), i) == subscriberIDs.end())
        {
            subscriberIDs.push_back(i);
            channelMutex.unlock();
            return i;
        }
        else {
            i++;
            continue;
        }
    }
    channelMutex.unlock();
    return -1;
}

bool Channel::detach(Subscriber* _sub) {
    channelMutex.lock();
    int k = 0;
    for (auto i = subscribers.begin(); i != subscribers.end(); ++i) {
        if ((*i)->getID() == _sub->getID()) {
            subscribers.erase(i);
            subscriberIDs.erase(subscriberIDs.begin() + k);
            break;
        }
        k++;
    }
    channelMutex.unlock();
    return true;
}

 void Channel::getMessage(Types::Message* message) {
    channelMutex.lock();
    for(int i=0; i<subscribers.size(); +i++) {
        if(subscribers.at(i)->haveTopic(message->topic)) {
            subscribers.at(i)->newMessage(*message);
        }
    }
    channelMutex.unlock();
 }