#include <cryptography/dh/KeyPair.hh>
#include <cryptography/Exception.hh>
#include <cryptography/cryptography.hh>
#include <cryptography/finally.hh>
#include <cryptography/deleter.hh>
#include <cryptography/types.hh>

#include <elle/attribute.hh>
#include <elle/assert.hh>
#include <elle/log.hh>

#include <openssl/engine.h>
#include <openssl/err.h>
#include <openssl/evp.h>

ELLE_LOG_COMPONENT("infinit.cryptography.dh.KeyPair");

namespace infinit
{
  namespace cryptography
  {
    namespace dh
    {
      /*-------------.
      | Construction |
      `-------------*/

      KeyPair::KeyPair()
      {
      }

      KeyPair::KeyPair(PublicKey const& K,
                       PrivateKey const& k):
        _K(new PublicKey(K)),
        _k(new PrivateKey(k))
      {
      }

      KeyPair::KeyPair(PublicKey&& K,
                       PrivateKey&& k):
        _K(new PublicKey(std::move(K))),
        _k(new PrivateKey(std::move(k)))
      {
      }

      KeyPair::KeyPair(KeyPair const& other):
        _K(new PublicKey(*other._K)),
        _k(new PrivateKey(*other._k))
      {
      }

      KeyPair::KeyPair(KeyPair&& other):
        _K(std::move(other._K)),
        _k(std::move(other._k))
      {
      }

      ELLE_SERIALIZE_CONSTRUCT_DEFINE(KeyPair)
      {
      }

      /*--------.
      | Methods |
      `--------*/

      PublicKey const&
      KeyPair::K() const
      {
        ELLE_ASSERT_NEQ(this->_K, nullptr);

        return (*this->_K);
      }

      PrivateKey const&
      KeyPair::k() const
      {
        ELLE_ASSERT_NEQ(this->_k, nullptr);

        return (*this->_k);
      }

      elle::Natural32
      KeyPair::size() const
      {
        ELLE_ASSERT_NEQ(this->_K, nullptr);
        ELLE_ASSERT_NEQ(this->_k, nullptr);
        ELLE_ASSERT_EQ(this->_K->size(), this->_k->size());

        return (this->_K->size());
      }

      elle::Natural32
      KeyPair::length() const
      {
        ELLE_ASSERT_NEQ(this->_K, nullptr);
        ELLE_ASSERT_NEQ(this->_k, nullptr);
        ELLE_ASSERT_EQ(this->_K->length(), this->_k->length());

        return (this->_K->length());
      }

      /*----------.
      | Operators |
      `----------*/

      elle::Boolean
      KeyPair::operator ==(KeyPair const& other) const
      {
        if (this == &other)
          return (true);

        ELLE_ASSERT_NEQ(this->_K, nullptr);
        ELLE_ASSERT_NEQ(this->_k, nullptr);

        // The public component is enough to uniquely identify a key pair.
        return (*this->_K == *other._K);
      }

      /*--------------.
      | Serialization |
      `--------------*/

      KeyPair::KeyPair(elle::serialization::SerializerIn& serializer):
        _K(),
        _k()
      {
        this->serialize(serializer);
      }

      void
      KeyPair::serialize(elle::serialization::Serializer& s)
      {
        s.serialize("public_key", this->_K);
        s.serialize("private_key", this->_k);
      }

      /*----------.
      | Printable |
      `----------*/

      void
      KeyPair::print(std::ostream& stream) const
      {
        ELLE_ASSERT_NEQ(this->_K, nullptr);
        ELLE_ASSERT_NEQ(this->_k, nullptr);

        stream << "(" << *this->_K << ", " << *this->_k << ")";
      }
    }
  }
}

//
// ---------- Generator -------------------------------------------------------
//

namespace infinit
{
  namespace cryptography
  {
    namespace dh
    {
      namespace keypair
      {
        /*----------.
        | Functions |
        `----------*/

        KeyPair
        generate()
        {
          ELLE_TRACE_FUNCTION();

          // Make sure the cryptographic system is set up.
          cryptography::require();

          // Integrate the parameters.
          ::EVP_PKEY* parameters = nullptr;

          if ((parameters = ::EVP_PKEY_new()) == nullptr)
            throw Exception(
              elle::sprintf("unable to allocate a parameters object: %s",
                            ::ERR_error_string(ERR_get_error(), nullptr)));

          INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_EVP_PKEY(parameters);

          if (::EVP_PKEY_set1_DH(parameters, ::DH_get_2048_256()) <= 0)
              throw Exception(
                elle::sprintf("unable to set the parameters: %s",
                              ::ERR_error_string(ERR_get_error(), nullptr)));

          // Prepare the key generation context.
          ::EVP_PKEY_CTX* context;

          if ((context = ::EVP_PKEY_CTX_new(parameters, nullptr)) == nullptr)
              throw Exception(
                elle::sprintf("unable to allocate a keypair generation "
                              "context: %s",
                              ::ERR_error_string(ERR_get_error(), nullptr)));

          INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_EVP_PKEY_CONTEXT(context);

          if (::EVP_PKEY_keygen_init(context) <= 0)
            throw Exception(
               elle::sprintf("unable to initialize the keypair generation "
                            "context: %s",
                            ::ERR_error_string(ERR_get_error(), nullptr)));

          // Generate the Diffie Hellman key pair.
          ::EVP_PKEY* key = nullptr;

          if (::EVP_PKEY_keygen(context, &key) <= 0)
            throw Exception(
              elle::sprintf("unable to generate a keypair: %s",
                            ::ERR_error_string(ERR_get_error(), nullptr)));

          INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_EVP_PKEY(key);

          ELLE_ASSERT_NEQ(key, nullptr);

          // Instanciate both a DH public and private key based on the
          // EVP_PKEY.
          PrivateKey k(key);
          PublicKey K(k);

          INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(key);

          INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(context);
          ::EVP_PKEY_CTX_free(context);

          INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(parameters);
          ::EVP_PKEY_free(parameters);

          return (KeyPair(std::move(K), std::move(k)));
        }
      }
    }
  }
}
