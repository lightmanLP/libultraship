#include "ship/window/MouseCaptureManager.h"

#include "ship/Context.h"
#include "ship/window/Window.h"

// FIXME: fast3d gettargetfps
#include "fast/Fast3dWindow.h"

namespace Ship {
MouseCaptureManager::MouseCaptureManager() {}

MouseCaptureManager::~MouseCaptureManager() {}

void MouseCaptureManager::StartFrame() {
    CursorTimeoutTick();
}

void MouseCaptureManager::CursorTimeoutTick() {
    static Ship::Coords mPrevMousePos;

    auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(Context::GetInstance()->GetWindow());
    if (ShouldForceCursorVisibility() || wnd->IsMouseCaptured()) {
        return;
    }

    Ship::Coords mousePos = wnd->GetMousePos();
    bool mouseMoved = abs(mousePos.x - mPrevMousePos.x) > 0 || abs(mousePos.y - mPrevMousePos.y) > 0;
    mPrevMousePos = mousePos;

    if (mouseMoved) {
        wnd->SetCursorVisibility(true);
        mCursorVisibleTicks = mCursorVisibleSeconds * wnd->GetTargetFps();
        return;
    }

    if (mCursorVisibleTicks == 0) {
        wnd->SetCursorVisibility(false);
        mCursorVisibleTicks = -1;
        return;
    }

    if (mCursorVisibleTicks > 0) {
        mCursorVisibleTicks--;
    }
}

bool MouseCaptureManager::ShouldAutoCaptureMouse() {
    return mAutoCaptureMouse;
}

void MouseCaptureManager::SetAutoCaptureMouse(bool capture) {
    mAutoCaptureMouse = capture;
}

bool MouseCaptureManager::ShouldForceCursorVisibility() {
    return mForceCursorVisibility;
}

void MouseCaptureManager::SetForceCursorVisibility(bool visible) {
    mForceCursorVisibility = visible;
}

void MouseCaptureManager::SetCursorVisibilityTime(int32_t seconds) {
    mCursorVisibleSeconds = seconds;
}

void MouseCaptureManager::ToggleMouseCaptureOverride() {
    const std::shared_ptr<Window> window = Context::GetInstance()->GetWindow();
    window->SetMouseCapture(!window->IsMouseCaptured());
}

void MouseCaptureManager::UpdateMouseCapture() {
    const std::shared_ptr<Window> window = Context::GetInstance()->GetWindow();
    if (!window->GetGui()->GetMenuOrMenubarVisible()) {
        window->SetMouseCapture(ShouldAutoCaptureMouse());
    } else {
        window->SetMouseCapture(false);
        // TODO: remove?
        // window->SetCursorVisibility(true);
        auto wnd = std::dynamic_pointer_cast<Fast::Fast3dWindow>(window);
        mCursorVisibleTicks = mCursorVisibleSeconds * wnd->GetTargetFps();
    }
}
} // namespace Ship
