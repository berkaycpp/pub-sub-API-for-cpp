/* Channel class
Channel is the regulator of the system. Each network has one channel, and
all publishers and subscribers are connected to it. It isolates the publishers
from subscribers. It has also a mutex to avoid confussion.

********************author: Berkay Şahin********************

*/

#ifndef CHANNEL_H
#define CHANNEL_H

#include "Subscriber.h"
#include "Types.h"
#include "Publisher.h"
#include <mutex>
#include "./../config.h"

using namespace std;

class Subscriber;
class Publisher;

class Channel {
    
    public:
        Channel();
        ~Channel(); 

        int attach(Subscriber* _sub); // non-positive returns mean error occured attaching process.
        bool detach(Subscriber* _sub); // true means detachment is successfull.

        void getMessage(Types::Message* message);
    
    private:
       
       vector<Subscriber*> subscribers;

       // each subscriber has unique ID, to assign ID's effectively, they are assigned from
       // the integer that is first available after 0
       vector<int> subscriberIDs; 

       // map<string, vector<int>> topicSubscribersMap; subscriber topics can be mapped to ID's for further implementations
       mutex channelMutex;
};

#endif