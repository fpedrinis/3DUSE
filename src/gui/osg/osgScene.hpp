// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

////////////////////////////////////////////////////////////////////////////////
#ifndef __OSGSCENE_HPP__
#define __OSGSCENE_HPP__
////////////////////////////////////////////////////////////////////////////////
/// Tools for osg tree
///
/// osg scene design :
///
/// root - OsgScene instance           osg::Group - root
///                                            |
/// effect                             osg::Group - effect
///                                            |
/// layers                      -------osg::Group - layers-------
///                             |                               |
/// layer child         osg::Switch - layer0        osg::Switch - layer1
///                                     |
/// LODs                   ------------osg::Group - LODs
///                        |                   |
/// LOD child     osg::Switch - LOD0   osg::Switch - LOD1    ...
///                        |                   |
/// Tiles         osg::Group - Tiles   osg::Group - Tiles   ...
///                     |           |
/// Tile child  osg::Group - Tile0  osg::Group - Tile1 ...
///
////////////////////////////////////////////////////////////////////////////////
#include "libcitygml/URI.hpp"
#include "libcitygml/utils/tile.hpp"
#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <QDateTime>
#include <osg/Geometry>
#include <osg/TextureCubeMap>
#include "osgCityGML.hpp"
#include "osgInfo.hpp"

////////////////////////////////////////////////////////////////////////////////
class OsgScene : public osg::Group
{
public:
    OsgScene();

    /// Init osg scene basic structure
    void init();

    /// \brief addTile Add a tile in a layer of the osg scene
    /// \param uriLayer URI pointing to the layer
    /// \param tile Tile to add
    void addTile(const vcity::URI& uriLayer, const vcity::Tile& tile);

    /// \brief setTileName Set the name of a tile
    /// \param uriTile URI pointing to the tile
    /// \param name Tile name
    void setTileName(const vcity::URI& uriTile, const std::string& name);

    /// \brief deleteTile Delete a tile in the osg scene
    /// \param uriTile URI pointing to the tile
    void deleteTile(const vcity::URI& uriTile);

    /// \brief addAssimpNode Add a node in a layer of the osg scene
    /// \param uriLayer URI pointing to the layer
    /// \param node Node to add
    void addAssimpNode(const vcity::URI& uriLayer, const osg::ref_ptr<osg::Node> node);

    /// \brief setAssimpNodeName Set the name of an assimpNode
    /// \param uri URI pointing to the assimpNode
    /// \param name AssimpNode name
    void setAssimpNodeName(const vcity::URI& uri, const std::string& name);

    /// \brief deleteAssimpNode Delete an assimpNode in the osg scene
    /// \param uri URI pointing to the assimpNode
    void deleteAssimpNode(const vcity::URI& uri);

    void addMntAscNode(const vcity::URI& uriLayer, const osg::ref_ptr<osg::Node> node);
    void addLasNode(const vcity::URI& uriLayer, const osg::ref_ptr<osg::Node> node);
    void addShpNode(const vcity::URI& uriLayer, const osg::ref_ptr<osg::Node> node);

    /// \brief addLayer Add a layer to the osg scene
    /// \param name Layer name
    void addLayer(const std::string& name);

    /// \brief setLayerName Set the name of a layer in the osg scene
    /// \param uriLayer URI pointing to the layer
    /// \param name Layer name
    void setLayerName(const vcity::URI& uriLayer, const std::string& name);

    /// \brief deleteLayer Delete a layer in the osg scene
    /// \param uriLayer URI pointing to the layer
    void deleteLayer(const vcity::URI& uriLayer);

    /// \brief deleteNode Delete a node in the osg scene
    /// \param uri URI pointing to the node
    void deleteNode(const vcity::URI& uri);

    /// Update grid depending on dataprofile
    void updateGrid();

    /// Enable / disable osg shadows
    void setShadow(bool shadow);

    /// Enable / disable skybox
    void toggleSkybox(bool skybox);

    /// Set date for temporal use, use -4000 as year to disable temporal
    void setDate(const QDateTime& date);

    /// Set Color (yellow or black, depending on sunlight)
    void changePolyColor(std::map<std::string, bool> *sunlightInfo);

