#include "..\Block.h"
#include "..\Player.h"
#include "..\AIPlayer.h"

#include <string>

using namespace game;

namespace TestHelper{
	char block_type_to_char(const BlockType& type);
	std::string BoardToString(const Board* board);
	std::string BoardMatchesToString(const Board* board);
	void GenerateBoardFromString(std::string* input, Board* board);
	void GeneratePlayerFromString(std::string* input, Player* p);

	void GeneratePlayerFromString(const char* input, Player* p);

	void RotatePlayerAndGetPlayerAsString(CAIPlayer* ai, std::string* output);

};