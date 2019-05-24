
template <typename T>
class Unique_Ptr
{
public:
	explicit Unique_Ptr(T *p) : ptr{p} { }
	~Unique_Ptr() { if (ptr) delete ptr; }

	Unique_Ptr(const Unique_Ptr &) = delete;
	Unique_Ptr & operator = (const Unique_Ptr &) = delete;

	Unique_Ptr(Unique_Ptr &&up) { ptr = up.ptr; up.ptr = nullptr; }
	Unique_Ptr & operator = (Unique_Ptr &&up) { ptr = up.ptr; up.ptr = nullptr; }

	T & operator * () { return &(*ptr); }
	T * operator -> () { return ptr; }

private:
	T *ptr;
};