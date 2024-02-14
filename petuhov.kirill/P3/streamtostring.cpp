#include "streamtostring.hpp"

char * petuhov::streamToString(std::istream & input)
{
  char sym = 0;
  size_t stringBufferSize = 0;
  char * string = nullptr;
  char * stringBuffer = nullptr;

  input >> std::noskipws;

  while (input >> sym && sym != '\n')
  {
    if (!input)
    {
      delete[] string;
      throw std::logic_error("Error reading input");
    }
    try
    {
      stringBuffer = new char[stringBufferSize + 10];
    }
    catch (std::bad_alloc & e)
    {
      throw;
    }

    if (string != nullptr)
    {
      for (size_t i = 0; i < stringBufferSize; ++i) {
        stringBuffer[i] = string[i];
      }
      delete[] string;
    }
    stringBuffer[stringBufferSize++] = sym;
    stringBuffer[stringBufferSize] = '\0';
    string = stringBuffer;
  }

  if (string == nullptr)
  {
    throw std::logic_error("Empty input string");
  }
  return string;
}