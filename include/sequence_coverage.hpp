#ifndef SEQUENCECOVERAGE_H
#define SEQUENCECOVERAGE_H

#include <iostream>
#include <vector>


struct intervalle
{
  int start;
  int end;
};


class SequenceCoverage {
  public:
    // Constructeurs
    SequenceCoverage();
    SequenceCoverage(int start, int end);
    ~SequenceCoverage();
    
    
    // Ajouter une nouvelle séquence
    void add_sequence(int start, int end);
    // taux de recouvrement en %
    int ratio_coverage_percent();
    

    // getters
    int start() { return start_; }
    int end() { return end_; }
    int sum_coverage() { return sum_coverage_; }
    std::vector<struct intervalle>* coverage() { return &coverage_; }
    std::vector<struct intervalle>* sequences_list() { return &sequences_list_; }


    // affichage
    void print_coverage();
    void print_sequences();
    void print_stats();


  private:
    int start_;
    int end_;
    int sum_coverage_;
    // calcul de la couverture
    std::vector<struct intervalle> coverage_;
    // liste des opérations
    std::vector<struct intervalle> sequences_list_;
};


#endif
