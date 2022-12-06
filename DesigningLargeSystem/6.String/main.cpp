#include <iostream>
#include <cassert>
#include "intrusive_ptr.h"

class TDoc: public TRefCounter<TDoc> {
};

int main() {
	TIntrusivePtr<TDoc> ptr = nullptr;

	ptr = MakeIntrusive<TDoc>();
	std::cout << ptr->RefCount() << "\n";

	TIntrusivePtr<TDoc> ptr2 = ptr;
	std::cout << ptr->RefCount() << " " << ptr2->RefCount() << "\n";

	TIntrusivePtr<TDoc> ptr3 = MakeIntrusive<TDoc>();
	ptr3.Reset(ptr2);
	std::cout << ptr->RefCount() << " " << ptr3->RefCount() << "\n";

	ptr3.Reset();
	std::cout << ptr->RefCount() << " " << ptr2->RefCount() << "\n";

	ptr3.Reset(std::move(ptr2));
	std::cout << ptr->RefCount() << " " << ptr3->RefCount() << "\n";

	static_assert(sizeof(TDoc*) == sizeof(ptr), "oh my God");

       TIntrusivePtr<TDoc> ptr = nullptr;

}