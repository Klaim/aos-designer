// Copyright (C) 2005-2010 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema
// to C++ data binding compiler, in the Proprietary License mode.
// You should have received a proprietary license from Code Synthesis
// Tools CC prior to generating this code. See the license text for
// conditions.
//

#ifndef AOSLCPP_AOSL__EFFECT_INL
#define AOSLCPP_AOSL__EFFECT_INL

// Begin prologue.
//
//
// End prologue.

namespace aosl
{
  // Effect
  // 

  inline
  const Effect::AnySequence& Effect::
  any () const
  {
    return this->any_;
  }

  inline
  Effect::AnySequence& Effect::
  any ()
  {
    return this->any_;
  }

  inline
  void Effect::
  any (const AnySequence& s)
  {
    this->any_ = s;
  }

  inline
  const Effect::TypeType& Effect::
  type () const
  {
    return this->type_.get ();
  }

  inline
  Effect::TypeType& Effect::
  type ()
  {
    return this->type_.get ();
  }

  inline
  void Effect::
  type (const TypeType& x)
  {
    this->type_.set (x);
  }

  inline
  void Effect::
  type (::std::auto_ptr< TypeType > x)
  {
    this->type_.set (x);
  }

  inline
  const ::xercesc::DOMDocument& Effect::
  dom_document () const
  {
    return *dom_document_;
  }

  inline
  ::xercesc::DOMDocument& Effect::
  dom_document ()
  {
    return *dom_document_;
  }
}

// Begin epilogue.
//
//
// End epilogue.

#endif // AOSLCPP_AOSL__EFFECT_INL
