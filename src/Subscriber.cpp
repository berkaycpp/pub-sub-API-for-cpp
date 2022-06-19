// Subscriber implementation

#include "Subscriber.h"

Subscriber::Subscriber() {
    messages = new Types::CircularMessageBuffer(MAX_SAVED_MESSAGE_COUNT);

#if TEST_FLAG
    printf("Subscriber is created.");
#endif
}

Subscriber::Subscriber(Channel* _channel,  const vector<string> _initialTopics) {
    vector<string> initialTopics(_initialTopics);
    sort(initialTopics.begin(), initialTopics.end());
    initialTopics.erase(unique(initialTopics.begin(), initialTopics.end() ), initialTopics.end());
    for(auto it = begin(initialTopics); it != end(initialTopics); it++) {
        subscribedTopics.push_back(*it);
    }
    this->channel = _channel;
    this->ID = channel->attach(this);
    messages = new Types::CircularMessageBuffer(MAX_SAVED_MESSAGE_COUNT);

#if TEST_FLAG
    printf("Subscriber %d is created.\n", ID);
#endif
}

Subscriber::Subscriber(Channel* _channel, const string _initialTopics) {
    subscribedTopics.push_back(_initialTopics);
    this->channel = _channel;
    this->ID = channel->attach(this);
    messages = new Types::CircularMessageBuffer(MAX_SAVED_MESSAGE_COUNT);

#if TEST_FLAG
    printf("Subscriber %d is created.", ID);
#endif
}

Subscriber::~Subscriber() {
    subscribedTopics.clear();
    bool tempFlag = channel->detach(this);
    delete messages;

#if TEST_FLAG
    if(tempFlag) {
        printf("Detachment successfull for %d.\n", ID);
    }
    else {
        printf("Detachment unsuccessfull for %d\n.", ID);
    }
#endif
}

bool Subscriber::subscribeTopic(const string _topic) {
    subscribedTopics.push_back(_topic);
    
#if TEST_FLAG
    printf("Subscriber %d subscribed topic '%s'.\n", ID, _topic.c_str());
#endif

    return true;
}

bool Subscriber::subscribeTopic(const vector<string> _topics) {
    for(auto it = begin(_topics); it != end(_topics); it++) {
        subscribedTopics.push_back(*it);
    }

#if TEST_FLAG
    for(auto it = begin(_topics); it != end(_topics); it++) {
        printf("Subscriber %d subscribed topic '%s'.\n", ID, (*it).c_str());
    }
#endif

    return true;
}

bool Subscriber::connectNetwork(Channel* _channel) {
    this->channel = _channel;
    this->ID = channel->attach(this);

#if TEST_FLAG
    printf("Subscriber %d connected the channel.", ID);
#endif

    return true;
} 

int Subscriber::getID() const {
    return ID;

#if TEST_FLAG
    printf("Subscriber ID = %d", ID);
#endif
}

void Subscriber::newMessage(const Types::Message& _message) {
    messages->writeMessage(_message);

    printf("Subscriber %d got a message from the topic: %s \nat: %d/%d/%d - %d/%d/%d \nMessage: %s\n",
        ID, _message.topic, _message.time.Day,  _message.time.Month,  _message.time.Year,
        _message.time.Hour,  _message.time.Minute,  _message.time.Second,  _message.payload);
}

void Subscriber::printSubscribedTopics() const {
    for(auto it = begin(subscribedTopics); it != end(subscribedTopics); it++) {
        printf("Subscriber %d has subscribed topic '%s'.\n", ID, (*it).c_str());
    }
}

void Subscriber::printSavedMessages() const {
    printf("Subscriber %d:\n", ID);
    messages->printMessages();
}

void Subscriber::printLastReceived() const {
    printf("Subscriber %d:\n", ID);
    messages->printLastMessage();
}

void Subscriber::clearMessages() {
    messages->clearBuffer();
}

bool Subscriber::haveTopic(const string topic) {
    if (std::find(subscribedTopics.begin(), subscribedTopics.end(), topic) != subscribedTopics.end()) {
        return true;
    }
    else {
        return false;
    }
}