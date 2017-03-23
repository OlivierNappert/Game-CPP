#include "../include/Phase.hpp"
#include "../include/Unit.hpp"

std::string Phase::getNameByPos(Player& player1, Player& player2, const int pos)
{
   std::vector<Unit*> player1Units = player1.getUnits();
   std::vector<Unit*> player2Units = player2.getUnits();
   std::string res;
   int i = 0;

   for(std::vector<Unit*>::const_iterator it = player1Units.begin(); it != player1Units.end(); ++it)
   {
      if((*it)->getPos() == pos)
      {
	 res = (*it)->getName().substr(0, WIDTH - 1);//on coupe le nom s'il est trop long
	 while(res.size() < (WIDTH - 1))
	 {
	   if(i % 2 == 0)
	     res.insert(0, 1, ' ');//si i est pair, on ajoute un espace au debut du nom
	   else
	     res.insert(res.size(), 1, ' ');//sinon on ajoute un espace a la fin
	   i++;
	 }
	   return res;
      }
   }

   for(std::vector<Unit*>::const_iterator it = player2Units.begin(); it != player2Units.end(); ++it)
   {
      if((*it)->getPos() == pos)
      {
	res = (*it)->getName().substr(0, WIDTH - 1);
	while(res.size() < (WIDTH - 1))
	{
	  if(i % 2 == 0)
	    res.insert(0, 1, ' ');//si i est pair, on ajoute un espace au debut du nom
	  else
	    res.insert(res.size(), 1, ' ');//sinon on ajoute un espace a la fin
	  i++;
	}
      return res;
      }
   }

   //si on ne trouve pas d'unite a cette position, on renvoie une chaine de WIDTH espaces
   res = "";
   for(int i = 0; i < WIDTH - 1; i++)
      res += " ";

   return res;
}

int Phase::getHpByPos(Player& player1, Player& player2, const int pos)
{
   std::vector<Unit*> player1Units = player1.getUnits();
   std::vector<Unit*> player2Units = player2.getUnits();

   for(std::vector<Unit*>::const_iterator it = player1Units.begin(); it != player1Units.end(); ++it)
   {
      if((*it)->getPos() == pos)
	 return (*it)->getHp();
   }

   for(std::vector<Unit*>::const_iterator it = player2Units.begin(); it != player2Units.end(); ++it)
   {
      if((*it)->getPos() == pos)
	 return (*it)->getHp();
   }

   //si on ne trouve pas d'unite a cette position, on renvoie 0 (une unite qui a 0 hp sera retiree du vector)
   return 0;
}

int Phase::getPlayerByPos(Player& player1, Player& player2, const int pos, const int direction)
{
  std::vector<Unit*> player1Units = player1.getUnits();//unites du joueur qui joue
  std::vector<Unit*> player2Units = player2.getUnits();//unites du joueur qui ne joue pas

  for(std::vector<Unit*>::const_iterator it = player1Units.begin(); it != player1Units.end(); ++it)
  {
    if((*it)->getPos() == pos)
      return direction == -1 ? 1 : 2;
  }

  for(std::vector<Unit*>::const_iterator it = player2Units.begin(); it != player2Units.end(); ++it)
  {
    if((*it)->getPos() == pos)
      return direction == -1 ? 2 : 1;
  }

  return 0;//on retourne 0 si aucune unite n'a ete trouvee a cette position
}

int Phase::getNumberOfDigits(int n)
{
   int digits = 0;

   do
   {
      n /= 10;
      digits++;
   } while(n != 0);

   return digits;
}

