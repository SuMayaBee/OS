#include<bits/stdc++.h>
using namespace std;

struct process {
    int burst_time;
    int priority;
    int arrival;
    int start;
    int end;
    int index;
    int turn;
    int wait;
    bool processed;
};

bool compare(process p1, process p2)
{
    return p1.start<p2.start;
}
bool compare2(process p1, process p2)
{
    return p1.arrival<p2.arrival;
}

int main() {
    int num;
    cout << "Enter number of processes\n";
    cin >> num;
    process processes[num];

    cout << "Enter burst time and priority for each process\n";
    for(int i=0; i<num; i++) {
        cin>>processes[i].burst_time>>processes[i].arrival;
        processes[i].processed = false;
        //processes[i].start = 0;
        //processes[i].end = processes[i].burst_time;
        processes[i].index = i+1;
        //processes[i].wait=0;
        //processes[i].turn = processes[i].burst_time;
    }
    
    sort(processes, processes+num, compare2);
    
    int curr=0;
    for(int i=0; i<num; i++)
    {
        int mTime = INT_MAX, idx;
        for(int j=0; j<num; j++)
        {
            if(processes[j].arrival<=curr && processes[j].burst_time<mTime && !processes[j].processed)
            {
                mTime = processes[j].burst_time;
                idx = j;
            }
        }
        if(mTime==INT_MAX)
        {
            int mBurst = INT_MAX;
            for(int j=0; j<num; j++)
            {
                if(processes[j].arrival<=mTime && processes[j].burst_time<mBurst && !processes[j].processed)
                {
                    mBurst = processes[j].burst_time;
                    mTime = processes[j].arrival; 
                    idx=j;
                }
            }
            curr = mTime;
        }
        processes[idx].start = curr, processes[idx].end = curr+processes[idx].burst_time;
        processes[idx].turn = processes[idx].end - processes[idx].arrival;
        processes[idx].wait = processes[idx].turn - processes[idx].burst_time;
        curr = processes[idx].end;
        processes[idx].processed = true;
    }
    
    sort(processes, processes+num,compare);
    for(auto x : processes)
    cout<<x.start<<" "<<x.end<<endl;
    cout<<"Gantt Chart\n";

    for(int i = 0; i < num; i++) {
        for(int j = processes[i].start; j < processes[i].end; j++) {
            if(j == processes[i].start)
                cout << "| ";
            else if(j == (processes[i].end - processes[i].start) / 2 + processes[i].start)
                cout << "P" << processes[i].index;
            else
                cout << "-";
        }
        if(processes[i].end - processes[i].start <= 1)
            cout << "P" << processes[i].index;
    }
    cout << "|";
    cout << endl;

    for(int i=0; i<num; i++)
    {
        for(int j=processes[i].start; j<processes[i].end; j++)
        {
            if(j==processes[i].start)
                cout<<j<<" ";
            else
            cout<<" ";
        }
    }
    cout<<processes[num-1].end<<endl;

    cout<<"Turnaround and Waiting times: \n";
    for(auto x : processes)
    {
        cout<<"P"<<x.index<<" Turn: "<<x.turn<<" Wait: "<<x.wait<<endl;
    }

    int sum=0;
    cout<<"Average Turn Around Time: \n";
    for(auto x : processes)
    sum+=x.turn;
    cout<<(double)sum/num<<endl;

    sum=0;
    cout<<"Average Waiting Time: \n";
    for(auto x : processes)
    sum+=x.wait;
    cout<<(double)sum/num<<endl;
    return 0;
}
