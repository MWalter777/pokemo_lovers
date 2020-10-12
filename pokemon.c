// recorer arbol en forma inorder (Izquierdo-Raiz-Derecho)
/*
** Autor: Walter Marroquin
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#define ENTER 13
#define ESC 27
#define LEFT 75
#define RIGHT 77
#define ARROW_UP 72
#define ARROW_DOWN 80
#define START_LINE 1
#define END_LINE 3
#define CLEAR system("cls");
#define FIRST_MESSAGE printf("    Seleccione una opcion y presione enter o presione ESC para salir \n");

/*    							ESTRUCTURA DEL ARBOL
*									(raiz)
*		¿Es pokemon en especifico?			¿Es de tipo x? 				
*					/								\
*				   /								 \
*				(nuevoNodo)						(nuevo nodo)
*
*/

int X = 8;
int Y = 7;
int NUMBER = 0;

struct node {
	char type[50];
	char name[50];
	int number;
	int option;
	struct node* left;
	struct node* right;
};


// Imprimimos los pokemon y su codigo para la visualizacion en el arbol
void printPokemonAndId(struct node* root) {
	if (root == NULL) return;
	printPokemonAndId(root->left);
	printf("{%d : %s},",root->number, root->name);
	printPokemonAndId(root->right);
}


// Inorder traversal
void inorder(struct node* root, int x, int y) {
	if (root == NULL) return;
	if(root->left != NULL){
		gotoxy(x-3,y+1);
		printf("/");
	}
	inorder(root->left, x-3, y+2);
	gotoxy(x,y);
	//printf("%s -> %s", root->type, root->name);
	printf("%d",root->number);
	if(root->right != NULL){
		gotoxy(x+3,y+1);
		printf("\\");		
	}
	inorder(root->right, x+3, y+2);
}


