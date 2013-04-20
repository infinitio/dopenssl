#include <cryptography/Input.hh>

namespace infinit
{
  namespace cryptography
  {
    /*-------------.
    | Construction |
    `-------------*/

    Input::Input(elle::WeakBuffer const& buffer):
      _buffer(buffer)
    {
    }

    /*----------.
    | Operators |
    `----------*/

    elle::Boolean
    Input::operator ==(Input const& other) const
    {
      if (this == &other)
        return (true);

      return (this->_buffer == other._buffer);
    }

    elle::Boolean
    Input::operator <(Input const& other) const
    {
      if (this == &other)
        return (false);

      return (this->_buffer < other._buffer);
    }

    elle::Boolean
    Input::operator <=(Input const& other) const
    {
      if (this == &other)
        return (true);

      return (this->_buffer <= other._buffer);
    }

    elle::Boolean
    Input::operator ==(Output const& other) const
    {
      return (this->_buffer == elle::WeakBuffer(other.buffer()));
    }

    elle::Boolean
    Input::operator <(Output const& other) const
    {
      return (this->_buffer < elle::WeakBuffer(other.buffer()));
    }

    elle::Boolean
    Input::operator <=(Output const& other) const
    {
      return (this->_buffer <= elle::WeakBuffer(other.buffer()));
    }

    /*----------.
    | Printable |
    `----------*/

    void
    Input::print(std::ostream& stream) const
    {
      stream << this->_buffer;
    }
  }
}