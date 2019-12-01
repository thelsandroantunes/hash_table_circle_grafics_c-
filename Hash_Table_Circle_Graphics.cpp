/*
    Programa: Tabela Hash com Grafics
    Autor: Thelsandro Antunes
    1ª Versão 
    Concluída em: 01/12/2019
    Breve descrição:
        Este programa captura os pontos (x,y) dos círculos gerados automaticamente e armazena.  				
*/
#include<graphics.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<windows.h>
#include<iostream>
#include<string>

#define TAM 25

using namespace std;

/********************************************/
int funcaoHash(int chave, int M){
 return chave % M; 
}
class noh{
friend class tabelaHash;
private:    
    int x;
    int y;
    noh* proximo = NULL;
public:
    noh();
};

class tabelaHash{
private:
    noh** elementos;
    int capacidade;
public:
    tabelaHash(int cap);
    ~tabelaHash();
    void insere(int x, int y);
    string recupera(int x, int y);    
    void percorre ();
};

noh::noh(){
    
}

tabelaHash::tabelaHash(int cap = TAM){
    elementos = new noh*[cap];
    capacidade = cap;
    for (int i = 0; i < cap; i++){
        elementos[i] = NULL;
    }
}

tabelaHash::~tabelaHash(){
    for (int i = 0; i < capacidade; ++i){
        noh* atual = elementos[i];
        while(atual != NULL){
            noh* aux = atual;
            atual = atual->proximo;
            delete aux;
        }
    }
    delete[] elementos;
}

void tabelaHash::insere( int x, int y){
    int hash = funcaoHash(x+y,capacidade);
    if (recupera(x,y) == "NAO ENCONTRADO"){
        if (elementos[hash] == NULL){
            elementos[hash] = new noh;            
            elementos[hash]->x = x;
            elementos[hash]->y = y;
        }else{            
            noh* atual = elementos[hash];
            while(atual->proximo != NULL){
                atual = atual->proximo;
            }
            noh* novo = new noh;            
            novo->x = x;
            novo->y = y;
            atual->proximo = novo;
        }
    }else{
        cout << "O ITEM JAH ESTA NA TABELA" << endl;
    }
}

string tabelaHash::recupera(int x, int y){	
    int hash = funcaoHash(x+y,capacidade);
    if (elementos[hash] != NULL and elementos[hash]->x == x and elementos[hash]->y == y){
    		char *pontoX, *pontoY = new char[2];
    		pontoX = itoa(elementos[hash]->x, pontoX, 10); 
    		pontoY = itoa(elementos[hash]->y, pontoY, 10); 
				
				string s;
				s += "(";
				s += pontoX;
				s += ",";
				s += pontoY;
				s += ")";
        return s;
    }else{
        noh* atual = elementos[hash];
        
        while (atual != NULL and atual->x != x and atual->y != y){
            atual = atual->proximo;
        }

        if (atual != NULL and atual->x == x and atual->y == y){
        		char *pontoX, *pontoY = new char[6];
		    		pontoX = itoa(atual->x, pontoX, 10); 
		    		pontoY = itoa(atual->y, pontoY, 10); 
						
						string s;
						s += "(";
						s += pontoX;
						s += ",";
						s += pontoY;
						s += ")";
            return s;
        }else{
            return "NAO ENCONTRADO";
        }
    }
}

void tabelaHash::percorre(){
    noh* atual;
    cout << "!--------------------!" << endl;
    for (int i = 0; i < capacidade; ++i){
        cout << i << ": ";
        atual = elementos[i];
        while (atual != NULL){
            cout << "(x:" << atual->x << ", y: " << atual->y << ") -->";
            atual = atual->proximo;
        }
        cout << " NULL" << endl;
    }
    cout << "!--------------------!" << endl;
}
/********************************************/
int main()
{
	tabelaHash th(TAM);
	int i = 0;
	
	DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
	DWORD screenHeight = GetSystemMetrics(SM_CYSCREEN);
	
	initwindow(screenWidth,screenHeight,"",-3,-3);	
	POINT cursorPosition;
		
	while(i < TAM){
					
		GetCursorPos(&cursorPosition);    
		cout << "(x: " << cursorPosition.x << ", y: " << cursorPosition.y << ")" << endl;
		th.insere (cursorPosition.x, cursorPosition.y);
		circle(cursorPosition.x,cursorPosition.y,50);
		
		delay(100);
		i++;
	}
	th.percorre();
	getch();
  closegraph();
  
  return 0; 
}
