// 11127164 - Project 4 - release 1.0.0 - Removed all redundant (comments) codes
#include <iostream>
#include <cctype>
#include <vector>
#include <deque>
#include <map>
#include <stdexcept>
#include <functional>
#include <climits>
#include <memory>

#define DEBUG
// #define TEST

#if defined(TEST)

#include <fstream>

#endif

#define ASSERT(cond, msg)\
  do {\
    if (!(cond)) throw AssertionError(msg);\
  } while (0)

#define RUNTIME(cond, msg)\
  do {\
    if (!(cond)) throw status_t{status_code::RuntimeError, status_info::general, msg};\
  } while (0)

#define RUNTIME_EXTEND(cond, info, msg, attm)\
  do {\
    if (!(cond)) throw status_t{status_code::RuntimeError, info, msg, attm};\
  } while (0)

#define Important(expr)\
  do {\
    try { expr; } catch (status_t& err) {\
      err.important = true;\
      throw;\
    }\
  } while (0)

#define IgnoreNoReturnValue(expr)\
  do {\
    try { expr; } catch (const status_t& err) {\
      if (err.info != status_info::NoReturnValue || err.important) {\
        throw;\
      }\
    }\
  } while (0)

#define NoReturnValue(expr)\
  do {\
    try { expr; } catch (status_t& err) {\
      if (err.info == status_info::NoReturnValue && !err.important) {\
        err.attachment = make_shared<Container>(root);\
      }\
      throw;\
    }\
  } while (0)

#define UnboundParameter(expr)\
  do {\
    try { expr; } catch (status_t& err) {\
      if (err.info == status_info::NoReturnValue && !err.important) {\
        err.info = status_info::UnboundParameter;\
        err.body = UNBOUND_PARAMETER;\
      }\
      throw;\
    }\
  } while (0)

#define UnboundCondition(expr)\
  do {\
    try { expr; } catch (status_t& err) {\
      if (err.info == status_info::NoReturnValue && !err.important) {\
        err.info = status_info::UnboundCondition;\
        err.body = UNBOUND_CONDITION;\
      }\
      throw;\
    }\
  } while (0)

#define UnboundTestCondition(expr)\
  do {\
    try { expr; } catch (status_t& err) {\
      if (err.info == status_info::NoReturnValue && !err.important) {\
        err.info = status_info::UnboundTestCondition;\
        err.body = UNBOUND_TEST_CONDITION;\
      }\
      throw;\
    }\
  } while (0)

#define __TYPE_ARGS const node_t*
#define __TYPE_ROOT const node_t* const &
#define __TYPE_LEVEL const level_t&
#define __TYPE_APPENDIX const void* const &
#define __TYPE_CONTAINERPTR const ContainerPtr&

#define STANDARD_TYPES\
  __TYPE_ROOT, __TYPE_LEVEL, __TYPE_APPENDIX

#define STANDARD_PARAMETERS\
  __TYPE_ROOT root, __TYPE_LEVEL level, __TYPE_APPENDIX appendix = nullptr

#define LAMBDA_PARAMETERS\
  __TYPE_CONTAINERPTR __var, __TYPE_ARGS args, __TYPE_LEVEL level

#define RESERVED_FUNCTION(func, name)\
  {name, make_shared<Container>(bind(&func, this, _1, _2, _3), name)}

class AssertionError : public std::exception {
 private:
  std::string message;
  
 public:
  AssertionError(const std::string& __s = "") {
    message = std::move(__s);
  }

  const char* what() const noexcept override {
    return message.c_str();
  }

  static inline void throws(const std::string __s) {
    throw AssertionError(__s);
  }
};

#define TERMINATE_CHARS\
  {EOF, ' ', '\n', '\t', '\r', '\f', '\v', '\0', '(', ')', '\'', '"', ';'}
#define WHITESPACE_CHARACTERS\
  {' ', '\n', '\t', '\r', '\f', '\v', '\0'}

#define UNEXPECTED_BEHAVIOR "Unexpected behavior occurred."
#define END_OF_FILE_ENCOUNTERD "ERROR (no more input) : END-OF-FILE encountered"
#define NO_CLOSING_QUOTE "ERROR (no closing quote) : END-OF-LINE encountered"
#define NO_MORE_INPUT "ERROR (no more input) : END-OF-FILE encountered"
#define UNEXPECTED_TOKEN_HEADER "ERROR (unexpected token) : "
#define UNEXPECTED_TOKEN_BODY " expected when token"
#define INCORRECT_NUMBER_OF_ARGS string("ERROR (incorrect number of arguments) : ")
#define UNBOUND_SYMBOL "ERROR (unbound symbol) : "
#define UNBOUND_PARAMETER "ERROR (unbound parameter) : "
#define UNBOUND_CONDITION "ERROR (unbound condition) : "
#define UNBOUND_TEST_CONDITION "ERROR (unbound test-condition) : "
#define NON_LIST "ERROR (non-list) : "
#define NO_RETURN_VALUE "ERROR (no return value) : "
#define APPLY_NON_FUNCTION "ERROR (attempt to apply non-function) : "
#define ILLEGAL_DEFINE_FORMAT "ERROR (DEFINE format) : "
#define ILLEGAL_COND_FORMAT "ERROR (COND format) : "
#define ILLEGAL_LET_FORMAT "ERROR (LET format) : "
#define ILLEGAL_LAMBDA_FORMAT "ERROR (LAMBDA format) : "
#define ILLEGAL_SET_FORMAT "ERROR (SET! format) : "
#define DIVISION_BY_ZERO "ERROR (division by zero) : "
#define LEVEL_EXIT_CALLED "ERROR (level of EXIT)"
#define LEVEL_DEFINE_CALLED "ERROR (level of DEFINE)"
#define LEVEL_CLEAN_ENVIRONMENT_CALLED "ERROR (level of CLEAN-ENVIRONMENT)"
#define CAR_WITH_INCORRECT_ARG_TYPE "ERROR (car with incorrect argument type) : "
#define CDR_WITH_INCORRECT_ARG_TYPE "ERROR (cdr with incorrect argument type) : "
#define ADD_WITH_INCORRECT_ARG_TYPE "ERROR (+ with incorrect argument type) : "
#define SUB_WITH_INCORRECT_ARG_TYPE "ERROR (- with incorrect argument type) : "
#define MUL_WITH_INCORRECT_ARG_TYPE "ERROR (* with incorrect argument type) : "
#define DIV_WITH_INCORRECT_ARG_TYPE "ERROR (/ with incorrect argument type) : "
#define EQ_WITH_INCORRECT_ARG_TYPE "ERROR (= with incorrect argument type) : "
#define GT_WITH_INCORRECT_ARG_TYPE "ERROR (> with incorrect argument type) : "
#define LT_WITH_INCORRECT_ARG_TYPE "ERROR (< with incorrect argument type) : "
#define GE_WITH_INCORRECT_ARG_TYPE "ERROR (>= with incorrect argument type) : "
#define LE_WITH_INCORRECT_ARG_TYPE "ERROR (<= with incorrect argument type) : "
#define SEQ_WITH_INCORRECT_ARG_TYPE "ERROR (string=? with incorrect argument type) : "
#define SGT_WITH_INCORRECT_ARG_TYPE "ERROR (string>? with incorrect argument type) : "
#define SLT_WITH_INCORRECT_ARG_TYPE "ERROR (string<? with incorrect argument type) : "
#define PUSHSTR_WITH_INCORRECT_ARG_TYPE "ERROR (string-append with incorrect argument type) : "
#define SHOWSTR_WITH_INCORRECT_ARG_TYPE "ERROR (display-string with incorrect argument type) : "
#define STOS_WITH_INCORRECT_ARG_TYPE "ERROR (symbol->string with incorrect argument type) : "
#define NTOS_WITH_INCORRECT_ARG_TYPE "ERROR (number->string with incorrect argument type) : "

#define IS_FUNCTION is_invocable_v<T, node_t*, int, void*>
#define IS_NODE is_same_v<T, node_t*>
#define IS_CONST_NODE is_same_v<T, const node_t*>

using namespace std;
using placeholders::_1;
using placeholders::_2;
using placeholders::_3;

struct status_t;
struct token_t;
struct node_t;
struct node_ext;
struct Container;

using ContainerPtr = shared_ptr<Container>;
using level_t = unsigned int;
using func_t = function<ContainerPtr(STANDARD_TYPES)>;

using Segment = map<string, ContainerPtr>;
using Page = vector<Segment>;

enum class tokenType {
  undefined,
  LeftParen,
  RightParen,
  Int,
  String,
  Dot,
  Float,
  Nil,
  T,
  Quote,
  Symbol
};

enum class nodeType {
  Expr,
  Atom
};

enum class containType {
  Void, Int, Boolean, Float, String, Node, Function, Lambda, Error
};

enum class status_code {
  Exit,
  EndOfFileEncountered,
  NoClosingQuote,
  UnexpectedToken,
  RuntimeError
};

enum class status_info {
  general,
  NoReturnValue,
  UnboundParameter,
  UnboundCondition,
  UnboundTestCondition
};

struct token_t {
  tokenType family;
  string text;
  size_t line;
  size_t column;

  inline string stringify() const {
    string str;
    switch (family) {
      case tokenType::Int: {
        char _buf[32];
        snprintf(_buf, sizeof(_buf), "%d", stoi(text));
        str = _buf;
        break;
      }
      case tokenType::Float: {
        char _buf[32];
        snprintf(_buf, sizeof(_buf), "%.3f", stod(text));
        str = _buf;
        break;
      }
      case tokenType::T: {
        str = "#t";
        break;
      }
      case tokenType::Nil: {
        str = "nil";
        break;
      }
      case tokenType::Quote: {
        str = "quote";
        break;
      }
      default: {
        str = text;
      }
    }
    return str;
  }

  bool operator==(const token_t& __obj) const noexcept {
    if (__obj.family == family) switch (family) {
      case tokenType::Int: return stoi(text) == stoi(__obj.text);
      case tokenType::Float: return stod(text) == stod(__obj.text);
      case tokenType::String: return text == __obj.text;
      case tokenType::Symbol: return text == __obj.text;
      default: return true;
    } else {
      return false;
    }
  }
};

struct node_t {
  nodeType type;
  token_t* body = nullptr;
  node_t* left = nullptr;
  node_t* right = nullptr;

  node_t() = default;

  node_t(
    const nodeType& type,
    token_t* const &body = nullptr,
    node_t* const &left = nullptr,
    node_t* const &right = nullptr
  ) : type(type), body(body), left(left), right(right) {}

  virtual ~node_t() {
    delete body;
    delete left;
    delete right;
  }

  virtual node_t* copy() const noexcept {
    return new node_t(
      type,
      body ? new token_t(*body) : nullptr,
      left ? left->copy() : nullptr,
      right ? right->copy() : nullptr
    );
  }

