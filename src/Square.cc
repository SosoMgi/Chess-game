#include "Square.h"



bool is_valid_input(string const &cmd) {
	regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
	return cmd.length() == 4 && regex_match(cmd, mouvmtpattern);
}


/*_______________________________________________________________________________________________*/


bool is_valid_little_roque(string const &cmd) {
	regex mouvmtpattern("(O|o|0)-(O|o|0)");
	return regex_match(cmd, mouvmtpattern);
}


/*_______________________________________________________________________________________________*/



bool is_valid_big_roque(string const &cmd) {
	regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
	return regex_match(cmd, mouvmtpattern);
}


/*_______________________________________________________________________________________________*/


Square::Square() : Square(0, 0) 
{}

/*_______________________________________________________________________________________________*/

Square::Square(int x, int y) : x(x), y(y) 
{}



/*_______________________________________________________________________________________________*/


int Square::get_x() const 
{
	return this->x;
}

/*_______________________________________________________________________________________________*/

int Square::get_y() const 
{
	return this->y;
}

/*_______________________________________________________________________________________________*/



void Square::to_string()
{

	int line = this->get_x() + 1;
	int column = this->get_y();;

	switch (column)
	{
	case 0:
		cout << "a" << line << endl;
		break;
	case 1:
		cout << "b" << line << endl;
		break;
	case 2:
		cout << "c" << line << endl;
		break;
	case 3:
		cout << "d" << line << endl;
		break;
	case 4:
		cout << "e" << line << endl;
		break;
	case 5:
		cout << "f" << line << endl;
		break;
	case 6:
		cout << "g" << line << endl;
		break;
	case 7:
		cout << "h" << line << endl;
		break;
	}
}


/*_______________________________________________________________________________________________*/




bool Square::to_alg(Square *org, Square *dest) 
{
	do {
		cin >> str;
	} while (str.at(0) == '#');
	roque = NONE;

	if (is_valid_little_roque(str) || is_valid_big_roque(str) ) 
	{
		if (str == "O-O") 
			roque = PETIT_ROQUE;
		if (str == "O-O-O")
			roque = GRAND_ROQUE;
		
		return true;
	}

	if (str != "/quit" && !is_valid_input(str)) 
		return false;

	org->set(str[0] - 'a', str[1] - '1');
	dest->set(str[2] - 'a', str[3] - '1');

	return true; 
}


/*_______________________________________________________________________________________________*/


void Square::set(int x, int y) 
{
	this->x = x;
	this->y = y;
}

/*_______________________________________________________________________________________________*/

void Square::set(Square const &position) 
{
	this->set(position.get_x(), position.get_y());
}


/*_______________________________________________________________________________________________*/



const Square operator+(Square const &pos1, Square const &pos2) 
{
	Square position(pos1.get_x() + pos2.get_x(), pos1.get_y() + pos2.get_y());
	return position;
}


/*_______________________________________________________________________________________________*/



const bool operator==(Square const &pos1, Square const &pos2) 
{
	return pos1.get_x() == pos2.get_x() && pos1.get_y() == pos2.get_y();
}

/*_______________________________________________________________________________________________*/

const bool operator!=(Square const &pos1, Square const &pos2) 
{
	return pos1.get_x() != pos2.get_x() || pos1.get_y() != pos2.get_y();
}


/*_______________________________________________________________________________________________*/

ostream &operator<<(ostream &out, Square const &pos) 
{
	out << "(" << pos.get_x() << " ; " << pos.get_y() << ")";
	return out;
}
