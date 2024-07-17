#include "drukarnia.h"

int main() {
	Menu menu;
	menu.czytanie("magazyn_papier.txt", "magazyn_farba.txt", "magazyn_maszyna.txt");
	menu.start();
}