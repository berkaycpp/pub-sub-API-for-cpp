#ifndef PUBSUB_H
#define PUBSUB_H

#include "src/Publisher.h"
#include "src/Channel.h"
#include "src/Subscriber.h"

// function for calling publish functions by user while threading
void  publishThread(Publisher* pubPtr, string payload, string topic)
{
    pubPtr->publishMessage(payload, topic);
}

#endif

