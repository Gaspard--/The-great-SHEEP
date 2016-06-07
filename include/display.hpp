#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

class	Display
{
public:
  int	WIDTH, HEIGHT;
  virtual void	render() = 0;
};

#endif // DISPLAY_HPP_
