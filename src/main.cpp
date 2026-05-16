#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp> // Includes the main menu files

using namespace geode::prelude;

// This "$modify" tells Geode you are changing the Main Menu
class $modify(MenuLayer) {
    
    bool init() {
        // 1. Run the game's normal code first
        if (!MenuLayer::init()) return false;

        // 2. PUT YOUR CUSTOM C++ CODE HERE!
        log::info("This message prints when the menu loads!");

        return true;
    }
};
