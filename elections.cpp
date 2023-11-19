#include <iostream>
#include <cstdlib>

#define MAX 20

int pStatus[MAX], n, cordinator;
using namespace std;

class ElectionAlgorithm
{
public:


    void bully(){
        int schoice, crash, activate, i , gid, flag, sub;

        do{
            cout<<"--------"<<endl;
            cout<<"1. Crash"<<endl;
            cout<<"2. Activate"<<endl;
            cout<<"3. Display"<<endl;
            cout<<"4. Exit"<<endl;
            cout<<"--------"<<endl;
            cout<<"Enter your choice: ";
            cin>>schoice;
            cout<<endl;


            switch(schoice){
                case 1:

                    cout<<"Enter to crash: ";
                    cin>>crash;

                    if(pStatus[crash]){
                        pStatus[crash]=0;
                    }
                    else {
                        cout<<"already dead";
                    }

                    flag = 0;
                    do{
                        cout<<"enter gid: ";
                        cin>>gid;
                        if(gid==cordinator||pStatus[gid]==0){
                            cout<<"Enter valid gid"<<endl;
                        }
                    }while(gid==cordinator||pStatus[gid]==0);

                    if(crash==cordinator){
                        for(i=gid+1; i<=n; i++){
                            cout<<"Message from "<<gid<<" to "<<i<<endl;
                            if(pStatus[i]){
                                cout<<"Response from "<<i<<" to "<<gid;
                                flag=1;
                                sub=i;
                            }
                        }

                        if(flag==1){
                            cordinator=sub;
                        }
                        else{
                            cordinator = gid;
                        }
                    }

                    break;

                case 2:
                    cout<<"Enter process to activate: ";
                    cin>>activate;

                    if(!pStatus[activate]){
                        pStatus[activate]=1;                        
                    }
                    else{
                        cout<<"Process already running"<<endl;
                        break;
                    }

                    if(activate==n){
                        cordinator=n;
                    }

                    for(i=activate+1; i<=n; i++){
                        cout<<"Message sent from "<<activate<<" to "<<i<<endl;
                            if(pStatus[i]){
                                sub=i;
                                cout<<"Response from "<<i<<" to "<<activate<<endl;
                                flag=1;
                            }                        
                    }
                    if(flag==1){
                        cordinator=sub;
                    }
                    else{
                        cordinator=activate;
                    }
                    break;
                
                case 3:
                    display();
                    break;

                case 4:
                    break;
            }
        }while(schoice!=4);
    }



    void ring(){
        int choice, crash, acitvate, gid, sub, i;

        do{
            cout<<"---------"<<endl;
            cout<<"1. crash"<<endl;
            cout<<"2. activate"<<endl;
            cout<<"3. display"<<endl;
            cout<<"4. end"<<endl;
            cout<<"---------"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;

            switch(choice){
                case 1:
                    cout<<"enter crash: ";
                    cin>>crash;

                    if(pStatus[crash]){
                        pStatus[crash]=1;
                    }
                    else{
                        cout<<"process already crash!";
                    }

                    do{
                        cout<<"Enter gid: ";
                        cin>>gid;
                        if(gid==cordinator){
                            cout<<"enter valid gid"<<endl;
                        }
                    }while(gid==cordinator);

                    if(crash==cordinator){
                        sub=1;
                        for(i=0; i<(n+1); i++){
                            int pid = (i+gid)%(n+1);
                            if(pid!=0){
                                if(pStatus[pid] && sub<pid){
                                    sub=pid;
                                    cout<<"Message from "<<pid<<" to "<<sub<<endl;
                                }
                            }
                        }
                        cordinator=sub;
                    }

                    break;

                case 2:
                    cout<<"Enter process to activate: ";
                    cin>>acitvate;

                    if(!pStatus[acitvate]){
                        pStatus[acitvate]=1;
                    }
                    else{
                        cout<<"Process already running"<<endl;
                        break;
                    }

                    sub = acitvate;
                    for(i=0; i<(n+1); i++){
                        int pid = (i+acitvate)%(n+1);

                        if(pid!=0){
                            if(pStatus[pid] && sub<pid){
                                sub=pid;
                            }
                            cout<<"Election passed from "<<pid<<" to "<<sub<<endl;
                        }
                    }

                    cordinator=sub;
                    break;

                case 3:
                    display();
                    break;

                case 4:
                    break;
            }
        }while(choice!=4);

        
    }

    void display()
    {
        int i;
        cout << endl;
        cout << "-------------------------------------------------\n";
        cout << "Processes:  ";
        for (i = 1; i <= n; i++)
            cout << i << "\t";
        cout << endl << "Alive:      ";
        for (i = 1; i <= n; i++)
            cout << pStatus[i] << "\t";
        cout << "\n-------------------------------------------------\n";
        cout << "COORDINATOR IS " << cordinator << endl;
        cout << endl;
    };
};

int main()
{
    ElectionAlgorithm e;
    int i, j, fchoice;

    cout << "Enter number of processes: ";
    cin >> n;
    for (i = 1; i <= n; i++)
    {
        cout << "Enter Process " << i << " is alive or not(0/1): ";
        cin >> pStatus[i];
        if (pStatus[i])
            cordinator = i;
    }

    e.display();
    cout << endl;
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << " ### MENU ###" << endl;
        cout << "1. Bully Algo" << endl;
        cout << "2. Ring Algo" << endl;
        cout << "3. Display" << endl;
        cout << "4. Exit the code" << endl;
        cout << "-------------------------------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> fchoice;
        cout << endl;

        switch (fchoice)
        {
        case 1:
            e.bully();
            break;
        case 2:
            e.ring();
            break;
        case 3:
            e.display();
            break;
        case 4:
            exit(1);
            break;
        }
    } while (fchoice != 4);
    return 0;
}