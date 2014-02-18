/**
 * Provides the TicTacToe GameState example in the GQE library.
 *
 * @file examples/tictactoe/src/GameState.cpp
 * @author Ryan Lindeman
 * @date 20110704 - Initial Release
 * @date 20110721 - Remove * from GetAsset() calls since it now returns TYPE&
 * @date 20110831 - Support new SFML2 snapshot changes
 * @date 20120421 - Use arial.ttf font since SFML 2 crashes on exit when using default font
 * @date 20120512 - Use new RAII Asset style
 * @date 20120630 - Fix mouse image of X or O and SFML 2 and Window mode.
 */
#include "MenuState.hpp"
#include <TVSource/Apps/GameState.hpp>
#include <TVSource/Interfaces/IApp.hpp>

MenuState::MenuState(GQE::IApp& theApp) :
  GQE::IState("Game",theApp),
  mWinFont("resources/Fonts/arial.ttf", GQE::AssetLoadNow),
  mBackground("resources/Graphics/BlackBG.png", GQE::AssetLoadNow),
  mStart("resources/Graphics/start.png", GQE::AssetLoadNow),
  mSettings("resources/Graphics/settings.png", GQE::AssetLoadNow),
  mExit("resources/Graphics/exit.png", GQE::AssetLoadNow),
  mWinnerText(NULL)
{
}

MenuState::~MenuState(void)
{
  delete mWinnerText;
  mWinnerText = NULL;
}

void MenuState::DoInit(void)
{
  // First call our base class implementation
  IState::DoInit();

  mBackgroundSprite.setTexture(mBackground.GetAsset());
  mStartSprite.setTexture(mStart.GetAsset());
  mStartSprite.setPosition((200.0f), (200.0f));
  mSettingsSprite.setTexture(mSettings.GetAsset());
  mSettingsSprite.setPosition((200.0f), (300.0f));
  mExitSprite.setTexture(mExit.GetAsset());
  mExitSprite.setPosition((200.0f), (400.0f));
  // Make sure our update loop is only called 30 times per second
  mApp.SetUpdateRate(30.0f);
}

void MenuState::ReInit(void)
{
  
}

void MenuState::HandleEvents(sf::Event theEvent)
{
  // Exit program if Escape key is pressed
    if((theEvent.type == sf::Event::KeyReleased) && (theEvent.key.code == sf::Keyboard::Escape))
    {
      // quits the app
		mApp.Quit(GQE::StatusAppOK);
      
    }


    if(theEvent.type == sf::Event::MouseButtonReleased)
    {
      // Determine what they have clicked on
      double col = (theEvent.mouseButton.x);
      double row = (theEvent.mouseButton.y);
      if((row < 300 && row > 200) && (col < 550 && col > 250))
      {
		  //Loads the game
        mApp.mStateManager.AddInactiveState(new(std::nothrow) GameState(mApp));
		mApp.mStateManager.DropActiveState();
      }
	  if((row < 500 && row > 400) && (col < 550 && col > 250))
      {
        // quits the app
		mApp.Quit(GQE::StatusAppOK);
      }


    }
}

void MenuState::UpdateFixed(void)
{
 
}

void MenuState::UpdateVariable(float theElapsedTime)
{
  
}

void MenuState::Draw(void)
{
  // Draw our Back Ground sprite
  mApp.mWindow.draw(mBackgroundSprite);
  //Render button sprites
  mApp.mWindow.draw(mStartSprite);
  mApp.mWindow.draw(mSettingsSprite);
  mApp.mWindow.draw(mExitSprite);
  
}

void MenuState::HandleCleanup(void)
{
}

/**
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
