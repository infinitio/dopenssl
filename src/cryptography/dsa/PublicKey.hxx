#ifndef INFINIT_CRYPTOGRAPHY_DSA_PUBLICKEY_HXX
# define INFINIT_CRYPTOGRAPHY_DSA_PUBLICKEY_HXX

//
// ---------- Class -----------------------------------------------------------
//

# include <cryptography/Plain.hh>
# include <cryptography/serialization.hh>
# include <cryptography/hash.hh>

# include <elle/Buffer.hh>
# include <elle/log.hh>

namespace infinit
{
  namespace cryptography
  {
    namespace dsa
    {
      /*--------.
      | Methods |
      `--------*/

      template <typename T>
      elle::Boolean
      PublicKey::verify(Signature const& signature,
                        T const& value) const
      {
        ELLE_LOG_COMPONENT("infinit.cryptography.dsa.PublicKey");
        ELLE_TRACE_METHOD("");
        ELLE_DUMP("signature: %x", signature);
        ELLE_DUMP("value: %x", value);

        static_assert(std::is_same<T, Digest>::value == false,
                      "this call should never have occured");

        elle::ConstWeakBuffer _value = cryptography::serialize(value);

        Digest digest = hash(Plain(_value), this->_digest_algorithm);

        return (this->verify(signature, digest));
      }
    }
  }
}

/*-------------.
| Serializable |
`-------------*/

# include <elle/serialize/Serializer.hh>
# include <elle/serialize/StaticFormat.hh>

# include <cryptography/finally.hh>
# include <cryptography/dsa/der.hh>

ELLE_SERIALIZE_SPLIT(infinit::cryptography::dsa::PublicKey)

ELLE_SERIALIZE_SPLIT_SAVE(infinit::cryptography::dsa::PublicKey,
                          archive,
                          value,
                          format)
{
  ELLE_ASSERT_NEQ(value._key, nullptr);

  elle::Buffer buffer =
    infinit::cryptography::dsa::der::encode_public(value._key->pkey.dsa);

  archive << buffer;
  archive << value._digest_algorithm;
}

ELLE_SERIALIZE_SPLIT_LOAD(infinit::cryptography::dsa::PublicKey,
                          archive,
                          value,
                          format)
{
  elle::Buffer buffer;

  archive >> buffer;
  archive >> value._digest_algorithm;

  ::DSA* dsa =
      infinit::cryptography::dsa::der::decode_public(buffer);

  INFINIT_CRYPTOGRAPHY_FINALLY_ACTION_FREE_DSA(dsa);

  value._construct(dsa);

  INFINIT_CRYPTOGRAPHY_FINALLY_ABORT(dsa);

  value._prepare();

  value._check();
}

//
// ---------- Hash ------------------------------------------------------------
//

namespace std
{
  template <>
  struct hash<infinit::cryptography::dsa::PublicKey>
  {
    size_t
    operator ()(infinit::cryptography::dsa::PublicKey const& value) const
    {
      std::stringstream stream;
      elle::serialize::OutputBinaryArchive archive(stream);

      archive << value;

      size_t result = std::hash<std::string>()(stream.str());

      return (result);
    }
  };
}

#endif
