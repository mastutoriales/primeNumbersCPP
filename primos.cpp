#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <dos.h>
#include <stdlib.h>

using namespace std;

class ListaLigada{
private:
    class Nodo{
    public:
        int dato;
        Nodo *sig;

        Nodo(){
            dato=0;
            sig=NULL;
        }
        Nodo(int dato){
            this->dato=dato;
            sig=NULL;
        }
    };
    Nodo* head;
    Nodo* tail;
public:
    ListaLigada(){
        head=NULL;
        tail=NULL;
    }
    void agregar(int dato){
        Nodo* t = new Nodo(dato);
        if(head!=NULL){
            tail->sig=t;
            tail=t;
        }
        else{
            head=t;
            tail=t;
        }
    }
    int eliminar(){
        if(head!=NULL){
            int d = head->dato;
            if(head==tail){
                delete head;
                head=NULL;
                tail=NULL;
            }
            else{
                Nodo* t= head;
                head=head->sig;
                delete t;
            }
            return d;
        }
        else{
            return 0;
        }
    }
    bool vacia(){
        return (head==NULL);
    }
    int maximo(int numero){
        return (int) ceil(sqrt(numero));
    }
    int cargar(string fichero){
    	ifstream file;
    	string s;
    	int n=0;
    	file.open(fichero.c_str());
    	if(file.is_open()){
    		while(!file.eof()){
    			getline(file,s);
    			if(s.length()>=1){
					agregar(_atoi64(s.c_str()));
					n++;
				}
			}
		}
		cout<<"Carga Completa"<<endl;
		return n;
	}
    void run(int nprimos, string salidaNombre,string entradaNombre){
        int fprimos=0;
        clock_t busquedai=clock();
        fprimos=cargar(entradaNombre);
        if(fprimos==0){
        	agregar(2);
        	agregar(3);
        	agregar(5);
		}
		cout<<"Iniciando Busqueda"<<endl;
        int u = tail->dato+2;
        Nodo *t;
        int m;
        bool primo;
        while(fprimos<=nprimos){
            t =head;
            m = maximo(u);
            primo=true;
            while(t->dato<=m){
                if(u%t->dato==0){
                    primo=false;
                    break;
                }
                t=t->sig;
            }
            t=NULL;
            if(primo){
                agregar(u);
                fprimos++;
            }
            u+=2;
        }
        clock_t busquedaf = clock();
        cout<<"Calculo Terminando"<<endl;
        ofstream salida;
        stringstream ss;
        clock_t guardari = clock();
        salidaNombre+=".txt";
        salida.open(salidaNombre.c_str());
        while(!vacia()){
            ss<<eliminar()<<endl;
        }
        salida<<ss.str();
        salida.close();
        clock_t guardarf = clock();

        cout<<"Tiempo Busqueda Primos: "<<tiempo((busquedaf - busquedai) / (float)CLK_TCK)<<endl;
        cout<<"Tiempo Guardado Primos: "<<tiempo((guardarf - guardari) / (float)CLK_TCK)<<endl;
        cout<<"Tiempo Total: "<<tiempo((guardarf - busquedai) / (float)CLK_TCK)<<endl;
        cout << "Presione ENTER para Salir: ";
        cin.ignore().get();
    }
    string tiempo(float segundos){
		float m=0,h=0,d=0;
		if(segundos>86400){
			float r = fmod(segundos,86400);
			d=(segundos-r)/86400;
			segundos-=(d*86400);
		}
		if(segundos>3600){
			float r = fmod(segundos,3600);
			h=(segundos-r)/3600;
			segundos-=(h*3600);
		}
		if(segundos>60){
			float r = fmod(segundos,60);
			m=(segundos-r)/60;
			segundos-=(m*60);
		}
		stringstream ss;
		if(d>0){
			if(d>1)ss<<d<<" Dias ";
			else ss<<d<<" Dia ";
		}
		if(h>0){
			if(h>1)ss<<h<<"  Horas ";
			else ss<<h<<"  Hora ";
		}
		if(m>0){
			if(m>1)ss<<m<<"  Minutos ";
			else ss<<m<<"  Minuto ";
		}
		if(segundos>0){
			if(segundos>1)ss<<segundos<<"  Segundos ";
			else ss<<segundos<<"  Segundo ";
		}
		return ss.str();
	}
    void run(){
        int primos;
        string nombre,entrada;
        cout<<"Cuantos numeros primos desea encontrar?: ";
        cin>>primos;
        cout<<"Ingrese el nombre del fichero de salida: ";
        cin>>nombre;
        cout<<"Ingrese el nombre del fichero de entrada: ";
        cin>>entrada;
        run(primos,nombre,entrada);
    }
};
int main(){
	
    ListaLigada ll;
	ll.run();
    return 0;
}
