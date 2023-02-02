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
#include <string>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include "new_tavola.h"

using namespace std;

bool vicini(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if ((abs(x1-x2) <= 1) and (abs(y1-y2) <= 1))
		return true;
	else
		return false;
}

bool lontani(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if ((abs(x1-x2) <= 1) and (abs(y1-y2) <= 1))
		return false;
	else
		return true;
}

bool ortogonali(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if ((x1 == x2) or (y1 == y2))
		return true;
	else
		return false;
}

bool diagonali(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2){
	if (abs(x1-x2) == abs(y1-y2))
		return true;
	else
		return false;
}


uint8_t x_standard[16] = {0,0,0,0,1,2,3,3,3,3,2,1,1,1,2,2};
uint8_t y_standard[16] = {0,1,2,3,3,3,3,2,1,0,0,0,1,2,2,1};


uint8_t x_spiral(uint8_t mode,uint8_t l){	
	switch (mode){
		case 0:
			return x_standard[l];
		break;
		case 1:
			return y_standard[l];
		break;
		case 2:
			return 3-x_standard[l];
		break;
		case 3:
			return 3-y_standard[l];
		break;
		case 4:
			return y_standard[l];
		break;
		case 5:
			return x_standard[l];
		break;
		case 6:
			return 3-y_standard[l];
		break;
		case 7:
			return 3-x_standard[l];
		break;
	}
	return 0;
}

uint8_t y_spiral(uint8_t mode,uint8_t l){	
	switch (mode){
		case 0:
			return y_standard[l];
		break;
		case 1:
			return 3-x_standard[l];
		break;
		case 2:
			return 3-y_standard[l];
		break;
		case 3:
			return x_standard[l];
		break;
		case 4:
			return x_standard[l];
		break;
		case 5:
			return 3-y_standard[l];
		break;
		case 6:
			return 3-x_standard[l];
		break;
		case 7:
			return y_standard[l];
		break;
	}
	return 0;
}







/*************************** Da qui classe Tavola ***************************/





Tavola :: Tavola(){
	Inizio();
}




Tavola :: Tavola(string nome_file){

	ifstream in (nome_file);
	
	//uint8_t t,r,c;
	int t,r,c;
	int k = 0;
	
	Mossa move;
	
	Inizio();
	
	// Elimina la prima riga del file
	string trash;
	in >> trash;
	
	in >> t;
	
	while (!(in.eof())){
		

		in >> r;
		in >> c;

		if (t >= 4){
			k++;
			Non_mosso();
		}
		else {
			
			move.riga = r;
			move.colonna = c;
			move.tipo = t;
			k++;
			Stampa_mossa(move);
			Aggiungi_mossa(move);
		}
		in >> t;
	}
	in.close();
	Mostra();
}




void Tavola :: Inizio(){
/*
	// qui si faceva tutto per bene. La verità è che le possibilità
	//   sono solo 2: angolo o non angolo.
	// preparazione scacchiera
	for (uint8_t r=0; r<4; r++){
		for (uint8_t c=0; c<4; c++){
			// tutte le caselle sono vuote
			caselle[r][c].piena = false;
			// le caselle al bordo sono ammesse
			if ((r==0 or r==3) or (c==0 or c ==3))
				caselle[r][c].come = true;
			else
				caselle[r][c].come = false;
		}
	}

*/

	// preparazione scacchiera eliminando simmetrie
	for (uint8_t r=0; r<4; r++){
		for (uint8_t c=0; c<4; c++){
			// tutte le caselle sono vuote
			caselle[r][c].piena = false;
			// le caselle al bordo sono ammesse
			if ((r==0 and c==0) or (r==0 and c ==1))
				caselle[r][c].come = true;
			else
				caselle[r][c].come = false;
		}
	}


	// preparazione tessere in mano
	for (uint8_t t=0; t<4; t++){
		// per ogni tipo ci cono 2 pezzi
		pezzi[0].rimasti[t] = true;
		pezzi[0].tanti[t] = true;	// significa 2 pezzi
		pezzi[1].rimasti[t] = true;
		pezzi[1].tanti[t] = true;	// significa 2 pezzi
	}
	
	// parte il bianco
	giocatore = 0;
	
	return;
}




bool Tavola :: Finito(){
	// partita finisce se chi è in turno ha finito i pezzi di ogni tipo.
	for (uint8_t t=0; t<4; t++){
		if (pezzi[giocatore].rimasti[t]){
			return false;
		}
	}
	return true;
}




