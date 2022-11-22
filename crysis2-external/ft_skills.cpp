#include "ft_skills.hpp"
#include "globals.hpp"
#include "offsets.hpp"
#include "structs.hpp"

void ft_skills::on_enable()
{
	const auto game = Globals::g_pProcess->read< uint64_t >( Offsets::cgame );

	if( !game )
		return;

	auto array_ptr = Globals::g_pProcess->read< uint32_t >( game + 0x2B8 );

	if( !array_ptr )
		return;

	// jump to the first element of the array
	array_ptr += 0x40;

	for( auto i = 0; i < 12; i++ )
	{
		// set m_bUnlocked true
		Globals::g_pProcess->write< bool >( array_ptr + i * sizeof( Perk ) + 0x50, true );

		// set m_bUsable true
		Globals::g_pProcess->write< bool >( array_ptr + i * sizeof( Perk ) + 0x51, true );
	}

	printf( "[#] All Perks unlocked!\n" );

	this->disable();
}

void ft_skills::on_disable() {}
