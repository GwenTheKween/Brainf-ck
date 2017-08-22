/*projeto simples de um interpretador de brainf*ck
  Criado por: Bruno Piazera Larsen
  2017
  */
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>

#define new_memory {memory.push_back(0);}
#define ERROR(s,n) {cout<<s<<endl;exit(n);}

using namespace std;

bool command(char c){
	return (c=='>')||(c=='<')||(c=='.')||(c==',')||(c=='+')||(c=='-')||(c=='[')||(c==']');
}

vector<char> memory;
string prog;
stack<int> loop;
int pointer,curr_instruction;

int main(int argc, char** argv) {
	char c;
	int l_count=0;
	if(argc!=2) 
		ERROR("too few arguments",-1);
	fstream cod(argv[1],fstream::in);;
	if(!cod.is_open())
		ERROR("unable to open file",-1);
	new_memory;
	pointer=curr_instruction=0;
	prog="";
	while(cod>>c){
		if(command(c)){
			prog+=c;
			if(c=='[')l_count++;
			else if(c==']'){
				l_count--;
				if(l_count<0) ERROR("missing a [ character",prog.length());
			}
		}
	}
	if(l_count>0) ERROR("missing a ] character",-1);
	while(curr_instruction!=prog.size()){
		switch(prog[curr_instruction]){
		case '+':
			memory[pointer]++;
			break;
		case '-':
			memory[pointer]--;
			break;
		case '>':
			pointer++;
			if(pointer==memory.size()) new_memory;
			break;
		case '<':
			pointer--;
			if(pointer<0) ERROR("pointer can not go below 0",-1)
			break;
		case '[':
			loop.push(curr_instruction);
			break;
		case ']':
			if(memory[pointer]) curr_instruction=loop.top();
			else{
				loop.pop();
			}
			break;
		case '.':
			cout<<memory[pointer];
			break;
		case ',':
			memory[pointer]=getchar();
			break;
		}
		curr_instruction++;
	}
	return 0;
}
