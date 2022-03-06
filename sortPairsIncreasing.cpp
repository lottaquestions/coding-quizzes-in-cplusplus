#include <iostream>
#include <vector>
#include <algorithm>

struct HtWt;
std::vector<HtWt> getIncreasingSequence(std::vector<HtWt> &items);
std::vector<HtWt> longestIncreasingSubsequence(std::vector<HtWt> &array);
void longestIncreasingSubsequence(std::vector<HtWt> &array, std::vector<std::vector<HtWt> > &solutions,
				  long int current_index);
std::vector<HtWt> seqWithMaxLength(std::vector<HtWt> &seq1, std::vector<HtWt> &seq2);


struct HtWt{
  int Ht;
  int Wt;
  
  // Returns true if "this" should be lined up before "other". Note that is it possible that
  // this.isBefore(other) and other.isBefore(this) are both false. This is different from the
  // compareTo method where if a < b, then b > a
  bool isBefore(HtWt other){
    if (this->Ht < other.Ht  &&  this->Wt < other.Wt)
      return true;
    else
      return false;
  }
};

std::vector<HtWt> getIncreasingSequence(std::vector<HtWt> &items){
  std::sort(items.begin(), items.end(), [](HtWt first, HtWt second){
                                          if (first.Ht != second.Ht)
                                            return first.Ht < second.Ht;
                                          else
                                            return first.Wt < second.Wt;
                                           });
  return longestIncreasingSubsequence(items);
}

std::vector<HtWt> longestIncreasingSubsequence(std::vector<HtWt> &array){
  
  std::vector<std::vector<HtWt> > solutions(array.size());
  
  longestIncreasingSubsequence(array, solutions, 0l);

  std::vector<HtWt> best_sequence{};

  for(long int i = 0; i < array.size(); i++){
    best_sequence = seqWithMaxLength(best_sequence, solutions[i]);
  }
  return best_sequence;
}

//Returns longer sequence
std::vector<HtWt> seqWithMaxLength(std::vector<HtWt> &seq1, std::vector<HtWt> &seq2){
  if (seq1.empty())
    return seq2;
  if (seq2.empty())
    return seq1;
  return seq1.size() > seq2.size() ? seq1 : seq2;
}

void longestIncreasingSubsequence(std::vector<HtWt> &array, std::vector<std::vector<HtWt> > &solutions,
				  long int current_index){
  if (current_index >= array.size() || current_index < 0)
    return;

  HtWt current_element{array[current_index]};

  //Find longest sequence we can append current element to
  std::vector<HtWt> best_sequence{};
  for(long int i=0; i < current_index; ++i){
    if (array[i].isBefore(current_element)){
      best_sequence = seqWithMaxLength(best_sequence, solutions[i]);
    }
  }

  //Append current_element
  std::vector<HtWt> new_solution{};
  if (!best_sequence.empty())
    new_solution.insert(new_solution.end(), best_sequence.begin(), best_sequence.end());
  new_solution.push_back(current_element);

  //Add to the list and recurse
  solutions[current_index] = new_solution;
  longestIncreasingSubsequence(array, solutions, current_index + 1);
}

int main(){
  std::vector<HtWt> items{{21,13},{25,12},{23,10},{22,14},{24,11}};
  std::vector<HtWt> results = getIncreasingSequence(items);
  for (auto cur_res: results){
    std::cout << "(" << cur_res.Ht << ", " << cur_res.Wt << "), ";
  }
  std::cout << std::endl;
  return 0;
}
