#include "bot.hpp"

#include <fstream>
#define FILE_NAME "values"

int main (void) {
	ifstream fich;
	fich.open(FILE_NAME);
  Bot BOT (&fich);
  fich.close();
  while (1) {
  	BOT.exe();
  	BOT.modifyEnvironment();
  }
} 