void Phase::renderMap(Player& playing, Player& notPlaying, const int mapSize, const int phaseNb, const int direction, const int turn)
{
   std::system(CLEAR);//on commence par clear la console

   std::stringstream output;
   int player1Hp, player1Golds, player2Hp, player2Golds;

   std::ofstream outFile;
   outFile.open("logs.txt", std::ios_base::app);

   //on commence par afficher le numero du tour
   output << "Tour numero : " << turn << "\n";

   //on affiche le joueur qui joue
   if(direction == -1)
     output << "Joueur actif : Player 1";
   else
     output << "Joueur actif : Player 2";

   output << "\n";

   //on affiche le numero de la phase
   output << "Phase : " << phaseNb << "\n";

   //puis on affiche la ligne contenant le nom des joueurs
   //on veut ajouter une nombre d'espace qui correspond a
   //2 fois la largeur d'une case - le nombre de caracteres de "Player 1" (8)
   //+ le nombre d'espaces
   output << "Player 1";
   for(int i = 0; i < (2 * (WIDTH - 8) + ((mapSize - 2) * WIDTH) + 1); i++)
      output << " ";

   output << "Player 2\n";

   //puis on affiche le haut de la map
   for(int i = 0; i < (mapSize * WIDTH) + 1; i++)
   {
      if(i == 0)
	 output << TLCORNER;
      else if(i == mapSize * WIDTH)
	 output << TRCORNER;
      else if(i % WIDTH == 0)
	 output << TOPCROSS;
      else
	 output << HORIZONTAL;
   }

   output << "\n";
   
   //puis on affiche la ligne inferieure, vide
   for(int i = 0; i < (mapSize * WIDTH) + 1; i++)
   {
      if(i % WIDTH == 0)
	 output << VERTICAL;
      else
	 output << " ";
   }

   output << "\n";

   //puis on affiche la ligne contenant le nom des unites
   for(int i = 0; i < mapSize; i++)
   {
      if(i == 0)
	 output << VERTICAL;
     
      output << getNameByPos(playing, notPlaying, i) << VERTICAL;
   }

   output << "\n";

   //puis on affiche la ligne contenant les hp des unites
   for(int i = 0; i < mapSize; i++)
   {
      if(i == 0)
	 output << VERTICAL;

      int hp = getHpByPos(playing, notPlaying, i);
      if(hp > 0){
        if(getNumberOfDigits(hp) == 2)
          output << "   hp:" << hp << VERTICAL;
        else
          output << "   hp: " << hp << VERTICAL;
      }
	   
      else
      {
	for(int i = 0; i < WIDTH - 1; i++)
	  output << " ";

	output << VERTICAL;
      }
   }

   output << "\n";

   //puis on affiche la ligne inferieure contenant le numero du joueur a qui appartient l'unite
   for(int i = 0; i < mapSize; i++)
   {
      if(i == 0)
	 output << VERTICAL;
      
      int playerIndex = getPlayerByPos(playing, notPlaying, i, direction);
      if(playerIndex != 0)
	output << "player:" << playerIndex;
      else
	for(int j = 0; j < (WIDTH - 1); j++)
	  output << " ";

      output << VERTICAL;
   }

   output << "\n";

   //puis on affiche le bas de la map
   for(int i = 0; i < (mapSize * WIDTH) + 1; i++)
   {
      if(i == 0)
	 output << BLCORNER;
      else if(i == mapSize * WIDTH)
	 output << BRCORNER;
      else if(i % WIDTH == 0)
	 output << BOTCROSS;
      else
	 output << HORIZONTAL;
   }

   output << "\n";

   if(direction == -1)
   {
      //joueur actif = joueur de gauche
      player1Hp = playing.getHp();
      player1Golds = playing.getGold();
      player2Hp = notPlaying.getHp();
      player2Golds = notPlaying.getGold();
   }
   else
   {
      //joueur actif = joueur de droite
      player1Hp = notPlaying.getHp();
      player1Golds = notPlaying.getGold();
      player2Hp = playing.getHp();
      player2Golds = playing.getGold();
   }

   output << "hp:" << player1Hp;
   for(int i = 0; i < ((2 * (WIDTH - 3) + ((mapSize - 2) * WIDTH) + 1) - (getNumberOfDigits(player1Hp) + getNumberOfDigits(player2Hp))); i++)
      output << " ";

   output << "hp:" << player2Hp;

   output << "\n";

   //puis on affiche les golds des joueurs
   output << "golds:" << player1Golds;
   for(int i = 0; i < ((2 * (WIDTH - 6) + ((mapSize - 2) * WIDTH) + 1) - (getNumberOfDigits(player1Golds) + getNumberOfDigits(player2Golds))); i++)
      output << " ";

   output << "golds:" << player2Golds << "\n";

   output << "\n";

   //on affiche le resultat dans la console et dans le fichier
   if(outFile)
      outFile << output.str();

   std::cout << output.rdbuf();

   outFile.close();

   std::string press;
   std::cout << ">>> Press ENTER to continue <<<" << std::endl;
   std::getline(std::cin, press);
}

