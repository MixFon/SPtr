//
//  SPrt.h
//  Prt
//
//  Created by Михаил Фокин on 04.11.2021.
//

#ifndef SPrt_h
#define SPrt_h

template <class T>
class ControlBlock {
	size_t referenceCounter = 0;
	T *data;
	
public:
	ControlBlock(): data(NULL), referenceCounter(0) {}
	
	ControlBlock(T *data): data(data) {
		increment();
	}
	
	void increment() {
		referenceCounter++;
		std::cout << "increment "<< " " << *data << " " << referenceCounter << std::endl;
	}
	
	void decrement() {
		referenceCounter--;
		std::cout << "decrement "<< " " << *data << " " << referenceCounter << std::endl;
	}
	
	size_t getReferenceCounter() const {
		return referenceCounter;
	}
	
	T *getData() const {
		return data;
	}
};

template <class T>
class SPtr {
	ControlBlock<T> *controlBlock;
	T *data;

public:
	SPtr(T *data): data(data), controlBlock(new ControlBlock<T>(data)) {}
	
	~SPtr() {
		std::cout << "destructor" << std::endl;
		controlBlock->decrement();
		if (controlBlock->getReferenceCounter() <= 0) {
			std::cout << "delete " << *data << std::endl;
			delete data;
			delete controlBlock;
			
		}
	}
	
	SPtr(SPtr &other) {
		data = other.data;
		other.controlBlock->increment();
		controlBlock = other.controlBlock;
	}
	
	SPtr &operator = (SPtr &other) {
		if (data == other.data)
			return *this;
		this->~SPtr();
		data = other.data;
		controlBlock = other.controlBlock;
		controlBlock->increment();
		return *this;
	}
	
	size_t getReferenceCounter() const {
		return controlBlock->getReferenceCounter();
	}
	
	T &operator *() {
		return *data;
	}
	
	T *operator -> () {
		return data;
	}
};

#endif /* SPrt_h */
