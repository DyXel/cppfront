
#ifndef CPP2REFLECT_H_CPP2
#define CPP2REFLECT_H_CPP2

#define CPP2_IMPORT_STD          Yes

//=== Cpp2 type declarations ====================================================


#include "cpp2util.h"

#line 1 "reflect.h2"

#line 19 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 27 "reflect.h2"
class source_position;

#line 44 "reflect.h2"
class passing_style;

#line 76 "reflect.h2"
class compiler_services;

#line 261 "reflect.h2"
class declaration_base;

#line 303 "reflect.h2"
class declaration;

#line 388 "reflect.h2"
class function_declaration;

#line 475 "reflect.h2"
class object_declaration;

#line 511 "reflect.h2"
class type_declaration;

#line 646 "reflect.h2"
class alias_declaration;

#line 985 "reflect.h2"
class value_member_info;

#line 1409 "reflect.h2"
}

}


//=== Cpp2 type definitions and function declarations ===========================

#line 1 "reflect.h2"

//  Copyright (c) Herb Sutter
//  SPDX-License-Identifier: CC-BY-NC-ND-4.0

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#line 14 "reflect.h2"
//===========================================================================
//  Reflection and meta
//===========================================================================

#line 19 "reflect.h2"
namespace cpp2 {

namespace meta {

#line 24 "reflect.h2"
using lineno_t = std::int32_t;
using colno_t = std::int32_t;    // not int16_t... encountered >80,000 char line during testing

class source_position
 {
    public: lineno_t lineno {1};   // one-based offset into program source
    public: colno_t colno {1};     // one-based offset into line

    public: source_position();
    public: source_position(cpp2::in<lineno_t> l);
#line 33 "reflect.h2"
    public: auto operator=(cpp2::in<lineno_t> l) -> source_position& ;
    public: source_position(cpp2::in<lineno_t> l, cpp2::in<colno_t> c);

#line 40 "reflect.h2"
    public: [[nodiscard]] auto to_string() const& -> std::string;
    public: [[nodiscard]] auto operator<=>(source_position const& that) const& -> std::strong_ordering = default;
public: source_position(source_position const& that);

public: auto operator=(source_position const& that) -> source_position& ;
public: source_position(source_position&& that) noexcept;
public: auto operator=(source_position&& that) noexcept -> source_position& ;

#line 41 "reflect.h2"
};

#line 44 "reflect.h2"
class passing_style
 {
private: cpp2::i8 _value; private: constexpr passing_style(cpp2::in<cpp2::i64> _val);

private: constexpr auto operator=(cpp2::in<cpp2::i64> _val) -> passing_style& ;
public: static const passing_style in;
public: static const passing_style copy;
public: static const passing_style inout;
public: static const passing_style out;
public: static const passing_style move;
public: static const passing_style forward;
public: static const passing_style invalid;
public: [[nodiscard]] constexpr auto get_raw_value() const& -> cpp2::i8;
public: constexpr explicit passing_style();
public: constexpr passing_style(passing_style const& that);
public: constexpr auto operator=(passing_style const& that) -> passing_style& ;
public: constexpr passing_style(passing_style&& that) noexcept;
public: constexpr auto operator=(passing_style&& that) noexcept -> passing_style& ;
public: [[nodiscard]] auto operator<=>(passing_style const& that) const& -> std::strong_ordering = default;
public: [[nodiscard]] auto to_string() const& -> std::string;

#line 53 "reflect.h2"
};

//  Not `passing_style::from_string` to workaround #555.
[[nodiscard]] auto to_passing_style(cpp2::in<std::string_view> s) -> passing_style;

#line 69 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Compiler services
//
//-----------------------------------------------------------------------
//

class compiler_services
 {
    //  Common data members
    //
    private: std::any data_; 
    private: [[nodiscard]] auto data() const& -> auto&&;
    private: [[nodiscard]] auto data() & -> auto&&;

