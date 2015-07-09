#ifndef INFINIT_CRYPTOGRAPHY_FWD_HH
# define INFINIT_CRYPTOGRAPHY_FWD_HH

namespace infinit
{
  namespace cryptography
  {
    enum class Cipher;
    enum class Mode;
    enum class Cryptosystem;
    enum class Oneway;
    class Exception;
    class SecretKey;
  }
}

# include <cryptography/rsa/fwd.hh>
# include <cryptography/dsa/fwd.hh>
# include <cryptography/dh/fwd.hh>

# if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
#  include <cryptography/_legacy/fwd.hh>
# endif

#endif