  bool operator==(const node_t& __root) const noexcept {
    struct wrap_t{
      const node_t* node_1;
      const node_t* node_2;
      int credit = 3;
      wrap_t(const node_t* const &__n1, const node_t* const &__n2) :
        node_1(__n1), node_2(__n2) {}
    };
    deque<wrap_t> queue;
    queue.emplace_back(this, &__root);
    bool exec = true;
    while (exec && !queue.empty()) {
      wrap_t& curr = queue.back();
      switch (curr.credit) {
        case 3:
          curr.credit--;
          if (curr.node_1->type == curr.node_2->type) {
            if (curr.node_1->type == nodeType::Atom) {
              exec = (*curr.node_1->body == *curr.node_2->body);
            }
          } else {
            exec = false;
            break;
          }
        case 2:
          curr.credit--;
          if (!!(curr.node_1->left) ^ !!(curr.node_2->left)) {
            const node_t* const &left_1 = curr.node_1->left;
            const node_t* const &left_2 = curr.node_2->left;
            exec = (
              (left_1 && left_1->body->family == tokenType::Nil) ||
              (left_2 && left_2->body->family == tokenType::Nil)
            );
            break;
          } else if (curr.node_1->left && curr.node_2->left) {
            queue.emplace_back(curr.node_1->left, curr.node_2->left);
            continue;
          }
        case 1:
          curr.credit--;
          if (!!(curr.node_1->right) ^ !!(curr.node_2->right)) {
            const node_t* const &right_1 = curr.node_1->right;
            const node_t* const &right_2 = curr.node_2->right;
            exec = (
              (right_1 && right_1->body->family == tokenType::Nil) ||
              (right_2 && right_2->body->family == tokenType::Nil)
            );
            break;
          } else if (curr.node_1->right && curr.node_2->right) {
            queue.emplace_back(curr.node_1->right, curr.node_2->right);
            continue;
          }
        default: queue.pop_back();
      }
    }
    return exec;
  }

};

struct node_ext : public node_t {
  ContainerPtr prototype = nullptr;

  node_ext(
    const nodeType& type,
    token_t* const &body = nullptr,
    node_t* const &left = nullptr,
    node_t* const &right = nullptr,
    const ContainerPtr& prototype = nullptr
  ) : node_t(type, body, left, right), prototype(prototype) {}

  ~node_ext() {
    prototype = nullptr;
  }

  node_ext* copy() const noexcept override {
    return new node_ext(
      type,
      body ? new token_t(*body) : nullptr,
      left ? left->copy() : nullptr,
      right ? right->copy() : nullptr,
      prototype
    );
  }

};

struct status_t {
  status_code code;
  status_info info = status_info::general;
  string body;
  ContainerPtr attachment = nullptr;
  bool important = false;
};

struct Container {
 public:  
  containType type = containType::Void;
  void* value = nullptr; 
  const string name;

  template <typename T,
  typename enable_if<!(IS_NODE || IS_CONST_NODE || IS_FUNCTION)>::type* = nullptr>
  Container(const T& __val, const string& __name = "") : name(__name) {
    if (is_same_v<int, T>)
      type = containType::Int;
    else if (is_same_v<bool, T>)
      type = containType::Boolean;
    else if (is_same_v<double, T>)
      type = containType::Float;
    else if (is_same_v<string, T>)
      type = containType::String;
    else AssertionError::throws(UNEXPECTED_BEHAVIOR);
    
    value = new T(__val);
  }

  template <typename T, typename enable_if<IS_NODE || IS_CONST_NODE>::type* = nullptr>
  Container(const T& __node, const string& __name = "") : name(__name) {
    if (__node->type == nodeType::Atom) {
      switch (__node->body->family) {
        case tokenType::Int: {
          type = containType::Int;
          value = new int(stoi(__node->body->text));
          break;
        }
        case tokenType::Float: {
          type = containType::Float;
          value = new double(stod(__node->body->text));
          break;
        }
        case tokenType::T: {
          type = containType::Boolean;
          value = new bool(true);
          break;
        }
        case tokenType::Nil: {
          type = containType::Boolean;
          value = new bool(false);
          break;
        }
        case tokenType::String: {
          type = containType::String;
          value = new string(__node->body->text);
          break;
        }
        case tokenType::Quote:
        case tokenType::Symbol: {
          type = containType::Node;
          value = __node->copy();
          break;
        }
        default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
      }
    } else {
      type = containType::Node;
      value = __node->copy();
    }
  }

  template <typename T, typename enable_if<IS_FUNCTION>::type* = nullptr>
  Container(const T& __func, const string& __name = "") : name(__name) {
    type = containType::Function;
    value = new func_t(__func);
  }

  Container() = default;

  Container(const Container& __obj) = delete;
  Container& operator=(const Container& __obj) = delete;

  ~Container() {
    switch (type) {
      case containType::Boolean: {
        delete static_cast<bool*>(value);
        break;
      }
      case containType::Float: {
        delete static_cast<double*>(value);
        break;
      }
      case containType::Int: {
        delete static_cast<int*>(value);
        break;
      }
      case containType::Function: {
        delete static_cast<func_t*>(value);
        break;
      }
      case containType::Lambda:
      case containType::Node: {
        delete static_cast<node_t*>(value);
        break;
      }
      case containType::Error:
      case containType::String: {
        delete static_cast<string*>(value);
        break;
      }
      case containType::Void: {
        break;
      }
      default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
    }
  }
};

class Scanner {
 private:
  struct char_t {
    char chr = '\0';
    size_t line = 0;       // line position where this char was read.
    size_t column = 0;     // column position where this char was read.
  };

  char_t get;       // info of lastest read character

  size_t line = 1;     // line of the next char to be read
  size_t column = 1;   // column of the next char to be read

  template <size_t N>
  static inline bool match(const char& __c, const char (&__arr)[N]) noexcept {
    for (const char& chr: __arr) {
      if (__c == chr) return true;
    }
    return false;
  }

  char& getchar() noexcept {
    get.chr = cin.get();
    get.line = line;
    get.column = column++;
    if (get.chr == '\n') {
      line += 1;
      column = 1;
    }

    return get.chr;
  }

  /**
   * Skip invalid characters like ` `, `\n`, `\f`, `\r`, `\t` and `\v`
   * until next valid character or `EOF` encountered.
   */
  char& flush() noexcept {
    while (match(get.chr, WHITESPACE_CHARACTERS) || get.chr == ';') {
      // skip whitespace
      while (match(get.chr, WHITESPACE_CHARACTERS)) getchar();
      // skip line comment
      if (get.chr == ';') {
        while (get.chr != '\n' && get.chr != EOF) getchar();
      }
    }
    
    return get.chr;
  }

  inline void getSymbol(token_t& token) noexcept {

    if (!iswspace(get.chr) && !match(get.chr, TERMINATE_CHARS)) {
      do {
        token.text.push_back(get.chr);
        getchar();
      } while (!iswspace(get.chr) && !match(get.chr, TERMINATE_CHARS));
      
      token.family = ( token.text.length() ?
        tokenType::Symbol :
        tokenType::undefined
      );
    }

    return;
  }

  inline void getStringLiteral(token_t& token) {
    token.family = tokenType::String;

    do {
      if ((get.chr == '\\' && match(cin.peek(), "nt\\\""))) {
        char chr = cin.peek();
        switch (chr) {
          case 'n': {
            get.chr = '\n';
            break;
          }
          case 't': {
            get.chr = '\t';
            break;
          }
          case '\\': {
            get.chr = '\\';
            break;
          }
          case '"': {
            get.chr = '\"';
            break;
          }
        }
        token.text.push_back(get.chr);
        getchar();
      } else {
        token.text.push_back(get.chr);
      }
      getchar();
    } while (!match(get.chr, {EOF, '\n'}) && get.chr != '"');

    if (get.chr != '"') {
      status_t err;
      err.code = status_code::NoClosingQuote;
      err.body = NO_CLOSING_QUOTE;
      (err.body += " at Line ") += to_string(get.line);
      (err.body += " Column ") += to_string(get.column);
      throw err;
    }

    token.text.push_back(get.chr);
    getchar();

    return;
  }

  inline void getNumeric(token_t& token) noexcept {
    token.family = tokenType::Int;
    {
      bool _fpoint = false;
      bool _digit = false;
      bool _halt = false;
      do {
        switch (get.chr) {
          case '+':
          case '-': {
            if (token.text.length()) {
              token.family = tokenType::Symbol;
              _halt = true;
            }
            break;
          }
          case '.': {
            if (_fpoint) {
              token.family = tokenType::Symbol;
              _halt = true;
            } else {
              token.family = tokenType::Float;
              _fpoint = true;
            }
            break;
          }
          default: {
            _digit = _digit ? true : static_cast<bool>(isdigit(get.chr));
          }
        }

        if (_halt) break;

        token.text.push_back(get.chr);
        getchar();

      } while (isdigit(get.chr) || get.chr == '.');

      if (!_digit) token.family = tokenType::Symbol;
    }

    getSymbol(token);

    return;
  }

 public:
  inline void discard() noexcept {
    if (get.chr != '\n') {
      cin.ignore(INT_MAX, '\n');
      cin.clear();
      get = char_t{'\n'};
    }
    return;
  }

  inline void refresh() noexcept {

    if (line != 1 || column != 1) {
      line = 1;
      if (get.chr != '\n') {
        column = 2;
        get.line = 1;
        get.column = 1;
      } else {
        column = 1;
      }
      while (get.chr != '\n' && iswspace(get.chr)) {
        getchar();
      }
      if (get.chr == ';') {
        while (get.chr != '\n' && get.chr != EOF) getchar();
      }
    }

    if (get.chr == '\n') {
      line = 1;
      column = 1;
    }

    return;
  }

  inline token_t* getNextToken() {
    flush();
    token_t* token = new token_t{
      .line = get.line,
      .column = get.column
    };
    try {
      if (isdigit(get.chr)) {

        getNumeric(*token);

      } else {
        switch (get.chr) {
          case '\u0022': /* " */ {
            getStringLiteral(*token);
            break;
          }
          case '\u0027': /* ' */ {
            token->text = "quote";
            token->family = tokenType::Quote;
            getchar();
            break;
          }
          case '\u0028': /* ( */ {
            /*if (cin.peek() == ')') {
              token->text = "()";
              token->family = tokenType::Nil;
              getchar();
            } else {*/
            token->text = "(";
            token->family = tokenType::LeftParen;
            /*}*/
            getchar();
            break;
          }
          case '\u0029': /* ) */ {
            token->text = ")";
            token->family = tokenType::RightParen;
            getchar();
            break;
          }
          case '\u002B': /* + */
          case '\u002D': /* - */
          case '\u002E': /* . */ {
            if (get.chr == '.' && match(cin.peek(), TERMINATE_CHARS)) {
              token->text = ".";
              token->family = tokenType::Dot;
              getchar();
            } else {
              getNumeric(*token);
            }
            break;
          }
          case '\n': {
            ASSERT(false, UNEXPECTED_BEHAVIOR);
            break;
          }
          case EOF: {
            throw status_t{
              .code = status_code::EndOfFileEncountered,
              .body = END_OF_FILE_ENCOUNTERD
            };
          }
          default: {
            getSymbol(*token);
            
            if (token->text == "nil" || token->text == "#f") {
              token->family = tokenType::Nil;
            } else if (token->text == "t" || token->text == "#t") {
              token->family = tokenType::T;
            }
          }
        }
      }
    } catch (const status_t& err) {
      delete token;
      throw;
    }

    return token;
  }

};

class Parser {
 private:
  Scanner& scanner;

  token_t* buf = nullptr;

  template <size_t N>
  static bool match(const token_t& token, const tokenType (&__arr)[N]) noexcept {
    for (const tokenType& __t: __arr) {
      if (token.family == __t) return true;
    }
    return false;
  }

