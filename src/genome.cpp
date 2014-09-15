#include "../include/genome.hpp"

#include <string>

using namespace std;

Genome::Genome() {
  set_size(0);   // 1M nucleotides
  set_ratioGC_percent(50);   // 50% GC - 50% AT
  nucleotides_string_ = NULL;
}

Genome::~Genome() {
  if (nucleotides_string_ != NULL)
    delete[] nucleotides_string_;
}

void Genome::auto_generation(int size, int ratioGC) {
  set_size(size);
  set_ratioGC_percent(ratioGC);
  nucleotides_string_ = new char[size_]();
  
  int cpt, choice, subChoice;
  string values = "ATGC";

  // Création de la sequence
  for ( cpt = 0; cpt < size_; cpt++){
    choice = rand() % 100 + 0;
    subChoice = choice % 2;
    if(choice <= ratioGC_percent_){
      nucleotides_string_[cpt] = values[subChoice+2];
    } else{
      nucleotides_string_[cpt] = values[subChoice];
    }
  }
}

bool Genome::load_file(char* path) {
  return false;
}

void Genome::set_size(int size) {
  size_ = size;
  if (size_ < 100) {
    size_ = 100;
  } else if (size_ > 1000000000) {
    cout << "Ajustement de la taille du génome à 1G" << endl;
    size_ = 10000000000;
  }
}

void Genome::set_ratioGC_percent(int ratioGC) {
  ratioGC_percent_ = ratioGC;
  if (ratioGC_percent_ <= 0) {
    ratioGC_percent_ = 1;
  } else if (ratioGC_percent_ >= 100) {
    ratioGC_percent_ = 99;
  }
}

int Genome::size() {
  return size_;
}

int Genome::ratioGC_percent() {
  return ratioGC_percent_;
}

char* Genome::nucleotides_string() {
  return nucleotides_string_;
}


