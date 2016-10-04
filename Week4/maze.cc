#include "maze.hh"
#include <iostream>
#include <assert.h>
using namespace std;

/* 
 * This is the initializing function. It initializes a new maze with the 
 * inputted number of rows and columns.
 */

void Maze::init(int rows, int cols)
{
	numRows = rows;
	numCols = cols;

	int arraySize = ((numRows * 2) + 1) * ((numCols * 2) + 1);
	cells = new MazeCell[arraySize];

	for(int i = 0; i < arraySize; i ++)
	{
		cells[i] = MazeCell::EMPTY;
	}

	Location sInit(0, 0);
	Location eInit(numRows - 1, numCols -1);

	start = sInit;
	end = eInit;
}

/* 
 * This is used by the copy constructor. It copies over the data from the 
 * inputted maze into the new maze.
 */

void Maze::copy(const Maze &m)
{
	numRows = m.numRows;
	numCols = m.numCols;
	start = m.start;
	end = m.end;

	int size = ((numRows * 2) + 1) * ((numCols * 2) + 1);

	cells = new MazeCell[size];
	for(int i = 0; i < size; i++)
	{
		cells[i] = m.cells[i];
	}
}

/* 
 * This takes 2D expanded coordinates and computes the corresponding
 * 1D array index.
 */

int Maze::getArrayIndex(const Location &loc) const
{
	int rowE = loc.row;
	int colE = loc.col;
	int numColumnsE = (numCols * 2) + 1;
	int newIndex = (numColumnsE * rowE) + colE;
	return newIndex;
}

/*
 * Returns the expanded coordinates of the specified cell coordinates.
 */

Location Maze::getCellArrayCoord(int cellRow, int cellCol) const
{
	int rowE = (cellRow * 2) + 1;
	int colE = (cellCol * 2) + 1;
	Location result(rowE, colE);
	return result;
}

/*
 * Returns the expanded coordinates of the wall on a specific side of 
 * a cell given in cell coordinates.
 */

Location Maze::getWallArrayCoord(int cellRow, int cellCol, 
	Direction direction) const
{
	Location expanded = getCellArrayCoord(cellRow, cellCol);
	int rowE = expanded.row;
	int colE = expanded.col;

	if(direction == Direction::NORTH)
	{
		rowE--;
	}
	else if (direction == Direction::SOUTH)
	{
		rowE++;
	}
	else if (direction == Direction::EAST)
	{
		colE++;
	}
	else if (direction == Direction::WEST)
	{
		colE--;
	}

	Location result(rowE, colE);
	return result;
}

/* 
 * This initializes a nwe maze of size rows x cols using the init function.
 */

Maze::Maze(int rows, int cols)
{
	init(rows, cols);
}

/*
 * This makes a copy of the existing maze object using the copy function.
 */
Maze::Maze(const Maze &m)
{
	copy(m);
}

/*
 * This is the maze destructor.
 */

Maze::~Maze()
{
	delete [] cells;
}

/* 
 * This returns the number of rows in the maze.
 */

int Maze::getNumRows() const
{
	return numRows;
}

/*
 * This returns the number of columns in the maze.
 */

int Maze::getNumCols() const
{
	return numCols;
}

/* 
 * This returns the starting point of the maze.
 */

Location Maze::getStart() const
{
	return start;
}

/*
 * This sets the starting point in the maze to be the inputted coordinates.
 */

void Maze::setStart(int row, int col)
{
	assert((row >= 0 && row < numRows) && "Not a valid position.");
	assert((col >= 0 && col < numCols) && "Not a valid position.");
	start.row = row;
	start.col = col;
}

/*
 * This returns the ending point of the maze.
 */

Location Maze::getEnd() const
{
	return end;
}

/*
 * This sets the ending point of the maze to be the inputted coordinates.
 */

void Maze::setEnd(int row, int col)
{
	assert((row >= 0 && row < numRows) && "Not a valid position.");
	assert((col >= 0 && col < numCols) && "Not a valid position.");
	end.row = row;
	end.col = col;
}

/*
 * This sets all the walls and cells to be empty. It completely clears the
 * maze.
 */

void Maze::clear()
{
	int expRows = (2 * numRows) + 1;
	int expCols = (2 * numCols) + 1;
	int arraySize = expRows * expCols;
	for(int i = 0; i < arraySize; i++)
	{
		cells[i] = MazeCell::EMPTY;
	}
}

/* 
 * This places a wall at every location that can be a wall in the maze.
 */

