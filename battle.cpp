#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;
struct shipclss {
	char target[10][10];
};
void ttl();
int cti(char in);
void rand(int& num, int max);
void fill(char x[][10]);
void locate(char x[][10], bool manul);
bool check(char a[][10], int x, int y, int boat, bool t);
void play(char a[][10], char b[][10], char c[][10]);
void see(char x[][10]);
void see2(char x[][10], char y[][10]);
void hit(char a[][10], char b[][10], int x, int y, int water[], int& point, bool& hit);
int main(){
	shipclss ppnnt, you, hit;
	int rnd, max = 10;//random number
	bool man;
	char yes;
	rand(rnd, max);
	do{
	ttl();
	locate(ppnnt.target, false);
	cout << "Do you want to manually input ships. Input 0 for it to be inputed atuomatically, and 1 to manually put in your ships.\n";
	cin >> man;
	locate(you.target, man);
	fill(hit.target);
	play(you.target, hit.target, ppnnt.target);
	cout << "Do you want to play again?(y/n)\n";
	cin >> yes;
	}while(yes == 'y');
	return 0;
}
void play(char a[][10], char b[][10], char c[][10]){//a = you b = hit c = opponent
	//puts the game in play after ships are in place.
	int shp[] = {5, 4, 6, 4}, you[] = {5, 4, 6, 4}, pt = 19, yt = 19, x, y, j;
	char nxt;
	bool ht = 1;//hit
	do{
		see2(b, a);
		j = 5;
		for(int i = 0; i < 4; i++){
			cout << "	Ship" << j << ": " << shp[i] << "		      " << "Ship" << j << ": " << you[i] << "\n";
			j--;
		}
		do{
		cout << "Input the coordinates for target. ex: b7\n";
		cin >> nxt;
		y = cti(nxt);
		cin >> nxt;
		x = cti(nxt);
		hit(c, b, x, y, shp, pt, ht);
		//cout << pt; //test
	}while(ht);
	do{
		rand(x, 10);
		rand(y, 10);
		hit(a, a, x, y, you, yt, ht);
	}while(ht);
	//cout << yt; //test
}while(pt > 0 && yt > 0);
	see2(b, a);
	if(pt == 0)
		cout << "YOU WON!\n";
	else
		cout << "YOU lost...\n";
}
void hit(char a[][10], char b[][10], int x, int y, int water[], int& point, bool& hit){//checks if you hit a ship
	if(b[x][y] == 'o' || b[x][y] == 'x'){
		hit = true;
	}else{
		if(a[x][y] == '~'){
		b[x][y] = 'o';
		a[x][y] = 'o';
	}else{
	switch(a[x][y]){
		case '5':
		water[0] = water[0] - 1; 
		b[x][y] = 'x';
		a[x][y] = 'x';
		point--;
		break;
		case '4':
		water[1] = water[1] - 1;
		b[x][y] = 'x';
		a[x][y] = 'x';
		point--;
		break;		
		case '3':
		water[2] = water[2] - 1; 
		b[x][y] = 'x';
		a[x][y] = 'x';
		point--;
		break;
		case '2':
		water[3] = water[3] - 1; 
		b[x][y] = 'x';
		a[x][y] = 'x';
		point--;
		break;
			}	
		}
		hit = false;
	}
}
void locate(char a[][10], bool manul){//puts your ships in place. can be done manually or automatically
	int i, j, temp, x, y, z, ship[] = {5, 4, 3, 3, 2, 2};
	char nxt, rotat, typ[] = {'5', '4', '3', '3', '2', '2'};
	bool tr;
		cout << "Input your ships, You are given five ships.\n";
		do{
			fill(a);
			for(i = 0; i < 6; i++){
			if(manul)
			see(a);
			do{
			if(manul){
			cout << "Input location of ship. Ship: ";
			for(int s = 0; s < ship[i]; s++){
				cout << ship[i];
			};
			cout << ". ex: b7 \n";
			cin >> nxt;
			y = cti(nxt);
			cin >> nxt;
			x = cti(nxt);
			cout << "Do you want to rotate the ship(y/n)\n";
			cin >> rotat;
			if(rotat == 'y'){
				rotat = true;
			}else{
				rotat = false;
			}
		}else{
			rand(x, 10);
			rand(y,10);
			rand(z, 2);
			if(z == 1){
				rotat = true;
			}else{
				rotat = false;
			}
		}
			tr = check(a, x, y, ship[i], rotat);
			//cout << tr << endl;
			}while(((x < 0 || x > 9 )||(y < 0 || y > 9)) || tr == 0);
			if(rotat){
				temp = x;
				for(j = 0; j < ship[i]; j++){
					a[temp][y] = typ[i];
					temp++;
				}
			}else{
				temp = y;
				for(j = 0; j < ship[i]; j++){
					a[x][temp] = typ[i];
					temp++;
				}
			}
		}
		if(manul){
		cout << "do you like where your boats are?(y/n)\n";
		cin >> rotat;
		if(rotat == 'y'){
			rotat = true;
		}else{
			rotat = false;
		}
	}else
		rotat = 1;
	}while(!rotat);
}
void see(char x[][10]){//shows one grid
	int i, j;
const char abc[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	cout << " ";
	for(i = 0; i < 10; i++){
		cout << setw(2) << abc[i];
	}
	cout << "\n";
	for(i = 0; i < 10; i++){
		cout << i;
		for(j = 0; j < 10; j++){
			cout << setw(2) << x[i][j];
		}
		cout << "\n";
	}
}
void fill(char a[][10]){//fills the array with "~" charecters
	int i, j;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			a[i][j] = '~';
		}
	}
}
bool check(char a[][10], int x, int y, int boat, bool t){//checks if a ship is already in that spot
	int temp, i, tr = 0;
	bool yes;
	
		if(t == true){
			temp = x;
			if(x <= (10 - boat)){
			for(i = 0; i < boat; i++){
			if(a[temp][y] == '~'){
			tr++;
		}else{
			tr--;
			i = boat;
			}
			temp++;
			}
		}
	}else{
			temp = y;
			if(y <= (10 - boat)){
			for(i = 0; i < boat; i++){
			if(a[x][temp] == '~'){
				tr++;
			}else{
				tr--;
				i = boat;
			}
			temp++;
		}
	}
}
	//cout << tr;
	if(tr == boat)
		yes = true;
	else
		yes = false;
	return yes;
}
void see2(char x[][10], char y[][10]){//shows two grids
	const char abc[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};
	int i, j;
	cout << "	target				you\n\n ";
	for(i = 0; i < 10; i++){
		cout << setw(2) << abc[i];
	}
	cout << "	 	";
	for(i = 0; i < 10; i++){
		cout << right <<  setw(2) << abc[i];
	}
	cout << "\n";
	for(i = 0; i < 10; i++){
		cout << i;
		for(j = 0; j < 10; j++){
			cout << setw(2) << x[i][j];
		}
		cout << "          ";
		cout << i;
		for(j = 0; j < 10; j++){
			cout << setw(2) << y[i][j];
		}
		cout << "\n";
	}
}
void rand(int& num, int max){//outputs a random integer
	ifstream fin;
	ofstream fout;
	char n;
	int rdm, i;
	fin.open("rdm.txt");
	if (fin.fail()){
		cout << "failed to open1\n";
		exit(1);
	}
	
	fin >> n;
	num = cti(n);
	for (i = 0; i < num; i++){
		rdm = rand() % max;
	}
	//cout << rdm << endl;
	fout.open("rdm.txt");
	if (fout.fail()){
		cout << "failed to open2\n";
		exit(1);
	}
	num++;
		fout << num;
		num = rdm;
		fin.close();
		fout.close();
}
int cti(char in){//converts charicters to integers
	int intger;
	switch(in){
		case '0':
		intger = 0;
		break;
		case '1':
		intger = 1;
		break;
		case '2':
		intger = 2;
		break;
		case '3':
		intger = 3;
		break;
		case '4':
		intger = 4;
		break;
		case '5':
		intger = 5;
		break;
		case '6':
		intger = 6;
		break;
		case '7':
		intger = 7;
		break;
		case '8':
		intger = 8;
		break;
		case '9':
		intger = 9;
		break;
		case 'a':
		intger = 0;
		break;
		case 'b':
		intger = 1;
		break;
		case 'c':
		intger = 2;
		break;
		case 'd':
		intger = 3;
		break;
		case 'e':
		intger = 4;
		break;
		case 'f':
		intger = 5;
		break;
		case 'g':
		intger = 6;
		break;
		case 'h':
		intger = 7;
		break;
		case 'i':
		intger = 8;
		break;
		case 'j':
		intger = 9;
		break;
		default:
		intger = 10;
	}
	return intger;
}
void ttl(){//shows title
	cout << "bbbbbb      aaaaa     ttttttttt ttttttttt lll   eeeeeee\n";
	cout << " bb  bb    aa   aa    ttttttttt ttttttttt lll   eee    \n";
	cout << " bbbbb    aaaaaaaaa      ttt       ttt    lll   eeeee  \n";
	cout << " bb  bb  aaa     aaa     ttt       ttt    lllll eee    \n";
	cout << "bbbbbb  aaa       aaa    ttt       ttt    lllll eeeeeee\n";
	cout << "\n";
	cout << "		 ssss  hh   hh iiiiiiiii pppppp  \n";
	cout << "		s      hh   hh    iii     pp  pp \n";
	cout << "		 ssss  hhhhhhh    iii    pppppp  \n";
	cout << "		     s hh   hh    iii     pp     \n";
	cout << "		 ssss  hh   hh iiiiiiiii  pp     \n";
	cout << "\n";
}