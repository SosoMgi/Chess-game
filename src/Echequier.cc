#include "Echequier.h"
#include "piece/Fou.h"
#include "piece/Roi.h"
#include "piece/Cavalier.h"
#include "piece/Pion.h"
#include "piece/Dame.h"
#include "piece/Tour.h"
#include "Square.h"
#include <algorithm>
#include <cstdlib>
#include <iostream> 

using namespace std; 


Echequier::Echequier() : grille() 
{
	roi_noir = new Roi(NOIR, "\u265A" );
	roi_blanc = new Roi(BLANC, "\u2654");

	for (size_t i = 0; i < 8; i++) 
	{
		poser(Square(i, 1), new Pion(BLANC, "\u2659"));
		poser(Square (i, 6), new Pion(NOIR, "\u265F"));
	}
	poser(Square(0, 0), new Tour(BLANC, "\u2656"));
	poser(Square(7, 0), new Tour(BLANC, "\u2656"));
	poser(Square(1, 0), new Cavalier(BLANC, "\u2658"));
	poser(Square(6, 0), new Cavalier(BLANC, "\u2658"));
	poser(Square(2, 0), new Fou(BLANC, "\u2657"));
	poser(Square(5, 0), new Fou(BLANC, "\u2657"));
	poser(Square(3, 0), new Dame(BLANC, "\u2655"));
	poser(Square(4, 0), roi_blanc);

	poser(Square(7, 7), new Tour(NOIR, "\u265C"));
	poser(Square(0, 7), new Tour(NOIR, "\u265C"));
	poser(Square(1, 7), new Cavalier(NOIR, "\u265E"));
	poser(Square(6, 7), new Cavalier(NOIR, "\u265E"));
	poser(Square(2, 7), new Fou(NOIR, "\u265D"));
	poser(Square(5, 7), new Fou(NOIR, "\u265D"));
	poser(Square(3, 7), new Dame(NOIR, "\u265B"));
	poser(Square(4, 7), roi_noir); 

	Piece *tmp;
	for (size_t i = 0; i < 8; i++) 
	{ 
		for (size_t j = 0; j < 8; j++) 
		{
			tmp = get(Square(i, j));
			if (tmp != nullptr) {
				if (tmp->get_couleur() == BLANC) 
				{
					this->pieces_blanches.push_back(tmp);
				} 
				else 
				{
					this->pieces_noires.push_back(tmp);
				}
			}
		}
	}
}



/*_______________________________________________________________________________________________*/



void Echequier::affiche() 
{
	string space5 = string(5, ' ');
	cout << endl;
	cout << "     a     b     c     d     e     f     g     h   " << endl;
	cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
	for (int y(8 - 1); y >= 0; y--) 
	{
		cout << y + 1 << " ";
		for (int x(0); x < 8; x++)
		{
			cout << "|";
			if (this->grille[x][y] != nullptr) 
			{
				cout << "\u0020\u0020"; // U+0020 est un esapce utf-8 taille
										// police
				cout << this->grille[x][y]->get_nom();
				cout << "\u0020"
					 << " ";
			} 
			else 
			{
				cout << space5; // 2 ascii spaces
			}
		}
		cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
		cout << endl;
	}
}



/*_______________________________________________________________________________________________*/



void Echequier::poser(Square const &position, Piece *piece) 
{
	this->grille[position.get_x()][position.get_y()] = piece;
	if (piece != nullptr) 
		piece->set_position(position);
}



/*_______________________________________________________________________________________________*/



Piece *Echequier::get(Square const &position) const 
{
	if (position.get_x() < 0 || position.get_x() > 7)
		return nullptr;
	if (position.get_y() < 0 || position.get_y() > 7)
		return nullptr;

	return this->grille[position.get_x()][position.get_y()];
}



/*_______________________________________________________________________________________________*/



void Echequier::destruction_piece(Square const &position, bool free) 
{
	if (get(position) != nullptr) 
	{
		if (get(position)->get_couleur() == BLANC) 
		{
			vector<Piece *>::iterator vec_position =
				find(pieces_blanches.begin(), pieces_blanches.end(), get(position));
			if (vec_position != pieces_blanches.end())
				pieces_blanches.erase(vec_position);
		} 
		
		else 
		{
			vector<Piece *>::iterator vec_position =
				find(pieces_noires.begin(), pieces_noires.end(), get(position));
			if (vec_position != pieces_noires.end())
				pieces_noires.erase(vec_position);
		}
		if (free)
			delete get(position);
	}
	poser(position, nullptr);
}




