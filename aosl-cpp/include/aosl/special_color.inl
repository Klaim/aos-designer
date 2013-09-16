// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

#ifndef AOSLCPP_AOSL__SPECIAL_COLOR_INL
#define AOSLCPP_AOSL__SPECIAL_COLOR_INL

// Begin prologue.
//
//
// End prologue.

namespace aosl
{
  // Special_color
  // 

  inline
  Special_color::
  Special_color (Value v)
  : ::xml_schema::String (_xsd_Special_color_literals_[v])
  {
  }

  inline
  Special_color::
  Special_color (const char* v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Special_color::
  Special_color (const ::std::string& v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Special_color::
  Special_color (const ::xml_schema::String& v)
  : ::xml_schema::String (v)
  {
  }

  inline
  Special_color::
  Special_color (const Special_color& v,
                 ::xml_schema::Flags f,
                 ::xml_schema::Container* c)
  : ::xml_schema::String (v, f, c)
  {
  }

  inline
  Special_color& Special_color::
  operator= (Value v)
  {
    static_cast< ::xml_schema::String& > (*this) = 
    ::xml_schema::String (_xsd_Special_color_literals_[v]);

    return *this;
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__SPECIAL_COLOR_INL