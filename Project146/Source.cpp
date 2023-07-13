#include <iostream>

template <typename T>
class Array {
private:
    T* data;
    int size;
    int capacity;
    int grow;

public:
    Array(int initialSize = 0, int initialCapacity = 10, int growValue = 1)
        : size(initialSize), capacity(initialCapacity), grow(growValue) {
        data = new T[capacity];
    }

    ~Array() {
        delete[] data;
    }

    int GetSize() const {
        return size;
    }

    void SetSize(int newSize, int newGrow = 1) {
        if (newSize < 0) {
            return;
        }

        grow = newGrow;
        if (newSize <= capacity) {
            size = newSize;
        }
        else {
            capacity = newSize + grow;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            size = newSize;
        }
    }

    int GetUpperBound() const {
        return size - 1;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    void FreeExtra() {
        if (size < capacity) {
            capacity = size;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
    }

    void RemoveAll() {
        delete[] data;
        size = 0;
        capacity = 0;
        data = new T[capacity];
    }

    T& GetAt(int index) const {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void SetAt(int index, const T& value) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        data[index] = value;
    }

    T& operator[](int index) const {
        return GetAt(index);
    }

    void Add(const T& value) {
        if (size == capacity) {
            capacity += grow;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size++] = value;
    }

    void Append(const Array<T>& other) {
        int newSize = size + other.size;
        if (newSize > capacity) {
            capacity = newSize + grow;
            T* newData = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        for (int i = 0; i < other.size; ++i) {
            data[size + i] = other.data[i];
        }
        size = newSize;
    }

    Array<T>& operator=(const Array<T>& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    T* GetData() const {
        return data;
    }

    void InsertAt(int index, const T& value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }

        if (size == capacity) {
            capacity += grow;
            T* newData = new T[capacity];
            for (int i = 0; i < index; ++i) {
                newData[i] = data[i];
            }
            newData[index] = value;
            for (int i = index; i < size; ++i) {
                newData[i + 1] = data[i];
            }
            delete[] data;
            data = newData;
            ++size;
        }
        else {
            for (int i = size - 1; i >= index; --i) {
                data[i + 1] = data[i];
            }
            data[index] = value;
            ++size;
        }
    }

    void RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        for (int i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }
};

int main() {
    Array<int> array;

  
    array.Add(10);
    array.Add(20);
    array.Add(30);


    std::cout << "Size: " << array.GetSize() << std::endl; 

  
    std::cout << "Element at index 0: " << array.GetAt(0) << std::endl; 
    std::cout << "Element at index 1: " << array[1] << std::endl; 

   
    array.RemoveAt(1);

    std::cout << "Upper bound: " << array.GetUpperBound() << std::endl;

  
    for (int i = 0; i < array.GetSize(); ++i) {
        std::cout << "Element at index " << i << ": " << array.GetAt(i) << std::endl;
    }

    return 0;
}