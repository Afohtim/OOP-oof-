#include "Red_black_tree.h"


void Red_black_tree::show_tree(int depth, int n, shared_ptr<Node> node)
{
	if (node == nullptr) return;
	if (current_tree.size() < depth + 1)
	{
		current_tree.push_back(vector<string>(1<<(depth)));
	}
	current_tree[depth][n] = (std::to_string(node->key->key) + ":" + node->key->data + ":" + std::to_string(node->color));
	show_tree(depth + 1, 2*n,  node->left);
	show_tree(depth + 1, 2*n + 1, node->right);
}

vector<vector<string> > Red_black_tree::show_tree()
{
	if (updated)
	{
		current_tree.clear();
	}
	shared_ptr<Node> current_root = root;
	show_tree(0, 0, current_root);
	return current_tree;
}




void Red_black_tree::insert(shared_ptr<Elem> key)
{
	if (root == nullptr)
	{
		root = shared_ptr<Node>(new Node(key));
		root->parent = root_par;
		root->color = Black;
		return;
	}
	shared_ptr<Node> inserted = root;
	shared_ptr<Node> parent_node = root;
	bool finded_parent = false;
	while (!finded_parent)
	{
		if (key->key < parent_node->key->key)
		{
			if (parent_node->left != nullptr)
			{
				parent_node = parent_node->left;
			}
			else
			{
				inserted = shared_ptr<Node>(new Node(key, parent_node));
				parent_node->left = inserted;
				finded_parent = true;
			}
		}
		else
		{
			if (parent_node->right != nullptr)
			{
				parent_node = parent_node->right;
			}
			else
			{
				inserted = shared_ptr<Node>(new Node(key, parent_node));
				parent_node->right = inserted;
				finded_parent = true;
			}
		}
	}
	insert_balance(inserted);
}

void Red_black_tree::erase(shared_ptr<Elem> key)
{
	shared_ptr<Node> erased = find_node(key);
	erase(erased);//PogU
}



Red_black_tree::Red_black_tree()
{
	updated = true;
	root_par = shared_ptr<Node>(new Node(0));
	root_par->color = Black;
	root_par->left = root_par->right = root_par->parent = nullptr;
}


Red_black_tree::~Red_black_tree()
{
	root = nullptr;
}

void Red_black_tree::insert_balance(shared_ptr<Node> inserted)
{
	while (inserted->parent->color == Red)
	{
		if (inserted->parent == inserted->parent->parent->left)
		{
			shared_ptr<Node> uncle = inserted->parent->parent->right;
			if (uncle != nullptr && uncle->color == Red)
			{
				uncle->color = Black;
				inserted->parent->color = Black;
				inserted->color = Red;
				inserted->parent->parent->color = Red;
				inserted = inserted->parent->parent;
			}
			else
			{
				if (inserted == inserted->parent->right)
				{
					inserted = inserted->parent;
					rotate_left(inserted);
				}
				inserted->parent->color = Black;
				inserted->parent->parent->color = Red;
				rotate_right(inserted->parent->parent);
			}
		}
		else if (inserted->parent == inserted->parent->parent->right)
		{
			shared_ptr<Node> uncle = inserted->parent->parent->left;
			if (uncle != nullptr && uncle->color == Red)
			{
				uncle->color = Black;
				inserted->parent->color = Black;
				inserted->color = Red;
				inserted->parent->parent->color = Red;
				inserted = inserted->parent->parent;
			}
			else
			{
				if (inserted == inserted->parent->left)
				{
					inserted = inserted->parent;
					rotate_right(inserted);
				}
				inserted->parent->color = Black;
				inserted->parent->parent->color = Red;
				rotate_left(inserted->parent->parent);
			}

		}
	}
	while (root->parent != root_par)
		root = root->parent;
	root->color = Black;
}

