#include "ft_infinite_energy.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_infinite_energy::on_enable()
{
	// This method also works but I discovered a new and better method
	// Globals::g_pProcess->nop_bytes( Offsets::infinite_energy, 4 );

	// Second method for infinite energy
	// If I'm correct with this approach, the energy shouldn't ever get below the maximum (100).
	// I'm changing a vsubss instruction to vaddss, which will result later always in the maximum (100) to be written into the energy variable in memory
	// Also this will regenerate the energy automatically until it reaches it's maximum, while the old method won't do that for you.
	// C4 C1 7A 5C C8 - vsubss xmm1, xmm0, xmm8  <=== original instruction
	// C4 C1 7A 58 C8 - vaddss xmm1, xmm0, xmm8  <=== modified instruction
	// one byte patches rulezzzzzzz
	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::infinite_energy2 + 3, 0x58 );
}

void ft_infinite_energy::on_disable()
{
	// Globals::g_pProcess->write_to_protected_memory< uint32_t >( Offsets::infinite_energy, 0x0311FAC5 );

	Globals::g_pProcess->write_to_protected_memory< uint8_t >( Offsets::infinite_energy2 + 3, 0x5C );
}
