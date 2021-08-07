//Array.h
#ifndef _ARRAY_H
#define _ARRAY_H
typedef signed long int Long;
template <typename T>

class Array {
public:
	Array(Long capacity = 256);
	Array(const Array& source);
	~Array();
	Long Store(Long index, T object);
	Long Insert(Long index, T object);
	Long AppendFromFront(T object);
	Long AppendFromRear(T object);
	Long Delete(Long index);
	Long DeleteFromFront();
	Long DeleteFromRear();
	void Clear();
	Long Modify(Long index, T object);
	Long LinearSearchUnique(void* key, int(*compare)(void*, void*));
	void LinearSearchDuplicate(void* key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	Long BinarySearchUnique(void* key, int(*compare)(void*, void*));
	void BinarySearchDuplicate(void* key, Long *(*indexes), Long *count, int(*compare)(void*, void*));
	void BubbleSort(int(*compare)(void*, void*));
	void SelectionSort(int(*compare)(void*, void*));
	void InsertionSort(int(*compare)(void*, void*));
	void Merge(const Array& one, const Array& other, int(*compare)(void*, void*));
	T& GetAt(Long index);
	Array& operator =(const Array& source);
	T& operator[](Long index);
	T* operator + (Long index);
	Long GetCapacity() const;
	Long GetLength() const;

private:
	T(*front);
	Long capacity;
	Long length;
};

template <typename T>
inline Long Array<T>::GetCapacity() const {
	return this->capacity;
}

template<typename T>
inline Long Array<T>::GetLength() const {
	return this->length;
}

template<typename T>
Array<T>::Array(Long capacity) {
	this->front = new T[capacity];
	this->capacity = capacity;
	this->length = 0;
}


template<typename T>
Array<T>::Array(const Array& source) {
	Long i = 0;
	this->front = new T[source.capacity];
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
}

template<typename T>
Array<T>::~Array() {
	if (this->front != 0) {
		delete[] this->front;
	}
}

template<typename T>
Long Array<T>::Store(Long index, T object) {
	this->front[index] = object;
	this->length++;

	return index;
}
template<typename T>
Long Array<T>::Insert(Long index, T object) {
	Long i = 0;
	T(*front);

	front = new T[this->capacity + 1];
	while (i < index) {
		front[i] = this->front[i];
		i++;
	}
	while (i < this->length) {
		front[i + 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::AppendFromFront(T object) {
	Long index = 0;
	T(*front);
	Long i = 0;
	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[i + 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::AppendFromRear(T object) {
	Long index;
	Long i = 0;
	T(*front) = 0;

	front = new T[this->capacity + 1];
	while (i < this->length) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = front;
	this->capacity++;
	index = this->length;
	this->front[index] = object;
	this->length++;

	return index;
}

template<typename T>
Long Array<T>::Delete(Long index) {
	T(*front)=0;
	Long i = 0;
	if (this->capacity > 1) {
		front = new T[this->capacity - 1];
	}
	while (i < index) {
		front[i] = this->front[i];
		i++;
	}

	i++;

	while (i < this->length) {
		front[i - 1] = this->front[i];
		i++;
	}

	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}

	if (this->capacity>1) {
		this->front = front;
	}

	this->capacity--;
	this->length--;
	index = -1;

	return index;
}

template<typename T>
Long Array<T>::DeleteFromFront() {
	Long index = -1;
	T(*front) = 0;
	Long i = 1;
	if (this->capacity > 1) {
		front = new T[this->capacity - 1];
	}
	while (i < this->length) {
		front[i - 1] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = front;
	}
	this->capacity--;
	this->length--;
	
	return index;
}

template<typename T>
Long Array<T> ::DeleteFromRear() {
	Long index = -1;
	T(*front) = 0;;
	Long i = 0;
	if (this->capacity > 1) {
		front =new T[this->capacity - 1];
	}
	while (i < this->capacity-1) {
		front[i] = this->front[i];
		i++;
	}
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	if (this->capacity > 1) {
		this->front = front;
	}
	this->capacity--;
	this->length--;

	return index;
}
template<typename T>
void Array<T>::Clear() {
	if (this->front != 0) {
		delete[] this->front;
		this->front = 0;
	}
	this->capacity = 0;
	this->length = 0;
}

template<typename T>
Long Array<T>::Modify(Long index, T object) {
	this->front[index] = object;

	return index;
}

template<typename T>
Long Array<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long i = 0;
	while (i < this->length&&compare(this->front + i, key) != 0) {
		i++;
	}
	if (i < this->length) {
		index = i;
	}
	return index;
}


template<typename T>
void Array<T>::LinearSearchDuplicate(void *key, Long *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long i = 0;
	Long index = 0;
	*count = 0;
	*indexes = new Long[this->length];
	while (index < this->length) {
		if (compare(this->front+index, key) == 0) {
			(*indexes)[i] = index;
			(*count)++;
			i++;
		}
		index++;
	}
}

template<typename T>
Long Array<T>::BinarySearchUnique(void*key, int(*compare)(void*, void*)) {
	Long index = -1;
	Long minIndex = 0;
	Long maxIndex;
	Long midIndex;
	maxIndex = this->length - 1;
	midIndex = (minIndex + maxIndex) / 2;
	while (minIndex <= maxIndex && compare(this->front + midIndex, key) != 0) {
		if (compare(this->front + midIndex, key) < 0) {
			minIndex = midIndex + 1;
		}
		else {
			minIndex = midIndex - 1;
		}
		midIndex = (minIndex + maxIndex) / 2;
	}
	if (minIndex <= maxIndex) {
		index = midIndex;
	}
	return index;
}

template<typename T>
void Array<T>::BinarySearchDuplicate(void*key, Long*(*indexes), Long *count, int(*compare)(void*, void*)) {
	Long minIndex = 0;
	Long maxIndex;
	Long midIndex;
	Long index;
	Long i = 0;
	*count = 0;
	*indexes = new Long[this->length];
	maxIndex = this->length - 1;
	midIndex = (minIndex + maxIndex) / 2;
	while (minIndex <= maxIndex && compare(this->front + midIndex, key) != 0) {
		if (compare(this->front + midIndex, key) > 0) {
			maxIndex = midIndex - 1;
		}
		else {
			minIndex = midIndex + 1;
		}
		midIndex = (minIndex + maxIndex) / 2;
	}
	index = midIndex - 1;
	while (index > 0 && compare(this->front + index, key) == 0) {
		index--;
	}
	index++;
	while (index > 0 && index < this->length && compare(this->front + index, key) == 0) {
		(*indexes)[i] = index;
		(*count)++;
		i++;
		index++;
	}
}

template<typename T>
void Array<T>::BubbleSort(int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	Long k;
	T temp;
	bool flag = false;
	Long length;

	while (i < this->length&&flag == false) {
		flag = true;
		j = 0;
		length = this->length - i;
		while (j < length) {
			k = j + 1;
			if (compare(this->front + j, this->front + k) > 0) {
				temp = this->front[j];
				this->front[j] = this->front[k];
				this->front[k] = temp;
				flag = false;
			}
			j++;
		}
		i++;
	}
}

template<typename T>
void Array<T>::SelectionSort(int(*compare)(void*, void*)) {
	Long i = 0;
	Long j;
	T temp;
	Long index;

	while (i < this->length - 1) {
		index = i;
		j = i + 1;
		while (j < this->length) {
			if (compare(this->front + index, this->front + j) > 0) {
				index = j;
			}
			j++;
		}
		temp = this->front[i];
		this->front[i] = this->front[index];
		this->front[index] = temp;
		i++;
	}
}

template<typename T>
void Array<T>::InsertionSort(int(*compare)(void*, void*)) {
	Long i = 1;
	Long j;
	T temp;
	Long k;
	while (i < this->length) {
		temp = this->front[i];
		j = 0;
		while (i > j && compare(this->front + j, &temp) < 0) {
			j++;
		}
		k = i;
		while (k > j) {
			this->front[k] = this->front[k - 1];
			k--;
		}
		this->front[j] = temp;
		i++;
	}
}

template<typename T>
void Array<T>::Merge(const Array& one, const Array& other, int(*compare)(void* one, void* other)) {
	Long length;
	Long i = 0;
	Long j = 0;
	Long k = 0;
	length = one.length + other.length;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[length];
	this->capacity = length;
	while (i < one.length && j < other.length) {
		if (compare(one.front + i, other.front + j) > 0 ||
			compare(one.front + i, other.front + j) == 0){
			this->front[k] = other.front[j];
			k++;
			j++;
}
		else {
			this->front[k] = one.front[i];
			k++;
			i++;
		}
	}
	while (i < one.length) {
		this->front[k] = one.front[i];
		k++;
		i++;
	}
	while (j < other.length) {
		this->front[k] = other.front[j];
		k++;
		j++;
	}
	this->length = length;
}

template<typename T>
T& Array<T>::GetAt(Long index) {
	return this->front[index];
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& source) {
	Long i = 0;
	if (this->front != 0) {
		delete[] this->front;
	}
	this->front = new T[source.capacity];
	this->capacity = source.capacity;
	while (i < source.length) {
		this->front[i] = source.front[i];
		i++;
	}

	this->length = source.length;
	return *this;
}

template<typename T>
T* Array<T>::operator+(Long index) {
	return this->front + index;
}

template<typename T>
T& Array<T>::operator[](Long index) {
	return this->front[index];
}



#endif//_ARRAY_H