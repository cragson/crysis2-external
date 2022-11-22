#include "crysis_cheat.hpp"

#include "ft_ai_ignore.hpp"
#include "ft_bypass_con.hpp"
#include "ft_infinite_ammo.hpp"
#include "ft_infinite_energy.hpp"
#include "ft_norecoil_crosshair.hpp"
#include "ft_skills.hpp"
#include "globals.hpp"
#include "utils.hpp"
#include "offsets.hpp"

bool crysis_cheat::setup_features()
{
	auto bypass = std::make_unique< ft_bypass_con >();
	bypass->set_name( L"Bypass Console Restriction" );
	bypass->set_activation_delay( 420 );
	bypass->set_print_status( true );
	bypass->set_virtual_key_code( VK_NUMPAD0 );

	this->m_features.push_back( std::move( bypass ) );

	auto ammo = std::make_unique< ft_infinite_ammo >();
	ammo->set_name( L"Infinite Ammo" );
	ammo->set_activation_delay( 420 );
	ammo->set_print_status( true );
	ammo->set_virtual_key_code( VK_NUMPAD1 );

	this->m_features.push_back( std::move( ammo ) );

	auto energy = std::make_unique< ft_infinite_energy >();
	energy->set_name( L"Infinite Energy" );
	energy->set_activation_delay( 420 );
	energy->set_print_status( true );
	energy->set_virtual_key_code( VK_NUMPAD2 );

	this->m_features.push_back( std::move( energy ) );

	auto ignore = std::make_unique< ft_ai_ignore >();
	ignore->set_name( L"AI Ignore" );
	ignore->set_activation_delay( 420 );
	ignore->set_print_status( true );
	ignore->set_virtual_key_code( VK_NUMPAD3 );

	this->m_features.push_back( std::move( ignore ) );

	auto cross = std::make_unique< ft_norecoil_crosshair >();
	cross->set_name( L"Norecoil Crosshair" );
	cross->set_activation_delay( 420 );
	cross->set_print_status( true );
	cross->set_virtual_key_code( VK_NUMPAD4 );

	this->m_features.push_back( std::move( cross ) );

	auto skills = std::make_unique< ft_skills >();
	skills->set_name( L"Unlock All Perks" );
	skills->set_activation_delay( 420 );
	skills->set_print_status( false );
	skills->set_virtual_key_code( VK_NUMPAD5 );

	this->m_features.push_back( std::move( skills ) );

	return true;
}

bool crysis_cheat::setup_offsets()
{
	if( !Globals::g_pProcess->does_image_exist_in_map( L"Crysis2Remastered.exe" ) )
		return false;

	const auto game = Globals::g_pProcess->get_image_ptr_by_name( L"Crysis2Remastered.exe" );

	const auto ammo = game->find_pattern( L"89 58 08 B0 01 48 83", false );

	if( !ammo )
		return false;

	Offsets::infinite_ammo = ammo;

	const auto energy = game->find_pattern( L"C5 FA 11 03 48 8B 5C 24 70", false );

	if( !energy )
		return false;

	Offsets::infinite_energy = energy;

	const auto ignore = game->find_pattern( L"74 07 32 C0 E9 0E 01 00 00", false );

	if( !ignore )
		return false;

	Offsets::ai_ignore = ignore;

	const auto crosshair = game->find_pattern( L"C5 E2 59 48 68", false );

	if( !crosshair )
		return false;

	Offsets::norecoil_crosshair = crosshair;

	const auto conbypass = game->find_pattern( L"0F 85 4E 02 00 00 49", false );

	if( !conbypass )
		return false;

	Offsets::bypass_conrestriction = conbypass;

	const auto cg = game->find_pattern( L"48 8B 0D ? ? ? ? 41 8B F8 44 8B F2", false );

	if( !cg )
		return false;

	Offsets::cgame = game->deref_address< uint32_t >( cg + 3 ) + cg + 7;

	return true;
}

void crysis_cheat::print_features()
{
	printf( "\n" );

	printf( "Feature-Name -> Feature-Hotkey\n" );

	for( const auto& feature : this->m_features )
		printf(
			"[>] %-25ws -> %s\n",
			feature->get_name().c_str(),
			utils::virtual_key_as_string( feature->get_virtual_key_code() ).c_str()
		);

	printf( "\n" );
}

void crysis_cheat::print_offsets()
{
	printf( "\n" );

	const auto msg = []( const std::string& name, const std::uintptr_t value )
	{
		printf( "[>] %-35s -> 0x%llX\n", name.c_str(), value );
	};

	msg( "Infinite Ammo", Offsets::infinite_ammo );
	msg( "Infinite Energy", Offsets::infinite_energy );
	msg( "AI Ignore", Offsets::ai_ignore );
	msg( "Norecoil Crosshair", Offsets::norecoil_crosshair );
	msg( "Bypass Console Restriction", Offsets::bypass_conrestriction );
	msg( "CGame", Offsets::cgame );

	printf( "\n" );
}

void crysis_cheat::run()
{
	for( const auto& feature : this->m_features )
	{
		// before tick'ing the feature, check first if the state will eventually change
		if( GetAsyncKeyState( feature->get_virtual_key_code() ) & 0x8000 )
			feature->toggle();

		// let the feature tick() when active
		if( feature->is_active() )
			feature->tick();
	}
}

void crysis_cheat::shutdown()
{
	// disable every feature here
	for( const auto& feature : this->m_features )
		if( feature->is_active() )
			feature->disable();

	// clear image map here
	if( Globals::g_pProcess )
		Globals::g_pProcess->clear_image_map();
}
