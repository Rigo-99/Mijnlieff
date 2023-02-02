/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini              
   _/   _/    _/   _/         _/    _/   Matricola 09099A                
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica           
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano  
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/
#include <vector>
#include <string>
#include <cstdint>


#ifndef __Tavola__
#define __Tavola__


using namespace std;

struct Casella {
	bool piena;
	bool come;
};

struct Mano {
	bool rimasti[4];
	bool tanti[4];
};


struct Mossa{
	uint8_t riga;
	uint8_t colonna;
	uint8_t tipo;
};

void Stampa_mossa(Mossa move);


uint8_t x_spiral(uint8_t mode,uint8_t l);
uint8_t y_spiral(uint8_t mode,uint8_t l);

class Tavola {

public:

	Casella caselle[4][4];
	Mano pezzi[2];	
	bool giocatore;
	
// constructors
	Tavola();
	Tavola(string nome_file);

// destructor
	~Tavola(){};

// methods
	void Passa_turno();
	void Inizio();
	bool Finito();
	uint8_t Triplette(bool giocatore);
	vector<Mossa> Mosse_possibili();
	void Aggiungi_mossa(Mossa move);
	void Non_mosso();	
	uint8_t Best_mode();
	bool bit_single(uint8_t m, uint8_t l);	
	uint64_t chiocciola();						// codice identificativo posizione tolte le simmetrie
	bool Schiacciante();	
	void Mostra();
};



#endif // __Tavola__




/************************************************************************
*************************************************************************
    _/_/_/     _/    _/_/_/     _/_/_/    Francesco Righini              
   _/   _/    _/   _/         _/    _/   Matricola 09099A                
  _/_/_/     _/   _/  _/_/   _/    _/   Dipartimento di Fisica           
 _/   _/    _/   _/    _/   _/    _/   Università degli Studi di Milano  
_/    _/   _/    _/_/_/     _/_/_/    francesco.righini@studenti.unimi.it
*************************************************************************
*************************************************************************/
