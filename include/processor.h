#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // Done: Declare any necessary private members
 private:
    float activeJiffies1CycleAgo_{0};
    float idleJiffies1CycleAgo_{0};

    float activeJiffies2CyclesAgo_{0};
    float idleJiffies2CyclesAgo_{0};

    float activeJiffies3CyclesAgo_{0};
    float idleJiffies3CyclesAgo_{0};
};

#endif