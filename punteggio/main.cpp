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


using namespace std;

int8_t Valuta(Tavola game, int grado){
	
	int8_t esito;

	// Stampa il temporaneo numero di nodi salvati ad ogni livello
	//Info_parziali(grado);
	
	/************************************************************************/
	
	// comincia il calcolo dell'esito
	bool finito = game.Finito();
	
	if (finito){
		esito = game.Triplette(0) - game.Triplette(1);
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
						
			int8_t best_esito = -25;
			int8_t coeff;
			if(game.giocatore == 0)		// lo standard è che al meglio si perde.
				coeff = 1;
			else
				coeff = -1;

			int i = 0;
			// finché non trovi una strategia vincente, prova
			while(i < numero_mosse){
				copia = successive[i];
				i++;
				
				esito = Valuta(copia,grado+1);
				
				if(coeff*esito > best_esito)
					best_esito = coeff*esito;
			} // fine ciclo "per ogni mossa"
			
			esito = coeff * best_esito;
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
	int8_t risultato;
	
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
	
	//Stampa_finale(risultato);

	cout << endl;
	if (risultato == 0)
		cout << "La partita finisce al meglio PATTA" << endl;
	else if (risultato > 0)
		cout << "La partita finisce con il BIANCO che vince di "<< +risultato << " punti" << endl;
	else
		cout << "La partita finisce con il NERO che vince di "<< -risultato << " punti" << endl;

	cout << "··· Tempo utilizzato: " << fine - inizio << " s ···" << endl;

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

