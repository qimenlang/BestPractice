#include <iostream>
#include <functional>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

class EventListener {
public:
    void addListener(const function<void()>& listener) {
        listeners.push_back(listener);
    }

    void trigger() {
        for (auto& listener : listeners) {
            listener();
        }
    }

private:
    vector<function<void()>> listeners;
};

class EventSystem {
public:
    void addEventListener(const string& eventName, const function<void()>& listener) {
        if (eventListeners.count(eventName) == 0) {
            eventListeners[eventName] = new EventListener();
        }

        eventListeners[eventName]->addListener(listener);
    }

    void removeEventListener(const string& eventName, const function<void()>& listener) {
        if (eventListeners.count(eventName) == 0) {
            return;
        }

       auto listeners = eventListeners[eventName];
       std::cout<<"listeners type:"<<typeid(listeners).name()<<std::endl;
              std::cout<<listeners<<std::endl;


        // auto it = find(listeners.begin(), listeners.end(), listener);
        // if (it != listeners.end()) {
        //     listeners->erase(it);
        // }
    }

    void triggerEvent(const string& eventName) {
        if (eventListeners.count(eventName) == 0) {
            return;
        }

        eventListeners[eventName]->trigger();
    }

private:
    map<string, EventListener*> eventListeners;
};

int main() {
    EventSystem eventSystem;

    auto listener1 = []() {
        cout << "Listener 1 called" << endl;
    };

    auto listener2 = []() {
        cout << "Listener 2 called" << endl;
    };

    eventSystem.addEventListener("event1", listener1);
    eventSystem.addEventListener("event1", listener2);

    eventSystem.triggerEvent("event1"); // 输出：Listener 1 called、Listener 2 called

    // eventSystem.removeEventListener("event1", listener1);

    eventSystem.triggerEvent("event1"); // 输出：Listener 2 called

    return 0;
}
