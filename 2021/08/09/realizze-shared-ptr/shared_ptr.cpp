#include<iostream>
#include <memory>
using namespace std;
template<class T>
class S_ptr
{
public:
    S_ptr();
    S_ptr(T *p);
    ~S_ptr();
    S_ptr(const S_ptr<T> &org);
    S_ptr<T>& operator = (const S_ptr<T> &org);
    int get_count();
    void get();
private:
    int *use_count;
    T *ptr;
};

template<class T>
S_ptr<T>::S_ptr() : ptr(), use_count(new int (1)) {
    cout << "Allocation11" << endl;
};
template<class T>
S_ptr<T>::S_ptr(T *p) : ptr(p) {
    use_count = new int(1);
    cout << "Allocation22" << endl;
    if (use_count == nullptr) {
        p = nullptr;
        cout << "Allocation Error" << endl;
        return;
    }
}

template<class T>
S_ptr<T>::~S_ptr() {
    if (--*use_count == 0) {
        delete ptr;
        ptr = nullptr;
        delete use_count;
        use_count = nullptr;
    }
}

template<class T>
S_ptr<T>::S_ptr(const S_ptr<T> &org) {
    ptr = org.ptr;
    use_count = org.use_count;
    (*use_count)++;
}
template<class T>
S_ptr<T>& S_ptr<T>::operator = (const S_ptr &org) {
    if (this->ptr) {
        if (--this->use_count == 0) {
            delete this->ptr;
            delete this->count;
        }
        this->ptr = org.ptr;
        this->use_count = org.use_count;
        (*use_count)++;
    }
    return *this;   
}
template<class T>
S_ptr<T>::get_count() {
    return *use_count;
}

int main() {
    //S_ptr<string> p1 = new string("hello");
    S_ptr<string> p1(new string("hello"));
    shared_ptr<int> p(new int(2));
    cout << p1.get_count() << endl;
    S_ptr<string> p2(p1);
    cout << p1.get_count() << endl;
    {
        S_ptr<string> p3(p1);
        cout << p1.get_count() << endl;
    }
    cout << p1.get_count() << endl;
    return 0;
}