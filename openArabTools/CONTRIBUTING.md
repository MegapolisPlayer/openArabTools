# Contributor guidelines

- Be respectful
- Assign yourself to issues which you want to solve.
- If someone is already solving an issue, do not solve it as well.
- Follow the naming style: class names **CapitalCase/PascalCase**, (member) functions with **camelCase** (same naming as ArabTools)
- Local variables follow **CapitalCase/PascalCase**
- Non-public member variables prefixed with `m`, e.g. `mMember1` or `mMember2`
- Parameters to functions prefixed with `a`, e.g. `void MyObject.myFunc(S32 aParameter, U32 aParameter2)`
- Static **variables** are prefixed with `s`, e.g. `static U64 sVar = 42;`
- Constants/readonly variables use `c`
- Pointers use `p`, pointers to pointers use `pp` and so on
- Raw arrays use `r` instead of `p`. A pointer to a raw array is `prPtrToArray` and a 2D raw array is `rr2DArray`
- Altough a type already covers this, still use the prefix if it works in the same way (e.g. `std::unique_ptr pStillAPtr` but `std::vector<int> NoPrefixHere`)
- Prefixes are **always** lowercase, variable uses **CapitalCase/PascalCase**
- Prefixes are ordered alphabetically, e.g. from code `appBuffer` (parameter to function, pointer to pointer)
- Use `constexpr` whenever possible 
- Avoid using basic types if OpenArabTools already provides a `typedef` for it. Typedefs are contained in the `StandardInclude.hpp` file.
- Avoid using exceptions: use the `Error::` functions for it.
- Always add `[[noreturn]], const, noexcept` or other specifiers if possible.
- Braces for functions and classes are **on the same line as the function declaration**.
- Speak (or, more like write) **public** posts only in English. Sure, 99% of contributors are probably from Czechia but using an international language makes the project more accessible.
- Any issues, disputes will be resolved via the administrator(s) of the project. (MegapolisPlayer)