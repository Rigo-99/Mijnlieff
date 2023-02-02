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
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "new_tavola.h"

using namespace std;



#ifndef __General__
#define __General__

struct exitus {
	bool vinto;
	bool chi;
};
// true,0 = ha vinto 0
// true,1 = ha vinto 1
// false,1 = finisce pari
// false,0 = ESITO NON TROVATO



struct salvataggio {
	uint64_t codice;
	exitus esito;
	salvataggio* next;
};


int inizio;
int fine;

int grado_iniziale = 0;
int grado_save_min = 4;
int grado_save_max = 10;
int grado_save_mod = 2;
int grado_diff_ricerca = 2;
int grado_show = 5;

bool bianco = 0;
bool nero = 1;

long int M =80000051;						// numero di hash values
long int A = 50;							// numero di elementi che voglio in media per ogni chiave	
//exitus vinto_bianco {true,0};				// è un numero a caso
//exitus vinto_nero {true,1};				// è un numero a caso
exitus esito_patta {false,1};				// è un numero a caso
exitus non_esistente {false,0};				// è un numero a caso

vector <salvataggio*> salvati;				// vettore globale

long int nodi[25] = {0};
long int copie[25] = {0};
long int n_tot = 0;

double media[25] = {0};
int numeri[25] = {0};

vector <int> tempi;
vector <long int> n_nodi;




int numero_mosse(string nome_file);
void Info_parziali(int grado);
int8_t Vittoria (bool giocatore);
bool da_equilibrare();
long int Nuova_M();
void Stampa_vettore();
void Stampa_tempi();
bool da_cercare(int grado);
bool da_salvare(int grado);
void Stampa_finale(int8_t risultato);
void Prendi_parametri();
void Aggiorna_media(int grado, double item);
bool compara_mosse(Tavola a, Tavola b);


#endif // __General__

/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini                                
   _/   _/    _/   _/         _/    _/   Matricola 09099A
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica              
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano                       
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/