    /// reset osg scene
    void reset();

    /// force
    void forceLOD(int lod);

    /// Show or hide a node by ptr
    void showNode(osg::ref_ptr<osg::Node> node, bool show);

    /// Show or hide a node by uri
    void showNode(const vcity::URI& uri, bool show);

    /// \brief centerOn Home camera on a node
    /// \param uri URI pointing to the node
    void centerOn(const vcity::URI& uri);

    void dump(std::ostream& out = std::cout, osg::ref_ptr<osg::Node> node = NULL, int depth = 0);

    /// OSG optimizer test (destroy tree topology and picking does not work after)
    void optim();

    osg::ref_ptr<osg::Node> buildGrid(const osg::Vec3& bbox_lower, const osg::Vec3& bbox_upper, const osg::Vec2& step, const osg::Vec3& offset, const osg::Vec2& tileOffset);
    osg::ref_ptr<osg::Geode> buildBBox(osg::Vec3 lowerBound, osg::Vec3 upperBound);

    /// \brief getNode Get a node in the osg scene with a URI
    /// \param uri URI pointing to the wanted node
    /// \return Node
    osg::ref_ptr<osg::Node> getNode(const vcity::URI& uri);

    /// Insert info bubble for a node
    osg::ref_ptr<osg::Node> createInfoBubble(osg::ref_ptr<osg::Node> node);


    /// \brief Fill layer with all info objects
    /// \param URI pointing to the appropriate layer
    /// \param stdd:vector with all infos
    void initInfo(const vcity::URI& uriLayer, std::vector<osgInfo*> info);

    /// \brief Fill switches LOD structure with all infos
    /// \param osg::ref_ptr<osg::Switch> pointer to switch root node
    /// \param stdd:vector with all infos
    void fillSwitches(osg::ref_ptr<osg::Switch> switchRoot, std::vector<osgInfo*> v_info);

    /// \brief Update is_requested members of all infos
    /// \param const QString& word from the filter search bar
    void filterInfo(const QString& filter);

public:
    /// Build osg node from CityGML data
    osg::ref_ptr<osg::Node> buildTile(const vcity::URI& uri, const vcity::Tile& tile);
    void buildCityObject(const vcity::URI& uri, osg::ref_ptr<osg::Group> nodeOsg, citygml::CityObject* node, ReaderOsgCityGML& reader, int depth = 0, osg::ref_ptr<osg::Group> nodeVersion = NULL, osg::ref_ptr<osg::Group> nodeWorkspace = NULL);

    bool m_shadow;                          ///< flag to use osg shadows or not
    osg::Vec4 m_shadowVec;

    osg::ref_ptr<osg::Group> m_layers;      ///< Group holding all layers, and below, all tiles, ...

    osg::ref_ptr<osg::Group> m_effectNone;
    osg::ref_ptr<osg::Group> m_effectShadow;

    osg::Node* m_skybox;

private:
    void setDateRec(const QDateTime& date, osg::ref_ptr<osg::Node> node);
    void changePolyColorRec(osg::ref_ptr<osg::Node> node, std::map<std::string, bool> *sunlightInfo);

    osg::TextureCubeMap* readCubeMap();
};
////////////////////////////////////////////////////////////////////////////////
/// \brief osgSceneBuild will create an osg tree (for rendering with osg) from a tile
/// \param tile : input tile
/// \return The osg scene tree
//osg::ref_ptr<osg::Node> osgSceneBuild(const Tile& tile);
////////////////////////////////////////////////////////////////////////////////
/// \brief osgSceneDeleteNode will delete the node name in osg tree root
/// \param root : osg tree
/// \param name : node to delete
//void osgSceneDeleteNode(osg::ref_ptr<osg::Group> root, const std::string& name);
////////////////////////////////////////////////////////////////////////////////
/// \brief osgSceneSetShadow
/// \param root : osg tree
/// \param shadow : bool to set or unset shadow effect
//void osgSceneSetShadow(osg::ref_ptr<osg::Group> root, bool shadow);
////////////////////////////////////////////////////////////////////////////////
#endif // __OSGSCENE_HPP__
