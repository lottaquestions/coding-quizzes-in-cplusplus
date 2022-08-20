#include <iostream>
#include <vector>
#include <map>
#include <tuple>

using std::vector;
using std::tuple;
using std::map;

struct ProfitCalculator{
  ProfitCalculator(vector<double>& prices) : prices(prices){}
  double maxProfit(){
    return maxProfitHelper(0, true);
  }
  double maxProfitHelper(int idx, bool buying){
    if(idx >= prices.size()){
      return 0.0;
    }

    auto itCached{cachedProfitMap.find(tuple(idx,buying))};
    if(itCached != cachedProfitMap.end()){
      return itCached->second;
    }

    double cooldown {maxProfitHelper(idx + 1, buying)};

    if(buying){
      double buy {maxProfitHelper(idx + 1, !buying) - prices[idx]};
      cachedProfitMap[tuple(idx,buying)] = std::max(buy, cooldown);
    }
    else{
      double sell {maxProfitHelper(idx + 2, !buying) + prices[idx]};
      cachedProfitMap[tuple(idx,buying)] = std::max(sell, cooldown);
    }
    return cachedProfitMap[tuple(idx,buying)];
  }
  vector<double>& prices;
  map<tuple<int,bool>, double> cachedProfitMap;
};

int main(){
  vector<double> input{1,2,3,0,2};
  //Expect output of 3
  //Explanation: transactions = [buy,sell, cooldown, buy, sell]
  ProfitCalculator profitCalculator(input);
  double result {profitCalculator.maxProfit()};
  std::cout << "The max profit is: " << result << std::endl;
  return 0;
}
