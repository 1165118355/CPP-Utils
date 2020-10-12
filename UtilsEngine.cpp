#include "UtilsEngine.h"
#include <SpaceApp.h>
#include <SpaceInterpreter.h>
#include <SpacePlayers.h>
#include <SpaceEditor.h>
#include <SpaceGame.h>

Space::NodePtr UtilsEngine::createNode(int type)
{
	Space::NodePtr node;
	switch (type)
	{
	case Space::Node::OBJECT_MESH_STATIC:
	{
		Space::ObjectMeshStaticPtr obj = Space::ObjectMeshStatic::create("");
		obj->release();
		node = obj->getNode();
	}
	break;
	case Space::Node::OBJECT_MESH_DYNAMIC:
	{
		Space::ObjectMeshDynamicPtr obj = Space::ObjectMeshDynamic::create();
		obj->release();
		node = obj->getNode();
	}
	break;
	case Space::Node::OBJECT_MESH_SKINNED:
	{
		Space::ObjectMeshSkinnedPtr obj = Space::ObjectMeshSkinned::create("");
		obj->release();
		node = obj->getNode();
	}
	break;
	case Space::Node::DECAL_MESH:
	{
		Space::DecalMeshPtr obj = Space::DecalMesh::create(Space::MeshPtr(), 3, "decal_base");
		obj->release();
		node = obj->getNode();
	}
	break;
	}
	return node;
}

Space::MeshPtr UtilsEngine::getMesh(Space::NodePtr node)
{
	Space::MeshPtr mesh = Space::Mesh::create();
	int type = node->getType();
	switch (type)
	{
	case Space::Node::OBJECT_MESH_STATIC:
	{
		Space::ObjectMeshStaticPtr obj = Space::ObjectMeshStatic::cast(node);
		obj->getMesh(mesh);
	}
	break;
	case Space::Node::OBJECT_MESH_DYNAMIC:
	{
		Space::ObjectMeshDynamicPtr obj = Space::ObjectMeshDynamic::cast(node);
		obj->getMesh(mesh);
	}
	break;
	case Space::Node::OBJECT_MESH_SKINNED:
	{
		Space::ObjectMeshSkinnedPtr obj = Space::ObjectMeshSkinned::cast(node);
		obj->getMesh(mesh);
	}
	break;
	case Space::Node::DECAL_MESH:
	{
		Space::DecalMeshPtr obj = Space::DecalMesh::cast(node);
		obj->getMesh(mesh);
	}
	break;
	}

	return mesh;
}

std::string UtilsEngine::getMeshName(Space::NodePtr node)
{
	std::string meshName;
	Space::MeshPtr mesh = Space::Mesh::create();
	int type = node->getType();
	switch (type)
	{
	case Space::Node::OBJECT_MESH_STATIC:
	{
		Space::ObjectMeshStaticPtr obj = Space::ObjectMeshStatic::cast(node);
		meshName = obj->getMeshName();
	}
	break;
	case Space::Node::OBJECT_MESH_DYNAMIC:
	{
		Space::ObjectMeshDynamicPtr obj = Space::ObjectMeshDynamic::cast(node);
		meshName = obj->getMeshName();
	}
	break;
	case Space::Node::OBJECT_MESH_SKINNED:
	{
		Space::ObjectMeshSkinnedPtr obj = Space::ObjectMeshSkinned::cast(node);
		meshName = obj->getMeshName();
	}
	break;
	case Space::Node::DECAL_MESH:
	{
		Space::DecalMeshPtr obj = Space::DecalMesh::cast(node);
		meshName = obj->getMeshName();
	}
	break;
	}

	return meshName;
}

