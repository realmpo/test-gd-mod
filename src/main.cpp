/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */


// Define a custom popup layer class
class MyCustomPopup : public FLAlertLayer {
protected:
    bool init() {
        // Initialize with default alert styling parameters
        if (!FLAlertLayer::init(nullptr, "Custom Menu", "", "Close", nullptr, 300.f, false, 150.f, 1.f)) {
            return false;
        }

        // 1. Find the main layer layout template container
        auto layer = cocos2d::CCLayer::create();
        this->addChild(layer);

        // 2. Create a label/text description for inside your box
        auto label = cocos2d::CCLabelBMFont::create("Click the special button below:", "bigFont.fnt");
        label->setPosition({285, 180});
        label->setScale(0.5f);
        layer->addChild(label);

        // 3. Create a custom button sprite using an in-game asset name
        auto goldButtonSprite = ButtonSprite::create("Click Me!", "goldFont.fnt", "GJ_button_01.png");
        
        // 4. Bind the sprite to a clickable menu item action function
        auto customButton = CCMenuItemSpriteExtra::create(
            goldButtonSprite,
            this,
            menu_selector(MyCustomPopup::onCustomButtonClick)
        );

        // 5. Create a layout menu frame to hold your interactive controls
        auto menu = cocos2d::CCMenu::create();
        menu->addChild(customButton);
        menu->setPosition({285, 140}); // Adjust coordinates to center the button in the window
        layer->addChild(menu);

        return true;
    }

    // This runs when your new custom button is clicked!
    void onCustomButtonClick(cocos2d::CCObject* sender) {
        // Create an interior confirmation alert
        FLAlertLayer::create("Success!", "You clicked the custom button!", "Nice")->show();
    }

public:
    // Helper helper constructor method
    static MyCustomPopup* create() {
        auto ret = new MyCustomPopup();
        if (ret && ret->init()) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/
		log::debug("Hello from my MenuLayer::init hook! This layer has {} children.", this->getChildrenCount());

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png"),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/
		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
	void onMyButton(CCObject* sender) {
    // Create and show your newly constructed custom multi-button popup window!
    auto popup = MyCustomPopup::create();
    if (popup) {
      popup->show();
    }
    }
};