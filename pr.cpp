#include <iostream>
#include <stdio.h>

using namespace std;

template<class T>
class cmp{
public:
	inline bool operator()(T x, T y){	return x<y;	}
};

template<class T>
class node{
public:
	node<T> *m_next;
	T m_dato;
	node(T x){
		this->m_dato = x;
		this->m_next = NULL;
	}
};

template<class T, class R>
class lista{
private:
	R cmp;
	node<T> *m_root;
public:
	lista(){	this->m_root = NULL;	}
	bool find(T, node<T> **&);
	bool insert(T);
	bool remove(T);
	void swap_b(node<T> **&, node<T> **&);
	void bubble_sort();
	void print();
};

template<class T, class R>
bool lista<T,R>::find(T x, node<T> **&p){
	for(p=&(m_root); *p and (*p)->m_dato!=x; p=&((*p)->m_next));
	return !!*p;
}

template<class T, class R>
bool lista<T,R>::insert(T x){
	node<T> **p = &(this->m_root);
	node<T> *t = this->m_root;
	*p = new node<T>(x);
	(*p)->m_next = t;
	return true;
}

template<class T, class R>
bool lista<T,R>::remove(T x){
	node<T> **p;
	if(!find(x,p))	return false;
	node<T> *t = *p;
	*p = (*p)->m_next;
	delete t;
	return true;
}

template<class T, class R>
void lista<T,R>::swap_b(node<T> **&p, node<T> **&r){
	if(p==r)	return;
	node<T> *w = *p;
	*p = *r;
	*r = (*p)->m_next;
	(*p)->m_next = w;
}

template<class T, class R>
void lista<T,R>::bubble_sort(){
	node<T> **p, **q, **r;
	for(p=&(m_root); (*p)->m_next; p=&((*p)->m_next)){
		for(r=p, q=&((*p)->m_next); *q; q=&((*q)->m_next)){
			if(cmp((*q)->m_dato,(*r)->m_dato))	r=q;
		}
		swap_b(p,r);
	}
}

template<class T, class R>
void lista<T,R>::print(){
	node<T> *t = this->m_root;
	while(t){
		cout << t->m_dato << " ";
		t = t->m_next;
	}
	cout << endl;
}

int main(int argc, char const *argv[]){
	lista<int, cmp<int>> *a = new lista<int,cmp<int>>();
	int t = 10;
	srand(time(NULL));
	for(int i=0; i<t; i++)	a->insert(rand()%t);
	a->print();
	a->remove(4);
	a->print();
	a->bubble_sort();
	a->print();
	return 0;
}

/*
string cad = "ABCD";
    vector<string> nod;
    unsigned cn = 0;
    do{
        a->insert_node(cad);
        nod.push_back(cad);
        cn++;
    }while(next_permutation(cad.begin(),cad.end()));
    cout << "nodos: " << cn << endl;
    srand(time(NULL));
    for(unsigned i=0; i<nod.size(); i++)
        a->insert_edge(rand()%10, nod[rand()%nod.size()], nod[rand()%nod.size()], 1);
    /*a->insert_node(65);    a->insert_node('B');
    a->insert_node('C');    a->insert_node('D');
    a->insert_node('E');    a->insert_node('F');
    a->insert_node('G');    a->insert_node('H');
    a->insert_node('I');    a->insert_node('J');

    a->insert_edge(2,'A','B',0);    a->insert_edge(4,'A','C',0);
    a->insert_edge(5,'B','E',0);    a->insert_edge(6,'B','D',0);
    a->insert_edge(3,'C','B',0);    a->insert_edge(2,'C','D',0);
    a->insert_edge(4,'D','E',0);    a->insert_edge(1,'D','A',0);
    a->insert_edge(6,'C','E',0);    a->insert_edge(9,'F','E',0);
    a->insert_edge(3,'G','D',0);    a->insert_edge(2,'G','H',0);
    a->insert_edge(2,'J','E',0);    a->insert_edge(6,'J','B',0);
    a->insert_edge(7,'F','C',0);    a->insert_edge(1,'I','E',0);*/
    //a->print();
    //string del = nod[rand()%nod.size()];
    //cout << endl << "delete " << del << ":   " << a->remove_node(del) << endl << endl;
    //a->print();
    //a->dijkstra("ABC","ACB");
*/