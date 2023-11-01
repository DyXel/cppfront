
#ifndef CPP2REFLECT_H_CPP2
#error This file is part of a '.h2' header compiled to be consumed from another -pure-cpp2 file. To use this file, write '#include "cpp2reflect.h2"' in a '.h2' or '.cpp2' file compiled with -pure-cpp2.
#endif

#ifndef CPP2REFLECT_HPP_CPP2
#define CPP2REFLECT_HPP_CPP2



//=== Cpp2 function definitions =================================================

#line 1 "cpp2reflect.h2"

#line 19 "cpp2reflect.h2"
namespace cpp2 {

namespace meta {

#line 36 "cpp2reflect.h2"
    [[nodiscard]] auto compiler_services::data() const& -> auto&& { return std::any_cast<std::add_lvalue_reference_t<compiler_services_data const>>(data_);  }
    [[nodiscard]] auto compiler_services::data() & -> auto&& { return std::any_cast<std::add_lvalue_reference_t<compiler_services_data>>(data_);  }

#line 41 "cpp2reflect.h2"
    compiler_services::compiler_services(

        cpp2::in<std::any> data_v
    )
        : data_{ data_v }
#line 45 "cpp2reflect.h2"
    {

        if (cpp2::Type.has_handler() && !(CPP2_UFCS(type)(data_) == Typeid<compiler_services_data>()) ) { cpp2::Type.report_violation(CPP2_CONTRACT_MSG("parameter 'data_v' must store a 'compiler_services_data'")); }
    }

#line 52 "cpp2reflect.h2"
    auto compiler_services::set_metafunction_name(cpp2::in<std::string_view> name, cpp2::in<std::vector<std::string>> args) & -> void{
        data().metafunction_name  = name;
        data().metafunction_args  = args;
        data().metafunctions_used = CPP2_UFCS(empty)(args);
    }

    [[nodiscard]] auto compiler_services::get_metafunction_name() const& -> std::string_view { return data().metafunction_name;  }

    [[nodiscard]] auto compiler_services::get_argument(cpp2::in<int> index) & -> std::string{
        data().metafunctions_used = true;
        if (([_0 = 0, _1 = index, _2 = CPP2_UFCS(ssize)(data().metafunction_args)]{ return cpp2::cmp_less_eq(_0,_1) && cpp2::cmp_less(_1,_2); }())) {
            return CPP2_ASSERT_IN_BOUNDS(data().metafunction_args, index); 
        }
        return ""; 
    }

    [[nodiscard]] auto compiler_services::get_arguments() & -> std::vector<std::string>{
        data().metafunctions_used = true;
        return data().metafunction_args; 
    }

    [[nodiscard]] auto compiler_services::arguments_were_used() const& -> bool { return data().metafunctions_used;  }

    [[nodiscard]] auto compiler_services::parse_statement(

        std::string_view source
    ) & -> auto

    {
        auto original_source {source}; 

        CPP2_UFCS(push_back)(generated_lines, std::vector<source_line>());
        auto lines {&CPP2_UFCS(back)(generated_lines)}; 

        auto add_line {[&, _1 = lines](cpp2::in<std::string_view> s) mutable -> void{
            static_cast<void>(CPP2_UFCS(emplace_back)((*cpp2::assert_not_null(_1)), s, source_line::category::cpp2));
        }}; 
{
auto newline_pos = CPP2_UFCS(find)(source, '\n');

        //  First split this string into source_lines
        //

#line 93 "cpp2reflect.h2"
        if ( cpp2::cmp_greater(CPP2_UFCS(ssize)(source),1) 
            && newline_pos != source.npos) 
        {
            while( newline_pos != std::string_view::npos ) 
            {
                add_line(CPP2_UFCS(substr)(source, 0, newline_pos));
                CPP2_UFCS(remove_prefix)(source, newline_pos + 1);
                newline_pos = CPP2_UFCS(find)(source, '\n');
            }
        }
}

#line 104 "cpp2reflect.h2"
        if (!(CPP2_UFCS(empty)(source))) {
            std::move(add_line)(std::move(source));
        }

        //  Now lex this source fragment to generate
        //  a single grammar_map entry, whose .second
        //  is the vector of tokens
        static_cast<void>(CPP2_UFCS(emplace_back)(generated_lexers, *cpp2::assert_not_null(data().errors)));
        auto tokens {&CPP2_UFCS(back)(generated_lexers)}; 
        CPP2_UFCS(lex)((*cpp2::assert_not_null(tokens)), *cpp2::assert_not_null(std::move(lines)), true);

        if (cpp2::Default.has_handler() && !(std::ssize(CPP2_UFCS(get_map)((*cpp2::assert_not_null(tokens)))) == 1) ) { cpp2::Default.report_violation(""); }

        //  Now parse this single declaration from
        //  the lexed tokens
        auto ret {CPP2_UFCS(parse_one_declaration)(data().parser, 
                 (*cpp2::assert_not_null(CPP2_UFCS(begin)(CPP2_UFCS(get_map)(*cpp2::assert_not_null(std::move(tokens)))))).second, 
                 *cpp2::assert_not_null(data().generated_tokens)
               )}; 
        if (!(ret)) {
            error("parse failed - the source string is not a valid statement:\n" + cpp2::to_string(std::move(original_source)));
        }
        return ret; 
    }

    [[nodiscard]] auto compiler_services::position() const& -> auto { return std::any_cast<source_position>(vposition());  }
    [[nodiscard]] auto compiler_services::vposition() const -> std::any { return source_position();  }

#line 135 "cpp2reflect.h2"
    auto compiler_services::require(

        cpp2::in<bool> b, 
        cpp2::in<std::string_view> msg
    ) const& -> void
    {
        if (!(b)) {
            error(msg);
        }
    }

    auto compiler_services::error(cpp2::in<std::string_view> msg) const& -> void
    {
        auto message {cpp2::as_<std::string>(msg)}; 
        if (!(CPP2_UFCS(empty)(data().metafunction_name))) {
            message = "while applying @" + cpp2::to_string(data().metafunction_name) + " - " + cpp2::to_string(message);
        }
        static_cast<void>(CPP2_UFCS(emplace_back)((*cpp2::assert_not_null(data().errors)), position(), std::move(message)));
    }

#line 158 "cpp2reflect.h2"
    auto compiler_services::report_violation(auto const& msg) const& -> void{
        error(msg);
        throw(std::runtime_error("  ==> programming bug found in metafunction @" + cpp2::to_string(data().metafunction_name) + " - contract violation - see previous errors"));
    }

