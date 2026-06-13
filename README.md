# 💻 Projets en Langage C | C Programming Academic Portfolio

Active repository dedicated to documenting my software development projects in C. This portfolio serves as technical evidence of my computer science foundations, structural logic, and low-level
programming skills for academic applications.

---

## 🇫🇷 Version Française

### 🛠️ Compétences Techniques Démontrées
* **Gestion Rigoureuse de la Mémoire :** Allocation dynamique (`malloc`, `calloc`, `free`), manipulation de pointeurs, structures de données (listes, piles, files) et prévention des fuites de mémoire
 (*memory leaks*).
* **Modularité et Conception :** Séparation stricte entre les interfaces (`.h`) et les implémentations (`.c`), favorisant la réutilisabilité et la clarté du code.
* **Automatisation et Normes :** Automatisation de la compilation via `Makefile` avec des flags de diagnostic stricts (`-Wall -Wextra -Werror`).



## EN English Version
### 🛠️  Core Technical Competences
* Rigorous Memory Management: Dynamic memory allocation (malloc, calloc, free), pointer arithmetic, custom data structures, and preventing memory leaks.
* Modular Software Design: Strict separation of interface (.h) and implementation (.c) files to maintain clean, scalable, and reusable codebases.
* Automation & Compilation Standards: Compilation automation using Makefile configuration embedded with strict diagnostic flags (-Wall -Wextra -Werror).






## 📂  Résume du Projet/ Project Summary 

### 📊 [01_analyseur_statistique] /[01_statistical_analyzer]

## FR Version
* **Description :** Analyseur statistique modulaire axé sur le traitement rigoureux des données. Le système reçoit un vecteur de nombres et calcule des métriques essentielles telles que la moyenne arithmétique, les valeurs maximale et minimale.
* **Concepts appliqués :** Structure de données modulaire, pointeurs/vecteurs (`float`), compilation rigoureuse avec les options GCC `-Wall -Wextra -Werror` et automatisation de la compilation via `Makefile`.
* **État :** Terminé et fonctionnel.

## EN Version
* **Description:** A modular statistical analyzer focused on rigorous data processing. The system receives a vector of numbers and calculates essential metrics such as arithmetic mean, maximum and minimum values.
* **Applied Concepts:** Modular data structure, pointers/vectors (`float`), rigorous compilation with GCC flags (`-Wall -Wextra -Werror`) and compilation automation via `Makefile`.
* **Status:** Completed and functional.

  
## 🛠️ Como Compilar e Executar os Projetos

Cada projeto possui o seu próprio arquivo `Makefile` independente dentro de sua respectiva subpasta. Para rodar qualquer um deles, você só precisa de um compilador GCC e da ferramenta Make:

1. Navegue até a pasta do projeto desejado:
   ```bash
   cd 01_analisador_estatistico

 2. Compile o código automaticamente:
    Bash
   make

 3. Execute o programa gerado:
      Bash
./analisador
