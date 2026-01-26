#pragma once

#include <memory>

namespace Ship {
class MouseCaptureManager {
  public:
    MouseCaptureManager();
    virtual ~MouseCaptureManager();

    virtual void StartFrame();

    virtual bool ShouldAutoCaptureMouse();
    virtual void SetAutoCaptureMouse(bool capture);
    virtual bool ShouldForceCursorVisibility();
    virtual void SetForceCursorVisibility(bool visible);

    virtual void SetCursorVisibilityTime(int32_t seconds);

    virtual void ToggleMouseCaptureOverride();
    virtual void UpdateMouseCapture();

  protected:
    virtual void CursorTimeoutTick();

  // subsequent
  private:
    bool mAutoCaptureMouse = false;
    bool mForceCursorVisibility = false;

    uint32_t mCursorVisibleTicks = 180;
    uint32_t mCursorVisibleSeconds = 3;
};
} // namespace Ship
