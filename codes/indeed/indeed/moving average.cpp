//
//  moving average.cpp
//  
//
//  Created by BlairWu on 30/01/2018.
//

#include <stdio.h>
#include <queue>

/*class Event{
    int val;
    int ts;
    
    Event(int v){
        this->val = v;
        this->ts = getNow();
    }
}*/

struct Event{
    int val;
    int ts;
    Event(int v, int t) : val(v), ts(t) {}
};

class movingAvg{
private:
    queue<Event> storage;
    int sum = 0;
    
    bool isExp(Event e, int curTime){
        return curTime - e.ts >= 5;
    }
    
    void removeExp(){
        while (!storage.empty() && isExp(storage.top(), getNow())) {
            sum -= storage.top().val;
            storage.pop();
        }
    }
public:
    void record(int val){
        Event e = Event(val, getNow());
        storage.push(e);
        sum += val;
        removeExp();
    }
    
    double getAvg(){
        removeExp();
        if(storage.empty())
            return 0;
        else
            return (double) sum / storage.size();
    }
};
