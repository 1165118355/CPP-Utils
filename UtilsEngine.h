////////////////////////////
//
//  Wirter: David.zhu
//  Date:   2020-04-27
//  brief:  xxx
//
#pragma once

#include <vector>
#include <SpaceObjects.h>
#include <SpaceNodes.h>
#include <SpacePlayers.h>
#include <SpaceDecals.h>

namespace UtilsEngine
{
	///	\brief	创建一个节点
	Space::NodePtr createNode(int type);

	///	\brief	获取Mehs(通用接口)
	Space::MeshPtr getMesh(Space::NodePtr node);
	std::string getMeshName(Space::NodePtr node);
	void setMesh(Space::NodePtr node, Space::MeshPtr mesh, const char *meshName = nullptr);

	///	\brief	给Node设置材质(通用接口)
	///	\pram	surface	指定的surface设置材质materialName, 如果surface=-1则为所有的surface赋予材质materialName
	void setMaterial(Space::NodePtr node, const char *materialName, int surface = -1);
	std::string getMaterialName(Space::NodePtr node, int surface=0);

    /// \brief  设置材质的状态
    void setMaterialState(Space::NodePtr node,const char *stateName, int state, int surface = -1, bool setChild=1);

	///	\brief	将Varible转换为字符串
    std::string VaribleToString(Space::Variable varible);

    /// \brief  获取相机（优先获取Editor相机）
    Space::PlayerPtr getPlayer();

    /// \brief  查找一个属性，
    Space::PropertyPtr findProperty(Space::NodePtr node, std::string findPropertyName, Space::NodePtr &outNode, bool isFindParent=false);

    /// \brief  判断Node是否被NodeReference等节点引用
    bool isReference(Space::NodePtr node);

	///	\brief	通过三维坐标获取屏幕坐标
	Space::Math::ivec2 getScreenPosition(Space::Math::Vec3 worldPosition);

    /// \brief  获取鼠标指向的三维射线坐标(用于射线检测)
    Space::Math::Vec3 getScenePointByMouse(float distance=-1);

    /// \brief  获取该点的投影坐标哦
    Space::Math::ivec2 projectionToScreenCoordinate(Space::Math::Vec3 position);


	bool getPlayerMouseDirection(Space::Math::Vec3& p0, Space::Math::Vec3& p1);

};

