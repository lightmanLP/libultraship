#pragma once

namespace Ship {
class BaseInputEditor {
  public:
    virtual bool IsMouseMappingBlocked() = 0;
};
} // namespace Ship