int Phase::closestObstacle(std::vector<Unit*> playingUnits, std::vector<Unit*> notPlayingUnits, int direction, unsigned int index, int mapSize){
        int obstaclePos;
        if(direction == -1){
	    //cas du joueur de gauche
            if(index != playingUnits.size()-1)
	        //si l'unite qui se deplace n'est pas la plus eloignee de la base du joueur
		//gauche, alors on renvoie la position de la prochaine unite dans le
		//vecteur d'unite du joueur
                obstaclePos = playingUnits[index+1]->getPos();
            else if(notPlayingUnits.size() > 0)
	        //sinon si le joueur adverse a des unites, on renvoie la position de la
		//premiere unite de son vecteur (celle qui est la plus proche du joueur
		//de gauche
                obstaclePos = notPlayingUnits[0]->getPos();
            else
	        //sinon on renvoie la position de la derniere case de la map
                obstaclePos = mapSize-1;
        }
        
        else{
	    //pour l'autre joueur, on fait la meme chose dans l'autre sens
            if(index != 0)
                obstaclePos = playingUnits[index-1]->getPos();
            else if(notPlayingUnits.size() > 0)
                obstaclePos = notPlayingUnits[notPlayingUnits.size()-1]->getPos();
            else
                obstaclePos = 0;
        }
        return obstaclePos;
}