    //  Constructor
    //
    public: explicit compiler_services(

        cpp2::in<std::any> data_v
    );

#line 95 "reflect.h2"
    //  Common API
    //
    public: auto set_metafunction_name(cpp2::in<std::string_view> name, cpp2::in<std::vector<std::string>> args) & -> void;

#line 103 "reflect.h2"
    public: [[nodiscard]] auto get_metafunction_name() const& -> std::string_view;

    public: [[nodiscard]] auto get_argument(cpp2::in<int> index) & -> std::string;

#line 113 "reflect.h2"
    public: [[nodiscard]] auto get_arguments() & -> std::vector<std::string>;

#line 118 "reflect.h2"
    public: [[nodiscard]] auto arguments_were_used() const& -> bool;

    protected: [[nodiscard]] auto parse_statement(

        std::string_view source
    ) & -> auto;

#line 174 "reflect.h2"
    public: [[nodiscard]] virtual auto position() const -> source_position;

#line 180 "reflect.h2"
    //  Error diagnosis and handling, integrated with compiler output
    //  Unlike a contract violation, .requires continues further processing
    //
    public: auto require(

        cpp2::in<bool> b, 
        cpp2::in<std::string_view> msg
    ) const& -> void;

#line 194 "reflect.h2"
    public: auto error(cpp2::in<std::string_view> msg) const& -> void;

#line 203 "reflect.h2"
    //  Enable custom contracts on this object, integrated with compiler output
    //  Unlike .requires, a contract violation stops further processing
    //
    public: auto report_violation(auto const& msg) const& -> void;

#line 211 "reflect.h2"
    public: [[nodiscard]] auto has_handler() const& -> auto;
    public: virtual ~compiler_services() noexcept;
public: compiler_services(compiler_services const& that);

#line 212 "reflect.h2"
};

#line 215 "reflect.h2"
/*
//-----------------------------------------------------------------------
//
//  Type IDs
//
//-----------------------------------------------------------------------
//

//  All type_ids are wrappers around a pointer to node
//
type_id: @polymorphic_base @copyable type =
{
    this: compiler_services = ();

    n: type_id_node;

    protected operator=: (
        out this,
        n_: type_id_node,
        s : compiler_services
    )
    = {
        compiler_services = s;
        n = n_;
        assert( n, "a meta::type_id must point to a valid type_id_node, not null" );
    }

    is_wildcard         : (this) -> bool        = n.is_wildcard();
    is_pointer_qualified: (this) -> bool        = n.is_pointer_qualified();
    template_args_count : (this) -> int         = n.template_arguments().ssize();
    to_string           : (this) -> std::string = n.to_string();

    position: (override this) -> source_position = n.position();
}
*/

#line 252 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Declarations
//
//-----------------------------------------------------------------------
//

//  All declarations are wrappers around a pointer to node
//
class declaration_base
: public compiler_services {

#line 265 "reflect.h2"
    public: class node_pointer
     {
        private: void* n; 

        public: template<typename T> node_pointer(

            T const& n_
        );
#line 269 "reflect.h2"
        public: template<typename T> auto operator=(

            T const& n_
        ) -> node_pointer& ;

#line 279 "reflect.h2"
        public: [[nodiscard]] auto operator*() const& -> auto&&;
        public: node_pointer(node_pointer const& that);

public: auto operator=(node_pointer const& that) -> node_pointer& ;
public: node_pointer(node_pointer&& that) noexcept;
public: auto operator=(node_pointer&& that) noexcept -> node_pointer& ;

#line 280 "reflect.h2"
    };

    protected: node_pointer n; 

    protected: explicit declaration_base(

        cpp2::in<node_pointer> n_, 
        cpp2::in<compiler_services> s
    );

#line 294 "reflect.h2"
    public: [[nodiscard]] auto position() const -> source_position override;

    public: [[nodiscard]] auto print() const& -> std::string;
    public: virtual ~declaration_base() noexcept;
public: declaration_base(declaration_base const& that);

#line 297 "reflect.h2"
};

#line 300 "reflect.h2"
//-----------------------------------------------------------------------
//  All declarations
//
class declaration
: public declaration_base {

#line 307 "reflect.h2"
    public: explicit declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    );

#line 316 "reflect.h2"
    public: [[nodiscard]] auto is_public() const& -> bool;
    public: [[nodiscard]] auto is_protected() const& -> bool;
    public: [[nodiscard]] auto is_private() const& -> bool;
    public: [[nodiscard]] auto is_default_access() const& -> bool;

