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
#include <math.h>
#include <algorithm>
#include <vector>
#include <ctime>
#include "tutto.h"
#include "new_tavola.h"
#include "roba.cpp"
#include "salvataggi.cpp"


using namespace std;

exitus Valuta(Tavola game, int grado){
	
	// Stampa il temporaneo numero di nodi salvati ad ogni livello
	Info_parziali(grado);
	
	uint64_t chiocciola;
	//bool chiocciola_calculated = false;
	exitus esito;
	
	if (da_cercare(grado)){
		chiocciola = game.chiocciola();
		//chiocciola_calculated = true;
	
		// Controlla se i calcoli per una configurazione equivalente sono già stati fatti e salvati.
		esito = Cerca_esito(chiocciola);
		
		if ((esito.vinto != non_esistente.vinto)&&(esito.chi != non_esistente.chi)){
			// conformazione già presente!
			copie[grado]++;
			return esito;
		}
	}
	
	/************************************************************************/
	
	// comincia il calcolo dell'esito
	bool finito = game.Finito();
	
	if (finito){

		if (game.Triplette(0) == game.Triplette(1)){
			esito = esito_patta;
		}
		else if (game.Triplette(0) > game.Triplette(1)){
			esito = {true,0};		// vince il giocatore 0
		}
		else{
			esito = {true,1};		// vince il giocatore 1
		}
	}
	
	else{
		// Partita non ancora finita
		// crea l'elenco delle mosse possibili
		
		vector<Mossa> elenco_mosse = game.Mosse_possibili();
		
		int numero_mosse = int(elenco_mosse.size());
				

		if (numero_mosse == 0){
			// se deve per forza passare
			game.Non_mosso();
			esito = Valuta(game,grado+1);			
		}
		else{
			// se si possono fare mosse
			Tavola copia;
			
			vector<Tavola> successive;
			
			for (int i=0; i<numero_mosse; i++){
				copia = game;
				copia.Aggiungi_mossa(elenco_mosse[i]);
				successive.push_back(copia);
			}
			/*
			// Ordina le mosse in base a vantaggio del bianco crescente
			sort (successive.begin(), successive.end(), compara_mosse);
			// se giocatore è bianco, la mossa migliore è l'ultima!
			if (game.giocatore == bianco){
				reverse (successive.begin(), successive.end());
			}
			*/
			
			
			bool vinto = false;
			exitus best_esito = {true, not game.giocatore};		// lo standard è che al meglio si perde.
			
			int i = 0;
			// finché non trovi una strategia vincente, prova
			while((not vinto) && (i<numero_mosse)){
				copia = successive[i];
				i++;
				
				esito = Valuta(copia,grado+1);
				
				if(esito.vinto){
					if(esito.chi == game.giocatore){
						best_esito = esito;
						vinto = true;
					}
				}
				else {
					best_esito = esito;		// non ci si arriva se si ha già trovato una strategia vincente
				}
			} // fine ciclo "per ogni mossa"
			
			if(numero_mosse > 1)
				Aggiorna_media(grado, 1- ((i-1)/(numero_mosse-1)));
			
			esito = best_esito;
		} // fine "se ci sono mosse"
	} // fine "partita non terminata"
	
	
	if(da_salvare(grado)){
		//if (not chiocciola_calculated)
		//	chiocciola = game.chiocciola();
		Save_esito(chiocciola,esito);
		nodi[grado]++;
	}
	
	return esito;
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int main (int argc, char *argv[]){

	Tavola game;
	exitus risultato;
	
	if(argc != 7){
	   	cout << "ERRORE: PARAMETRI NON CORRETTI" << endl;
		cout << "· nome file iniziale" << endl;				// 1
		cout << "· numero di chiavi" << endl;				// 2
		cout << "· grado di stampa" << endl;				// 3
		cout << "· grado minimo di salvataggio" << endl;	// 4
		cout << "· grado massimo di salvataggio" << endl;	// 5
		cout << "· modulo grado di salvataggio" << endl;	// 6
		//cout << "· differenza range per ricerca" << endl;	// 7
		return -1;
	}
		
	//cerr << "Inizio dal file: " << argv[1] << endl;
	Tavola gioco(argv[1]);
	grado_iniziale = numero_mosse(argv[1]);

	M = atol(argv[2]);
	grado_show = atoi(argv[3]);	
	grado_save_min = atoi(argv[4]);	
	grado_save_max = atoi(argv[5]);	
	grado_save_mod = atoi(argv[6]);
	//grado_diff_ricerca = atoi(argv[7]);

	game = gioco;

	azzera();
	
	inizio = time(NULL);
	risultato = Valuta(game,grado_iniziale);
	fine = time(NULL);
	
	Stampa_finale(risultato);

	Stampa_tempi();
	
	cerr << "**************** E N D ****************" << endl;
	
	return 0;
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

