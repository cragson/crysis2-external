#pragma once
#include "crysis_cheat.hpp"
#include "crysis_overlay.hpp"
#include "osmium/Memory/Process/process.hpp"


namespace Globals
{
	inline auto g_pCheat = std::make_unique< crysis_cheat >();

	inline auto g_pOverlay = std::make_unique< crysis_overlay >();

	inline auto g_pProcess = std::make_unique< process >();
}
