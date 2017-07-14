#include <iostream>
#include <thread>

using namespace std;

void _find(int *p, int search, int begin, int end){
	p += begin;
    for (int i = begin; i<end and (*p)!=search; i++,p++);
	if((*p)==search) cout << "yes" << endl;
	else cout << "no" << endl;
}

int main(int argc, char const *argv[]){

    int tl = 100;
    int *p = new int[tl];
    srand(time(NULL));
    for (int i = 0; i < tl; ++i){
        *(p+i)=rand()%tl;
    }
    
    int search=10;
    int n = thread::hardware_concurrency();
    
    thread th[n];
    int sum = tl/n, begin=0, end=0;
    for(int i=0; i<n; i++){
    	begin = end;
    	end = begin+sum;
    	//find(p,search,begin,end);
    	th[i] = thread(&_find,p,search,begin,end);
    }
	for(int i=0; i<n; i++)	th[i].join();
    return 0;
}