#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h" //should this be here or in system.h?

using std::set;
using std::size_t;
using std::string;
using std::vector;

// Constructor to fill some private variables
System::System(){
    kernel_ = LinuxParser::Kernel();
}

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    // get and sort current processes pids
    vector<int> currentProcessesPids = LinuxParser::Pids();
    std::sort(currentProcessesPids.begin(), currentProcessesPids.end());

    // iterate through previous and current pids vectors to find differences
    std::size_t i = 0, j = 0, maxI =processesPids_.size(), maxJ=currentProcessesPids.size();
    while (i < maxI && j < maxJ) {
        if (processesPids_[i] < currentProcessesPids[j]){
            // a process was terminated
            // look for terminated process and delete it from container
            for(std::size_t k=0; k<processes_.size(); k++){
                if(processes_[k].Pid()==processesPids_[i]){
                    processes_.erase(std::next(processes_.begin(), k));
                    break;
                }
            }
            i++;
        }
        else if (currentProcessesPids[j] < processesPids_[i]){
            // a process was added
            // add to container
            Process process(currentProcessesPids[j]);
            processes_.push_back(process);
            j++;
        }
        else
        {
            // same process. Check next one
            i++;
            j++;
        }
    }
    // deal with added/deleted processes at the end of PIDs containers
    while (i < maxI){
        // a process was terminated
        // look for terminated process and delete it from container
        for(std::size_t k=0; k<processes_.size(); k++){
            if(processes_[k].Pid()==processesPids_[i]){
                processes_.erase(std::next(processes_.begin(), k));
                break;
            }
        }
        i++;
    }
    while (j < maxJ){
        // a process was added
        // add to container
        Process process(currentProcessesPids[j]);
        processes_.push_back(process);
        j++;
    }

    // update values for next run
    processesPids_ = currentProcessesPids;

    return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return LinuxParser::UpTime(); }