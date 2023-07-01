#include <iostream>
#include <string>
#define M 100000
using namespace std;

struct cm{
	string iden;
	string instruc;
	int prioridad;
};

cm* heap;

class minheap{
private:
	int len;

public:
	minheap(){
		heap = new cm[sizeof(cm)*M];
		len = 2;	
		cm raiz;
		raiz.prioridad = 0;
	}

	~minheap(){
		delete[] heap;
	}

	void expandir(int len){
		cm* aux = new cm[len+1];
		for(int i = 0; i<len; i++){
			aux[i] = heap[i];
		}
		heap = aux;
		delete[] aux;
	}

	void disminuir(int len){
		cm* aux = new cm[len-1];
		for(int i = 0; i<len; i++){
			aux[i] = heap[i];
		}
		heap = aux;
		delete[] aux;
	}

/*****
* void flotar
******
* Reorganizar el heap
******
* Input:
* cm agregar : es el contenido de la ranura del heap
* int len : es el 
******
* Returns:
* TipoRetorno, Descripción retorno
*****/
 
	void flotar(cm agregar, int len){
		while(heap[(len-1)/2].prioridad != 0 && agregar.prioridad < heap[(len-1)/2].prioridad){
			cm aux = heap[(len-1)/2];
			heap[(len-1)/2] = agregar;
			len = (len-1)/2;
		}
	}

/*****
* void hundir
******
* Reorganizar el heap 
******
* Input:
* int len : es el largo del heap
******
* Returns:
* void
*****/

	void hundir(int len){
		int pos = 1;
		heap[1] = heap[len-1];
		while(((pos+1)*2 < len && pos*2 < len) && (heap[pos].prioridad > heap[(pos+1)*2].prioridad || heap[pos].prioridad > heap[(pos)*2].prioridad)){
			if(heap[pos].prioridad > heap[pos*2].prioridad){
				cm aux = heap[pos*2];
				heap[pos*2] = heap[pos];
				pos = pos*2;
			} else {
				cm aux = heap[(pos+1)*2];
				heap[(pos+1)*2] = heap[pos];
				pos = (pos+1)*2;
			}
		}
	}

	void pushcommand(cm agregar, int len){
		heap[len-1] = agregar;
		while(true){
			if (agregar.prioridad < heap[(len-1)/2].prioridad){
				flotar(agregar, len);	
			} else {
				break;
			}
		}
	}

};

int main(){
	minheap mainheap;
	int length = 2;
	int cont = 0;
	int created = 0;
	int sent = 0;

	while(true){
		string comando;
		cin >> comando;
		if (comando == "TERMINATE"){
			cout << sent << " SENT " << created << " CREATED" << endl;
			break;
		}

		if (comando == "PUSHCOMMAND"){
			cont++;
			created++;
			string id;
			//Si la instrucción supera los 100 caracteres no funcionará el código
			char instruccion[100];
			int pr;
			cin >> id >> pr;
			cin.getline(instruccion, 100);
			cm elemento;
			elemento.iden = id;
			elemento.instruc = instruccion;
			elemento.prioridad = pr;
			mainheap.pushcommand(elemento, length);
			length++;
			cout << cont << " PENDING" << endl;
		}


		if (comando == "GET"){
			int ncoms;
			cin >> ncoms;
			sent += ncoms;
			if(length >= 3){
				cout << ncoms;
				cm* auxiliar = new cm[sizeof(cm)*ncoms];
				int lineas_blancas = 0;
				int naux = 0;
				for(int j = 1; j <= ncoms; j++){
					if (j <= length){
					cout << " " << heap[j].iden << " ##";
					auxiliar[j] = heap[j];
					mainheap.hundir(length);
					length--;
					cont--;
					naux++;
					} else {
						lineas_blancas++;
					}
				for(int ins = 1; ins<=naux; ins++){
					cout << auxiliar[ins].instruc << endl;
				}
				delete[] auxiliar;
				string separador(lineas_blancas, '\n');
				cout << separador;
				}
			} else {
				cout << "0" << endl;
			}
		}
	}
}
