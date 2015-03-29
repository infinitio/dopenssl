#include <cryptography/Oneway.hh>
#include <cryptography/Exception.hh>

#include <elle/log.hh>

ELLE_LOG_COMPONENT("infinit.cryptography.Oneway");

namespace infinit
{
  namespace cryptography
  {
    /*----------.
    | Operators |
    `----------*/

    std::ostream&
    operator <<(std::ostream& stream,
                Oneway const oneway)
    {
      switch (oneway)
      {
        case Oneway::md5:
        {
          stream << "md5";
          break;
        }
        case Oneway::sha:
        {
          stream << "sha";
          break;
        }
        case Oneway::sha1:
        {
          stream << "sha1";
          break;
        }
        case Oneway::sha224:
        {
          stream << "sha224";
          break;
        }
        case Oneway::sha256:
        {
          stream << "sha256";
          break;
        }
        case Oneway::sha384:
        {
          stream << "sha384";
          break;
        }
        case Oneway::sha512:
        {
          stream << "sha512";
          break;
        }
        default:
          throw Exception(elle::sprintf("unknown one-way algorithm '%s'",
                                        static_cast<int>(oneway)));
      }

      return (stream);
    }

    namespace oneway
    {
      /*----------.
      | Functions |
      `----------*/

      ::EVP_MD const*
      resolve(Oneway const name)
      {
        ELLE_TRACE_FUNCTION(name);

        switch (name)
        {
          case Oneway::md5:
            return (::EVP_md5());
          case Oneway::sha:
            return (::EVP_sha());
          case Oneway::sha1:
            return (::EVP_sha1());
          case Oneway::sha224:
            return (::EVP_sha224());
          case Oneway::sha256:
            return (::EVP_sha256());
          case Oneway::sha384:
            return (::EVP_sha384());
          case Oneway::sha512:
            return (::EVP_sha512());
          default:
            throw Exception(elle::sprintf("unable to resolve the given one-way "
                                          "function name '%s'", name));
        }

        elle::unreachable();
      }
    }
  }
}