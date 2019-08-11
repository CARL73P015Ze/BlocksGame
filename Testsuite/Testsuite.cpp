// Testsuite.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <igloo/igloo_alt.h>

#include "..\Block.h"
#include "TestHelper.h"

#include "..\AIPlayer.h"

using namespace igloo;

using namespace TestHelper;
using namespace game;

Describe(a_new_game)
{

	//Game game;
	

	void SetUp()
	{
//		game.NewGame();
	}

	
	It(can_create_board_from_string)
	{
		Board board;
//		initBoard(&board);
		std::string 
		input =  "0100000";
		input += "0100000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0012000";
		input += "0554000";
		input += "0155000";
		input += "0331000";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		std::string output = BoardToString(&board);

		Assert::That(input, Is().EqualTo(output));
	}


	It(can_work_out_best_place_for_player)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0012000";
		input += "0554000";
		input += "0155000";
		input += "0331000";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 3;
		player.Blocks.middle = (BlockType)4;
		player.Blocks.bottom = (BlockType)4;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(0));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(1));
	
	}
	
	It(left_bit)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0030330";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 3;
		player.Blocks.middle = (BlockType)4;
		player.Blocks.bottom = (BlockType)4;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(3));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(1));
	}


	It(diag_down_right)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0030000";
		input += "0020000";
		input += "0010300";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 4;
		player.Blocks.middle = (BlockType)3;
		player.Blocks.bottom = (BlockType)4;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(3));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(0));
	}

	

	It(diag_up_right)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000300";
		input += "0000200";
		input += "0030100";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 5;
		player.Blocks.middle = (BlockType)6;
		player.Blocks.bottom = (BlockType)3;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(3));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(1));
	}


	It(verticle)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0030000";
		input += "0030000";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 5;
		player.Blocks.middle = (BlockType)6;
		player.Blocks.bottom = (BlockType)3;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(2));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(0));
	}
	

	It(verticlsesd)
	{
		Board board;
	//	initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000002";
		input += "0000003";
		input += "0000043";
		input += "0000024";
		input += "0000013";
		input += "0000015";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 2;
		player.Blocks.middle = (BlockType)3;
		player.Blocks.bottom = (BlockType)2;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(6));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(1));
	}

		//GivenTheBoard();
		//GivenThePlayer()
		// WhenAiCalulatesTheMove();

		// Then


	It(verticlsesd1)
	{
		Board board;
		Player player;
		CAIPlayer ai(&player);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "3000000";
		input += "2000000";
		input += "2000000";
		TestHelper::GenerateBoardFromString(&input, &board);
		TestHelper::GeneratePlayerFromString("123", &player);
		

		ai.CalculateMove(&board);

		
		Assert::That(ai.GetTargetX(), Is().EqualTo(1), "Wrong column", __LINE__);

		
		std::string strPlayer = "";
		TestHelper::RotatePlayerAndGetPlayerAsString(&ai, &strPlayer);

		Assert::That(strPlayer, Is().EqualTo("312"), "Player Blocks Wrong order", __LINE__);
	}

	
	
	It(verticlsesd2)
	{
		Board board;
		Player player;
		CAIPlayer ai(&player);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "2000000";
		input += "2000000";
		input += "3000000";
		TestHelper::GenerateBoardFromString(&input, &board);
		TestHelper::GeneratePlayerFromString("123", &player);
		

		ai.CalculateMove(&board);

		
		Assert::That(ai.GetTargetX(), Is().EqualTo(0), "Wrong column", __LINE__);

		
		std::string strPlayer = "";
		TestHelper::RotatePlayerAndGetPlayerAsString(&ai, &strPlayer);

		Assert::That(strPlayer, Is().EqualTo("312"), "Player Blocks Wrong order", __LINE__);
	}
	








	/*
2
5
1
000000
000000
000000
000000
000003
000001
000002
000004
300001
410544
544121
	*/



	It(CalculatesABetterRanking)
	{
		ColRanking best_rank;


		best_rank.col = 1;
		best_rank.y = 2;
		for(int i=0; i < BLOCKS_MATCHED_SIZE+1; i++)
			best_rank.blocks_matched[i] = 0;




		ColRanking ranking;


		ranking.col = 1;
		ranking.y = 2;
		for(int i=0; i < BLOCKS_MATCHED_SIZE+1; i++)
			ranking.blocks_matched[i] = 0;

		best_rank.blocks_matched[1] = 10;
		ranking.blocks_matched[3] = 1;



		AssignIfBetterRanking(&ranking, &best_rank);

		Assert::That(best_rank.col, Is().EqualTo(ranking.col));
	}
	
	/*
1
2
3


3
1
2

2
3
1
000000
000000
000000
000000
000000
000000
000000
000000
200000
200000
300000
*/


	/*
	It(priority_should_be_twoX3_not_oneX4)
	{
		Board board;
		initBoard(&board);
		std::string 
		input =  "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "0000000";
		input += "1010000";
		input += "1010303";
		TestHelper::GenerateBoardFromString(&input, &board);
		
		Player player;
		player.Blocks.top = (BlockType) 1;
		player.Blocks.middle = (BlockType)1;
		player.Blocks.bottom = (BlockType)3;
		CAIPlayer ai(&player);

		ai.CalculateMove(&board);
		//ai.GetTargetRotation();
		int x = ai.GetTargetX();
		Assert::That(x, Is().EqualTo(1));
		int r = ai.GetTargetRotation();
		Assert::That(r, Is().EqualTo(1));
		
	}
	*/
	
};





int _tmain(int argc, _TCHAR* argv[])
{
	//can_create_board_from_string();
	return TestRunner::RunAllTests(argc, argv);
	//return 0;
}

