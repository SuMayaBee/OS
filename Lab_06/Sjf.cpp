#include<bits/stdc++.h>
using namespace std;

struct Process{
    int arrival;
    int burst;
    int priority;
    string name;
    bool is_finished;
};

struct Result{
    string name;
    int start;
    int end;
};

bool burst_compare(Process a,Process b);
bool arrival_compare(Process a,Process b);
void create_queue(vector<Process> &process_queue,vector<Process> processess,int curr_time);
int main(){
    freopen("input.txt","r",stdin);
    int i,j;
    int num_process=6;
    int unarrived=num_process;
    int finished=0;
    vector<Process> processes(num_process);
    vector<Result> results;
    for(i=0;i<num_process;i++){
        cin>>processes[i].burst>>processes[i].priority>>processes[i].arrival;
        processes[i].name="P"+to_string(i+1);
    }
    vector<Process> temp_processes;
    temp_processes=processes;
    sort(temp_processes.begin(),temp_processes.end(),arrival_compare);
    int curr_time=0;

    while(finished<num_process){
        Result temp_result;

    }
    return 0;
}

bool burst_compare(Process a,Process b){
    return a.burst<b.burst;
}

bool arrival_compare(Process a,Process b){
    if(a.arrival==b.arrival){
        return a.burst<b.burst;
    }
    return a.arrival<b.arrival;
}
void create_queue(vector<Process> &process_queue,vector<Process> processess,int curr_time){
    for(auto p:processess){
        if(p.arrival<=curr_time&&!p.is_finished){
            process_queue.push_back(p);
        }
    }
    sort(process_queue.begin(),process_queue.end(),burst_compare);
}