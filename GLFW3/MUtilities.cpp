#include "MUtilities.h"
#include <stdio.h>

namespace FileManager
{

std::string read(const char *fileName)
{
	FILE *fp;
	int res = fopen_s(&fp, fileName, "r");
	if (res) return std::string();
	fseek(fp, 0, SEEK_END);
	int len = ftell(fp);
	rewind(fp);
	char *tmp = (char *) malloc(sizeof(char) * (len+1));
	tmp[len] = '\0';
	fread(tmp, sizeof(char), len, fp);
	fclose(fp);
	std::string strs = tmp;
	free(tmp);
	return strs;
}

}