    [[nodiscard]] auto compiler_services::has_handler() const& -> auto { return true;  }

    compiler_services::~compiler_services() noexcept{}
compiler_services::compiler_services(compiler_services const& that)
                                : data_{ that.data_ }{}

#line 221 "cpp2reflect.h2"
        template<typename T> declaration_base::node_pointer::node_pointer(

            T const& n_
        )
            : n{ n_ }
#line 225 "cpp2reflect.h2"
        {

            if (cpp2::Default.has_handler() && !(n_) ) { cpp2::Default.report_violation(CPP2_CONTRACT_MSG("a meta::declaration must point to a valid declaration_node, not null")); }
            static_assert(std::is_same_v<T,declaration_node*>);
        }
#line 221 "cpp2reflect.h2"
        template<typename T> auto declaration_base::node_pointer::operator=(

            T const& n_
        ) -> node_pointer& 
        {
            n = n_;

#line 227 "cpp2reflect.h2"
            if (cpp2::Default.has_handler() && !(n_) ) { cpp2::Default.report_violation(CPP2_CONTRACT_MSG("a meta::declaration must point to a valid declaration_node, not null")); }
            static_assert(std::is_same_v<T,declaration_node*>);
            return *this;
#line 229 "cpp2reflect.h2"
        }

        [[nodiscard]] auto declaration_base::node_pointer::operator*() const& -> auto&& { return *cpp2::assert_not_null(std::any_cast<declaration_node*>(n));  }

