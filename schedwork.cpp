
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <array>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// typedef std::vector<std::vector<bool>> AvailabilityMatrix;
// typedef std::vector<std::vector<Worker_T> > DailySchedule;

// Add prototypes for any helper functions here
bool makeSched(vector<vector<int>>& schedule, vector<vector<int>> daysWorkers, vector<int> workerShifts);
void print(vector<vector<int>> sched);
// Add your implementation of schedule() and other helper functions here
void print(vector<vector<int>> sched)
{
    int day = 0;
    for(auto s : sched)
    {
        cout << "Day " << day << ": ";
        for(auto nurse : s)
        {
            cout << nurse << " ";
        }
        cout << endl;
        day++;
    }
}
bool makeSched(vector<vector<int>>& schedule, vector<vector<int>> daysWorkers, vector<int> workerShifts){
    bool passed = true;
    //find col and row of next slot that needs to be filled into schedule
    int nextCol = (int)schedule.size();
    int nextRow = (int)schedule[0].size();
    //check if schedule if fully filled
    for(int i = 0; i < (int)schedule.size(); i++){
        for(int j = 0; j < (int)schedule[0].size(); j++){
            if(schedule[i][j] == -1){
                if(i < nextCol && j < nextRow){
                    nextCol = i;
                    nextRow = j;
                }
                passed = false;
            }
        }
    }
    //check if any workers are working more than max shifts
    for(int i = 0; i < (int)workerShifts.size(); i++){
        if(workerShifts[i] < 0){
            return false;
        }
    }
    //return true if schedule is valid
    if(passed){
        return true;
    }
    //try out new person in schedule
    for(int i = nextCol; i < (int)daysWorkers.size(); i++){
        for(int j = 0; j < (int)daysWorkers[0].size(); j++){
            //if worker is available and schedule still needs to be filled then add worker to schedule
            int temp = daysWorkers[i][j];
            if(nextCol < (int)schedule.size() && schedule[nextCol][nextRow] == -1 && nextCol == i){
                schedule[nextCol][nextRow] = temp;
                workerShifts[temp]--;
                bool repeat = false;
                if(nextRow > 0 && schedule[nextCol][nextRow] == schedule[nextCol][nextRow-1]){
                    repeat = true;
                }
                //if move is valid increment next row, if not undo everything
                if(!repeat && workerShifts[temp] >= 0 && makeSched(schedule, daysWorkers, workerShifts)){
                    if(nextCol == 3 && nextRow == 0){
                        //cout << temp << endl;
                        //print(daysWorkers);
                    }
                    
                    nextRow++;
                    if(nextRow >= (int)schedule[0].size()){
                        nextCol++;
                        nextRow = 0;
                    }
                }else{
                    workerShifts[temp]++;
                    schedule[nextCol][nextRow] = -1;                  
                }
            }
        }
    }
    for(int i = 0; i < (int)schedule.size(); i++){
        for(int j = 0; j < (int)schedule[0].size(); j++){
            if(schedule[i][j] == -1){
                return false;
            }
        }
    }
    return true;
}


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false; 
    }
    sched.clear();
    // Add your code below

    //vector corresponding to schedule solution that has daily needs cols and amount of days rows
    vector<vector<int>> schedule;

    //different 2d vector that has days and then daysWorkers
	vector<vector<int>> daysWorkers;
    //adding in vectors to sched, schedule, and daysWorkers
    for(int i = 0; i < (int)avail.size(); i++){
        vector<int> a;
        vector<Worker_T> b;
        vector<int> c;
        daysWorkers.push_back(c);
        schedule.push_back(c);
        sched.push_back(b);
    }
		//setting all values of schedule to -1   
		for(int i = 0; i < (int)avail.size(); i++){
				for(int k = 0; k < (int)dailyNeed; k++) schedule[i].push_back(-1);
		} 

    for(int i = 0; i < (int)avail.size(); i++){
        for(int j = 0; j < (int)avail[0].size(); j++){
            //setting up values for daysWorkers
            if(avail[i][j]){
                daysWorkers[i].push_back(j);
            }else{
                daysWorkers[i].push_back(-1);
            }
            
        }

    }
    //vector corresponding the the remaning amount of shifts each worker can do
    vector<int> workerShifts;
    for(int i = 0; i < (int)avail[0].size(); i++){
        workerShifts.push_back((int)maxShifts);
    }
    //if function returns true then fill in schedule
    if(makeSched(schedule, daysWorkers, workerShifts)){
        for(int i = 0; i < (int)schedule.size(); i++){
            for(int j = 0; j < (int)schedule[0].size(); j++){
                sched[i].push_back((unsigned int)schedule[i][j]);
            }
        }
				return true;
    }
    return false;
    
}

