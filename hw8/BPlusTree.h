/* ASSUMPTIONS:
1. When a node must be split and has an odd number of keys, the extra key will go to the new right-hand node.
2. There will never be a duplicate key passed to insert.
*/

#include <vector>
#include <string>
#include <iostream>

#ifndef DS_BPLUSTREE
#define DS_BPLUSTREE

///////////////////////////////////////////////////////////////////////////////
//DO NOT CHANGE THIS CODE
///////////////////////////////////////////////////////////////////////////////

//Do not implement the class here, this is a forward declaration. Implement at
//the bottom of the .h file
template <class T> class BPlusTree; 

template <class T>
class BPlusTreeNode{
public:
	BPlusTreeNode() : parent(NULL) {};
	bool is_leaf();
	bool contains(const T& key);

	//For grading only. This is bad practice to have, because
	//it exposes a private member variable.
	BPlusTreeNode* get_parent() { return parent; } 

	//We need this to let BPlusTree access private members
	friend class BPlusTree<T>; 
private:
	bool contains(const T& key,std::size_t low,std::size_t high);
	std::vector<T> keys;
	std::vector<BPlusTreeNode*> children;
	BPlusTreeNode* parent;
};

template <class T>
bool BPlusTreeNode<T>::is_leaf(){
	for(unsigned int i=0; i<children.size(); i++){
		if(children[i]){
			return false;
		}
	}
	return true;
}

template <class T>
bool BPlusTreeNode<T>::contains(const T& key){
	return contains(key,0,keys.size()-1);
}

//Private method takes advantage of the fact keys are sorted
template <class T>
bool BPlusTreeNode<T>::contains(const T& key,std::size_t low,std::size_t high){
	if(low>high){
		return false;
	}
	if(low==high){
		return key == keys[low];
	}
	std::size_t mid = (low+high)/2;
	if(key<=keys[mid]){
		return contains(key,0,mid);
	}
	else{
		return contains(key,mid+1,high);
	}
}

///////////////////////////////////////////////////////////////////////////////////////
//Your BPlusTree implementation goes below this point.
///////////////////////////////////////////////////////////////////////////////////////

template <class T>
class BPlusTree {
public:
	//Constructor, Assignment and Copy Constructors, and Destructor
	BPlusTree(int s) : degree(s), root_(NULL){};
	BPlusTree(const BPlusTree<T>& old) : degree(old.degree) {
		if (!old.root_){
			root_ = NULL;
		}
        else root_ = this->copy_tree(old.root_);
    }
    ~BPlusTree(){this->destroy_tree(root_);}

    //borrowed from ds_set file from lab
    BPlusTree<T>& operator=(const BPlusTree<T>& old) {
    	if (!old.root_){
    		root_ = NULL;
    	}
        else if (&old != this) {
            this->destroy_tree(root_);
            root_ = this->copy_tree(old.root_);
            degree = old.degree;
        }
        return *this;
    }


    //Print functions
    void print_sideways(std::ostream& os) const {print_sideways(os, this->root_);}
    void print_BFS(std::ostream& os) const;

    //Member functions
	BPlusTreeNode<T>* find(const T& key) const {return find(key, root_); }
	void insert(const T& value) {return insert(value, NULL, root_);}

private:
	//Representation
	int degree;
	BPlusTreeNode<T>* root_;
	
	//PRIVATE HELPER FUNCTIONS

	//This function finds a node for a given value, regardless if it is in the tree or not. If tree is empty, return NULL
	BPlusTreeNode<T>* find(const T& value, BPlusTreeNode<T>* current) const {
		if (!root_) return NULL;

		//goes through every single key, each time checking if the given value is larger than the
		//key, so we can use later on to traverse the tree
		unsigned int child_index = 0;
		for (unsigned int i = 0; i < current->keys.size(); i++) {
			if (value >= current->keys[i]) {
				child_index = i+1;
			}

		}
		//checks to see if the node reaches a leaf and hasn't found the value
		int less_than = 0;
		if (current->is_leaf() && child_index < current->keys.size()) {
			less_than += 1;
			return current;
		}

		//if the node reaches leaf node and hasn't found the value
		if (child_index < current->keys.size() && current->is_leaf()) return current;
		//if we haven't reached the leaf node, the node could still be somewhere to the left
		if (child_index < current->keys.size()) return find(value, current->children[child_index]);
		//the node could be somewhere to the right
		if (less_than == 0){
			if (current->is_leaf()) return current;
			return find(value, current->children[child_index]);
		}
		//if node reaches leaf
		if (current->is_leaf()) return current;
	}

