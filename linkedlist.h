//barbara de Graaf
//026587139
//DSA555 Assignment 1
//Part B
//double linked list

#include <iostream>
#include <string>
using namespace std;
template <class T>
class LinkedList{
	struct Node{
		string key_;
		T value_;
		Node* next_;
		Node* prev_;

		Node(const string& key="", const T& value=T(), Node* next=nullptr, Node* prev=nullptr){
			key_ = key;
			value_=value;
			next_=next;
			prev_=prev;	
		}
	};

	Node* first_;
	Node* last_;

public:
	//Two iterator classes below
	///////////////////////////
	class const_iterator{
	friend LinkedList<T>;
//	protected:
	public:
		Node* cur_;
//	public:
		const_iterator(){
			cur_=nullptr;
		}
		const_iterator(Node* p){
			cur_ = p;
		}
		const_iterator operator++(){ //post
			cur_=cur_->next_;
			return *this;
		}
		const_iterator operator++(int){ //pre
			const_iterator o = *this;
			cur_=cur_->next_;
			return o;
		}
		bool operator==(const_iterator other){
			return cur_==other.cur_;
		}
		bool operator!=(const_iterator other){
			return cur_!=other.cur_;
		}
		const std::string& operator*() const{
			return cur_->key_;
		}
	};
	
	class iterator : public const_iterator{
	friend LinkedList<T>;
	public:
		iterator():const_iterator(){} //call base class
		iterator(Node* p):const_iterator(p){} //call the base class
		iterator operator++(){ //post
			this->cur_=this->cur_->next_;
			return *this;
		}
		iterator operator++(int){ //pre
			iterator o = *this;
			this->cur_=this->cur_->next_;
			return o;
		}
		bool operator==(iterator other){
			return this->cur_==other.cur_;
		}
		bool operator!=(iterator other){
			return this->cur_!=other.cur_;
		}
		const std::string& operator*() const{
			return this->cur_->key_;
		}
		std::string& operator*() {
			return this->cur_->key_;
		}
	};
	////////////////////////////////////
	//back to sorted list
	//sorted list functions
	//ctor
	LinkedList(){
		first_=new Node;
        	last_=new Node;
        	first_->next_=last_;
        	last_->prev_=first_;
	}
	//dtor
        ~LinkedList(){
        	while (first_){
        	 	Node* temp= first_->next_;
        	        delete first_;
			first_ = temp;
       		 }
	}
	//assignment optr, delte everything and then copy the other info over
        LinkedList& operator=(const LinkedList& other){
		if (this != &other){
			//delete all first and then add the others
			while (first_->next_){
                        	Node* temp= first_->next_;
                        	delete first_;
                        	first_ = temp;
                 	}	
		
			first_=new Node;
                	last_=new Node;
                	first_->next_=last_;
                	last_->prev_=first_;

			for (const_iterator i=other.begin(); i!=other.end(); i++){	
                	        insert(i.cur_->key_, i.cur_->value_);
                	}
                }
                return *this;

	}
	//copy ctor create the new nodes and then call insert
        LinkedList(const LinkedList& source){
		first_=new Node;
                last_=new Node;
                first_->next_=last_;
                last_->prev_=first_;
 		for (const_iterator i=source.begin(); i!=source.end(); i++){
                	insert(i.cur_->key_, i.cur_->value_);
                }
        }
	//
        bool insert(std::string key, const T& value){
		iterator temp;
                Node* curr = first_;
                Node* prev = first_;
                Node* next = last_;
		bool found =false;	
		bool uporin = false;
		//while going through and the data to put is larger than ones going through
                while(curr!=last_ && found == false){
			if (curr->key_ == key){
				curr->value_ = value;
				uporin = true;
				found = true;
			}
			if (found == false) curr = curr->next_;
                }
		if (found == false){
		//storing prev and next nodes based on above 
		prev = curr->prev_;
                next = curr;

		//create a new node with the values and then set the prev and next nodes of 
		//ones next and prev to the new node

                Node* nn=new Node(key, value ,next,prev);;
                prev->next_ = nn;
                next->prev_ = nn;

                temp = nn->next_;
		uporin = true;
		}
                return uporin;
	}
	iterator find(string key, bool& found){
		iterator temp;
		Node* cur_ = first_;
		while(cur_!= last_ && found == false){
			if (cur_->key_ == key)
				found = true;
			if (found == false)cur_ = cur_ -> next_;
		}
		temp = cur_;
		return temp;
	}
		
	//remove by iterating though and if found value erase it 
	bool remove(string key){
		for (iterator i=begin(); i!=end(); i++){
			if (i.cur_->key_ == key){
				erase(i);
				return true;
			}
		}
		return false;
	}
	
	//store the cur, prev and next nodes of the iterator pased in
	iterator erase(iterator i1){
		Node* temp = i1.cur_;
		Node* tprev = temp->prev_;
		Node* tnext = temp->next_;

		iterator iter(tnext);

		//if the prev is not the nullptr then the prev's next will be next
		if ( tprev != nullptr){
			tprev->next_= tnext;
		}else 
		//otherwise it the first's next that is next
			first_->next_ = tnext;

		//same logic as above for next's
		if (tnext != nullptr){
			tnext->prev_ =tprev;
		}else
			last_ = tprev;

		delete temp;
		return iter; 
	}
	//go though for loop from iterartor 1 to 2 calling erase on each one
        iterator erase(iterator i1, iterator i2){
		for( iterator itr = i1; itr != i2; itr++ )
            		erase( itr );

        	return i2;	
	}
	//begin starts after the first
	iterator begin() {return iterator(first_->next_);}
	//last is the last node since that is after useful nodes
	iterator end(){return iterator(last_);}
	const_iterator begin() const {return const_iterator(first_->next_);}
	const_iterator end() const {return const_iterator(last_);}	
};
