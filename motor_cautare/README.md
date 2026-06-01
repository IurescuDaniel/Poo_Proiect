# Motor de Căutare Full-Text (Proiect POO)

Acesta este un motor de căutare full-text dezvoltat în C++17, compatibil cu mediile de dezvoltare Linux. Proiectul indexează toate fișierele `.txt` dintr-un director specificat (inclusiv subdirectoare) și permite căutarea eficientă a cuvintelor, returnând lista fișierelor în care acestea apar.

## Structura Proiectului
- `src/` - conține codul sursă (clasele `Document`, `Index` și `main.cpp`).
- `docs/` - conține documentația proiectului (inclusiv diagrama UML).
- `.gitignore` - configurare pentru ignorarea fișierelor compilate pe Linux.

## Cerințe de Sistem
- Un compilator C++ ce suportă standardul C++17 (ex. `g++`).
- Mediu Linux (ex. Ubuntu via WSL sau Remote SSH).

## Instrucțiuni de Compilare și Rulare
Poți compila acest proiect folosind `g++` din terminal:
```bash
g++ -std=c++17 src/Document.cpp src/Index.cpp src/main.cpp -o motor_cautare
```

Rularea programului:
```bash
./motor_cautare
```
