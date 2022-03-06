#include <iostream>
#include <algorithm>
#include <vector>
#include <type_traits>
#include <unordered_map>
#include <string>
#include <cstdlib>
#include <ctime>

const auto LETTER_COUNT = 4;
const auto MAX_WORDS = 100;

std::vector<std::string> populate_anagram_list(){
    srand(time(0));
    
    std::vector<std::string> anagramList;
    anagramList.reserve(MAX_WORDS);
    
    for( auto i = 0; i < MAX_WORDS; ++i){
        std::string strHolder(LETTER_COUNT, ' ');
        std::generate(strHolder.begin(),strHolder.end(),[](){return static_cast<char>('a'+(rand()%LETTER_COUNT));});
        anagramList.push_back(std::move(strHolder));
    }
    return anagramList;
}

// Above is the original function and below is the more highly optimized one.
// I still need to figure out how to allocate a vector of contiguous string objects (perhaps an allocator?)
// Will check the assembly code to see if RVO is done for the whole vector
/*
std::vector<std::string(6, ' ')> populate_anagram_list(){
    srand(time(0));
    const auto MAX_WORDS = 100;
    std::vector<std::string> anagramList;
    anagramList.reserve(MAX_WORDS);
    
    for( auto i = 0; i < MAX_WORDS; ++i){
        std::generate(anagramList[i].begin(),anagramList[i].end(),[](){return static_cast<char>('a'+(rand()%LETTER_COUNT));});
    }
    return anagramList;
}*/

int main (){
    auto anagramList = populate_anagram_list();
    auto print_anagram = [](std::vector<std::string> &anagramList){
        std::cout<< std::endl;
        for(auto anagram = anagramList.begin(); anagram != anagramList.end(); ++anagram)
            std::cout<< *anagram << ' ';
        std::cout<< std::endl;
        std::cout<< "================================" <<std::endl;
    };
    
    print_anagram(anagramList);
    
    std::unordered_map<std::string, std::vector<std::string> > anagrams;
    
    for(auto i = 0 ; i < anagramList.size(); ++i){
        // We will be using std::move which modifies the vector
        // so iterators will be invalidated. so we choose to use
        // the index into the array
        auto toCheck= anagramList[i];
        std::sort(toCheck.begin(), toCheck.end());
        auto itAnagram = anagrams.find(static_cast<std::add_const<std::string>::type> (toCheck));
        if(itAnagram != anagrams.end()){
            itAnagram->second.push_back(std::move(anagramList[i]));
        }
        else{
            anagrams[toCheck].push_back(std::move(anagramList[i])); 
        }
    }
    
    std::vector<std::string> anagramOutList;
    anagramOutList.reserve(MAX_WORDS);
    
    auto anagram_unpack = [&anagramOutList](std::pair< const std::string, std::vector<std::string> >anagramGroupContainer){
        auto anagramGroup = anagramGroupContainer.second;
        for(auto i = 0 ; i < anagramGroup.size(); ++i){
            anagramOutList.push_back(std::move(anagramGroup[i]));
        }
    };
    
    //Create a vector from the grouped contents of the hash table
    std::for_each(anagrams.begin(), anagrams.end(), anagram_unpack);
    
    print_anagram(anagramOutList);
    
    return 0;
}
