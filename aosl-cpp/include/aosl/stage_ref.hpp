// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

/**
 * @file
 * @brief Generated from stage_ref.xsd.
 */

#ifndef AOSLCPP_AOSL__STAGE_REF_HPP
#define AOSLCPP_AOSL__STAGE_REF_HPP

// Begin prologue.
//

#include <aoslcpp/common.hpp>

//
// End prologue.

#include <xsd/cxx/config.hxx>

#if (XSD_INT_VERSION != 3030000L)
#error XSD runtime version mismatch
#endif

#include <xsd/cxx/pre.hxx>

#include "aosl/stage_ref_forward.hpp"

#include <memory>    // std::auto_ptr
#include <limits>    // std::numeric_limits
#include <algorithm> // std::binary_search

#include <xsd/cxx/xml/char-utf8.hxx>

#include <xsd/cxx/tree/exceptions.hxx>
#include <xsd/cxx/tree/elements.hxx>
#include <xsd/cxx/tree/containers.hxx>
#include <xsd/cxx/tree/list.hxx>

#include <xsd/cxx/xml/dom/parsing-header.hxx>

#include <xsd/cxx/tree/containers-wildcard.hxx>

#ifndef XSD_DONT_INCLUDE_INLINE
#define XSD_DONT_INCLUDE_INLINE

#undef XSD_DONT_INCLUDE_INLINE
#else

#endif // XSD_DONT_INCLUDE_INLINE

/**
 * @brief C++ namespace for the %artofsequence.org/aosl/1.0
 * schema namespace.
 */
namespace aosl
{
  /**
   * @brief Union class corresponding to the %stage_ref
   * schema type.
   *
   * The mapping represents unions as strings.
   *
   * Reference to a Stage or to a special stage search.
   */
  class Stage_ref: public ::xml_schema::String
  {
    public:

    /**
     * @brief Create an instance from a C string.
     *
     * @param v A string value.
     */
    Stage_ref (const char* v);

    /**
     * @brief Create an instance from a string.
     *
     * @param v A string value.
     */
    Stage_ref (const ::std::string& v);

    /**
     * @brief Create an instance from a DOM element.
     *
     * @param e A DOM element to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Stage_ref (const ::xercesc::DOMElement& e,
               ::xml_schema::Flags f = 0,
               ::xml_schema::Container* c = 0);

    /**
     * @brief Create an instance from a DOM attribute.
     *
     * @param a A DOM attribute to extract the data from.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Stage_ref (const ::xercesc::DOMAttr& a,
               ::xml_schema::Flags f = 0,
               ::xml_schema::Container* c = 0);

    /**
     * @brief Create an instance from a string fragment.
     *
     * @param s A string fragment to extract the data from.
     * @param e A pointer to DOM element containing the string fragment.
     * @param f Flags to create the new instance with.
     * @param c A pointer to the object that will contain the new
     * instance.
     */
    Stage_ref (const ::std::string& s,
               const ::xercesc::DOMElement* e,
               ::xml_schema::Flags f = 0,
               ::xml_schema::Container* c = 0);

    /**
     * @brief Copy constructor.
     *
     * @param x An instance to make a copy of.
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     *
     * For polymorphic object models use the @c _clone function instead.
     */
    Stage_ref (const Stage_ref& x,
               ::xml_schema::Flags f = 0,
               ::xml_schema::Container* c = 0);

    /**
     * @brief Copy the instance polymorphically.
     *
     * @param f Flags to create the copy with.
     * @param c A pointer to the object that will contain the copy.
     * @return A pointer to the dynamically allocated copy.
     *
     * This function ensures that the dynamic type of the instance is
     * used for copying and should be used for polymorphic object
     * models instead of the copy constructor.
     */
    virtual Stage_ref*
    _clone (::xml_schema::Flags f = 0,
            ::xml_schema::Container* c = 0) const;
  };
}

#ifndef XSD_DONT_INCLUDE_INLINE

#endif // XSD_DONT_INCLUDE_INLINE

#include <iosfwd>

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream&, const Stage_ref&);
}

#include <iosfwd>

#include <xercesc/sax/InputSource.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>

namespace aosl
{
}

#include <iosfwd>

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMErrorHandler.hpp>
#include <xercesc/framework/XMLFormatter.hpp>

#include <xsd/cxx/xml/dom/auto-ptr.hxx>

namespace aosl
{
  void
  operator<< (::xercesc::DOMElement&, const Stage_ref&);

  void
  operator<< (::xercesc::DOMAttr&, const Stage_ref&);

  void
  operator<< (::xml_schema::ListStream&,
              const Stage_ref&);
}

#ifndef XSD_DONT_INCLUDE_INLINE
#include "aosl/stage_ref.inl"
#endif // XSD_DONT_INCLUDE_INLINE

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__STAGE_REF_HPP
