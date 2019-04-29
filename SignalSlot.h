/*
 * SignalSlot.h
 *
 *  Created on: 14 feb. 2016
 *      Author: alexandru.bogdan
 */

#ifndef SIGNALSLOT_H_
#define SIGNALSLOT_H_

#include "Callback.h"

template<typename ... Args>
class FunctionSlot: public FunctionCallback<void, Args ...>
{
public:
	explicit FunctionSlot(typename FunctionCallback<void, Args ...>::F f) : FunctionCallback<void, Args ...>(f) { }
};

template<class T, typename ... Args>
class MethodSlot: public MethodCallback<T, void, Args ...>
{
public:
	MethodSlot(T &t, typename MethodCallback<T, void, Args ...>::F f) : MethodCallback<T, void, Args ...>(t, f) { }
};

template<unsigned int NrSlots, typename ... Args>
class Signal
{
public:
	Signal() : _slots(), _isEmitting(false) { }
	~Signal() { }

	void Emit(Args ... args)
	{
		if(_isEmitting)
			return;

		_isEmitting = true;
		for (unsigned int i = 0; i < NrSlots; i++)
		{
			if (_slots[i] != nullptr)
				(*_slots[i])(args ...);
		}
		_isEmitting = false;
	}

	bool Connect(CallbackBase<void, Args ...> *slot)
	{
		for (unsigned int i = 0; i < NrSlots; i++)
		{
			if (_slots[i] == nullptr)
			{
				_slots[i] = slot;
				return true;
			}
		}
		return false;
	}

	bool Disconnect(CallbackBase<void, Args ...> *slot)
	{
		for (unsigned int i = 0; i < NrSlots; i++)
		{
			if (_slots[i] == slot)
			{
				_slots[i] = nullptr;
				return true;
			}
		}
		return false;
	}

private:
	CallbackBase<void, Args ...> *_slots[NrSlots];
	bool _isEmitting;
};

#endif /* SIGNALSLOT_H_ */
