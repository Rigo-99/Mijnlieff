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
//#include "salvataggi.cpp"


using namespace std;

exitus Valuta(Tavola game, int grado){
	
	exitus esito;

	// Stampa il temporaneo numero di nodi salvati ad ogni livello
	Info_parziali(grado);
	
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
	
	nodi[grado]++;
	
	return esito;
}


/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

int main (int argc, char *argv[]){

	Tavola game;
	exitus risultato;
	
	if(argc != 2){
		cout << "ERRORE: PARAMETRI NON CORRETTI" << endl;
		cout << "· nome file iniziale" << endl;
		return -1;
	}
		
	//cerr << "Inizio dal file: " << argv[1] << endl;
	Tavola gioco(argv[1]);
	grado_iniziale = numero_mosse(argv[1]);

	game = gioco;

	inizio = time(NULL);
	risultato = Valuta(game,grado_iniziale);
	fine = time(NULL);
	
	Stampa_finale(risultato);

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