  /**
   * Get token and then update `buf` if `buf` is empty.
   */
  inline token_t* next() {
    buf = (buf ? buf : scanner.getNextToken());
    return buf;
  }

  inline token_t* next(const tokenType& __t) {
    buf = (buf ? buf : scanner.getNextToken());
    return (buf->family == __t) ? buf : nullptr;
  }

  inline token_t* next(const nodeType& __t) {
    buf = (buf ? buf : scanner.getNextToken());
    token_t* token = nullptr;
    switch (__t) {
      case nodeType::Atom: {
        token = (isatom(*buf)) ? buf : nullptr;
        break;
      }
      case nodeType::Expr: {
        token = (!isatom(*buf)) ? buf : nullptr;
        break;
      }
    }
    return token;
  }

  token_t* fetch() {
    token_t* token = next();
    buf = nullptr;
    return token;
  }

  /**
   * Get next token if and only if the text was matched.
   */
  token_t* fetch(const tokenType& __t) {
    token_t* token = next();
    if (token->family == __t) {
      buf = nullptr;
    } else {
      token = nullptr;
    }
    return token;
  }

  token_t* fetch(const nodeType& __t) {
    token_t* token = next();
    switch (__t) {
      case nodeType::Atom: {
        if (isatom(*token)) {
          buf = nullptr;
        } else {
          token = nullptr;
        }
        break;
      }
      case nodeType::Expr: {
        if (!isatom(*token)) {
          buf = nullptr;
        } else {
          token = nullptr;
        }
        break;
      }
    }
    return token;
  }

  token_t* expect(const string& __s, const bool& atom_override = false) {
    token_t* token = next();
    if (token->text == __s || (atom_override && isatom(*buf))) {
      buf = nullptr;
    } else {
      status_t err;
      err.code = status_code::UnexpectedToken;
      err.body = UNEXPECTED_TOKEN_HEADER;

      if (atom_override) err.body.append("atom");
      if (atom_override && __s.length()) err.body.append(" or ");
      if (__s.length()) err.body.append("'").append(__s).append("'");
      
      err.body.append(UNEXPECTED_TOKEN_BODY);

      (err.body += " at Line ") += to_string(token->line);
      (err.body += " Column ") += to_string(token->column);

      err.body.append(" is >>").append(token->text).append("<<");

      fetch();

      throw err;
    }
    return token;
  }

  /**
   * <expr> ::= LEFT-PAREN <expr> <expr>* (. <expr>)? RIGHT-PAREN
   *            | QUOTE <expr>
   *            | <atom>
   *            | LEFT-PAREN RIGHT-PAREN
   */
  node_t* analyExpr() {
    // the root node for this loop
    node_t* node = nullptr;
    // public used container to hold the value fetch from `buf`
    token_t* bin = nullptr;

    try {
      if ((bin = fetch(tokenType::LeftParen))) {

        if (next()->family == tokenType::RightParen) {
          bin->family = tokenType::Nil;
          bin->text = "()";
          node = new node_t(nodeType::Atom, bin);
        } else {
          
          delete bin;
          
          node = new node_t(
            nodeType::Expr,
            nullptr,
            analyExpr(),
            nullptr
          );

          node_t* curr = node;
          while (!match(*next(), {tokenType::RightParen, tokenType::Dot})) {
            curr->right = new node_t(
              nodeType::Expr,
              nullptr,
              analyExpr(),
              nullptr
            );

            curr = curr->right;
          }

          if ((bin = fetch(tokenType::Dot))) {
            delete bin;
            curr->right = analyExpr();
          }
        }
        
        bin = expect(")");
        delete bin;

      } else if (next(tokenType::Quote)) {
        
        /**
         * @warning
         * C++14 or lower version
         * DOES NOT guarantee that arguments are executed in order
         */
        node = new node_t(nodeType::Expr);
        node->left = new node_t(nodeType::Atom, fetch(tokenType::Quote)),
        node->right = new node_t(
          nodeType::Expr,
          nullptr,
          analyExpr(),
          nullptr
        );

      } else {
        
        node = new node_t(nodeType::Atom, expect("(", true));

      }
    } catch (const status_t& err) {
      /**
       * @note
       * Unused `bin` is always released immediately,
       * so there is no need to worry about memory leaks if an exception
       * is thrown during the execution of a deeper `analyExpr()`.
       */
      delete node;
      throw;
    }
    return node;
  }

  /**
   * <atom> ::= SYMBOL | INT | FLOAT | STRING | NIL | T | LEFT-PAREN RIGHT-PAREN
   */
  static inline bool isatom(const token_t& token) {
    switch (token.family) {
      case tokenType::Int:
      case tokenType::String:
      case tokenType::Float:
      case tokenType::Nil:
      case tokenType::T:
      case tokenType::Symbol: return true;
      default: return false;
    }
  }

 public:
  Parser(Scanner& __obj) : scanner(__obj) {}
  
  inline node_t* build() {
    scanner.refresh();
    return analyExpr();
  }

};

class Executor {
#if defined(TEST) 
 public:
#else
 private:
#endif
  Scanner& scanner;
  Parser& parser;

  bool verbose_mode = true;
  
  const Segment reserved = {
    RESERVED_FUNCTION(Executor::add, "+"),
    RESERVED_FUNCTION(Executor::sub, "-"),
    RESERVED_FUNCTION(Executor::mul, "*"),
    RESERVED_FUNCTION(Executor::div, "/"),
    RESERVED_FUNCTION(Executor::eq, "="),
    RESERVED_FUNCTION(Executor::gt, ">"),
    RESERVED_FUNCTION(Executor::lt, "<"),
    RESERVED_FUNCTION(Executor::ge, ">="),
    RESERVED_FUNCTION(Executor::le, "<="),
    RESERVED_FUNCTION(Executor::_and, "and"),
    RESERVED_FUNCTION(Executor::is_atom, "atom?"),
    RESERVED_FUNCTION(Executor::begin, "begin"),
    RESERVED_FUNCTION(Executor::is_boolean, "boolean?"),
    RESERVED_FUNCTION(Executor::car, "car"),
    RESERVED_FUNCTION(Executor::cdr, "cdr"),
    RESERVED_FUNCTION(Executor::cons, "cons"),
    RESERVED_FUNCTION(Executor::cond, "cond"),
    RESERVED_FUNCTION(Executor::clean, "clean-environment"),
    RESERVED_FUNCTION(Executor::create_error_object, "create-error-object"),
    RESERVED_FUNCTION(Executor::define, "define"),
    RESERVED_FUNCTION(Executor::display_string, "display-string"),
    RESERVED_FUNCTION(Executor::is_equal, "equal?"),
    RESERVED_FUNCTION(Executor::is_eqv, "eqv?"),
    RESERVED_FUNCTION(Executor::is_error_object, "error-object?"),
    RESERVED_FUNCTION(Executor::eval, "eval"),
    RESERVED_FUNCTION(Executor::exit, "exit"),
    RESERVED_FUNCTION(Executor::_if, "if"),
    RESERVED_FUNCTION(Executor::is_interger, "integer?"),
    RESERVED_FUNCTION(Executor::lambda, "lambda"),
    RESERVED_FUNCTION(Executor::let, "let"),
    RESERVED_FUNCTION(Executor::list, "list"),
    RESERVED_FUNCTION(Executor::is_list, "list?"),
    RESERVED_FUNCTION(Executor::newline, "newline"),
    RESERVED_FUNCTION(Executor::_not, "not"),
    RESERVED_FUNCTION(Executor::is_null, "null?"),
    RESERVED_FUNCTION(Executor::is_number, "number?"),
    RESERVED_FUNCTION(Executor::ntos, "number->string"),
    RESERVED_FUNCTION(Executor::_or, "or"),
    RESERVED_FUNCTION(Executor::is_pair, "pair?"),
    RESERVED_FUNCTION(Executor::quote, "quote"),
    RESERVED_FUNCTION(Executor::read, "read"),
    RESERVED_FUNCTION(Executor::is_real, "real?"),
    RESERVED_FUNCTION(Executor::set, "set!"),
    RESERVED_FUNCTION(Executor::is_string, "string?"),
    RESERVED_FUNCTION(Executor::is_string_lt, "string<?"),
    RESERVED_FUNCTION(Executor::is_string_gt, "string>?"),
    RESERVED_FUNCTION(Executor::is_string_eq, "string=?"),
    RESERVED_FUNCTION(Executor::string_append, "string-append"),
    RESERVED_FUNCTION(Executor::is_symbol, "symbol?"),
    RESERVED_FUNCTION(Executor::stos, "symbol->string"),
    RESERVED_FUNCTION(Executor::verbose, "verbose"),
    RESERVED_FUNCTION(Executor::is_verbose, "verbose?"),
    RESERVED_FUNCTION(Executor::write, "write")
  };

  Segment global;

  deque<Page> stack = {Page()};   // there's always at least 1 page exists

