#include "processor.h"
#include "linux_parser.h"

// Done: Return the CPU utilization for the last 3 screen updates (around every 3s)
float Processor::Utilization() {
    std::vector<long> currentActiveIdleJiffies = LinuxParser::ActiveIdleJiffies();
    float utilization = 0;
    
    // make sure no division over 0 happens
    if(currentActiveIdleJiffies[1]+currentActiveIdleJiffies[1]-activeJiffies3CyclesAgo_-idleJiffies3CyclesAgo_>0){
        // utilization = (current active jiffies - last active jiffies)/(current total jiffies - last total jiffies)
        utilization = (currentActiveIdleJiffies[0]-activeJiffies3CyclesAgo_)/(currentActiveIdleJiffies[0]+currentActiveIdleJiffies[1]-activeJiffies3CyclesAgo_-idleJiffies3CyclesAgo_);
    }
    
    // save current values for next iteration
    activeJiffies3CyclesAgo_ = activeJiffies2CyclesAgo_;
    idleJiffies3CyclesAgo_ = idleJiffies2CyclesAgo_;

    activeJiffies2CyclesAgo_ = activeJiffies1CycleAgo_;
    idleJiffies2CyclesAgo_ = idleJiffies1CycleAgo_;

    activeJiffies1CycleAgo_ = currentActiveIdleJiffies[0];
    idleJiffies1CycleAgo_ = currentActiveIdleJiffies[1];

    return utilization;
}