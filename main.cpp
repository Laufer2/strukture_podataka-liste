#include <cstdlib>
#include <iostream>
#include "lista_polje.h"
#include <ctime>
#include <cstring>
using namespace std;

int unos(list *l);
int kontrolna(int polje[]);
void horo(list *l);
void ispis_zaposlenika(int i, list *l, int r);
int brisanje_oib(list *l);
int brisanje_radno_mjesto(list *l);
void quicksort(list *l, int start, int end);
void swap(list x, list y);

int main(){
	int izbor;
	list* l=InitL(l);
	do{
		cout<<endl<<"*****************************"<<endl;
		cout<<"1. Unos zaposlenika "<<endl;
		cout<<"2. Silazno sortiranje i ispis"<<endl;
		cout<<"3. Ispis horo i svih"<<endl;
		cout<<"4. Brisanje po OIB-u"<<endl;
		cout<<"5. Brisanje po radnom mjestu"<<endl;
		cout<<"9. Izlaz iz programa"<<endl;
		cout<<"*****************************"<<endl;
		cout<<"Odaberite opciju: ";
		cin>>izbor;
		cout<<"*****************************"<<endl;
		switch(izbor){
			case 1:
				unos(l);
				break;
			case 2:
				if(CountL(l)==0){
					cout<<"Lista je prazna."<<endl;
					cout<<"Unesite zaposlenika preko mogucnosti 1."<<endl; break;
				}
				quicksort(l,0,l->cursor-1);
				ispis_zaposlenika(0,l,2);
				break;
			case 3:
				horo(l);
				break;
			case 4:
				brisanje_oib(l);
				break;
			case 5:
				brisanje_radno_mjesto(l);
				break;
			case 9: cout<<"Izlaz iz programa..."<<endl; break;
			default: cout<<"Ponovi izbor!"<<endl;
		}
	}while(izbor!=9);
	return 0;
}

int unos(list *l){
	zaposlenik novi;
	cout<<"Ime: ";
	cin>>novi.ime;
	cout<<"Prezime: ";
	cin>>novi.prezime;
	cout<<"Datum rodjenja "<<endl;
	cout<<"\tDan: ";
	cin>>novi.dan;
	cout<<"\tMjesec: ";
	cin>>novi.mjesec;
	cout<<"\tGodina: ";
	cin>>novi.godina;
	cout<<"Radno mjesto: ";
	cin>>novi.mjesto;
	srand(time(0));
	rand();
	int polje[11];
	bool isti=false;
	do{
		for(int i=0; i<11; i++){
			polje[i]=rand()%9+1;
			novi.oib[i]=polje[i] + 48;
			if(i==10){
				polje[i]=kontrolna(polje);
				novi.oib[i]=polje[i]+48;
			}
		}
		for(int i=0; i<CountL(l); i++){ // provjera istih oib-a
			if(strcmp(l->z[i].oib, novi.oib) == 0) isti=true;
		}
	}while(isti);
	cout<<"Oib: ";
	for (int i=0; i<12; i++)	cout<<novi.oib[i];
	bool upis=InsertL(novi, EndL(l), l);
	if(upis) return 1;// s curosr-om i povecanjem D
	else return 0;
}

int kontrolna(int polje[]){//kontrolna znamenka ISO 7064 MOD 11,10
	int a=0;
	for(int i=0; i<10; i++){
		a+=polje[i]+10;
		a%=10;
		if(a==0) a=10;
		a*=2;
		a%=11;
	}
	if(a==1) a=0;
	else a=11-a;
	return a;
}

//sort po oib-u
void quicksort(list *l, int start, int end){
	if(end-start<=0) return;
	int pivot=(rand()%(end-start+1))+start;
	swap(l->z[pivot],l->z[start]);
	int c=start;
	for(int i=c+1; i<=end; ++i)
		if(strcmp(l->z[i].oib, l->z[c].oib)>0){
			swap(l->z[i], l->z[c+1]);
			swap(l->z[c], l->z[c+1]);
			c++;
		}
	quicksort(l, start, c-1);
	quicksort(l, c+1, end);
}

void swap(list x, list y){
	list temp=x;
	x=y;
	y=temp;
}

int brojac=0;
void ispis_zaposlenika(int i, list *l, int r=1){
	switch (r){
		case 1:
			cout<<endl;
			cout<<"-----------------------------"<<endl;
			cout<<"Ime: "<<l->z[i].ime<<endl;
			cout<<"Prezime: "<<l->z[i].prezime<<endl;
			cout<<"Datum rodjenja: "<<l->z[i].dan<<"."<<l->z[i].mjesec<<"."<<l->z[i].godina<<"."<<endl;
			cout<<"Radno mjesto: "<<l->z[i].mjesto<<endl;
			cout<<"OIB: "<<l->z[i].oib<<endl;
			brojac++; break;
		case 2:
			for(i=0;i<CountL(l);i++){
				cout<<"-----------------------------"<<endl;
				cout<<"Ime: "<<l->z[i].ime<<endl;
				cout<<"Prezime: "<<l->z[i].prezime<<endl;
				cout<<"Datum rodjenja: "<<l->z[i].dan<<"."<<l->z[i].mjesec<<"."<<l->z[i].godina<<"."<<endl;
				cout<<"Radno mjesto: "<<l->z[i].mjesto<<endl;
				cout<<"OIB: "<<l->z[i].oib<<endl;				
			}
		}
}

