#pragma once

#include <cstdint>

namespace scl::lex {

enum class TokenKind : std::uint8_t {
    Error,
    Colon,
    Equal,
    Comma,
    Semi,
    OpenParen,
    OpenCurlyBrace,
    OpenSquareBracket,
    CloseParen,
    CloseCurlyBrace,
    CloseSquareBracket,
    kw_fn,
    Identifier,
    IntLiteral,
    FileEnd
};

}  // namespace scl::lex