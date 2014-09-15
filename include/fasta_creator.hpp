#ifndef FASTACREATOR_H
#define FASTACREATOR_H

#include <iostream>
#include <sstream>

#include "../include/genome.hpp"
#include "../include/fasta_format.hpp"
#include "../include/sequence_coverage.hpp"

class FastaCreator {
  public:
    // Constructeurs
    FastaCreator(Genome *genome);
    ~FastaCreator();
    
    void generate(int coverage, FastaFormat* my_file);

    /**
     * Renvoi le pourcentage de couverture courant.
     * @return pourcentage de couverture.
     **/
    int get_coverage();

    /**
     * Renvoi un ségment de la chaîne de nucléotides générée au début du traitement.
     * @param debut
     *		index du début de la chaîne à récupérer.
     * @param longueur
     *		longueur de la chaîne à récupérer. Si la séquence demandée dépasse la taille de la chaîne, la séquence renvoyée sera tronquée.
     * @return sous chaîne de la chaîne de nucléotides.
     **/
	std::string get_chaine(int debut, int longueur);

	/**
	 * Taille du fichier .fasta courant.
	 * @return taille du fichier en octet.
	 **/
	int get_file_size();

	/**
	 * Retourne le tableau de la couverture actuelle au format JSON.
	 * @return chaîne représentant la couverture au format JSON.
	 * 		ex : [{"debut" : 150, "fin" : 500}, {"debut" 650, "fin" : 750}]
	 **/
	std::string get_coverage_json();
    
    
  private:
    Genome* genome_;
    int fc_coverage;
    
    FastaCreator();

    FastaFormat* ff_file;
	SequenceCoverage* seq;
    
		
  
};


#endif
