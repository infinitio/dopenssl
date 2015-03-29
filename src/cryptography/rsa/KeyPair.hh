#ifndef INFINIT_CRYPTOGRAPHY_RSA_KEYPAIR_HH
# define INFINIT_CRYPTOGRAPHY_RSA_KEYPAIR_HH

# include <cryptography/fwd.hh>
# include <cryptography/Oneway.hh>
# include <cryptography/Cipher.hh>
# include <cryptography/rsa/PublicKey.hh>
# include <cryptography/rsa/PrivateKey.hh>
# include <cryptography/rsa/KeyPair.hh>
# include <cryptography/rsa/Padding.hh>

# include <utility>
ELLE_OPERATOR_RELATIONALS();

# include <iosfwd>

# include <elle/serialize/construct.hh>
# include <elle/types.hh>

namespace infinit
{
  namespace cryptography
  {
    namespace rsa
    {
      /// Represent a cryptographic key pair _i.e_ a pair of public and
      /// private keys.
      ///
      /// Note that the public key is always written as a capital 'K'
      /// while a private key is noted with a lower-case 'k'.
      class KeyPair:
        public elle::Printable
      {
        /*----------.
        | Constants |
        `----------*/
      public:
        /// The algorithm used for hashing the content to sign/verify.
        ///
        /// XXX to remove
        static Oneway const signature_oneway_algorithm =
          Oneway::sha256;

        /*-------------.
        | Construction |
        `-------------*/
      public:
        KeyPair(); // XXX[to deserialize]
        KeyPair(PublicKey const& K,
                PrivateKey const& k);
        KeyPair(PublicKey&& K,
                PrivateKey&& k);
        explicit
# if defined(INFINIT_CRYPTOGRAPHY_ROTATION)
        /// Deduce a keypair based out of the given seed.
        KeyPair(Seed const& seed,
                Padding const encryption_padding = Padding::oaep,
                Padding const signature_padding = Padding::pss,
                Oneway const digest_algorithm = Oneway::sha256,
                Cipher const envelope_algorithm = Cipher::aes256);
# endif
        KeyPair(KeyPair const& other);
        KeyPair(KeyPair&& other);
        ELLE_SERIALIZE_CONSTRUCT_DECLARE(KeyPair);
        virtual
        ~KeyPair() = default;

        /*--------.
        | Methods |
        `--------*/
      public:
        /// Return the public key.
        PublicKey const&
        K() const;
        /// Return the private key.
        PrivateKey const&
        k() const;
        /// Return the key pair's size in bytes.
        elle::Natural32
        size() const;
        /// Return the key pair's length in bits.
        elle::Natural32
        length() const;

        /*----------.
        | Operators |
        `----------*/
      public:
        elle::Boolean
        operator ==(KeyPair const& other) const;
        ELLE_OPERATOR_NO_ASSIGNMENT(KeyPair);

        /*----------.
        | Printable |
        `----------*/
      public:
        // printable
        void
        print(std::ostream& stream) const override;

        /*--------------.
        | Serialization |
        `--------------*/
      public:
        KeyPair(elle::serialization::SerializerIn& serializer);
        void
        serialize(elle::serialization::Serializer& serializer);

        /*----------.
        | Serialize |
        `----------*/
      public:
        // serializable
        ELLE_SERIALIZE_FRIEND_FOR(KeyPair);

        /*-----------.
        | Attributes |
        `-----------*/
      private:
        /// The public key.
        ELLE_ATTRIBUTE(std::unique_ptr<PublicKey>, K);
        /// The private key.
        ELLE_ATTRIBUTE(std::unique_ptr<PrivateKey>, k);
      };
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
    namespace rsa
    {
      namespace keypair
      {
        /*----------.
        | Functions |
        `----------*/

        /// Return a pair composed of the public and private key of a
        /// freshly generated RSA key pair.
        ///
        /// Note that the length is in bits.
        KeyPair
        generate(elle::Natural32 const length,
                 Padding const encryption_padding = Padding::oaep,
                 Padding const signature_padding = Padding::pss,
                 Oneway const digest_algorithm = Oneway::sha256,
                 Cipher const envelope_algorithm = Cipher::aes256);
      }
    }
  }
}

# include <cryptography/rsa/KeyPair.hxx>

#endif