	// This function inserts a given value into a node in the list, if neccessary, will split
	//nodes that become full from the insertion
	void insert(const T& value, BPlusTreeNode<T>* parent_ , BPlusTreeNode<T>*& current){
		//Checks if the tree is empty first
		if (!root_){
			root_ = new BPlusTreeNode<T>();
			root_->keys.push_back(value);
			return;
		}
		//if the recursive function reaches a leaf node, we insert the value
		else if (current->is_leaf()){
			unsigned int i= 0;
			///finds the ith index to add the value into the sorted vector
			while (i < current->keys.size()){
				//if value is smaller than the first value of the vector
				if (i==0 && value < current->keys[i]) break;
				//if we reach the end of the vector
				if (i+1 == current->keys.size()){
					if (value < current->keys[i]){
						break;
					}
					else{
						i += 1;
						break;
					}
				}
				//if we found the correct spot to add the value into the vector
				if (value > current->keys[i] && value < current->keys[i+1]) {
					i += 1;
					break;
				}
				i += 1;
			}
			//insert the key value into the keys vector in sorted order
			current->keys.insert(current->keys.begin() +i, value);
/*
i originally didn't have this if statement, because if i splitted the node down below, i thought it would account for every nodes being full and split it,, but apparently it didn't account
for nodes that are root. which is why i wrote this if statement here. 
*/


			//if after adding the keys, the root becomes full
			if (current == root_ && current->keys.size() >= degree){

				//find the end index of the first node, and the start of the second node
				int first_split_end = (current->keys.size()/2)-1;
				int second_split_start;
				//start index of second node varies whether the node is leaf or not
				current->is_leaf() ? second_split_start = first_split_end +1 : second_split_start = first_split_end + 2;

				//create a new node that is going to split the overloaded one
				BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
				//transfer the second half of the elements in the overloaded node into the new one
				int count = 0;
				for (unsigned int j= second_split_start; j<current->keys.size(); ++j){
					newNode->keys.push_back(current->keys[j]);
					count += 1;
				}

				//find the middle value that will be moved into the parent node later
				T up_value = current->keys[(current->keys.size()/2)];

				int leaf_popback = 0;
				//delete the elements that have been added into the new node
				for (unsigned int j=0; j<count; ++j){
					if (leaf_popback == 0 && !current->is_leaf()) {
						current->keys.pop_back();
						leaf_popback++;
					}
					current->keys.pop_back();
				}

				//divide the children nodes between the current and newly created node (child of the new root)
				if (current->is_leaf() == false){
					while (newNode->children.size() < newNode->keys.size() +1){
						newNode->children.insert(newNode->children.begin(), current->children.back());
						current->children.pop_back();
					}
				}

				//create a new node that will be the new root
				BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>();
				new_root->keys.push_back(up_value);
				new_root->children.insert(new_root->children.begin(), newNode);
				new_root->children.insert(new_root->children.begin(), current);

				newNode->parent = new_root;
				current->parent = new_root;

				this->root_ = new_root;
			}
		}
		//If the tree is not empty and we haven't reached leaf node, we traverse the tree
		else if (root_ != NULL && current->is_leaf() == false) {
			/*
		what I originally had for check was that I would do a while loop that does while i < current->keys.size() && check == 0,
		if I check that the value is larger than the last index of the vector, then I will set i to the last element of the vector, call the function recursively and do check +=1 so that
		we don't need to go over the entire while loop. however, with the whole recursion think, when I used gdb, i found out that the check variable was not able to cancel the while loop since
		it keeps going back to the previous recursive function and that previous recursive function did not have check incremented, making the while loop goes on and on. 

		from then, i thought of the inserted
		variable, i'd put it inside the while loop, so that it's always 0 at the start of the loop, each time we CALL a recursive function, then that means what that recursive function is finished,
		we should break out of the while loop. my check variable wasn't able to do that. so as you can see at the bottom, i have the line that checks if inserted is over 0, and if so we break the while
		loop.

			*/
			int check =0;
			unsigned int i =0;
			while ( i<current->keys.size()){
				int inserted =0;
				//if the inserted value is smaller than the value in the current node,
				//we should go down to the child node with the same i value
				//of that value in the keys vector
				if (value < current->keys[i]){
					insert(value, current, current->children[i] );
					inserted += 1;
				}
				//if value is larger than all keys value in the node
				else if (value > current->keys.back()){
					check += 1;
					i = current->keys.size();
					insert(value, current, current->children[i]);
					inserted += 1;
				}
				/*
			anyways, the code after line 270 (this part) is when we have successfully inserted the value into the child node which would be accounted for with the if statement above that i already explained.
			after that is done, i would go back to the previous recursive function, which means that i would be currently on a node that is the parent of the leaf node that has the added element. since
			i still have the i index, i would check if the node that I added is now full. 
				*/

				//after adding the element into the leaf node recursively, we check if
				//that node is now full. If it is we will split it
				if (current->children[i]->keys.size() >= degree){

					/*
				if the node is full, i will now split the node, which i heavily relied on the b+ plus visualization website you gave us. on that website, i noticed when
				splitting a node, it is different if the node is a leaf node or not. for a leaf node, let's say the node has 1,2,3,4 in it, then we will split 3 and 4 to the right node, making
				3 into the parent node. however, if it's not a leaf node, we would only split 4 into the right node, and move 3 into the parent node. we can safely know that the newly splitted left node
				will always remain the same, which i calculated is from index 0 to one index less than the middle index of the vector.  which you can see is what i have done here

				then, depending on if it is a leaf node or not, the second node that will be splitted will contain either 1 or 2 index after the last element of the first node. 
				from then, i created a newnode, using my second_split_start variable i calculated, i would transfer all the elements at that position into the new one.

				each time i increment the count variable so that later on, i will pop_back the elements that much time to correctly erase the elements that i have transferred.
				since the value that goes into the parent node will always be the same, we just calculate with the size of keys divide by 2 and floor it. 


					*/

					int first_split_end = (current->children[i]->keys.size()/2)-1;
					int second_split_start;
					current->children[i]->is_leaf() ? second_split_start = first_split_end +1 : second_split_start = first_split_end + 2;

					BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
					//transfer the second half of the elements in the overloaded node into a new one
					int count = 0;
					for (unsigned int j= second_split_start; j<current->children[i]->keys.size(); ++j){
						newNode->keys.push_back(current->children[i]->keys[j]);
						count += 1;
					}

					//find the middle value that will be moved into the parent node later
					T up_value = current->children[i]->keys[(current->children[i]->keys.size()/2)];
					if (current->children[i]->is_leaf() == false) current->children[i]->keys.pop_back();


					//delete the elements that have been added in to the new node
					for (unsigned int j=0; j<count; ++j){
						current->children[i]->keys.pop_back();
					}
				/*
				i originally did not set newnode parent as current, which was when I ran the program, i got a seg fault, it took me really long to figure it out.
				but i had to use gdb and set a breakline before the seg fault, and from then, i wouldn't increment the program. i would literally print out all the information i could get,
				starting from my roots. i'd print the keys in my root, and the keys of its children. i would go down to each children, checking their keys and their children keys as well. i then
				realized that the node that i splitted, it did not have enough children nodes as it should've, and that was when i realized i didn't set the newly created node as its child and the 
				current node as its parents. 
				*/
					newNode->parent = current;
					
					/*
					from here, when i split the node, i now have to move the middle value into the parent node. originally, i tried to create a different variable called j, i would then
					go through all keys vector of the current node, and check if variable up_value is smaller than the first index, larger than the last index, or is somewhere in the node. however,
					for some reason, i kept getting a seg fault and gdb was not working at all, i even got the correct j value to insert.

					it then took me a solid 2-3 hours to realize that i am still in a while loop, as this whole recursion thing was really confusing for me, i realized that since i traversed down the
					ith index of my child node, that ith index perfectly corresponds to the middle value of its child node. I had to use b+ tree visualization for this and a lot of thinking as well. 

					and since the ith index corresponds to the index of the child node of the current node, since i created the new node, that node should be the the child node of the ith index to the 
					RIGHT of the current ith child node. 
					*/
					current->keys.insert(current->keys.begin()+i, up_value);
					++i;
					current->children.insert(current->children.begin()+i, newNode);

		            // If current node is the root and it is full
			        if (current == root_ && current->keys.size() >= degree){

						//find the end index of the first node, and the start of the second node
						int first_split_end = (current->keys.size()/2)-1;
						int second_split_start;
						//start index of second node varies whether the node is leaf or not
						current->is_leaf() ? second_split_start = first_split_end +1 : second_split_start = first_split_end + 2;

						//create a new node that is going to split the overloaded one
						BPlusTreeNode<T>* newNode = new BPlusTreeNode<T>();
						//transfer the second half of the elements in the overloaded node into the new one
						int count = 0;
						for (unsigned int j= second_split_start; j<current->keys.size(); ++j){
							newNode->keys.push_back(current->keys[j]);
							count += 1;
						}

						//find the middle value that will be moved into the parent node later
						T up_value = current->keys[(current->keys.size()/2)];

						int leaf_popback = 0;
						//delete the elements that have been added into the new node
						for (unsigned int j=0; j<count; ++j){
							if (leaf_popback == 0 && !current->is_leaf()) {
								current->keys.pop_back();
								leaf_popback++;
							}
							current->keys.pop_back();
						}

						//divide the children nodes between the current and newly created node (child of the new root)
						if (current->is_leaf() == false){
							while (newNode->children.size() < newNode->keys.size() + 1){
								newNode->children.insert(newNode->children.begin(), current->children.back());
								current->children.pop_back();
							}
						}

						//create a new node that will be the new root
						BPlusTreeNode<T>* new_root = new BPlusTreeNode<T>();						

						new_root->keys.push_back(up_value);
						new_root->children.insert(new_root->children.begin(), newNode);
						new_root->children.insert(new_root->children.begin(), current);

						newNode->parent = new_root;
						current->parent = new_root;
						this->root_ = new_root;
			   		}
			   		
				}
				if (inserted > 0) break;
				++i;
			}
		}
	}