        declaration_base::node_pointer::node_pointer(node_pointer const& that)
                                : n{ that.n }{}

auto declaration_base::node_pointer::operator=(node_pointer const& that) -> node_pointer& {
                                n = that.n;
                                return *this;}
declaration_base::node_pointer::node_pointer(node_pointer&& that) noexcept
                                : n{ std::move(that).n }{}
auto declaration_base::node_pointer::operator=(node_pointer&& that) noexcept -> node_pointer& {
                                n = std::move(that).n;
                                return *this;}
#line 236 "cpp2reflect.h2"
    declaration_base::declaration_base(

        cpp2::in<node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : compiler_services{ s }
        , n{ n_ }
#line 241 "cpp2reflect.h2"
    {

#line 244 "cpp2reflect.h2"
    }

    [[nodiscard]] auto declaration_base::vposition() const -> std::any { return CPP2_UFCS(position)((*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration_base::print() const& -> std::string { return CPP2_UFCS(pretty_print_visualize)((*cpp2::assert_not_null(n)), 0);  }

    declaration_base::~declaration_base() noexcept{}
declaration_base::declaration_base(declaration_base const& that)
                                : compiler_services{ static_cast<compiler_services const&>(that) }
                                , n{ that.n }{}

#line 259 "cpp2reflect.h2"
    declaration::declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : declaration_base{ n_, s }
#line 264 "cpp2reflect.h2"
    {

    }

    [[nodiscard]] auto declaration::is_public() const& -> bool { return CPP2_UFCS(is_public)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_protected() const& -> bool { return CPP2_UFCS(is_protected)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_private() const& -> bool { return CPP2_UFCS(is_private)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_default_access() const& -> bool { return CPP2_UFCS(is_default_access)((*cpp2::assert_not_null(n)));  }

    auto declaration::default_to_public() & -> void { static_cast<void>(CPP2_UFCS(make_public)((*cpp2::assert_not_null(n)))); }
    auto declaration::default_to_protected() & -> void { static_cast<void>(CPP2_UFCS(make_protected)((*cpp2::assert_not_null(n))));  }
    auto declaration::default_to_private() & -> void { static_cast<void>(CPP2_UFCS(make_private)((*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto declaration::make_public() & -> bool { return CPP2_UFCS(make_public)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_protected() & -> bool { return CPP2_UFCS(make_protected)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::make_private() & -> bool { return CPP2_UFCS(make_private)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::has_name() const& -> bool { return CPP2_UFCS(has_name)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::has_name(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_name)((*cpp2::assert_not_null(n)), s); }

    [[nodiscard]] auto declaration::name() const& -> std::string_view{
        if (has_name()) {return CPP2_UFCS(as_string_view)((*cpp2::assert_not_null(CPP2_UFCS(name)(*cpp2::assert_not_null(n))))); }
        else          { return ""; }
    }

    [[nodiscard]] auto declaration::has_initializer() const& -> bool { return CPP2_UFCS(has_initializer)((*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration::is_global() const& -> bool { return CPP2_UFCS(is_global)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_function() const& -> bool { return CPP2_UFCS(is_function)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_object() const& -> bool { return CPP2_UFCS(is_object)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_base_object() const& -> bool { return CPP2_UFCS(is_base_object)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_member_object() const& -> bool { return CPP2_UFCS(is_member_object)((*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_type() const& -> bool { return CPP2_UFCS(is_type)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_namespace() const& -> bool { return CPP2_UFCS(is_namespace)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_alias() const& -> bool { return CPP2_UFCS(is_alias)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::is_type_alias() const& -> bool { return CPP2_UFCS(is_type_alias)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::is_namespace_alias() const& -> bool { return CPP2_UFCS(is_namespace_alias)((*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::is_object_alias() const& -> bool { return CPP2_UFCS(is_object_alias)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::is_function_expression() const& -> bool { return CPP2_UFCS(is_function_expression)((*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto declaration::as_function() const& -> function_declaration { return function_declaration(n, (*this));  }
    [[nodiscard]] auto declaration::as_object() const& -> object_declaration { return object_declaration(n, (*this)); }
    [[nodiscard]] auto declaration::as_type() const& -> type_declaration { return type_declaration(n, (*this)); }
    [[nodiscard]] auto declaration::as_alias() const& -> alias_declaration { return alias_declaration(n, (*this)); }

    [[nodiscard]] auto declaration::get_parent() const& -> declaration { return declaration((*cpp2::assert_not_null(n)).parent_declaration, (*this)); }

    [[nodiscard]] auto declaration::parent_is_function() const& -> bool { return CPP2_UFCS(parent_is_function)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_object() const& -> bool { return CPP2_UFCS(parent_is_object)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_type() const& -> bool { return CPP2_UFCS(parent_is_type)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_namespace() const& -> bool { return CPP2_UFCS(parent_is_namespace)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_alias() const& -> bool { return CPP2_UFCS(parent_is_alias)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::parent_is_type_alias() const& -> bool { return CPP2_UFCS(parent_is_type_alias)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto declaration::parent_is_namespace_alias() const& -> bool { return CPP2_UFCS(parent_is_namespace_alias)((*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto declaration::parent_is_object_alias() const& -> bool { return CPP2_UFCS(parent_is_object_alias)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto declaration::parent_is_polymorphic() const& -> bool { return CPP2_UFCS(parent_is_polymorphic)((*cpp2::assert_not_null(n)));  }

    auto declaration::mark_for_removal_from_enclosing_type() & -> void

    {
        if (cpp2::Type.has_handler() && !(parent_is_type()) ) { cpp2::Type.report_violation(""); }
#line 328 "cpp2reflect.h2"
        auto test {CPP2_UFCS(type_member_mark_for_removal)((*cpp2::assert_not_null(n)))}; 
        if (cpp2::Default.has_handler() && !(std::move(test)) ) { cpp2::Default.report_violation(""); }// ... to ensure this assert is true
    }

    declaration::~declaration() noexcept{}
declaration::declaration(declaration const& that)
                                : declaration_base{ static_cast<declaration_base const&>(that) }{}

#line 341 "cpp2reflect.h2"
    function_declaration::function_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 346 "cpp2reflect.h2"
    {

        if (cpp2::Default.has_handler() && !(CPP2_UFCS(is_function)((*cpp2::assert_not_null(n)))) ) { cpp2::Default.report_violation(""); }
    }

    [[nodiscard]] auto function_declaration::index_of_parameter_named(cpp2::in<std::string_view> s) const& -> int { return CPP2_UFCS(index_of_parameter_named)((*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_parameter_named)((*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_in_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_in_parameter_named)((*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_out_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_out_parameter_named)((*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::has_move_parameter_named(cpp2::in<std::string_view> s) const& -> bool { return CPP2_UFCS(has_move_parameter_named)((*cpp2::assert_not_null(n)), s); }
    [[nodiscard]] auto function_declaration::first_parameter_name() const& -> std::string { return CPP2_UFCS(first_parameter_name)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::has_parameter_with_name_and_pass(cpp2::in<std::string_view> s, auto const& pass) const& -> bool { 
                                                  return CPP2_UFCS(has_parameter_with_name_and_pass)((*cpp2::assert_not_null(n)), s, pass);  }
    [[nodiscard]] auto function_declaration::is_function_with_this() const& -> bool { return CPP2_UFCS(is_function_with_this)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_virtual() const& -> bool { return CPP2_UFCS(is_virtual_function)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_defaultable() const& -> bool { return CPP2_UFCS(is_defaultable_function)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor() const& -> bool { return CPP2_UFCS(is_constructor)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_default_constructor() const& -> bool { return CPP2_UFCS(is_default_constructor)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_move() const& -> bool { return CPP2_UFCS(is_move)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_swap() const& -> bool { return CPP2_UFCS(is_swap)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_that() const& -> bool { return CPP2_UFCS(is_constructor_with_that)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_in_that() const& -> bool { return CPP2_UFCS(is_constructor_with_in_that)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_constructor_with_move_that() const& -> bool { return CPP2_UFCS(is_constructor_with_move_that)((*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_assignment() const& -> bool { return CPP2_UFCS(is_assignment)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_that() const& -> bool { return CPP2_UFCS(is_assignment_with_that)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_in_that() const& -> bool { return CPP2_UFCS(is_assignment_with_in_that)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::is_assignment_with_move_that() const& -> bool { return CPP2_UFCS(is_assignment_with_move_that)((*cpp2::assert_not_null(n)));  }
    [[nodiscard]] auto function_declaration::is_destructor() const& -> bool { return CPP2_UFCS(is_destructor)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::is_copy_or_move() const& -> bool { return is_constructor_with_that() || is_assignment_with_that(); }

    [[nodiscard]] auto function_declaration::has_declared_return_type() const& -> bool { return CPP2_UFCS(has_declared_return_type)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_deduced_return_type() const& -> bool { return CPP2_UFCS(has_deduced_return_type)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_bool_return_type() const& -> bool { return CPP2_UFCS(has_bool_return_type)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto function_declaration::has_non_void_return_type() const& -> bool { return CPP2_UFCS(has_non_void_return_type)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::unnamed_return_type() const& -> std::string { return CPP2_UFCS(unnamed_return_type_to_string)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto function_declaration::get_parameters() const& -> std::vector<object_declaration>

    {
        std::vector<object_declaration> ret {}; 
        for ( auto const& param : CPP2_UFCS(get_function_parameters)((*cpp2::assert_not_null(n))) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, &*cpp2::assert_not_null((*cpp2::assert_not_null(param)).declaration), (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto function_declaration::is_binary_comparison_function() const& -> bool { return CPP2_UFCS(is_binary_comparison_function)((*cpp2::assert_not_null(n)));  }

    auto function_declaration::default_to_virtual() & -> void { static_cast<void>(CPP2_UFCS(make_function_virtual)((*cpp2::assert_not_null(n)))); }

    [[nodiscard]] auto function_declaration::make_virtual() & -> bool { return CPP2_UFCS(make_function_virtual)((*cpp2::assert_not_null(n))); }

    auto function_declaration::add_initializer(cpp2::in<std::string_view> source) & -> void

#line 404 "cpp2reflect.h2"
    {
        if ((*this).has_handler() && !(!(has_initializer())) ) { (*this).report_violation(CPP2_CONTRACT_MSG("cannot add an initializer to a function that already has one")); }
        if ((*this).has_handler() && !(parent_is_type()) ) { (*this).report_violation(CPP2_CONTRACT_MSG("cannot add an initializer to a function that isn't in a type scope")); }
        //require( !has_initializer(),
        //         "cannot add an initializer to a function that already has one");
        //require( parent_is_type(),
        //         "cannot add an initializer to a function that isn't in a type scope");

#line 410 "cpp2reflect.h2"
        auto stmt {parse_statement(source)}; 
        if (!((cpp2::as_<bool>(stmt)))) {
            error("cannot add an initializer that is not a valid statement");
            return ; 
        }
        require(CPP2_UFCS(add_function_initializer)((*cpp2::assert_not_null(n)), std::move(stmt)), 
                 std::string("unexpected error while attempting to add initializer"));
    }

    function_declaration::function_declaration(function_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 428 "cpp2reflect.h2"
    object_declaration::object_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 433 "cpp2reflect.h2"
    {

        if (cpp2::Default.has_handler() && !(CPP2_UFCS(is_object)((*cpp2::assert_not_null(n)))) ) { cpp2::Default.report_violation(""); }
    }

    [[nodiscard]] auto object_declaration::is_const() const& -> bool { return CPP2_UFCS(is_const)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto object_declaration::has_wildcard_type() const& -> bool { return CPP2_UFCS(has_wildcard_type)((*cpp2::assert_not_null(n)));  }

    [[nodiscard]] auto object_declaration::type() const& -> std::string{
        auto ret {CPP2_UFCS(object_type)((*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this type: " + ret);
        return ret; 
    }

    [[nodiscard]] auto object_declaration::initializer() const& -> std::string{
        auto ret {CPP2_UFCS(object_initializer)((*cpp2::assert_not_null(n)))}; 
        require(!(contains(ret, "(*ERROR*)")), 
                 "cannot to_string this initializer: " + ret);
        return ret; 
    }

    object_declaration::object_declaration(object_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 464 "cpp2reflect.h2"
    type_declaration::type_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 469 "cpp2reflect.h2"
    {

        if (cpp2::Default.has_handler() && !(CPP2_UFCS(is_type)((*cpp2::assert_not_null(n)))) ) { cpp2::Default.report_violation(""); }
    }

    auto type_declaration::reserve_names(cpp2::in<std::string_view> name, auto&& ...etc) const& -> void
    {                           // etc is not declared ':string_view' for compatibility with GCC 10.x
        for ( 
             auto const& m : get_members() ) {
            CPP2_UFCS(require)(m, !(CPP2_UFCS(has_name)(m, name)), 
                       "in a '" + cpp2::to_string(get_metafunction_name()) + "' type, the name '" + cpp2::to_string(name) + "' is reserved for use by the '" + cpp2::to_string(get_metafunction_name()) + "' implementation");
        }
        if constexpr (!(CPP2_PACK_EMPTY(etc))) {
            reserve_names(CPP2_FORWARD(etc)...);
        }
    }

    [[nodiscard]] auto type_declaration::is_polymorphic() const& -> bool { return CPP2_UFCS(is_polymorphic)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::is_final() const& -> bool { return CPP2_UFCS(is_type_final)((*cpp2::assert_not_null(n))); }
    [[nodiscard]] auto type_declaration::make_final() & -> bool { return CPP2_UFCS(make_type_final)((*cpp2::assert_not_null(n))); }

    [[nodiscard]] auto type_declaration::get_member_functions() const& -> std::vector<function_declaration>

    {
        std::vector<function_declaration> ret {}; 
        for ( 
             auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::functions) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_functions_needing_initializer() const& -> std::vector<function_declaration>

    {
        std::vector<function_declaration> ret {}; 
        for ( 
             auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::functions) ) 
        if ( !(CPP2_UFCS(has_initializer)((*cpp2::assert_not_null(d)))) 
            && !(CPP2_UFCS(is_virtual_function)((*cpp2::assert_not_null(d)))) 
            && !(CPP2_UFCS(is_defaultable_function)((*cpp2::assert_not_null(d))))) 
        {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_objects() const& -> std::vector<object_declaration>

    {
        std::vector<object_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::objects) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_types() const& -> std::vector<type_declaration>

    {
        std::vector<type_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::types) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_member_aliases() const& -> std::vector<alias_declaration>

    {
        std::vector<alias_declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::aliases) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::get_members() const& -> std::vector<declaration>

    {
        std::vector<declaration> ret {}; 
        for ( auto const& d : CPP2_UFCS(get_type_scope_declarations)((*cpp2::assert_not_null(n)), declaration_node::all) ) {
            static_cast<void>(CPP2_UFCS(emplace_back)(ret, d, (*this)));
        }
        return ret; 
    }

    [[nodiscard]] auto type_declaration::query_declared_value_set_functions() const& -> query_declared_value_set_functions_ret

#line 563 "cpp2reflect.h2"
    {
            cpp2::deferred_init<bool> out_this_in_that;
            cpp2::deferred_init<bool> out_this_move_that;
            cpp2::deferred_init<bool> inout_this_in_that;
            cpp2::deferred_init<bool> inout_this_move_that;
#line 564 "cpp2reflect.h2"
        auto declared {CPP2_UFCS(find_declared_value_set_functions)((*cpp2::assert_not_null(n)))}; 
        out_this_in_that.construct(declared.out_this_in_that != nullptr);
        out_this_move_that.construct(declared.out_this_move_that != nullptr);
        inout_this_in_that.construct(declared.inout_this_in_that != nullptr);
        inout_this_move_that.construct(std::move(declared).inout_this_move_that != nullptr);
    return  { std::move(out_this_in_that.value()), std::move(out_this_move_that.value()), std::move(inout_this_in_that.value()), std::move(inout_this_move_that.value()) }; }

    auto type_declaration::add_member(cpp2::in<std::string_view> source) & -> void
    {
        auto decl {parse_statement(source)}; 
        if (!((cpp2::as_<bool>(decl)))) {
            error("the provided source string is not a valid statement");
            return ; 
        }
        if (!(CPP2_UFCS(is_declaration)((*cpp2::assert_not_null(decl))))) {
            error("cannot add a member that is not a declaration");
        }
        require(CPP2_UFCS(add_type_member)((*cpp2::assert_not_null(n)), std::move(decl)), 
                 std::string("unexpected error while attempting to add member:\n") + source);
    }

    auto type_declaration::remove_marked_members() & -> void { CPP2_UFCS(type_remove_marked_members)((*cpp2::assert_not_null(n)));  }
    auto type_declaration::remove_all_members() & -> void { CPP2_UFCS(type_remove_all_members)((*cpp2::assert_not_null(n))); }

    auto type_declaration::disable_member_function_generation() & -> void { CPP2_UFCS(type_disable_member_function_generation)((*cpp2::assert_not_null(n)));  }

    type_declaration::type_declaration(type_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 599 "cpp2reflect.h2"
    alias_declaration::alias_declaration(

        cpp2::in<declaration_base::node_pointer> n_, 
        cpp2::in<compiler_services> s
    )
        : declaration{ n_, s }
#line 604 "cpp2reflect.h2"
    {

        if (cpp2::Default.has_handler() && !(CPP2_UFCS(is_alias)((*cpp2::assert_not_null(n)))) ) { cpp2::Default.report_violation(""); }
    }

    alias_declaration::alias_declaration(alias_declaration const& that)
                                : declaration{ static_cast<declaration const&>(that) }{}

#line 623 "cpp2reflect.h2"
auto add_virtual_destructor(meta::type_declaration& t) -> void
{
    CPP2_UFCS(add_member)(t, "operator=: (virtual move this) = { }");
}

#line 641 "cpp2reflect.h2"
auto interface(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& m : CPP2_UFCS(get_members)(t) ) 
    {
        CPP2_UFCS(require)(m, !(CPP2_UFCS(is_object)(m)), 
                   "interfaces may not contain data objects");
        if (CPP2_UFCS(is_function)(m)) {
            auto mf {CPP2_UFCS(as_function)(m)}; 
            CPP2_UFCS(require)(mf, !(CPP2_UFCS(is_copy_or_move)(mf)), 
                        "interfaces may not copy or move; consider a virtual clone() instead");
            CPP2_UFCS(require)(mf, !(CPP2_UFCS(has_initializer)(mf)), 
                        "interface functions must not have a function body; remove the '=' initializer");
            CPP2_UFCS(require)(mf, CPP2_UFCS(make_public)(mf), 
                        "interface functions must be public");
            CPP2_UFCS(default_to_virtual)(mf);
            has_dtor |= CPP2_UFCS(is_destructor)(mf);
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS(add_virtual_destructor)(t);
    }
}

#line 687 "cpp2reflect.h2"
auto polymorphic_base(meta::type_declaration& t) -> void
{
    auto has_dtor {false}; 

    for ( auto& mf : CPP2_UFCS(get_member_functions)(t) ) 
    {
        if (CPP2_UFCS(is_default_access)(mf)) {
            CPP2_UFCS(default_to_public)(mf);
        }
        CPP2_UFCS(require)(mf, !(CPP2_UFCS(is_copy_or_move)(mf)), 
                    "polymorphic base types may not copy or move; consider a virtual clone() instead");
        if (CPP2_UFCS(is_destructor)(mf)) {
            has_dtor = true;
            CPP2_UFCS(require)(mf, ((CPP2_UFCS(is_public)(mf) || CPP2_UFCS(is_default_access)(mf)) && CPP2_UFCS(is_virtual)(mf)) 
                        || (CPP2_UFCS(is_protected)(mf) && !(CPP2_UFCS(is_virtual)(mf))), 
                        "a polymorphic base type destructor must be public and virtual, or protected and nonvirtual");
        }
    }

    if (!(std::move(has_dtor))) {
        CPP2_UFCS(add_virtual_destructor)(t);
    }
}

#line 732 "cpp2reflect.h2"
auto ordered_impl(
    meta::type_declaration& t, 
    cpp2::in<std::string_view> ordering
) -> void
{
    auto has_spaceship {false}; 

    for ( auto& mf : CPP2_UFCS(get_member_functions)(t) ) 
    {
        if (CPP2_UFCS(has_name)(mf, "operator<=>")) {
            has_spaceship = true;
            auto return_name {CPP2_UFCS(unnamed_return_type)(mf)}; 
            if (CPP2_UFCS(find)(return_name, ordering) == return_name.npos) 
            {
                CPP2_UFCS(error)(mf, "operator<=> must return std::" + cpp2::as_<std::string>(ordering));
            }
        }
    }

    if (!(std::move(has_spaceship))) {
        CPP2_UFCS(add_member)(t, "operator<=>: (this, that) -> std::" + (cpp2::as_<std::string>(ordering)) + ";");
    }
}

#line 761 "cpp2reflect.h2"
auto ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "strong_ordering");
}

#line 769 "cpp2reflect.h2"
auto weakly_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "weak_ordering");
}

#line 777 "cpp2reflect.h2"
auto partially_ordered(meta::type_declaration& t) -> void
{
    ordered_impl(t, "partial_ordering");
}

#line 799 "cpp2reflect.h2"
auto copyable(meta::type_declaration& t) -> void
{
    //  If the user explicitly wrote any of the copy/move functions,
    //  they must also have written the most general one - we can't
    //  assume we can safely generate it for them since they've opted
    //  into customized semantics
    auto smfs {CPP2_UFCS(query_declared_value_set_functions)(t)}; 
    if ( !(smfs.out_this_in_that) 
        && (
            smfs.out_this_move_that 
            || smfs.inout_this_in_that 
            || smfs.inout_this_move_that)) 

    {
        CPP2_UFCS(error)(t, "this type is partially copyable/movable - when you provide any of the more-specific operator= signatures, you must also provide the one with the general signature (out this, that); alternatively, consider removing all the operator= functions and let them all be generated for you with default memberwise semantics");
    }
    else {if (!(std::move(smfs).out_this_in_that)) {
        CPP2_UFCS(add_member)(t, "operator=: (out this, that) = { }");
    }}
}

#line 827 "cpp2reflect.h2"
auto basic_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS(copyable)(t);

    auto has_default_ctor {false}; 
    for ( auto& mf : CPP2_UFCS(get_member_functions)(t) ) {
        has_default_ctor |= CPP2_UFCS(is_default_constructor)(mf);
        CPP2_UFCS(require)(mf, !(CPP2_UFCS(is_protected)(mf)) && !(CPP2_UFCS(is_virtual)(mf)), 
                    "a value type may not have a protected or virtual function");
        CPP2_UFCS(require)(mf, !(CPP2_UFCS(is_destructor)(mf)) || CPP2_UFCS(is_public)(mf) || CPP2_UFCS(is_default_access)(mf), 
                    "a value type may not have a non-public destructor");
    }

    if (!(std::move(has_default_ctor))) {
        CPP2_UFCS(add_member)(t, "operator=: (out this) = { }");
    }
}

#line 855 "cpp2reflect.h2"
auto value(meta::type_declaration& t) -> void
{
    CPP2_UFCS(ordered)(t);
    CPP2_UFCS(basic_value)(t);
}

auto weakly_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS(weakly_ordered)(t);
    CPP2_UFCS(basic_value)(t);
}

auto partially_ordered_value(meta::type_declaration& t) -> void
{
    CPP2_UFCS(partially_ordered)(t);
    CPP2_UFCS(basic_value)(t);
}

#line 899 "cpp2reflect.h2"
auto cpp2_struct(meta::type_declaration& t) -> void
{
    for ( auto& m : CPP2_UFCS(get_members)(t) ) 
    {
        CPP2_UFCS(require)(m, CPP2_UFCS(make_public)(m), 
                   "all struct members must be public");
        if (CPP2_UFCS(is_function)(m)) {
            auto mf {CPP2_UFCS(as_function)(m)}; 
            CPP2_UFCS(require)(t, !(CPP2_UFCS(is_virtual)(mf)), 
                       "a struct may not have a virtual function");
            CPP2_UFCS(require)(t, !(CPP2_UFCS(has_name)(mf, "operator=")), 
                       "a struct may not have a user-defined operator=");
        }
    }
    CPP2_UFCS(disable_member_function_generation)(t);
}

#line 940 "cpp2reflect.h2"
auto basic_enum(
    meta::type_declaration& t, 
    auto const& nextval, 
    cpp2::in<bool> bitwise
    ) -> void
{
    std::vector<value_member_info> enumerators {}; 
    cpp2::i64 min_value {}; 
    cpp2::i64 max_value {}; 
    cpp2::deferred_init<std::string> underlying_type; 

    CPP2_UFCS(reserve_names)(t, "operator=", "operator<=>");
    if (bitwise) {
        CPP2_UFCS(reserve_names)(t, "has", "set", "clear", "to_string", "get_raw_value", "none");
    }

    //  1. Gather: The names of all the user-written members, and find/compute the type

    underlying_type.construct(CPP2_UFCS(get_argument)(t, 0));// use the first template argument, if there was one

    auto found_non_numeric {false}; 
{
std::string value = "-1";

#line 963 "cpp2reflect.h2"
    for ( 
          auto const& m : CPP2_UFCS(get_members)(t) ) 
    if (  CPP2_UFCS(is_member_object)(m)) 
    {
        CPP2_UFCS(require)(m, CPP2_UFCS(is_public)(m) || CPP2_UFCS(is_default_access)(m), 
                    "an enumerator cannot be protected or private");

        auto mo {CPP2_UFCS(as_object)(m)}; 
        if (!(CPP2_UFCS(has_wildcard_type)(mo))) {
            CPP2_UFCS(error)(mo, "an explicit underlying type should be specified as a template argument to the metafunction - try 'enum<u16>' or 'flag_enum<u64>'");
        }

        auto init {CPP2_UFCS(initializer)(mo)}; 

        auto is_default_or_numeric {is_empty_or_a_decimal_number(init)}; 
        found_non_numeric |= !(CPP2_UFCS(empty)(init)) && !(is_default_or_numeric);
        CPP2_UFCS(require)(m, !(is_default_or_numeric) || !(found_non_numeric) || CPP2_UFCS(has_name)(mo, "none"), 
            cpp2::to_string(CPP2_UFCS(name)(mo)) + ": enumerators with non-numeric values must come after all default and numeric values");

        nextval(value, init);

        auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS(value, 0), nullptr, 10)}; // for non-numeric values we'll just get 0 which is okay for now
        if (cpp2::cmp_less(v,min_value)) {
            min_value = v;
        }
        if (cpp2::cmp_greater(v,max_value)) {
            max_value = v;
        }

        //  Adding local variable 'e' to work around a Clang warning
        value_member_info e {cpp2::as_<std::string>(CPP2_UFCS(name)(mo)), "", value}; 
        CPP2_UFCS(push_back)(enumerators, e);

        CPP2_UFCS(mark_for_removal_from_enclosing_type)(mo);
    }
}

#line 999 "cpp2reflect.h2"
    if ((CPP2_UFCS(empty)(enumerators))) {
        CPP2_UFCS(error)(t, "an enumeration must contain at least one enumerator value");
        return ; 
    }

    //  Compute the default underlying type, if it wasn't explicitly specified
    if (underlying_type.value() == "") 
    {
        CPP2_UFCS(require)(t, !(std::move(found_non_numeric)), 
            "if you write an enumerator with a non-numeric-literal value, you must specify the enumeration's underlying type");

        if (!(bitwise)) {
            if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i8>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i8>::max())) {
                underlying_type.value() = "i8";
            }
            else {if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i16>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i16>::max())) {
                underlying_type.value() = "i16";
            }
            else {if (cpp2::cmp_greater_eq(min_value,std::numeric_limits<cpp2::i32>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i32>::max())) {
                underlying_type.value() = "i32";
            }
            else {if (cpp2::cmp_greater_eq(std::move(min_value),std::numeric_limits<cpp2::i64>::min()) && cpp2::cmp_less_eq(max_value,std::numeric_limits<cpp2::i64>::max())) {
                underlying_type.value() = "i64";
            }
            else {
                CPP2_UFCS(error)(t, "values are outside the range representable by the largest supported underlying signed type (i64)");
            }}}}
        }
        else {
            auto umax {std::move(max_value) * cpp2::as_<cpp2::u64, 2>()}; 
            if (cpp2::cmp_less_eq(umax,std::numeric_limits<cpp2::u8>::max())) {
                underlying_type.value() = "u8";
            }
            else {if (cpp2::cmp_less_eq(umax,std::numeric_limits<cpp2::u16>::max())) {
                underlying_type.value() = "u16";
            }
            else {if (cpp2::cmp_less_eq(std::move(umax),std::numeric_limits<cpp2::u32>::max())) {
                underlying_type.value() = "u32";
            }
            else {
                underlying_type.value() = "u64";
            }}}
        }
    }

#line 1045 "cpp2reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents
    //
    //  Note that most values and functions are declared as '==' compile-time values, i.e. Cpp1 'constexpr'

    CPP2_UFCS(remove_marked_members)(t);

    //  Generate the 'none' value if appropriate, and use that or
    //  else the first enumerator as the default-constructed value
    auto default_value {CPP2_ASSERT_IN_BOUNDS(enumerators, 0).name}; 
    if (bitwise) {
        default_value = "none";
        value_member_info e {"none", "", "0"}; 
        CPP2_UFCS(push_back)(enumerators, std::move(e));
    }

    //  Generate all the private implementation
    CPP2_UFCS(add_member)(t, "    _value            : " + cpp2::to_string(underlying_type.value()) + ";");
    CPP2_UFCS(add_member)(t, "    private operator= : (implicit out this, _val: i64) == _value = cpp2::unsafe_narrow<" + cpp2::to_string(underlying_type.value()) + ">(_val);");

    //  Generate the bitwise operations
    if (bitwise) {
        CPP2_UFCS(add_member)(t, "    operator|=: ( inout this, that )                 == _value |= that._value;");
        CPP2_UFCS(add_member)(t, "    operator&=: ( inout this, that )                 == _value &= that._value;");
        CPP2_UFCS(add_member)(t, "    operator^=: ( inout this, that )                 == _value ^= that._value;");
        CPP2_UFCS(add_member)(t, "    operator| : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS(name)(t)) + "  == _value |  that._value;");
        CPP2_UFCS(add_member)(t, "    operator& : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS(name)(t)) + "  == _value &  that._value;");
        CPP2_UFCS(add_member)(t, "    operator^ : (       this, that ) -> " + cpp2::to_string(CPP2_UFCS(name)(t)) + "  == _value ^  that._value;");
        CPP2_UFCS(add_member)(t, "    has       : ( inout this, that ) -> bool         == _value &  that._value;");
        CPP2_UFCS(add_member)(t, "    set       : ( inout this, that )                 == _value |= that._value;");
        CPP2_UFCS(add_member)(t, "    clear     : ( inout this, that )                 == _value &= that._value~;");
    }

    //  Add the enumerators
    for ( auto const& e : enumerators ) {
        CPP2_UFCS(add_member)(t, "    " + cpp2::to_string(e.name) + " : " + cpp2::to_string(CPP2_UFCS(name)(t)) + " == " + cpp2::to_string(e.value) + ";");
    }

    //  Generate the common functions
    CPP2_UFCS(add_member)(t, "    get_raw_value     : (this) -> " + cpp2::to_string(std::move(underlying_type.value())) + " == _value;");
    CPP2_UFCS(add_member)(t, "    operator=         : (out this) == { _value = " + cpp2::to_string(std::move(default_value)) + "._value; }");
    CPP2_UFCS(add_member)(t, "    operator=         : (out this, that) == { }");
    CPP2_UFCS(add_member)(t, "    operator<=>       : (this, that) -> std::strong_ordering;");
{
std::string to_string = "    to_string: (this) -> std::string = { \n";

    //  Provide a 'to_string' function to print enumerator name(s)

#line 1090 "cpp2reflect.h2"
    {
        if (bitwise) {
            to_string += "    _ret   : std::string = \"(\";\n";
            to_string += "    _comma : std::string = ();\n";
            to_string += "    if this == none { return \"(none)\"; }\n";
        }

        for ( 
              auto const& e : enumerators ) {
            if (e.name != "_") {// ignore unnamed values
                if (bitwise) {
                    if (e.name != "none") {
                        to_string += "    if (this & " + cpp2::to_string(e.name) + ") == " + cpp2::to_string(e.name) + " { _ret += _comma + \"" + cpp2::to_string(e.name) + "\"; _comma = \", \"; }\n";
                    }
                }
                else {
                    to_string += "    if this == " + cpp2::to_string(e.name) + " { return \"" + cpp2::to_string(e.name) + "\"; }\n";
                }
            }
        }

        if (bitwise) {
            to_string += "    return _ret+\")\";\n}\n";
        }
        else {
            to_string += "    return \"invalid " + cpp2::to_string(CPP2_UFCS(name)(t)) + " value\";\n}\n";
        }

        CPP2_UFCS(add_member)(t, std::move(to_string));
    }
}
#line 1120 "cpp2reflect.h2"
}

#line 1132 "cpp2reflect.h2"
auto cpp2_enum(meta::type_declaration& t) -> void
{
    //  Let basic_enum do its thing, with an incrementing value generator
    CPP2_UFCS(basic_enum)(t, 
        [](std::string& value, cpp2::in<std::string> specified_value) mutable -> void{
            if (!(CPP2_UFCS(empty)(specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS(value, 0), nullptr, 10)}; 
                value = cpp2::as_<std::string>((std::move(v) + 1));
            }
        }, 
        false   // disable bitwise operations
    );
}

#line 1159 "cpp2reflect.h2"
auto flag_enum(meta::type_declaration& t) -> void
{
    //  Let basic_enum do its thing, with a power-of-two value generator
    CPP2_UFCS(basic_enum)(t, 
        [](std::string& value, cpp2::in<std::string> specified_value) mutable -> void{
            if (!(CPP2_UFCS(empty)(specified_value))) {
                value = specified_value;
            }else {
                auto v {std::strtoll(&CPP2_ASSERT_IN_BOUNDS(value, 0), nullptr, 10)}; 
                if (cpp2::cmp_less(v,1)) {
                    value = "1";
                }
                else {
                    value = cpp2::as_<std::string>((std::move(v) * 2));
                }
            }
        }, 
        true    // enable bitwise operations
    );
}

#line 1205 "cpp2reflect.h2"
auto cpp2_union(meta::type_declaration& t) -> void
{
    std::vector<value_member_info> alternatives {}; 
{
auto value = 0;

    //  1. Gather: All the user-written members, and find/compute the max size

#line 1212 "cpp2reflect.h2"
    for ( 

           auto const& m : CPP2_UFCS(get_members)(t) )  { do 
    if (   CPP2_UFCS(is_member_object)(m)) 
    {
        CPP2_UFCS(require)(m, CPP2_UFCS(is_public)(m) || CPP2_UFCS(is_default_access)(m), 
                   "a union alternative cannot be protected or private");

        CPP2_UFCS(require)(m, !(CPP2_UFCS(starts_with)(CPP2_UFCS(name)(m), "is_")) 
                   && !(CPP2_UFCS(starts_with)(CPP2_UFCS(name)(m), "set_")), 
                   "a union alternative's name cannot start with 'is_' or 'set_' - that could cause user confusion with the 'is_alternative' and 'set_alternative' generated functions");

        auto mo {CPP2_UFCS(as_object)(m)}; 
        CPP2_UFCS(require)(mo, CPP2_UFCS(empty)(CPP2_UFCS(initializer)(mo)), 
                    "a union alternative cannot have an initializer");

        //  Adding local variable 'e' to work around a Clang warning
        value_member_info e {cpp2::as_<std::string>(CPP2_UFCS(name)(mo)), CPP2_UFCS(type)(mo), cpp2::as_<std::string>(value)}; 
        CPP2_UFCS(push_back)(alternatives, e);

        CPP2_UFCS(mark_for_removal_from_enclosing_type)(mo);
    } while (false); ++value; }
}

#line 1235 "cpp2reflect.h2"
    std::string discriminator_type {}; 
    if (cpp2::cmp_less(CPP2_UFCS(ssize)(alternatives),std::numeric_limits<cpp2::i8>::max())) {
        discriminator_type = "i8";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS(ssize)(alternatives),std::numeric_limits<cpp2::i16>::max())) {
        discriminator_type = "i16";
    }
    else {if (cpp2::cmp_less(CPP2_UFCS(ssize)(alternatives),std::numeric_limits<cpp2::i32>::max())) {
        discriminator_type = "i32";
    }
    else {
        discriminator_type = "i64";
    }}}

#line 1250 "cpp2reflect.h2"
    //  2. Replace: Erase the contents and replace with modified contents

    CPP2_UFCS(remove_marked_members)(t);
{
std::string storage = "    _storage: cpp2::aligned_storage<cpp2::max( ";

    //  Provide storage

#line 1256 "cpp2reflect.h2"
    {
{
std::string comma = "";

#line 1258 "cpp2reflect.h2"
        for ( 

              auto const& e : alternatives )  { do {
            storage += comma + "sizeof(" + cpp2::to_string(e.type) + ")";
        } while (false); comma = ", "; }
}

#line 1264 "cpp2reflect.h2"
        storage += "), cpp2::max( ";
{
std::string comma = "";

#line 1267 "cpp2reflect.h2"
        for ( 

              auto const& e : alternatives )  { do {
            storage += comma + "alignof(" + cpp2::to_string(e.type) + ")";
        } while (false); comma = ", "; }
}

#line 1273 "cpp2reflect.h2"
        storage += " )> = ();\n";
        CPP2_UFCS(add_member)(t, std::move(storage));
    }
}

    //  Provide discriminator
#line 1278 "cpp2reflect.h2"
    CPP2_UFCS(add_member)(t, "    _discriminator: " + cpp2::to_string(std::move(discriminator_type)) + " = -1;\n");

    //  Add the alternatives: is_alternative, get_alternative, and set_alternative
    for ( 
         auto const& a : alternatives ) 
    {
        CPP2_UFCS(add_member)(t, "    is_" + cpp2::to_string(a.name) + ": (this) -> bool = _discriminator == " + cpp2::to_string(a.value) + ";\n");

        CPP2_UFCS(add_member)(t, "    " + cpp2::to_string(a.name) + ": (this) -> forward " + cpp2::to_string(a.type) + " pre(is_" + cpp2::to_string(a.name) + "()) = reinterpret_cast<* const " + cpp2::to_string(a.type) + ">(_storage&)*;\n");

        CPP2_UFCS(add_member)(t, "    " + cpp2::to_string(a.name) + ": (inout this) -> forward " + cpp2::to_string(a.type) + " pre(is_" + cpp2::to_string(a.name) + "()) = reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)*;\n");

        CPP2_UFCS(add_member)(t, "    set_" + cpp2::to_string(a.name) + ": (inout this, _value: " + cpp2::to_string(a.type) + ") = { if !is_" + cpp2::to_string(a.name) + "() { _destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&), _value); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)* = _value; } _discriminator = " + cpp2::to_string(a.value) + "; }\n");

        CPP2_UFCS(add_member)(t, "    set_" + cpp2::to_string(a.name) + ": (inout this, forward _args...: _) = { if !is_" + cpp2::to_string(a.name) + "() { _destroy(); std::construct_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&), _args...); } else { reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&)* = :" + cpp2::to_string(a.type) + " = (_args...); } _discriminator = " + cpp2::to_string(a.value) + "; }\n");
    }
{
std::string destroy = "    private _destroy: (inout this) = {\n";

    //  Add destroy

#line 1297 "cpp2reflect.h2"
    {
        for ( 
              auto const& a : alternatives ) {
            destroy += "        if _discriminator == " + cpp2::to_string(a.value) + " { std::destroy_at( reinterpret_cast<*" + cpp2::to_string(a.type) + ">(_storage&) ); }\n";
        }

        destroy += "        _discriminator = -1;\n";
        destroy += "    }\n";
        CPP2_UFCS(add_member)(t, std::move(destroy));
    }
}

    //  Add the destructor
#line 1309 "cpp2reflect.h2"
    CPP2_UFCS(add_member)(t, "    operator=: (move this) = { _destroy(); }");

    //  Add default constructor
    CPP2_UFCS(add_member)(t, "    operator=: (out this) = { }");
{
std::string value_set = "";

    //  Add copy/move construction and assignment

#line 1316 "cpp2reflect.h2"
    {
        for ( 
              auto const& a : alternatives ) {
            value_set += "        if that.is_" + cpp2::to_string(a.name) + "() { set_" + cpp2::to_string(a.name) + "( that." + cpp2::to_string(a.name) + "() ); }\n";
        }
        value_set += "    }\n";

        CPP2_UFCS(add_member)(t, std::string("    operator=: (out this, that) = {\n") 
                    + "        _storage = ();\n" 
                    + "        _discriminator = -1;\n" 
                    + value_set
                    );
        CPP2_UFCS(add_member)(t, std::string("    operator=: (inout this, that) = {\n") 
                    + "        _storage = _;\n" 
                    + "        _discriminator = _;\n" 
                    + std::move(value_set)
                    );
    }
}
#line 1334 "cpp2reflect.h2"
}

#line 1341 "cpp2reflect.h2"
auto print(cpp2::in<meta::type_declaration> t) -> void
{
    std::cout << CPP2_UFCS(print)(t) << "\n";
}

#line 1347 "cpp2reflect.h2"
}

}

#endif
