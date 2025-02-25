#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename, vector<string> &names ,vector<int> &scores,vector<char> &grades){
    ifstream file(filename);
    string text;
    char name[100];
    char format[] = "%[^:]: %d %d %d";
    int a,b,c;
    int sum = 0;
    while(getline(file,text)){
        sscanf(text.c_str(),format,name,&a,&b,&c);
        sum = a+b+c;
        names.push_back(name);
        scores.push_back(sum);
        grades.push_back(score2grade(sum));
    }
}

void getCommand(string &command, string &key){
    string text;
    cout << "Please input your command: \n";
    cin >> command;
    if(toUpperStr(command) == "GRADE"||toUpperStr(command) == "NAME") {
        cin.ignore();
        getline(cin,text);
    }
    else {
        getline(cin,text);
    }
    key = text;
}

void searchName(vector<string> name,vector<int> score,vector<char> grade,string key){
    unsigned int i = 0;
    bool isFound = false;
    cout << "--------------------------------- \n";
    while(i < name.size()){
        if(toUpperStr(key) == toUpperStr(name[i])){
            printf("%s's score = %d\n%s's grade = %c\n",name[i].c_str(),score[i],name[i].c_str(),grade[i]);
            isFound = true;
            break;
        }
        i++;
    }
    if(!isFound) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> name,vector<int> score,vector<char> grade,string key){
    unsigned int i = 0;
    bool isFound = false;
    string key2 = toUpperStr(key);
    cout << "---------------------------------\n";
    while(i < grade.size()){
        if(key2[0] == grade[i]){
            printf("%s (%d)\n",name[i].c_str(),score[i]);
            isFound = true;
        }
        i++;
    }
    if(!isFound) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
