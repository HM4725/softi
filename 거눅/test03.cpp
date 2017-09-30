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
int count=getChatCount(chats);
for (int i=x; i<=y&&i<=count--; i++){ 
/* i<=count : #remove 입력숫자가 chats수보다 클 때 for문 중지 
	count--한 이유는 아래의 이유와 같음.
*/
	removeChat(chats, x);
}	
/*removeChat(chats,i) 일땐 3-5인 경우
removeChat(chats,3) -> 4가 3이 되고 5가 4가 되는식으로 한칸씩 밀리기 때문에
그다음 removeChat(chats,4)를 할 땐 맨 처음엔 번호가 5였던 문장이 지워짐.
==> 3을 지운후 그다음 3을 지워야함(번호 4문장이 밀려서 번호 3문장이 되었기 때문)
그래서 removeChat(chats,x)로 계속 돌려줘야 하는것.
(오름차순이기 때문에 이런 현상이 일어나는것
아니면 ,에서의 알고리즘처럼 내림차순으로 하면 신경쓸필요없음.)
*/
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
int count=getChatCount(chats);
for(int xr=0; xr<k; xr++){
if(xrr[xr]<count&&xrr[xr]>=0){ // chats수 초과했을때,int값이 음수일 때  remove방지
removeChat(chats, xrr[xr]);
count--; // chats 수가 1개 줄었기 때문 (remove)
}
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
/* 
remove " - " : 오름차순으로 숫자가 연속적으로 나열된다.
	예를 들어 getchatCount가 8인 상황에서 (0,1,2,3,4,5,6,7)
	#remove 6-10을 했을 때 6,7만 지우고 8부터는 for문을 안돌려도 되므로
	for 문의 조건argument에 i<=count를 써준것
remove " , " : 내림차순으로 숫자가 불연속적으로 나열된다.
	예를 들어 getchatCount가 8인 상황에서 (0,1,2,3,4,5,6,7)
	#remove 1,100,4,3을 했을때 100,4,3,1로 int배열이 생성되는데
	이때 for문의 조건 argument에 i<=count조건을 더 써붙이면 for문이
	바로 정지되어 4,3,1을 지울 수 없기 때문에 if문을 사용한 것.


(보완)
#remove -2,-1,0,1(음수+",")의 경우에는 사실 , 케이스로 진행을 해야하는데
if 문중 - 케이스가 ,보다 먼저 진행되므로 위의 경우 -케이스로 실행됨
==> ,케이스를 -케이스보다 먼저 쓰면 해결됨.
if ( "," ~)
else if ( "-" ~ )

그리고 이 strtok 함수로는 -1-3같이 음수가 나오는 경우는 해결할 수 없음.
그래서 - 케이스에선 음수방지를 할수 없음.
*/

