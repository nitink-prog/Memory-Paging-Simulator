//  Memory Paging Simulator
//  Created by Nitin Kumar on 12/18/19.

#include <iostream>
#include <random>
#include <time.h>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// Prototypes
void LRU(int, int, int [10]);
void FIFO(int, int, int [10]);

int main(){
    srand(time(NULL));
    
    // RANDOMIZE PAGE NUMBER (0-9), RANDOMIZE FRAME NUMBER (1-7)
    int pageNum = rand()%10;
    int frameNum = (rand()%7)+ 1;
    
    // RANDOMIZE 10 NUMBERS (0-9) FOR PAGE REFERENCE STRING
    int pageRefString[10] = {};
    int pageRefStringLength = sizeof(pageRefString) / sizeof(pageRefString[0]);
    
    for (int i = 0; i < pageRefStringLength; i++)
        pageRefString[i] = rand()%10;
    
    // PRINTING INTs FROM ABOVE SO THEY ARE SEEN IN THE OUTPUT
    cout << "Number of Pages:\t" << pageNum << endl
    << "Number of Frames:\t" << frameNum << endl
    << "Reference String:\t";
    for (int i = 0; i < pageRefStringLength; i++)
        cout << pageRefString[i] << ' ';
    
    cout << endl << endl << endl;
    
    // CALLING FIFO AND LRU HERE WITH SAME PARAMETERS
    FIFO(pageNum, frameNum, pageRefString);
    LRU(pageNum, frameNum, pageRefString);
    
    return 0;
}

void LRU(int numPages, int numFrames, int refString[10]){
    cout << "Least Recently Used (LRU) Paging Algorithm";
    
    int count = 0;
    
    int frame[numFrames], fcount[numFrames];
    for(int i = 0; i < numFrames; i++){
        frame[i] = -1; //Store the frames
        fcount[i] = 0; //Track when the page is last used
    }
    
    for(int i = 0; i < numPages; i++){
        int flag = 0;
        for(int j = 0; j < numFrames; j++){
            if(refString[i] == frame[j]){  //Checking whether page already exist in frames or not
                flag = 1;
                fcount[j] = i+1;
            }
        }
        
        cout << endl << "------------------------------------------------------------------------" << endl;
        cout << refString[i] << ":";
        
        if(flag == 0){
            int min = 0;
            for(int k = 0; k < numFrames-1; k++){
                if(fcount[min] > fcount[k+1]) //Calculating the page which is least recently used
                    min = k+1;
            }
            
            frame[min] = refString[i]; //Replacing it
            fcount[min] = i+1;    //Increasing the time
            count++;           //counting Page Fault
            
            for(int j = 0; j < numFrames; j++)
                cout << '\t' << '\t' << frame[j];
        }
    }
    
    cout << endl << "------------------------------------------------------------------------" << endl;
    cout << "LRU Page Fault count is: " << count << endl << endl << endl;
}

void FIFO(int numPages, int numFrames, int refString[10]){
    cout << "First In First Out (FIFO) Paging Algorithm";
    
    int count = 0;
    int count1[numFrames];
    
    for(int i = 0; i < numFrames; i++)
        count1[i] = -1;
    
    for(int i = 0; i < numPages; i++){
        int k = 0;
        for(int j = 0; j < numFrames; j++){
            if(refString[i] == count1[j]){
                k++;
                count--;
            }
        }
        count++;
        
        if(count <= numFrames && k == 0)
            count1[i] = refString[i];
        
        else if(k == 0)
            count1[(count-1)%numFrames] = refString[i];
        
        cout << endl <<  "------------------------------------------------------------------------" << endl;
        
        cout << refString[i] << ":";
        
        for(int j = 0; j < numFrames; j++)
            cout << '\t' << '\t' << count1[j];
    }
    cout << endl << "FIFO Page Fault count is: " << count << endl << endl << endl;
}