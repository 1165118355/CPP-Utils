#include "SDL2_Xml.h"
#pragma warning(disable:4996)

using namespace WaterBox;

WaterBox::SDL2_Xml::SDL2_Xml()
{
	m_Name = "";
	m_Parent = nullptr;
	m_Hierarchy=0;
}

WaterBox::SDL2_Xml::~SDL2_Xml()
{
	for (int i=0; i<m_Child.size(); ++i)
	{
		delete m_Child[i];
	}
}

void WaterBox::SDL2_Xml::writeTraverseChild(std::string & file, SDL2_Xml * xmlNode)
{
	for (int i=0; i<xmlNode->getHierarchy(); ++i)
	{
		file += "\t";
	}
	//	开始
	file += std::string("<") + xmlNode->getName();

	//	添加标签
	std::map<std::string, std::string> *nowTag = xmlNode->getAllTag();
	for (std::map<std::string, std::string>::iterator it = nowTag->begin(); it != nowTag->end(); ++it)
	{
		file += std::string(" ") + it->first + std::string("=\"") + it->second + std::string("\"");
	}
	file += ">\n";


	//	数据
	if (!xmlNode->getData().empty())
	{
		for (int i = 0; i<xmlNode->getHierarchy(); ++i)
		{
			file += "\t";
		}
		file += std::string("\t") + std::string(xmlNode->getData().c_str()) + std::string("\n");
	}

	//	子结点继续遍历
	for (int i = 0; i<xmlNode->getNumChild(); ++i)
	{
		SDL2_Xml *childXml = xmlNode->getChild(i);
		if (!childXml)
		{	
			continue;
		}
		writeTraverseChild(file, childXml);
	}

	for (int i = 0; i<xmlNode->getHierarchy(); ++i)
	{
		file += "\t";
	}
	//	结束
	file += std::string("</") + xmlNode->getName() + std::string(">\n");
}

SDL2_Xml * WaterBox::SDL2_Xml::create()
{
	SDL2_Xml *xml = new SDL2_Xml();
	xml->m_Self = xml;
	return xml;
}

SDL2_Xml * WaterBox::SDL2_Xml::create(std::string name)
{
	SDL2_Xml *xml = SDL2_Xml::create();
	xml->setName(name);
	return xml;
}

SDL2_Xml * WaterBox::SDL2_Xml::create(std::string name, SDL2_Xml * parent)
{
	SDL2_Xml *xml = SDL2_Xml::create();
	xml->setName(name);
	xml->setParent(parent);
	return xml;
}

int WaterBox::SDL2_Xml::load(std::string path)
{
	std::fstream file(path, std::ios::in);
	if (!file.is_open())				
	{
		std::cout << "path error\n";
		file.close();
		return -1;
	}
	std::string parseStr;
	char buffer[233];
	while(!file.eof())
	{
		file.read(buffer, 233);
		parseStr += buffer;
	}
	file.close();
	parse(parseStr); 
	save("tempCheck.xml");
	return 0;
}

int WaterBox::SDL2_Xml::save(std::string path)
{
	std::fstream file(path, std::ios::out);

	//	通过递归的方式遍历所有的节点，并将节点 的信息写入file
	std::string fileStr;
	writeTraverseChild(fileStr, m_Self);
	file << fileStr.c_str();
	file.close();
	return 0;
}

int WaterBox::SDL2_Xml::addChild(SDL2_Xml * child)
{
	if (child == NULL)
	{
		return -1;
	}
	child->setParent(m_Self);
	child->sortHierarchy();
	m_Child.push_back(child);
	return 0;
}

int WaterBox::SDL2_Xml::removeChild(std::string name)
{
	for (int i=0; i<m_Child.size(); ++i)
	{
		if (!strcmp(name.c_str(), m_Child[i]->getName().c_str()))
		{
			m_Child.erase(m_Child.begin()+i);
		}
	}
	return 0;
}

SDL2_Xml *WaterBox::SDL2_Xml::getChild(int num)
{
	if (m_Child.size() > num)
	{
		return m_Child[num];
	}
	return nullptr;
}

int WaterBox::SDL2_Xml::getNumChild()
{
	return m_Child.size();
}

void WaterBox::SDL2_Xml::setName(std::string name)
{
	m_Name = name;
}

std::string WaterBox::SDL2_Xml::getName()
{
	return m_Name;
}

SDL2_Xml * WaterBox::SDL2_Xml::getParent()
{
	return m_Parent;
}

int WaterBox::SDL2_Xml::setTag(std::string name, std::string data)
{
	std::map<std::string, std::string>::iterator it = m_Tag.find(name);
	if (it == m_Tag.end())
	{
		addTag(name, data);
		return -1;
	}
	it->second = data;
	return 1;
}

int WaterBox::SDL2_Xml::setTag(std::string name, int data)
{
	char ch[30];
	sprintf(ch, "%d", data);
	return setTag(name, ch);
}

int WaterBox::SDL2_Xml::setTag(std::string name, float data)
{
	char ch[30];
	sprintf(ch, "%f", data);
	return setTag(name, ch);
}

int WaterBox::SDL2_Xml::setTag(std::string name, double data)
{
	char ch[30];
	sprintf(ch, "%f", data);
	return setTag(name, ch);
}

std::string WaterBox::SDL2_Xml::getTag(std::string name)
{
	std::map<std::string, std::string>::iterator it = m_Tag.find(name);
	if (it == m_Tag.end())
	{
		return "";
	}
	return it->second;
}

void WaterBox::SDL2_Xml::addTag(std::string name, std::string data)
{
	std::pair<std::string, std::string> pa(name, data);
	m_Tag.insert(pa);
}