// Create a new Node
struct node* createNode(char type[50], char name[50], int option) {
	struct node* newNode = malloc(sizeof(struct node));
	strcpy(newNode->type, type);
	strcpy(newNode->name, name);
	newNode->number = NUMBER;
	newNode->option = option;
	NUMBER +=1;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

// Insert on the left of the node
void insertRightLeft(struct node* root, char type[50], char name[50], int option) {
	if(root != NULL){
		if(root->left == NULL){
			root->left = createNode(type, name, option);
		}else{
			if(root->right != NULL){
				insertRightLeft(root->right, type, name, option);
			}else{
				root->right = createNode(type, name, option);
			}
		}		
	}else{
		root = createNode(type, name, option);
	}
}

// Insert on the left of the node
void insertLeftRight(struct node* root, char type[50], char name[50], int option) {
	if(root != NULL){
		if(root->right == NULL){
			root->right = createNode(type, name, option);
		}else{
			if(root->left != NULL){
				insertLeftRight(root->left, type, name, option);
			}else{
				root->left = createNode(type, name, option);
			}
		}		
	}else{
		root = createNode(type, name, option);
	}
}

void gotoxy(int x,int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
	COORD dwPos;  
	dwPos.X = x;  
	dwPos.Y= y;  
	SetConsoleCursorPosition(hcon,dwPos);  
}

int gessPokemon(struct node* root, int x, int y){
	if (root == NULL) return;
	int isType, isPokemon, option;
	char name[50], type[50];
	gotoxy(x,y);
	y++;
	gotoxy(x,y);
	printf("%s ?", root->type);
	y++;
	isType = yesOrNot(x,y);
	if(isType==root->option){
		y++;
		gotoxy(x,y);
		printf("Es %s ?", root->name);
		y++;
		isPokemon = yesOrNot(x,y);
		if(isPokemon == 1){
			printf("Adivine!!! ");
			getch();
			return;
		}else{
			if(root->left == NULL){
				fflush(stdin);
				y++;
				gotoxy(x,y);
				printf("En que pokemon pensabas ?");
				y++;
				gotoxy(x,y);
				gets(name);
				y++;
				gotoxy(x,y);
				printf("Que pregunta diferenciaria a %s de %s ?", name,root->name);
				y++;
				gotoxy(x,y);
				gets(type);
				y++;
				gotoxy(x,y);
				printf("Si tu pokemon fuera %s cual seria la respuesta a %s ?",name, type);
				y++;
				option = yesOrNot(x,y);
				insertRightLeft(root, type, name, option);
			}else{
				gessPokemon(root->left, x, y);
			}			
		}
	}else{
		if(root->right == NULL){
			fflush(stdin);
			char name[50], type[50];
			y++;
			gotoxy(x,y);
			printf("En que pokemon pensabas ?");
			y++;
			gotoxy(x,y);
			gets(name);
			y++;
			gotoxy(x,y);
			printf("Que pregunta diferenciaria a %s de %s ?", name,root->name);
			y++;
			gotoxy(x,y);
			gets(type);
			y++;
			gotoxy(x,y);
			printf("Si tu pokemon fuera %s cual seria la respuesta a %s ?",name, type);
			y++;
			option = yesOrNot(x,y);
			insertLeftRight(root, type, name,option);
		}else{
			gessPokemon(root->right, x, y);
		}
	}
	
}


int yesOrNot(int x,int y){
	int res = 1, val;
	gotoxy(x,y);
	printf(" ____ ");
	gotoxy(x,y+1);
	printf("| SI |");
	gotoxy(x,y+2);
	printf(" ---- ");
	gotoxy(x+12, y+1);
	printf("  NO  ");
	val = getch();
	while(val != ENTER){
		switch(val){
			case LEFT:
				gotoxy(x,y);
				printf(" _____");
				gotoxy(x,y+1);
				printf("| SI  |");
				gotoxy(x,y+2);
				printf(" ---- ");
				gotoxy(x+12, y);
				printf("       ");
				gotoxy(x+12, y+1);
				printf("  NO   ");
				gotoxy(x+12, y+2);
				printf("       ");
				res = 1;
				break;
			case RIGHT:
				gotoxy(x,y);
				printf("       ");
				gotoxy(x,y+1);
				printf("  SI   ");
				gotoxy(x,y+2);
				printf("       ");
				gotoxy(x+12, y);
				printf(" ____ ");
				gotoxy(x+12, y+1);
				printf("| NO |");
				gotoxy(x+12, y+2);
				printf(" ---- ");
				res = 2;
				break;
		}
		val = getch();
	}
	
	gotoxy(x,y);
	printf("           ");
	gotoxy(x,y+1);
	printf("           ");
	gotoxy(x,y+2);
	printf("           ");
	gotoxy(x+12, y);
	printf("           ");
	gotoxy(x+12, y+1);
	printf("           ");
	gotoxy(x+12, y+2);
	printf("           ");
	return res;
}

void playGame(){
	struct node* root = createNode("Es de electricidad", "Pikachuu",1);
	int x=5, y=5, exit;
	CLEAR
	printf("Estas pensando en un pokemon? \n");
	exit = yesOrNot(x,y);
	
	while(exit != 2){
		CLEAR
		gessPokemon(root, 0, 0);
		CLEAR
		printf("Estas pensando en un pokemon? \n");
		exit = yesOrNot(x,y);
	}
	CLEAR
	printPokemonAndId(root);
	inorder(root, 16, 7);
	gotoxy(x,y+5);	
}

void showRules(){
	printf("============================================ REGLAS DEL JUEGO ==========================================================\n");
	printf("\n\nRESPONDE LAS PREGUNTAS QUE SE TE INDICARAN PARA ALMACENARLOS EN EL ARBOL, UTILIZA LAS FLEZHAS (IZQUIERDA-DERECHA) PARA SELECCIONAR UNA OPCION (SI O NO) Y PRESIONA ENTER PARA ESCOGER LA OPCION, CUANDO SE TE PIDA EL NOMBRE O DESCRIPCION DE UN POQUEMON PUEDES UTILIZAR ESPACIOS EN BLANCO Y SE GUARDARA HASTA QUE PRESIONES ENTER\n\n");
}

void ask_for_continue(int y){
    gotoxy(0,y);
    printf("Presiona cualquier tecla para volver al menu\n\n");
    getch();
}
int menu(){
	int option, position_y=START_LINE, y=15, X=25;
	FIRST_MESSAGE
	printf("    1.  JUGAR	\n");
	printf("    2.  REGLAS DEL JUEGO\n");
	printf("    4. Salir \n");
	gotoxy(0, position_y);
	printf(">>>");
	gotoxy(X, position_y);
	printf("<<<");
	option = getch();
	while(option != ENTER && option != ESC){
		gotoxy(0, position_y);
		printf("   ");
		gotoxy(X, position_y);
		printf("   ");
		switch(option){
            case ARROW_UP:
            	position_y--;
            break;
            case ARROW_DOWN:
            	position_y++;
            break;
		}
		if (position_y > END_LINE) position_y=START_LINE; //si la posicion de y es mayor a 5 significa que hay que regresarlo a la opcion 1 del menu
		if (position_y < START_LINE) position_y=END_LINE; //Si la posicion de y es cero significa que debe regresar al ultimo item
		gotoxy(0,position_y);
		printf(">>>");
		gotoxy(X, position_y);
		printf("<<<");
		option = getch();
	}
	gotoxy(0,START_LINE);
	if(option==ENTER){
		switch(position_y){
			case START_LINE:
				CLEAR
				playGame();
			break;
			case START_LINE + 1:
				CLEAR
				showRules();
			break;
		}
	}
	if(option != ESC && position_y != END_LINE ){
		ask_for_continue(y);
	}
	else {
		position_y = END_LINE;
		CLEAR
	}
	return position_y;
}


int main(){
	int exit= 0;
	do{
		CLEAR
		exit = menu();
	}while(exit!=END_LINE);
	
	return 0;
}

