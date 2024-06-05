#include "internalFuncs.hpp"
#include <cctype>
#include <vector>

std::ostream& psarev::outInvCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
  return out;
}

std::ostream& psarev::outEmptyFile(std::ostream& out)
{
  out << "Error: File is empty!\n";
  return out;
}

std::ostream& psarev::outSucCreate(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been created!\n";
  return out;
}

std::ostream& psarev::outSucChoose(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been choosen!\n";
  return out;
}

std::ostream& psarev::outSucDelete(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> has been deleted!\n";
  return out;
}

std::ostream& psarev::outStoreName(std::ostream& out, std::string name)
{
  out << "Storage <" << name << "> \n";
  return out;
}

std::ostream& psarev::outDirectWrite(std::ostream& out)
{
  out << "Whole depot was printed at the directory!\n";
  return out;
}

std::ostream& psarev::outAdmMessage(std::ostream& out)
{
  out << "Directory with that name already exists, do you want to overwrite it? (Y/N)\n";
  return out;
}

std::map< std::string, std::vector< std::string > > psarev::readStorage(std::istream& in)
{
  using storage_t = std::map< std::string, std::vector< std::string > >;

  storage_t resStorage;
  std::string word = "";

  while (!in.eof())
  {
    if (in >> word)
    {
      cleanUpWord(word);
      if (checkLiter(word))
      {
        std::string spType = getSpType(word);
        auto scanFor = resStorage.find(spType);
        if (scanFor == resStorage.end())
        {
          std::vector< std::string > words;
          words.push_back(word);
          resStorage.emplace(spType, words);
        }
        else
        {
          (resStorage.at(spType)).push_back(word);
        }
      }
    }
  }
  return resStorage;
}

void psarev::cleanUpWord(std::string& word)
{
  const std::string puncts = ".,:;?!";
  for (char p : puncts)
  {
    if (word.back() == p)
    {
      word.pop_back();
    }
  }

  const std::string extras = "(){}[]<>'";
  for (char ex : extras)
  {
    if (word.back() == ex)
    {
      word.pop_back();
    }
    if (word.front() == ex)
    {
      word.erase(word.begin());
    }
  }
}

bool psarev::checkLiter(const std::string& word)
{
  for (char c : word)
  {
    if (!isalpha(c))
    {
      return false;
    }
  }
  return true;
}

std::string psarev::getSpType(std::string& word)
{
  using storage_t = std::map< std::string, std::vector< std::string > >;

  std::string resType = "";
  storage_t rusEnds;

  rusEnds["noun"] = { "а", "ев", "ов", "ье", "иями", "ями", "ами", "еи", "ии", "и", "ией" };
  std::vector< const std::string > nSec = { "ем", "ам", "ом", "о", "у", "ах", "иях", "ях" };
  std::vector< const std::string > nThi = { "я", "ок", "мва", "яна", "ровать", "ег", "ги" };
  std::vector< const std::string > nFou = { "ий", "й", "иям", "ю", "ия", "ья", "ям", "ием" };
  std::vector< const std::string > nFif = { "ы", "ь", "ию", "ью", "га", "сть", "сти", "ей", "ой" };
  rusEnds["noun"].insert(rusEnds["noun"].end(), nSec.begin(), nSec.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nThi.begin(), nThi.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFou.begin(), nFou.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFif.begin(), nFif.end());

  rusEnds["verb"] = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "уй" };
  std::vector< const std::string > vSec = { "ено", "ят", "ует", "уют", "ит", "ыт", "ены", "ить" };
  std::vector< const std::string > vThi = { "на", "ете", "йте", "ли", "й", "л", "ем", "н", "ло" };
  std::vector< const std::string > vFou = { "им", "ым", "ен", "ило", "ыло", "ть", "ешь", "нно", "ет" };
  std::vector< const std::string > vFif = { "ыть", "ишь", "ую", "ют", "ны", "ю", "ла", "ил", "ыл" };
  rusEnds["verb"].insert(rusEnds["verb"].end(), vSec.begin(), vSec.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vThi.begin(), vThi.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFou.begin(), vFou.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFif.begin(), vFif.end());

  rusEnds["adjective"] = { "ее", "ие", "ые", "ое", "ими", "ыми", "ей", "ий", "ый", "ой" };
  std::vector< const std::string > aSec = { "его", "ого", "ему", "ому", "их", "ых", "ую", "юю" };
  std::vector< const std::string > aThi = { "ая", "яя", "ою", "ею", "ем", "им", "ым", "ом" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aSec.begin(), aSec.end());
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aThi.begin(), aThi.end());

  rusEnds["adverb"] = { "чно", "еко", "око", "имо", "мно", "жно", "жко", "ело", "тно" };
  std::vector< const std::string > dSec = { "здо", "зко", "шо", "хо", "но", "льно" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), dSec.begin(), dSec.end());

  rusEnds["numeric"] = { "много", "еро", "вое", "рое", "еро", "сти", "двух", "рех", "еми" };
  std::vector< const std::string > uSec = { "дного", "сот", "сто", "ста", "тысяча", "тысячи" };
  std::vector< const std::string > uThi = { "мью", "тью", "одним", "умя", "тью", "мя", "тью" };
  std::vector< const std::string > uFou = { "три", "одна", "яти", "ьми", "ати", "две" };
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uSec.begin(), uSec.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uThi.begin(), uThi.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uFou.begin(), uFou.end());

  rusEnds["conjuct"] = { "более", "менее", "очень", "крайне", "когда", "однако", "если" };
  std::vector< const std::string > cSec = { "зато", "что", "или", "потом", "это", "того", "тоже" };
  std::vector< const std::string > cThi = { "и", "да", "кабы", "коли", "ничем", "чем", "также" };
  std::vector< const std::string > cFou = { "словно", "ежели", "хотя", "как", "так", "чтоб" };
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cSec.begin(), cSec.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cThi.begin(), cThi.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cFou.begin(), cFou.end());

  rusEnds["prepos"] = { "в", "на", "slovo", "из", "за", "у", "от", "с", "об", "к", "перед" };
  std::vector< const std::string > pSec = { "из-под", "для", "про", "до", "о", "вокруг", "при" };
  std::vector< const std::string > pThi = { "возле", "из-за", "без", "между", "под", "около" };
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pSec.begin(), pSec.end());
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pThi.begin(), pThi.end());

  for (auto iter = rusEnds["prepos"].begin(); iter != rusEnds["prepos"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Prepos";
    }
  }
  for (auto iter = rusEnds["conjuct"].begin(); iter != rusEnds["conjuct"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Conjuct";
    }
  }
  for (auto iter = rusEnds["numeric"].begin(); iter != rusEnds["numeric"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Numeric";
    }
  }

  std::vector< std::string > spTypes = { "noun", "verb", "adjective", "adverb", "numeric" };
  for (auto iter = spTypes.begin(); iter != spTypes.end(); ++iter)
  {
    for (size_t i = 0; i <= 6; i++)
    {
      if (checkType(word, i, rusEnds[*iter]))
      {
        return *iter;
      }
    }
  }

  return resType;
}

