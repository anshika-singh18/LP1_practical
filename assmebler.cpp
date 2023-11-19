// #include <iostream>
// #include <fstream>
// #include <climits>
// #include <map>
// #include <vector>
// #include <string>
// #include <sstream>
// using namespace std;

// bool isNumber(string s){
//     for(int i=0; i<s.length(); i++){
//         if(isdigit(s[i])==false){
//             return false;
//         }
//     }
//     return true;
// }

// int main(){
//     map<string, pair<string, string>> OPCODE;

//     OPCODE["STOP"] = {"IS", "0"};
//     OPCODE["ADD"] = {"IS", "1"};
//     OPCODE["SUB"] = {"IS", "2"};
//     OPCODE["MULT"] = {"IS", "3"};
//     OPCODE["MOVER"] = {"IS", "4"};
//     OPCODE["MOVEM"] = {"IS", "5"};
//     OPCODE["COMP"] = {"IS", "6"};
//     OPCODE["BC"] = {"IS", "7"};
//     OPCODE["DIV"] = {"IS", "8"};
//     OPCODE["READ"] = {"IS", "9"};
//     OPCODE["PRINT"] = {"IS", "10"};

//     OPCODE["START"] = {"AD", "1"};
//     OPCODE["END"] = {"AD", "2"};
//     OPCODE["ORIGIN"] = {"AD", "3"};
//     OPCODE["EQU"] = {"AD", "4"};
//     OPCODE["LTORG"] = {"AD", "5"};

//     OPCODE["AREG"] = {"1", ""};
//     OPCODE["BREG"] = {"2", ""};
//     OPCODE["CREG"] = {"3", ""};
//     OPCODE["DREG"] = {"4", ""};

//     OPCODE["DC"] = {"DL", "1"};
//     OPCODE["DS"] = {"DL", "2"};

//     OPCODE["LT"] = {"1", ""};
//     OPCODE["LE"] = {"2", ""};
//     OPCODE["EQ"] = {"3", ""};
//     OPCODE["GT"] = {"4", ""};
//     OPCODE["GE"] = {"5", ""};
//     OPCODE["ANY"] = {"6", ""};

//     ifstream fin;
//     fin.open("input.txt");

//     ofstream fout;
//     fout.open("output.txt");

//     string line, words;
//     map<string, pair<int, string>> symtab;
//     vector<pair<string, int>>littab;
//     vector<string> pooltab;

//     int litindex = 0;
//     int lc = -1;

//     while(getline(fin, line)){
//         stringstream st(line);
//         st>>words;
//         string label = "";

//         if(OPCODE.count(words)==0){
//             if(symtab.count(words)==0){
//                 symtab[words] = {lc, to_string(symtab.size()+1)};
//             }
//             else{
//                 symtab[words].first = lc;
//             }
//             label = words;
//             st>>words;
//         }

//         string operation = words;

//         if(operation=="START"){
//             fout<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
//             st>>words;
//             fout<<"(C, "<<words<<")";
//             lc = stoi(words);
//         }

//         else if(operation=="END"){
//             fout<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
//             pooltab.push_back(to_string(litindex+1));

//             for(; litindex<littab.size(); litindex++){
//                 littab[litindex].second = lc;
//             }
//         }

//         else if(operation=="LTORG"){
//             fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
//             pooltab.push_back(to_string(litindex+1));

//             for(; litindex<littab.size(); litindex++){
//                 littab[litindex].second = lc;
//                 lc++;
//             }
//         }
//         else if(operation=="EQU"){
//             fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
//             st>>words;
//             int plusminusindex=0;
//             for(int i=0; i<words.length(); i++){
//                 if(words[i]=='+' || words[i]=='-'){
//                     plusminusindex=i;
//                     break;
//                 }
//             }

//             char plusminus = '0';
//             string before, after;

//             if(plusminusindex!=0){
//                 plusminus = words[plusminusindex];
//                 after = words.substr(plusminusindex+1);
//                 before = words.substr(0, plusminusindex);
//             }
//             else{
//                 before = words.substr(0, words.length());
//             }

//             symtab[label].first = symtab[before].first;

//             if(plusminus=='+'){
//                 symtab[label].first += stoi(after);
//             }
//             else {
//                 symtab[label].first -= stoi(after);
//             }
//         }

