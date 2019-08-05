#pragma once

#include "Macros.h"
#include <algorithm>

template <typename T>
class ConcTree
{
public:
	ConcTree() : root_{ nullptr } {}

	DISALLOW_COPY_AND_MOVE(ConcTree);

	struct ConcTreeNode
	{
		ConcTreeNode() = default;

		ConcTreeNode(const size_t level = 0U, const size_t size = 1U, bool is_data_node = false)
			: left{ nullptr }
			, right{ nullptr }
			, level{ level }
			, size{ size }
			, is_data_node{ is_data_node }
		{
		}

		ConcTreeNode(ConcTreeNode* left, ConcTreeNode* right, bool is_data_node = false)
			: left{ left }
			, right{ right }
			, level{ std::max(left->level, right->level) + 1U }
			, size{ left->size + right->size }
			, is_data_node{ is_data_node }
		{
		}

		DISALLOW_COPY_AND_MOVE(ConcTreeNode);

		ConcTreeNode* left;
		ConcTreeNode* right;
		size_t level;
		size_t size;
		bool is_data_node : 1;
	};

	struct DataConcTreeNode : public ConcTreeNode
	{
		DataConcTreeNode() = default;

		// I choose to initialize data by parenthesis initialization and not bracket so expect a related behaviour
		// in cases where that matters e.g vector

		DataConcTreeNode(const T& data, const size_t level = 0U, const size_t size = 1U)
			: ConcTreeNode{ level, size, true }
			, data(data)
		{
		}

		DataConcTreeNode(T&& data, const size_t level = 0U, const size_t size = 1U)
			: ConcTreeNode{ level, size, true }
			, data(std::move(data))
		{
		}

		T data;
	};

	void concatenate(ConcTree& other)
	{
		root_ = concatenate_wrapper(root_, other.root_);
	}

	void insert(const T& data)
	{
		DataConcTreeNode* new_node = new DataConcTreeNode(data);
		if (root_)
		{
			root_ = concatenate_wrapper(root_, new_node);
		}
		else
		{
			root_ = new_node;
		}
	}

	void insert(T&& data)
	{
		DataConcTreeNode* new_node = new DataConcTreeNode(std::move(data));
		if (root_)
		{
			root_ = concatenate_wrapper(root_, new_node);
		}
		else
		{
			root_ = new_node;
		}
	}

	void print_inorder()
	{
		print_inorder(root_);
	}

private:

	ConcTreeNode* concatenate(ConcTreeNode* left, ConcTreeNode* right)
	{
		const int64_t level_difference = static_cast<int16_t>(right->level) - static_cast<int64_t>(left->level);

		if (std::abs(level_difference) <= 1)
		{
			return new ConcTreeNode(left, right);
		}

		if (level_difference < -1)
		{
			if (left->left->level >= left->right->level)
			{
				ConcTreeNode* new_right = concatenate(left->right, right);
				return new ConcTreeNode(left->left, new_right);
			}

			ConcTreeNode* new_right_right = concatenate(left->right->right, right);
			if (new_right_right->level == left->level - 3)
			{
				ConcTreeNode* new_right = new ConcTreeNode(left->right->left, new_right_right);
				return new ConcTreeNode(left->left, new_right);
			}

			ConcTreeNode* new_left = new ConcTreeNode(left->left, left->right->left);
			return new ConcTreeNode(new_left, new_right_right);
		}

		if (right->right->level >= right->left->level)
		{
			ConcTreeNode* new_left = concatenate(left, right->left);
			return new ConcTreeNode(new_left, right->right);
		}

		ConcTreeNode* new_left_left = concatenate(left, right->left->left);

		if (new_left_left->level == right->level - 3)
		{
			ConcTreeNode* new_left = new ConcTreeNode(new_left_left, right->left->right);
			return new ConcTreeNode(new_left, right->right);
		}

		ConcTreeNode* new_right = new ConcTreeNode(right->left->right, right->right);
		return new ConcTreeNode(new_left_left, new_right);
	}

	ConcTreeNode* concatenate_wrapper(ConcTreeNode* left, ConcTreeNode* right)
	{
		if (left->size && right->size)
		{
			return concatenate(left, right);
		}
		return !left->size ? right : left;
	}

	void print_inorder(ConcTreeNode* root)
	{
		if (root == nullptr) return;

		print_inorder(root->left);

		if (root->is_data_node)
		{
			std::cout << static_cast<DataConcTreeNode*>(root)->data << std::endl;
		}

		print_inorder(root->right);
	}

	ConcTreeNode* root_;
};
