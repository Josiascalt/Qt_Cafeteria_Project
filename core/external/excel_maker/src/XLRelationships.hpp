/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2018, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef OPENXLSX_XLRELATIONSHIPS_HPP
#define OPENXLSX_XLRELATIONSHIPS_HPP

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas" // disable warning about below #pragma warning being unknown
#ifdef _MSC_VER                                    // additional condition because the previous line does not work on gcc 12.2
#   pragma warning(push)
#   pragma warning(disable : 4251)
#   pragma warning(disable : 4275)
#endif // _MSC_VER
#pragma GCC diagnostic pop

// ===== External Includes ===== //
#pragma once 

#include <random>       // std::mt19937
#include <string>
#include <vector>

// ===== OpenXLSX Includes ===== //
#include "OpenXLSX-Exports.hpp"
#include "XLXmlFile.hpp"
#include "XLXmlParser.hpp"

namespace OpenXLSX
{
    /**
     * @brief Enable use of random (relationship) IDs
     */
    void UseRandomIDs();

    /**
     * @brief Disable use of random (relationship) IDs (default behavior)
     */
    void UseSequentialIDs();

    /**
     * @brief Return a 32 bit random value
     * @return A 32 bit random value
     */
    extern std::mt19937 Rand32;

    /**
     * @brief Return a 64 bit random value (by invoking Rand32 twice)
     * @return A 64 bit random value
     */
    uint64_t Rand64();

    /**
     * @brief Initialize XLRand32 data source
     * @param pseudoRandom If true, sequence will be reproducible with a constant seed
     */
    void InitRandom(bool pseudoRandom = false);


    class XLRelationships;

    class XLRelationshipItem;

    /**
     * @brief An enum of the possible relationship (or XML document) types used in relationship (.rels) XML files.
     */
    enum class XLRelationshipType {
        CoreProperties,
        ExtendedProperties,
        CustomProperties,
        Workbook,
        Worksheet,
        Chartsheet,
        Dialogsheet,
        Macrosheet,
        CalculationChain,
        ExternalLink,
        ExternalLinkPath,
        Theme,
        Styles,
        Chart,
        ChartStyle,
        ChartColorStyle,
        Image,
        Drawing,
        VMLDrawing,
        SharedStrings,
        PrinterSettings,
        VBAProject,
        ControlProperties,
        Comments,
        Unknown
    };
} //     namespace OpenXLSX

namespace OpenXLSX_XLRelationships { // special namespace to avoid naming conflict with another GetStringFromType function
    using namespace OpenXLSX;
    /**
     * @brief helper function, used only within module and from XLProperties.cpp / XLAppProperties::createFromTemplate
     * @param type the XLRelationshipType for which to return the correct XML string
     */
    std::string GetStringFromType(XLRelationshipType type);
} //    namespace OpenXLSX_XLRelationships

namespace OpenXLSX {
    /**
     * @brief An encapsulation of a relationship item, i.e. an XML file in the document, its type and an ID number.
     */
    class OPENXLSX_EXPORT XLRelationshipItem
    {
    public:    // ---------- Public Member Functions ---------- //
        /**
         * @brief
         */
        XLRelationshipItem();

        /**
         * @brief Constructor. New items should only be created through an XLRelationship object.
         * @param node An XMLNode object with the relationship item. If no input is provided, a null node is used.
         */
        explicit XLRelationshipItem(const XMLNode& node);

        /**
         * @brief Copy Constructor.
         * @param other Object to be copied.
         */
        XLRelationshipItem(const XLRelationshipItem& other);

        /**
         * @brief Move Constructor.
         * @param other Object to be moved.
         */
        XLRelationshipItem(XLRelationshipItem&& other) noexcept = default;

        /**
         * @brief
         */
        ~XLRelationshipItem();

        /**
         * @brief Copy assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to the lhs object.
         */
        XLRelationshipItem& operator=(const XLRelationshipItem& other);

        /**
         * @brief Move assignment operator.
         * @param other Right hand side of assignment operation.
         * @return A reference to lhs object.
         */
        XLRelationshipItem& operator=(XLRelationshipItem&& other) noexcept = default;

        /**
         * @brief Get the type of the current relationship item.
         * @return An XLRelationshipType enum object, corresponding to the type.
         */
        XLRelationshipType type() const;

