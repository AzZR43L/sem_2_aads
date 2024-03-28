#ifndef OUT_FUNCS
#define OUT_FUNCS
#include "list.hpp"
#include <iostream>
#include <limits>

using depot_t = psarev::List< std::pair< std::string, psarev::List< unsigned long long > > >;

namespace psarev
{
  template< typename T >
  void outOrds(depot_t& lines);

  template< typename T >
  List< T > outDigits(depot_t& lines, size_t maxDigits, bool& isOF);

  template< typename T >
  void outSums(List< T >& sums);
}

template< typename T >
void psarev::outOrds(depot_t& lines)
{
  depot_t::Iterator iterLine = lines.begin();
  for (size_t i = 0; i < lines.getSize(); i++)
  {
    std::cout << (*iterLine).first;
    iterLine++;
    if (i < (lines.getSize() - 1))
    {
      std::cout << ' ';
    }
    else
    {
      std::cout << '\n';
    }
  }
}

template< typename T >
psarev::List< T > psarev::outDigits(depot_t& lines, size_t maxDigits, bool& isOF)
{
  depot_t::Iterator iterLine = lines.begin();
  typename List< T >::Iterator iterDig;
  List< T > sums;
  T curSum = 0;
  for (size_t i = 0; i < maxDigits; i++)
  {
    curSum = 0;
    iterLine = lines.begin();
    for (size_t j = 0; j < lines.getSize(); j++)
    {
      iterDig = (*iterLine).second.begin();
      if ((*iterLine).second.getSize() > i)
      {
        for (size_t k = 0; k < i; k++)
        {
          iterDig++;
        }
        if (curSum != 0)
        {
          std::cout << ' ';
        }
        std::cout << *iterDig;
        if (*iterDig > std::numeric_limits< unsigned long long >::max() - curSum)
        {
          isOF = true;
        }
        else
        {
          curSum += *iterDig;
        }
      }
      iterLine++;
    }
    sums.pushBack(curSum);
    std::cout << '\n';
  }
  return sums;
}

template< typename T >
void psarev::outSums(List< T >& sums)
{
  if (sums.empty())
  {
    std::cout << 0;
  }
  else
  {
    typename psarev::List< T >::Iterator iterSums = sums.begin();
    for (size_t i = 0; i < sums.getSize(); i++)
    {
      if (i != 0)
      {
        std::cout << ' ';
      }
      std::cout << *iterSums;
      iterSums++;
    }
  }
  std::cout << '\n';
}

#endif