#pragma once
#include <rttr/visitor.h>

#include <sol/sol.hpp>
class sol_visitor : public rttr::visitor
{
public:
    template<typename Derived>
    void iterate_base_classes()
    {
    }

    template<typename Derived, typename Base_Class, typename...Base_Classes>
    void iterate_base_classes()
    {
        //m_chai.add(chaiscript::base_class<Base_Class, Derived>());
        iterate_base_classes<Derived, Base_Classes...>();
    }

    /////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename...Base_Classes>
    void visit_type_begin(const type_info<T>& info)
    {
        using declaring_type_t = typename type_info<T>::declaring_type;
        //iterate_base_classes<declaring_type_t, Base_Classes...>();
    }

    /////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename...Ctor_Args>
    void visit_constructor(const constructor_info<T>& info)
    {
        using declaring_type_t = typename constructor_info<T>::declaring_type;
        m_chai.add(chaiscript::constructor<declaring_type_t(Ctor_Args...)>(), get_type_name<declaring_type_t>());
    }

    /////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void visit_global_method(const method_info<T>& info)
    {
        //m_chai.add(chaiscript::fun(info.function_ptr), info.method_item.get_name().to_string());
    }

    /////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void visit_method(const method_info<T>& info)
    {
        //m_chai.add(chaiscript::fun(info.function_ptr), info.method_item.get_name().to_string());
    }

    /////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void visit_property(const property_info<T>& info)
    {
       // m_chai.add(chaiscript::fun(info.property_accessor), info.property_item.get_name().to_string());
    }

    template<typename T>
    void visit_getter_setter_property(const property_getter_setter_info<T>& info)
    {
       // m_chai.add(chaiscript::fun(info.property_getter), std::string("get_") + info.property_item.get_name().to_string());
       // m_chai.add(chaiscript::fun(info.property_setter), std::string("set_") + info.property_item.get_name().to_string());
    }

    template<typename T>
    void visit_readonly_property(const property_info<T>& info)
    {
        //m_chai.add(chaiscript::fun(info.property_accessor), info.property_item.get_name().to_string());
    }

    /////////////////////////////////////////////////////////////////////////////////////

private:
    template<typename T>
    static std::string get_type_name()
    {
        return rttr::type::template get<T>().get_name().to_string();
    };

private:
    sol::state& state;

    RTTR_ENABLE(visitor) // Important!! Otherwise the object instance cannot be casted from "visitor" to "chai_script_binding_visitor"
};


RTTR_REGISTER_VISITOR(sol_visitor); // Important!!
// In order to make the visitor available during registration