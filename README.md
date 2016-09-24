Progetto di Sistemi Multimediali
===============================================================

Questo progetto in C++ e OpenGL è un nato come progetto universitario.
Si tratta di un gioco basato su un labirinto, in cui lo scopo è quello di disattivare gli allarmi in tempo, altrimenti si perde.


### Prerequisiti

Per poter Eseguire il progetto è necessario avere la suite di OpenGL e OpenAL instalata.
### How To

Per compilare il progetto, entrare nella cartella e digitare:
```bash
g++ main.cpp -o main.out -lGL -lGLU -lglut -lalut -lopenal

```

Per eseguire, è sufficiente digitare:
```bash
./main.out
```

Aggiungendo il paramtro **debug** al comando di esecuzione, si attiverà la scrittura dei log su console