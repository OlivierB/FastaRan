#include <iostream>
#include <time.h>
#include <string>

#include "../include/fasta_creator.hpp"
#include "../include/genome.hpp"
#include "../include/fasta_format.hpp"
#include "../include/websocket_watcher.hpp"

// Structure
struct s_parameters {
  int size;
  int ratioGC;
  int coverage;
};


// Prototypes des fonctions
void DisplayHelp(char*);
void DisplayParameters(struct s_parameters params);
bool GetParameters(int argc, char** argv, struct s_parameters* params);


// Déclaration de std pour les I/O
using namespace std;

int main(int argc, char** argv) {
  // initialisation du random
  srand (time(NULL));
  
  // Nom du fichier de sortie
  string fileName = "fichier.fasta";
  
  // Récupération des paramètres de la ligne de commande
  struct s_parameters params;
  if (!GetParameters(argc, argv, &params)) {
    DisplayHelp(argv[0]);
    return 1;
  }
  
  // Affichage des entrées
  DisplayParameters(params);
  
  // Création du génome de travail
  Genome genome;
  genome.auto_generation(params.size, params.ratioGC);

  // Création du fichier de sortie
  FastaFormatUn myFile;
  myFile.set_file_name(fileName);
  
  // Algo principal
  FastaCreator fastaCreator(&genome);

  WebSocketWatcher watcher(&fastaCreator);
  watcher.run(9002);
  
  // Go !
  fastaCreator.generate(params.coverage, &myFile);

  watcher.join();

  return 0;
}

// Affichage de l'aide
void DisplayHelp(char* name) {
  cout << "FastaRan Programme" << endl;
  cout << "Utilisation : " << name << " ARG1 ARG2 ARG3" << endl;
  cout << "ARG1 : Taille du genome (en Mb)" << endl;
  cout << "ARG2 : Taux GC par rapport à AT (en %)" << endl;
  cout << "ARG3 : Taux de recouvrement du genome (en %)" << endl;
}

// Récupère les paramètres de la ligne de commande
//  dans une structure
bool GetParameters(int argc, char** argv, struct s_parameters* params) {
  // Gestion des paramètres
  if (argc != 4) {
    cout << "ERREUR : Trois paramètres attendus" << endl;
    return false;
  }
  
  // ARG1 : taille
  params->size = atoi(argv[1]);
  if (params->size < 1)
    params->size = 1;
  params->size = params->size * 1000000;
  
  // ARG 2 : ratio GC
  params->ratioGC = atoi(argv[2]);
  if (params->ratioGC < 0)
    params->ratioGC = 0;
  else if (params->ratioGC > 100)
    params->ratioGC = 100;
    
  // ARG 3 : recouvrement
  params->coverage = atoi(argv[3]);
  if (params->coverage < 0)
    params->coverage = 0;
  else if (params->coverage > 100)
    params->coverage = 100;
    
  return true;
}

// Affiche les paramètres de la structure
void DisplayParameters(struct s_parameters params) {
  cout << "Taille du génome : " << params.size << " nucléotides (" << params.size/1000000 << "M)" << endl;
  cout << "Ratio GC : " << params.ratioGC << "%" << endl;
  cout << "Recouvrement génome : " << params.coverage << "%" << endl;
}