        /**
         * @brief Get the target, i.e. the path to the XML file the relationship item refers to.
         * @return An XMLAttribute object containing the Target getValue.
         */
        std::string target() const;

        /**
         * @brief Get the id of the relationship item.
         * @return An XMLAttribute object containing the Id getValue.
         */
        std::string id() const;

        /**
         * @brief Test if relationship item is empty (== m_relationshipNode->empty())
         * @return true if this is an empty relationship item
         */
        bool empty() const;

    private:                                         // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_relationshipNode; /**< An XMLNode object with the relationship item */
    };

    // ================================================================================
    // XLRelationships Class
    // ================================================================================

    /**
     * @brief An encapsulation of relationship files (.rels files) in an Excel document package.
     */
    class OPENXLSX_EXPORT XLRelationships : public XLXmlFile
    {
    public:    // ---------- Public Member Functions ---------- //
        /**
         * @brief
         */
        XLRelationships() = default;

        /**
         * @brief
         * @param xmlData
         * @param pathTo Initialize m_path from this: the path to the relationships file origin of xmlData
         * @note m_path is used to resolve relative relationship target paths to an absolute
         */
        explicit XLRelationships(XLXmlData* xmlData, std::string pathTo);

        /**
         * @brief Destructor
         */
        ~XLRelationships();

        /**
         * @brief
         * @param other
         */
        XLRelationships(const XLRelationships& other) = default;

        /**
         * @brief
         * @param other
         */
        XLRelationships(XLRelationships&& other) noexcept = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLRelationships& operator=(const XLRelationships& other) = default;

        /**
         * @brief
         * @param other
         * @return
         */
        XLRelationships& operator=(XLRelationships&& other) noexcept = default;

        /**
         * @brief Look up a relationship item by ID.
         * @param id The ID string of the relationship item to retrieve.
         * @return An XLRelationshipItem object.
         */
        XLRelationshipItem relationshipById(const std::string& id) const;

        /**
         * @brief Look up a relationship item by Target.
         * @param target The Target string of the relationship item to retrieve.
         * @param throwIfNotFound Throw an XLException when target is not found, default: true
         *                        when false, XLRelationshipItem::empty() can be tested on the return value
         * @return An XLRelationshipItem object.
         */
        XLRelationshipItem relationshipByTarget(const std::string& target, bool throwIfNotFound = true) const;

        /**
         * @brief Get the std::map with the relationship items, ordered by ID.
         * @return A const reference to the std::map with relationship items.
         */
        std::vector<XLRelationshipItem> relationships() const;

        /**
         * @brief
         * @param relID
         */
        void deleteRelationship(const std::string& relID);

        /**
         * @brief Delete an item from the Relationships register
         * @param item The XLRelationshipItem object to delete.
         */
        void deleteRelationship(const XLRelationshipItem& item);

        /**
         * @brief Add a new relationship item to the XLRelationships object.
         * @param type The type of the new relationship item.
         * @param target The target (or path) of the XML file for the relationship item.
         */
        XLRelationshipItem addRelationship(XLRelationshipType type, const std::string& target);

        /**
         * @brief Check if a XLRelationshipItem with the given Target string exists.
         * @param target The Target string to look up.
         * @return true if the XLRelationshipItem exists; otherwise false.
         */
        bool targetExists(const std::string& target) const;

        /**
         * @brief Check if a XLRelationshipItem with the given Id string exists.
         * @param id The Id string to look up.
         * @return true if the XLRelationshipItem exists; otherwise false.
         */
        bool idExists(const std::string& id) const;

        // ---------- Protected Member Functions ---------- //
    protected:

        //----------------------------------------------------------------------------------------------------------------------
        //           Private Member Variables
        //----------------------------------------------------------------------------------------------------------------------
    private:
        std::string m_path; // the path - within the XLSX file - to the relationships file on which this object is instantiated
    };
}    // namespace OpenXLSX

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunknown-pragmas" // disable warning about below #pragma warning being unknown
#ifdef _MSC_VER                                    // additional condition because the previous line does not work on gcc 12.2
#   pragma warning(pop)
#endif // _MSC_VER
#pragma GCC diagnostic pop

#endif    // OPENXLSX_XLRELATIONSHIPS_HPP
