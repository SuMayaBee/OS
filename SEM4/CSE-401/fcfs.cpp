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
};

int main() {
    int num;
    cout << "Enter number of processes\n";
    cin >> num;
    process processes[num];

    cout << "Enter burst time and priority for each process\n";
    for(int i=0; i<num; i++) {
        cin >> processes[i].burst_time>>processes[i].arrival;
        //processes[i].arrival = 0;
        processes[i].start = 0;
        processes[i].end = processes[i].burst_time;
        processes[i].index = i+1;
        processes[i].wait=0;
        processes[i].turn = processes[i].burst_time;
    }
    
    for(int i = 1; i < num; i++) {
        if(processes[i].arrival>processes[i-1].end)
        {
            processes[i].start = processes[i].arrival;
            processes[i].end = processes[i].start+processes[i].burst_time;
            processes[i].turn = processes[i].end-processes[i].arrival;
            processes[i].wait = processes[i-1].start;
        }
        else
        {
            processes[i].start = processes[i - 1].end;
            processes[i].end = processes[i].start + processes[i].burst_time;
            processes[i].turn = processes[i].end - processes[i].arrival;
            processes[i].wait = processes[i-1].wait + processes[i-1].burst_time;
        }
    }

    for(auto x :processes)
    cout<<x.start<<" "<<x.end<<endl;
    cout<<"Gantt Chart\n";

    for(int i = 0; i < num; i++) {
        for(int j = processes[i].start; j < processes[i].end; j++) {
            if(j == processes[i].start)
                cout << "| ";
            else if(j == (processes[i].end - processes[i].start) / 2 + processes[i].start)
                cout << "P" << i + 1;
            else
                cout << "-";
        }
        if(processes[i].end - processes[i].start <= 1)
            cout << "P" << i + 1;
    }

    cout << "|";
    cout << endl;

    for(int i=0; i<num; i++)
    {
        for(int j=processes[i].start; j<processes[i].end; j++)
        {
            if(j==processes[i].start)
                cout<<j;
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
