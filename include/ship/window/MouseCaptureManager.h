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

    virtual void ToggleMouseCaptureOverride();
    virtual void UpdateMouseCapture();

    void SetCursorVisibilityTime(uint32_t seconds);
    uint32_t GetCursorVisibilityTime();

  protected:
    void CursorTimeoutTick();
    void SetCursorVisibleTicks(uint32_t ticks);

  // subsequent
  private:
    bool mAutoCaptureMouse = false;
    bool mForceCursorVisibility = false;

    uint32_t mCursorVisibleTicks = 180;
    uint32_t mCursorVisibleSeconds = 3;
};
} // namespace Ship
