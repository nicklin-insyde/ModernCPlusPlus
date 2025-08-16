#ifndef TREE_H
#define TREE_H
 
/*
 * Node Declaration
 */
struct avl_node
{
	int id;
    int data;
    struct avl_node *left;
    struct avl_node *right;
};

void test_func();
 
/*
 * Class Declaration
 */
class avlTree
{
public:	
	avlTree();

  void insert(int value);
  avl_node *insert(avl_node *, int);
  void display();
  void pop_root();   
  
  avl_node *find(int val);

  void inorder();
  void preorder();
  void postorder();

private:
	static int id;
	bool _isEmpty();

	int _diff(avl_node *);
	int _height(avl_node *);
	void _display(avl_node *, int);
	avl_node *_find(avl_node *, int);
	avl_node* _balance(avl_node *);
	avl_node *_rr_rotation(avl_node *);
	avl_node *_ll_rotation(avl_node *);
	avl_node *_lr_rotation(avl_node *);
	avl_node *_rl_rotation(avl_node *);

	void _inorder(avl_node *);
	void _preorder(avl_node *);
	void _postorder(avl_node *);

//protected:
	avl_node *root;
};
#endif
