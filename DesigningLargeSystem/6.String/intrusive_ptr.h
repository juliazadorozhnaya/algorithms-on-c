#include <algorithm>

template<typename T>
class TBasePtr {
public:
    TBasePtr(T* from_ptr = nullptr) : ptr(from_ptr) { }

    T* operator->() const {
        return ptr;
    }

    T& operator*() const {
        return *ptr;
    }

	friend bool operator != (const TBasePtr& lhs, const TBasePtr& rhs) {
		return lhs.value != rhs.value;
	}

	friend bool operator == (const TBasePtr& lhs, const TBasePtr& rhs) {
		return lhs.value == rhs.value;

    }
    operator bool() const {
        return ptr != nullptr;
    }

protected:
	TBasePtr() = default;
    T* ptr = nullptr;
};

template<typename T>
class TIntrusivePtr : public TBasePtr<T> {
public:
    TIntrusivePtr(T* from_ptr) : TBasePtr<T>(from_ptr) {
        if (this->ptr) {
            this->ptr->Inc();
        }
    }

    TIntrusivePtr(const TIntrusivePtr& other) : TIntrusivePtr<T>(other.ptr) { }

    TIntrusivePtr(TIntrusivePtr&& other) noexcept : TIntrusivePtr<T>(other.ptr) {
            other.Release();
    }

    TIntrusivePtr& operator=(TIntrusivePtr other) {
        Swap(other);
        return *this;
    }

    ~TIntrusivePtr() {
        if (this->ptr) {
            this->ptr->Dec();
            if (this->ptr->RefCount() == 0) {
                delete this->ptr;
            }
        }
    }

    size_t UseCount() const {
        if (this->ptr) {
            return this->ptr->RefCount();
        } else {
            return 0;
        }
    }

    T* Get() const {
        return this->ptr;
    }

    void Reset(TIntrusivePtr<T> other = nullptr) {
        Swap(other);
    }

    T* Release() {
        T* ans = this->ptr;
        if (ans) {
            ans->Dec();
        }
        this->ptr = nullptr;
        return ans;
    }

    void Swap(TIntrusivePtr<T>& other) {
        std::swap(this->ptr, other.ptr);
    }

    size_t RefCount() const {
        return UseCount();
    }
};



template <typename T>
class TRefCounter
{
public:
    TRefCounter() = default;

    size_t RefCount() {
        return ref_count;
    }

private:
    friend TIntrusivePtr<T>;

    size_t Dec() {
        --ref_count;
        return ref_count;
    }

    size_t Inc() {
        ++ref_count;
        return ref_count;
    }
    size_t ref_count = 0;
};

template <typename T, typename... Args>
TIntrusivePtr<T> MakeIntrusive(Args&&... params) {
    return TIntrusivePtr<T>(new T(std::forward<Args>(params)...));
};