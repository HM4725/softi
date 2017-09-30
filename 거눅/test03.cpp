#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int NUM_OF_CHAT = 200;

int getChatCount(string *_chatList){
	int i;
	for(i=0; i<NUM_OF_CHAT; ++i){
	string s = _chatList[i];
	if(s.empty() == true)
	break;
	}
return i;
}

void printChat(string *_chatList){
int count = getChatCount(_chatList);
for(int i=0; i<count; ++i){
cout << i << " " << _chatList[i] << endl;
}
}

bool addChat(string *_chatList, string _chat){
_chatList[getChatCount(_chatList)] = _chat;
return true;

}
bool removeChat(string *_chatList, int _index){

int count=getChatCount(_chatList);

for(int a=_index; a<count-1;a++){

_chatList[a]=_chatList[a+1];

}

_chatList[count-1]="";

return true;
}

int main() {
string*chats = new string[NUM_OF_CHAT];

addChat(chats, "Hello, Reply Administrator!");
addChat(chats, "I will be a good programmer.");
addChat(chats, "This class is awesome");
addChat(chats, "Professor Lim is wise.");
addChat(chats, "Two TAs are kind and helpful.");
addChat(chats, "I think TAs look cool.");

while (true) {
string command;
getline(cin, command);

char *removeN = strtok((char *)command.c_str(), " ");

if (command.find("quit") != -1)
break;
else if (command.find("#remove") != -1) {

if (command.find('-') != -1){

removeN = strtok(NULL, "-");
int x = atoi(removeN);
removeN = strtok(NULL, "-");
int y = atoi(removeN);
for (int i=x; i<=y; i++)
{
removeChat(chats, i);
}
printChat(chats);
}

else{
int arr[200];
int num=0;
int k=1;
removeN = strtok(NULL,",");
while(removeN!=NULL){
arr[num]=atoi(removeN);
num=num+1;
k=k+1;
removeN = strtok(NULL, ",");
if(removeN==NULL){
num=num-1;
k=k-1;
}
}
int xrr[k];
for(int m=0; m<k; m++){
xrr[m]=arr[m];
}
sort(xrr,xrr+k);
reverse(xrr, xrr+k);
for(int xr=0; xr<k; xr++){
removeChat(chats, xrr[xr]);
}
printChat(chats);
}
}

else if (addChat(chats, command))
printChat(chats);
}

delete[] chats;
return 0;

}
