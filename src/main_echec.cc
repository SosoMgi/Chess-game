/**
 * @file main_echec.cc
 * @author Sofian Mareghni
 * @version 1.0
 * @date 2022-04-24
 * 
 */



#include "Jeu.h"

int main(int argc, char *argv[]) 
{
	Jeu jeu;

	while (jeu.partie_en_cours()) 
	{
		jeu.print();
		jeu.play();
	}

	return 0;
}