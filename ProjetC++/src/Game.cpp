#include <iostream>
#include "../include/Game.hpp"

Game::~Game(){
    for(unsigned int i = 0; i < players.size(); i++)
        players[i]->getUnits().clear();

    players.clear();
    factoryUnits.clear();
}

void Game::run()
{

    bool win = false, exit = false;
    int turn = 1;

    // On trie les unites factory par prix dans le doute, pour avoir Soldat - Archer - Catapult
    std::sort(factoryUnits.begin(), factoryUnits.end(), sortByPrice);

    std::cout << "\nLe jeu demarre !\n" << std::endl;
    
    do{
        int direction = 0;
        int other = 0;
        for(unsigned int i = 0; i < players.size() && !win; i++){
            std::cout << "Au tour du joueur " << i+1 << " de jouer.\n" << std::endl;
            i == 0 ? direction = -1 : direction = 1;
            i == 0 ? other = 1 : other = -1;
          
            giveGolds(*players[i]);
            phase.phase1(*players[i],*players[i+other],direction,mapSize);
            phase.renderMap(*players[i],*players[i+other],mapSize,1,direction, turn);
            phase.phase2(*players[i],*players[i+other],direction,mapSize);
            phase.renderMap(*players[i],*players[i+other],mapSize,2,direction, turn);
            phase.phase3(*players[i],*players[i+other],direction,mapSize);
            phase.renderMap(*players[i],*players[i+other],mapSize,3,direction, turn);
            win = phase.checkWin(*players[i+other]);
            if(win)
                break;

            // phase.renderShop();
            players[i]->shop(factoryUnits,direction,mapSize);
        }

	turn++;

        refreshUnits();

    }while(!win && !exit && turn < 50);

    unsigned int index;
    bool winner = false;
    for(index = 0; index < players.size(); index++){
        if(players[index]->getHp() <= 0){
            winner = true;
            break;
        }
    }

    if(winner){
         if(index == 0) index = 1;
         else index = 0;
         std::cout << "Bravo, le Joueur " << index+1 << " a remporte la victoire avec " << players[index]->getHp() << " points de vie !" << std::endl;
    }

    else{
        std::cout << turn << " tours se sont ecoules, il n'y a pas de gagnant !" << std::endl;
    }
    std::cout << "C'est la fin du jeu, merci d'y avoir joue !" << std::endl;
}

bool Game::sortByPrice(Unit* unit1, Unit* unit2)
{
    return (unit1->getCost()< unit2->getCost());
}

void Game::giveGolds(Player& playing)
{
    playing.addGold(goldPerTurn);
}

void Game::refreshUnits(){
    for(unsigned int i = 0; i < players.size(); i++){
        std::vector<Unit*> playerUnits = players[i]->getUnits();
        for(unsigned int j = 0; j < playerUnits.size(); j++)
            playerUnits[j]->refresh();
    }
}
