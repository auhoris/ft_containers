#include "includes/stack.hpp"

int main ()
{
  ft::stack<int> mystack;

  mystack.push(10);
  mystack.push(20);

  mystack.top() -= 5;

  std::cout << "mystack.top() is now " << mystack.top() << '\n';
  mystack.pop();
  std::cout << mystack.top() << std::endl;
  mystack.push(12);
  mystack.push(13);
  mystack.push(14);
  mystack.push(15);
  mystack.push(16);
  std::cout << mystack.size() << std::endl;
  mystack.push(17);
  mystack.push(18);

  return 0;
}
