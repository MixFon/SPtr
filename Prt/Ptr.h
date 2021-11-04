//
//  Ptr.h
//  Prt
//
//  Created by Михаил Фокин on 04.11.2021.
//

#ifndef Ptr_h
#define Ptr_h

template <class T>
class Ptr {
	T *data;
	
public:
	
	Ptr(T *data): data(data) {}

	~Ptr() {
		if (data == NULL)
			return;
		delete data;
		
	}
	
	Ptr(const Ptr &other) = delete;
	
	Ptr &operator = (Ptr &other) = delete;
	
	T &operator *() {
		return *data;
	}
	
	T *operator -> () {
		return data;
	}
};


#endif /* Ptr_h */
