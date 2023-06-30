#include <iostream>
#include <string>
using namespace std;

struct cm{
	string iden;
	string instruc;
	int prioridad;
};

void expandir(cm* heap, int len){
	cm* aux = new cm[len+1];
	for(int i = 0; i<len; i++){
		aux[i] = heap[i];
	}
	heap = aux;
	delete[] aux;
}

void flotar(cm* strs, cm agregar, int len){
	while(strs[(len-1)/2].prioridad != 0 && agregar.prioridad < strs[(len-1)/2].prioridad){
		cm aux = strs[(len-1)/2];
		strs[(len-1)/2] = agregar;
		flotar(strs, agregar, (len-1)/2);
	}
}

//Agrandar el arreglo antes de hundir para evitar que se llegue a un espacio inexistente
void hundir(cm* strs, cm agregar, int len){
	while(agregar.prioridad > strs[(len-1)*2].prioridad || agregar.prioridad > strs[(len)*2].prioridad){
		if(agregar.prioridad > strs[(len-1)*2].prioridad){
			cm aux = strs[(len-1)*2];
			strs[(len-1)*2] = agregar;
			hundir(strs, agregar, (len-1)*2);
		} else {
			cm aux = strs[(len)*2];
			strs[(len)*2] = agregar;
			hundir(strs, agregar, (len)*2);
		}
	}
}

void pushcommand(cm* strs, cm agregar, int len){
	strs[len-1] = agregar;
	while(true){
		if (agregar.prioridad < strs[(len-1)/2].prioridad){
			flotar(strs, agregar, len);
		}
		if (agregar.prioridad > strs[(len-1)*2].prioridad || agregar.prioridad > strs[(len)*2].prioridad){
			hundir(strs, agregar, len);
		} else {
			break;
		}
	}
	return;
}

//hacer length un puntero para cambiarlo en funcion?

int main(){
	cm* minheap = new cm[sizeof(cm)*2];
	cm raiz;
	raiz.prioridad = 0;
	int length = 2;

	while(true){
		string comando;
		cin >> comando;
		if (comando == "TERMINATE"){
			break;
		} else if (comando == "PUSHCOMMAND"){
			expandir(minheap, length++);
			string id, instruccion;
			int pr;
			cin >> id >> pr >> instruccion;
			cm elemento;
			elemento.iden = id;
			elemento.instruc = instruccion;
			elemento.prioridad = pr;
			pushcommand(minheap, elemento, length);
			
		} else if (comando == "GET"){

		}
	}

	delete[] minheap;
}
