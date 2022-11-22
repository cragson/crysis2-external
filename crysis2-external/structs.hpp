#pragma once

class Perk
{
public:
	char pad_0000[ 16 ]; //0x0000
	char m_szSlot[ 8 ]; //0x0010
	char pad_0018[ 32 ]; //0x0018
	char m_szPerk[ 8 ]; //0x0038
	char pad_0040[ 16 ]; //0x0040
	bool m_bUnlocked; //0x0050
	bool m_bUsable; //0x0051
	char pad_0052[ 22 ]; //0x0052
}; //Size: 0x0068
