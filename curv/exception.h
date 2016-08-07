// Copyright Doug Moen 2016.
// Distributed under The MIT License.
// See accompanying file LICENSE.md or https://opensource.org/licenses/MIT

#ifndef CURV_EXCEPTION_H
#define CURV_EXCEPTION_H

#include <aux/exception.h>
#include <ostream>
#include <curv/location.h>
#include <curv/phrase.h>

namespace curv {

/// Virtual base class for Curv compile time and run time errors.
///
/// Has two parts: a message (returned by what()), and a location() that
/// specifies where the error occurred.
/// These two parts are printed separately (see write()).
struct Exception : public aux::Exception
{
    Location loc_;

    Exception(Location loc, const char* msg)
    : aux::Exception(msg), loc_(std::move(loc)) {}

    Exception(Location loc, Shared<String> msg)
    : aux::Exception(std::move(msg)), loc_(std::move(loc)) {}

    const Location& location() { return loc_; }

    /// write the message and location to a stream.
    ///
    /// Multiple lines may be written, but no final newline.
    virtual void write(std::ostream&) const override;
};

/// Curv error, where location is specified by a token.
struct Token_Error : public Exception
{
    Token_Error(const Script& s, Token tok, const char* msg)
    : Exception(Location(s, std::move(tok)), msg)
    {}

    Token_Error(const Script& s, Token tok, Shared<String> msg)
    : Exception(Location(s, std::move(tok)), std::move(msg))
    {}
};

/// Lexical analysis error: an illegal character in the input.
///
/// Subclass of Token_Error where the token spans just the illegal character.
struct Char_Error : public Token_Error
{
    Char_Error(const Script& s, Token tok);
};

struct Phrase_Error : public Exception
{
    Phrase_Error(const Phrase& syn, const char* msg)
    : Exception(syn.location(), msg)
    {}

    Phrase_Error(const Phrase& syn, Shared<String> msg)
    : Exception(syn.location(), std::move(msg))
    {}
};

struct Arg_Error : public aux::Exception
{
    const char* argname_;

    Arg_Error(const char* argname, const char* msg)
    : aux::Exception(msg), argname_(argname)
    {}

    Arg_Error(const char* argname, Shared<String> msg)
    : aux::Exception(std::move(msg)), argname_(argname)
    {}
};

} // namespace curv
#endif // header guard
