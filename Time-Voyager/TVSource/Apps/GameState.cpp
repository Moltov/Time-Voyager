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
#include "GameState.hpp"
#include <TVSource/Apps/MenuState.hpp>
#include <TVSource/Interfaces/IApp.hpp>
#include <SFML/Graphics.hpp>
#include <TVSource/Entity/classes/Instance.hpp>
#include <TVSource/assets/ImageAsset.hpp>



GameState::GameState(GQE::IApp& theApp) :
  GQE::IState("Game",theApp),
  mAnimationSystem(theApp),
  mRenderSystem(theApp),
  mPlayer("player", 255),
  mWinFont("resources/Fonts/arial.ttf", GQE::AssetLoadNow),
  mBackground("resources/Graphics/Board.png", GQE::AssetLoadNow),
  mPlayer1("resources/Graphics/Player1.png", GQE::AssetLoadNow),
  mPlayer2("resources/Graphics/Player2.png", GQE::AssetLoadNow),
  mEmpty("resources/Graphics/Empty.png", GQE::AssetLoadNow),
  mCurrentPlayer(0),
  mWinnerText(NULL)
{
	mCharacterImage.loadFromFile("resources/Graphics/character1.png");
}

GameState::~GameState(void)
{
  delete mWinnerText;
  mWinnerText = NULL;
}

void GameState::DoInit(void)
{
  // First call our base class implementation
  IState::DoInit();

  // Register all ISystems for the Player prototype
  mPlayer.AddSystem(&mAnimationSystem);
  mPlayer.AddSystem(&mRenderSystem);

   // Create a single player instance and set its various properties
  mCharacter = mPlayer.MakeInstance();

  // Did we get a valid Instance? then set some of its properties now
  if(mCharacter != NULL)
  {
    // Set the player image
    mCharacter->mProperties.Set<sf::Sprite>("Sprite",
      sf::Sprite(mCharacterImage));

    // Get the SpriteRect property from our instance
    sf::IntRect anSpriteRect(0,64*2,64,64);
    mCharacter->mProperties.Set<sf::IntRect>("rSpriteRect", anSpriteRect);

    // Set our visible property
    mCharacter->mProperties.Set<bool>("bVisible", true);

    // Set our animation properties
    mCharacter->mProperties.Set<float>("fFrameDelay", 0.08f);
    mCharacter->mProperties.Set<sf::Vector2u>("wFrameModifier", sf::Vector2u(1,0));
    mCharacter->mProperties.Set<sf::IntRect>("rFrameRect",
        sf::IntRect(0,0,mCharacterImage.getSize().x, mCharacterImage.getSize().y));

    // Set initial position on the screen to the middle of the screen
    mCharacter->mProperties.Set<sf::Vector2f>("vPosition",
        sf::Vector2f((float)(mApp.mWindow.getSize().x - anSpriteRect.width) / 2,
          (float)(mApp.mWindow.getSize().y - anSpriteRect.height) / 2));
  }
  else
  {
    // Signal the application to exit
    mApp.Quit(GQE::StatusError);
  }


  // Load our Background image which will show the TicTacToe game board
  mBackgroundSprite.setTexture(mBackground.GetAsset());


  // Setup winner text color as White
  mWinnerText = new sf::Text("", mWinFont.GetAsset(), 30);
  mWinnerText->setColor(sf::Color::White);

  // Call ReInit to reset the board
  ReInit();

  // Make sure our update loop is only called 30 times per second
  mApp.SetUpdateRate(30.0f);
}

void GameState::ReInit(void)
{
  // Reset our board
  for(GQE::Uint8 row = 0; row < 3; row++)
  {
    for(GQE::Uint8 col = 0; col < 3; col++)
    {
      // Reset the sprite for this square to empty
      mBoardSprite[row][col].setTexture(mEmpty.GetAsset());
      mBoardSprite[row][col].setPosition((col*270.0f), (row*202.0f));

      // Set this squares owner to no player
      mBoardPlayer[row][col] = 0;
    }
  }

  // Set Cursor to Player 1 image
  mCursor.setTexture(mPlayer1.GetAsset());

  // Set Cursor scale to be 25% of original image
  mCursor.setScale(0.25f, 0.25f);

  // Set current player to player 1
  mCurrentPlayer = 1;

  // Reset our winner text
  mWinnerText->setString("");
}

