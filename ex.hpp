#ifndef HEADER_EX_DEFINED
#define HEADER_EX_DEFINED


#define self (*this)
#define repeat(n) for(decay_t<decltype(n)> __repeat_i = 0, __repeat_end = n; __repeat_i < __repeat_end; ++__repeat_i)
#define unused_arg(a) (void)(a)
#define packname(name) {#name, name}


using codepoint_t = unsigned int;


#endif // HEADER_EX_DEFINED