    public: auto default_to_public() & -> void;
    public: auto default_to_protected() & -> void;
    public: auto default_to_private() & -> void;

    public: [[nodiscard]] auto make_public() & -> bool;
    public: [[nodiscard]] auto make_protected() & -> bool;
    public: [[nodiscard]] auto make_private() & -> bool;

    public: [[nodiscard]] auto is_visible() const& -> bool;
    public: [[nodiscard]] auto make_visible() & -> bool;

    public: [[nodiscard]] auto has_name() const& -> bool;
    public: [[nodiscard]] auto has_name(cpp2::in<std::string_view> s) const& -> bool;

    public: [[nodiscard]] auto name() const& -> std::string_view;

#line 340 "reflect.h2"
    public: [[nodiscard]] auto has_initializer() const& -> bool;

    public: [[nodiscard]] auto is_global() const& -> bool;
    public: [[nodiscard]] auto is_function() const& -> bool;
    public: [[nodiscard]] auto is_object() const& -> bool;
    public: [[nodiscard]] auto is_base_object() const& -> bool;
    public: [[nodiscard]] auto is_member_object() const& -> bool;
    public: [[nodiscard]] auto is_type() const& -> bool;
    public: [[nodiscard]] auto is_namespace() const& -> bool;
    public: [[nodiscard]] auto is_alias() const& -> bool;

    public: [[nodiscard]] auto is_type_alias() const& -> bool;
    public: [[nodiscard]] auto is_namespace_alias() const& -> bool;
    public: [[nodiscard]] auto is_object_alias() const& -> bool;

    public: [[nodiscard]] auto is_function_expression() const& -> bool;

    public: [[nodiscard]] auto as_function() const& -> function_declaration;
    public: [[nodiscard]] auto as_object() const& -> object_declaration;
    public: [[nodiscard]] auto as_type() const& -> type_declaration;
    public: [[nodiscard]] auto as_alias() const& -> alias_declaration;

    public: [[nodiscard]] auto get_parent() const& -> declaration;

    public: [[nodiscard]] auto parent_is_function() const& -> bool;
    public: [[nodiscard]] auto parent_is_object() const& -> bool;
    public: [[nodiscard]] auto parent_is_type() const& -> bool;
    public: [[nodiscard]] auto parent_is_namespace() const& -> bool;
    public: [[nodiscard]] auto parent_is_alias() const& -> bool;

    public: [[nodiscard]] auto parent_is_type_alias() const& -> bool;
    public: [[nodiscard]] auto parent_is_namespace_alias() const& -> bool;
    public: [[nodiscard]] auto parent_is_object_alias() const& -> bool;

    public: [[nodiscard]] auto parent_is_polymorphic() const& -> bool;

    public: auto mark_for_removal_from_enclosing_type() & -> void;
    public: virtual ~declaration() noexcept;
public: declaration(declaration const& that);

                                                    // this precondition should be sufficient ...

#line 382 "reflect.h2"
};

#line 385 "reflect.h2"
//-----------------------------------------------------------------------
//  Function declarations
//
class function_declaration
: public declaration {

#line 392 "reflect.h2"
    public: explicit function_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    );

#line 402 "reflect.h2"
    public: [[nodiscard]] auto index_of_parameter_named(cpp2::in<std::string_view> s) const& -> int;
    public: [[nodiscard]] auto has_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_in_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_out_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto has_move_parameter_named(cpp2::in<std::string_view> s) const& -> bool;
    public: [[nodiscard]] auto first_parameter_name() const& -> std::string;

