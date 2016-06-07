#ifndef BUFFER_HPP_
# define BUFFER_HPP_

template <class StorageType>
class	Buffer
{
public:
  StorageType	*data;
  unsigned int	data_size;
  unsigned int	capacity;

  Buffer()
  {
    data_size = 0;
    capacity = 0;
    data = 0;
  }

  ~Buffer()
  {
    if (data_size)
      delete [] data;
  }

  Buffer	*addData(StorageType *toAdd, unsigned int amount)
  {
    return (prepareCapacity(amount)->noIfAdd(toAdd, amount));
  }

  Buffer	*prepareCapacity(unsigned int amount)
  {
    StorageType	*temp;

    if (data_size + amount > capacity)
      {
	temp = data;
	data = new StorageType[data_size + amount];
	if (data_size)
	  {
	    memcpy(data, temp, (data_size) * sizeof(StorageType));
	    delete [] temp;
	  }
	capacity = data_size + amount;
      }
    return (this);
  }

  Buffer	*noIfAdd(StorageType *toAdd, unsigned int amount)
  {
    memcpy(data + data_size, toAdd, amount * sizeof(StorageType));
    data_size = data_size + amount;
    return (this);
  }
};

#endif // BUFFER_HPP_