	//This function will print all the contents inside the tree sideways
	void print_sideways(std::ostream& os, BPlusTreeNode<T>* current) const {
	    // If tree is empty, simply state so in the file
		if (!root_){
			os << "Tree is empty." << std::endl;
			return;
		}

		//Split the children nodes into two groups, finding the index 
		//of when the left group ends and the start of the right group
	    unsigned int left_end = (current->children.size()/2)-1;
	    unsigned int right_start = left_end + 1;

	    /*
		i actually had this function going through the right side of the children nodes first, since i thought were should print the right side, 
		which makes sense and i didn't read the output correctly. after i ucompared it with the given output, i realized it was the left side that is
		printed first.
	    */

	    /*
		so based on the given output txt file, i see that we have to print the key that is at the very bottom level all the way to the left. to do that, i would have to 
		have a recursive function that traverse all the way down to the leftmost node of the tree and print the keys. 

		to go to the leftmost bottom node from the root node of the tree, i would have to check if time if the current node is a leaf node or not. if it not, i will have a 
		for loop that goes through the left side keys, always starting at 0. and since it always starts at 0, the first time calling this function, the first thing this function will 
		do is recursively go down to the first child of every node starting from the root.

		lets say we start at the root, with the for loop, id go down to the first child of the root node, then checks if the that node is leaf or not, if not then i go down again 
		to the first child node. based on the output, i'd only go down twice until i reach the leaf node.
	    */

	    //if we still have to traverse down into the left side of our tree, we will do so recursively
	    if (!current->is_leaf()){
		    for (unsigned int i=0; i<=left_end; ++i){
		    	print_sideways(os, current->children[i]);
		    }
		}

		/*
		after i reach the leaf node, i create a new tmp node that will be used to identify the level of the tree, since i will need to know its level in order to print.
		to do that, i simply iterate the tmp node, each time setting the tmp node into its parent, until the tmp node reaches the root node where it has no more parent. each time i do that,
		i add level by 1 and that will give me the correct level i need for printing.
		*/

		//calculate the level the node is on for output
		BPlusTreeNode<T>* tmp = current;
		int levels = 0;
		while (tmp->parent){
			if (tmp->parent) {
				tmp = tmp->parent;
				levels += 1;
			}
		}
/*as you can see here, i output as much tabs there is corresponding to the level, the deeper the node is, the more level it has and the more tabs it gets printed. */
		os << std::string(levels,'\t');

		//print the keys of the current node
		for (unsigned int i=0; i<current->keys.size(); ++i) {
			if (i+1 == current->keys.size()){
				os << current->keys[i] << std::endl;
				break;
			}
			os << current->keys[i] << ',';
		}

		//next we will traverse down the right side of our tree
		if(!current->is_leaf()){
			for (unsigned int i=right_start; i<current->children.size(); ++i){
				print_sideways(os, current->children[i]);
			}
		}
	}