//         else if(operation=="ORIGIN"){
//             fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
//             st>>words;
//             if(isNumber(words)){
//                 lc = stoi(words);
//                 fout<<"(C, "<<words<<") ";
//             }
//             else{
//                 int plusminusindex=0;
//                 for(int i=0; i<words.length(); i++){
//                     if(words[i]=='+' || words[i]=='-'){
//                         plusminusindex=i;
//                         break;
//                     }
//                 }

//                 char plusminus = '0';
//                 string before, after;

//                 if(plusminusindex!=0){
//                     plusminus = words[plusminusindex];
//                     after = words.substr(plusminusindex+1);
//                     before = words.substr(0, plusminusindex);
//                 }
//                 else{
//                     before = words.substr(0, words.length());
//                 }

//                 lc = symtab[before].first;
//                 fout<<"(S, "<<symtab[before].second<<") ";

//                 if(plusminus=='+'){
//                     lc += stoi(after);
//                 }
//                 else if(plusminus=='-') {
//                     lc -= stoi(after);
//                 }                
//             }
//         }
        
//         else{
//             fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";

//             while(st>>words){
//                 if(operation=="DC"){
//                     words = words.substr(1, words.length()-2);
//                     fout<<"(C, "<<words<<")";
//                 }
//                 else if(operation=="DS"){
//                     fout<<"(C, "<<words<<")";
//                 }
//                 else if(words[0]=='='){
//                     littab.push_back({words, lc});
//                     fout<<"(L, "<<littab.size()<<")";
//                 }
//                 else if(OPCODE.count(words)>0){
//                     fout<<"("<<OPCODE[words].first<<") ";
//                 }
//                 else{
//                     if(symtab.count(words)==0){
//                         symtab[words] = {lc, to_string(symtab.size()+1)};
//                     }
//                     fout<<"(S, "<<symtab[words].second<<")";
//                 }
//             }
//             lc++;
//         }
//         fout<<endl;
//     }

//     fin.close();
//     fout.close();

//     ofstream sout;
//     sout.open("st.txt");

//     for(auto i: symtab){
//         sout<<i.first<<" "<<i.second.first<<endl;
//     }
//     sout.close();

//     ofstream lout;
//     lout.open("lit.txt");

//     for(auto i: littab){
//         lout<<i.first<<" "<<i.second<<endl;
//     }
//     lout.close();

//     ofstream pout;
//     pout.open("poolt.txt");

//     for(auto i: pooltab){
//         pout<<i<<endl;
//     }

//     pout.close();

//     cout<<"End"<<endl;
// }

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

bool isNumber(string w){
    for(int i=0; i<w.length(); i++){
        if(isdigit(w[i])==false){
            return false;
        }
    }
    return true;
}

