#ifndef HEADER_EX_DEFINED
#define HEADER_EX_DEFINED


#define self (*this)
#define with(init) if(init;true)
#define repeat(n) for(decltype(n) __repeat_i = decltype(n)(0);__repeat_i<n;++__repeat_i)


#endif // HEADER_EX_DEFINED