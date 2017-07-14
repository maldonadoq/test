#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "src/sws.h"
#include "src/sort.h"
#include "src/sort_t.h"

FILE *a, *b;

using namespace std;

int main(int argc, char const *argv[]){
	int tm;
	bool t=true;


	int r, nv=50, inc=100000;
	while(t){
		cout << "0. size" << endl;
		cout << "1. bubble" << endl;
		cout << "2. insertion" << endl;
		cout << "3. quick" << endl;
		cout << "4. merge" << endl;
		cout << "5. exit" << endl;
		cin >> tm;
		cout << endl;
		switch(tm){
			case 0:
				cout << "number thread: " << th << endl;
				cout << "number of tests: " << nv << endl;
				cout << "increment: " << inc << endl;
				int qw;
				cout << "change: "; cin >> qw;
				if(qw==1){
					cout << "number thread: "; cin >> th;
					cout << "number of tests: "; cin >> nv;
					cout << "increment: "; cin >> inc;
					cout << endl;
				}
				break;
			case 1:{
				r = 100;
				a = fopen("../datos/bubble.dat","w");
				b = fopen("../datos/bubble_t.dat","w");
				for(int i=0; i<nv; i++,r+=inc){
					int *A = new int[r];
					int *B = new int[r];
					pull_al(A,B,r);
					dat(a,A,r,bubble_sort);
					dat(b,B,r,bubble_thread);
					delete A; delete B;
				}
				fclose(a);
				fclose(b);
				break;
			}
			case 2:
				r = 100;
				a = fopen("../datos/insertion.dat","w");
				b = fopen("../datos/insertion_t.dat","w");
				for(int i=0; i<nv; i++,r+=inc){
					int *A = new int[r];
					int *B = new int[r];
					pull_al(A,B,r);
					dat(a,A,r,insertion_sort);
					dat(b,B,r,insertion_thread);
					delete A; delete B;
				}
				fclose(a);
				fclose(b);
				break;
			case 3:
				r = 100;
				a = fopen("../datos/quick.dat","w");
				b = fopen("../datos/quick_t.dat","w");
				for(int i=0; i<nv; i++,r+=inc){
					int *A = new int[r];
					int *B = new int[r];
					pull_al(A,B,r);
					dat(a,A,r,quick_sort);
					dat(b,B,r,quick_thread);
					delete A; delete B;
				}
				fclose(a);
				fclose(b);
				break;
			case 4:
				r = 100;
				a = fopen("../datos/merge.dat","w");
				b = fopen("../datos/merge_t.dat","w");
				for(int i=0; i<nv; i++,r+=inc){
					int *A = new int[r];
					int *B = new int[r];
					pull_al(A,B,r);
					dat(a,A,r,merge_sort);
					dat(b,B,r,merge_thread);
					delete A; delete B;
				}
				fclose(a);
				fclose(b);
				break;
			case 5:
				t = false;
				break;
		}
	}

	return 0;
}
//plot "bubble.dat" w l, "insertion.dat" w l, "quick.dat" w l, "merge.dat" w l