uint8_t Tavola :: Triplette(bool giocatore){

	uint8_t triplette = 0;	

	// calcolo terne in orizzontale
	for (uint8_t r=0; r<4; r++){
		// per ogni riga se le due centrali sono occupate
		if ((caselle[r][1].piena) && (caselle[r][2].piena)){
			// se sono occupate dal giocatore
			if ((caselle[r][1].come == giocatore) && (caselle[r][2].come == giocatore)){
				// controlla le due laterali ed eventualmente aggiungi un punto ogni volta.
				if ((caselle[r][0].piena) && (caselle[r][0].come == giocatore)){
					triplette ++;
				}
				if ((caselle[r][3].piena) && (caselle[r][3].come == giocatore)){
					triplette ++;
				}
			}
		}
	}
	
	// calcolo terne in verticale
	for (uint8_t c=0; c<4; c++){
		// per ogni colonna se le due centrali sono occupate
		if ((caselle[1][c].piena) && (caselle[2][c].piena)){
			// se sono occupate dal giocatore
			if ((caselle[1][c].come == giocatore) && (caselle[2][c].come == giocatore)){
				// controlla le due laterali ed eventualmente aggiungi un punto ogni volta.
				if ((caselle[0][c].piena) && (caselle[0][c].come == giocatore)){
					triplette ++;
				}
				if ((caselle[3][c].piena) && (caselle[3][c].come == giocatore)){
					triplette ++;
				}
			}
		}
	}
	
	// calcolo delle terne in diagonale
	for (uint8_t c=1; c<=2; c++){
		for (uint8_t r=1; r<=2; r++){
			// se una casella centrale è occupata dal giocatore
			if ((caselle[r][c].piena) && (caselle[r][c].come == giocatore)){
				// controlla la diagonaletta piccola ed eventualmente aggiungi un punto.
				if (r == c){
					if (((caselle[r+1][c-1].piena) && (caselle[r+1][c-1].come == giocatore))&&((caselle[r-1][c+1].piena) && (caselle[r-1][c+1].come == giocatore))){
						triplette ++;
					}
				}
				else {
					if (((caselle[r+1][c+1].piena) && (caselle[r+1][c+1].come == giocatore))&&((caselle[r-1][c-1].piena) && (caselle[r-1][c-1].come == giocatore))){
						triplette ++;
					}
				}	
				// e controlla anche la compagna sulla diagonalona
				if (r == 1){
					if (c == 1){
						// siamo nella casella 1,1
						// se la sua compagna di diagonalona è occupata dal giocatore				
						if ((caselle[2][2].piena) && (caselle[2][2].come == giocatore)){
							// allora controllo la diagonalona
							if ((caselle[0][0].piena) && (caselle[0][0].come == giocatore)){
								triplette ++;
							}
							if ((caselle[3][3].piena) && (caselle[3][3].come == giocatore)){
								triplette ++;
							}
						}
					}
					else {
						// siamo nella casella 1,2
						// se la sua compagna di diagonalona è occupata dal giocatore
						if ((caselle[2][1].piena) && (caselle[2][1].come == giocatore)){
							if ((caselle[3][0].piena) && (caselle[3][0].come == giocatore)){
								triplette ++;
							}
							if ((caselle[0][3].piena) && (caselle[0][3].come == giocatore)){
								triplette ++;
							}
						}						
					}					
				}
			}
		}
	}
	
	return triplette;
}




void Tavola :: Aggiungi_mossa(Mossa move){
	
	uint8_t r = move.riga;
	uint8_t c = move.colonna;
	uint8_t t = move.tipo;
	
	if(caselle[r][c].piena)
		cerr << "Attenzione! Casella già occupata" << endl;
	
	caselle[r][c].piena = true;
	caselle[r][c].come = giocatore;
	
	
	if (not pezzi[giocatore].rimasti[t])
		cerr << "Attenzione! Pezzo non esistente" << endl;
	
	// se ce ne erano 2, cambia solo il valore di "tanti"	
	if (pezzi[giocatore].tanti[t]){
		pezzi[giocatore].tanti[t] = false;
	}
	// se ce ne era 1, cambia il valore di "rimasti"
	else{
		pezzi[giocatore].rimasti[t] = false;
	}
	
	
	for (uint8_t ri=0; ri<4; ri++){
		for (uint8_t ci=0; ci<4; ci++){
			
			switch (t){
				case 0:{
					if (not caselle[ri][ci].piena){
						if (vicini(ri,ci,r,c)){
							caselle[ri][ci].come = true;
						}
						else{
							caselle[ri][ci].come = false;
						}
					}
				}
				break;
		
				case 1:{
					if (not caselle[ri][ci].piena){
						if (lontani(ri,ci,r,c)){
							caselle[ri][ci].come = true;
						}
						else{
							caselle[ri][ci].come = false;
						}
					}
				}
				break;
		
				case 2:{
					if (not caselle[ri][ci].piena){
						if (ortogonali(ri,ci,r,c)){
							caselle[ri][ci].come = true;
						}
						else{
							caselle[ri][ci].come = false;
						}
					}
				}
				break;
		
				case 3:{
					if (not caselle[ri][ci].piena){
						if (diagonali(ri,ci,r,c)){
							caselle[ri][ci].come = true;
						}
						else{
							caselle[ri][ci].come = false;
						}
					}
				}
				break;
			}
		}
	}	
	
	Passa_turno();
}




