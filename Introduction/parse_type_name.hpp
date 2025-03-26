#pragma once
#include "Examples/PreetyPrint/PrintDamage.hpp"
#include "Examples/demangle_type_name.hpp"

#include "Usage/With.hpp"  // for some includes to Scheme, traits and types

template <typename T>
auto type_name_result(std::string text = name<T>()) {
    struct Data {
        std::string type;
        std::string num;
        std::string tokens;
    };

    struct Result {
        std::string base;
        std::vector<Data> properties;
    } result;

    std::string what = name<std::string>();
    std::string into = "std::string";
    for (
        auto target = text.find(what);
        target != std::string::npos;
        target = text.find(what)) {
        text.replace(target, what.size(), into);
    }

    text.erase(std::remove(text.begin(), text.end(), ' '), text.end());

    auto find_and_replace = [](auto& text, const auto& what, const auto& into) {
        if (what == into) {
            return;
        }
        for (size_t target = text.find(what); target != std::string::npos; target = text.find(what)) {
            text.replace(target, what.size(), into);
        }
    };

    using base_type = typename helpers::Scheme<T>::base;
    std::string base_name = name<base_type>();

    what = base_name;
    into = "Base";
    find_and_replace(text, what, into);

    into = "\n";
    what = ",impl::UserProperty_<";
    find_and_replace(text, what, into);

    what = "impl::UserProperty_<";
    find_and_replace(text, what, into);

    into = "\nimpl::";
    what = ",impl::";
    find_and_replace(text, what, into);

    what = "impl::";  // replace pattern "impl::****_<" with "\nimpl::****_\n" or remove "impl::"
    for (size_t target = text.find(what); target != std::string::npos; target = text.find(what)) {
        std::string ender = "_<";
        auto target_end = text.find(ender, target);

        if (target_end != std::string::npos) {
            auto pattern_size = (target_end - target) + ender.size();
            auto pattern = text.substr(target, pattern_size - 1);  // pattern "impl::****_"

            for (std::string illegal_char : {"<", ">", ","}) {  // end of pattern goes too far
                if (pattern.contains(illegal_char)) {
                    text.replace(target, what.size(), "");
                    continue;
                }
            }
            text.replace(target, pattern_size, "\n" + pattern + "\n");
        } else {
            text.replace(target, what.size(), "");
        }
    }

    if (auto target = text.find_last_of("<", text.find("Base") - 1); target != std::string::npos) {
        size_t limit = text.find_last_of("<", text.find("Base") - 1);
        // text.replace(limit, 1, into);

        for (target = text.find(",");
             (target != std::string::npos) and target < limit;) {
            text.replace(target, 1, into);
            target = text.find(",");
        }
        for (target = text.find("<");
             (target != std::string::npos) and target < limit;) {
            text.erase(target, 1);
            target = text.find("<");
        }
    }

    for (std::string what : {",Base,", "<Base,"}) {
        if (auto target = text.find(what); target != std::string::npos) {
            text.replace(target, what.size(), "\nBase,");
        }
    }
    for (std::string what : {"<Base>", ",Base>", "Base>"}) {
        if (auto target = text.find(what); target != std::string::npos) {
            text.replace(target, what.size(), "\nBase,[]>");  // mark last properties without tags with [_]
        }
    }

    what = ">>";
    into = ">,[]>";
    find_and_replace(text, what, into);

    what = "\n\n";
    into = "\n";
    find_and_replace(text, what, into);

    for (size_t start = 0, index = 0, target = text.find("\n", start); target != std::string::npos; target = text.find("\n", start)) {
        auto target_end = text.find("\n", target + 1);
        if (target_end != std::string::npos) {
            auto name = text.substr(target + 1, target_end - target - 1);
            if (auto e = name.find("<"); e != std::string::npos) {
                name.replace(e, 1, "");
            }
            auto pos = std::to_string(index++);
            result.properties.emplace_back(
                name,
                pos);
        }
        start = target + 1;
    }

    {  // *
        auto target = text.find("\nBase");
        auto it = text.begin();
        std::advance(it, target);
        text.erase(text.begin(), it);
    }

    into = "-> Base";  // tag base type
    std::string token_text;
    if (text.size() < 6) {
        text = into;
    } else {
        for (std::string what : {"Base>,", "Base>", "Base,"}) {
            if (auto target = text.find(what); target != std::string::npos) {
                text.replace(target, what.size(), into);

                size_t after_base = target + into.size();
                token_text = "Tokens: [" + text.substr(after_base);
                text = text.substr(0, after_base);
            }
        }
    }

    what = ">>";
    into = ">,[]>";
    find_and_replace(token_text, what, into);

    what = "[]";
    into = "[";
    find_and_replace(token_text, what, into);

    what = ">,";
    into = "], [";
    find_and_replace(token_text, what, into);

    what = ">";
    into = "]";
    find_and_replace(token_text, what, into);

    what = "[[";
    into = "[";
    find_and_replace(token_text, what, into);

    for (
        size_t index = result.properties.size(),
               offset = 0,
               start = token_text.find("[", offset),
               finish = token_text.find("]", offset);
        (start != std::string::npos) and (finish != std::string::npos);
        start = token_text.find("[", offset),
               finish = token_text.find("]", offset)) {
        auto token = token_text.substr(start + 1, finish - start - 1);

        if (index == 0) {
            throw std::range_error("missed token.");
            break;
        }
        if (token.empty()) {
            result.properties[index - 1].tokens = "_";  // * mark empty token list
        } else {
            result.properties[index - 1].tokens = token;
        }
        index--;
        offset = finish + 1;
    }

    result.base = text;
    result.base += " == " + base_name + '\n';
    if constexpr (trait<Name>::accessable<base_type>)
        result.base += "  : Name\n";
    if constexpr (trait<CureHealth>::accessable<base_type>)
        result.base += "  : CureHealth\n";
    if constexpr (trait<Protection>::accessable<base_type>)
        result.base += "  : Protection\n";
    if constexpr (trait<Damage>::accessable<base_type>)
        result.base += "  : Damage\n";
    if constexpr (trait<EffectContainer>::accessable<base_type>)
        result.base += "  : EffectContainer\n";
    if constexpr (trait<WearContainer>::accessable<base_type>)
        result.base += "  : WearContainer\n";
    if constexpr (trait<Health>::accessable<base_type>)
        result.base += "  : Health\n";
    if constexpr (trait<int>::accessable<base_type>)
        result.base += "  : int\n";
    if constexpr (requires { typename base_type::base_type; })
        if constexpr (trait<int>::accessable<typename base_type::base_type>)
            result.base += "  : : int\n";

    return result;
};

template <typename T>
auto parse_type_name() {
    std::string result;
    auto data = type_name_result<T>();
    for (auto [type, pos, tokens] : data.properties) {
        result += '\n' + pos + " : " + type + " : " + tokens;
    }
    result += data.base;
    return result;
}
