#ifndef CA_UWATERLOO_ALUMNI_DWHARDER_MAZE_GENERATION
#define CA_UWATERLOO_ALUMNI_DWHARDER_MAZE_GENERATION

#include <cassert>
#include <ostream>
#include "Disjoint_sets.h"
using Data_structures::Disjoint_sets;
#include "Permutation.h"
using Data_structures::Permutation;

// Author:  Douglas Wilhelm Harder
// Copyright (c) 2009 by Douglas Wilhelm Harder.  All rights reserved.

namespace Data_structures {
	/****************************************************
	 * ************************************************ *
	 * *                Maze Generation               * *
	 * ************************************************ *
	 ****************************************************/

	/*
	 * There are a total of 2mn - m - n walls.  They are numbered from
	 * from 0 to 2*m*n - m - n - 1 from top to bottom and left to right.
	 *
	 *     m rows
	 *
	 *        0      | | | | | | | | | |        n - 1 vertical walls
	 *              - - - - - - - - - - -       n   horiztonal walls
	 *
	 *        1      | | | | | | | | | |
	 *              - - - - - - - - - - -
	 *
	 *        2      | | | | | | | | | |
	 *              - - - - - - - - - - -
	 *
	 *      m - 1    | | | | | | | | | |        n - 1 vertical walls
	 *
	 *  The algorithm is as follows:
	 *     Each room is placed in its own disjoint set.
	 *     A wall is picked at random and if the two adjacent rooms
	 *     are in different sets, we remove the wall.
	 *     Continue with this algorithm until there is only one set.
	 *
	 *  The walls are numbered 0 through 2*m*n - m - n - 1 and the
	 *  rooms are number 0 through m*n - 1.  To ensure that we only
	 *  test each wall at most once, we use the following algorithm:
	 *
	 *     Initialize the array walls with the entries
	 *             0, 1, 2, ..., 2*m*n - m - n - 1
	 *     At the kth step (starting at 0) select a random entry
	 *     from 0 to 2*m*n - m - n - k - 1.  Choose that to be the
	 *     wall and replace that randomly chosen entry with
	 *     the entry in the last current location:
	 *               2*m*n - m - n - k - 1.
	 */

	void find_adjacent_rooms( int room[2], int wall, int n ) {
		// Determine which row and column 
		int row =    wall / (2*n - 1);
		int column = wall % (2*n - 1);

		// Determine which rooms they connect
		if ( column < n - 1 ) {
			// A vertical wall
			room[0] = n*row + column;
			room[1] = n*row + column + 1;
		} else {
			// A horizontal wall
			column += 1 - n;

			room[0] = n* row      + column;
			room[1] = n*(row + 1) + column;
		}
	}

	void build_maze( int m, int n ) {
		///////////////////////
		// Generate the maze //
		///////////////////////

		Disjoint_sets rooms( m*n );

		int number_of_walls = 2*m*n - m - n;
		bool is_wall[number_of_walls];
		Permutation untested_walls( number_of_walls );

		for ( int i = 0; i < number_of_walls; ++i ) {
			is_wall[i] = true;
		}

		while ( rooms.disjoint_sets() > 1 ) {
			int wall = untested_walls.next();
			int room[2];
			find_adjacent_rooms( room, wall, n );

			// If the two rooms are not connected,
			//   remove the wall between them and
			//   take the union of the two sets.
			if ( rooms.find( room[0] ) != rooms.find( room[1] ) ) {
				is_wall[wall] = false;
				rooms.set_union( room[0], room[1] );
			}
		}

		////////////////////
		// Print the maze //
		////////////////////

		//  + +-+-+-+-+-+-+-+-+-+-+-+-+-+  Top border
		//  | ? ? ? ? ? ? ? ? ? ? ? ? ? |  \ 0th row
		//  +?+?+?+?+?+?+?+?+?+?+?+?+?+?+  /
		//  | ? ? ? ? ? ? ? ? ? ? ? ? ? |
		//  +?+?+?+?+?+?+?+?+?+?+?+?+?+?+
		//  | ? ? ? ? ? ? ? ? ? ? ? ? ? |
		//  +?+?+?+?+?+?+?+?+?+?+?+?+?+?+
		//  | ? ? ? ? ? ? ? ? ? ? ? ? ? |  \ (m - 2)nd row
		//  +?+?+?+?+?+?+?+?+?+?+?+?+?+?+  /
		//  | ? ? ? ? ? ? ? ? ? ? ? ? ? |  Last row
		//  +-+-+-+-+-+-+-+-+-+-+-+-+-+ +  Bottom border

		// Print the top border.

		std::cout << "+  +";

		for ( int i = 0; i < n - 1; ++i ) {
			std::cout << "--+";
		}

		std::cout << std::endl;

		int wall_counter = 0;

		for ( int i = 0; i < m - 1; ++i ) {
			// Print the vertical walls of the ith row.

			std::cout << "|";

			for ( int j = 0; j < n - 1; ++j ) {
				if ( is_wall[wall_counter] ) {
					std::cout << "  |";
				} else {
					std::cout << "   ";
				}

				++wall_counter;
			}

			std::cout << "  |" << std::endl;

			// Print the horizontal walls of the ith row:
			//  - these are the walls between the ith and (i + 1)st rows.

			std::cout << "+";

			for ( int j = 0; j < n; ++j ) {
				if ( is_wall[wall_counter] ) {
					std::cout << "--+";
				} else {
					std::cout << "  +";
				}

				++wall_counter;
			}

			std::cout << std::endl;
		}

		// Print the horizontal walls of the last row.

		std::cout << "|";

		for ( int j = 0; j < n - 1; ++j ) {
			if ( is_wall[wall_counter] ) {
				std::cout << "  |";
			} else {
				std::cout << "   ";
			}

			++wall_counter;
		}

		std::cout << "  |" << std::endl;

		// Print the bottom border.

		for ( int i = 0; i < n - 1; ++i ) {
			std::cout << "+--";
		}

		std::cout << "+  +" << std::endl;
	}
}

#endif
