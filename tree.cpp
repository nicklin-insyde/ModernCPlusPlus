#include<iostream>
#include "tree.h"

using namespace std;

int avlTree::id = 0;

void test_func()
{
	avlTree avl;
	bool break_loop = false;
	int choice = 0, item = 0;
	while (1)
	{
		cout << endl<<"---------------------" << endl;
		cout << "AVL Tree Implementation" << endl;
		cout << "---------------------" << endl;
		cout << "1.Insert Element into the tree" << endl;
		cout << "2.Display Balanced AVL Tree" << endl;
		cout << "3.InOrder traversal" << endl;
		cout << "4.PreOrder traversal" << endl;
		cout << "5.PostOrder traversal" << endl;
		cout << "6.Exit" << endl;
		cout << "Enter your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter value to be inserted: ";
			cin >> item;
			avl.insert(item);
			break;

		case 2:
			avl.display();
			break;
		case 3:
			avl.inorder();
			break;
		case 4:
			avl.preorder();
			break;
		case 5:
			avl.postorder();
			break;
		case 6:
			break_loop = true;
			break;
		default:
			cout << "Wrong Choice" << endl;
		}
		if(break_loop == true)
			break;
	}
}

//
// constructor
//
avlTree::avlTree() :root(nullptr) {}

void avlTree::insert(int value)
{
	insert(root, value);
}

void avlTree::pop_root()
{
	cout << root->data<<endl;
}

avl_node *avlTree::insert(avl_node *ptr, int value)
{
    if (ptr == nullptr)
    {
        ptr = new avl_node;
		ptr->id = this->id;
		ptr->data = value;
		ptr->left = nullptr;
		ptr->right = nullptr;
		if (this->root == nullptr)
        	this->root = ptr;
		this->id++;
    }
    else if (value < ptr->data)
    {
    	  //cout<<"insert at left"<<endl;
        ptr->left = insert(ptr->left, value);
        ptr = _balance (ptr);
    }
    else if (value >= ptr->data)
    {
        ptr->right = insert(ptr->right, value);
        //cout<<"insert at right, right_data="<<ptr->right->data<<endl;
        ptr = _balance (ptr);
    }

	this->root = ptr;
    return ptr;
}

int avlTree::_height(avl_node *temp)
{
    int h = 0;
	if (temp != nullptr)
    {
        int l_height = _height (temp->left);
        int r_height = _height (temp->right);
		    int max_height = std::max (l_height, r_height);
        h = max_height + 1;
    }

    return h;
}

bool avlTree::_isEmpty()
{
	bool ret = false;
	if (root == nullptr)
	{
		ret = true;
		cout << "AVL tree is empty!" << endl;
	}
	return ret;
}

int avlTree::_diff(avl_node *temp)
{
    int l_height = _height (temp->left);
    int r_height = _height (temp->right);
    int b_factor= l_height - r_height;

    return b_factor;
}

avl_node *avlTree::_balance(avl_node *temp)
{
    int bal_factor = _diff (temp);

    if (bal_factor > 1)
    {
        if (_diff (temp->left) > 0)
            temp = _ll_rotation (temp);
        else
            temp = _lr_rotation (temp);
    }
    else if (bal_factor < -1)
    {
        if (_diff (temp->right) > 0)
            temp = _rl_rotation (temp);
        else
            temp = _rr_rotation (temp);
    }
    return temp;
}

void avlTree::display()
{
	if (_isEmpty())
		return;
	_display(root, 1);
	cout << endl;
}

void avlTree::_display(avl_node *ptr, int level)
{
    int i;
	if (ptr != nullptr)
    {
        _display(ptr->right, level + 1);
        printf("\n");
        if (ptr == root)
        cout<<"Root -> ";
        for (i = 0; i < level && ptr != root; i++)
            cout<<"        ";
        cout<<ptr->data;
        _display(ptr->left, level + 1);
    }
}


avl_node *avlTree::_rr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

avl_node *avlTree::_ll_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

avl_node *avlTree::_lr_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->left;
    parent->left = _rr_rotation (temp);
    return _ll_rotation (parent);
}

avl_node *avlTree::_rl_rotation(avl_node *parent)
{
    avl_node *temp;
    temp = parent->right;
    parent->right = _ll_rotation (temp);
    return _rr_rotation (parent);
}

avl_node *avlTree::find(int val)
{
	return _find(root, val);
}

avl_node *avlTree::_find(avl_node *tree, int val)
{
	avl_node *pCurr = tree;
	if (pCurr == nullptr) {
		cout<<"I can't find it! val("<<val<<") "<<endl;
	} else if(pCurr->data == val) {
		cout<<"(id, val)=("<<pCurr->id<<", "<<pCurr->data<<") "<<endl;
	} else {
		cout<<"hit (id, val)=("<<pCurr->id<<", "<<pCurr->data<<") "<<endl;
		if(pCurr->data < val) {
			pCurr = _find(pCurr->right, val);
		} else {
			pCurr = _find(pCurr->left, val);
		}
	}
	return pCurr;
}

void avlTree::inorder()
{
	if (_isEmpty())
		return;
	cout << "--- inorder traversal ---"<<endl;
	_inorder(root);
	cout << endl << "--- end traversal ---" << endl;
}

void avlTree::preorder()
{
	if (_isEmpty())
		return;
	cout << "--- preorder traversal ---" << endl;
	_preorder(root);
	cout << endl <<"--- end traversal ---" << endl;
}

void avlTree::postorder()
{
	if (_isEmpty())
		return;
	cout << "--- postorder traversal ---" << endl;
	_postorder(root);
	cout << endl << "--- end traversal ---" << endl;
}

void avlTree::_inorder(avl_node *tree)
{
	if (tree == nullptr)
        return;
    _inorder (tree->left);
    cout<<tree->data<<"  ";
    _inorder (tree->right);
}

void avlTree::_preorder(avl_node *tree)
{
	if (tree == nullptr)
        return;
    cout<<tree->data<<"  ";
    _preorder (tree->left);
    _preorder (tree->right);
}

void avlTree::_postorder(avl_node *tree)
{
	if (tree == nullptr)
        return;
    _postorder ( tree ->left );
    _postorder ( tree ->right );
    cout<<tree->data<<"  ";
}
