#pragma once

#ifndef CONTAINER_NAMESPACE_BEGIN
#define CONTAINER_NAMESPACE_BEGIN namespace MyContainer{
#endif

#ifndef CONTAINER_NAMESPACE_END
#define CONTAINER_NAMESPACE_END }
#endif

#ifndef Version1_BEGIN
#define Version1_BEGIN inline namespace ver1{
#endif

#ifndef Version1_END
#define Version1_END }
#endif

#include "MyAllocator.h"
#include "MyIterator.h"

CONTAINER_NAMESPACE_BEGIN

Version1_BEGIN 

template<typename T, typename Alloc = MyContainer::MyAllocator<T>>
class MyVector
{
	struct MyPair 
	{
		T* first;
		T* last;
		T* end;
		MyPair() : first(nullptr), last(nullptr), end(nullptr){}
	};
	MyPair _MyPair;
	Alloc allocator;
public:
	using value_type = T;
	using iterator = MyIterator<T>;

	explicit MyVector(size_t size, const T& value, const Alloc& allocator = Alloc()) : _MyPair(), allocator(allocator)
	{
		this->_MyPair.first = this->allocator.allocate(size);
		this->_MyPair.last = this->_MyPair.first + size;
		this->_MyPair.end = this->_MyPair.first + size;

		for (T* pointer = this->_MyPair.first; pointer != this->_MyPair.last; ++pointer)
		{
			this->allocator.construct(pointer, value);
		}
	}

	explicit MyVector(size_t size) : MyVector(size, T(), Alloc()){}

	explicit MyVector(const Alloc& allocator) noexcept: _MyPair(), allocator(allocator) {}

	explicit MyVector() noexcept: _MyPair(), allocator(Alloc()) {}

	MyVector(const MyVector& rhs) : _MyPair(), allocator(rhs.allocator)
	{
		this->reallocate(rhs.size());

		T* pointer = this->_MyPair.first;// 意味あり

		for (size_t i = 0; i < rhs.size(); ++i)
		{
			this->allocator.construct(&pointer[i], rhs._MyPair.first[i]);
		}
		this->_MyPair.last += rhs.size();
	}

	MyVector(MyVector&& rhs) : _MyPair(), allocator(std::move(rhs.allocator))
	{
		this->_MyPair.first = rhs._MyPair.first;
		rhs._MyPair.first = nullptr;

		this->_MyPair.last = rhs._MyPair.last;
		rhs._MyPair.last = nullptr;

		this->_MyPair.end = rhs._MyPair.end;
		rhs._MyPair.end = nullptr;
	}
	~MyVector() noexcept
	{
		for (T* pointer = this->_MyPair.first; pointer != this->_MyPair.last; ++pointer)
		{
			this->allocator.destroy(pointer);
		}

		this->allocator.deallocate(this->_MyPair.first, this->capacity());
	}

	void push_back(const T& value)
	{
		this->emplace_one_at_back(value);
	}

	void push_back(T&& value)
	{
		this->emplace_one_at_back(std::move(value));
	}
	template<typename... Valty>
	void emplace_back(Valty&&... value)
	{
		this->emplace_one_at_back(std::forward<Valty>(value)...);
	}
	void pop_back()
	{
		if (this->size() == 0) return;
		--this->val.last;
		this->alloc.destroy(this->val.last);
	}

	void clear() noexcept
	{
		size_t size = this->size();

		for (size_t i = 0; i < size; ++i)
		{
			this->pop_back();
		}
	}
	
	size_t size() const noexcept
	{
		return this->_MyPair.last - this->_MyPair.first;
	}

	size_t capacity() const noexcept
	{
		return this->_MyPair.end - this->_MyPair.first;
	}

	bool empty() const noexcept
	{
		return this->size() == 0;
	}

	T& operator[](const size_t index)
	{
		if (index >= this->size() || index < 0) throw;
		return *(this->_MyPair.first + index);
	}

	const T& operator[](const size_t index) const
	{
		if (index >= this->size()) throw;
		return *(this->_MyPair.first + index);
	}

	T* data() const noexcept
	{
		return this->_MyPair.first;
	}

	T front() const
	{
		if (!this->_MyPair.first) throw;
		return *this->_MyPair.first;
	}

	T back() const
	{
		if (!this->_MyPair.first) throw;
		return *(this->_MyPair.last - 1);
	}

	void resize(size_t size) 
	{
		if (size <= this->size())
		{
			return;
		}

		size_t old_size = this->size();

		this->reallocate(size);

		for (size_t i = old_size; i < size; ++i)
		{
			this->allocator.construct(&this->_MyPair.first[i], T());
		}

		this->_MyPair.last += size - old_size;
	}

	void reserve(size_t size)
	{
		if (size <= this->size())
		{
			return;
		}

		this->reallocate(size);
	}

	void shrink_to_fit()
	{
		if (this->_MyPair.last == this->_MyPair.end)
		{
			return;
		}
		
		this->reallocate(this->size());
	}

	iterator begin() const
	{
		return iterator(this->_MyPair.first, this->_MyPair.first, this->_MyPair.last);
	}

	iterator end() const
	{
		return iterator(this->_MyPair.last, this->_MyPair.first, this->_MyPair.last);
	}
private:
	// size を再度確保する時の次のサイズを計算する関数
	size_t resize_algorithm(size_t size)
	{
		return 2 * size + 1;
		// STL
		if (size == 1) return 2;
		return static_cast<size_t>(this->resize_algorithm(size - 1) * (1.5));
	}

	void reallocate(size_t new_allocate_size)
	{
		size_t old_size = this->size();
		size_t old_capacity = this->capacity();
		T* pointer = this->allocator.allocate(new_allocate_size);
		for (size_t i = 0; i < old_size; ++i)
		{
			this->allocator.construct(&pointer[i], this->_MyPair.first[i]);
		}

		for (size_t i = 0; i < old_size; ++i)
		{
			this->allocator.destroy(&this->_MyPair.first[i]);
		}
		this->allocator.deallocate(this->_MyPair.first, old_capacity);

		this->_MyPair.first = pointer;
		this->_MyPair.last = pointer + old_size;
		this->_MyPair.end = pointer + new_allocate_size;
	}

	template<typename... Valty>
	T& emplace_one_at_back(Valty&&... value)
	{
		if (static_cast<size_t>(this->_MyPair.end - this->_MyPair.last) > 0)
		{
			this->allocator.construct(this->_MyPair.last, std::forward<Valty>(value)...);
			T& result = *this->_MyPair.last;
			++this->_MyPair.last;
			return result;
		}
		else
		{
			size_t size_ = this->size();

			this->reallocate(this->resize_algorithm(this->size()));

			this->allocator.construct(&this->_MyPair.first[size_], std::forward<Valty>(value)...);
			T& result = *this->_MyPair.last;
			++this->_MyPair.last;
			return result;
		}
	}
};

Version1_END

CONTAINER_NAMESPACE_END