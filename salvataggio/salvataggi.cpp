/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini                                
   _/   _/    _/   _/         _/    _/   Matricola 09099A   
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica              
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano                       
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;




long int hash_code(long int chiocciola){
	return chiocciola % M;
}


void azzera(){
	salvati.resize(M);
	
	for(long int i=0; i<M; i++){
		salvati[i] = NULL;
	}
}


void Save_esito(uint64_t codex, exitus esito){
	salvataggio* id;
	long int indice = hash_code(codex);
	id = salvati[indice];
	
	salvataggio* nuovo = new salvataggio;
	nuovo->codice = codex;
	nuovo->esito = esito;
	nuovo->next = id;
	salvati[indice] = nuovo;
	n_tot ++;
}


exitus Cerca_esito(uint64_t codex){				// se c'è, ritorna l'esito, altrimenti non esistente
	salvataggio* id;
	id = salvati[hash_code(codex)];
	while (id!=NULL){
		if(id->codice == codex){
			return id->esito;
		}
		id = id->next;
	}
	return non_esistente;
}


void Aggiorna_hash(){
	cerr << "Iniziata ricalibrazione" << endl;
	long int old_length = salvati.size();
	salvataggio* head = NULL;
	salvataggio* tail = NULL;
	long int i=0;

	// crea una listona unica a serpentone da head.
	
	while (i < old_length && salvati[i] == NULL){
		i++;
	}
	if(i < old_length){
		head = salvati[i];
		tail = salvati[i];
		salvati[i] = NULL;
	}
	while (tail->next != NULL){
		tail = tail->next;
	}
	i++;
	while(i < old_length){
		if (salvati[i] != NULL){
			tail->next = salvati[i];
			
			while (tail->next != NULL){
				tail = tail->next;
			}	
		}
		i++;
	}
	
	// ridimensiono e rimetto tutto a vuoto
	
	azzera();
	
	// riempio usando i nuovi hash
	
	while (head!=NULL){
		long int indice = hash_code(head->codice);
		tail = head->next;
		head->next = salvati[indice];
		salvati[indice] = head;
		head = tail;
	}
	cerr << "Terminata ricalibrazione" << endl;		
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
