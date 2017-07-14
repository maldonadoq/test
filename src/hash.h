#ifndef _CHASH_H_
#define _CHASH_H_

#include <iostream>

using namespace std;

template<class T, class F, class E, unsigned s>
class chash{
public:
	E *m_table;
	F m_fd;
	chash(){	this->m_table = new E[s];	}
	bool insert(T *x){
		unsigned id = m_fd(x)%s;
		return this->m_table[id].ins(x);
	}

	bool remove(T *x){
		unsigned id = m_fd(x)%s;
		return this->m_table[id].rem(x);
	}

	bool find(T *x){
		unsigned id = m_fd(x)%s;
		return this->m_table[id].fin(x);
	}

	void print(){
		for(unsigned i=0; i<s; i++){
			cout << "         hash[" << i << "]" << endl;
			cout << "-----------------------------------" << endl;
			this->m_table[i].pri();
		}
	}

	~chash(){	delete []m_table;	}
};

#endif