  // Reserved function - `verbose?`
  ContainerPtr is_verbose(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 0), INCORRECT_NUMBER_OF_ARGS + "verbose?");
    return make_shared<Container>(verbose_mode);
  }

  // Reserved function - `verbose`
  ContainerPtr verbose(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "verbose");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      verbose_mode = !(
        args->type == containType::Boolean &&
        *cast<bool*>(args) == false
      )
    );
  }

  // Reserved function - `set!`
  ContainerPtr set(STANDARD_PARAMETERS) {
    enum class Format {
      undefined,
      Symbol,
      Lambda
    };

    Format format = Format::undefined;
    
    string args_1;
    ContainerPtr args_2 = nullptr;
    
    try {
      // check if the argument is at least two
      RUNTIME(atleast(root, 2), ILLEGAL_SET_FORMAT);
      // check if the 1st argument is symbol or function declaration
      const node_t* node = root->right;
      if (issymbol(node->left)) /* (set! num 123) */ {
        
        // symbol declaration must having two arguments exactly
        RUNTIME(exact(root, 2), ILLEGAL_SET_FORMAT);
        args_1 = node->left->body->text;
        // check alias is not reserved words
        RUNTIME(reserved.find(args_1) == reserved.end(), ILLEGAL_SET_FORMAT);
        format = Format::Symbol;

      } else if (isridge(node->left)) /* (set! (func x y) (+ x y)) */ {
        
        // check function alias is symbol
        RUNTIME(issymbol(node->left->left), ILLEGAL_SET_FORMAT);
        args_1 = node->left->left->body->text;
        // check function alias is not reserved words
        RUNTIME(reserved.find(args_1) == reserved.end(), ILLEGAL_SET_FORMAT);
        format = Format::Lambda;
      
      } else RUNTIME(false, ILLEGAL_SET_FORMAT);

    } catch (status_t& err) {
      // attach the struct of define call for error display
      err.attachment = make_shared<Container>(root);
      throw;
    }
    // valid format, resolve remaining arguments
    switch (format) {
      case Format::Symbol: {
        args_2 = run(root->right->right->left, level);
        break;
      }
      case Format::Lambda: {
        const node_t* const pseudo_root = new node_t(
          nodeType::Expr,
          nullptr,
          new node_t(
            nodeType::Atom,
            new token_t{
              .family = tokenType::Symbol,
              .text = args_1
            }
          ),
          new node_t(
            nodeType::Expr,
            nullptr,
            root->right->left->right,
            root->right->right
          )
        );
        try {
          const string error_msg = ILLEGAL_SET_FORMAT;
          args_2 = lambda(pseudo_root, level+1, &error_msg);
        } catch (status_t& err) {
          pseudo_root->right->left = nullptr;
          pseudo_root->right->right = nullptr;
          delete pseudo_root;
          throw;
        }
        pseudo_root->right->left = nullptr;
        pseudo_root->right->right = nullptr;
        delete pseudo_root;
        break;
      }
      default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
    }

    // different with `define`, `set!` have to check local variable first
    ContainerPtr* matched = mapping(args_1);
    if (matched) {
      *matched = args_2;
    } else {
      global[args_1] = args_2;
    }

    return args_2;
  }

  // Reserved function - `eval`
  ContainerPtr eval(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "eval");
    ContainerPtr retval = nullptr;
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    const node_t* const &pseudo_root = backtrack(args);
    try {
      NoReturnValue(retval = run(pseudo_root, 0));
    } catch (const status_t& err) {
      delete pseudo_root;
      throw;
    }
    delete pseudo_root;
    RUNTIME_EXTEND(
      retval,
      status_info::NoReturnValue,
      NO_RETURN_VALUE,
      make_shared<Container>(root)
    );
    return retval;
  }

  // Reserved function - `number->string`
  ContainerPtr ntos(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "number->string");
    ContainerPtr retval = nullptr;
    UnboundParameter(retval = run(root->right->left, level));
    switch (retval->type) {
      case containType::Int: {
        retval = make_shared<Container>(
          string("\"") + to_string(*cast<int*>(retval)) + "\""
        );
        break;
      }
      case containType::Float: {
        char _buf[32];
        snprintf(_buf, sizeof(_buf), "%.3f", *cast<double*>(retval));
        retval = make_shared<Container>(string("\"") + _buf + "\"");
        break;
      }
      default: RUNTIME_EXTEND(
        false,
        status_info::general,
        NTOS_WITH_INCORRECT_ARG_TYPE,
        retval
      );
    }
    return retval;
  }

  // Reserved function - `symbol->string`
  ContainerPtr stos(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "symbol->string");
    ContainerPtr retval = nullptr;
    UnboundParameter(retval = run(root->right->left, level));
    switch (retval->type) {
      case containType::String: {
        break;
      }
      case containType::Node: {
        const node_t* const node = cast<node_t*>(retval);
        if (
          node->type == nodeType::Atom && node->body->family == tokenType::Symbol
        ) {
          retval = make_shared<Container>(string("\"") + node->body->text + "\"");
          break;
        }
      }
      default: RUNTIME_EXTEND(
        false,
        status_info::general,
        STOS_WITH_INCORRECT_ARG_TYPE,
        retval
      );
    }
    return retval;
  }

  // Reserved function - `newline`
  ContainerPtr newline(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 0), INCORRECT_NUMBER_OF_ARGS + "newline");
    cout << '\n';
    return make_shared<Container>(false);
  }

  // Reserved function - `error-object?`
  ContainerPtr is_error_object(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "error-object?");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::Error
    );
  }

  // Reserved function - `create-error-object`
  ContainerPtr create_error_object(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "create-error-object");
    ContainerPtr retval = make_shared<Container>();
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    switch (args->type) {
      case containType::Error:
      case containType::String: {
        retval->type = containType::Error;
        retval->value = fetch<string*>(args);
        break;
      }
      default: RUNTIME_EXTEND(
        false,
        status_info::general,
        SHOWSTR_WITH_INCORRECT_ARG_TYPE,
        args
      );
    }
    return retval;
  }

  // Reserved function - `display-string`
  ContainerPtr display_string(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "display-string");
    ContainerPtr retval = nullptr;
    UnboundParameter(retval = run(root->right->left, level));
    switch (retval->type) {
      case containType::Error:
      case containType::String: {
        // redundant processing, but safety first
        const string& raw_string = *cast<string*>(retval);
        size_t from = raw_string.find_first_not_of(' ');
        size_t to = raw_string.find_last_not_of(' ');
        const size_t length = raw_string.length();
        from = (
          (from != string::npos && raw_string.at(from) == '"') ? from : -1
        );
        to = (
          (to != string::npos && raw_string.at(to) == '"') ? to : length
        );
        cout << raw_string.substr(from + 1, to - from - 1);
        break;
      }
      default: RUNTIME_EXTEND(
        false,
        status_info::general,
        SHOWSTR_WITH_INCORRECT_ARG_TYPE,
        retval
      );
    }
    return retval;
  }

  // Reserved function - `write`
  ContainerPtr write(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "write");
    ContainerPtr retval = nullptr;
    UnboundParameter(retval = run(root->right->left, level));
    cout << stringify(retval);
    return retval;
  }

  // Reserved function - `read`
  ContainerPtr read(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 0), INCORRECT_NUMBER_OF_ARGS + "read");
    ContainerPtr retval = make_shared<Container>();
    try {
      retval->value = parser.build();
      retval->type = containType::Node;
    } catch (const status_t& err) {
      switch (err.code) {
        case status_code::EndOfFileEncountered:
        case status_code::UnexpectedToken:
          scanner.discard();
        case status_code::NoClosingQuote: {
          retval->value = new string(string("\"") + err.body + "\"");
          retval->type = containType::Error;
          break;
        }
        default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
      }
    }
    return purify(retval);
  }

  // Reserved function - `lambda`
  ContainerPtr lambda(STANDARD_PARAMETERS) {
    /**
     * @note
     * `lambda` help `define` to resolve naming function definition,
     *  so error massage have two types:
     *  - ILLEGAL_LAMBDA_FORMAT
     *  - ILLEGAL_DEFINE_FORMAT
     *  - ILLEGAL_SET_FORMAT
     */
    ASSERT((root->left && root->left->body), UNEXPECTED_BEHAVIOR);
    const string error_msg = (
      appendix ? *static_cast<const string*>(appendix) : ILLEGAL_LAMBDA_FORMAT
    );
    try {
      RUNTIME(atleast(root, 2), error_msg);
      {
        const node_t* node = root->right->left;
        RUNTIME(islist(node), error_msg);
        while (isridge(node)) {
          // check parameter is symbol
          RUNTIME(issymbol(node->left), error_msg);
          // check parameter is not reserved words
          RUNTIME(
            reserved.find(node->left->body->text) == reserved.end(),
            error_msg
          );
          node = node->right;
        }
      }
    } catch (status_t& err) {
      err.attachment = make_shared<Container>(root);
      throw;
    }

    // `containType::Lambda` is a variant of `containType::Node`
    const string& alias = root->left->body->text;
    ContainerPtr retval = make_shared<Container>(root->right, alias);
    retval->type = containType::Lambda;
    
    return retval;
  }
  
  // Reserved function - `let`
  ContainerPtr let(STANDARD_PARAMETERS) {
    try {
      // format check 1: `let` must have at least 2 arguments
      RUNTIME(atleast(root, 2), ILLEGAL_LET_FORMAT);
      // format check 2: first arguments must be nil or a series of dot pair
      {
        const node_t* node = root->right->left;
        while (isridge(node)) {
          RUNTIME(exact(node->left, 1), ILLEGAL_LET_FORMAT);
          RUNTIME(issymbol(node->left->left), ILLEGAL_LET_FORMAT);
          RUNTIME(
            reserved.find(node->left->left->body->text) == reserved.end(),
            ILLEGAL_LET_FORMAT
          );
          node = node->right;
        }
      }
    } catch (status_t& err) {
      err.attachment = make_shared<Container>(root);
      throw;
    }

    // valid format
    // create a new stack area and register local variables
    Page& page = stack.back();      // get current page
    Segment segment = Segment();    // create a new segment
    {
      const node_t* node = root->right->left;
      while (isridge(node)) {
        const node_t* var = node->left;
        Important(segment[var->left->body->text] = run(var->right->left, level+1));
        node = node->right;
      }
    }
    // defer push, prevent behavior conflict with `mapping()`
    page.push_back(move(segment));
    // execute all remaining arguments of `let`
    ContainerPtr retval = nullptr;
    try {
      const node_t* node = root->right->right;
      while (isridge(node)) {
        retval = nullptr;
        IgnoreNoReturnValue(retval = run(node->left, level));
        node = node->right;
      }
    } catch (const status_t& err) {
      page.pop_back();  // garbage collection
      throw;
    }
    page.pop_back();  // garbage collection

    RUNTIME_EXTEND(
      retval,
      status_info::NoReturnValue,
      NO_RETURN_VALUE,
      make_shared<Container>(root)
    );

    return retval;
  }

  // Reserved function - `begin`
  ContainerPtr begin(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 1), INCORRECT_NUMBER_OF_ARGS + "begin");
    const node_t* node = root->right;
    ContainerPtr retval = nullptr;
    while (isridge(node)) {
      retval = nullptr;
      IgnoreNoReturnValue(retval = run(node->left, level));
      node = node->right;
    }
    RUNTIME_EXTEND(
      retval,
      status_info::NoReturnValue,
      NO_RETURN_VALUE,
      make_shared<Container>(root)
    );
    return retval;
  }

  // Reserved function - `cond`
  ContainerPtr cond(STANDARD_PARAMETERS) {
    try {
      // format check 1: must have at least 1 statement
      RUNTIME(atleast(root, 1), ILLEGAL_COND_FORMAT);
      // format check 2: every statement must have 1+ arguments
      {
        const node_t* node = root->right;
        while (isridge(node)) {
          RUNTIME(atleast(node->left, 1), ILLEGAL_COND_FORMAT);
          node = node->right;
        }
      }
    } catch (status_t& err) {
      err.attachment = make_shared<Container>(root);
      throw;
    }

    ContainerPtr retval = nullptr;
    const node_t* node = root->right;
    while (isridge(node)) {
      const node_t* const &head = node->left;
      const bool is_last_elem = isnil(node->right);
      const bool captured_else = (
        issymbol(head->left) && head->left->body->text == "else"
      );
      bool cond = false;
      /**
       * if is not last element, or is last element but doesn't hold
       * keyword `else`, then must to resolve its condition statement
       * @brief not last one with else -> resolve it
       */
      if (!(is_last_elem && captured_else)) {
        ContainerPtr cond_statement = nullptr;
        UnboundTestCondition(cond_statement = run(head->left, level+1));
        switch (cond_statement->type) {
          case containType::Boolean: {
            cond = *cast<bool*>(cond_statement);
            break;
          }
          case containType::Node: {
            const node_t* const &temp = cast<node_t*>(cond_statement);
            if (temp->type == nodeType::Atom) {
              switch (temp->body->family) {
                case tokenType::Nil: {
                  cond = false;
                  break;
                }
                default: cond = true;
              }
            } else {
              cond = true;
            }
            break;
          }
          default: cond = true;
        }
      } else {
        cond = true;  // else-statement
      }
      
      // if `ture`, resovle its following expression
      if (cond) {
        const node_t* _node = head->right;
        while (isridge(_node)) {
          retval = nullptr;
          IgnoreNoReturnValue(retval = run(_node->left, level+1));
          _node = _node->right;
        }
        break;
      }

      node = node->right;
    }
    RUNTIME_EXTEND(
      retval,
      status_info::NoReturnValue,
      NO_RETURN_VALUE,
      make_shared<Container>(root)
    );
    return retval;
  }

  // Reserved function - `if`
  ContainerPtr _if(STANDARD_PARAMETERS) {
    try {
      RUNTIME(exact(root, 3), INCORRECT_NUMBER_OF_ARGS + "if");
    } catch (const status_t& err) {
      RUNTIME(exact(root, 2), INCORRECT_NUMBER_OF_ARGS + "if");
    }
    ContainerPtr retval = nullptr;
    bool cond;
    {
      ContainerPtr _cond = nullptr;
      UnboundTestCondition(_cond = run(root->right->left, level));
      switch (_cond->type) {
        case containType::Boolean: {
          cond = *cast<bool*>(_cond);
          break;
        }
        case containType::Node: {
          const node_t* const &node = cast<node_t*>(_cond);
          if (node->type == nodeType::Atom) {
            switch (node->body->family) {
              case tokenType::Nil: {
                cond = false;
                break;
              }
              default: cond = true;
            }
          } else {
            cond = true;
          }
          break;
        }
        default: cond = true;
      }
    }
    if (cond) {
      NoReturnValue(retval = run(root->right->right->left, level));
    } else {
      RUNTIME_EXTEND(
        exact(root, 3),
        status_info::NoReturnValue,
        NO_RETURN_VALUE,
        make_shared<Container>(root)
      );
      NoReturnValue(retval = run(root->right->right->right->left, level));
    }
    return retval;
  }

  // Reserved function - `equal?`
  ContainerPtr is_equal(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 2), INCORRECT_NUMBER_OF_ARGS + "equal?");
    ContainerPtr args_1 = nullptr;
    UnboundParameter(args_1 = run(root->right->left, level));
    ContainerPtr args_2 = nullptr;
    UnboundParameter(args_2 = run(root->right->right->left, level));
    ContainerPtr retval = make_shared<Container>(false);
    bool& value = *cast<bool*>(retval);
    switch (args_1->type) {
      case containType::Int: {
        switch (args_2->type) {
          case containType::Int: /* [Int, Int] */ {
            value = *cast<int*>(args_1) == *cast<int*>(args_2);
            break;
          }
          case containType::Float: /* [Int, Float] */ {
            value = *cast<int*>(args_1) == *cast<double*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Float: {
        switch (args_2->type) {
          case containType::Int: /* [Float, Int] */ {
            value = *cast<double*>(args_1) == *cast<int*>(args_2);
            break;
          }
          case containType::Float: /* [Float, Float] */ {
            value = *cast<double*>(args_1) == *cast<double*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Boolean: {
        switch (args_2->type) {
          case containType::Boolean: /* [Boolean, Boolean] */ {
            value = *cast<bool*>(args_1) == *cast<bool*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Error:
      case containType::String: {
        switch (args_2->type) {
          case containType::Error:
          case containType::String: /* [String, String] */ {
            value = *cast<string*>(args_1) == *cast<string*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Node: {
        const node_t* const node_1 = cast<node_t*>(args_1);
        if (node_1->type == nodeType::Atom) {
          switch (args_2->type) {
            case containType::Node: /* [Node, Node] */ {
              const node_t* const node_2 = cast<node_t*>(args_2);
              value = (*node_1 == *node_2);
              break;
            }
            default: value = false;
          }
        } else {
          // here is the difference with `eqv?`
          switch (args_2->type) {
            case containType::Node: /* [Node(expr), Node(any)] */ {
              const node_t* const node_2 = cast<node_t*>(args_2);
              value = (*node_1 == *node_2);
              break;
            }
            default: value = false;
          }
        }
        break;
      }
      default: value = (args_1 == args_2);
    }
    return retval;
  }

  // Reserved function - `eqv?`
  ContainerPtr is_eqv(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 2), INCORRECT_NUMBER_OF_ARGS + "eqv?");
    ContainerPtr args_1 = nullptr;
    UnboundParameter(args_1 = run(root->right->left, level));
    ContainerPtr args_2 = nullptr;
    UnboundParameter(args_2 = run(root->right->right->left, level));
    ContainerPtr retval = make_shared<Container>(false);
    bool& value = *cast<bool*>(retval);
    /**
     * Int <-> Int, Float, Node
     * Float <-> Int, Float, Node
     * String <-> String, Node
     * Node := Int, Float, String
     */
    switch (args_1->type) {
      case containType::Int: {
        switch (args_2->type) {
          case containType::Int: /* [Int, Int] */ {
            value = *cast<int*>(args_1) == *cast<int*>(args_2);
            break;
          }
          case containType::Float: /* [Int, Float] */ {
            value = *cast<int*>(args_1) == *cast<double*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Float: {
        switch (args_2->type) {
          case containType::Int: /* [Float, Int] */ {
            value = *cast<double*>(args_1) == *cast<int*>(args_2);
            break;
          }
          case containType::Float: /* [Float, Float] */ {
            value = *cast<double*>(args_1) == *cast<double*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Boolean: {
        switch (args_2->type) {
          case containType::Boolean: /* [Boolean, Boolean] */ {
            value = *cast<bool*>(args_1) == *cast<bool*>(args_2);
            break;
          }
          default: value = false;
        }
        break;
      }
      case containType::Node: {
        const node_t* const node_1 = cast<node_t*>(args_1);
        if (node_1->type == nodeType::Atom) {
          switch (args_2->type) {
            case containType::Node: /* [Node, Node] */ {
              const node_t* const node_2 = cast<node_t*>(args_2);
              if (node_2->type == nodeType::Atom) {
                value = (*node_1 == *node_2);
              } else {
                value = (args_1 == args_2);
              }
              break;
            }
            default: value = false;
          }
        } else {
          value = (args_1 == args_2);
        }
        break;
      }
      default: value = (args_1 == args_2);
    }
    return retval;
  }

  // Reserved function - `string-append`
  ContainerPtr string_append(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "string-append");
    const node_t* node = root->right;
    string base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          base = *cast<string*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          PUSHSTR_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          string& temp = *cast<string*>(args);
          base.pop_back();        // remove the last '"' of base
          base += temp.substr(1); // ignore the first '"' of temp
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          PUSHSTR_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(base);
  }
  
  // Reserved function - `string<?`
  ContainerPtr is_string_lt(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "string<?");
    const node_t* node = root->right;
    bool response = true;
    string base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          base = *cast<string*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SLT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          if (response) {
            response = base < *cast<string*>(args);
            base = *cast<string*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SLT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `string>?`
  ContainerPtr is_string_gt(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "string>?");
    const node_t* node = root->right;
    bool response = true;
    string base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          base = *cast<string*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SGT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          if (response) {
            response = base > *cast<string*>(args);
            base = *cast<string*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SGT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `string=?`
  ContainerPtr is_string_eq(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "string=?");
    const node_t* node = root->right;
    bool response = true;
    string base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          base = *cast<string*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SEQ_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Error:
        case containType::String: {
          if (response) {
            response = base == *cast<string*>(args);
            base = *cast<string*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SEQ_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `=`
  ContainerPtr eq(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "=");
    const node_t* node = root->right;
    bool response = true;
    double base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          base = *cast<int*>(args);
          break;
        }
        case containType::Float: {
          base = *cast<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          EQ_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          if (response) {
            response = base == *cast<int*>(args);
            base = *cast<int*>(args);
          }
          break;
        }
        case containType::Float: {
          if (response) {
            response = base == *cast<double*>(args);
            base = *cast<double*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          EQ_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `<=`
  ContainerPtr le(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "<=");
    const node_t* node = root->right;
    bool response = true;
    double base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          base = *cast<int*>(args);
          break;
        }
        case containType::Float: {
          base = *cast<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          LE_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          if (response) {
            response = base <= *cast<int*>(args);
            base = *cast<int*>(args);
          }
          break;
        }
        case containType::Float: {
          if (response) {
            response = base <= *cast<double*>(args);
            base = *cast<double*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          LE_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `>=`
  ContainerPtr ge(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + ">=");
    const node_t* node = root->right;
    bool response = true;
    double base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          base = *cast<int*>(args);
          break;
        }
        case containType::Float: {
          base = *cast<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          GE_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          if (response) {
            response = base >= *cast<int*>(args);
            base = *cast<int*>(args);
          }
          break;
        }
        case containType::Float: {
          if (response) {
            response = base >= *cast<double*>(args);
            base = *cast<double*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          GE_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `<`
  ContainerPtr lt(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "<");
    const node_t* node = root->right;
    bool response = true;
    double base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          base = *cast<int*>(args);
          break;
        }
        case containType::Float: {
          base = *cast<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          LT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          if (response) {
            response = base < *cast<int*>(args);
            base = *cast<int*>(args);
          }
          break;
        }
        case containType::Float: {
          if (response) {
            response = base < *cast<double*>(args);
            base = *cast<double*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          LT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `>`
  ContainerPtr gt(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + ">");
    const node_t* node = root->right;
    bool response = true;
    double base;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          base = *cast<int*>(args);
          break;
        }
        case containType::Float: {
          base = *cast<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          GT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
    }
    node = node->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          if (response) {
            response = base > *cast<int*>(args);
            base = *cast<int*>(args);
          }
          break;
        }
        case containType::Float: {
          if (response) {
            response = base > *cast<double*>(args);
            base = *cast<double*>(args);
          }
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          GT_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    return make_shared<Container>(response);
  }

  // Reserved function - `or`
  ContainerPtr _or(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "or");
    ContainerPtr retval = nullptr;
    ContainerPtr args = nullptr;
    const node_t* node = root->right;
    while (isridge(node) && (retval == nullptr)) {
      UnboundCondition(args = run(node->left, level));
      switch (args->type) {
        case containType::Boolean: {
          if (*cast<bool*>(args) == true) {
            retval = args;
          }
          break;
        }
        default: retval = args;
      }
      node = node->right;
    }
    return retval ? retval : args;
  }

  // Reserved function - `and`
  ContainerPtr _and(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "and");
    ContainerPtr retval = nullptr;
    ContainerPtr args = nullptr;
    const node_t* node = root->right;
    while (isridge(node) && (retval == nullptr)) {
      UnboundCondition(args = run(node->left, level));
      switch (args->type) {
        case containType::Boolean: {
          if (*cast<bool*>(args) == false) {
            retval = args;
          }
          break;
        }
        default: break;
      }
      node = node->right;
    }
    return retval ? retval : args;
  }

  // Reserved function - `not`
  ContainerPtr _not(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "not");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::Boolean && *cast<bool*>(args) == false
    );
  }

  // Reserved function - `/`
  ContainerPtr div(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "/");
    ContainerPtr retval = make_shared<Container>();
    const node_t* node = root->right;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          retval->type = containType::Int;
          retval->value = fetch<int*>(args);
          break;
        }
        case containType::Float: {
          retval->type = containType::Float;
          retval->value = fetch<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          DIV_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      // deciding on the return type and caculate at the same time
      switch (retval->type) {
        case containType::Int: {
          switch (args->type) {
            case containType::Int: {
              int& total = *cast<int*>(retval);
              int& value = *cast<int*>(args);
              RUNTIME(value, string(DIVISION_BY_ZERO) + "/");
              total /= value;
              break;
            }
            case containType::Float: /* implicit conversion */ {
              int total = *cast<int*>(retval);
              double& value = *cast<double*>(args);
              RUNTIME(value, string(DIVISION_BY_ZERO) + "/");
              delete cast<int*>(retval);
              retval->type = containType::Float;
              retval->value = new double(total / value);
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              DIV_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        case containType::Float: {
          double& total = *cast<double*>(retval);
          switch (args->type) {
            case containType::Int: {
              int& value = *cast<int*>(args);
              RUNTIME(value, string(DIVISION_BY_ZERO) + "/");
              total /= value;
              break;
            }
            case containType::Float: {
              double& value = *cast<double*>(args);
              RUNTIME(value, string(DIVISION_BY_ZERO) + "/");
              total /= value;
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              DIV_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        default: ASSERT(false, UNEXPECTED_BEHAVIOR);
      }
      // move foward
      node = node->right;
    }
    return retval;
  }

  // Reserved function - `*`
  ContainerPtr mul(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "*");
    ContainerPtr retval = make_shared<Container>();
    const node_t* node = root->right;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          retval->type = containType::Int;
          retval->value = fetch<int*>(args);
          break;
        }
        case containType::Float: {
          retval->type = containType::Float;
          retval->value = fetch<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          MUL_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      // deciding on the return type and caculate at the same time
      switch (retval->type) {
        case containType::Int: {
          switch (args->type) {
            case containType::Int: {
              int& total = *cast<int*>(retval);
              total *= *cast<int*>(args);
              break;
            }
            case containType::Float: /* implicit conversion */ {
              int total = *cast<int*>(retval);
              delete cast<int*>(retval);
              retval->type = containType::Float;
              retval->value = new double(
                total * (*cast<double*>(args))
              );
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              MUL_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        case containType::Float: {
          double& total = *cast<double*>(retval);
          switch (args->type) {
            case containType::Int: {
              total *= *cast<int*>(args);
              break;
            }
            case containType::Float: {
              total *= *cast<double*>(args);
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              MUL_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        default: ASSERT(false, UNEXPECTED_BEHAVIOR);
      }
      // move foward
      node = node->right;
    }
    return retval;
  }

  // Reserved function - `-`
  ContainerPtr sub(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "-");
    ContainerPtr retval = make_shared<Container>();
    const node_t* node = root->right;
    {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      switch (args->type) {
        case containType::Int: {
          retval->type = containType::Int;
          retval->value = fetch<int*>(args);
          break;
        }
        case containType::Float: {
          retval->type = containType::Float;
          retval->value = fetch<double*>(args);
          break;
        }
        default: RUNTIME_EXTEND(
          false,
          status_info::general,
          SUB_WITH_INCORRECT_ARG_TYPE,
          args
        );
      }
      node = node->right;
    }
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      // deciding on the return type and caculate at the same time
      switch (retval->type) {
        case containType::Int: {
          switch (args->type) {
            case containType::Int: {
              int& total = *cast<int*>(retval);
              total -= *cast<int*>(args);
              break;
            }
            case containType::Float: /* implicit conversion */ {
              int total = *cast<int*>(retval);
              delete cast<int*>(retval);
              retval->type = containType::Float;
              retval->value = new double(
                total - *cast<double*>(args)
              );
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              SUB_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        case containType::Float: {
          double& total = *cast<double*>(retval);
          switch (args->type) {
            case containType::Int: {
              total -= *cast<int*>(args);
              break;
            }
            case containType::Float: {
              total -= *cast<double*>(args);
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              SUB_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        default: ASSERT(false, UNEXPECTED_BEHAVIOR);
      }
      // move foward
      node = node->right;
    }
    return retval;
  }

  // Reserved function - `+`
  ContainerPtr add(STANDARD_PARAMETERS) {
    RUNTIME(atleast(root, 2), INCORRECT_NUMBER_OF_ARGS + "+");
    ContainerPtr retval = make_shared<Container>(0);
    const node_t* node = root->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      // deciding on the return type and caculate at the same time
      switch (retval->type) {
        case containType::Int: {
          switch (args->type) {
            case containType::Int: {
              int& total = *cast<int*>(retval);
              total += *cast<int*>(args);
              break;
            }
            case containType::Float: /* implicit conversion */ {
              int total = *cast<int*>(retval);
              delete cast<int*>(retval);
              retval->type = containType::Float;
              retval->value = new double(total + *cast<double*>(args));
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              ADD_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        case containType::Float: {
          double& total = *cast<double*>(retval);
          switch (args->type) {
            case containType::Int: {
              total += *cast<int*>(args);
              break;
            }
            case containType::Float: {
              total += *cast<double*>(args);
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              ADD_WITH_INCORRECT_ARG_TYPE,
              args
            );
          }
          break;
        }
        default: ASSERT(false, UNEXPECTED_BEHAVIOR);
      }
      // move foward
      node = node->right;
    }
    return retval;
  }

  // Reserved function - `atom?`
  ContainerPtr is_atom(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "atom?");
    ContainerPtr retval = make_shared<Container>();
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type != containType::Node ||
      cast<node_t*>(args)->type == nodeType::Atom
    );
  }

  // Reserved function - `boolean?`
  ContainerPtr is_boolean(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "boolean?");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(args->type == containType::Boolean);
  }

  // Reserved function - `list?`
  ContainerPtr is_list(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "list?");
    ContainerPtr retval = make_shared<Container>();
    ContainerPtr args_1 = nullptr;
    UnboundParameter(args_1 = run(root->right->left, level));
    switch (args_1->type) {
      case containType::Node: {
        const node_t* const &head = cast<node_t*>(args_1);
        retval->value = new bool(islist(head));
        break;
      }
      default: {
        retval->value = new bool(false);
      }
    }
    retval->type = containType::Boolean;
    return retval;
  }

  // Reserved function - `symbol?`
  ContainerPtr is_symbol(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "symbol?");
    ContainerPtr retval = make_shared<Container>();
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    switch (args->type) {
      case containType::Node: {
        const node_t* const &head = cast<node_t*>(args);
        retval->value = new bool(
          head->type == nodeType::Atom &&
          head->body->family == tokenType::Symbol
        );
        break;
      }
      default: {
        retval->value = new bool(false);
      }
    }
    retval->type = containType::Boolean;
    return retval;
  }

  // Reserved function - `string?`
  ContainerPtr is_string(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "string?");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::String || args->type == containType::Error
    );
  }

  // Reserved function - `real?`
  ContainerPtr is_real(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "real?");
    return __is_number_prototype(root, level);
  }

  // Reserved function - `number?`
  ContainerPtr is_number(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "number?");
    return __is_number_prototype(root, level);
  }

  inline ContainerPtr __is_number_prototype(STANDARD_PARAMETERS) {
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::Int || args->type == containType::Float
    );
  }

  // Reserved function - `interger?`
  ContainerPtr is_interger(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "integer?");
    ContainerPtr retval = make_shared<Container>();
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(args->type == containType::Int);
  }

  // Reserved function - `null?`
  ContainerPtr is_null(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "null?");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::Boolean && *cast<bool*>(args) == false
    );
  }

  // Reserved function - `pair?`
  ContainerPtr is_pair(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "pair?");
    ContainerPtr args = nullptr;
    UnboundParameter(args = run(root->right->left, level));
    return make_shared<Container>(
      args->type == containType::Node &&
      isridge(cast<node_t*>(args))
    );
  }

  // Reserved function - `cdr`
  ContainerPtr cdr(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "cdr");

    // try to resolve the 1st argument
    ContainerPtr retval = nullptr;
    ContainerPtr args_1 = nullptr;
    UnboundParameter(args_1 = run(root->right->left, level));
    RUNTIME_EXTEND(
      (
        args_1->type == containType::Node &&
        isridge(cast<node_t*>(args_1))
      ),
      status_info::general,
      string(CDR_WITH_INCORRECT_ARG_TYPE),
      args_1
    );
    // valid format, extract remaining node that exclude first node
    node_t* const head = fetch<node_t*>(args_1);
    retval = make_shared<Container>();
    retval->type = containType::Node;
    // might be nil node but represented as nullptr
    if (head->right) {
      retval->value = head->right;
    } else {
      retval->value = new node_t(
        nodeType::Atom,
        new token_t {
          .family = tokenType::Nil,
          .text = "nil"
        }
      );
    }

    // unbind, prevent to be deleted recursively
    head->right = nullptr;
    delete head;

    return purify(retval);
  }

  // Reserved function - `car`
  ContainerPtr car(STANDARD_PARAMETERS) {
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "car");

    // try to get resolve the 1st argument
    ContainerPtr retval = nullptr;
    ContainerPtr args_1 = nullptr;
    UnboundParameter(args_1 = run(root->right->left, level));
    RUNTIME_EXTEND(
      (
        args_1->type == containType::Node &&
        isridge(cast<node_t*>(args_1))
      ),
      status_info::general,
      string(CAR_WITH_INCORRECT_ARG_TYPE),
      args_1
    );
    // valid format, extract first node
    node_t* const head = fetch<node_t*>(args_1);
    retval = make_shared<Container>();
    retval->type = containType::Node;
    retval->value = head->left;

    // unbind, prevent to be deleted recursively
    head->left = nullptr;
    delete head;

    return purify(retval);
  }

  // Reserved function - `list`
  ContainerPtr list(STANDARD_PARAMETERS) {
    ContainerPtr retval = make_shared<Container>();
    node_t* couple = new node_t(nodeType::Expr);
    retval->type = containType::Node;
    retval->value = couple;
    const node_t* node = root->right;
    while (isridge(node)) {
      ContainerPtr args = nullptr;
      UnboundParameter(args = run(node->left, level));
      if (args->type == containType::Node) {
        couple->left = fetch<node_t*>(args);
      } else {
        couple->left = backtrack(args);
      }
      couple->right = new node_t(nodeType::Expr);
      couple = couple->right;
      node = node->right;
    }
    couple->type = nodeType::Atom;
    couple->body = new token_t{
      .family = tokenType::Nil,
      .text = "nil"
    };
    return retval;
  }

  // Reserved function - `clean-environment`
  ContainerPtr clean(STANDARD_PARAMETERS) {
    RUNTIME((level == 1), LEVEL_CLEAN_ENVIRONMENT_CALLED);
    RUNTIME(exact(root, 0), INCORRECT_NUMBER_OF_ARGS + "clean-environment");
    global.clear();
    if (verbose_mode) cout << "environment cleaned" << endl;
    return nullptr;
  }

  // Reserved function - `define`
  ContainerPtr define(STANDARD_PARAMETERS) {
    // check if is top-level function call
    RUNTIME((level == 1), LEVEL_DEFINE_CALLED);

    enum class Format {
      undefined,
      Symbol,
      Lambda
    };

    Format format = Format::undefined;
    
    string args_1;
    ContainerPtr args_2 = nullptr;
    
    try {
      // check if the argument is at least two
      RUNTIME(atleast(root, 2), ILLEGAL_DEFINE_FORMAT);
      // check if the 1st argument is symbol or function declaration
      const node_t* node = root->right;
      if (issymbol(node->left)) /* (define num 123) */ {
        
        // symbol declaration must having two arguments exactly
        RUNTIME(exact(root, 2), ILLEGAL_DEFINE_FORMAT);
        args_1 = node->left->body->text;
        // check alias is not reserved words
        RUNTIME(reserved.find(args_1) == reserved.end(), ILLEGAL_DEFINE_FORMAT);
        format = Format::Symbol;

      } else if (isridge(node->left)) /* (define (func x y) (+ x y)) */ {
        
        // check function alias is symbol
        RUNTIME(issymbol(node->left->left), ILLEGAL_DEFINE_FORMAT);
        args_1 = node->left->left->body->text;
        // check function alias is not reserved words
        RUNTIME(reserved.find(args_1) == reserved.end(), ILLEGAL_DEFINE_FORMAT);
        format = Format::Lambda;
      
      } else RUNTIME(false, ILLEGAL_DEFINE_FORMAT);

    } catch (status_t& err) {
      // attach the struct of define call for error display
      err.attachment = make_shared<Container>(root);
      throw;
    }
    // valid format, resolve remaining arguments
    switch (format) {
      case Format::Symbol: {
        args_2 = run(root->right->right->left, level);
        global[args_1] = args_2;
        break;
      }
      case Format::Lambda: {
        const node_t* const pseudo_root = new node_t(
          nodeType::Expr,
          nullptr,
          new node_t(
            nodeType::Atom,
            new token_t{
              .family = tokenType::Symbol,
              .text = args_1
            }
          ),
          new node_t(
            nodeType::Expr,
            nullptr,
            root->right->left->right,
            root->right->right
          )
        );
        try {
          const string error_msg = ILLEGAL_DEFINE_FORMAT;
          args_2 = lambda(pseudo_root, level+1, &error_msg);
          global[args_1] = args_2;
        } catch (status_t& err) {
          pseudo_root->right->left = nullptr;
          pseudo_root->right->right = nullptr;
          delete pseudo_root;
          throw;
        }
        pseudo_root->right->left = nullptr;
        pseudo_root->right->right = nullptr;
        delete pseudo_root;
        break;
      }
      default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
    }

    if (verbose_mode) cout << args_1 << " defined" << endl;
    return nullptr;
  }

  // Reserved function - `quote`
  ContainerPtr quote(STANDARD_PARAMETERS) {
    // check if the argument is exactly one
    RUNTIME(exact(root, 1), INCORRECT_NUMBER_OF_ARGS + "quote");
    // process below can be considered to be move to Container's constructor
    /* moved */
    return make_shared<Container>(root->right->left);
  }

  // Reserved function - `cons`
  ContainerPtr cons(STANDARD_PARAMETERS) {
    // check if the argument is exactly two
    RUNTIME(exact(root, 2), INCORRECT_NUMBER_OF_ARGS + "cons");
    ContainerPtr args_1 = nullptr;
    ContainerPtr args_2 = nullptr;
    ContainerPtr retval = nullptr;
    {
      // move forward
      const node_t* node = root->right;
      // execute the 1st argument
      UnboundParameter(args_1 = run(node->left, level));
      // move forward
      node = node->right;
      // execute the 2nd argument
      UnboundParameter(args_2 = run(node->left, level));
    }
    // valid format, starting construct
    node_t* head = nullptr;
    // examine the 1st argument type
    if (args_1->type == containType::Node) {
      // create a new root for args_1's tree and args_2's tree
      head = new node_t(
        nodeType::Expr,
        nullptr,
        fetch<node_t*>(args_1),
        nullptr
      );
      // examine the 2nd argument type
      if (args_2->type == containType::Node) {
        // if the 2nd argument is also node type, connect them directly
        head->right = fetch<node_t*>(args_2);
      } else {
        // non-node data, must revert it back to node_t
        head->right = backtrack(args_2);
      }
      // prevent unnecessary tree copy (move<node_t*> already handled that)
      // declare void container instead of passing node_t into constructor
      
    } else {
      // the 1st argument is non-node type, must revert it back to node_t
      head = new node_t(
        nodeType::Expr,
        nullptr,
        backtrack(args_1),
        nullptr
      );
      if (args_2->type == containType::Node) {
        // the 2nd argument is node type, connect them directly
        head->right = fetch<node_t*>(args_2);
      } else {
        // the 2nd argument is non-node type, so...
        head->right = backtrack(args_2);
      }
    }
    retval = make_shared<Container>();
    retval->type = containType::Node;
    retval->value = head;
    return retval;
  }

  // Reserved function - `exit`
  ContainerPtr exit(STANDARD_PARAMETERS) const {
    // check if is top-level function call
    RUNTIME((level == 1), LEVEL_EXIT_CALLED);
    // check if is no trailing arguments
    RUNTIME(exact(root, 0), INCORRECT_NUMBER_OF_ARGS + "exit");
    throw status_t{status_code::Exit};
    return nullptr; // unreachable, just for unify specifications
  }

  inline ContainerPtr* mapping(const string& __key) const noexcept {
    {
      auto pair = reserved.find(__key);
      if (pair != reserved.end()) {
        return const_cast<ContainerPtr*>(&pair->second);
      }
    }
    {
      const Page& page = stack.back();  // only search in current page
      for (auto it = page.rbegin(); it != page.rend(); it++) {
        const Segment& segment = *it;
        auto pair = segment.find(__key);
        if (pair != segment.end()) {
          return const_cast<ContainerPtr*>(&pair->second);
        }
      }
    }
    {
      auto pair = global.find(__key);
      if (pair != global.end()) {
        return const_cast<ContainerPtr*>(&pair->second);
      }
    }
    return nullptr;
  }

  inline const string* mapping(const ContainerPtr& __val) const noexcept {
    for (auto it = reserved.begin(); it != reserved.end(); it++) {
      if (it->second == __val) {
        return &(it->first);
      }
    }
    {
      const Page& page = stack.back();
      for (auto it = page.rbegin(); it != page.rend(); it++) {
        const Segment& segment = *it;
        for (auto it = segment.begin(); it != segment.end(); it++) {
          if (it->second == __val) {
            return &(it->first);
          }
        }
      }
    }
    for (auto it = global.begin(); it != global.end(); it++) {
      if (it->second == __val) {
        return &(it->first);
      }
    }
    return nullptr;
  }

  // Convert `Container` back to `node_t`
  inline node_t* backtrack(const ContainerPtr& __obj) noexcept {
    node_t* node = nullptr;
    
    switch (__obj->type) {
      case containType::Boolean: {
        node = new node_t(nodeType::Atom);
        if (*cast<bool*>(__obj)) {
          node->body = new token_t{
            .family = tokenType::T,
            .text = "#t"
          };
        } else {
          node->body = new token_t{
            .family = tokenType::Nil,
            .text = "nil"
          };
        }
        break;
      }
      case containType::Float: {
        node = new node_t(
          nodeType::Atom,
          new token_t{
            .family = tokenType::Float,
            .text = to_string(*cast<double*>(__obj))
          }
        );
        break;
      }
      case containType::Int: {
        node = new node_t(
          nodeType::Atom,
          new token_t{
            .family = tokenType::Int,
            .text = to_string(*cast<int*>(__obj))
          }
        );
        break;
      }
      case containType::Error:
      case containType::String: {
        node = new node_t(
          nodeType::Atom,
          new token_t{
            .family = tokenType::String,
            .text = *cast<string*>(__obj)
          }
        );
        break;
      }
      case containType::Node: {
        node = cast<node_t*>(__obj)->copy();
        break;
      }
      case containType::Lambda:
      case containType::Function: {
        node = new node_ext(
          nodeType::Atom,
          new token_t {
            .family = tokenType::Symbol,
            .text = string("#<procedure ") + __obj->name + ">"
          },
          nullptr, nullptr, __obj
        );
        break;
      }
      default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
    }
    return node;
  }

  // Decay the node type container which holds an atom node to the base type
  inline ContainerPtr purify(ContainerPtr& __var) noexcept {
    ContainerPtr retval = make_shared<Container>();
    if (__var->type == containType::Node) {
      const node_t* const& root = cast<node_t*>(__var);
      if (root->type == nodeType::Atom) {
        switch (root->body->family) {
          case tokenType::Int: {
            retval->type = containType::Int;
            retval->value = new int(stoi(root->body->text));
            break;
          }
          case tokenType::Float: {
            retval->type = containType::Float;
            retval->value = new double(stod(root->body->text));
            break;
          }
          case tokenType::T: {
            retval->type = containType::Boolean;
            retval->value = new bool(true);
            break;
          }
          case tokenType::Nil: {
            retval->type = containType::Boolean;
            retval->value = new bool(false);
            break;
          }
          case tokenType::String: {
            retval->type = containType::String;
            retval->value = new string(root->body->text);
            break;
          }
          case tokenType::Quote:
          case tokenType::Symbol: {
            
            // (car (cons define define)) -> define (I'm function)
            // (car '(define . define)) -> define (I'm unprocessed symbol)
            if (const node_ext* node = dynamic_cast<const node_ext*>(root)) {
              retval = node->prototype;
            } else {
              retval->type = containType::Node;
              retval->value = fetch<node_t*>(__var);
            }

            break;
          }
          default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
        }
      } else {
        retval->type = containType::Node;
        retval->value = fetch<node_t*>(__var);
      }
      return retval;
    }
    return __var;
  }

  // Resolving procedure of `lambda`, partial of `Executor::run()`
  ContainerPtr run_lambda(LAMBDA_PARAMETERS) {
    /**
     * @note
     * Lambda DOES NOT search for symbols on current stack during execution,
     * so I use page-segment structure on `stack`.
     * `run_lambda()` will create a new page, `let()` only create new segment,
     * single page is able to contain several segment,
     * and `mapping()` is limited to not searching over pages. That's all.
     * @example
     * > (let ((a 1) (b 2) (c 3)) ((lambda () (+ a b c))))
     * ERROR (unbound symbol) : a
     */
    node_t* const pseudo_root = new node_t(
      nodeType::Expr,
      nullptr,
      const_cast<node_t*>(cast<const node_t*>(__var)),
      const_cast<node_t*>(args)
    );

    ContainerPtr retval = nullptr;

    try {
      {
        size_t param_count = 0;
        const node_t* param = pseudo_root->left->left;
        while (isridge(param)) {
          param_count++;
          param = param->right;
        }
        RUNTIME(
          exact(pseudo_root, param_count),
          INCORRECT_NUMBER_OF_ARGS + __var->name
        );
      }
      /**
       * @warning
       * Move page into stack after register process was done,
       * prevent duplicate variable name conflict cause `mapping()`
       * use the forward registered parameter as expected value.
       * @example
       * > (define x 1)
       * x defined
       * > (define (sum (x y z) (+ x y z)) 8 7 x)
       *                                       ^
       *                        expected 1, but 8 was fetched,
       *                   cause x = 8, y = 7 was already registered.
       */
      Page page = Page(1);  // create a new empty page
      Segment& segment = page.back();
      
      // register parameters
      {
        const node_t* param = pseudo_root->left->left;
        while (isridge(param)) {
          UnboundParameter(segment[param->left->body->text] = run(args->left, level));
          param = param->right;
          args = args->right;
        }
      }
      // page was push to stack if and only if parameters' registration was done
      stack.push_back(move(page));
      try {
        
        // execute all expression
        const node_t* expr = pseudo_root->left->right;
        while (isridge(expr)) {
          retval = nullptr;
          IgnoreNoReturnValue(retval = run(expr->left, level));
          expr = expr->right;
        }

      } catch (const status_t& err) {
        stack.pop_back(); // page destruction (fuse)
        throw;
      }
      stack.pop_back(); // page destruction

    } catch (const status_t& err) {
      // unbind, prevent chaining deletion by `node_t` destructor (fuse)
      pseudo_root->left = pseudo_root->right = nullptr;
      delete pseudo_root;
      throw;
    }
    // unbind, prevent chaining deletion by `node_t` destructor
    pseudo_root->left = pseudo_root->right = nullptr;
    delete pseudo_root;

    RUNTIME_EXTEND(
      retval,
      status_info::NoReturnValue,
      NO_RETURN_VALUE,
      nullptr
    );
    
    return retval;
  }

  // Recursive analyzer
  ContainerPtr run(STANDARD_PARAMETERS) {
    ContainerPtr retval = nullptr;
    
    switch (root->type) {
      case nodeType::Atom: {
        /**
         * Only the rest of list items or single element
         * would be able to enter this part.
         * @example
         * 1. (define add +) - only `add` and `+`
         * 2. owo - `owo` itself
         */
        switch (root->body->family) {
          case tokenType::Int: {
            retval = make_shared<Container>(stoi(root->body->text));
            break;
          }
          case tokenType::Float: {
            retval = make_shared<Container>(stod(root->body->text));
            break;
          }
          case tokenType::T: {
            retval = make_shared<Container>(true);
            break;
          }
          case tokenType::Nil: {
            retval = make_shared<Container>(false);
            break;
          }
          case tokenType::String: {
            retval = make_shared<Container>(root->body->text);
            break;
          }
          case tokenType::Quote:
          case tokenType::Symbol: {
            const string& raw_text = root->body->text;
            if (const node_ext* node = dynamic_cast<const node_ext*>(root)) {
              retval = node->prototype;
            } else {
              ContainerPtr* matched = mapping(root->body->text);
              retval = matched ? *matched : nullptr;
            }
            RUNTIME((retval), string(UNBOUND_SYMBOL) + raw_text);
            break;
          }
          default: AssertionError::throws(UNEXPECTED_BEHAVIOR);
        }

        break;
      }
      case nodeType::Expr: {

        // check if is not list declaration at first
        RUNTIME_EXTEND(
          islist(root),
          status_info::general,
          NON_LIST,
          make_shared<Container>(root)
        );
        
        {
          ContainerPtr getval = nullptr;
          Important(getval = run(root->left, level+1));

          // check if is attempt to apply non-function or non-lambda
          switch (getval->type) {
            case containType::Function: {
              retval = (*cast<func_t*>(getval))(root, level+1, nullptr);
              break;
            }
            case containType::Lambda: {
              NoReturnValue(retval = run_lambda(getval, root->right, level+1));
              break;
            }
            default: RUNTIME_EXTEND(
              false,
              status_info::general,
              APPLY_NON_FUNCTION,
              getval
            );
          }

        }

        break;
      }
    }
    return retval;
  }

  // Check if is ridge of the tree
  static inline bool isridge(const node_t* const &node) noexcept {
    return node && node->type == nodeType::Expr;
  }

  // Check if is terminate node
  static inline bool isnil(const node_t* const &node) noexcept {
    return (!node || (
      node->type == nodeType::Atom &&
      node->body->family == tokenType::Nil
    ));
  }

  // Check if is symbol node
  static inline bool issymbol(const node_t* const &node) noexcept {
    return (
      node &&
      node->type == nodeType::Atom &&
      node->body->family == tokenType::Symbol
    );
  }

  // Check if is list structure (nil terminate)
  static inline bool islist(const node_t* const &root) noexcept {
    const node_t* node = root;
    while (isridge(node)) node = node->right;
    return isnil(node);
  }

  // Check if is the arguments amount exactly as same as specific number
  static inline bool exact(const node_t* const &root, const int& __n) noexcept {
    const node_t* node = root->right;
    int count = 0;
    for (; count < __n && isridge(node); count++) node = node->right;
    return isnil(node) && count == __n;
  }

  // Check if is the arguments amount is greater equal than specific number
  static inline bool atleast(const node_t* const &root, const int& __n) noexcept {
    const node_t* node = root->right;
    int count = 0;
    for (; count < __n && isridge(node); count++) node = node->right;
    return count == __n;
  }

  // Check if the ContainerPtr is number type
  static inline bool isnumber(const ContainerPtr& __var) noexcept {
    return __var->type == containType::Int || __var->type == containType::Float;
  }

  // Short form of `static_cast<T>(__var->value)`
  template <typename T>
  static inline T cast(const ContainerPtr& __var) noexcept {
    return static_cast<T>(__var->value);
  }

  template <typename T,
  typename enable_if<!(IS_NODE || IS_CONST_NODE || IS_FUNCTION)>::type* = nullptr>
  static inline T fetch(ContainerPtr& __var)
#ifndef DEBUG
  noexcept
#endif
  {
    auto use_count = __var.use_count();
#ifdef DEBUG
    ASSERT(use_count, UNEXPECTED_BEHAVIOR);
#endif
    T temp = nullptr;
    if (use_count == 1) {
      temp = static_cast<T>(__var->value);
      __var->value = nullptr;
      __var = nullptr;
    } else {
      temp = new remove_pointer_t<T>(*static_cast<T>(__var->value));
    }
    return temp;
  }
  
  template <typename T,
  typename enable_if<(IS_NODE || IS_CONST_NODE)>::type* = nullptr>
  static inline T fetch(ContainerPtr& __var)
#ifndef DEBUG
  noexcept
#endif
  {
    auto use_count = __var.use_count();
#ifdef DEBUG
    ASSERT(use_count, UNEXPECTED_BEHAVIOR);
#endif
    T temp = nullptr;
    if (use_count == 1) {
      temp = static_cast<node_t*>(__var->value);
      __var->value = nullptr;
      __var = nullptr;
    } else {
      temp = static_cast<node_t*>(__var->value)->copy();
    }
    return temp;
  }

 public:
  Executor(Scanner& scanner, Parser& parser) : scanner(scanner), parser(parser) {}

  void build(const node_t* const &root) {
    ContainerPtr container = run(root, 0);
    if (container.use_count()) {
      ASSERT((container->type != containType::Void), UNEXPECTED_BEHAVIOR);
      cout << stringify(container) << endl;
    }
    return;
  }

  string stringify(const ContainerPtr&__obj) const {
    string buf;
    switch (__obj->type) {
      case containType::Boolean: {
        buf = *static_cast<bool*>(__obj->value) ? "#t" : "nil";
        break;
      }
      case containType::Float: {
        char _buf[32];
        snprintf(_buf, sizeof(_buf), "%.3f", *static_cast<double*>(__obj->value));
        buf = _buf;
        break;
      }
      case containType::Int: {
        buf = to_string(*static_cast<int*>(__obj->value));
        break;
      }
      case containType::Error:
      case containType::String: {
        buf = *static_cast<string*>(__obj->value);
        break;
      }
      case containType::Node: {
        buf = stringify(static_cast<node_t*>(__obj->value));
        break;
      }
      case containType::Lambda:
      case containType::Function: {
        ((buf += "#<procedure ") += __obj->name) += ">";
        break;
      }
      default: break;
    }
    return buf;
  }

  string stringify(const node_t* const &root) const {
    struct wrap_t {
      const node_t* node;
      int level;
      int credit = 3;
      wrap_t(const node_t* __n, const int& __lvl) : node(__n), level(__lvl) {}
    };

    auto indent = [](const int& __n) -> int {
      return ((__n) > 0) ? (__n << 1) : 0;
    };

    string buf;

    int level = -1;
    int level_h = -1;
    deque<wrap_t> queue;
    queue.emplace_back(root, 0);
    while (!queue.empty()) {
      wrap_t& curr = queue.back();

      if (curr.node->type == nodeType::Expr) {
        if (level < curr.level) {
          if (level_h == level) {
            buf += string(indent(curr.level), ' ');
          }
          buf += "( ";
        } else if (level > curr.level) {
          buf += string(indent(curr.level+1), ' ') + ")\n";
        }
        level_h = level;
        level = curr.level;
      }

      switch (curr.credit) {
        case 3: {
          curr.credit--;
          if (curr.node->type == nodeType::Atom) {
            if (level_h == level) {
              buf += string(indent(level+1), ' ');
            }
            buf += curr.node->body->stringify() + '\n';
          }
        }
        case 2: {
          curr.credit--;
          if (curr.node->left) {
            queue.emplace_back(curr.node->left, curr.level+1);
            continue;
          }
        }
        case 1: {
          curr.credit--;
          if (curr.node->right) {
            if (curr.node->right->type == nodeType::Atom) {
              if (curr.node->right->body->family != tokenType::Nil) {
                const string _indent = string(indent(level+1), ' ');
                buf += _indent + ".\n"
                     + _indent + curr.node->right->body->stringify() + '\n';
              }
            } else {
              queue.emplace_back(curr.node->right, curr.level);
            }
            continue;
          }
        }
        default: {
          queue.pop_back();
        }
      }
    }

    if (root) switch (root->type) {
      case nodeType::Expr: {
        buf += ")";
        break;
      }
      case nodeType::Atom: {
        if (buf.back() == '\n') buf.pop_back();
        break;
      }
    }
    
    return buf;
  }

};

class EventHandler {
 private:
  static EventHandler self;

  EventHandler() = default;

 public:
  EventHandler(const EventHandler& __obj) = delete;

  EventHandler& operator=(const EventHandler& __obj) = delete;

  static EventHandler& instance() {
    return self;
  }

  /* ---------------------------------------------------------------- */
 private:
  Scanner scanner = Scanner();
  Parser parser = Parser(scanner);
  Executor executor = Executor(scanner, parser);

 public:
  EventHandler& execute() {
    cout << "Welcome to OurScheme!" << endl;
    {
      int bin;
      cin >> bin;
      cin.ignore(INT_MAX, '\n');
      cin.clear();
    }
    
    bool halt = false;
    node_t* root = nullptr;
    while (!halt) try {

      cout << "\n> ";

      root = parser.build();

      executor.build(root);

      delete root;
      // necessary, explaination at the bottom of catch statement
      root = nullptr;

    } catch (const status_t& err) {
      
      switch (err.code) {
        case status_code::Exit: {
          cout << endl;
          halt = true;
          break;
        }
        case status_code::EndOfFileEncountered: {
          cout << err.body << endl;
          halt = true;
          break;
        }
        case status_code::NoClosingQuote: {
          cout << err.body << endl;
          break;
        }
        case status_code::UnexpectedToken: {
          cout << err.body << endl;
          scanner.discard();
          break;
        }
        case status_code::RuntimeError: {
          if (err.attachment) {
            cout << err.body << executor.stringify(err.attachment) << endl;
          } else {
            cout << err.body << endl;
          }
          break;
        }
      }

      delete root;
      // prevent next loop doing illegal memory release
      // occurs when `status_t` throw in parse.build()
      // cause `root` didn't be updated
      root = nullptr;
    }

    cout << "Thanks for using OurScheme!";
    return self;
  }

};

EventHandler EventHandler::self;

int main() {
#ifdef TEST
  ifstream input = ifstream("project/input.txt");
  if (input.is_open()) {
    cin.rdbuf(input.rdbuf());
  }

  ofstream output = ofstream("project/output.txt");
  if (output.is_open()) {
    cout.rdbuf(output.rdbuf());
  }
#endif

#ifndef BLOCK
  EventHandler::instance().execute();  
#endif

#ifdef TEST
  input.close();
  output.close();
#endif

  return 0;
}