void GameState::HandleEvents(sf::Event theEvent)
{
  // Exit program if Escape key is pressed
    if((theEvent.type == sf::Event::KeyReleased) && (theEvent.key.code == sf::Keyboard::Escape))
    {
      // 
		mApp.mStateManager.AddInactiveState(new(std::nothrow) MenuState(mApp));
	  mApp.mStateManager.DropActiveState();
    }


    if(theEvent.type == sf::Event::MouseButtonReleased)
    {
      // Determine which square they clicked on
      GQE::Uint8 col = (theEvent.mouseButton.x / 270);
      GQE::Uint8 row = (theEvent.mouseButton.y / 202);
      if(3 > col && 3 > row && mBoardPlayer[row][col] == 0)
      {
        // Set ownership of this square to the current player
        mBoardPlayer[row][col] = mCurrentPlayer;

        // Determine which Sprite to use for this square
        switch(mCurrentPlayer)
        {
          case 1:
            // Set Player 1 image for this square
            mBoardSprite[row][col].setTexture(mPlayer1.GetAsset());

            // Set Cursor to Player 2 image
            mCursor.setTexture(mPlayer2.GetAsset());

            // Switch to Player 2
            mCurrentPlayer = 2;
            break;
          case 2:
            // Set Player 2 image for this square
            mBoardSprite[row][col].setTexture(mPlayer2.GetAsset());

            // Set Cursor to Player 1 image
            mCursor.setTexture(mPlayer1.GetAsset());

            // Switch to Player 1
            mCurrentPlayer = 1;
            break;
          default:
            // Leave as empty, we shouldn't even be here!
            break;
        }
      }

      // If current player is 0 then the last game ended, start a new game
      if(0 == mCurrentPlayer)
      {
        // Reinitialize the board and start a new game
        ReInit();
      }
    }
}

void GameState::UpdateFixed(void)
{
  // Start with a tie game
  GQE::Uint8 anWinner = 3;

  // Check each row to see if some player has won!
  for(GQE::Uint8 row = 0; row < 3; row++)
  {
    // Make sure each column matches and that its not the Empty player (0)
    if(mBoardPlayer[row][0] != 0 &&
        mBoardPlayer[row][0] == mBoardPlayer[row][1] &&
        mBoardPlayer[row][0] == mBoardPlayer[row][2])
    {
      // Make a note of which player is the winner!
      anWinner = mBoardPlayer[row][0];
      break;
    }

    // Check for empty columns on each row
    if(mBoardPlayer[row][0] == 0 ||
        mBoardPlayer[row][1] == 0 ||
        mBoardPlayer[row][2] == 0 &&
        anWinner == 3)
    {
      // No tie game, there are still empty spaces
      anWinner = 0;
    }
  }

  // Check each column to see if some player has won!
  for(GQE::Uint8 col = 0; col < 3; col++)
  {
    // Make sure each column matches and that its not the Empty player (0)
    if(mBoardPlayer[0][col] != 0 &&
        mBoardPlayer[0][col] == mBoardPlayer[1][col] &&
        mBoardPlayer[0][col] == mBoardPlayer[2][col])
    {
      // Make a note of which player is the winner!
      anWinner = mBoardPlayer[0][col];
      break;
    }
  }

  // Check diagonals
  if(mBoardPlayer[1][1] != 0 &&
      ((mBoardPlayer[1][1] == mBoardPlayer[0][0] && mBoardPlayer[1][1] == mBoardPlayer[2][2]) ||
       (mBoardPlayer[1][1] == mBoardPlayer[0][2] && mBoardPlayer[1][1] == mBoardPlayer[2][0])))
  {
    anWinner = mBoardPlayer[1][1];
  }

  // Did we find a winner?
  if(anWinner == 1)
  {
    mWinnerText->setString("X's Win!");
    // Setup winner text in middle of screen
    mWinnerText->setPosition(355.0f,280.0f);
  }
  else if(anWinner == 2)
  {
    mWinnerText->setString("O's Win!");
    // Setup winner text in middle of screen
    mWinnerText->setPosition(355.0f,280.0f);
  }
  else if(anWinner == 3)
  {
    mWinnerText->setString("Tie Game");
    // Setup winner text in middle of screen
    mWinnerText->setPosition(340.0f,280.0f);
  }

  // Set current player and cursor to empty if a winner was declared
  if(anWinner != 0)
  {
    // Set Cursor to Player 1 image
    mCursor.setTexture(mEmpty.GetAsset());

    // Switch to empty (no player)
    mCurrentPlayer = 0;
  }
  mAnimationSystem.UpdateFixed();
}

void GameState::UpdateVariable(float theElapsedTime)
{
  // Draw the current player image at the mouse position
  mCursor.setPosition(sf::Mouse::getPosition(mApp.mWindow).x-32.0f,
    sf::Mouse::getPosition(mApp.mWindow).y-25.25f);
}

void GameState::Draw(void)
{
  // Draw our Board sprite
  mApp.mWindow.draw(mBackgroundSprite);

  for(GQE::Uint8 row = 0; row < 3; row++)
  {
    for(GQE::Uint8 col = 0; col < 3; col++)
    {
      // Draw our Board
      mApp.mWindow.draw(mBoardSprite[row][col]);
    }
  }

  // Draw winner text
  mApp.mWindow.draw(*mWinnerText);

  // Draw our cursor
  mApp.mWindow.draw(mCursor);

  // Allow our RenderSystem to draw our character
  mRenderSystem.Draw();
}

void GameState::HandleCleanup(void)
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
