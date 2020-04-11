#ifndef HEADER_EX_DEFINED
#define HEADER_EX_DEFINED


#define self (*this)
#define with(init) if(init;true)
#define repeat(n) for(decay_t<decltype(n)> __repeat_i = 0, __repeat_end = n; __repeat_i < __repeat_end; ++__repeat_i)
#define until(c) while(!(c))
#define unless(c) if(!(c))


#endif // HEADER_EX_DEFINED