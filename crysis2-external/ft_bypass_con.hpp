#pragma once
#include "osmium/Cheat/Feature/feature.hpp"

class ft_bypass_con : public feature
{
public:
	void on_first_activation() override;
	void on_enable() override;
	void on_disable() override;

	void on_render() override {}

	void tick() override {}

private:
	uint32_t m_address;
};
