#include "IOProcessing.hpp"

std::string miheev::getWord(std::string& s)
{
  std::string symbol = s.substr(0, s.find(" "));
  if (s.find(" ") == std::string::npos)
  {
    s = "";
  }
  else
  {
    s = s.substr(s.find(" ") + 1);
  }
  return symbol;
}

void miheev::inputData(std::istream& in, miheev::Data& container)
{
  std::string line = "";
  std::getline(in, line);
  int key = 0;
  std::string value = "";
  while (line != "")
  {
    key = std::stoi(getWord(line));
    value = getWord(line);
    container.insert(key, value);
  }
}

void miheev::inputDatasets(std::istream& in, miheev::Tree< std::string, miheev::Data >& container)
{
  std::string datasetName = "";
  in >> datasetName >> std::ws;
  if (datasetName == "")
  {
    return;
  }
  miheev::Data datasetData;
  inputData(in, datasetData);
  container.insert(datasetName, datasetData);
}