void Tavola :: Passa_turno(){
	
	giocatore = not giocatore;
}




void Tavola :: Non_mosso(){
	
	for (uint8_t r=0; r<4; r++){
		for (uint8_t c=0; c<4; c++){
			
			if (not caselle[r][c].piena)
				caselle[r][c].come = true;
		}
	}	
	
	Passa_turno();
}



uint8_t ordine_pezzi[4] = {1,0,2,3};

/*
vector<Mossa> Tavola :: Mosse_possibili(){

	// in questo caso cerco innanzitutto di conquistare il centro se son bianco
	// mentre di conquistare i bordi se son nero.
	// in secondo luogo di farlo con pezzi che occupano spazio.

	//uint8_t ordine_pezzi[4] = {1,0,2,3};

	vector<Mossa> mosse;
	
	uint8_t base;
	int8_t coeff;

	if (giocatore == 0){
		base = 15;
		coeff = -1;
	}
	else{
		base = 0;
		coeff = 1;
	}

	for (uint8_t l=0; l<16; l++){
		// se la casella è libera e ammessa			
		uint8_t r = x_standard[base+coeff*l];
		uint8_t c = y_standard[base+coeff*l];
		if((not caselle[r][c].piena)&&(caselle[r][c].come)){
			Mossa move;
			move.riga = r;
			move.colonna = c;
			// per tutti i tipi possibili di pezzi
			for (uint8_t t=0; t<4; t++){
				// se ce ne sono ancora
				uint8_t tipo = ordine_pezzi[t];
				if (pezzi[giocatore].rimasti[tipo]){
					// proponi quella mossa
					move.tipo = tipo;
					mosse.push_back(move);
				}
			}					
		}
	}
	return mosse;
}
*/


vector<Mossa> Tavola :: Mosse_possibili(){

	// in questo caso cerco innanzitutto di conquistare il centro
	// in secondo luogo di farlo con pezzi che occupano spazio.

	//uint8_t ordine_pezzi[4] = {1,0,2,3};

	vector<Mossa> mosse;
	
	for (uint8_t l=0; l<16; l++){
		// se la casella è libera e ammessa			
		uint8_t r = x_standard[15-l];
		uint8_t c = y_standard[15-l];
		if((not caselle[r][c].piena)&&(caselle[r][c].come)){
			Mossa move;
			move.riga = r;
			move.colonna = c;
			// per tutti i tipi possibili di pezzi
			for (uint8_t t=0; t<4; t++){
				// se ce ne sono ancora
				uint8_t tipo = ordine_pezzi[t];
				if (pezzi[giocatore].rimasti[tipo]){
					// proponi quella mossa
					move.tipo = tipo;
					mosse.push_back(move);
				}
			}					
		}
	}
	return mosse;
}



/*
// QUI LE MOSSE VENGONO PRESENTATE IN ORDINE CASUALE
vector<Mossa> Tavola :: Mosse_possibili(){
	
	vector<Mossa> mosse;
	
	for (uint8_t r=0; r<4; r++){
		for (uint8_t c=0; c<4; c++){
			// se la casella è libera e ammessa			
			if((not caselle[r][c].piena)&&(caselle[r][c].come)){
				Mossa move;
				move.riga = r;
				move.colonna = c;
				// per tutti i tipi possibili di pezzi
				for (uint8_t t=0; t<4; t++){
					// se ce ne sono ancora
					if (pezzi[giocatore].rimasti[t]){
						// proponi quella mossa
						move.tipo = t;
						mosse.push_back(move);
					}
				}					
			}
		}
	}
	return mosse;
}
*/

bool Tavola :: bit_single(uint8_t m, uint8_t l){
	
	if (l%2 == 0)
		return caselle[x_spiral(m,l/2)][y_spiral(m,l/2)].piena;
	else
		return caselle[x_spiral(m,(l-1)/2)][y_spiral(m,(l-1)/2)].come;
}
 