std::vector<Unit*> Phase::getTargets(std::vector<Unit*> playingUnits, std::vector<Unit*> notPlayingUnits,
    const int direction, const unsigned int index, const int mapSize, bool* attackPlayerP){ // bool attackPlayer
    std::vector<Unit*> targets;
    Range range = playingUnits[index]->getRange();
    int unitPos = playingUnits[index]->getPos();
    int r = 0;
    bool found = false;

    if(direction == -1){
        unsigned int k;
        // On cherche un ennemi vivant dans la range de l'unite
        for(int i = unitPos+1; i <= mapSize-1 && range.rangeMin + r <= (range.rangeMax + range.aoe -1) &&!found; i++, r++){
            for(k = 0; k < notPlayingUnits.size(); k++){
              if(notPlayingUnits[k]->getPos() == unitPos + range.rangeMin + r && notPlayingUnits[k]->getHp() > 0){
                // Si on en trouve un et que l'unite n'attaque pas en zone ( une seule cible ), ajouter seulement cet ennemi
                targets.push_back(notPlayingUnits[k]);
                // Sinon, ajouter toutes les unites dans la zone d'effet
                if(range.aoe > 1){

                    // Si on a pas atteint la portee maximale, l'AOE ne peut toucher que des ennemis
                    if(range.rangeMin + r < range.rangeMax + range.aoe-1){
                      for(unsigned int j = k+1; j < notPlayingUnits.size(); j++){
                        if(notPlayingUnits[j]->getPos() <= notPlayingUnits[k]->getPos() + (range.aoe-1) && notPlayingUnits[j]->getHp() > 0)
                            targets.push_back(notPlayingUnits[j]);
                      }
                    }

                    // Sinon on peut aussi toucher des allies
                    else{
                      for(unsigned int j = index+1; j < playingUnits.size(); j++){
                        if(playingUnits[j]->getPos() >= notPlayingUnits[k]->getPos() - (range.aoe-1))
                            targets.push_back(playingUnits[j]);
                      }
                    }
                }
                found = true;
                break;
              }
            }
        }

        if(playingUnits[index]->getPa() == 0 || !playingUnits[index]->playerInRange(direction,mapSize))
          *attackPlayerP = false;

        // Si le joueur ennemi est a porte et qu'il n'y a pas d'unites ennemie en jeu, on l'attaque
        else if(notPlayingUnits.size() == 0)
          *attackPlayerP = true;
        
        // Si il y'a des unites en face et que l'unite qui attaque n'a pas d'AOE, on attaque en priorite les unites ennemies
        else if(range.aoe == 1)
          *attackPlayerP = false;

        // Le joueur est a porte, il y'a des unites ennemies en face et on peut attaquer en AOE
        else if(notPlayingUnits[notPlayingUnits.size()-1]->getPos() != mapSize-1 && notPlayingUnits[k]->getPos() + (range.aoe-1) >= mapSize-1)
          *attackPlayerP = true;

        else
          *attackPlayerP = false;
    }
    
    else{
        // On cherche un ennemi vivant dans la range de l'unite
        unsigned int k;
        for(int i = unitPos-1; i >= 0 && range.rangeMin + r <= (range.rangeMax + range.aoe-1) && !found; i--, r++){
          for(k = 0; k < notPlayingUnits.size(); k++){
            if(notPlayingUnits[k]->getPos() == unitPos - (range.rangeMin + r) && notPlayingUnits[k]->getHp() > 0){
                // Si il existe et que l'aoe de l'attaquant est nul ( une seule cible ), ajouter seulement cette unite
                targets.push_back(notPlayingUnits[k]);
                // Sinon, ajouter toutes les unites dans la zone d'effet
                if(range.aoe > 1){

                  // Si on a pas atteint la portee maximale, l'AOE ne peut toucher que des ennemis
                  if(range.rangeMin + r < range.rangeMax + range.aoe-1){
                    for(unsigned int j = k+1; j < notPlayingUnits.size(); j++){
                      if(notPlayingUnits[j]->getHp() > 0 && notPlayingUnits[j]->getPos() >= notPlayingUnits[k]->getPos() - (range.aoe-1))
                          targets.push_back(notPlayingUnits[j]);
                    }
                  }

                  // Sinon on peut aussi toucher des allies
                  else{
                    for(int j = index-1; j >= 0; j--){
                      if(playingUnits[j]->getPos() >= notPlayingUnits[k]->getPos() - (range.aoe-1))
                          targets.push_back(playingUnits[j]);
                    }
                  } 
                }
              found = true;
              break; 
            }
          }
        }
        
        if(playingUnits[index]->getPa() == 0 || !playingUnits[index]->playerInRange(direction,mapSize))
          *attackPlayerP = false;

        // Si le joueur ennemi est a porte et qu'il n'y a pas d'unites ennemie en jeu, on l'attaque
        else if(notPlayingUnits.size() == 0)
          *attackPlayerP = true;
        
        // Si il y'a des unites en face et que l'unite qui attaque n'a pas d'AOE, on attaque en priorite les unites ennemies
        else if(range.aoe == 1)
          *attackPlayerP = false;

        // Le joueur est a porte, il y'a des unites ennemies en face et on peut attaquer en AOE
        else if(notPlayingUnits[0]->getPos() != 0 && notPlayingUnits[k]->getPos() - (range.aoe-1) <= 0)
          *attackPlayerP = true;

        else
          *attackPlayerP = false;
    }
    
    if(*attackPlayerP == true)
      playingUnits[index]->minPa();

    return targets;
}

