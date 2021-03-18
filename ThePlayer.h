


class Player {
private:
	enum Players { PlayerX, PlayerY } thePlayer;
	float Hits;
public:
	// Constructor 
	Player(int temp) {
		// Player based user input
		if (temp == 1) {
			thePlayer = Players::PlayerX;
		}
		else {
			thePlayer = Players::PlayerY;
		}

		// Set Hit to 0;
		Hits = 0;
	}

	// For Cloning object (Deep Copy)
	Player(Player& temp) {
		// Reverse
		if (temp.thePlayer == Players::PlayerX) {
			thePlayer = Players::PlayerY;
		}
		else {
			thePlayer = Players::PlayerX;
		}
		Hits = temp.Hits;
	}

	// Setter
	void SetHits(float a) {
		Hits = a;
	}

	// Getter
	float GetHits() {
		return Hits;
	}
	Players GetPlayers() {
		return thePlayer;
	}
};