    public: [[nodiscard]] auto has_parameter_with_name_and_pass(cpp2::in<std::string_view> s, cpp2::in<passing_style> pass) const& -> bool;

    public: [[nodiscard]] auto is_function_with_this() const& -> bool;
    public: [[nodiscard]] auto is_virtual() const& -> bool;
    public: [[nodiscard]] auto is_defaultable() const& -> bool;
    public: [[nodiscard]] auto is_constructor() const& -> bool;
    public: [[nodiscard]] auto is_default_constructor() const& -> bool;
    public: [[nodiscard]] auto is_move() const& -> bool;
    public: [[nodiscard]] auto is_swap() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_constructor_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_in_that() const& -> bool;
    public: [[nodiscard]] auto is_assignment_with_move_that() const& -> bool;
    public: [[nodiscard]] auto is_destructor() const& -> bool;

    public: [[nodiscard]] auto is_copy_or_move() const& -> bool;

    public: [[nodiscard]] auto has_declared_return_type() const& -> bool;
    public: [[nodiscard]] auto has_deduced_return_type() const& -> bool;
    public: [[nodiscard]] auto has_bool_return_type() const& -> bool;
    public: [[nodiscard]] auto has_non_void_return_type() const& -> bool;

    public: [[nodiscard]] auto unnamed_return_type() const& -> std::string;

    public: [[nodiscard]] auto get_parameters() const& -> std::vector<object_declaration>;

#line 446 "reflect.h2"
    public: [[nodiscard]] auto is_binary_comparison_function() const& -> bool;

    public: auto default_to_virtual() & -> void;

    public: [[nodiscard]] auto make_virtual() & -> bool;

    public: auto add_initializer(cpp2::in<std::string_view> source) & -> void;
    public: function_declaration(function_declaration const& that);


#line 469 "reflect.h2"
};

#line 472 "reflect.h2"
//-----------------------------------------------------------------------
//  Object declarations
//
class object_declaration
: public declaration {

#line 479 "reflect.h2"
    public: explicit object_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    );

#line 489 "reflect.h2"
    public: [[nodiscard]] auto is_const() const& -> bool;
    public: [[nodiscard]] auto has_wildcard_type() const& -> bool;

    public: [[nodiscard]] auto type() const& -> std::string;

#line 499 "reflect.h2"
    public: [[nodiscard]] auto initializer() const& -> std::string;
    public: object_declaration(object_declaration const& that);


#line 505 "reflect.h2"
};

#line 508 "reflect.h2"
//-----------------------------------------------------------------------
//  Type declarations
//
class type_declaration
: public declaration {

#line 515 "reflect.h2"
    public: explicit type_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    );

#line 525 "reflect.h2"
    public: auto reserve_names(cpp2::in<std::string_view> name, auto&& ...etc) const& -> void;

#line 537 "reflect.h2"
    public: [[nodiscard]] auto is_polymorphic() const& -> bool;
    public: [[nodiscard]] auto is_final() const& -> bool;
    public: [[nodiscard]] auto make_final() & -> bool;

    public: [[nodiscard]] auto get_member_functions() const& -> std::vector<function_declaration>;

#line 552 "reflect.h2"
    public: [[nodiscard]] auto get_member_functions_needing_initializer() const& -> std::vector<function_declaration>;

#line 567 "reflect.h2"
    public: [[nodiscard]] auto get_member_objects() const& -> std::vector<object_declaration>;

#line 577 "reflect.h2"
    public: [[nodiscard]] auto get_member_types() const& -> std::vector<type_declaration>;

#line 587 "reflect.h2"
    public: [[nodiscard]] auto get_member_aliases() const& -> std::vector<alias_declaration>;

#line 597 "reflect.h2"
    public: [[nodiscard]] auto get_members() const& -> std::vector<declaration>;
struct query_declared_value_set_functions_ret { bool out_this_in_that; bool out_this_move_that; bool inout_this_in_that; bool inout_this_move_that; };



#line 607 "reflect.h2"
    public: [[nodiscard]] auto query_declared_value_set_functions() const& -> query_declared_value_set_functions_ret;

