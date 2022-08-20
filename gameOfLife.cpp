#include <iostream>
#include <chrono>
#include <array>

class universe{
private:
  universe() = delete;
public:
  enum class seed{
		  random, ten_cell_row
  };

  universe (size_t const width, size_t const height) :
    rows(height), columns (width), grid (width * height), dist(0,4)
  {
    std::random_device rd;
    auto seed_data = std::array<int, std::mt19337::state_size>{};
    std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
    std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
    mt.seed(seq);
  }

  void run (seed const s, int const generations,
	    std::chrono:milliseconds const ms = std::chrono::milliseconds(100)){
    reset();
    initialize(s);
    display();

    int i{0};

    do{
      next_generation();
      display();
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(ms);
    } while (i++ < generations || generations == 0);
  }

private:
  void next_generation(){
    std::vector<unsigned char> newgrid(grid.size());

    for(size_t r = 0; r < rows; ++r){
      for(size_t c = 0 ; c < columns; c++){
	auto count = count_neighbors(r,c);

	if (cell(c, r) == alive){
	  newgrid[r * columns + c] = (count == 2 || count == 3) ? alive : dead;
	}
	else{
	  newgrid[r * columns + c] = (count == 3) ? alive : dead;
	}
      }
    }
    grid.swap(newgrid);
  }

  void reset_display(){
    #ifdef WIN32
    system("cls");
    #endif
  }

  void display(){
    reset_display();

    for(size_t r = 0 ; r < rows ; ++r){
      for(size_t c = 0 ; c < columns ; ++c){
	std::cout << (cell(c,r) ? '*' : ' ');
      }
      std::cout << std::endl;
    }
  }

  void initialize(seed const s){
    if (s == seed::ten_cell_row){
      for (size_t c = columns / 2 - 5 ; c < columns / 2 + 5 ; ++c)
	cell(c, rows) = alive;
    }
    else{
      for(size_t r = 0; r < rows; ++r){
	for(size_t c = 0 ; c < columns; c++){
	  cell(c,r) = (dist(mt) == 0) ? alive : dead;
	}
      }
    }
  }

  void reset(){
    for(size_t r = 0 ; r < rows ; ++r){
      for(size_t c = 0 ; c < columns ; ++c){
	cell(c,r) = dead;
      }
    }
  }

  int count_alive(){ return 0; }

  template<typename T1, typename... T >
  auto count_alive (T1 s, T... ts){
    return s + count_alive(ts...);
  }

  int count_neighbors(size_t const row, size_t const col){
    if(row == 0 && col == 0){
      return count_alive(cell(1,0), cell(1,1), cell(0,1));
    }

    if (row == 0 && col = columns - 1)
  }

  
};