void Maze::setAllWalls()
{
	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numCols; j++)
		{

				Location locN = getWallArrayCoord(i, j, Direction::NORTH);
				cells[getArrayIndex(locN)] = MazeCell::WALL;

				Location locS = getWallArrayCoord(i, j, Direction::SOUTH);
				cells[getArrayIndex(locS)] = MazeCell::WALL;

				Location locW = getWallArrayCoord(i, j, Direction::WEST);
				cells[getArrayIndex(locW)] = MazeCell::WALL;

				Location locE = getWallArrayCoord(i, j, Direction::EAST);
				cells[getArrayIndex(locE)] = MazeCell::WALL;
		}
	}
}

/* 
 * This returns the value of the specified cell.
 */

MazeCell Maze::getCell(int cellRow, int cellCol) const
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location curCell = getCellArrayCoord(cellRow, cellCol);
	int checkIndex = getArrayIndex(curCell);
	return cells[checkIndex];
}

/*
 * This sets the value of the specified cell to be the inputted MazeCell value.
 */

void Maze::setCell(int cellRow, int cellCol, MazeCell val)
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location curCell = getCellArrayCoord(cellRow, cellCol);
	int checkIndex = getArrayIndex(curCell);
	cells[checkIndex] = val;
}

/* 
 * This returns the cell-coordinates of the neighboring cell in the specified
 * direction. It trips an assertion if the given cell has no neighbor in the
 * specified direction.
 */

Location Maze::getNeighborCell(int cellRow, int cellCol, Direction direction) 
	const
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	if(direction == Direction::NORTH)
    {
        cellRow = cellRow -1;
    }
    else if (direction == Direction::EAST)
    {
        cellCol = cellCol + 1;
    }
    else if (direction == Direction::SOUTH)
    {
        cellRow = cellRow + 1;
    }
    else if (direction == Direction::WEST)
    {
        cellCol = cellCol - 1;
    }

    assert ((cellRow >= 0 && cellRow < numRows) 
        && "No neighbor in specified direction");
    assert ((cellCol >= 0 && cellCol < numCols) 
        && "No neighbor in specified direction");

    Location neighbor(cellRow, cellCol);
    return neighbor;
}

/* 
 * Returns true if there is a wall in the specified direction from the
 * given cell, false otherwise.
 */

bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int checkIndex = getArrayIndex(wall);

	if(cells[checkIndex] == MazeCell::WALL)
	{
		return true;
	}
	return false;
}

/*
 * Puts a wall on the specified side of the given cell.
 */

void Maze::setWall(int cellRow, int cellCol, Direction direction)
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int checkIndex = getArrayIndex(wall);
	cells[checkIndex] = MazeCell::WALL;
}

/*
 * Removes a wall on the specified side of the given cell.
 */

void Maze::clearWall(int cellRow, int cellCol, Direction direction)
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location wall = getWallArrayCoord(cellRow, cellCol, direction);
	int checkIndex = getArrayIndex(wall);
	cells[checkIndex] = MazeCell::EMPTY;
}

/*
 * Returns true if the specified maze cell has been visited.
 */

bool Maze::isVisited(int cellRow, int cellCol) const
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location current = getCellArrayCoord(cellRow, cellCol);
	int checkIndex = getArrayIndex(current);

	if(cells[checkIndex] == MazeCell::VISITED)
	{
		return true;
	}
	return false;
}

/*
 * Changes the cell's value to VISITED.
 */

void Maze::setVisited(int cellRow, int cellCol)
{
	assert((cellRow >= 0 && cellRow < numRows) && "Not a valid position.");
	assert((cellCol >= 0 && cellCol < numCols) && "Not a valid position.");

	Location current = getCellArrayCoord(cellRow, cellCol);
	int checkIndex = getArrayIndex(current);
	cells[checkIndex] = MazeCell::VISITED;
}

/*
 * This prints out the maze.
 */

void Maze::print(ostream &os) const
{
	os << "Number of Rows: " << numRows << endl;
	os << "Number of Columns: " << numCols << endl;

	for(int i = 0; i < numRows; i++)
	{
		for(int j = 0; j < numCols; j++)
		{
			if(hasWall(i, j, Direction::NORTH))
			{
				os << "+---";
			}
			else
			{
				os << "+   ";
			}
		}
		os << "+" << endl;
		for (int j = 0; j < numCols; j++)
		{
			if(hasWall(i, j, Direction::WEST))
			{
				if(start.row == i && start.col == j)
				{
					os << "| S ";
				}
				else if(end.row == i && end.col == j)
				{
					os << "| E ";
				}
				else
				{
					os << "|   ";
				}
			}
			else
			{
				if(start.row == i && start.col == j)
				{
					os << "  S ";
				}
				else if(end.row == i && end.col == j)
				{
					os << "  E ";
				}
				else
				{
					os << "    ";
				}
			}
		}
		os << "|" << endl;
	}

	for(int j = 0; j < numCols; j++)
	{
		os << "+---";
	}
	os << "+" << endl;
}
