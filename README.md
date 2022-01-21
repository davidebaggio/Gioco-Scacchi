Progetto Scacchi in C++ per corso di Laboratorio di Programmazione:

Comandi su console
$cd build
$cmake ..
$make

In caso il "cmake .." non funzionasse perchè non trova il generatore corretto (a causa dell'implementazione su vari sistemi operativi differenti):

$rm CMakeCache.txt
$cmake -G "MinGW Makefiles" ..
$make

I file di log rispettivamente per la partita PC e CC sono presenti nella cartella build sotto forma di file logPC.txt e logCC.txt
E' importante che non si usino altri file .txt per il replay perchè sono generati in modo da contenere altre informazioni importanti quali per esempio le mosse speciali (file spec.txt).
