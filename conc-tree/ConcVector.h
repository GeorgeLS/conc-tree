#pragma once

#include "Macros.h"
#include "ConcTree.h"
#include <algorithm>

template <typename T>
class ConcVector
{
public:
	// We go for 64 because that's the most common cache line size in bytes in modern processors
	// despite the fact that the size of the type will probably be over 1 byte
	ConcVector(const size_t chunk_size = 64U)
		: tree_{}
		, chunk_{ new T[chunk_size] }
		, chunk_size_{ chunk_size }
		, index_{ 0U }
	{
	}

	DISALLOW_COPY_AND_MOVE(ConcVector);

	void insert(const T& data)
	{
		if (index_ == chunk_size_)
		{
			expand();
		}

		chunk_[index_++] = data;
	}

	void insert(T&& data)
	{
		if (index_ == chunk_size_)
		{
			expand();
		}

		chunk_[index_++] = std::move(data);
	}

private:

	void expand()
	{
		tree_.insert(chunk_);
		chunk_ = new T[chunk_size_];
		index_ = 0U;
	}

	ConcTree<T*> tree_;
	T* chunk_;
	size_t chunk_size_;
	size_t index_;
};
