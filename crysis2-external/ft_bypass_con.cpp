#include "ft_bypass_con.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_bypass_con::on_first_activation()
{
	this->m_address = Globals::g_pProcess->read< uint32_t >( Offsets::bypass_conrestriction + 2 );
}

void ft_bypass_con::on_enable()
{
	Globals::g_pProcess->nop_bytes( Offsets::bypass_conrestriction, 6 );
}

void ft_bypass_con::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::bypass_conrestriction, 0x850F );
	Globals::g_pProcess->write_to_protected_memory< uint32_t >( Offsets::bypass_conrestriction + 2, this->m_address );
}
