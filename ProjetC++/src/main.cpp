#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <stdio.h>

#include "../include/Game.hpp"
#include "../include/Player.hpp"
#include "../include/Phase.hpp"
#include "../include/Unit.hpp"
#include "../include/Soldier.hpp"
#include "../include/Bowman.hpp"
#include "../include/Catapult.hpp"

using namespace std;

/*
 * Fonction assignValue
 *
 * Entress : la valeur a modifier, le nom de cette valeur et la nouvelle valeur
 * Sorties : aucune
 *
 * Assigne la valeur value a la cle key representee par le pointeur config
 */
void assignValue(int* config, const string key, const string value)
{
  int toInt;

  try
  {
    toInt = stoi(value);
  }
  catch(const invalid_argument& ia)
  {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
    return;
  }
  catch(const out_of_range& oor)
  {
    std::cerr << "Out of range : " << oor.what() << '\n';
    return;
  }

  if(toInt <= 0 || toInt > 100)
  {
    std::cout << "Invalid value for parameter : " << key << "\nValue must be between 1 and 100." << endl;
    return;
  }

  *config = toInt;
}

int main(int argc, char* argv[])
{
  //on supprime le fichier de logs, peu importe s'il existe ou pas
  remove("logs.txt");

  //Variables de configuration, initialisees a leurs valeurs par defaut
  int mapSize = 12;
  int playerHp = 100;
  int goldPerTurn = 8;
  int startingGolds = 12;

  //Soldier
  const int soldierId = 1;//ne pourra pas etre modifie par le fichier de config
  int soldierHp = 10;
  int soldierCost = 10;
  int soldierAttackValue = 4;
  int soldierPa = 1;
  int soldierMoveValue = 1;
  int soldierPm = 1;
  const Range soldierRange = {1, 1, 1};//min = 1, max = 1, aoe = 1

  //Bowman
  const int bowmanId = 2;//ne pourra pas etre modifier par le fichier de config
  int bowmanHp = 8;
  int bowmanCost = 12;
  int bowmanAttackValue = 3;
  int bowmanPa = 1;
  int bowmanMoveValue = 1;
  int bowmanPm = 1;
  const Range bowmanRange = {1, 3, 1};//min = 1, max = 3, aoe = 1

  //Catapult
  const int catapultId = 3;//ne pourra pas etre modifier par le fichier de config
  int catapultHp = 12;
  int catapultCost = 20;
  int catapultAttackValue = 6;
  int catapultPa = 1;
  int catapultMoveValue = 1;
  int catapultPm = 1;
  const Range catapultRange = {2, 3, 2};//min = 2, max = 3, aoe = 2

  ifstream ifs;
  string input;

  if(argc > 1)
  {
    ifs.open(argv[1]);//on ouvre le fichier de config

    if(ifs.is_open())
    {
      while(ifs.good())
      {
	getline(ifs, input);//on parse une ligne du fichier

	if(input[0] == '#' || input.size() <= 1)//on ignore la ligne si elle commence par #
	  continue;

	stringstream ss(input);
	string key;

	if(getline(ss, key, '='))//on parse la cle de la ligne
	{
	  string value;
	  
	  if(getline(ss, value))//on parse la valeur de la ligne
	  {
	    if(key.compare("mapSize") == 0)
	      assignValue(&mapSize, key, value);
	    else if(key.compare("playerHp") == 0)
	      assignValue(&playerHp, key, value);
	    else if(key.compare("goldPerTurn") == 0)
	      assignValue(&goldPerTurn, key, value);
	    else if(key.compare("startingGolds") == 0)
	      assignValue(&startingGolds, key, value);
	    else if(key.compare("soldierHp") == 0)
	      assignValue(&soldierHp, key, value);
	    else if(key.compare("soldierCost") == 0)
	      assignValue(&soldierCost, key, value);
	    else if(key.compare("soldierPa") == 0)
	      assignValue(&soldierPa, key, value);
	    else if(key.compare("soldierAttackValue") == 0)
	      assignValue(&soldierAttackValue, key, value);
	    else if(key.compare("soldierPm") == 0)
	      assignValue(&soldierPm, key, value);
	    else if(key.compare("soldierMoveValue") == 0)
	      assignValue(&soldierMoveValue, key, value);
	    else if(key.compare("bowmanHp") == 0)
	      assignValue(&bowmanHp, key, value);
	    else if(key.compare("bowmanCost") == 0)
	      assignValue(&bowmanCost, key, value);
	    else if(key.compare("bowmanPa") == 0)
	      assignValue(&bowmanPa, key, value);
	    else if(key.compare("bowmanAttackValue") == 0)
	      assignValue(&bowmanAttackValue, key, value);
	    else if(key.compare("bowmanPm") == 0)
	      assignValue(&bowmanPm, key, value);
	    else if(key.compare("bowmanMoveValue") == 0)
	      assignValue(&bowmanMoveValue, key, value);
	    else if(key.compare("catapultHp") == 0)
	      assignValue(&catapultHp, key, value);
	    else if(key.compare("catapultCost") == 0)
	      assignValue(&catapultCost, key, value);
	    else if(key.compare("catapultPa") == 0)
	      assignValue(&catapultPa, key, value);
	    else if(key.compare("catapultAttackValue") == 0)
	      assignValue(&catapultAttackValue, key, value);
	    else if(key.compare("catapultPm") == 0)
	      assignValue(&catapultPm, key, value);
	    else if(key.compare("catapultMoveValue") == 0)
	      assignValue(&catapultMoveValue, key, value);
	    else
	      cout << key << " : invalid parameter." << endl;
	  }
	  else
	    cerr << "Error : can't parse line : " << ss.str() << endl;
	}
	else
	  cerr << "Error : can't parse line : " << input << endl;
      }
    }
    else
    {
      cerr << "Error : can't open config file." << endl;
      return 1;
    }

    cout << "\nParsing du fichier de config : OK\n" << endl;
    ifs.close();
  }

  cout << "Bienvenue dans ce jeu tour par tour !\n" << endl;

  vector<Player*> players;
  vector<Unit*> factoryUnits;
  players.reserve(2);
  factoryUnits.reserve(3);
  int nbHumans = 0;
  int nbIA = 0;
  int difficulte = 2;
  input = "";
  bool restart = false;

  factoryUnits.push_back(new Soldier(soldierHp, soldierPa, soldierPm, soldierAttackValue, soldierMoveValue, soldierRange, soldierCost, soldierId));
  factoryUnits.push_back(new Bowman(bowmanHp, bowmanPa, bowmanPm, bowmanAttackValue, bowmanMoveValue, bowmanRange, bowmanCost, bowmanId));
  factoryUnits.push_back(new Catapult(catapultHp, catapultPa, catapultPm, catapultAttackValue, catapultMoveValue, catapultRange, catapultCost, catapultId));

  Phase phase;
  do{
  		if(players.size() > 0)
  			players.clear();
  		
		  do
		  {
		    if(nbHumans < 0 || nbHumans > 2)
			cout << "Erreur, le nombre entre doit etre compris entre 0 et 2. Recommencez svp." << endl;
		    
		    cout << "Combien de joueurs humains doit il y avoir dans la partie ( 2 max ) ?" << endl;
		    getline(cin,input);
		    if(input == "0") 
		    	nbHumans = 0;
		    else if(input == "1")
		    	nbHumans = 1;
		    else if(input == "2")
		    	nbHumans = 2;
		    else
		    	nbHumans = -1;
		  }while(nbHumans < 0 || nbHumans > 2);
		      
		  nbIA = 2 - nbHumans;
		  cout << "\nIl y aura donc " << nbHumans << " humains et " << nbIA << " IA dans la partie.\n" << endl;
		      
		  if(nbIA == 1)
		  {
		    do
		    {
					if(difficulte < 1 || difficulte > 4)
					    cout << "Erreur, le nombre entre doit etre compris entre 1 et 4. Recommencez svp." << endl;
					    
					cout << "\nChoisissez une difficulte pour l'IA:" << endl;
					cout << "1. Facile" << endl;
					cout << "2. Normal" << endl;
					cout << "3. Difficile" << endl;
					cout << "4. Tres difficile" << endl;
					getline(cin,input);

					if(input == "1")
						difficulte = 1;
					else if(input == "2")
						difficulte = 2;
					else if(input == "3")
						difficulte = 3;
					else if(input == "4")
						difficulte = 4;
					else
						difficulte = -1;
		    }while(difficulte < 1 || difficulte > 4);
		  }

		  switch(nbHumans)
		  {
		    case 0:
					players.push_back(new AI(playerHp, startingGolds));
					players.push_back(new AI(playerHp, startingGolds));
					break;
		    case 1:
					players.push_back(new Human(playerHp, startingGolds));
					switch(difficulte)
					{
					    case 1:
						players.push_back(new AI(playerHp/2, startingGolds));
						break;
					    case 2:
						 players.push_back(new AI(playerHp, startingGolds));
						 break;
					    case 3:
						 players.push_back(new AI(playerHp + 50, startingGolds));
						 break;
					    case 4:
						 players.push_back(new AI(playerHp * 2, startingGolds));
						 break;
					}
					break;
		    case 2:
					players.push_back(new Human(playerHp, startingGolds));
					players.push_back(new Human(playerHp, startingGolds));
					break;
		  }

		  Game game(players, factoryUnits, phase, mapSize, goldPerTurn);

		  game.run();

		  do{
		  	cout << "\nVoulez vous rejouer ? Entrez 'O' ou 'o' pour Oui, 'N' ou 'n' pour Non." << endl;
		 		getline(cin,input);
		  	if(input == "O" || input == "o")
		  		restart = true;

		  	else if(input == "N" || input == "n")
		  		restart = false;

		  	else
		  		cout << "Choix incorrect, recommencez svp." << endl;

		  }while(input != "O" && input != "o" && input != "N" && input != "n");
		  cout << "\n" << endl;

  }while(restart);

  factoryUnits.clear();

  return 0;
}
