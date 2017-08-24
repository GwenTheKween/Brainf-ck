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

int main(int argc, char** argv) {
	char c;
	int l_count=0,pointer,curr_instruction;
	bool flag;
	fstream cod;
	vector<char> memory;
	string prog;
	stack<int> loop;

	if(argc>2) {
		ERROR("too many arguments",-1);
	}else if(argc==2){
		prog=argv[1];
		if(prog.find(".b")+2==prog.length())
			cod.open(argv[1],fstream::in);
		if(!cod.is_open())
			ERROR("unable to open file, is the extension '.b'?",-1);
		new_memory;
		pointer=curr_instruction=0;
		prog="";
		while(cod>>c){
			if(command(c)){
				prog+=c;
				if(c=='[')l_count++;
				else if(c==']'){
					l_count--;
					if(l_count<0)
						ERROR("missing a [ character",prog.length());
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
	}else{
		cout<<"enter your code, the interpreter leaves when an empty line is entered"<<endl;
		new_memory;
		pointer=0;
		flag=true;
		while(flag){
			cout<<">>!";
			prog="";
			l_count=0;
			flag=true;
			while((c=getchar())!='\n'){
				prog+=c;
				if(c=='[')l_count++;
				else if(c==']'){
					l_count--;
					if(l_count<0){
						cout<<"missing a [ character"<<endl;
						while((c=getchar())!='\n');
						flag=false;
						break;
					}
				}
			}
			if(!flag){
				flag=true;
				continue;
			}
			if(l_count>0)
				cout<<"missing a ] character"<<endl;
			else if(prog=="")
				flag=false;
			else{
				curr_instruction=0;
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
				for(int i=0;i<memory.size();i++){
					cout<<(int)memory[i]<<' ';
				}
				cout<<endl<<"pointer: "<<pointer<<endl;
			}
		}
	}
	return 0;
}
