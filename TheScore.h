
// Class of score
class Score {
private:
	int PlayerXScore;
	int PlayerYScore;
public:
	// Constructor
	Score(int x, int y) {
		PlayerXScore = x;
		PlayerYScore = y;
	}
	
	// Setter
	void SetScore(int x, int y) {
		PlayerXScore = x;
		PlayerYScore = y;
	}

	// Getter
	int GetXScore() {
		return PlayerXScore;
	}
	int GetYScore() {
		return PlayerYScore;
	}

	// Add PlayerXScore by 1
	void AddXScore() {
		PlayerXScore++;
	}

	// Add PlayerYScore by 1
	void AddYScore() {
		PlayerYScore++;
	}
};
