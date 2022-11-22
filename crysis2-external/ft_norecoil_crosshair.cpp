#include "ft_norecoil_crosshair.hpp"
#include "globals.hpp"
#include "offsets.hpp"

void ft_norecoil_crosshair::on_enable()
{
	Globals::g_pProcess->nop_bytes( Offsets::norecoil_crosshair, 5 );
}

void ft_norecoil_crosshair::on_disable()
{
	Globals::g_pProcess->write< uint32_t >( Offsets::norecoil_crosshair, 0x4859E2C5 );
	Globals::g_pProcess->write< uint8_t >( Offsets::norecoil_crosshair + 4, 0x68 );
}
