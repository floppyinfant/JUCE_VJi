//
// Created by thorsten on 28.10.2025.
//

#include "UIController.h"

UIController::UIController(PluginAudioProcessor& p)
    : processor(p), editor(*p.getActiveEditor())
{
    setWantsKeyboardFocus(true);
    // addKeyListener(this);  // every Component is already a KeyListener ? ...
    // ... and you can't set it in it's own constructor: must be set in parent class after the component is fully visible or trigger a AsyncUpdate Event.
    // https://forum.juce.com/t/keypress-event/27415/7
    // https://forum.juce.com/t/detecting-a-keypress/16441/2

    //setSize(100, 100);
}

UIController::~UIController() {
}

// -----------------------------------------------------------------------

void UIController::paint(juce::Graphics &g) {
    juce::ignoreUnused(g);
}

void UIController::resized() {

}

// -----------------------------------------------------------------------

/**
 * juce::MouseListener
 * https://docs.juce.com/master/classjuce_1_1MouseEvent.html
 * https://docs.juce.com/master/classjuce_1_1ModifierKeys.html (LMB, RMB)
 * https://docs.juce.com/master/structjuce_1_1MouseWheelDetails.html
 * https://docs.juce.com/master/classjuce_1_1MouseInputSource.html  (Muti-Touch)
*/
void UIController::mouseEnter(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseExit(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseMove(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseDown(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseUp(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseDrag(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseDoubleClick(const MouseEvent &event) {
    juce::ignoreUnused(event);
}

void UIController::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    juce::ignoreUnused(event, wheel);
}

void UIController::mouseMagnify(const MouseEvent &event, float scaleFactor) {
    juce::ignoreUnused(event, scaleFactor);
}

// -----------------------------------------------------------------------

/**
 * juce::KeyListener
 * Component needs KeyboardFocus to receive KeyPressed Events:
 * Component::setWantsKeyboardFocus (true)
 * Component::grabKeyboardFocus()  // programmatically give the focus to a component
 * handleAsyncUpdate()
 */
bool UIController::keyPressed(const KeyPress &key) {

    DBG(String(key.getKeyCode()) + ", " + key.getTextCharacter());

    if (key == KeyPress::escapeKey) {

    } else if (key == KeyPress::tabKey) {

    } else if (key == KeyPress::spaceKey) {

    } else if (key == KeyPress(KeyPress::spaceKey, ModifierKeys::ctrlModifier, 0)) {

    } else if (key == KeyPress::returnKey) {

    } else if (key == KeyPress(KeyPress::returnKey, ModifierKeys::ctrlModifier, 0)) {

    } else if (key == KeyPress::backspaceKey) {

    } else if (key == KeyPress::deleteKey) {

    } else if (key == KeyPress::leftKey) {

    } else if (key == KeyPress::rightKey) {

    } else if (key == KeyPress::upKey) {

    } else if (key == KeyPress::downKey) {

    } else if (key == KeyPress::homeKey) {

    } else if (key == KeyPress::endKey) {

    } else if (key == KeyPress::pageUpKey) {

    } else if (key == KeyPress::pageDownKey) {

    } else if (key == KeyPress::F1Key) {

    } else if (key == KeyPress::F11Key) {

    } else if (key == 'w') {
        // up
    } else if (key == 'a') {
        // left
    } else if (key == 's') {
        // down
    } else if (key == 'd') {
        //right
    } else if (key == 'e') {
        // Action Key
    } else if (key == KeyPress('c', ModifierKeys::ctrlModifier, 0)) {
        // copy
    } else if (key == KeyPress('v', ModifierKeys::ctrlModifier, 0)) {
        // paste
    } else if (key == KeyPress('x', ModifierKeys::ctrlModifier, 0)) {
        // cut
    }

    return true;
}

bool UIController::keyStateChanged(bool isKeyDown) {
    return Component::keyStateChanged(isKeyDown);
}

void UIController::modifierKeysChanged(const ModifierKeys &modifiers) {
    Component::modifierKeysChanged(modifiers);
}

// -----------------------------------------------------------------------

