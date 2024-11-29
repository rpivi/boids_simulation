# Boid Simulation

## Descrizione del progetto

Questo progetto implementa una simulazione bidimensionale del volo di stormi basata sull'algoritmo di Craig Reynolds del 1986. I "boids" (dall'inglese "bird-oid objects") sono oggetti la cui interazione crea un comportamento emergente: lo stormo. La simulazione include una visualizzazione grafica dei "boids" utilizzando la libreria SFML.

Per maggiori informazioni sul progetto,
consultare la relazione riguandante il codice ed i risultati della simulazione reperibile in questa repository.

### Tecnologie utilizzate
- **Linguaggio**: C++
- **Framework di visualizzazione**: [SFML](https://www.sfml-dev.org/)
- **Sistema di Build**: [CMake](https://cmake.org/)

## Struttura del progetto

Il progetto è organizzato nei seguenti file:

- **Codice Sorgente**
  - `main.cpp`: Inizializzazione della simulazione e gestione dell'input utente.
  - `birds.cpp`, `twodimensional.cpp`, `trianglesfml.cpp`: Contengono le definizioni delle classi e delle funzioni.
  - Header files: `birds.hpp`, `twodimensional.hpp`, `trianglesfml.hpp`.

- **Test**
  - `test.cpp`: Contiene i test per verificare la correttezza delle funzioni principali utilizzando il framework Doctest.

- **File di configurazione**
  - `.clangformat`: Per la formattazione del codice.
  - `CMakeLists.txt`: File di configurazione per la compilazione con CMake.

## Compilazione ed Esecuzione

### Requisiti
- **CMake** 3.16 o superiore
- **SFML** 2.5 o superiore

### Istruzioni di Compilazione ed Esecuzione
I comandi per compilare ed eseguire:
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build
cd build
./boids


