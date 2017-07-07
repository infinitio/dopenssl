#if defined(INFINIT_CRYPTOGRAPHY_LEGACY)
# ifndef INFINIT_CRYPTOGRAPHY_LEGACY_OUTPUT_HH
#  define INFINIT_CRYPTOGRAPHY_LEGACY_OUTPUT_HH

#  include <elle/types.hh>
#  include <elle/attribute.hh>
#  include <elle/operator.hh>
#  include <elle/Buffer.hh>
#  include <elle/Printable.hh>

#  include <elle/serialize/construct.hh>
#  include <elle/serialization/Serializer.hh>

#  include <cryptography/fwd.hh>

namespace infinit
{
  namespace cryptography
  {
    /// Represent an output of a cryptographic operation. Note that one
    /// can retrieve the buffer embedded in this class so as to use it
    /// outside of the cryptography library.
    class Output:
      public elle::Printable
    {
      /*-------------.
      | Construction |
      `-------------*/
    public:
      explicit
      Output(elle::Natural64 const size);
      explicit
      Output(elle::Buffer const& buffer);
      explicit
      Output(elle::Buffer&& buffer);
      Output(Output const& other);
      Output(Output&& other);
      virtual
      ~Output() = default;

      /*----------.
      | Operators |
      `----------*/
    public:
      elle::Boolean
      operator ==(Output const& other) const;
      elle::Boolean
      operator <(Output const& other) const;
      elle::Boolean
      operator <=(Output const& other) const;
      ELLE_OPERATOR_NEQ(Output);
      ELLE_OPERATOR_GT(Output);
      ELLE_OPERATOR_GTE(Output);
      void
      operator =(Output const& other) = delete;
      Output&
      operator =(Output&& other) = default;

      elle::Boolean
      operator ==(Input const& other) const;
      elle::Boolean
      operator <(Input const& other) const;
      elle::Boolean
      operator <=(Input const& other) const;
      ELLE_OPERATOR_NEQ(Input);
      ELLE_OPERATOR_GT(Input);
      ELLE_OPERATOR_GTE(Input);

      /*----------.
      | Printable |
      `----------*/
    public:
      void
      print(std::ostream& stream) const override;

      /*--------------.
      | Serialization |
      `--------------*/
    public:
      Output(elle::serialization::SerializerIn& serializer);
      void
      serialize(elle::serialization::Serializer& serializer);

      /*-----------.
      | Attributes |
      `-----------*/
    private:
      ELLE_ATTRIBUTE_RX(elle::Buffer, buffer);

      /*----------.
      | Serialize |
      `----------*/
    public:
      Output() {}
      ELLE_SERIALIZE_CONSTRUCT(Output,
                               _buffer)
      {}
      ELLE_SERIALIZE_FRIEND_FOR(Output);
    };
  }
}

#  include <cryptography/_legacy/Output.hxx>

# endif
#else
# warning "LEGACY: this file should not have been included"
#endif