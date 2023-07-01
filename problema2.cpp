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

void disminuir(cm* heap, int len){
	cm* aux = new cm[len-1];
	for(int i = 0; i<len; i++){
		aux[i] = heap[i];
	}
	heap = aux;
	delete[] aux;
}

void flotar(cm* strs, cm agregar, int len){
	//Evitar que llegue al 0
	while(strs[(len-1)/2].prioridad != 0 && agregar.prioridad < strs[(len-1)/2].prioridad){
		cm aux = strs[(len-1)/2];
		strs[(len-1)/2] = agregar;
		len = (len-1)/2;
	}
}

void hundir(cm* strs, int len){
	int pos = 1;
	strs[1] = strs[len-1];
	disminuir(strs, len);

	//utilizar pos para no pasarse de len
	while(((pos+1)*2 < len && pos*2 < len) && (strs[pos].prioridad > strs[(pos+1)*2].prioridad || strs[pos].prioridad > strs[(pos)*2].prioridad)){
		if(strs[pos].prioridad > strs[pos*2].prioridad){
			cm aux = strs[pos*2];
			strs[pos*2] = strs[pos];
			pos = pos*2;
		} else {
			cm aux = strs[(pos+1)*2];
			strs[(pos+1)*2] = strs[pos];
			pos = (pos+1)*2;
		}
	}
}

//quitar hundir porque solo es necesario cuando se borra nodo?
//hay que evitar que se flote hasta la posicion 0
void pushcommand(cm* strs, cm agregar, int len){
	strs[len-1] = agregar;
	while(true){
		if (agregar.prioridad < strs[(len-1)/2].prioridad){
			flotar(strs, agregar, len);	
			cout<< "AQUI" <<strs[len-1].iden<<endl;
		} else {
			break;
		}
	}
}

//hacer length un puntero para cambiarlo en funcion?

int main(){
	cm* minheap = new cm[sizeof(cm)*2];
	cm raiz;
	raiz.prioridad = 0;
	int length = 2;
	int cont = 0;
	int created = 0;
	int sent = 0;

	while(true){
		string comando;
		cin >> comando;
		cout << "COMANDO: " << comando << endl;
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
			pushcommand(minheap, elemento, length);
			expandir(minheap, length++);
			cout << cont << " PENDING" << endl;
		}

		for(int z = 0; z<5; z++){
			cout << z << " iden: " << minheap[z].iden << endl;
		}

		if (comando == "GET"){
			int ncoms;
			cin >> ncoms;
			cout << "ncoms: " << ncoms << endl;
			sent += ncoms;
			cout << "sent: " << sent << endl;
			if(length >= 3){
				cout << ncoms;
				cm* auxiliar = new cm[sizeof(cm)*ncoms];
				int lineas_blancas = 0;
				int naux = 0;

				for(int j = 1; j <= ncoms; j++){
					cout << " probar: " << minheap[1].iden << endl;
					if (j <= length){

						cout << " " << minheap[j].iden;
						cout << "AYUDA" << endl;
						cout << "NO ESTOY LLEGANDO";
						auxiliar[j] = minheap[j];
						hundir(minheap, length);
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
				string separador(lineas_blancas + 1, '\n');
				cout << separador;
				}
			} else {
				cout << "0" << endl;
			}
		}
	}
	delete[] minheap;
}
