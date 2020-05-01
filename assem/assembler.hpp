#ifndef HEADER_ASSEM_ASSEMBLER_DEFINED
#define HEADER_ASSEM_ASSEMBLER_DEFINED


#include "../libs.hpp"
#include "../nodes.hpp"


namespace assem
{
	class assembler
	{
	protected:
		any_node* root;
		
		//
		
	public:
		assembler();
	};
}


#else // HEADER_ASM_ASSEMBLER_DEFINED


namespace assem
{
	class assembler;
}


#endif // HEADER_ASM_ASSEMBLER_DEFINED