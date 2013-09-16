// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

// Begin prologue.
//

#define AOSLCPP_SOURCE 

//
// End prologue.

#include <xsd/cxx/pre.hxx>

#include "aosl/unique_move_ref.hpp"

#include <xsd/cxx/xml/dom/wildcard-source.hxx>

#include <xsd/cxx/xml/dom/parsing-source.hxx>

#include <xsd/cxx/tree/type-factory-map.hxx>

#include <xsd/cxx/tree/comparison-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_factory_plate< 0, char >
  type_factory_plate_init;

  static
  const ::xsd::cxx::tree::comparison_plate< 0, char >
  comparison_plate_init;
}

namespace aosl
{
  // Unique_move_ref
  //

  Unique_move_ref::
  Unique_move_ref (const ::xml_schema::Idref& _xsd_Idref_base)
  : ::aosl::Unique_ref (_xsd_Idref_base)
  {
  }

  Unique_move_ref::
  Unique_move_ref (const Unique_move_ref& x,
                   ::xml_schema::Flags f,
                   ::xml_schema::Container* c)
  : ::aosl::Unique_ref (x, f, c)
  {
  }

  Unique_move_ref::
  Unique_move_ref (const ::xercesc::DOMElement& e,
                   ::xml_schema::Flags f,
                   ::xml_schema::Container* c)
  : ::aosl::Unique_ref (e, f, c)
  {
  }

  Unique_move_ref::
  Unique_move_ref (const ::xercesc::DOMAttr& a,
                   ::xml_schema::Flags f,
                   ::xml_schema::Container* c)
  : ::aosl::Unique_ref (a, f, c)
  {
  }

  Unique_move_ref::
  Unique_move_ref (const ::std::string& s,
                   const ::xercesc::DOMElement* e,
                   ::xml_schema::Flags f,
                   ::xml_schema::Container* c)
  : ::aosl::Unique_ref (s, e, f, c)
  {
  }

  Unique_move_ref* Unique_move_ref::
  _clone (::xml_schema::Flags f,
          ::xml_schema::Container* c) const
  {
    return new class Unique_move_ref (*this, f, c);
  }

  Unique_move_ref::
  ~Unique_move_ref ()
  {
  }
}

#include <ostream>

#include <xsd/cxx/tree/std-ostream-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::std_ostream_plate< 0, char >
  std_ostream_plate_init;
}

namespace aosl
{
  ::std::ostream&
  operator<< (::std::ostream& o, const Unique_move_ref& i)
  {
    o << static_cast< const ::aosl::Unique_ref& > (i);

    return o;
  }
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace aosl
{
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/type-serializer-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_serializer_plate< 0, char >
  type_serializer_plate_init;
}

namespace aosl
{
  void
  operator<< (::xercesc::DOMElement& e, const Unique_move_ref& i)
  {
    e << static_cast< const ::aosl::Unique_ref& > (i);
  }

  void
  operator<< (::xercesc::DOMAttr& a, const Unique_move_ref& i)
  {
    a << static_cast< const ::aosl::Unique_ref& > (i);
  }

  void
  operator<< (::xml_schema::ListStream& l,
              const Unique_move_ref& i)
  {
    l << static_cast< const ::aosl::Unique_ref& > (i);
  }
}

#include <xsd/cxx/post.hxx>

// Begin epilogue.
//
//
// End epilogue.
