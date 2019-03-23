#include "stdafx.h"
#include <igloo/igloo_alt.h>
#include "Game.h"
#include <string>
#include "TestHelper.h"
using namespace igloo;

Describe(a_game_board)
{
	Game* game;

	void SetUp()
	{
		game = new Game();
		game->NewGame();
	}

	It(should_add_blocks)
	{
		game->AddBoardPiece(2,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
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
		expected += " , ,r, , , , \n"; // 10

		Assert::That(actual, Is().EqualTo(expected));
	}
	
	It(should_find_horizontal_matches)
	{
		game->AddBoardPiece(2,RED);
		game->AddBoardPiece(3,RED);
		game->AddBoardPiece(4,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
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
		expected += " , ,r,r,r, , \n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , , , , , , \n";  // 8
		expected += " , , , , , , \n";  // 9
		expected += " , ,1,1,1, , \n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}

	It(should_not_find_horizontal_matches_when_no_match)
	{
		game->AddBoardPiece(2,RED);
		game->AddBoardPiece(3,RED);
		game->AddBoardPiece(4,BLUE);
		game->AddBoardPiece(5,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
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
		expected += " , ,r,r,b,r, \n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , , , , , , \n";  // 8
		expected += " , , , , , , \n";  // 9
		expected += " , , , , , , \n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}

	It(should_find_vertical_matches)
	{
		game->AddBoardPiece(2,RED);
		game->AddBoardPiece(2,RED);
		game->AddBoardPiece(2,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
		std::string expected = ""; 
		expected += " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,r, , , , \n";  // 8
		expected += " , ,r, , , , \n";  // 9
		expected += " , ,r, , , , \n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,1, , , , \n";  // 8
		expected += " , ,1, , , , \n";  // 9
		expected += " , ,1, , , , \n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}


	It(should_find_Diagonal_Down_Right_matches)
	{
		game->AddBoardPiece(2,BLUE);
		game->AddBoardPiece(2,BLUE);
		game->AddBoardPiece(2,RED);

		game->AddBoardPiece(3,BLUE);
		game->AddBoardPiece(3,RED);

		game->AddBoardPiece(4,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
		std::string expected = ""; 
		expected += " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,r, , , , \n";  // 8
		expected += " , ,b,r, , , \n";  // 9
		expected += " , ,b,b,r, , \n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,1, , , , \n";  // 8
		expected += " , , ,1, , , \n";  // 9
		expected += " , , , ,1, , \n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}

	It(should_find_Diagonal_Down_Left_matches)
	{
		game->AddBoardPiece(2,BLUE);
		game->AddBoardPiece(2,BLUE);
		game->AddBoardPiece(2,RED);

		game->AddBoardPiece(1,BLUE);
		game->AddBoardPiece(1,RED);

		game->AddBoardPiece(0,RED);

		std::string actual = Helper::BoardToString(game->GetBoard());
		
		std::string expected = ""; 
		expected += " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,r, , , , \n";  // 8
		expected += " ,r,b, , , , \n";  // 9
		expected += "r,b,b, , , , \n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , ,1, , , , \n";  // 8
		expected += " ,1, , , , , \n";  // 9
		expected += "1, , , , , , \n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}


	It(should_find_matches_at_right_edge)
	{
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);


		std::string actual = Helper::BoardToString(game->GetBoard());
		
		std::string expected = ""; 
		expected += " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , , , , , ,r\n";  // 8
		expected += " , , , , , ,r\n";  // 9
		expected += " , , , , , ,r\n";  // 10

		game->FindMatches();
		Assert::That(actual, Is().EqualTo(expected));

		expected  = " , , , , , , \n";  // 0
		expected += " , , , , , , \n";  // 1
		expected += " , , , , , , \n";  // 2
		expected += " , , , , , , \n";  // 3
		expected += " , , , , , , \n";  // 4
		expected += " , , , , , , \n";  // 5
		expected += " , , , , , , \n";  // 6
		expected += " , , , , , , \n";  // 7
		expected += " , , , , , ,1\n";  // 8
		expected += " , , , , , ,1\n";  // 9
		expected += " , , , , , ,1\n";  // 10
		
		actual = Helper::BoardMatchesToString(game->GetBoard());
		Assert::That(actual, Is().EqualTo(expected));
	}

	It(orphaned_block_should_land_on_bottom)
	{
		game->NewGame();

		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,BLUE);
		
		game->FindMatches();
		game->RemoveMatchedBlocks();

		Assert::That(game->HasOrphaned(), Is().True());

		game->ProcessOrphaned();
		game->ProcessOrphaned();
		game->ProcessOrphaned();
		game->ProcessOrphaned();

		std::string actual = Helper::BoardToString(game->GetBoard());
		
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
		expected += " , , , , , ,b\n";  // 10

		Assert::That(actual, Is().EqualTo(expected));
	}

	It(orphaned_block_should_land_ontop_of_other_blocks)
	{
		game->NewGame();

		game->AddBoardPiece(6,GREEN);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,RED);
		game->AddBoardPiece(6,BLUE);
		
		game->FindMatches();
		game->RemoveMatchedBlocks();

		Assert::That(game->HasOrphaned(), Is().True());

		game->ProcessOrphaned();
		game->ProcessOrphaned();
		game->ProcessOrphaned();
		game->ProcessOrphaned();

		std::string actual = Helper::BoardToString(game->GetBoard());
		
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
		expected += " , , , , , ,b\n";  // 9
		expected += " , , , , , ,g\n";  // 10

		Assert::That(actual, Is().EqualTo(expected));
	}
};