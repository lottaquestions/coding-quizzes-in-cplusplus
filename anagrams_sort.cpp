#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

const auto LETTER_COUNT = 4;

std::vector<std::string> populate_anagram_list(){
    srand(time(0));
    const auto MAX_WORDS = 100;
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
    auto print_anagram = [&anagramList](){
        std::cout<< std::endl;
        for(auto anagram = anagramList.begin(); anagram != anagramList.end(); ++anagram)
            std::cout<< *anagram << ' ';
        std::cout<< std::endl;
        std::cout<< "================================" <<std::endl;
    };
    
    print_anagram();
    
    auto sort_func = [](std::string str1, std::string str2){
        std::sort(str1.begin(), str1.end());
        std::sort(str2.begin(), str2.end());
        return !str1.compare(str2); // Compare returns 0 when they are equal
    };
    
    std::sort(anagramList.begin(), anagramList.end(), sort_func);
    
    print_anagram();
    
    return 0;
}
