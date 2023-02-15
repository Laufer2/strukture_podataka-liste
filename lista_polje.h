#include <cstring>
struct zaposlenik{
	char oib[11];
	int dan, mjesec, godina;
	char ime[20], prezime[20], mjesto[40];
};
struct Lis{
	zaposlenik z[100];
	int cursor;
};
typedef Lis list;

int FirstL(Lis *L){
	return 0;
}

int EndL(Lis *L){
	return L->cursor;
}

int NextL(int in, Lis *L){
	if (in<L->cursor && in>=0)
		return in+1;
	else return -1;
}

int CountL(Lis *L){
	return L->cursor;
}

int PreviousL(int in, Lis *L){
	if(in<=L->cursor && in>0)
		return in-1;
	else return -1;
}
int LocateL(char o[], Lis *L){
	for (int i=0; i<L->cursor; i++){
		if (strcmp(L->z[i].oib, o)==0) return i;
	}
	return L->cursor;
}
bool InsertL(zaposlenik zap, int in, Lis *L){
	if(in <= L->cursor){
		L->cursor++;
		for (int i=L->cursor-1; i>in; i--){
			L->z[i]=L->z[i-1];
		}
		L->z[in]=zap;
		return true;
	}else return false;
}
void DeleteL(int in, Lis *L){ 
	for (int i=in+1; i<L->cursor; i++){
		L->z[i-1]=L->z[i];
	}
	L->cursor--;
}
zaposlenik RetrieveL(int in, Lis *L){
	return L->z[in];
}
void DeleteAllL(Lis *L){
	L->cursor=0;
}
Lis* InitL(Lis *L){
	L=new Lis;
	L->cursor=0;
	return L;
}
