#include "SignalSlot.h"

#include <iostream>
#include <string>

using namespace std;

size_t MyFunction(string text)
{
    cout << "FunctionCallback says: " << text << endl;
    return text.length();
}

class CallbackClass {
public:
    void CallbackMethod(string text) {cout << "MethodCallback says: " << text << endl;}
    void SlotMethod0(int i, string text) {cout << "Slot0: Signal " << i << " says: " << text << endl;}
    void SlotMethod1(int i, string text) {cout << "Slot1: Signal " << i << " says: " << text << endl;}
};


CallbackClass callbackClass;

FunctionCallback<size_t, string> myFunctionCallback(&MyFunction);
MethodCallback<CallbackClass, void, string> myMethodCallback(callbackClass, &CallbackClass::CallbackMethod);

Signal<3, int, string> mySignal;
MethodSlot<CallbackClass, int, string> mySlot0(callbackClass, &CallbackClass::SlotMethod0);
MethodSlot<CallbackClass, int, string> mySlot1(callbackClass, &CallbackClass::SlotMethod1);

int main()
{
    cout << myFunctionCallback("Hello Function") << " characters" << endl;
    myMethodCallback("Hello Method");
	
    mySignal.Connect(&mySlot0);
    mySignal.Connect(&mySlot1);
    mySignal.Emit(1, "Goodbye");
    
    return 0;
}
