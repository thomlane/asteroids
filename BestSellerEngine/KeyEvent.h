#pragma once
class KeyEvent :
    public Event
{
public:
    KeyEvent(std::string name, int keyCode,bool pressed, bool repeated) 
        : Event(name), keyCode(keyCode), pressed(pressed), repeated(repeated) {}

    inline int GetKeyCode() const { return keyCode; }
    inline bool Pressed() const { return pressed; }
    inline bool Released() const { return !pressed; }
    inline bool Repeated() const { return repeated; }
private:
    int keyCode;
    bool pressed;   // If this is a key press or release event
    bool repeated;  // If this key was also pressed
};

