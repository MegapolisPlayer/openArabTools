# Contributor guidelines

- Be respectful
- Assign yourself to issues which you want to solve.
- If someone is already solving an issue, do not solve it as well.
- Follow the coding style: class names CapitalCase/PascalCase, methods with camelCase (same naming as ArabTools)
- Member variables prefixed with `m`, e.g. `mMember1` or `mMember2`
- Local variables follow CapitalCase/PascalCase
- Parameters to functions prefixed with `a`, e.g. `void MyObject.myFunc(S32 aParameter, U32 aParameter2)`
- Avoid using basic types if OpenArabTools already provides a `typedef` for it. Typedefs are contained in the `StandardInclude.hpp` file.
- Avoid using exceptions: use the `Error::` functions for it.
- Always add `[[noreturn]], const, noexcept` or other specifiers if possible.
- Speak (or, more like write) **public** posts only in English. Sure, 99% of contributors are probably from Czechia but using an international language makes the project more accessible.
- Any issues, disputes will be resolved via the administrator(s) of the project. (MegapolisPlayer)