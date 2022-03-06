#include <iostream>
#include <string>

std::string printBinary(double num){
  if (num >=1 || num <= 0)
    return "Error:Number not in range (0,1)";

  std::string binary{};

  binary.append("0.");

  while (num > 0){
    //Setting a limit on length:32 characters
    if (binary.length()>=34)
      return "Error: Binary is greater than 32 characters";

    double r = num*2;
    if (r >=1){
      binary.append("1");
      num = r-1;
    }
    else{
      binary.append("0");
      num = r;
    }
  }

  return binary;
}

int main (){
  double inputVar{0};

  std::cout << "Enter a decimal number between 0 and 1\n";
  std::cin >> inputVar;
  std::cout << "Binary: " << printBinary(inputVar) << std::endl;
  return 0;
}
