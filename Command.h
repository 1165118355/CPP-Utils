#pragma once
#include "Utils/DTSingleton.h"
#include <string>
#include <vector>

class Command: public DTSingleton<Command>
{
	friend class DTSingleton<Command>;
public:
    ~Command();
    void init(int argc, wchar_t *argv[]);
    void init(int argc, char *argv[]);

	std::string getValue(const char *command);
protected:
	Command();

	std::vector<std::pair<std::string, std::string>> m_Commands;
};

