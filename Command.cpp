#include "Command.h"
#include "Utils/UtilsString.h"


Command::Command()
{
}


Command::~Command()
{
}

void Command::init(int argc, wchar_t * argv[])
{
	m_Commands.clear();
	for (int i = 1; i<argc; ++i)
	{
		std::wstring wcommand = argv[i];
		std::string command = UtilsString::wstringToString(wcommand);
		if (argv[i][0] == L'-')
		{
			std::wstring wvalue = argv[i];
            if (++i < argc && argv[i][0] != L'-')
				wvalue = argv[i];
			std::string value = UtilsString::wstringToString(wvalue);
			m_Commands.push_back(std::pair<std::string, std::string>(command, value));
			printf("argv[%d]=%s  %s\n", i, command.c_str(), value.c_str());
		}
	}
}
void Command::init(int argc, char * argv[])
{
    m_Commands.clear();
    printf("init command = %d\n", argc);
	for (int i=1; i<argc; ++i)
	{
        if (argv[i][0] == '-')
        {
            std::string command = argv[i];
            std::string value = argv[i];
            if (++i < argc && argv[i][0] != '-')
				value = argv[i];
			m_Commands.push_back(std::pair<std::string, std::string>(argv[i - 1], value));
            printf("argv[%d]=%s  %s\n", i, command.c_str(), value.c_str());
		}
	}
}

std::string Command::getValue(const char * command)
{
	for (int i=0; i<m_Commands.size(); ++i)
	{
		auto sourceCommand = m_Commands[i];
		if (sourceCommand.first == command)
		{
			return sourceCommand.second;
		}
	}
	return std::string("");
}
