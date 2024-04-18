#pragma once
#include "../../defs/all.h"

class CreditsLayer : public Popup<std::string const&> {
protected:
    bool setup(std::string const& value) override;
public:
    static CreditsLayer* create(std::string const& title);
};