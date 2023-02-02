/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini                                
   _/   _/    _/   _/         _/    _/   Matricola 09099A   
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica              
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano                       
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/

#include "new_tavola.h"

using namespace std;


int numero_mosse(string nome_file){
    fstream file;
    string s;
    file.open(nome_file,ios::in);
    int contarighe=0;
        while(!file.eof()){
           getline(file,s,'\n');
           contarighe++;
        }
        return contarighe-2; // In quanto conta anche l'ultima riga vuota e la prima in cui non ci sono mosse
}


void Info_parziali(int grado){
	if (grado == 2){
		for(int i=0; i<25; i++){
			cerr << "Fin'ora ho visitato " << nodi[i] << " \tnodi a profondita' " << i << "\tcon efficienza: " << media[i]/numeri[i] << endl;

		}
		cerr << "----- Time: " << time(NULL) - inizio << " s." << endl;
	
		tempi.push_back(time(NULL) - inizio);
		n_nodi.push_back(nodi[6]);
		Stampa_tempi();
	}
}



bool da_equilibrare(){
/*
	if((n_tot+1) % A == 0){
		if(M*A < n_tot){
			return true;
		}
		else
			return false;
	}
	else
		return false;
*/
	return false;
}

long int Nuova_M(){
	return M+10000000;
}



void Stampa_vettore(){
	ofstream out ("hash_table.dat");
	salvataggio* id;
	int n;
		
	for (long int i=0; i<M; i++){
		n=0;
		id = salvati[i];
		while (id!=NULL){
			n ++;
			id = id->next;
		}
		out << n << endl;
	}
	out.close();
}



void Stampa_tempi(){
	ofstream out ("tempi.dat");
	long int l=tempi.size();
	for (long int i=0; i<l; i++){
		out << tempi[i] << "\t " << n_nodi[i] << endl;
	}
	out.close();
}



bool da_cercare(int grado){
	return true;
}



bool da_salvare(int grado){
	return (grado % grado_salvataggio == 0);
}



void Stampa_finale(exitus risultato){
	if(risultato.vinto == false){
		cout << "!!!  Esito finale: PATTA  !!!" << endl;
	}
	else if(risultato.chi == bianco){
		cout << "!!!  Esito finale: VINCE IL BIANCO  !!!" << endl;
	}
	else{
		cout << "!!!  Esito finale: VINCE IL NERO  !!!" << endl;
	}
	
	cout << "··· Tempo utilizzato: " << fine - inizio << " s ···" << endl;

	for(int i=0; i<25; i++){
		cout << "Ho salvato " << nodi[i] << " + " << copie[i] << " \tesiti a profondità " << i << "\tcon efficienza: " << media[i]/numeri[i] << endl;
	}
	cout << "----- Salvati " << n_tot << " nodi in "<< M <<" chiavi -----" << endl;
}


void Stampa_parametri(){
	cout << "\n\n------------------------------------------------------\n";
	cout << "Grado iniziale:\t" << grado_iniziale << endl; 
	cout << "numero di chiavi iniziali:\t" << M << endl; 
	cout << "grado massimo di salvataggio:\t" << grado_salvataggio << endl; 
	//cout << "grado massimo di ricerca:    \t" << grado_ricerca << endl; 
	cout << "··········································" << endl; 
}



void Aggiorna_media(int grado, double item){
	
	media[grado] += item;
	numeri[grado] ++;

}


bool compara_mosse(Tavola a, Tavola b){
	return ((a.Triplette(0)-a.Triplette(1)) < (b.Triplette(0)-b.Triplette(1)));
}



/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini                                
   _/   _/    _/   _/         _/    _/   Matricola 09099A   
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica              
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano                       
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/
