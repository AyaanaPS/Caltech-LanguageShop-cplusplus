#include "maze.hh"
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

Maze generateMaze(int rows, int cols);
void addDirectionOption(const Maze &maze, const Location &current,
        Direction dir, vector<Direction> &v);
/* This function is used in the main function. It serves to print out a 
 * usage statement in case of any errors with the command line arguments.
 */

void printUsage(char *name)
{
    cerr << "usage: " << name << "numRows numCols\n\t"
        "numRows is the number of rows in the maze\n\t"
        "numCols is the number of columns in the maze" << endl;
}

/* This is the main function of the program */

int main(int argc, char** argv)
{
    /* First, the command line arguments are parsed and checked */

    if(argc != 3)
    {
        printUsage(argv[0]);
    }

    int numRows = atoi(argv[1]);
    int numCols = atoi(argv[2]);

    /* Seeds random number generator */
    srand(time(NULL));

    /* Calls the generateMaze function 
    */
    Maze m = generateMaze(numRows, numCols);

    m.print(cout);
    
    return 0;

}

/* This function takes in integers representing the number of rows and the
 * number of columns. It then generates a maze. 
 */

Maze generateMaze(int rows, int cols)
{
    Maze m(rows, cols);
    vector<Location> path;

    /* Clear the maze, set all possible walls to walls, set the start and end
     * position to the top left and bottom right respectively.
     */

    m.clear();
    m.setAllWalls();
    Location start(0, 0);
    Location end(rows-1, cols-1);

    m.setStart(start.row, start.col);
    m.setEnd(end.row, end.col);

    m.setVisited(start.row, start.col);
    path.push_back(start);

    /* Iterate while stack of potential moves is not empty */
    while(!path.empty())
    {
        /* Current is the last move in the path */
        Location current = path.back();

        /* If current is the end position, pop it off the stack and continue
         * the iteration of the loop.
         */
        if(current == m.getEnd())
        {
            path.pop_back();
        }
        else
        {
            /* Fill the vector of potential directions by checking to see if
             * the cells is on a border of the maze. If it isn't on at least
             * one border, call the addDirectionOption function for that
             * direction.
             */

            vector<Direction> options;

            if (current.row > 0)
            {
                addDirectionOption(m, current, Direction::NORTH, options);
            }

            if (current.row < m.getNumRows() - 1)
            {
                addDirectionOption(m, current, Direction::SOUTH, options);
            }
            
            if (current.col > 0)
            {
                addDirectionOption(m, current, Direction::WEST, options);
            }

            if (current.col < m.getNumCols() - 1)
            {
                addDirectionOption(m, current, Direction::EAST, options);
            }

            /* If there are no potential options, pop off the latest move. 
             * This is the backtracing step 
             */

            if(options.empty())
            {
                path.pop_back();
            }

            /* Else, choose a random direction and clear the wall in that
             * direction. Then, make the next move the neighbor in that
             * direction and set the status of the neighbor to visited.
             * Then append next to the path vector.
             */

            else
            {
                int randomIndex = rand() % options.size();
                Direction dir = options[randomIndex];
                m.clearWall(current.row, current.col, dir);

                Location next = m.getNeighborCell(current.row, current.col,
                        dir);
                m.setVisited(next.row, next.col);
                path.push_back(next);
            }
        }
    }

    return m;
}

/* This helper functions checks to see if the neighbor in the direction
 * specified has been visited. If it hasn't then the direction is appended
 * to the vector of options */
 
void addDirectionOption(const Maze &maze, const Location &current,
        Direction dir, vector<Direction> &v)
{
    Location neighbor = maze.getNeighborCell(current.row, current.col, dir);
    if(!maze.isVisited(neighbor.row, neighbor.col))
    {
        v.push_back(dir);
    }
}
