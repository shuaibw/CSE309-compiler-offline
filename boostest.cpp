#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> split(string s, char c = ' '){
    vector<string> result;
    const char* str = s.c_str();
    do{
        const char *begin = str;
        while(*str != c && *str) str++;
        result.push_back(string(begin, str));
    } while (0 != *str++);
    return result;
}

vector<string> parse_params(string s){
    vector<string> result;
    vector<string> comma_sep = split(s, ',');
    for(const auto &str: comma_sep){
        vector<string> space_sep = split(str, ' ');
        if(space_sep.size()!=2){
            result.push_back("ERR");
            return result;
        }
        result.push_back(space_sep.back());
    }
    return result;
}

int main(){
    vector<string> vec = parse_params("int a,int b,float c,double d");
    for(const auto &s: vec){
        cout<<s<<endl;
    }
}