void UtilsEngine::setMesh(Space::NodePtr node, Space::MeshPtr mesh, const char * meshName)
{
	int type = node->getType();
	switch (type)
	{
	case Space::Node::OBJECT_MESH_STATIC:
	{
		Space::ObjectMeshStaticPtr obj = Space::ObjectMeshStatic::cast(node);
		obj->setMesh(mesh);
		if (meshName)
		{
			obj->setMeshName(meshName);
		}
	}
	break;
	case Space::Node::OBJECT_MESH_DYNAMIC:
	{
		Space::ObjectMeshDynamicPtr obj = Space::ObjectMeshDynamic::cast(node);
		obj->setMesh(mesh);
		if (meshName)
		{
			obj->setMeshName(meshName);
		}
	}
	break;
	case Space::Node::OBJECT_MESH_SKINNED:
	{
		Space::ObjectMeshSkinnedPtr obj = Space::ObjectMeshSkinned::cast(node);
		obj->setMesh(mesh);
		if (meshName)
		{
			obj->setMeshName(meshName);
		}
	}
	break;
	case Space::Node::DECAL_MESH:
	{
		Space::DecalMeshPtr obj = Space::DecalMesh::cast(node);
		obj->setMesh(mesh);
		if (meshName)
		{
			obj->setMeshName(meshName);
		}
	}
	break;
	}

}

void UtilsEngine::setMaterial(Space::NodePtr node, const char * materialName, int surface)
{
	int type = node->getType();
	if (type >= Space::Node::OBJECT_BEGIN && type <= Space::Node::OBJECT_END)
	{
		Space::ObjectPtr obj = Space::Object::cast(node);
		if (surface == -1)
		{
			obj->setMaterial(materialName, "*");
		}
		else
		{
			obj->setMaterial(materialName, surface);
		}
	}
        else if (type >= Space::Node::DECAL_BEGIN && type <= Space::Node::DECAL_END)
	{
		Space::DecalPtr obj = Space::Decal::cast(node);
		obj->setMaterial(materialName);
	}
}

std::string UtilsEngine::getMaterialName(Space::NodePtr node, int surface)
{
	std::string materialName;
	int type = node->getType();
	if (type >= Space::Node::OBJECT_BEGIN && type <= Space::Node::OBJECT_END)
	{
		Space::ObjectPtr obj = Space::Object::cast(node);
		materialName = obj->getMaterial(surface)->getName();
	}
	else if (type >= Space::Node::DECAL_BEGIN && type <= Space::Node::DECAL_END)
	{
		Space::DecalPtr obj = Space::Decal::cast(node);
		materialName = obj->getMaterial()->getName();
	}
	return materialName;
}

std::string UtilsEngine::VaribleToString(Space::Variable varible)
{
	Space::XmlPtr xml = Space::Xml::create();
	std::string str;
	int type = varible.getType();
	switch (type)
	{
		case Space::Variable::INT:
			xml->setIntData(varible.getInt());
			break;
		case Space::Variable::LONG:
			xml->setLongData(varible.getLong());
			break;
		case Space::Variable::FLOAT:
			xml->setFloatData(varible.getFloat());
			break;
		case Space::Variable::DOUBLE:
			xml->setDoubleData(varible.getDouble());
			break;
		case Space::Variable::VEC2:
			xml->setVec2Data(varible.getVec2());
			break;
		case Space::Variable::VEC3:
			xml->setVec3Data(varible.getVec3());
			break;
		case Space::Variable::VEC4:
			xml->setVec4Data(varible.getVec4());
			break;
		case Space::Variable::DVEC2:
			xml->setDVec2Data(varible.getDVec2());
			break;
		case Space::Variable::DVEC3:
			xml->setDVec3Data(varible.getDVec3());
			break;
		case Space::Variable::DVEC4:
			xml->setDVec4Data(varible.getDVec4());
			break;
		case Space::Variable::IVEC2:
			xml->setIVec2Data(varible.getIVec2());
			break;
		case Space::Variable::IVEC3:
			xml->setIVec3Data(varible.getIVec3());
			break;
		case Space::Variable::IVEC4:
			xml->setIVec4Data(varible.getIVec4());
			break;
		case Space::Variable::MAT4:
			xml->setMat4Data(varible.getMat4());
			break;
		case Space::Variable::DMAT4:
			xml->setDMat4Data(varible.getDMat4());
			break;
		case Space::Variable::QUAT:
			xml->setQuatData(varible.getQuat());
			break;
		case Space::Variable::STRING:
			xml->setData(varible.getString());
			break;
		case Space::Variable::GUID:
			xml->setData(varible.getGUID().getString());
			break;
		case Space::Variable::USER_CLASS:
			break;
		case Space::Variable::EXTERN_CLASS:
			break;
	}
	str = xml->getData();
	return str;
}

