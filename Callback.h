#ifndef CALLBACK_H_
#define CALLBACK_H_

template<typename R, typename ... Args>
class CallbackBase
{
public:
	virtual R operator()(Args ...) const noexcept = 0;
};

template<typename R, typename ... Args>
class FunctionCallback: virtual public CallbackBase<R, Args ...>
{
public:
	typedef R (*F)(Args ...);

	explicit FunctionCallback(F cb) : _cb(cb) { }
	R operator()(Args ... args) const noexcept { return _cb(args ...); }

private:
	F _cb;
};

template<class T, typename R, typename ... Args>
class MethodCallback: virtual public CallbackBase<R, Args ...>
{
public:
	typedef R (T::*F)(Args ...);

	MethodCallback(T& t, F f) : _t(&t), _f(f) { }
	R operator()(Args ... args) const noexcept { return (_t->*_f)(args ...); }

private:
	T* _t;
	F _f;
};

template<class T, typename R, typename ... Args>
MethodCallback<T, R, Args ...> MakeCallback(T& t, R (T::*f)(Args ...))
{
	return MethodCallback<T, R, Args ...>(t, f);
}

template<typename R, typename ... Args>
FunctionCallback<R, Args ...> MakeCallback(R (*cb)(Args ...))
{
	return FunctionCallback<R, Args ...>(cb);
}

#endif /* CALLBACK_H_ */
