/*
main code to test
(while compiling , do not forget to add "-lpthread" parameter)
----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------------------------------------------

********************author: Berkay Şahin********************

*/

#include "pubsub.h"
#include <string>
#include <bits/stdc++.h>
#include <iostream>
#include <thread>

int main() {
     // firstly channel must be created to assign publishers and subscribers
    Channel* _channel = new Channel();
    Publisher* _publishers[3];
    Subscriber* _subscribers[10];

    // the topic pool
    vector<string> topics = {"ABC", "XYZ", "QWE", "Blue", "Red", "Orange", "Yellow", "Car", "Dog", "Tree", "Sun", "House"};

    // topics that will be sent to publisher messages
    vector<string> initialTopics;
    
    // publisher initialization
    for(int i=0; i<3; i++) {
        _publishers[i] = new Publisher(_channel);
    }
    
    // topics are randomly set to be assigned subscribers
    for(int i=0; i<10; i++) {
        initialTopics.push_back(topics[(i+10)%3]);
        initialTopics.push_back(topics[(i+10)%4]);
        initialTopics.push_back(topics[(i+10)%6]);
        initialTopics.push_back(topics[(i+10)%8]);
        _subscribers[i] = new Subscriber(_channel, initialTopics);
        initialTopics.clear();
    }

    std::thread threadObj1a(publishThread, _publishers[0], "Hello!", topics[0]);
    std::thread threadObj2a(publishThread, _publishers[1], "Good n8.", topics[1]);
    std::thread threadObj3a(publishThread, _publishers[2], "--.--...", topics[2]);
    /*
    std::thread threadObj4a(publishThread, _publishers[0], "How are you?", topics[3]);
    std::thread threadObj5a(publishThread, _publishers[1], "20 times z zzzzzzzzzzzzzzzzzzzz", topics[4]);
    std::thread threadObj6a(publishThread, _publishers[2], "ESEN", topics[5]);
    std::thread threadObj7a(publishThread, _publishers[2], "123456789 987654321", topics[6]);
    std::thread threadObj8a(publishThread, _publishers[2], "xyz", topics[7]);
    std::thread threadObj9a(publishThread, _publishers[1], "abcdef", topics[8]);
    std::thread threadObj10a(publishThread, _publishers[0], "147852369", topics[9]);
    */
    std::thread threadObj11a(publishThread, _publishers[1], "+-+-+-+", topics[10]);
    std::thread threadObj12a(publishThread, _publishers[1], ":D", topics[11]);

    threadObj1a.join();
    threadObj2a.join();
    threadObj3a.join();
    /*
    threadObj4a.join();
    threadObj5a.join();
    threadObj6a.join();
    threadObj7a.join();
    threadObj8a.join();
    threadObj9a.join();
    threadObj10a.join();
    */
    threadObj11a.join();
    threadObj12a.join();

    _subscribers[0]->subscribeTopic(topics[3]);
    _subscribers[1]->subscribeTopic(topics[3]);
    _subscribers[2]->subscribeTopic(topics[3]);
    _subscribers[3]->subscribeTopic(topics[3]);
    _subscribers[4]->subscribeTopic(topics[3]);
    _subscribers[5]->subscribeTopic(topics[3]);
    _subscribers[6]->subscribeTopic(topics[3]);
    _subscribers[7]->subscribeTopic(topics[3]);

/*
    std::thread threadObj1b(publishThread, _publishers[2], "Hello!", topics[3]);
    std::thread threadObj2b(publishThread, _publishers[1], "Good n8.", topics[2]);
    std::thread threadObj3b(publishThread, _publishers[0], "--.--...", topics[1]);
    std::thread threadObj4b(publishThread, _publishers[0], "How are you?", topics[6]);
*/
    std::thread threadObj5b(publishThread, _publishers[0], "20 times z zzzzzzzzzzzzzzzzzzzz", topics[7]);
    std::thread threadObj6b(publishThread, _publishers[1], "ESEN", topics[8]);
    std::thread threadObj7b(publishThread, _publishers[1], "123456789 987654321", topics[9]);
    std::thread threadObj8b(publishThread, _publishers[2], "xyz", topics[10]);
    std::thread threadObj9b(publishThread, _publishers[0], "abcdef", topics[4]);
/*
    std::thread threadObj10b(publishThread, _publishers[1], "147852369", topics[5]);
    std::thread threadObj11b(publishThread, _publishers[0], "+-+-+-+", topics[11]);
    std::thread threadObj12b(publishThread, _publishers[2], ":D", topics[10]);
*/

/*   
    threadObj1b.join();
    threadObj2b.join();
    threadObj3b.join();
    threadObj4b.join();
*/
    threadObj5b.join();
    threadObj6b.join();
    threadObj7b.join();
    threadObj8b.join();
    threadObj9b.join();
/*
    threadObj10b.join();
    threadObj11b.join();
    threadObj12b.join();
*/

    _subscribers[0]->printAllMessages();

    // expected outputs can be compared with actual outputs as a test result

    // channel must be deleted at the end, but this restriction can be removed
    for(int i=0; i<10; i++) {
        delete _subscribers[i];
    }
     for(int i=0; i<3; i++) {
        delete _publishers[i];
    }
    delete _channel;

    return 0;
}