Space::PlayerPtr UtilsEngine::getPlayer()
{
    Space::PlayerPtr player = Space::Editor::get()->getPlayer();
    if(!player)
    {
        player = Space::Game::get()->getPlayer();
    }
    return player;
}

Space::PropertyPtr UtilsEngine::findProperty(Space::NodePtr node, std::string findPropertyName, Space::NodePtr &outNode, bool isFindParent)
{
    if(!node)
    {
        return Space::PropertyPtr();
    }
    int numProperty = node->getNumProperties();
    for(int i=0; i<numProperty; ++i)
    {
        Space::PropertyPtr property = node->getProperty(i);
        if(property)
        {
            std::string propertyName = property->getName();
            if(findPropertyName == propertyName)
            {
                outNode = node;
                return property;
            }
        }
    }
    if(isFindParent)
    {
        Space::NodePtr parent = node->getParent();
        if(parent)
        {
            return findProperty(parent, findPropertyName, outNode, isFindParent);
        }
    }

    return Space::PropertyPtr();
}

bool UtilsEngine::isReference(Space::NodePtr node)
{
    Space::NodePtr possessor=node->getPossessor();
    return possessor.get();
}

Space::Math::ivec2 UtilsEngine::getScreenPosition(Space::Math::Vec3 worldPosition)
{
	Space::Math::ivec2 screenPos;
	getPlayer()->getScreenPosition(screenPos.x, screenPos.y, worldPosition);
	return screenPos;
}

void UtilsEngine::setMaterialState(Space::NodePtr node, const char *stateName, int state, int surface, bool setChild)
{
    Space::ObjectPtr obj = Space::Object::cast(node);
    if(obj)
    {
        if(surface == -1)
        {
            for(int i=0; i<obj->getNumSurfaces(); ++i)
            {
                setMaterialState(node, stateName, state, i, 0);
            }
        }
        else
        {
            if(surface < obj->getNumSurfaces())
            {
                obj->setMaterialState(stateName, state, surface);
            }
        }
    }
    if(setChild)
    {
        for(int i=0; i<node->getNumChildren(); ++i)
        {
            Space::NodePtr child = node->getChild(i);
            setMaterialState(child, stateName, state, surface, setChild);
        }
    }
}

Space::Math::Vec3 UtilsEngine::getScenePointByMouse(float distance)
{
    Space::PlayerPtr player = getPlayer();
    if(distance == -1)
    {
        distance = player->getZFar();
    }

    int x = Space::App::get()->getMouseX();
    int y = Space::App::get()->getMouseY();
    Space::Math::vec3 dir = player->getDirectionFromScreen(x, y);
    return Space::Math::Vec3(dir * distance);
}

bool UtilsEngine::getPlayerMouseDirection(Space::Math::Vec3& p0, Space::Math::Vec3& p1)
{
	Space::PlayerPtr player = Space::Editor::get()->getPlayer();
	if (player.get() == NULL)
		return false;

	int width = Space::App::get()->getWidth();
	int height = Space::App::get()->getHeight();

	int mouse_x = Space::App::get()->getMouseX();
	int mouse_y = Space::App::get()->getMouseY();
	Space::Math::mat4 projection = player->getProjection();
	Space::Math::Mat4 imodelview = player->getWorldTransform();

	projection.m00 *= float(height) / width;
	float x = -(float(mouse_x) / width * 2.0f - 1.0f + projection.m02) / projection.m00;
	float y = (float(mouse_y) / height * 2.0f - 1.0f + projection.m12) / projection.m11;
	if (projection.m32 == 0.0f)
	{
		p0 = imodelview * Space::Math::Vec3(-x, -y, -1.0f);
		p1 = imodelview * Space::Math::Vec3(-x, -y, 1.0f);
	}
	else
	{
		p0 = Space::Math::Vec3(imodelview.m03, imodelview.m13, imodelview.m23);
		p1 = imodelview * Space::Math::Vec3(x, y, 1.0f);
	}
	p1 = p0 - Space::Math::normalize(p1 - p0) * player->getZFar();
	return true;
}

