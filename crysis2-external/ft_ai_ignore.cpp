#include "ft_ai_ignore.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_ai_ignore::on_enable()
{
	Globals::g_pProcess->nop_bytes( Offsets::ai_ignore, 2 );
}

void ft_ai_ignore::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::ai_ignore, 0x0774 );
}
