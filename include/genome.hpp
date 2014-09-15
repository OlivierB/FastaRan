#ifndef GENOME_H
#define GENOME_H

#include <iostream>


class Genome {
  public:
    // Constructeurs
    Genome();
    ~Genome();
    
    // génération du génome
    void auto_generation(int size, int ratioGC);
    // Chargement d'un génome à partir d'un fichier
    bool load_file(char* path);
    
    // Getter
    int size();
    int ratioGC_percent();
    char* nucleotides_string();
    
  private:
    // Nombre de nucléotides
    int size_;
    // Ratio de GC par rapport aux AT
    int ratioGC_percent_;
    // Chaine de nucléotides
    char* nucleotides_string_;
  
    // Setter
    void set_size(int size);
    void set_ratioGC_percent(int ratioGC);
};
//LOULLLL

#endif