uint8_t Tavola :: Best_mode(){

	bool mode[8] = {true};
	bool unico = false;
	
	uint8_t l = 0;
	
	// il massimo valore di l è 31. Se è ancora nel while vuol dire che è simmetrica
	// quindi qualsiasi è la risposta giusta
	
	while ((not unico) && (l<32)){

		// finché non trovi un 1
		uint8_t m = 0;
		
		// parti dal primo ancora true
		while (mode[m] == false){
			m ++;
		}

		// cerca il primo ancora true e con un 1
		while ((m<8) && (bit_single(m,l) == 0)){
			m ++;
			while ((m<8) && (mode[m] == false)){
				m ++;
			}
		}
		// se ne hai trovato uno
		if (m<8){
			// metto a false tutti quelli prima
			// è sciocco, ma quelli che lo sono già li ri-metto false
			for (uint8_t i=0; i<m; i++){
				mode[i] = false;
			}
			// per ora ne ho visto uno solo
			unico = true;
			// vado avanti
			while (m<8){
				if (mode[m] == true){
					if (bit_single(m,l) == 1){
						unico = false;
					}
					else{
						mode[m] = false;
					}			
				}
				m ++;
			}
		}
		l ++;
	}
	
	// quando ce n'è uno solo scorri finché non lo trovi
	// quando è indifferente va bene il primo.
	uint8_t m = 0;
	while (mode[m] == false){
		m ++;
	}
	return m;
}


uint64_t Tavola :: chiocciola(){
	// caso nuovo, con molti meno bit in cui inserisco anche il giocatore in turno.
	uint8_t m = Best_mode();
	
	bool a;
	int8_t b;
	uint64_t result = 0;
	uint64_t coeff = 1;
	
	// il bit dell'unità è quello del giocatore
	result = giocatore;
	
	// poi si mettono i bit dei pezzi rimanenti
	for(uint8_t l=0; l<8; l++){
		
		if(pezzi[(l-(l%4))/4].rimasti[l%4]){
			if(pezzi[(l-(l%4))/4].tanti[l%4]){
				b = 2;
			}
			else{
				b = 1;
			}
		}
		else{
			b = 0;
		}
		coeff = 3*coeff;
		result += coeff * b;
	}

	// poi si mettono i bit della scacchiera
	for(uint8_t l=0; l<32; l++){
		a = bit_single(m,l);
		
		coeff = 2* coeff;
		result += coeff * a;
	}
	return result;
}

/*
uint64_t Tavola :: chiocciola(){
	// per ora lo faccio a 49 bit, in cui inserisco anche il giocatore in turno.
	uint8_t m = Best_mode();
	
	bool a;
	uint64_t result = 0;
	uint64_t coeff = 1;
	
	for(uint8_t l=0; l<49; l++){
		if(l<8){
			a = pezzi[(l-(l%4))/4].rimasti[l%4];	
		}
		else if (l<16){
			a = pezzi[((l-8)-(l%4))/4].tanti[l%4];
		}
		else if (l<48){
			a = bit_single(m,l-16);
		}
		else if (l<49){
			a = giocatore;
		}
		else{
			cerr << "ERRORE!" << endl;
		}

		result += coeff * a;
		coeff = 2* coeff;
	}
	return result;
}	
*/	


 

void Tavola :: Mostra(){
	cerr << "@: " << chiocciola() << endl;
	cerr << "       ▁▁▁▁▁▁▁▁" << endl;


	char simbolo[4] = {'.','o','+','x'};
	
	for (uint8_t r=0; r<4; r++){
		
		cerr << simbolo[r] << ' ';
		
		if (pezzi[0].rimasti[r]){
			if(pezzi[0].tanti[r]){
				cerr << "▓ ▓";
			}
			else{
				cerr << "  ▓";
			}
		}
		else{
			cerr << "   ";
		}
		
		cerr << " ▕";
		for (uint8_t c=0; c<4; c++){

			
			if (caselle[r][c].piena){
				if (caselle[r][c].come == 1)
					cerr << "░░";
				else
					cerr << "▓▓";
			}
			else if (caselle[r][c].come)
				cerr << "╺╸";
			else
				cerr << "  ";
		}
		cerr << "▏ ";
		
		if (pezzi[1].rimasti[r]){
			if(pezzi[1].tanti[r]){
				cerr << "░ ░";
			}
			else{
				cerr << "░  ";
			}
		}
		else{
			cerr << "   ";
		}

		cerr << ' ' << simbolo[r] << endl;
		
	}	
	
	cerr << "       ▔▔▔▔▔▔▔▔" << endl;
	
	if (giocatore==0)
		cerr << "  ▓ Tocca al bianco ▓" << endl;
	else
		cerr << "   ░ Tocca al nero ░" << endl;
}


void Stampa_mossa(Mossa move){
	string nomi_pezzi[4] = {"VICINO     \t","LONTANO    \t","ORTOGONALE \t","DIAGONALE  \t"};
	cerr << "Mettere il pezzo " << nomi_pezzi[move.tipo] << " in (" << +move.riga << " , " << +move.colonna << ")" << endl;

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