void Phase::phase1(Player& playing, Player& notPlaying, const int direction, const int mapSize){
    std::vector<Unit*> playingUnits = playing.getUnits();
    std::vector<Unit*> notPlayingUnits = notPlaying.getUnits();
    std::sort(playingUnits.begin(),playingUnits.end(),sortByPosition);
    std::sort(notPlayingUnits.begin(),notPlayingUnits.end(),sortByPosition);
    bool attackPlayer = false;
    bool* attackPlayerP = &attackPlayer;

    if(direction == -1){ 
        for(unsigned int i = 0; i < playingUnits.size(); i++){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action1()){
                case IDLE:
                    break;
                case MOVE:            
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());
                    break;
            }
            cleanUnits(playing,notPlaying);
          }
        }
    }
    
    else{
        for(int i = playingUnits.size()-1; i >= 0 ;i--){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action1()){
                case IDLE:
                    break;
                case MOVE:
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());
                    break;
            }
            cleanUnits(playing,notPlaying);
          }
        }
    }
}

void Phase::phase2(Player& playing, Player& notPlaying, const int direction, const int mapSize){
    std::vector<Unit*> playingUnits = playing.getUnits();
    std::vector<Unit*> notPlayingUnits = notPlaying.getUnits();
    std::sort(playingUnits.begin(),playingUnits.end(),sortByPosition);
    std::sort(notPlayingUnits.begin(),notPlayingUnits.end(),sortByPosition);
    bool attackPlayer = false;
    bool* attackPlayerP = &attackPlayer;

    if(direction == -1){ 
        for(int i = playingUnits.size()-1; i >= 0; i--){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action2()){
                case IDLE:
                    break;
                case MOVE:            
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());
                    break;
            }
            cleanUnits(playing,notPlaying);
          }
        }
    }
    
    else{
        for(unsigned int i = 0; i < playingUnits.size() ;i++){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action2()){
                case IDLE:
                    break;
                case MOVE:
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());
                    break;
            }
            cleanUnits(playing,notPlaying);
          }
        }
    }
}

void Phase::phase3(Player& playing, Player& notPlaying, const int direction, const int mapSize){
    std::vector<Unit*> playingUnits = playing.getUnits();
    std::vector<Unit*> notPlayingUnits = notPlaying.getUnits();
    std::sort(playingUnits.begin(),playingUnits.end(),sortByPosition);
    std::sort(notPlayingUnits.begin(),notPlayingUnits.end(),sortByPosition);
    bool attackPlayer = false;
    bool* attackPlayerP = &attackPlayer;

    if(direction == -1){ 
        for(int i = playingUnits.size()-1; i >= 0; i--){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action3()){
                case IDLE:
                    break;
                case MOVE:            
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());

                    cleanUnits(playing,notPlaying);
                    break;
            }
          }
        }
    }
    
    else{
        for(unsigned int i = 0; i < playingUnits.size() ;i++){
          if(playingUnits[i]->getHp() > 0){
            switch(playingUnits[i]->action3()){
                case IDLE:
                    break;
                case MOVE:
                    playingUnits[i]->move(closestObstacle(playingUnits,notPlayingUnits,direction,i,mapSize),direction);
                    break;
                case ATTACK:
                    playingUnits[i]->attack(getTargets(playingUnits,notPlayingUnits,direction,i,mapSize,attackPlayerP),direction,mapSize);
                    if(attackPlayer)
                      notPlaying.takeDamage(playingUnits[i]->getAttackValue());

                    cleanUnits(playing,notPlaying);
                    break;
            }
          }
        }
    }
}

void Phase::cleanUnits(Player& playing, Player& notPlaying){
    notPlaying.addGold(playing.killUnits());
    playing.addGold(notPlaying.killUnits());
} 

bool Phase::checkWin(Player& player){
    return player.getHp() <= 0 ? true : false;
}

bool Phase::sortByPosition(Unit* unit1, Unit* unit2){
    return (unit1->getPos() < unit2->getPos());
}
