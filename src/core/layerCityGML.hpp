// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

////////////////////////////////////////////////////////////////////////////////
#ifndef __LAYERCITYGML_HPP__
#define __LAYERCITYGML_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "abstractlayer.hpp"
#include "tile.hpp"

#include "URI.hpp"
#include <string>
#include <memory>
////////////////////////////////////////////////////////////////////////////////
namespace vcity
{
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief LayerCityGML class : it holds all the tiles
    /// A layer contains a set of tiles. Tiles are identified by a name and a position on a grid.
    /// Grid info is in the data profile
    class LayerCityGML : public abstractLayer
    {
    public:
        /// \brief Layer Build empty layer
        /// \param name Layer name
        LayerCityGML(const std::string& name);

        virtual ~LayerCityGML() override;

        /// \brief addTile Add a tile in a layer
        /// \param tile The tile to add
        void addTile(Tile* tile);

        /// \brief getTile Get a tile
        /// \param uri URI pointing to the tile
        /// \return The tile
        Tile* getTile(const URI& uri);

        /// \brief getTiles Get all tiles in the layer
        /// \return A vector of Tile
        std::vector<Tile*>& getTiles();

        /// \brief getTiles Get all tiles in the layer (const)
        /// \return A const vector of Tile
        const std::vector<Tile*>& getTiles() const;

        /// \brief deleteTile Delete a tile in a layer
        /// \param uri URI pointing to the tile
        void deleteTile(const URI& uri);

        /// \brief getCityObjectNode Get a CityGML node
        /// \param uri URI pointing to the CityGML node
        /// \return Ptr to CityGML node or nullptr
        citygml::CityObject* getCityObjectNode(const URI& uri, bool inPickingMode = false);

        /// Get layer type as string
        const std::string getType() const override;

        /// Get Layer URI
        URI getURI() const override;

        void dump() override;

    private:
        std::vector<Tile*> m_tiles;     ///< Tiles
    };
    ////////////////////////////////////////////////////////////////////////////////
    typedef std::shared_ptr<LayerCityGML> LayerCityGMLPtr;
    ////////////////////////////////////////////////////////////////////////////////
} // namespace vcity
////////////////////////////////////////////////////////////////////////////////
#endif // __LAYERCITYGML_HPP__
