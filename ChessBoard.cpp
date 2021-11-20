#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <climits>
#include <math.h>

using namespace std;

class ChessBoard
{
public:
	int BoardVisited[20][20], Distance[20][20];

	//x and y direction where a knight can move
	int xPositions[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int yPositions[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

	//Parameterized constructer to initialize all cells of 2D Array to 0 to represent unvisited cells
	ChessBoard(int N)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				BoardVisited[i][j] = 0;
			}
		}
	}

	void knight_plays(int N, vector<int> &SourcePos, vector<int> &TargetPos)
	{
		//path vector stores the moves to reach destination
		vector<pair<int, int>> path;
		int minDistance = shortestPath(SourcePos, TargetPos, N, path);

		//Print the shortest path
		cout << "\nShortest distance from source to destination is: " << minDistance << endl;

		path.push_back(make_pair(TargetPos[0], TargetPos[1])); //added the destination pair

		//print the squares/cells leading to shortest path
		cout << endl
			<< "The path followed to reach destination in shortest distance is: ";
		for (int i = 0; i < path.size(); i++)
		{
			cout << "[" << path[i].first << "," << path[i].second << "], ";
		}
	}

	//isValid is function to find whether the x and y position is a valid knight move or not
	bool isValid(int x, int y, int N)
	{
		//returns false if (x, y) lies outside chess board or if it is already visited. Else, returns true
		if (x < 0 || y < 0 || x > N || y > N || BoardVisited[x][y] == 1)
			return false;

		return true;
	}

	int shortestPath(vector<int> &SourcePos, vector<int> &TargetPos, int N, vector<pair<int, int>> &path)
	{
		//We use Breadth First Search and store the chess board's cell position in queue such that each element of queue has pair of x coordinate and y coordinate.
		//We find adjacent valid cells for each knight's move and push it into the queue
		queue<pair<int, int>> q;
		int xCoordinate = SourcePos[0];
		int yCoordinate = SourcePos[1];
		Distance[xCoordinate][yCoordinate] = 0;

		//Since source is visited, we mark it as 1 and push source into the queue
		BoardVisited[xCoordinate][yCoordinate] = 1;
		q.push({ xCoordinate, yCoordinate });

		if (xCoordinate == TargetPos[0] && yCoordinate == TargetPos[1])
			return (Distance[xCoordinate][yCoordinate]);

		//path vector stores the moves to reach destination. We initiate the path_x and path_y with source coordinates.
		int path_x = xCoordinate, path_y = yCoordinate;
		double path_dist = INT_MAX;
		path.push_back(make_pair(path_x, path_y));

		while (!q.empty())
		{
			int curr_x = q.front().first;
			int curr_y = q.front().second;
			q.pop();
			for (int i = 0; i < 8; i++)
			{
				if (isValid(curr_x + xPositions[i], curr_y + yPositions[i], N) == true)
				{
					xCoordinate = curr_x + xPositions[i];
					yCoordinate = curr_y + yPositions[i];

					Distance[xCoordinate][yCoordinate] = Distance[curr_x][curr_y] + 1;

					BoardVisited[xCoordinate][yCoordinate] = 1;
					q.push({ xCoordinate, yCoordinate });

					double distanceFromDestination = calculateDistances(xCoordinate, TargetPos[0], yCoordinate, TargetPos[1]);
					if (distanceFromDestination < path_dist)
					{
						path_x = xCoordinate;
						path_y = yCoordinate;
						path_dist = distanceFromDestination;
					}

					if (xCoordinate == TargetPos[0] && yCoordinate == TargetPos[1])
						return Distance[xCoordinate][yCoordinate];
				}
			}
			path.push_back(make_pair(path_x, path_y));
		}
		//if Target Position is unreachable, return -1
		return -1;
	}

	double calculateDistances(int xi, int xj, int yi, int yj)
	{
		return sqrt((pow(xj - xi, 2)) + pow(yj - yi, 2));
	}
};

int main()
{
	int N;
	vector<int> SourcePos(2);
	vector<int> TargetPos(2);

	cout << "Please enter the size of board N: ";
	cin >> N;

	//Calling the constructor to initialize all cells as unvisited initially
	ChessBoard obj(N);

	cout << "\nPlease enter knight's source position: ";
	cin >> SourcePos[0] >> SourcePos[1];

	cout << "\nPlease enter knight's target position: ";
	cin >> TargetPos[0] >> TargetPos[1];

	obj.knight_plays(N, SourcePos, TargetPos);

	return 0;
}