	//Helper function for class destructor
	void destroy_tree(BPlusTreeNode<T>* current) {

/*
i actually based this function off of an online destructor for a binary search tree, since we are not doing a BST, i'd assume that it is fine.
based on the code i saw on stackoverflow, its been a while, but i remember that its destructor had a while loop, checking each time if the current
node is not null, if not then it recursively calls the function to the left and to the right. something like :
destroy_tree(current->left);
destroy_tree(current->right);

since our assignment doesn't have that, to go through all the children nodes, i would have a for loop that goes through all of them and each time recursively call the function.

the code on stack overflow will delete the current node after the recursive function of destroy_tree(current-right), which is what i did exactly as you can see here. and the else statement
is when we have reached a child of a leaf node, which is invalid in that case we simply return the function and go back to the previous node we were at. 
*/

		//if the current node is not NULL, we go through all of its children,
		//each time deleting them
		if (current){
			for (unsigned int i=0; i<current->children.size(); ++i){
				destroy_tree(current->children[i]);
			}
			delete current;
		}
		else{
			return;
		}
	}

	//Helper function for assignment/copy constructor
	BPlusTreeNode<T>* copy_tree(BPlusTreeNode<T>* original_tree) {
/*
So I have included a reference i used in my README file, which was a code on stackoverflow that showed a copy constructor for a binary search tree.
I assumed that is allowed as well.

As you can see from the stackoverflow code, the code simply had a few recursion calls. it first creates a new node, and transfers all the values from the copy node
to the current node. it then recursively calls the function, iterating the node to the left and to the right. 

so if you look at my code, it is basically the same idea. I create a new node called answer, i first check if it is a root or not. if it is, i simply transfer all the values
from the copy node to the new node. after that, i start my recursion. as you can see, my recursion calls is almost the same with the stackoverflow's the only difference is the for loop 
since we are doing a B+ tree, where i recursively call all the children nodes, every time i do that, i would transfer all the keys at that current copy node to this node. after iterating through 
all the children nodes, i return that node to the previous recursive node, which at the end should copy everything. 
*/


		//create a node that will hold all the values of the old tree and return it
		BPlusTreeNode<T>* answer = new BPlusTreeNode<T>();
		//first case, if we are currently at the root, we copy all the keys into the answer node
	    if (!original_tree->parent){  
		    for (unsigned int i=0; i<original_tree->keys.size(); ++i){
		    	answer->keys.push_back(original_tree->keys[i]);
		    }
		}

		//goes through every single children nodes recursively, each time copying its
		//keys and parent
	    for (unsigned int i=0; i<original_tree->children.size(); ++i){
	    	copy_tree(original_tree->children[i]);
	    	/*
			i originally had a for loop that goes through the keys vector, each time push_back it into the answer node. after looking at the code on stackoverflow,
			i realized i couldve just simply used the = operator to transfer them correctly.
	    	*/
	    	answer->keys = original_tree->keys;
	     	answer->parent = original_tree->parent;

	    } 
	    return answer;
	}

};

