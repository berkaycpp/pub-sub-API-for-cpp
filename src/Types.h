#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <algorithm>
#include <bits/stdc++.h>
#include "./../config.h"

#pragma pack(1)

namespace Types {

typedef struct Time {
    uint16_t Year;
    uint8_t Month;
    uint8_t Day;
    uint8_t Hour;
    uint8_t Minute;
    uint8_t Second;
}Time;

typedef struct Message {
    char topic[MAX_TOPIC_SIZE_IN_CHAR];
    Time time;
    char payload[MAX_PAYLOAD_SIZE_IN_CHAR];
}Message;

class CircularMessageBuffer {
    public:
        CircularMessageBuffer(uint32_t capacity) : currentIndex(0), size(0), capacity(capacity) {
            messagePtr = new Message[capacity];
        }
        ~CircularMessageBuffer() {
            delete [] messagePtr;
        }
        
        void writeMessage(const Message& _message) {
            memcpy(messagePtr+(1*currentIndex), &_message, sizeof(Message));
            currentIndex++;
            size++;
            if(currentIndex == capacity) {
                currentIndex == 0;
            }
        }
        Message readLastMessage() const {
            return (Message)(*(messagePtr+sizeof(Message)*(currentIndex-1)));
        }
        void printLastMessage() const {
            auto* it = messagePtr+sizeof(Message)*(currentIndex-1);
            printf("Message = %s, Time = %d/%d/%d - %d/%d/%d, Topic = %s\n",
                it->payload, it->time.Day, it->time.Month, it->time.Year, it->time.Hour, it->time.Minute, it->time.Second, it->topic);
        }
        void clearBuffer() {
            size = currentIndex = 0;
        }
        void printMessages() {
            if(size != capacity) {
                for(auto it = messagePtr; it != messagePtr+sizeof(Message)*(currentIndex); it=it+sizeof(Message)) {
                    printf("Message = %s, Time = %d/%d/%d - %d/%d/%d, Topic = %s\n",
                        it->payload, it->time.Day, it->time.Month, it->time.Year, it->time.Hour, it->time.Minute, it->time.Second, it->topic);
                }
            }
            else {
                for(auto it = messagePtr+sizeof(Message)*currentIndex; it != messagePtr+sizeof(Message)*(capacity+1); it=it+sizeof(Message)) {
                    printf("Message = %s, Time = %d/%d/%d - %d/%d/%d, Topic = %s\n",
                        it->payload, it->time.Day, it->time.Month, it->time.Year, it->time.Hour, it->time.Minute, it->time.Second, it->topic);
                }
                for(auto it = messagePtr; it != messagePtr+sizeof(Message)*currentIndex; it=it+sizeof(Message)) {
                    printf("Message = %s, Time = %d/%d/%d - %d/%d/%d, Topic = %s\n",
                        it->payload, it->time.Day, it->time.Month, it->time.Year, it->time.Hour, it->time.Minute, it->time.Second, it->topic);
                }
            }
        }

    private:
        uint32_t getSize() const {
            return size;
        }
        uint32_t getCapacity() const {
            return capacity;
        }

        uint32_t currentIndex; // where the next message received will be saved.
        uint32_t size, capacity;
        Message* messagePtr;
};

}

#endif