/*_______________________________________________________________________________________________*/




bool Echequier::mvt(Square const &org, Square const &dest,
				 	bool move_effective) 
{
	Piece *cible = this->get(org);

	if (cible == nullptr) 
	{
		cerr << "invalid piece" << endl;
		return false;
	}

	cible->set_position(org);

	if (this->get(dest) != nullptr && cible->get_couleur() == this->get(dest)->get_couleur()) 
		return false;

	bool cible_vide = this->get(dest) == nullptr ;
	if (!cible->mvt_legal(dest, this, cible_vide)) 
		return false;
	

	this->destruction_piece(dest, move_effective);
	this->poser(dest, cible);
	this->poser(org, nullptr);

	if (move_effective)
		cible->mvt(*this, org, cible_vide);

	return true;
}




/*_______________________________________________________________________________________________*/



bool Echequier::ligne_vide(Square const &org, Square const &dest) const 
{
	if (org.get_x() != dest.get_x() && org.get_y() != dest.get_y()) 
		return false;
	

	if (org.get_y() == dest.get_y()) 
	{
		int distance = abs(dest.get_x() - org.get_x());
		int dir = (dest.get_x() - org.get_x()) / distance;

		for (int i = 1; i < distance; i++) 
		{
			if (this->get(org + Square(dir * i, 0)) != nullptr) 
				return false;
		}
	} 
	
	else 
	{
		int distance = abs(dest.get_y() - org.get_y());
		int dir = (dest.get_y() - org.get_y()) / distance;

		for (int i = 1; i < distance; i++) 
		{
			if (this->get(org + Square(0, dir * i)) != nullptr) 
				return false;
		}
	}
	return true;
}





/*_______________________________________________________________________________________________*/




bool Echequier::diag_vide(Square const &org, Square const &dest) const 
{
	if (abs(dest.get_x() - org.get_x()) != abs(dest.get_y() - org.get_y())) 
		return false;
	

	int distance = abs(dest.get_x() - org.get_x());
	int x_dir = (dest.get_x() - org.get_x()) / distance;
	int y_dir = (dest.get_y() - org.get_y()) / distance;

	for (int i = 1; i < distance; i++) 
	{
		if (this->get(org + Square(x_dir * i, y_dir * i)) != nullptr) 
			return false;
		
	}

	return true;
}




/*_______________________________________________________________________________________________*/




Piece *Echequier::get_roi(Couleur couleur) 
{
	return couleur == BLANC ? roi_blanc : roi_noir;
}




/*_______________________________________________________________________________________________*/



vector<Piece *> Echequier::get_pieces(Couleur couleur) 
{
	return couleur == NOIR ? pieces_noires : pieces_blanches;
}



/*_______________________________________________________________________________________________*/




bool Echequier::roi_en_echec(Couleur couleur) 
{
	Piece *roi = get_roi(couleur);
	Piece *tmp;
	Square pos = Square(0, 0);

	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			pos.set(i, j);
			tmp = get(pos);

			if (tmp == nullptr)
				continue;
			// ignore piece of same king color
			if (tmp->get_couleur() == couleur)
				continue;

			if (tmp->mvt_legal(roi->get_position(), this, false)) 
				return true;
		}
	}
	return false;
}





/*_______________________________________________________________________________________________*/




bool Echequier::promotion(Square destination, Couleur player)
{
	string type;
	do {
		cin >> type;
	} while (type.at(0) == '#');

	Piece *new_piece = nullptr;
	if (player == NOIR)
	{
		if (type == "Queen")
			new_piece = new Dame(NOIR, "\u265B");
		else if (type == "Knight")
			new_piece = new Cavalier(NOIR, "\u265E");
		else if (type == "Bishop")
			new_piece = new Fou(NOIR, "\u265D");
		else if (type == "Rook")
			new_piece = new Tour(NOIR, "\u265C");
	}

	else
	{
		if (type == "Queen")
			new_piece = new Dame(BLANC, "\u2655");
		else if (type == "Knight")
			new_piece = new Cavalier(BLANC, "\u2658");
		else if (type == "Bishop")
			new_piece = new Fou(BLANC, "\u2657");
		else if (type == "Rook")
			new_piece = new Tour(BLANC, "\u2656");
	}

	if (new_piece == nullptr) //Not a valid piece type
		return false;

	this->poser(destination, new_piece);

	return true;
}





