Una **linked list** (lista collegata) è una struttura dati fondamentale in informatica usata per memorizzare una sequenza di elementi.

---

## Cos’è una linked list?

* È una **collezione di nodi**, dove ogni nodo contiene:

  * Un **dato** (ad esempio un numero, un carattere, una struttura...)
  * Un **puntatore** (o riferimento) al nodo successivo nella lista

---

## Come funziona?

* Il primo nodo è chiamato **testa** (head).
* Ogni nodo “punta” al nodo successivo, formando una catena.
* L’ultimo nodo punta a `NULL`, che indica la fine della lista.
* Non è necessario che gli elementi siano contigui in memoria, a differenza degli array.

---

## Vantaggi:

* Inserire o rimuovere elementi è facile e veloce (specialmente all’inizio o in mezzo), senza dover spostare gli altri elementi.
* La lista può crescere o ridursi dinamicamente senza dover definire dimensioni fisse.

---

## Svantaggi:

* Accesso casuale (ad esempio l’elemento i-esimo) è lento — devi scorrere i nodi uno per uno.
* Più overhead di memoria rispetto a un array, per via dei puntatori.
