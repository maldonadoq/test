#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "src/node.h"

using namespace std;

int main(int argc, char const *argv[]){
	dnode<int> *a = new dnode<int>(0);
    cout << "head: " << a << endl;
    
    cout << "pointer a->m_node[1]: " << a->m_node[1] << endl;
    cout << "pointer a->m_node[0]: " << a->m_node[0] << endl;

    dnode<int> **p = &(a->m_node[1]);
    dnode<int> *r = a->m_node[1];
    cout << "pointer p: " << *p << endl;
    cout << "pointer r: " << r << endl;

    dnode<int> *n = new dnode<int>(0);
    dnode<int> *t = *p;
    cout << "pointer t: " << t << endl;
    *p = n;
    cout << "pointer n: " << n << endl;
    cout << "pointer p: " << *p << endl;
    cout << "pointer a->m_node[1]: " << a->m_node[1] << endl;
    cout << "pointer t: " << t << endl;

    n->m_node[1] = t;
    n->m_node[0] = r;
    cout << "pointer n->m_node[1]: " << n->m_node[1] << endl;
    cout << "pointer n->m_node[0]: " << n->m_node[0] << endl;

    cout << "pointer a->m_node[1]: " << a->m_node[1] << endl;
    cout << "pointer a->m_node[0]: " << a->m_node[0] << endl;

    p = &(a->m_node[1]);
    r = a->m_node[1];
    cout << "pointer p: " << *p << endl;
    cout << "pointer r: " << r << endl;

	return 0;
}	


/*
//dlista<int, cml<int>> *a = new dlista<int, cml<int>>();
    int t, tt=50;
    double pr1=0, pr2, sw1, sw2;
    cout << "tamaño: "; cin >> t;
    for(int i=0; i<tt; i++){
        clista<int, cml<int>> *a = new clista<int, cml<int>>();
        list_circle<int> *b = new list_circle<int>();
        sw1 = (time_insert<clista<int,cml<int>>, int>(a,t)/1000);
        sw2 = (time_insert<list_circle<int>, int>(b,t)/1000);
        //cout << i << ": " << (double)sw << endl;
        pr1+=sw1;
        pr2+=sw2;
        delete a; delete b;
    }
    cout << "clista     : " << (double)(pr1/tt) << endl;
    cout << "list_circle    : " << (double)(pr2/tt) << endl;
*/