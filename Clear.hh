//
// ---------- header ----------------------------------------------------------
//
// project       elle
//
// license       infinit
//
// author        julien quintard   [tue oct 30 10:05:43 2007]
//

#ifndef ELLE_CRYPTOGRAPHY_CLEAR_HH
#define ELLE_CRYPTOGRAPHY_CLEAR_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/cryptography/Plain.hh>

namespace elle
{
  namespace cryptography
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class represents a decoded text, both through symmetric and
    /// asymmetric cryptosystems.
    ///
    /// this type is logically equivalent to a plain text.
    ///
    typedef Plain       Clear;

  }
}

#endif