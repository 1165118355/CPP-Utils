///////////////////////////////
//	this class is a Xml in c++.
//	xml类，可以用来创建或者是解析xml文件
//	《xml类》
//	2018年8月13日 20:13:28
//	by	水华宝箱
#ifndef _SDL2_XML_H_BOX
#define _SDL2_XML_H_BOX

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

namespace WaterBox
{
	class SDL2_Xml
	{
	public:
		///	\breif	创建一个空的xml节点
		static SDL2_Xml *create();

		///	\breif	创建一个xml节点(如果mode=0 name就是创建一个xml节点，如果mode=1, name就是加载一个xml节点)
		static SDL2_Xml *create(std::string name);

		///	\brief	创建一个Xml节点并设置他的父节点
		static SDL2_Xml *create(std::string name, SDL2_Xml *parent);

		///	\brief	删除该结点（他会删除这个节点下所有的子结点）
		~SDL2_Xml();

		///	\brief	记载一个xml文件，path表示路径加名字
		int load(std::string path);

		///	\brief	保存一个xml文件，path表示路径加名字
		int save(std::string path);

		///	\brief	添加或删除子结点
		int addChild(SDL2_Xml *child);
		int removeChild(std::string name);

		///	\brief	获取子结点(根据index)
		SDL2_Xml *getChild(int num);

		///	\breif	获取当前节点总共的子节点数量
		int getNumChild();

		///	\brief	设置当前节点的名字
		void setName(std::string name);
		std::string getName();

		///	\brief	获取当前节点的父亲
		SDL2_Xml *getParent();

		///	\brief	设置当前节点的标签（如果没有找到该标签会自动添加该标签并设置它）
		int setTag(std::string name, std::string data);
		int setTag(std::string name, int data);
		int setTag(std::string name, float data);
		int setTag(std::string name, double data);
		std::string getTag(std::string name);
		void addTag(std::string name, std::string data);

		///	\brief	设置该节点的数据（他是一个字符串）
		void setData(std::string data);
		std::string getData();

		///	\brief	将一个字符串解析到xml实例
		void parse(std::string parseStr);
		std::string getTree();

		///	\brief	获取当前节点的层级
		int getHierarchy();

		///	\brief	清理该结点的信息
		void clear(int child = 0);


	private:
		enum
		{
			NONE,
			INPUT_OTHER,
			INPUT_NAME,
			INPUT_TAG_NAME,
			INPUT_TAG_DATA,
			INPUT_DATA
		};

		//	优雅的构造函数
		SDL2_Xml();

		///	\brief	将一个字符串解析到xml实例 (他是用来做递归的)
		bool parse(std::string parseStr, int &nowSub, SDL2_Xml *xmlNode);

		//	写， 将child中的信息写入file
		void writeTraverseChild(std::string &file, SDL2_Xml *xmlNode);

		//	设置父结点
		int setParent(SDL2_Xml *parent);

		//	设置层级
		void setHierarchy(int hierarchy);

		//	排序层级结构
		void sortHierarchy();

		//	获取所有的Tag
		std::map<std::string, std::string> *getAllTag();
	private:
		std::string							m_Name;				//	保存名字
		std::map<std::string, std::string>	m_Tag;				//	保存标签
		std::string							m_Data;				//	保存数据
		std::vector<SDL2_Xml *>				m_Child;			//	保存孩子
		std::string							m_Buffer;			//	缓存（用于打印调试）
		SDL2_Xml*							m_Parent;			//	保存父亲
		int									m_Hierarchy;		//	保存层级
		SDL2_Xml*							m_Self;				//	保存自己
	};
}
#endif // !_SDL2_XML_H_BOX
