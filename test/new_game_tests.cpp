#include <igloo/igloo_alt.h>
#include "Game.h"
#include <string>
#include "TestHelper.h"
using namespace igloo;

Describe(a_new_game)
{

	Game game;

	void SetUp()
	{
		game.NewGame();
	}

	It(should_start_with_an_empty_board)
	{
		std::string actual = Helper::BoardToString(game.GetBoard());
		
		std::string expected = ""; 
		expected += " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , , , , , , \n";  // 8
		expected += " , , , , , , \n";  // 9
		expected += " , , , , , , \n"; // 10

		Assert::That(actual, Is().EqualTo(expected));
	}

	It(should_start_with_a_score_of_zero)
	{
		Assert::That(game.GetScore(), Is().EqualTo(0));
	}

	It(should_start_at_level_1)
	{
		Assert::That(game.GetLevel(), Is().EqualTo(1));
	}

	It(should_have_a_valid_current_block)
	{
		Player* player = game.GetPlayer();
		const PlayerBlock* item = player->get_blocks();
		char actual = Helper::block_type_to_char(item->bottom);
		Assert::That("rbobyp", Is().Containing(actual));
	}

	It(should_have_a_valid_next_block)
	{
		const PlayerBlock& item = game.GetNext();
		char actual = Helper::block_type_to_char(item.bottom);
		Assert::That("rbobyp", Is().Containing(actual));
	}
	
	It(should_start_the_player_at_the_top_middle_of_the_board)
	{
		Player* player = game.GetPlayer();
		int x_pos = player->getX();
		Assert::That(x_pos, Is().EqualTo(3));
	}

};