#include <iostream>
#include <climits>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class MNTvalues{
	int PP, KP, KPDTP, MDTP;

	public:
	MNTvalues(){
		PP=0;
		KP=0;
		KPDTP=0;
		MDTP=0;
	}

	friend class MacroProcessor;
};

class MacroProcessor{
	vector<pair<string, MNTvalues>>MNT;
	vector<pair<string, string>>KPDTAB;
	vector<vector<string>>MDT;
	vector<string>PNTAB;
	fstream file;

	fstream mnt;
	fstream kptab;
	fstream mdt;
	fstream pntab;

	public:

	MacroProcessor(){
		file.open("input.txt", ios::in);
		if(!file.is_open()){
			cout<<"Error in opening input file!"<<endl;
		}

		mnt.open("mnt.txt", ios::out);
		if(!mnt.is_open()){
			cout<<"Error in opening MNT file"<<endl;
		}

		mdt.open("mdt.txt", ios::out);
		if(!mdt.is_open()){
			cout<<"Error in opening MDT"<<endl;
		}

		kptab.open("kptab.txt", ios::out);
		if(!kptab.is_open()){
			cout<<"Error in opening KPDTAB"<<endl;
		}

		pntab.open("pntab.txt", ios::out);
		if(!pntab.is_open()){
			cout<<"Error in opening kpdtab"<<endl;
		}
	}

	int findParameter(string parameter, string name){
		int reference = 0;
		for(int i=0; i<PNTAB.size(); i++){
			if(PNTAB[i]==name){
				reference = i;
				break;
			}
		}
		for(int i=reference; i<PNTAB.size(); i++){
			if(PNTAB[i]==parameter){
				return i-reference;
			}
		}
		return -1;
	}


	void passOne(){
		vector<string>words;
		vector<string>temp;
		string line, name;

		int kcounter=0, mcounter=0, pcounter=0;
		bool insideMacro=false, firstline=false;
		MNTvalues m;

		if(file.is_open()){
			while(!file.eof()){
				getline(file, line);
				string w = "";
				for(int i=0; i<line.size(); i++){
					if(line[i] != ' '){
						w+=line[i];
					}
					else{
						words.push_back(w);
						w="";
					}
				}
				words.push_back(w);

				if(words[0] == "MACRO"){
					insideMacro = true;
					firstline = true;
				}

				else if(firstline && insideMacro){
					name = words[0];
					PNTAB.push_back(name);

					for(int i=1; i<words.size(); i++){
						if(words[i][0]=='&'){
							PNTAB.push_back(words[i]);
							pcounter++;
						}
						else if(words[i]=="="){
							if(i!=words.size()-1 && words[i+1][0]!='&'){
								KPDTAB.push_back({words[i-1], words[i+1]});
								kcounter++;
							}
							else if(i==words.size()-1 || words[i+1][0]=='&'){
								KPDTAB.push_back({words[i-1], ""});
								kcounter++;
							}
						}
					}
					if(kcounter!=0){
						m.KPDTP = KPDTAB.size() - kcounter + 1;
					}

					m.KP = kcounter;
					m.PP = pcounter-kcounter;
					m.MDTP = mcounter+1;
					firstline = false;
					pcounter=0;
					kcounter=0;
					MNT.push_back({words[0], m});
				}

				else if(!firstline && insideMacro){
					for(int i=0; i<words.size(); i++){
						if(words[i][0]=='&'){
							string para = "(P, ";
							para += to_string(findParameter(words[i], name));
							para += ")";
							temp.push_back(para);
						}
						else{
							temp.push_back(words[i]);
						}
					}
					MDT.push_back(temp);
					temp.clear();
					mcounter++;
				}

				if(words[0]=="MEND"){
					insideMacro=false;
				}



				// else if(firstline && insideMacro){
				// 	name = words[0];
				// 	PNTAB.push_back(name);
				// 	for(int i = 1; i<words.size(); i++){
				// 		if(words[i].at(0) == '&'){
				// 			PNTAB.push_back(words[i]);
				// 			pcounter++;
				// 		}
				// 		else if(words[i]=="="){
				// 			if(i!=words.size()-1 && words[i+1].at(0)!='&'){
				// 				KPDTAB.push_back({words[i-1], words[i+1]});
				// 				kcounter++;
				// 			}
				// 			else if(i==words.size()-1 || words[i+1].at(0)=='&'){
				// 				KPDTAB.push_back({words[i-1], ""});
				// 				kcounter++;
				// 			}
				// 		}
				// 	}

				// 	if(kcounter!=0){
				// 		m.KPDTP = KPDTAB.size() - kcounter + 1;
				// 	}

				// 	m.KP = kcounter;
				// 	m.PP = pcounter-kcounter;
				// 	m.MDTP = mcounter+1;
				// 	firstline = false;
				// 	pcounter = 0;
				// 	kcounter = 0;
				// 	MNT.push_back({words[0], m});
				// }


				// else if(!firstline && insideMacro){
				// 	for(int i=0; i<words.size(); i++){
				// 		if(words[i].at(0)=='&'){
				// 			string parameter = "(P, ";
				// 			parameter += to_string(findParameter(words[i], name));
				// 			parameter += ")";
				// 			temp.push_back(parameter);
				// 		}
				// 		else{
				// 			temp.push_back(words[i]);
				// 		}
				// 	}
				// 	MDT.push_back(temp);
                //     temp.clear();
                //     mcounter++;
				// }
				// if (words[0] == "MEND") {
				// 	insideMacro = false;
				// }
				words.clear();
			}
		}
		else{
			cout<<"Error in opening file!"<<endl;
			file.close();
		}
	}

	void displayMNT(){
			for(auto x: MNT){
				mnt<<x.first<<" "<<x.second.KP<<" "<<x.second.PP<<" "<<x.second.KPDTP<<" "<<x.second.MDTP<<endl;
			}
			mnt.close();
	}

	void displayKPDTAB() {
        for (auto x: KPDTAB) {
            kptab<<x.first<<" "<<x.second<<endl;
        }
        kptab.close();
    }

    void displayMDT() {
        for (int i = 0; i < MDT.size(); i++) {
            for (int j = 0; j < MDT[i].size(); j++) {
                mdt<<MDT[i][j]<<" ";
            }
            mdt<<endl;
        }
        mdt.close();
    }

    void displayPNTAB() {
        for (auto x: PNTAB) {
            pntab<<x<<endl;
        }
        pntab.close();
    }

};

int main(){
	MacroProcessor m;
	m.passOne();
	m.displayMNT();
    m.displayKPDTAB();
    m.displayMDT();
    m.displayPNTAB();

	return 0;
}
