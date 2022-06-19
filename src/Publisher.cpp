// Publisher implementation

#include "Publisher.h"

Publisher::Publisher(Channel* _channel) : channel(_channel) {
    messageSent = new Types::Message;
}

Publisher::~Publisher() {
    if(messageSent != NULL) {
        delete messageSent;
    }
}

void Publisher::publishMessage(const string payload, const string topic) {
    memcpy(&(messageSent->payload[0]), &payload[0], payload.size());
    messageSent->payload[payload.size()] = '\0';
    memcpy(&(messageSent->topic[0]), &topic[0], topic.size());
    messageSent->topic[topic.size()] = '\0';
    insertTime();

    channel->getMessage(messageSent);
}

void Publisher::insertTime() const {
    time_t now = time(0);
    struct tm tstruct;
    tstruct = *localtime(&now);
    messageSent->time.Year = tstruct.tm_year+1900;
    messageSent->time.Month = tstruct.tm_mon+1;
    messageSent->time.Day = tstruct.tm_mday;
    messageSent->time.Hour = tstruct.tm_hour;
    messageSent->time.Minute = tstruct.tm_min;
    messageSent->time.Second = tstruct.tm_sec;
}