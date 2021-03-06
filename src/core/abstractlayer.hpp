// Copyright University of Lyon, 2012 - 2017
// Distributed under the GNU Lesser General Public License Version 2.1 (LGPLv2)
// (Refer to accompanying file LICENSE.md or copy at
//  https://www.gnu.org/licenses/old-licenses/lgpl-2.1.html )

////////////////////////////////////////////////////////////////////////////////
#ifndef __ABSTRACTLAYER_HPP__
#define __ABSTRACTLAYER_HPP__
////////////////////////////////////////////////////////////////////////////////
#include "URI.hpp"
#include <string>
#include <memory>
////////////////////////////////////////////////////////////////////////////////
namespace vcity
{
    ////////////////////////////////////////////////////////////////////////////////
    /// \brief abstractLayer class : abstract class for all layer types
    class abstractLayer
    {
    public:
        /// \brief abstractLayer Build empty layer
        /// \param name Layer name
        abstractLayer(const std::string& name);

        virtual ~abstractLayer() {}

        /// \brief setName Set layer name
        /// \param name Layer name
        void setName(const std::string& name);

        /// \brief getName Get layer name
        /// \return Layer name string
        const std::string& getName() const;

        // --- pure virtual

        /// Get layer type as string
        virtual const std::string getType() const = 0;

        /// get layer URI
        virtual URI getURI() const = 0;

        virtual void dump() = 0;

    private:
        std::string m_name;             ///< layer name
    };
    ////////////////////////////////////////////////////////////////////////////////
    typedef std::shared_ptr<abstractLayer> iLayerPtr;
    ////////////////////////////////////////////////////////////////////////////////
} // namespace vcity
////////////////////////////////////////////////////////////////////////////////
#endif // __ABSTRACTLAYER_HPP__
