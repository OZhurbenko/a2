#include <string>
#include <utility>
#include <iostream>
#include "linkedlist.h"

template <class TYPE>
class Table{
public:
	Table(){}
	Table(const Table& other){}
	virtual bool update(const char* key, const TYPE& value)=0;
	virtual bool remove(const char* key)=0;
	virtual bool find(const char* key, TYPE& value)=0;
	virtual int numRecords()  =0;
	virtual const Table& operator=(const Table<TYPE>& other){return *this;}
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{
	std::pair<std::string, TYPE>* data;
	int table_size;
	int max;
public:
	SimpleTable(int maxExpected);
	SimpleTable(const SimpleTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int numRecords();
	virtual const SimpleTable& operator=(const SimpleTable& other);
	virtual ~SimpleTable();
};
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int maxExpected): Table<TYPE>(){
	data = new std::pair<std::string, TYPE>[maxExpected];
	max = maxExpected;
	table_size =0;
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& other){
//copy ctor
	data = new std::pair<std::string, TYPE>[other.max];
	max = other.max;
	table_size = other.table_size;

	for (int i=0; i<=table_size; i++){
		data[i] = other.data[i];
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::update(const char* key, const TYPE& value){
	if (table_size == max){
		max = max*2;
		std::pair<std::string, TYPE>* tmp = new std::pair<std::string, TYPE>[max];
		for (int i=0; i<=table_size; i++){
			tmp[i] = data[i];
		}
		delete [] data;
		data = new std::pair<std::string, TYPE>[max];
		data = tmp;
	}
	bool uporin = false;
	std::string k(key);
	for (int i=0; i<=table_size && uporin == false; i++){
		
		if (data[i].first == k){
			data[i].second = value;
			uporin = true;
		}
		else if (data[i].first > k || i == table_size){
			for (int j=table_size; j>i; j--){
				data[j] = data[j-1];
			}
			data[i] = std::make_pair(k, value);
			table_size ++;
			uporin = true;
		}
	}
		
	return uporin;
}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const char* key){
	
	bool removed = false;
	std::string k(key);
	for (int i=0; i<=table_size && removed == false; i++){
		if (data[i].first == k){
			for (int j=i; j<=table_size; j++){
				data[j] = data[j+1];
			}
			table_size--;
			removed = true;
		}
	}
	return removed;
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const char* key, TYPE& value){
	bool found = false;
	std::string k(key);
	
	for (int i=0; i<=table_size && found == false; i++){
		if (data[i].first == k){
			found = true;
			value = data[i].second;
		}
	}
	return found; 
}

template<class TYPE>
int SimpleTable<TYPE>::numRecords(){
	return table_size;
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& other){
	if (this != &other){
		max = other.max;
		table_size = other.table_size;
		delete [] data;
		data = new std::pair<std::string, TYPE>[max];
		for (int i=0; i<=table_size; i++){
			data[i] = other.data[i];
		}
	}
	return *this;

}

template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	delete [] data;
}

template <class TYPE>
class HashTable:public Table<TYPE>{

	LinkedList<TYPE>* data;
	int max;
	int tablesize;

public:
	HashTable(int maxExpected);
	HashTable(const HashTable& other);
	virtual bool update(const char* key, const TYPE& value);
	virtual bool remove(const char* key);
	virtual bool find(const char* key, TYPE& value);
	virtual int numRecords();
	virtual const HashTable& operator=(const HashTable& other);
	virtual ~HashTable();
};
/* none of the code in the function definitions below are correct.  You can replace what you need
*/
template <class TYPE>
HashTable<TYPE>::HashTable(int maxExpected): Table<TYPE>(){
	data = new LinkedList<TYPE>[maxExpected];
	max = maxExpected;
	tablesize =0;
}

template <class TYPE>
HashTable<TYPE>::HashTable(const HashTable<TYPE>& other){
	data = new LinkedList<TYPE>[other.max];
	
	//data = other.data;
	max = other.max;
	for (int i=0; i<max; i++){
		data[i] = other.data[i];
	}		
	tablesize=other.tablesize;
	
}

template <class TYPE>
bool HashTable<TYPE>::update(const char* key, const TYPE& value){
	bool uporin = false;

	if (tablesize == max){
		std::cout<<"HERE"<<std::endl;
//		max = max*1.5;
//		LinkedList<TYPE>* tmp;
//		tmp  = new LinkedList<TYPE>[max];
//		for (int i=0; i<tablesize; i++){
//			tmp[i] = data[i];
//			//delete data[i]
//		}
	//	delete [] data;
	//	data = new LinkedList<TYPE>[max];
	//	data = tmp;
	
	}
	std::string k(key);
	std::hash<std::string> hashfn;
	std::size_t hashvalue = hashfn(k);
	hashvalue = hashvalue%10000;
	uporin = data[hashvalue].insert(k, value);
	tablesize++;

	return uporin;
}

template <class TYPE>
bool HashTable<TYPE>::remove(const char* key){
	bool found = false;
	std::string k(key);
	std::hash<std::string> hashfn;
	std::size_t hashvalue = hashfn(k);
	hashvalue = hashvalue%10000;
		
	auto temp = data[hashvalue].find(k, found);
	
	if (found == true){
		data[hashvalue].erase(temp);
		return true;
	}
	return false;
	


}

template <class TYPE>
bool HashTable<TYPE>::find(const char* key, TYPE& value){
	bool found = false;	
	std::string k(key);	
	std::hash<std::string> hashfn;
	std::size_t hashvalue = hashfn(k);
	hashvalue = hashvalue%10000;
	
	auto temp = (data[hashvalue].find(k, found));
	if (found == true)
		value = temp.cur_->value_;
	return found;
}

template<class TYPE>
int HashTable<TYPE>::numRecords(){
	return tablesize;
}

template <class TYPE>
const HashTable<TYPE>& HashTable<TYPE>::operator=(const HashTable<TYPE>& other){
	if (this != &other){
		delete [] data;
		data = new LinkedList<TYPE>[other.max];
	
		max = other.max;
		for (int i=0; i<max; i++){
			data[i] = other.data[i];
		}		
		tablesize=other.tablesize;
	}
	return *this;
}
	
template <class TYPE>
HashTable<TYPE>::~HashTable(){
	delete [] data;
}

