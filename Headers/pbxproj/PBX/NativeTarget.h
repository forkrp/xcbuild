// Copyright 2013-present Facebook. All Rights Reserved.

#ifndef __pbxproj_PBX_NativeTarget_h
#define __pbxproj_PBX_NativeTarget_h

#include <pbxproj/PBX/Target.h>

namespace pbxproj { namespace PBX {

class NativeTarget : public Target {
public:
    typedef std::shared_ptr <NativeTarget> shared_ptr;

private:
    std::string                    _productType;
    PBX::FileReference::shared_ptr _productReference;
    PBX::BuildRule::vector         _buildRules;

public:
    NativeTarget();

public:
    inline std::string const &productType() const
    { return _productType; }

public:
    inline PBX::FileReference::shared_ptr const &productReference() const
    { return _productReference; }
    inline PBX::FileReference::shared_ptr &productReference()
    { return _productReference; }

public:
    inline BuildRule::vector const &buildRules() const
    { return _buildRules; }
    inline BuildRule::vector &buildRules()
    { return _buildRules; }

public:
    bool parse(Context &context, plist::Dictionary const *dict);

public:
    static inline char const *Isa()
    { return ISA::PBXNativeTarget; }
};

} }

#endif  // !__pbxproj_PBX_NativeTarget_h