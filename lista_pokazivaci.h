using namespace std;

struct zaposlenik{
	char oib[11];
	int datum;
	char ime[20], prezime[20], mjesto[40];
};
struct List {
       zaposlenik z;
       List *sljedeci;
       };

typedef List *element;
typedef List list;

element FirstL(list *L) {
        return L->sljedeci;
        }
        
element EndL(list *L) {
        List *tekuci=L->sljedeci;
        while(tekuci->sljedeci) tekuci=tekuci->sljedeci;
        return tekuci->sljedeci;
        }

element NextL(element z, list *L) {
        return z->sljedeci;
        }

element PreviousL(element z, list *L) {
        element tekuci=L;
        while(tekuci->sljedeci!=z) tekuci=tekuci->sljedeci;
        return tekuci;
        }

element LocateL (zaposlenik z, list * L){
        element tekuci = L;
		element zadnji = EndL(L);
		while(1){
			if (tekuci == zadnji) return zadnji;
			if (tekuci->z.oib==z.oib) return tekuci;
			tekuci = tekuci->sljedeci;
		}
}

void InsertL(zaposlenik z, element e, list *L) {
     element novi= new list;
	novi->z=z;
	novi->sljedeci=e->sljedeci;
	e->sljedeci=novi;
    }

void DeleteL(element z, list *L) {
     element next=z->sljedeci;
     z->sljedeci=next->sljedeci;
	delete(next);
    }

zaposlenik RetreiveL(element z, list *L) {
          return z->z;
          }

void DeleteAllL(list *L) {
     element tekuci=L->sljedeci, sljedeci;
     while(tekuci) {
                   sljedeci=tekuci->sljedeci;
                   delete tekuci;
                   tekuci=sljedeci;
                   }
     }

list *InitL(list *L) {
     L=new list;
	L->sljedeci=nullptr;
     return L;
      }