//This function prints all values at a corresponding level it is at on the tree
template <class T>
void BPlusTree<T>::print_BFS(std::ostream& os) const {
	//https://www.youtube.com/watch?v=VsxLHGUqAKs (3:45)

    // Check: If tree is empty
    if (!root_) {
        os << "Tree is empty." << std::endl;
        return;
    }

    //create a stack that holds all the nodes that we are travelling through
    std::vector<BPlusTreeNode<T>*> stack;
    stack.push_back(root_);

    //while we have not yet covered all the nodes in the tree
    while (stack.size() > 0){
    	//save the original size of the stack and create a temporary stack
    	int original_size = stack.size();
    	std::vector<BPlusTreeNode<T>*> tmp_stack;

    	//goes through the current stack with the current nodes
    	for (unsigned int i=0; i<stack.size(); ++i){
    		//prints out the keys of the current node on the stack
    		for (unsigned int j=0; j<stack[i]->keys.size(); ++j){
    			//if we're at the last key element, we will not print ','
    			if (j+1 == stack[i]->keys.size()){
    				os << stack[i]->keys[j];
    				break;
    			}
    			os << stack[i]->keys[j] << ',';
    		}
    		//if we reach the last node on the stack, we print a line break
    		if(i+1 == stack.size()) {
    			os << std::endl;
    			break;
    		}
    		os << '\t';
    	}
    	//after printing all the keys of the current nodes, we add all the children
    	//nodes of our current nodes into a temporary stack
    	for (unsigned int i=0; i<stack.size(); ++i){
    		//goes through every children of the nodes in the stack and add it
    		for (unsigned int j=0; j<stack[i]->children.size(); ++j){
    			tmp_stack.push_back(stack[i]->children[j]);
    		}
    	}
    	//clear the original stack and set that equal to the new one filled with new child nodes
    	stack.clear();
    	//transfer all elements in tmp_stack to original stack
    	stack = tmp_stack;
    	tmp_stack.clear();
    }
}

#endif
