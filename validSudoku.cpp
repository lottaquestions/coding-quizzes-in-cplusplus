#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <numeric>

bool validSudoku(std::vector<std::vector<int32_t>>& input){
  using std::vector;
  using std::set;
  using std::map;
  using std::pair;

  constexpr uint32_t blockSize{3};

  if (input.empty())
    return false;

  vector<set<int32_t>> rowSets(input.size(), set<int32_t>());
  vector<set<int32_t>> colSets(input[0].size(),set<int32_t>());
  map<pair<uint32_t,uint32_t>,set<int32_t>> blockSets{};
  vector<uint32_t> fillVec(input.size()/blockSize, 0);
  std::iota(fillVec.begin(), fillVec.end(), 0);
  for(auto i : fillVec){
    for (auto j : fillVec){
      blockSets.insert({{i,j},{}});
    }
  }
  

  uint32_t rowIdx{0};
  for (auto row : input){
    uint32_t colIdx{0};
    for (auto col : row){
      auto [it, valid] = rowSets[rowIdx].insert(col);
      if(valid){
	auto [it, valid] = colSets[colIdx].insert(col);
	if(valid){
	  auto blockRowIdx{static_cast<uint32_t>(rowIdx/blockSize)};
	  auto blockColIdx{static_cast<uint32_t>(colIdx/blockSize)};
	  auto blockKey{pair<uint32_t,uint32_t>(blockRowIdx,blockColIdx)};
	  auto [it, valid] = blockSets[blockKey].insert(col);
	  if (!valid)
	    return valid;
	}else
	  return valid;
      }
      else
	return valid;
      ++colIdx;
    }
    ++rowIdx;
  }
  return true;

}


int main(){
  std::vector<std::vector<int32_t>> input{};
  std::map<bool,std::string> bool2String{{true, "true"}, {false, "false"}};
  bool isValid{validSudoku(input)};
  std::cout<< "Is valid sudoko: " <<  bool2String[isValid] << std::endl;
}
