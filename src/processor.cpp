#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    std::vector<long> currentActiveIdleJiffies = LinuxParser::ActiveIdleJiffies();
    float utilization = 0;
    
    // make sure no division over 0 happens
    if(currentActiveIdleJiffies[1]+currentActiveIdleJiffies[1]-lastActiveJiffies_-lastIdleJiffies_>0){
        // utilization = (current active jiffies - last active jiffies)/(current total jiffies - last total jiffies)
        utilization = (currentActiveIdleJiffies[0]-lastActiveJiffies_)/(currentActiveIdleJiffies[0]+currentActiveIdleJiffies[1]-lastActiveJiffies_-lastIdleJiffies_);
    }
    
    // save current values for next iteration
    lastActiveJiffies_ = currentActiveIdleJiffies[0];
    lastIdleJiffies_ = currentActiveIdleJiffies[1];

    return utilization;
}