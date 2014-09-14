#ifndef FastaFormat_H
#define FastaFormat_H

#include <iostream>
#include <string>
#include <fstream>


#include "../include/genome.hpp"

class FastaFormat {
  public:
    // Constructeurs
    FastaFormat()
      { set_file_name("default"); file_is_open_ = false;}
    ~FastaFormat()
      {close();}
    
    // methode virtuelle pure
    virtual void write(Genome* genome, struct intervalle* inter) = 0;

    void set_file_name(std::string file_name)
      { file_name_ = file_name; }
    
  protected:
    std::string file_name_;
    std::ofstream file_stream_;
    bool file_is_open_;


    void open();
    void close();
};


class FastaFormatUn: public FastaFormat {
  public:
    
    void write(Genome* genome, struct intervalle* inter);
    
  private:
};




#endif
