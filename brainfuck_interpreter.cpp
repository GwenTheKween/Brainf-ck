/*projeto simples de um interpretador de brainf*ck
  Criado por: Bruno Piazera Larsen
  2017
  */

#include <iostream>
#include <vector>
#include <string>
#include <stack>

#define new_memory {memory.push_back(0);}
#define ERROR(s) {cout<<s<<endl;exit(0);}

using namespace std;

vector<char> memory;
string prog;
stack<int> loop;
int pointer,curr_instruction;

int main() {
	char c;
	new_memory;
	pointer=curr_instruction=0;
	prog="";
	while(cin>>c){
		prog+=c;
	}
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
			if(pointer<0) ERROR("pointer can not go below 0")
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
			cin>>memory[pointer];
			break;
		}
		curr_instruction++;
	}
	return 0;
}