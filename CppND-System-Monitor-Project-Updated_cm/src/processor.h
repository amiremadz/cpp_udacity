#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  void Extraction();
  float Utilization();  // TODO: See src/processor.cpp


  // TODO: Declare any necessary private members
 private:
 double prev_idle {};
 double prev_total {};
 double prev_time {};
 
};

#endif