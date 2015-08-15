// Copyright 2013-present Facebook. All Rights Reserved.

#include <pbxproj/XC/TestAction.h>

using pbxproj::XC::TestAction;

TestAction::TestAction() :
    _shouldUseLaunchSchemeArgsEnv(false)
{
}

bool TestAction::
parse(plist::Dictionary const *dict)
{
    if (!Action::parse(dict))
        return false;

    auto SDI    = dict->value <plist::String> ("selectedDebuggerIdentifier");
    auto SLI    = dict->value <plist::String> ("selectedLauncherIdentifier");
    auto SULSAE = dict->value <plist::Boolean> ("shouldUseLaunchSchemeArgsEnv");
    auto TRs    = dict->value <plist::Dictionary> ("Testables");
    auto ME     = dict->value <plist::Dictionary> ("MacroExpansion");

    if (SDI != nullptr) {
        _selectedDebuggerIdentifier = SDI->value();
    }

    if (SLI != nullptr) {
        _selectedLauncherIdentifier = SLI->value();
    }

    if (SULSAE != nullptr) {
        _shouldUseLaunchSchemeArgsEnv = SULSAE->value();
    }

    if (TRs != nullptr) {
        if (auto TRd = TRs->value <plist::Dictionary> ("TestableReference")) {
            auto TR = std::make_shared <TestableReference> ();
            if (!TR->parse(TRd))
                return false;

            _testables.push_back(TR);
        } else if (auto TRa = TRs->value <plist::Array> ("TestableReference")) {
            for (size_t n = 0; n < TRa->count(); n++) {
                auto TRd = TRa->value <plist::Dictionary> (n);
                if (TRd == nullptr)
                    continue;

                auto TR = std::make_shared <TestableReference> ();
                if (!TR->parse(TRd))
                    return false;

                _testables.push_back(TR);
            }
        }
    }

    if (ME != nullptr) {
        auto BR = ME->value <plist::Dictionary> ("BuildableReference");
        if (BR != nullptr) {
            _macroExpansion = std::make_shared <BuildableReference> ();
            if (!_macroExpansion->parse(BR))
                return false;
        }
    }

    return true;
}