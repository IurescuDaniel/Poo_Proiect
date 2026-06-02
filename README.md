# 🔍 Motor de Căutare Simplu pentru Documente Text

> Temă: Motor de Căutare Simplu pentru Documente Text  
> Limbaj: **C++17**
> Nume: Iurescu Daniel Liviu
> Grupa: 3123B

---

## 📋 Descriere

Acest proiect implementează un **motor de căutare full-text** în C++17, capabil să indexeze colecții de documente `.txt` și să permită căutarea eficientă a cuvintelor. Programul parcurge recursiv un director, construiește un index inversat și returnează documentele relevante împreună cu numărul de apariții al cuvântului căutat.

---

## 🏗️ Structura Proiectului

| Director / Fișier | Rol în cadrul aplicației |
|---|---|
| `src/` | Cod sursă C++ — clasele `Document`, `Index`, `Observer`, `Logger` și `main.cpp` |
| `tests/` | Teste unitare automate pentru validarea logicii de indexare și căutare |
| `Teste_Cautare/` | Colecție de documente `.txt` în română folosite pentru testare |
| `Makefile` | Automatizează compilarea și rularea pe Linux |
| `baza_date.index` | Index inversat salvat persistent pe disc *(generat automat)* |
| `cautari.log` | Jurnal generat de clasa `Logger` la fiecare căutare *(generat automat)* |

---

## ⚙️ Compilare și Rulare

### Cerințe de sistem
- Compilator **g++** cu suport C++17
- Sistem de operare **Linux / Ubuntu**

### Compilare și rulare

```bash
make
./aplicatie_motor
```
