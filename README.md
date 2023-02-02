# Mijnlieff
Codice usato per risolvere il gioco Mijnlieff con esplorazione dell'albero delle possibili partite.

Nelle tre cartelle ci sono tutti i files necessari alla compilazione dei tre diversi algoritmi utilizzati:
- ##punteggio: Data una posizione iniziale, l'algoritmo esegue una ricerca completa del sottoalbero albero delle possibili evoluzioni e restituisce l'esito della partita nel caso in cui i due giocatori giocassero in maniera ottima ossia cercando di massimizzare il proprio punteggio finale sull'avversario.

- ##vittoria: Data una posizione iniziale, l'algoritmo esegue una ricerca parziale del sottoalbero delle possibili evoluzioni e restituisce l'esito della partita nel caso in cui i due giocatori giocassero in maniera quasi-ottima, ossia cercando di vincere (indipendentemente dallo scarto di punti sull'avversario).

- ##salvataggio: L'algoritmo di ricerca è il medesimo di quello della versione "vittoria", ma permette di salvare esiti di conformazioni visitate, in modo tale da non dover ri-esplorare il sottoalbero di un nodo che è già stato esplorato.

Nella cartella "files_iniziali" ci sono alcuni files di configurazioni iniziali "iniziato_X.dat" dove X indica il numero di mosse effettuate dall'inizio della partita per arrivare nella configurazione. Ovviamente il file iniziato_0.dat è l'inizio di ogni partita.