#line 622 "reflect.h2"
    public: auto add_member(cpp2::in<std::string_view> source) & -> void;

#line 636 "reflect.h2"
    public: auto remove_marked_members() & -> void;
    public: auto remove_all_members() & -> void;

    public: auto disable_member_function_generation() & -> void;
    public: type_declaration(type_declaration const& that);

#line 640 "reflect.h2"
};

#line 643 "reflect.h2"
//-----------------------------------------------------------------------
//  Alias declarations
//
class alias_declaration
: public declaration {

#line 650 "reflect.h2"
    public: explicit alias_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    );
    public: alias_declaration(alias_declaration const& that);


#line 659 "reflect.h2"
};

#line 662 "reflect.h2"
//-----------------------------------------------------------------------
//
//  Metafunctions - these are hardwired for now until we get to the
//  step of writing a Cpp2 interpreter to run inside the compiler
//
//-----------------------------------------------------------------------
//

//-----------------------------------------------------------------------
//  Some common metafunction helpers (metafunctions are just functions,
//  so they can be factored as usual)
//
auto add_virtual_destructor(meta::type_declaration& t) -> void;

#line 680 "reflect.h2"
//-----------------------------------------------------------------------
//
//      "... an abstract base class defines an interface ..."
//
//          -- Stroustrup (The Design and Evolution of C++, 12.3.1)
//
//-----------------------------------------------------------------------
//
//  interface
//
//  an abstract base class having only pure virtual functions
//
auto interface(meta::type_declaration& t) -> void;

#line 719 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C.35: A base class destructor should be either public and
//      virtual, or protected and non-virtual."
//
//     "[C.43] ... a base class should not be copyable, and so does not
//      necessarily need a default constructor."
//
//          -- Stroustrup, Sutter, et al. (C++ Core Guidelines)
//
//-----------------------------------------------------------------------
//
//  polymorphic_base
//
//  A pure polymorphic base type that is not copyable, and whose
//  destructor is either public and virtual or protected and nonvirtual.
//
//  Unlike an interface, it can have nonpublic and nonvirtual functions.
//
auto polymorphic_base(meta::type_declaration& t) -> void;

#line 763 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "... A totally ordered type ... requires operator<=> that
//      returns std::strong_ordering. If the function is not
//      user-written, a lexicographical memberwise implementation
//      is generated by default..."
//
//          -- P0707R4, section 3
//
//      Note: This feature derived from Cpp2 was already adopted
//            into Standard C++ via paper P0515, so most of the
//            heavy lifting is done by the Cpp1 C++20/23 compiler,
//            including the memberwise default semantics
//            (In contrast, cppfront has to do the work itself for
//            default memberwise semantics for operator= assignment
//            as those aren't yet part of Standard C++)
//
//-----------------------------------------------------------------------
//

auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::in<std::string_view> ordering// must be "strong_ordering" etc.
) -> void;

#line 807 "reflect.h2"
//-----------------------------------------------------------------------
//  ordered - a totally ordered type
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto ordered(meta::type_declaration& t) -> void;

#line 817 "reflect.h2"
//-----------------------------------------------------------------------
//  weakly_ordered - a weakly ordered type
//
auto weakly_ordered(meta::type_declaration& t) -> void;

#line 825 "reflect.h2"
//-----------------------------------------------------------------------
//  partially_ordered - a partially ordered type
//
auto partially_ordered(meta::type_declaration& t) -> void;

#line 834 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A value is ... a regular type. It must have all public
//      default construction, copy/move construction/assignment,
//      and destruction, all of which are generated by default
//      if not user-written; and it must not have any protected
//      or virtual functions (including the destructor)."
//
//          -- P0707R4, section 3
//
//-----------------------------------------------------------------------
//
//  copyable
//
//  A type with (copy and move) x (construction and assignment)
//
auto copyable(meta::type_declaration& t) -> void;

