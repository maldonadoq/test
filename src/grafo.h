#ifndef _GRAFO_H_
#define _GRAFO_H_

#include <vector>
#include <list>
#include <queue>
#include <vector>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <algorithm>
#include <stdlib.h>
#include "node.h"
#include "edge.h"
#include "prqueue.h"
#include "traits.h"

using namespace std;

FILE *word;

template<class G>
class cgrafo{
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::node node;
    typedef typename G::edge edge;
    typedef typename G::niterator niterator;
    typedef typename G::eiterator eiterator;
    unsigned ne, nn;
    string m_name;
    vector<node *> m_nodes;
    
    cgrafo(string name){
        this->ne = 0; this->nn = 0;
        this->m_name = name;   
    }

    void info(){
        cout << "-----------------------------------" << endl;
        cout << "   " << this->m_name << "   nodos: " << nn << "    aristas: " << ne << endl;
        cout << "-----------------------------------" << endl;  
    }

    bool find(N x, unsigned &i){
        for(i=0; i<m_nodes.size(); i++)
            if(m_nodes[i]->m_dato==x)	return true;
        return false;
    }
    
    bool insert_node(N x){
        node *tr = new node(x,nn++);
        m_nodes.push_back(tr);
        return true;
    }
    
    // crear un grafo aleatorio, para unir nodos
    bool insert_edge_al(E x, node *a, node *b, bool d){
        edge *c = new edge(x,d);
        a->m_edges.push_back(c);
        b->m_edges.push_back(c);
        c->m_nodes[0] = a;
        c->m_nodes[1] = b;
        this->ne++;
        return true;
    }

    int** matriz(){
        unsigned t = m_nodes.size();
        int **a = new int*[t];
        for(unsigned i=0; i<t; i++) a[i] = new int[t];
        for(unsigned i=0; i<t; i++)
            for(unsigned j=0; j<t; j++)
                a[i][j] = 0;

        for(unsigned i=0; i<t; i++){
            for(eiterator it=m_nodes[i]->m_edges.begin(); it!=m_nodes[i]->m_edges.end(); it++){
                if((*it)->m_dir){
                    if((*it)->m_nodes[1]->m_dato!=m_nodes[i]->m_dato)
                        a[i][(*it)->m_nodes[1]->m_id] = (*it)->m_dato;
                    else
                        a[i][(*it)->m_nodes[0]->m_id] = (*it)->m_dato;
                }
                else{
                    if((*it)->m_nodes[1]->m_dato!=m_nodes[i]->m_dato)
                        a[i][(*it)->m_nodes[1]->m_id] = (*it)->m_dato;
                }
            }
        }
        return a;
    }

    void crea(int **a, unsigned t){
        string da;
        for(unsigned i=0; i<t; i++){ 
            da = "";
            char sw = 65+i;
            da+=sw;
            insert_node(da);
        }
        for(unsigned i=0; i<t; i++){
            for(unsigned j=0; j<t; j++){
                if(a[i][j]!=0){
                    insert_edge_al(a[i][j], m_nodes[i], m_nodes[j], 1);
                }
            }
        }  
    }

    // unir nodos, yo les doy el nodo
    bool insert_edge(E x, N a, N b, bool d){
        unsigned p,q;
        if(find(a,p) and find(b,q)){
            edge *c = new edge(x,d);
            m_nodes[p]->m_edges.push_back(c);
            m_nodes[q]->m_edges.push_back(c);
            c->m_nodes[0] = m_nodes[p];
            c->m_nodes[1] = m_nodes[q];
        }
        this->ne++;
        return true;
    }
    
    bool remove_edge(N a, N b){
    	unsigned p,q;
    	if(!(find(a,p) and find(b,q)))	return false;
    	m_nodes[p]->remove_edge(m_nodes[q]);
    	this->ne--;
        return true;
    }
    
    bool remove_node(N x){
        unsigned p;
        if(!find(x,p))   return false;
        this->ne -= m_nodes[p]->m_edges.size();
        m_nodes[p]->remove_edges();
        delete m_nodes[p];
        m_nodes.erase(m_nodes.begin()+p);
        return true;
    }
    
    void print(){
    	info();
        unsigned wq = (m_nodes.size()/10 == 0)? 1: m_nodes.size()/10;
        for(unsigned i=0; i<m_nodes.size(); i+=wq)  
            m_nodes[i]->print();
    }
    
    void create(unsigned r){
        vector<N> nod;
        char d;
        word = fopen("../datos/word.dat","r");
        N wo = "";
        while((d=getc(word))!=EOF){
            if(d!='\n'){
                wo+=d;
                /*if(wo.size()==s){
                    insert_node(wo);
                    nod.push_back(wo);
                    wo="";
                }*/ 
            }
            else{
                insert_node(wo);
                nod.push_back(wo);
                wo="";
            }
        }
        fclose(word);

        srand(time(NULL));
        unsigned p, q;
        for(unsigned i=0; i<r; i++){
            p = rand()%m_nodes.size();   q = rand()%m_nodes.size();
            if(p!=q and !m_nodes[p]->operator==(m_nodes[q])) //!m_nodes[p]->conex(m_nodes[q])
                insert_edge_al(rand()%9 +1, m_nodes[p], m_nodes[q], 1);
        }
    }

    void fn(node *a, E ed, E ac, vector<unsigned> road){
        if((ac+ed)<a->m_acum){
            a->m_acum = ac+ed;
            a->m_road = road;
            a->m_road.push_back(a->m_id);
        }
    }

