#include "ft_infinite_energy.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_infinite_energy::on_enable()
{
	Globals::g_pProcess->nop_bytes(Offsets::infinite_energy, 4);
}

void ft_infinite_energy::on_disable()
{
	Globals::g_pProcess->write_to_protected_memory< uint32_t >(Offsets::infinite_energy, 0x0311FAC5);
}
