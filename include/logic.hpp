#ifndef LOGIC_HPP_
# define LOGIC_HPP_

# include <vector>

class Fixture;

class Logic
{
private:
  std::vector<Fixture *> fixtures;
public:
  Logic();
  void addFixture(Fixture *fixture);
  void removeFixture(Fixture *fixture);
};

#endif // !LOGIC_HPP_