#line 871 "reflect.h2"
//-----------------------------------------------------------------------
//
//  basic_value
//
//  A regular type: copyable, plus has public default construction
//  and no protected or virtual functions
//
auto basic_value(meta::type_declaration& t) -> void;

#line 896 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "A 'value' is a totally ordered basic_value..."
//
//          -- P0707R4, section 3
//
//  value - a value type that is totally ordered
//
//  Note: the ordering that should be encouraged as default gets the nice name
//
auto value(meta::type_declaration& t) -> void;

#line 912 "reflect.h2"
auto weakly_ordered_value(meta::type_declaration& t) -> void;

#line 918 "reflect.h2"
auto partially_ordered_value(meta::type_declaration& t) -> void;

#line 925 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "By definition, a `struct` is a `class` in which members
//      are by default `public`; that is,
//
//      	struct s { ...
//
//      is simply shorthand for
//
//          class s { public: ...
//
//      ... Which style you use depends on circumstances and taste.
//      I usually prefer to use `struct` for classes that have all
//      data `public`."
//
//          -- Stroustrup (The C++ Programming Language, 3rd ed., p. 234)
//
//-----------------------------------------------------------------------
//
//  struct
//
//  a type with only public bases, objects, and functions,
//  no virtual functions, and no user-defined constructors
//  (i.e., no invariants) or assignment or destructors.
//
auto cpp2_struct(meta::type_declaration& t) -> void;

#line 968 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "C enumerations constitute a curiously half-baked concept. ...
//      the cleanest way out was to deem each enumeration a separate type."
//
//          -- Stroustrup (The Design and Evolution of C++, 11.7)
//
//     "An enumeration is a distinct type ... with named constants"
//
//          -- ISO C++ Standard
//
//-----------------------------------------------------------------------
//
//  basic_enum
//
//  a type together with named constants that are its possible values
//
class value_member_info {
    public: std::string name; 
    public: std::string type; 
    public: std::string value; 
};

auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::in<bool> bitwise
    ) -> void;

#line 1174 "reflect.h2"
//-----------------------------------------------------------------------
//
//    "An enum[...] is a totally ordered value type that stores a
//     value of its enumerators's type, and otherwise has only public
//     member variables of its enumerator's type, all of which are
//     naturally scoped because they are members of a type."
//
//          -- P0707R4, section 3
//
auto cpp2_enum(meta::type_declaration& t) -> void;

#line 1200 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "flag_enum expresses an enumeration that stores values
//      corresponding to bitwise-or'd enumerators. The enumerators must
//      be powers of two, and are automatically generated [...] A none
//      value is provided [...] Operators | and & are provided to
//      combine and extract values."
//
//          -- P0707R4, section 3
//
auto flag_enum(meta::type_declaration& t) -> void;

#line 1232 "reflect.h2"
//-----------------------------------------------------------------------
//
//     "As with void*, programmers should know that unions [...] are
//      inherently dangerous, should be avoided wherever possible,
//      and should be handled with special care when actually needed."
//
//          -- Stroustrup (The Design and Evolution of C++, 14.3.4.1)
//
//     "C++17 needs a type-safe union... The implications of the
//      consensus `variant` design are well understood and have been
//      explored over several LEWG discussions, over a thousand emails,
//      a joint LEWG/EWG session, and not to mention 12 years of
//      experience with Boost and other libraries."
//
//          -- Axel Naumann, in P0088 (wg21.link/p0088),
//             the adopted proposal for C++17 std::variant
//
//-----------------------------------------------------------------------
//
//  union
//
//  a type that contains exactly one of a fixed set of values at a time
//

auto cpp2_union(meta::type_declaration& t) -> void;

#line 1388 "reflect.h2"
//-----------------------------------------------------------------------
//
//  print - output a pretty-printed visualization of t
//
auto print(cpp2::in<meta::type_declaration> t) -> void;

#line 1398 "reflect.h2"
//-----------------------------------------------------------------------
//
//  visible - makes t visible in a DLL
//
auto visible(meta::function_declaration& t) -> void;

#line 1409 "reflect.h2"
}

}

#endif
