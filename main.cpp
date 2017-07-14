#include <iostream>
#include <time.h>
#include "src/allocator.h"
#include "src/grafo.h"
#include "src/hash.h"
#include "src/traits.h"

using namespace std;

const unsigned n = 17;
typedef traits<string,int>			T;
typedef cgrafo<T>					G;
typedef chash<G,F<G>,Alist<G>,n>	H;

int main(int argc, char const *argv[]){
	H *a = new H();
	
	unsigned t = 50, e = 30, m = 46, s;
	string name[e] = {"EAA","EAB","EAC","EAD","EAE","EBA","EBB","EBC","EBD","EBE","EEB","EEC","EED","ABD","ABE","ABF","DEF","DQS","SDC","SWS","SAR","ACE","GDE","EDA","TRG","QWE","PER","DAS","STE","KUG"};
	srand(time(NULL));
	for(unsigned i=0; i<t; i++){
		G *b = new G(name[i%e]);
		b->create(rand()%m +10);
		a->insert(b);
		//free(b);
	}

	a->print();

	delete a;
	return 0;
}