void horo(list *l){//switch case D
	if(CountL(l)==0){
		cout<<"Lista je prazna."<<endl;
		cout<<"Unesite zaposlenika preko mogucnosti 1."<<endl;
		return;
	}
	int d, mj;
	cout<<"*** Ispis zaposlenika istog horoskopskog znaka kao Vi ***"<<endl;
	cout<<"Datum rodjenja "<<endl;
	cout<<"\tDan: ";
	cin>>d;
	cout<<"\tMjesec: ";
	cin>>mj;
	for(int i=0; i<CountL(l); i++){
		if(((d<=19&&mj==2)||(d>=21&&mj==1))&&((l->z[i].dan<=19&&l->z[i].mjesec==2)||(l->z[i].dan>=21&&l->z[i].mjesec==1)))//vodenjak
			ispis_zaposlenika(i, l);
		if(((d<=20&&mj==3)||(d>=20&&mj==2))&&((l->z[i].dan<=20&&l->z[i].mjesec==3)||(l->z[i].dan>=20&&l->z[i].mjesec==2)))//riba
			ispis_zaposlenika(i, l);		
		if(((d<=20&&mj==4)||(d>=21&&mj==3))&&((l->z[i].dan<=20&&l->z[i].mjesec==4)||(l->z[i].dan>=21&&l->z[i].mjesec==3)))//ovan
			ispis_zaposlenika(i, l);		
		if(((d<=21&&mj==5)||(d>=21&&mj==4))&&((l->z[i].dan<=21&&l->z[i].mjesec==5)||(l->z[i].dan>=21&&l->z[i].mjesec==4)))//bik
			ispis_zaposlenika(i, l);	
		if(((d<=21&&mj==6)||(d>=22&&mj==5))&&((l->z[i].dan<=21&&l->z[i].mjesec==6)||(l->z[i].dan>=21&&l->z[i].mjesec==5)))//blizanci
			ispis_zaposlenika(i, l);	
		if(((d<=22&&mj==7)||(d>=22&&mj==6))&&((l->z[i].dan<=22&&l->z[i].mjesec==7)||(l->z[i].dan>=22&&l->z[i].mjesec==6)))//rak
			ispis_zaposlenika(i, l);	
		if(((d<=22&&mj==8)||(d>=23&&mj==7))&&((l->z[i].dan<=22&&l->z[i].mjesec==8)||(l->z[i].dan>=23&&l->z[i].mjesec==7)))//lav
			ispis_zaposlenika(i, l);	
		if(((d<=22&&mj==9)||(d>=23&&mj==8))&&((l->z[i].dan<=22&&l->z[i].mjesec==9)||(l->z[i].dan>=23&&l->z[i].mjesec==8)))//djevica
			ispis_zaposlenika(i, l);
		if(((d<=22&&mj==10)||(d>=23&&mj==9))&&((l->z[i].dan<=22&&l->z[i].mjesec==10)||(l->z[i].dan>=23&&l->z[i].mjesec==9)))//vaga
			ispis_zaposlenika(i, l);
		if(((d<=21&&mj==11)||(d>=23&&mj==10))&&((l->z[i].dan<=21&&l->z[i].mjesec==11)||(l->z[i].dan>=23&&l->z[i].mjesec==10)))//�korpion
			ispis_zaposlenika(i, l);
		if(((d<=21&&mj==12)||(d>=22&&mj==11))&&((l->z[i].dan<=21&&l->z[i].mjesec==12)||(l->z[i].dan>=22&&l->z[i].mjesec==11)))//strijelac
			ispis_zaposlenika(i, l);
		if(((d<=20&&mj==1)||(d>=22&&mj==12))&&((l->z[i].dan<=20&&l->z[i].mjesec==1)||(l->z[i].dan>=22&&l->z[i].mjesec==12)))//jarac
			ispis_zaposlenika(i, l);
	}
	cout<<"Ukupan broj zaposlenika: "<<brojac<<endl;
	brojac=0;
}

int brisanje_oib(list *l){
	if(CountL(l)==0){
		cout<<"Lista je prazna."<<endl;
		cout<<"Unesite zaposlenika preko mogucnosti 1."<<endl;
		return 0;
	}
	cout<<"Moguci oib-i"<<endl;
	for(int i=0; i<CountL(l); i++){
		cout<<"OIB: "<<l->z[i].oib<<endl;
	}
	char bris[12]="\0";
	cout<<"Unesite OIB zaposlenika za brisanje: ";
	cin.ignore();
	cin.getline(bris, 12);
	for(int i=0; i<CountL(l); i++){
		if(strcmp(l->z[i].oib, bris)==0){
			DeleteL(i, l);
			cout<<"Zapis obrisan!"<<endl;
			return 1;
		}
	}
	cout<<"Zapis nije obrisan!"<<endl;
	return 0;
}
int brisanje_radno_mjesto(list *l){
	if(CountL(l)==0){
		cout<<"Lista je prazna."<<endl;
		cout<<"Unesite zaposlenika preko mogucnosti 1."<<endl;
		return 0;
	}
	char radno_mjesto[40];
	bool obrisan=false;
	cout<<"Unesite radno mjesto zaposlenika koje zelite obrisati: ";
	cin.ignore();
	cin.getline(radno_mjesto, 40);
	for(int i=0; i<CountL(l); i++){
		if(strcmp(l->z[i].mjesto, radno_mjesto)==0){
			DeleteL(i, l);
			i--;		
			obrisan=true; 
		}
	}
	if (obrisan){
		cout<<"Brisanje uspjelo!"<<endl;
		return 1;
	}
	else{
		cout<<"Neuspjelo brisanje!";
		return 0;
	}
}

