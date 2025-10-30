//
// Created by thorsten on 28.10.2025.
//

#include "ViewController.h"

ViewController::ViewController(PluginAudioProcessor p)
    : processor(p), editor(*p.getActiveEditor())
{

    //setSize(100, 100);
}

ViewController::~ViewController() {
}

// -----------------------------------------------------------------------

void ViewController::paint(juce::Graphics &g) {
    Component::paint(g);
}

void ViewController::resized() {
    Component::resized();
}

// -----------------------------------------------------------------------

void ViewController::mouseEnter(const MouseEvent &event) {
    Component::mouseEnter(event);
}

void ViewController::mouseExit(const MouseEvent &event) {
    Component::mouseExit(event);
}

void ViewController::mouseMove(const MouseEvent &event) {
    Component::mouseMove(event);
}

void ViewController::mouseDown(const MouseEvent &event) {
    Component::mouseDown(event);
}

void ViewController::mouseUp(const MouseEvent &event) {
    Component::mouseUp(event);
}

void ViewController::mouseDrag(const MouseEvent &event) {
    Component::mouseDrag(event);
}

void ViewController::mouseDoubleClick(const MouseEvent &event) {
    Component::mouseDoubleClick(event);
}

void ViewController::mouseWheelMove(const MouseEvent &event, const MouseWheelDetails &wheel) {
    Component::mouseWheelMove(event, wheel);
}

void ViewController::mouseMagnify(const MouseEvent &event, float scaleFactor) {
    Component::mouseMagnify(event, scaleFactor);
}

// -----------------------------------------------------------------------

bool ViewController::keyPressed(const KeyPress &key) {
    return Component::keyPressed(key);
}

bool ViewController::keyStateChanged(bool isKeyDown) {
    return Component::keyStateChanged(isKeyDown);
}

void ViewController::modifierKeysChanged(const ModifierKeys &modifiers) {
    Component::modifierKeysChanged(modifiers);
}

// -----------------------------------------------------------------------

