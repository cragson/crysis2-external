#include "ft_infinite_ammo.hpp"

#include "globals.hpp"
#include "offsets.hpp"

void ft_infinite_ammo::on_enable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::infinite_ammo, 0x40FF );
}

void ft_infinite_ammo::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint16_t >( Offsets::infinite_ammo, 0x5889 );
}
