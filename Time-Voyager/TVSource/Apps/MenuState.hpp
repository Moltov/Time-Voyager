/**
 * Provides the TicTacToe GameState example in the GQE library.
 *
 * @file example/tictactoe/src/GameState.cpp
 * @author Ryan Lindeman
 * @date 20110704 - Initial Release
 * @date 20120421 - Use arial.ttf font since SFML 2 crashes on exit when using default font
 * @date 20120512 - Use new RAII Asset style
 */

#ifndef   MENU_STATE_HPP_INCLUDED
#define   MENU_STATE_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <TVSource/Assets/FontAsset.hpp>
#include <TVSource/Assets/ImageAsset.hpp>
#include <TVSource/Interfaces/IState.hpp>
#include <TVSource/Core/Core_types.hpp>

/// Provides Menu state to manage gameplay
class MenuState : public GQE::IState
{
  public:
    /**
     * MenuState constructor
     * @param[in] theApp is an address to the App class.
     */
    MenuState(GQE::IApp& theApp);

    /**
     * GameState deconstructor
     */
    virtual ~MenuState(void);

    /**
     * DoInit is responsible for initializing this State
     */
    virtual void DoInit(void);

    /**
     * ReInit is responsible for Reseting this state when the
     * StateManager::ResetActiveState() method is called.  This way a Game
     * State can be restarted without unloading and reloading the game assets
     */
    virtual void ReInit(void);

    /**
     * HandleEvents is responsible for handling input events for this
     * State when it is the active State.
     * @param[in] theEvent to process from the App class Loop method
     */
    virtual void HandleEvents(sf::Event theEvent);

    /**
     * UpdateFixed is responsible for handling all State fixed update needs for
     * this State when it is the active State.
     */
    virtual void UpdateFixed(void);

    /**
     * UpdateVariable is responsible for handling all State variable update
     * needs for this State when it is the active State.
     * @param[in] theElapsedTime since the last Draw was called
     */
    virtual void UpdateVariable(float theElapsedTime);

    /**
     * Draw is responsible for handling all Drawing needs for this State
     * when it is the Active State.
     */
    virtual void Draw(void);

  protected:
    /**
     * HandleCleanup is responsible for performing any cleanup required before
     * this State is removed.
     */
    virtual void HandleCleanup(void);

  private:
    // Variables
    /////////////////////////////////////////////////////////////////////////
    GQE::FontAsset  mWinFont;
    GQE::ImageAsset mBackground;
    GQE::ImageAsset mStart;
    GQE::ImageAsset mSettings;
    GQE::ImageAsset mExit;
	sf::Sprite      mBackgroundSprite;
	sf::Sprite      mStartSprite;
	sf::Sprite      mSettingsSprite;
	sf::Sprite      mExitSprite;

    /// Winner string
    sf::Text*       mWinnerText;


}; // class MenuState

#endif // GAME_STATE_HPP_INCLUDED

/**
 * @class GameState
 * @ingroup Examples
 * The TicTacToe GameState class provides the TicTacToe example game
 * implementation for the GQE library.
 *
 * Copyright (c) 2010-2011 Ryan Lindeman
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