int main(){

    map<string, pair<string, string>>OPCODE;

    OPCODE["STOP"] = {"IS", "0"};
    OPCODE["ADD"] = {"IS", "1"};
    OPCODE["SUB"] = {"IS", "2"};
    OPCODE["MULT"] = {"IS", "3"};
    OPCODE["MOVERM"] = {"IS", "4"};
    OPCODE["MOVEM"] = {"IS", "5"};
    OPCODE["COMP"] = {"IS", "6"};
    OPCODE["BC"] = {"IS", "7"};
    OPCODE["DIV"] = {"IS", "8"};
    OPCODE["READ"] = {"IS", "9"};
    OPCODE["PRINT"] = {"IS", "10"};

    OPCODE["START"] = {"AD", "1"};
    OPCODE["END"] = {"AD", "2"};
    OPCODE["ORIGIN"] = {"AD", "3"};
    OPCODE["EQU"] = {"AD", "4"};
    OPCODE["LTORG"] = {"AD", "5"};

    OPCODE["DC"] = {"DL", "1"};
    OPCODE["DS"] = {"DL", "2"};

    OPCODE["AREG"] = {"1", ""};
    OPCODE["BREG"] = {"3", ""};
    OPCODE["CREG"] = {"2", ""};
    OPCODE["DREG"] = {"4", ""};

    OPCODE["LT"] = {"1", ""};
    OPCODE["LE"] = {"2", ""};
    OPCODE["EQ"] = {"3", ""};
    OPCODE["GT"] = {"4", ""};
    OPCODE["GE"] = {"5", ""};
    OPCODE["ANY"] = {"6", ""};

    ifstream fin;
    fin.open("input.txt");

    ofstream fout;
    fout.open("output.txt");

    map<string, pair<int, string>>SYMTAB;
    vector<pair<string, int>>LITTAB;
    vector<string>POOLTAB;

    string line, words;
    int litindex = 0;
    int lc = -1;

    while(getline(fin, line)){
        stringstream st(line);
        st>>words;
        string label = "";

        if(OPCODE.count(words)==0){
            if(SYMTAB.count(words)==0){
                SYMTAB[words] = {lc, to_string(SYMTAB.size()+1)};
            }
            else{
                SYMTAB[words].first = lc;
            }
            label = words;
            st>>words;
        }

        string operation = words;

        if(operation=="START"){
            fout<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
            st>>words;
            fout<<"(C, "<<words<<")";
            lc = stoi(words);
        }

        else if(operation=="END"){
            fout<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
            POOLTAB.push_back(to_string(litindex+1));

            for(; litindex<LITTAB.size(); litindex++){
                LITTAB[litindex].second = lc;
                lc++;
            }
        }

        else if(operation=="LTORG"){
            fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
            POOLTAB.push_back(to_string(litindex+1));

            for(; litindex<LITTAB.size(); litindex++){
                LITTAB[litindex].second = lc;
                lc++;
            }
        }

        else if(operation=="EQU"){
            fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
            st>>words;
            int plusminusindex = 0;
            for(int i=0; i<words.size(); i++){
                if(words[i]=='+' || words[i]=='-'){
                    plusminusindex = i;
                    break;
                }
            }

            string before, after;
            char plusminus = '0';

            if(plusminusindex!=0){
                plusminus = words[plusminusindex];
                after = words.substr(plusminusindex+1);
                before = words.substr(0, plusminusindex);
            }
            else{
                before = words.substr(0, words.length());
            }

            SYMTAB[label].first = SYMTAB[before].first;

            if(plusminus=='+'){
                SYMTAB[before].first += stoi(after);
            }
            else{
                SYMTAB[before].first -= stoi(after);
            }
        }

        else if(operation=="ORIGIN"){
            fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";
            st>>words;
            int plusminusindex = 0;
            for(int i=0; i<words.size(); i++){
                if(words[i]=='+' || words[i]=='-'){
                    plusminusindex = i;
                    break;
                }
            }

            string before, after;
            char plusminus = '0';

            if(plusminusindex!=0){
                plusminus = words[plusminusindex];
                after = words.substr(plusminusindex+1);
                before = words.substr(0, plusminusindex);
            }
            else{
                before = words.substr(0, words.length());
            }

            // SYMTAB[label].first = SYMTAB[before].first;
            lc = SYMTAB[before].first;
            fout<<"(S, "<<SYMTAB[before].second<<")";

            if(plusminus=='+'){
                lc += stoi(after);
            }
            else{
                lc -= stoi(after);
            }
        }

        else {
            fout<<lc<<" ("<<OPCODE[words].first<<", "<<OPCODE[words].second<<") ";

            while(st>>words){
                if(operation=="DC"){
                    words = words.substr(1, words.length()-2);
                    fout<<"(C, "<<words<<")";
                }
                else if(operation=="DS"){
                    lc+=(stoi(words)-1);
                    fout<<"(C, "<<words<<")";
                }
                else if(operation=="="){
                    LITTAB.push_back({words, lc});
                    fout<<"(L, "<<LITTAB.size()+1<<")";
                }
                else if(OPCODE.count(words)>0){
                    fout<<"("<<OPCODE[words].first<<")";
                }

                else{
                    if(SYMTAB.count(words)==0){
                        SYMTAB[words] = {lc, to_string(SYMTAB.size()+1)};
                    }
                    fout<<"(S, "<<SYMTAB[words].second<<")";
                }
            }
            lc++;
        }
        fout<<endl;
    }

        fin.close();
    fout.close();

    ofstream sout;
    sout.open("st.txt");

    for(auto i: SYMTAB){
        sout<<i.first<<" "<<i.second.first<<endl;
    }
    sout.close();

    ofstream lout;
    lout.open("lit.txt");

    for(auto i: LITTAB){
        lout<<i.first<<" "<<i.second<<endl;
    }
    lout.close();

    ofstream pout;
    pout.open("poolt.txt");

    for(auto i: POOLTAB){
        pout<<i<<endl;
    }

    pout.close();

    cout<<"End"<<endl;
}