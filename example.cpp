#include "SignalSlot.h"

#include <iostream>
#include <string>

using namespace std;

class CallbackClass {
    public:
    CallbackClass() {}
    ~CallbackClass() {}
    
    void CallbackMethod(std::string text) {cout << "Callback says: " << text << " !" << endl;}
    void SlotMethod0(int i, std::string text) {cout << "Slot0: Signal " << i << " says: " << text << " !" << endl;}
    void SlotMethod1(int i, std::string text) {cout << "Slot1: Signal " << i << " says: " << text << " !" << endl;}
};

CallbackClass callbackClass;
MethodCallback<CallbackClass, void, string> myCallback(callbackClass, &CallbackClass::CallbackMethod);

Signal<3, int, string> mySignal;
MethodSlot<CallbackClass, int, string> mySlot0(callbackClass, &CallbackClass::SlotMethod0);
MethodSlot<CallbackClass, int, string> mySlot1(callbackClass, &CallbackClass::SlotMethod1);

int main()
{
    myCallback("Hello");
	
    mySignal.Connect(&mySlot0);
    mySignal.Connect(&mySlot1);
    
    mySignal.Emit(1, "Goodbye");
    
    return 0;
}
