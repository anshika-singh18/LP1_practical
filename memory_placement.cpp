#include <iostream>
using namespace std;

void firstfit(int processSize[], int blocksize[], int m, int n){
    int allocate[m];

    for(int i=0; i<m; i++){
        allocate[i] = -1;
    }

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(blocksize[j]>=processSize[i]){
                allocate[i] = j;
                blocksize[j] -= processSize[i];
                break;
            }
        }
    }

    cout<<"****FIRST FIT*****"<<endl;
    cout<<"Process No. Process Size Block No."<<endl;
    for(int i=0; i<m; i++){
        cout<<" "<<i+1<<"\t\t"<<processSize[i]<<"\t   ";
        if(allocate[i]!=-1){
            cout<<allocate[i]+1;
        }
        else{
            cout<<"Not Allocated";
        }
        cout<<endl;
    }
}



void bestfit(int process[], int block[], int m, int n){
    int allocate[m];

    for(int i=0; i<m; i++){
        allocate[i] = -1;
    }

    for(int i=0; i<m; i++){
        int bestindex = -1;
        for(int j=0; j<n; j++){
            if(block[j]>=process[i]){
                if(bestindex==-1){
                    bestindex=j;
                }
                else if(block[bestindex]>block[j]){
                    bestindex = j;
                }
            }
        }
        if(bestindex!=-1){
            allocate[i] = bestindex;
            block[bestindex] -= process[i];
        }
    }

    cout<<"****BEST FIT*****"<<endl;
    cout<<"Process No. Process Size Block No."<<endl;
    for(int i=0; i<m; i++){
        cout<<" "<<i+1<<"\t\t"<<process[i]<<"\t   ";
        if(allocate[i]!=-1){
            cout<<allocate[i]+1;
        }
        else{
            cout<<"Not Allocated";
        }
        cout<<endl;
    }
}


void worstfit(int process[], int block[], int m, int n){
    int allocate[m];

    for(int i=0; i<m; i++){
        allocate[i] = -1;
    }

    for(int i=0; i<m; i++){
        int worstindex = -1;
        for(int j=0; j<n; j++){
            if(block[j]>=process[i]){
                if(worstindex==-1){
                    worstindex=j;
                }
                else if(block[worstindex]<block[j]){
                    worstindex = j;
                }
            }
        }
        if(worstindex!=-1){
            allocate[i] = worstindex;
            block[worstindex] -= process[i];
        }
    }

    cout<<"****WORST FIT*****"<<endl;
    cout<<"Process No. Process Size Block No."<<endl;
    for(int i=0; i<m; i++){
        cout<<" "<<i+1<<"\t\t"<<process[i]<<"\t   ";
        if(allocate[i]!=-1){
            cout<<allocate[i]+1;
        }
        else{
            cout<<"Not Allocated";
        }
        cout<<endl;
    }
}
void nextfit1(int process[], int block[], int m, int n) {
    int allocation[m];
    int j = 0;
    int t = n - 1;
    cout << "next fit" << endl;

    for (int i = 0; i < m; i++) {
        allocation[i] = -1;
    }

    // for (int i = 0; i < m; i++) {
    //     while (j < n) {
    //         if (block[j] >= process[i]) {
    //             allocation[i] = j;
    //             block[j] -= process[i];

    //             t = (j - 1) % n;
    //             break;
    //         }

    //         if (t == j) {
    //             t = (j - 1) % n;
    //             break;
    //         }

    //         j = (j + 1) % n;
    //     }
    // }

    for(int i=0; i<m; i++){
        while(j<n){
            if(process[i]<=block[j]){
                allocation[i] = j;
                block[j] -= process[i];
                t = (j-1)%n;
                break;
            }

            if(t==j){
                t = (j-1)%n;
                break;
            }

            j = (j+1)%n;
        }
    }

    cout << "****NEXT FIT*****" << endl;
    cout << "Process No. Process Size Block No." << endl;
    for (int i = 0; i < m; i++) {
        cout << " " << i + 1 << "\t\t" << process[i] << "\t   ";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }
}


int main(){

    // int processsize[] = {300,25,125,50};
    // int blocksize[] = {150,350};
    int processsize[] = {100, 200, 300, 400};
    int blocksize[] = {200, 300, 400};

    int m = 4;
    int n = 3;
    int y = sizeof(processsize) / sizeof(processsize[0]);
    int z = sizeof(blocksize) / sizeof(blocksize[0]);


    // nextfit1(processsize,blocksize,y,z);
    // bestfit(processsize,blocksize,m,n);
    worstfit(processsize,blocksize,m,n);
    // firstfit(processsize, blocksize, m, n);


    return 0;
}