bool psarev::checkType(std::string& word, size_t& endSize, std::vector< std::string >& ends)
{
  std::string endL = word.substr(word.length() - endSize);
  for (auto iter = ends.begin(); iter != ends.end(); ++iter)
  {
    if (endL == *iter)
    {
      return true;
    }
  }
  return false;
}

void psarev::outDepot(std::string dest, std::ofstream& out, std::map< std::string, storage_t >& depot)
{
  for (auto storage : depot)
  {
    out.open(dest + "\\" + storage.first + ".txt");
    if (out.is_open())
    {
      for (auto iter : storage.second)
      {
        size_t len = (iter.second).size();
        for (size_t i = 0; i < len; i++)
        {
          out << iter.second[i] << " ";
        }
      }
    }
    out.close();
  }
}

int psarev::letToSound(int let, bool& softFact)
{
  const std::string softMakers = "ёйеячищюь";
  const std::string notSoftMakers = "цукнгшзхъфывапролджэсмтб";
  for (int l : softMakers)
  {
    if (l == let)
    {
      softFact = true;
      if (l == -11887)
      {
        return -12098;
      }
      else if (l == -12103)
      {
        return -12103;
      }
      else if (l == -11889)
      {
        return -12112;
      }
      else if (l == -11897)
      {
        return -11897;
      }
      else if (l == -12104)
      {
        return -12104;
      }
      else if (l == -11895)
      {
        return -11895;
      }
      else if (l == -11890)
      {
        return -11901;
      }
    }
  }

  for (int l : notSoftMakers)
  {
    if (l == let)
    {
      softFact = false;
      if (l == -11898)
      {
        return -11898;
      }
      else if (l == -11901)
      {
        return -11901;
      }
      else if (l == -12102)
      {
        return -12102;
      }
      else if (l == -12099)
      {
        return -12099;
      }
      else if (l == -12109)
      {
        return -12102;
      }
      else if (l == -11896)
      {
        return -11896;
      }
      else if (l == -12105)
      {
        return -11903;
      }
      else if (l == -11899)
      {
        return -11899;
      }
      else if (l == -11900)
      {
        return -11900;
      }
      else if (l == -11893)
      {
        return -11893;
      }
      else if (l == -12110)
      {
        return -12110;
      }
      else if (l == -12112)
      {
        return -12112;
      }
      else if (l == -12097)
      {
        return -12097;
      }
      else if (l == -11904)
      {
        return -11904;
      }
      else if (l == -12098)
      {
        return -12098;
      }
      else if (l == -12101)
      {
        return -12101;
      }
      else if (l == -12108)
      {
        return -11902;
      }
      else if (l == -12106)
      {
        return -11896;
      }
      else if (l == -11891)
      {
        return -11891;
      }
      else if (l == -11903)
      {
        return -11903;
      }
      else if (l == -12100)
      {
        return -12100;
      }
      else if (l == -11902)
      {
        return -11902;
      }
      else if (l == -12111)
      {
        return -12097;
      }
    }
  }
  return ' ';
}

bool psarev::printSound(std::ostream& out, int sound, bool softFact)
{
  const std::string vowel = "уыаоэи";
  for (int l : vowel)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - гласный";
      if (l == -12098 && softFact)
      {
        out << " ,ударный";
      }
      out << '\n';
      return true;
    }
  }

  const std::string deafNPair = "хцчщ";
  const std::string deafPair = "кшфпст";
  const std::string voicedNPair = "йнрмл";
  const std::string voicedPair = "гзвдж";
  for (int l : deafNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой непарный";
      if ((softFact && l == -11899) || (l != -11899))
      {
        out << " ,мягкий";
        if (l == -11899)
        {
          out << " парный";
        }
        else
        {
          out << " непарный";
        }
      }
      else if (!softFact && l == -11899)
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : deafPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой парный";
      if (softFact && l != -11896)
      {
        out << " ,мягкий";
        if (l == -11896)
        {
          out << " непарный";
        }
        else
        {
          out << " парный";
        }
      }
      else
      {
        if (l == -11896)
        {
          out << " ,твердый непарный";
        }
        else
        {
          out << " ,твердый парный";
        }
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий непарный";
      if (l == -12103)
      {
        out << " ,мягкий непарный";
      }
      else if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий парный";
      if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  return false;
}