void Red_black_tree::erase_balance(shared_ptr<Node> erased, shared_ptr<Node> parent)
{
	while (erased == nullptr || erased != root && erased->color == Black)
	{
		shared_ptr<Node> sibling;
		if (erased == parent->left)
		{
			sibling = parent->right;
			if (sibling->color == Red)
			{
				sibling->color = Black;
				parent->color = Red;
				rotate_left(parent);
				sibling = parent->right;
			}
			if ((sibling->left == nullptr || sibling->left->color == Black) && (sibling->right == nullptr || sibling->right->color == Black))
			{
				sibling->color = Red;
				erased = parent;
				parent = parent->parent;
			}
			else
			{
				if (sibling->right == nullptr || sibling->right->color == Black)
				{
					if (sibling->left != nullptr)
						sibling->left->color = Black;
					sibling->color = Red;
					rotate_right(sibling);
					sibling = sibling->right;
				}
				sibling->color = parent->color;
				parent->color = Black;
				if (sibling->right != nullptr)
					sibling->right->color = Black;
				rotate_left(parent);
				erased = root;
			}
		}
		else
		{
			sibling = parent->left;
			if (sibling->color == Red)
			{
				sibling->color = Black;
				parent->color = Red;
				rotate_right(parent);
				sibling = parent->left;
			}
			if ((sibling->right == nullptr || (sibling->right != nullptr && sibling->right->color == Black)) && (sibling->left == nullptr || (sibling->left != nullptr && sibling->left->color == Black)))
			{
				sibling->color = Red;
				erased = parent;
				parent = parent->parent;
			}
			else
			{
				if (sibling->left == nullptr || sibling->left->color == Black)
				{
					if (sibling->right != nullptr)
						sibling->right->color = Black;
					sibling->color = Red;
					rotate_left(sibling);
					sibling = sibling->left;
				}
				sibling->color = parent->color;
				parent->color = Black;
				if (sibling->left != nullptr)
					sibling->left->color = Black;
				rotate_right(parent);
				erased = root;
			}
		}
	}
	erased->color = Black;
	

}

void Red_black_tree::rotate_left(shared_ptr<Node> pivot)
{
	shared_ptr<Node> rotated_node = pivot->right;

	pivot->right = rotated_node->left;
	if (rotated_node->left != nullptr)
		rotated_node->left->parent = pivot;


	rotated_node->parent = pivot->parent;

	if (pivot->parent == root_par)
	{
		root = rotated_node;
	}
	else 
	{
		if (pivot == pivot->parent->left)
			pivot->parent->left = rotated_node;
		else
			pivot->parent->right = rotated_node;
	}
	rotated_node->left = pivot;
	pivot->parent = rotated_node;
	

}

void Red_black_tree::rotate_right(shared_ptr<Node> pivot)		
{
	shared_ptr<Node> rotated_node = pivot->left;

	pivot->left = rotated_node->right;
	if (rotated_node->right != nullptr)
		rotated_node->right->parent = pivot;


	rotated_node->parent = pivot->parent;

	if (pivot->parent == root_par)
	{
		root = rotated_node;
	}
	else
	{
		if (pivot == pivot->parent->right)
			pivot->parent->right = rotated_node;
		else
			pivot->parent->left = rotated_node;
	}
	rotated_node->right = pivot;
	pivot->parent = rotated_node;
}

shared_ptr<Node> Red_black_tree::successor(shared_ptr<Node> node)
{
	if (node->left != nullptr)
	{
		node = node->left;
		while (node->right != nullptr)
			node = node->right;
		return node;
	}
	else
	{
		node = node->right;
		while (node->left != nullptr)
			node = node->left;
		return node;
	}
	
}

shared_ptr<Node> Red_black_tree::find_node(shared_ptr<Elem> key)
{
	shared_ptr<Node> temp_node = root;
	while (temp_node != nullptr)
	{
		if (key->key == temp_node->key->key)
			return temp_node;
		else if (key->key < temp_node->key->key)
			temp_node = temp_node->left;
		else
			temp_node = temp_node->right;
	}
	
	return nullptr;
}

void Red_black_tree::erase(shared_ptr<Node> erased)
{
	if (erased == nullptr)
		return;
	shared_ptr<Node> to_remove;
	if (erased->left == nullptr || erased->right == nullptr)
		to_remove = erased;
	else
		to_remove = successor(erased);

	shared_ptr<Node> removed_son;
	if (to_remove->left != nullptr)
		removed_son = to_remove->left;
	else
		removed_son = to_remove->right;
	if(removed_son != nullptr)
		removed_son->parent = to_remove->parent;

	if (to_remove == root)
	{
		root = removed_son;
	}
	else
	{
		if (to_remove == to_remove->parent->left)
			to_remove->parent->left = removed_son;
		else
			to_remove->parent->right = removed_son;
	}
	if (erased != to_remove)
	{
		erased->key = to_remove->key; //copy 
	}
	shared_ptr<Node> parent_node = to_remove->parent;
	while (parent_node != root_par)
	{
		parent_node = parent_node->parent;
	}
	if (to_remove->color == Black)
		erase_balance(removed_son, to_remove->parent);
}



Node::Node(shared_ptr<Elem> key, shared_ptr<Node> parent, int node_color)
{
	this->key = key;
	this->parent = parent;
	left = right = nullptr;
	color = node_color;
}