/*_______________________________________________________________________________________________*/




void Echequier::update_position() 
{
	for (size_t i = 0; i < 8; i++) 
	{
		for (size_t j = 0; j < 8; j++) 
		{
			if (grille[i][j] != nullptr)
				grille[i][j]->set_position(Square(i, j));
		}
	}
}




/*_______________________________________________________________________________________________*/



 string Echequier::pgn_piece_name(string const name, bool view_pawn, bool view_color) const 
 {

	string psymb;
	if      (name=="\u2656") psymb="R";  // Rook W
	else if (name=="\u2658") psymb="N";  // Knight W
	else if (name=="\u2657") psymb="B";  // Bishop W
	else if (name=="\u2655") psymb="Q";  // Queen W
	else if (name=="\u2654") psymb="K";  // King W
	else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
	if (psymb.size()>0) 
	{ // one of the white piece has been found
			if (view_color)
					return "w"+psymb;
			else
					return psymb;
	} 
	if      (name=="\u265C") psymb= "R";  // Rook B
	else if (name=="\u265E") psymb= "N";  // Knight B
	else if (name=="\u265D") psymb= "B"; // Bishop B
	else if (name=="\u265B")  psymb= "Q"; // Queen B
	else if (name=="\u265A")  psymb= "K"; // King B
	else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
	if (psymb.size()>0) 
	{ // one of the black piece has been found
			if (view_color)
					return "b"+psymb;
			else
					return psymb;
	} 
	else return "";
}




/*_______________________________________________________________________________________________*/




string Echequier::canonical_position() const 
{
      string output;
	  Square square;
	  string str;
      for (size_t row(1); row<=8; row++)
	  {
              for (char col('a');col<='h';col++) 
			  {
                       square.set(col-'a', row-1);
                      if (this->get(square) != nullptr)
					  {
						  // get pieces with theit PGN names, 
                          // true -> with P for pawns, true -> w/b for colors.
						str = this->get(square)->get_nom();
                            output += pgn_piece_name(str,true,true);
                      output += ",";
					  }
              }
      }
	  cout << output << endl;
      return output;
}




/*_______________________________________________________________________________________________*/



bool Echequier::roque(int roque, Couleur couleur) 
{
	Piece *tour;

	switch (roque)
	{
		case 1:
			tour = get(Square(0, couleur == BLANC ? 0 : 7));
			break;
		case 2:
			tour = get(Square(7, couleur == BLANC ? 0 : 7));
			break;
		default:
			return false;
	}

	if (get_roi(couleur)->first_mvt())
	{
		cerr << "invalid castling" << endl;
		cerr << "king has already moved" << endl;
		return false;
	}

	if (tour == nullptr || tour->first_mvt())
	{
		cerr << "invalid castling" << endl;
		cerr << "tower has already moved or is not here" << endl;
		return false;
	}

	if (!this->ligne_vide(tour->get_position(), get_roi(couleur)->get_position()))
	{
		cerr << "invalid castling" << endl;
		cerr << "piece between king and rook" << endl;
		return false;
	}

	int roi_dir =
		tour->get_position().get_x() - get_roi(couleur)->get_position().get_x();
	roi_dir /= abs(roi_dir);
	int tour_dir = -roi_dir;

	poser(get_roi(couleur)->get_position(), nullptr);
	poser(get_roi(couleur)->get_position() + Square(2 * roi_dir, 0),
		get_roi(couleur));

	poser(tour->get_position(), nullptr);
	poser(get_roi(couleur)->get_position() + Square(tour_dir, 0), tour);
	return true;
}



/*_______________________________________________________________________________________________*/



void Echequier::dispose() 
{
	for (auto const &piece : pieces_noires) 
	{
		delete piece;
	}

	for (auto const &piece : pieces_blanches) 
	{
		delete piece;
	}
}


