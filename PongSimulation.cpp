#include <iostream> // cout; cin 
#include <thread> // Thread
#include <stdlib.h> // srand, rand
#include <time.h> // time
#include <random> // random
#include <mutex> // mutex
#include "TheScore.h" // Score class
#include "ThePlayer.h" // Player class

// 4210191011     M. Alifian

// Create score instance as global variable
Score score(0, 0);

// For lock so inaccessible to another thread 
std::mutex m;

// Random Hits
void RandomizePlayerHits(Player* thePlayer, bool* isOver) {
	// For randomize using address as seed
	m.lock();
	int* temp = new int;
	srand((int)temp);
	delete temp;
	//  Randomize Player.Hits from 0 to 100
	thePlayer->SetHits(rand() % 101);
	m.unlock();
	
	// For UI
	std::cout << " Hits Value : " << thePlayer->GetHits() << " # ";
	if (thePlayer->GetPlayers() == 0) {
		std::cout << " Player X ";
	}
	else {
		std::cout << " Player Y ";
	}

	// Miss pong
	if(thePlayer->GetHits() <= 50) {
		// Update score + 1 to opponent score
		if (thePlayer->GetPlayers() == 0) {
			score.AddYScore();
		}
		else {
			score.AddXScore();
		}
		std::cout << "Miss\n";

		// End of the round
		*isOver = true;
	}
	// Hit pong
	else {
		std::cout << "Hit\n";
	}

	// Slow down proccess
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
}

// Help randomize First Turn
void randomFirstTurn(int* alpha) {
	int* temp = new int;
	srand((int)temp);
	delete temp;
	*alpha = rand() % 2;
}

int main()
{
	// For randomize
	srand(time(0));
	
	// Create player instance once
	Player playerX(1);

	// Clone previous player to new player (Deep Copy)
	Player playerY = playerX; 


	int roundCount = 1;
	// Simulation flow (Main Loop)
	while (score.GetXScore() < 10 && score.GetYScore() < 10) {
		// Start from random player, player X or player Y
		int randomStart;
		std::thread randomFirst(randomFirstTurn, &randomStart);
		randomFirst.join();
		bool roundIsOver = false;
		
		// For UI
		std::cout << "\nRound " << roundCount << "\n";
		// Rounds Loop
		while (roundIsOver == false) {
			if (randomStart == 0) { // Player X first
				// For UI
				std::cout << "Start From Player X\n";
				
				// Player x Thread 
				std::thread playerXThread(RandomizePlayerHits, &playerX, &roundIsOver);
				playerXThread.join();

				// Check miss or not
				if (roundIsOver == true) {
					roundCount++;
					break;
				}			
				
				// Player Y Thread
				std::thread playerYThread(RandomizePlayerHits, &playerY, &roundIsOver);
				playerYThread.join();

				// Check miss or not
				if (roundIsOver == true) {
					roundCount++;
					break;
				}
			}
			else if (randomStart == 1) { // Player Y first
				// For UI
				std::cout << "Start From Player Y\n";

				// Player Y Thread
				std::thread playerYThread(RandomizePlayerHits, &playerY, &roundIsOver);
				playerYThread.join();
				
				// Check miss or not
				if (roundIsOver == true) {
					roundCount++;
					break;
				}

				// Player X Thread
				std::thread playerXThread(RandomizePlayerHits, &playerX, &roundIsOver);
				playerXThread.join();

				// Check miss or not
				if (roundIsOver == true) {
					roundCount++;
					break;
				}
			}
		}
	}

	// Show the final score at the end of the game
	if (score.GetXScore() >= 10) {
		std::cout << "\nPlayer X win  " << score.GetXScore() << "-" << score.GetYScore();
	}
	else {
		std::cout << "\nPlayer Y win  " << score.GetYScore() << "-" << score.GetXScore();
	}
	std::cout << "\n";

	return 0;
}