void WaterBox::SDL2_Xml::setData(std::string data)
{
	m_Data = data;
}

std::string WaterBox::SDL2_Xml::getData()
{
	return m_Data;
}

void WaterBox::SDL2_Xml::parse(std::string parseStr)
{
	int i = 0;
	parse(parseStr, i, m_Self);
}

std::string WaterBox::SDL2_Xml::getTree()
{
	//	写， 将child中的信息写入file
	std::string file;
	writeTraverseChild(file, m_Self);
	return file;
}

bool WaterBox::SDL2_Xml::parse(std::string parseStr, int &nowSub, SDL2_Xml * xmlNode)
{

	int flag = INPUT_OTHER;
	char buffer[2] = "";
	char bufferTemp[2] = "";
	std::string nodeBuffer;
	std::string name;
	std::string tagName;
	std::string tagData;
	std::string data;

	//	检查前标记，例如：<xyz tag="233">
	while (nowSub <  parseStr.size() && flag != INPUT_DATA)
	{
		buffer[0] = parseStr[nowSub];
		nowSub++;
		switch (buffer[0])
		{
		case '<':
			buffer[0] = parseStr[nowSub];
			if (buffer[0] != '/')
			{
				flag = INPUT_NAME;
			}
			else
			{
				//	上来就检查到这是一个结束标记，我甚至不知道该怎么办了，姑且先返回一个空吧
				return false;
			}
			break;
		case '>':
			if (flag == INPUT_NAME)
			{
				xmlNode->setName(name);
			}
			else if (flag == INPUT_TAG_DATA)
			{
				if ((!tagName.empty()) && (!tagData.empty()))
				{
					if (tagData[tagData.size() - 1] == '"')
					{
						tagData.resize(tagData.size() - 1);
					}
					xmlNode->addTag(tagName, tagData);
				}
			}
			flag = INPUT_DATA;
			break;
		case '=':
			if (flag == INPUT_TAG_NAME)
			{
				flag = INPUT_TAG_DATA;
				bufferTemp[0] = parseStr[nowSub];
				if (bufferTemp[0] == '"')
				{
					nowSub++;
				}
			}
			else
			{
				//	当出现了不应该出现的东西时，我甚至不知道该怎么办，只好姑且先给你个空试试
				return false;
			}
			break;
		case ' ':
			if (flag == INPUT_NAME)
			{
				flag = INPUT_TAG_NAME;
				xmlNode->setName(name);
				name = "";
			}
			else if (flag == INPUT_TAG_DATA)
			{
				flag = INPUT_TAG_NAME;
				if ((!tagName.empty()) && (!tagData.empty()))
				{
					if (tagData[tagData.size() - 1] == '"')
					{
						tagData.resize(tagData.size() - 1);
					}
					xmlNode->addTag(tagName, tagData);
					tagName = "";
					tagData = "";
				}
			}
			break;
		default:
			switch (flag)
			{
			case INPUT_NAME:
				name += buffer;
				break;
			case INPUT_TAG_NAME:
				tagName += buffer;
				break;
			case INPUT_TAG_DATA:
				tagData += buffer;
				break;
			}
			break;
		}
		nodeBuffer += buffer;
	}

	//	检查Data咯，例如：xxooxxoo
	while (nowSub < parseStr.size()  && flag != NONE)
	{
		buffer[0] = parseStr[nowSub];
		buffer[1] = '\0';
		if (buffer[0] == '<')
		{
			flag = NONE;
			break;
		}
		if (buffer[0] != '\n' && buffer[0] != '\t')
		{
			nodeBuffer += buffer;
			data += buffer;
		}
		nowSub++;
	}
	xmlNode->setData(data);

	//	检查后标记，例如：</xyz>
	while (nowSub < parseStr.size())
	{
		buffer[0] = parseStr[nowSub];
		nowSub++;
		if (buffer[0] == '<')
		{
			buffer[0] = parseStr[nowSub];
			if (buffer[0] == '/')
			{
				nodeBuffer += "</";
				while (nowSub < parseStr.size())
				{
					buffer[0] = parseStr[nowSub];
					++nowSub;
					buffer[1] = '\0';
					nodeBuffer += buffer;
					if (buffer[0] == '>')
					{
						return true;
					}
				}
			}
			else
			{
				--nowSub;
				SDL2_Xml *childXml = SDL2_Xml::create();
				if (parse(parseStr, nowSub, childXml))
				{
					xmlNode->addChild(childXml);
				}
				else
				{
					delete childXml;
				}
			}
		}
	}
	return true;
}

int WaterBox::SDL2_Xml::getHierarchy()
{
	return m_Hierarchy;
}

void WaterBox::SDL2_Xml::clear(int child /*=0*/)
{
	m_Name = "";
	m_Tag.clear();
	m_Parent = nullptr;
	if(1 == child)
	{
		for (int i=0; i<this->getNumChild(); ++i)
		{
			delete this->getChild(i);
		}
		m_Child.clear();
	}
}

std::map<std::string, std::string> *WaterBox::SDL2_Xml::getAllTag()
{
	return &m_Tag;
}

int WaterBox::SDL2_Xml::setParent(SDL2_Xml * parent)
{
	if (parent != NULL)
	{
		m_Parent = parent;
	}
	else
	{
		return -1;
	}
	return 0;
}

void WaterBox::SDL2_Xml::setHierarchy(int hierarchy)
{
	m_Hierarchy = hierarchy;
}

void WaterBox::SDL2_Xml::sortHierarchy()
{
	if (m_Parent != NULL)
	{
		m_Hierarchy = m_Parent->getHierarchy() + 1;
	}
	for (int i=0; i<m_Child.size(); ++i)
	{
		m_Child[i]->sortHierarchy();
	}
}
