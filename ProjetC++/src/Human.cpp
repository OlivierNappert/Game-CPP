#include <iostream>
#include "../include/Human.hpp"
#include "../include/Unit.hpp"

void Human::shop(std::vector<Unit*> factoryUnits, const int direction, const int mapSize)
{
    std::cout << "Bienvenue dans la boutique Player " << (direction == -1 ? 1 : 2) <<"." << std::endl;

    if(!hasEnoughGold(factoryUnits[0]->getCost()))
    {
        std::cout << "Vous n'avez pas assez d'argent pour acheter une Unite. Sortie de la boutique." << std::endl;
	   return;
    }

    if(units.size() > 0)
    {
      if(unitOnBase(direction,mapSize))
      {
	   std::cout << "Une Unite se trouve deja sur votre base, impossible d'acheter a nouveau une Unite. Sortie de la boutique." << std::endl;
	   return;
      }
    }

    std::vector<std::string> unitNames;

    // On met dans le vector unitNames les noms complets des unites ainsi que leurs initiales
    for(unsigned int i = 0; i < factoryUnits.size(); i++){
	   unitNames.push_back(factoryUnits[i]->getName());
	   unitNames.push_back(factoryUnits[i]->getName().substr(0,1));
    }

    std::string choix = "";
    bool canBuy;

     do{
        canBuy = true;

    	if(choix != "" && choix != "help" && !(std::find(unitNames.begin(),unitNames.end(),choix) != unitNames.end()) && choix != "CANTBUY")
    	    std::cout << "Erreur, choix invalide. Recommencez svp." << std::endl;
    	
    	std::cout << "Quelle unite voulez vous acheter ? Entrez le nom affiche de l'Unite ou son initiale pour la selectionner." << std::endl;
    	std::cout << "Vous pouvez quitter la boutique en appuyant sur ENTER, et entrer 'help' pour afficher la liste des commandes." << std::endl;
    	std::getline(std::cin,choix);

    	if(choix == "")                    
    	    std::cout << "Vous decidez de ne rien acheter." << std::endl;

        else if(choix == "help"){
            std::string commandes = "\n";
            int cout;
            for(unsigned int i = 0; i < unitNames.size(); i++){
                if(i%2 == 0){
                    commandes += "Entrez '";
                    commandes += unitNames[i];
                    commandes += "' ou '";
                    commandes += unitNames[i+1];
                    commandes += "' pour acheter une unite ";
                    commandes += unitNames[i];
                    commandes += " contre ";
                    for(unsigned int j = 0; j < factoryUnits.size(); j++){
                        if(factoryUnits[j]->getName() == unitNames[i]){
                            cout = factoryUnits[j]->getCost();
                            break;
                        }
                    }
                    commandes += std::to_string(cout);
                    commandes += " or.\n";
                }
            } 
            std::cout << commandes << std::endl;
        }   

    	else{
    	    for(unsigned int i = 0; i < unitNames.size(); i++){
        		if(unitNames[i] == choix){
        		    if(i%2 != 0) 
        			   i--; // Car par construction les initiales sont toujours sur les index impairs, et le nom complet est juste avant

        		    for(unsigned int j = 0; j < factoryUnits.size() ; j++){
            			if(factoryUnits[j]->getName() == unitNames[i]){
            			    if(hasEnoughGold(factoryUnits[j]->getCost())){
                				std::cout << "Vous avez achete une Unite " << factoryUnits[j]->getName() << "." << std::endl;
                				this->addUnit(*factoryUnits[j], direction, mapSize);
                				canBuy = false;
            			    }
            			    else{
            			     	std::cout << "Vous n'avez pas assez d'argent pour acheter une Unite " <<  factoryUnits[j]->getName() << ". Veuillez selectionner autre chose ou quitter la boutique." << std::endl;
                                choix = "CANTBUY";
                            }
            			    break;                                
            			}
        		    }
        		    break;
        		}
    	    }
    	}
    // On reste dans la boutique tant qu'aucune selection valide n'a ete rentree, a tester
    }while(choix != "" && !(std::find(unitNames.begin(),unitNames.end(),choix) != unitNames.end()) && canBuy);

    std::cout << "Sortie de la boutique.\n" << std::endl;
}