    virtual void dijkstra(N a, N b){
        unsigned i;
        if(!find(a,i)) return;
        cout << endl;
        struct timeval ti, tf;
        double tiempo;
        gettimeofday(&ti, NULL);

        prqueue<G> pq;
        pq.push(m_nodes[i]);
        eiterator it;
        node *t;
        m_nodes[i]->m_acum = 0;
        while(!pq.empty()){
            t = pq.top();   pq.pop();
            for(it=t->m_edges.begin(); it!=t->m_edges.end(); it++){
                if(!(*it)->m_vst){
                    if((*it)->m_dir){
                        if(((*it)->m_nodes[0]->m_dato!=t->m_dato)){  fn((*it)->m_nodes[0], (*it)->m_dato, t->m_acum,(*it)->m_nodes[1]->m_road);  pq.push((*it)->m_nodes[0]);   }
                        else{    fn((*it)->m_nodes[1], (*it)->m_dato, t->m_acum,(*it)->m_nodes[0]->m_road);    pq.push((*it)->m_nodes[1]);   }
                        (*it)->m_vst = true;
                    }
                    else{
                        if(((*it)->m_nodes[1]->m_dato!=t->m_dato)){  
                            (*it)->m_vst = true;
                            fn((*it)->m_nodes[1], (*it)->m_dato, t->m_acum,(*it)->m_nodes[0]->m_road);  
                            pq.push((*it)->m_nodes[1]);   
                        }
                    }
                }
            }
        }

        gettimeofday(&tf, NULL);
        tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
        printf("dijkstra:  %.10f\n", tiempo/1000);

        unsigned wq = (m_nodes.size()/10 == 0)? 1: m_nodes.size()/10;
        for(unsigned i=0; i<m_nodes.size(); i+=wq){
            cout << "[" << a << "->" << m_nodes[i]->m_dato << "]    " << m_nodes[i]->m_acum << " \t";
            for(unsigned j=0; j<m_nodes[i]->m_road.size(); j++)
                cout << "->" << m_nodes[m_nodes[i]->m_road[j]]->m_dato;
            cout << endl;
        }
    }

    void pull(){
        eiterator it;
        for(unsigned i=0; i<m_nodes.size(); i++){
            m_nodes[i]->m_road.clear();
            for(it=m_nodes[i]->m_edges.begin(); it!=m_nodes[i]->m_edges.end(); it++)
                (*it)->m_vst = false;
        }
    }

    virtual ~cgrafo(){ 
        node *t;
        while(m_nodes.size()!=0){
            t = m_nodes[0];
            m_nodes.erase(m_nodes.begin());
            delete t;
        }
    };
};

template<class G>
class dgrafo: public cgrafo<G>{
public:
    typedef typename G::N N;
    typedef typename G::E E;
    typedef typename G::node node;
    typedef typename G::edge edge;
    typedef typename G::niterator niterator;
    typedef typename G::eiterator eiterator;

	dgrafo():cgrafo<G>(){	};
    void create(){
        node *tr = new node(cord(23,2),this->nn++);
        this->m_nodes.push_back(tr);
    }

    void f(node *a, vector<unsigned> road){
        a->m_road = road;
        a->m_road.push_back(a->m_id);
    }

    void dijkstra(N a, N b){
        unsigned i,j;
        if(!(this->find(a,i) and this->find(b,j))) return;
        cout << endl;

        struct timeval ti, tf;
        double tiempo;
        gettimeofday(&ti, NULL);

        prqueue<G> pq(this->m_nodes[j]);
        pq.pushd(this->m_nodes[i]);
        eiterator it;
        node *t;
        while(!pq.empty()){
            t = pq.top();   pq.pop();
            if(t==this->m_nodes[j])    break;
            for(it=t->m_edges.begin(); it!=t->m_edges.end(); it++){
                if(!(*it)->m_vst){
                    if((*it)->m_dir){
                        if(((*it)->m_nodes[0]->m_dato!=t->m_dato)){ f((*it)->m_nodes[0],(*it)->m_nodes[1]->m_road); pq.pushd((*it)->m_nodes[0]);    }
                        else{   f((*it)->m_nodes[1],(*it)->m_nodes[0]->m_road); pq.pushd((*it)->m_nodes[1]);    }
                        (*it)->m_vst = true;
                    }
                    else{
                        if(((*it)->m_nodes[1]->m_dato!=t->m_dato)){  
                            (*it)->m_vst = true;
                            f((*it)->m_nodes[1],(*it)->m_nodes[0]->m_road);
                            pq.pushd((*it)->m_nodes[1]);   
                        }
                    }
                }
            }
        }

        gettimeofday(&tf, NULL);
        tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000;
        printf("dijkstrah:  %.10f\n", tiempo/1000);

        unsigned wq = (this->m_nodes.size()/10 == 0)? 1: this->m_nodes.size()/10;
        for(unsigned i=0; i<this->m_nodes.size(); i+=wq){
            cout << "[" << a << "->" << this->m_nodes[i]->m_dato << "]\t";
            for(unsigned j=0; j<this->m_nodes[i]->m_road.size(); j++)
                cout << "->" << this->m_nodes[this->m_nodes[i]->m_road[j]]->m_dato;
            cout << endl;
        }
    }
	virtual ~dgrafo(){	};
};

#endif