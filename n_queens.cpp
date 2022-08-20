#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <functional>

using std::set;
using std::vector;
using std::string;

struct DataStore{
  set<int>& col;
  set<int>& positiveDiag; // r + c
  set<int>& negativeDiag; // r - c
  vector<vector<string>>& result;
  
  vector<vector<string>>& board;

  int& n;
};

void backtrack (DataStore& store, int r){
  auto [col, positiveDiag, negativeDiag, result, board, n] = store;
  if (r == n){
    vector<string> validBoard{};
    for (vector<string>& row : board){
      string sRow = std::accumulate(row.begin(), row.end(), string(), [](string accum, string curCol){
									return std::move(accum) + curCol;
								      });
      validBoard.push_back(sRow);
    }
    result.push_back(validBoard);
    return;
  }

  for (int c =0; c < n ; c++){
    if (col.find(c) != col.end() || positiveDiag.find(r+c) != positiveDiag.end() || negativeDiag.find(r-c) != negativeDiag.end())
      continue;
		     
    col.insert(c);
    positiveDiag.insert(r+c);
    negativeDiag.insert(r-c);
    board[r][c] = "Q";

    backtrack(store, r+1);

    col.erase(c);
    positiveDiag.erase(r+c);
    negativeDiag.erase(r-c);
    board[r][c] = ".";
  }
}

std::vector<std::vector<std::string>> solveNQueens(int n){

  
  set<int> col{};
  set<int> positiveDiag{}; // r + c
  set<int> negativeDiag{}; // r - c
  vector<vector<string>> result{};
  
  vector<vector<string>> board (n, vector<string>(n, "."));

  DataStore store{col, positiveDiag, negativeDiag, result, board , n};

  
  backtrack(store, 0);
  return result;
  
}

int main(){
  auto result{solveNQueens(8)};
  for (auto& validSol : result){
    for_each(validSol.begin(), validSol.end(),[] (string& input){std::cout << input<<std::endl;});
    std::cout <<std::endl<<std::endl;
  }
  return 0;
}
